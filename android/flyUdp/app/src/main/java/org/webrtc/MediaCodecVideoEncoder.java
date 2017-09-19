/*
 * libjingle
 * Copyright 2013 Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


package org.webrtc;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.media.MediaCodecInfo.CodecCapabilities;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileFilter;
import java.io.FileReader;
import java.nio.ByteBuffer;
import java.util.regex.Pattern;

// Java-side of peerconnection_jni.cc:MediaCodecVideoEncoder.
@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
// This class is an implementation detail of the Java PeerConnection API.
// MediaCodec is thread-hostile so this class must be operated on a single
// thread.
@SuppressLint("NewApi")
public class MediaCodecVideoEncoder {
  // This class is constructed, operated, and destroyed by its C++ incarnation,
  // so the class and its methods have non-public visibility.  The API this
  // class exposes aims to mimic the webrtc::VideoEncoder API as closely as
  // possibly to minimize the amount of translation work necessary.

  private static final String TAG = "MediaCodecVideoEncoder";

  // Tracks webrtc::VideoCodecType.
  public enum VideoCodecType {
	    VIDEO_CODEC_VP8,
	    VIDEO_CODEC_VP9,
	    VIDEO_CODEC_H264,
	    VIDEO_CODEC_I420,
	    VIDEO_CODEC_RED,
	    VIDEO_CODEC_ULPFEC,
	    VIDEO_CODEC_Generic,
	    VIDEO_CODEC_H265,
	    VIDEO_CODEC_Unknown
  }

  private static final int DEQUEUE_TIMEOUT = 0;  // Non-blocking, no wait.
  private Thread mediaCodecThread;
  private MediaCodec mediaCodec;
  private ByteBuffer[] outputBuffers;
  private static final String VP8_MIME_TYPE = "video/x-vnd.on2.vp8";
  private static final String H264_MIME_TYPE = "video/avc";
  private static final String H265_MIME_TYPE = "video/hevc";
  // List of supported HW VP8 codecs.
  private static final String[] supportedVp8HwCodecPrefixes =
    {"OMX.qcom.", "OMX.Nvidia.", "OMX.Exynos." };
  // List of supported HW H.264 codecs.
  private static final String[] supportedH264HwCodecPrefixes =
    {"OMX.qcom.", "OMX.IMG.", "OMX.ti.", "OMX.MTK."/*, "OMX.hantro."*/ };
  
  private static final String[] supportedH265HwCodecPrefixes =
	{"OMX.qcom.", "OMX.IMG.", "OMX.ti.", "OMX.MTK."/*, "OMX.hantro."*/ };
  // Bitrate modes - should be in sync with OMX_VIDEO_CONTROLRATETYPE defined
  
  private static final String codec_disabled_name = "OMX.IMG.TOPAZ.VIDEO.Encoder";
  
  // in OMX_Video.h
  private static final int VIDEO_ControlRateVariable = 1;
  private static final int VIDEO_ControlRateConstant = 2;
  // NV12 color format supported by QCOM codec, but not declared in MediaCodec -
  // see /hardware/qcom/media/mm-core/inc/OMX_QCOMExtns.h
  private static final int
    COLOR_QCOM_FORMATYUV420PackedSemiPlanar32m = 0x7FA30C04;
  // Allowable color formats supported by codec - in order of preference.
  private static final int[] supportedColorList = {
	CodecCapabilities.COLOR_FormatYUV420SemiPlanar,  //首选编码格式采用nv12，而不是yuv420
    CodecCapabilities.COLOR_FormatYUV420Planar,
    CodecCapabilities.COLOR_QCOM_FormatYUV420SemiPlanar,
    COLOR_QCOM_FORMATYUV420PackedSemiPlanar32m
  };
  private int colorFormat;
  // Video encoder type.
  private VideoCodecType type;
  // SPS and PPS NALs (Config frame) for H.264.
  private ByteBuffer configData = null;

  private MediaCodecVideoEncoder() {}

  // Helper struct for findHwEncoder() below.
  private static class EncoderProperties {
    public EncoderProperties(String codecName, int colorFormat) {
      this.codecName = codecName;
      this.colorFormat = colorFormat;
    }
    public final String codecName; // OpenMax component name for HW codec.
    public final int colorFormat;  // Color format supported by codec.
  }

  /* get cpu frequnce, (khz) */
  public static int getCurCpuMaxFreq() {
      int result = 0;
      String kCpuInfoCurFreqFilePath = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq";
      FileReader fr = null;
      BufferedReader br = null;
      try {
          fr = new FileReader(kCpuInfoCurFreqFilePath);
          br = new BufferedReader(fr);
          String text = br.readLine();
          result = Integer.parseInt(text.trim());
          br.close();
      } catch (Exception e) {
          e.printStackTrace();
      } 
      result = result/1000;
     
      Log.i(TAG, "cpu freq:  " + result);
      return result;
  }
  
  
  public static int getNumCores() {
      //Private Class to display only CPU devices in the directory listing
      class CpuFilter implements FileFilter {
          @Override
          public boolean accept(File pathname) {
              //Check if filename is "cpu", followed by a single digit number
              if(Pattern.matches("cpu[0-9]", pathname.getName())) {
                  return true;
              }
              return false;
          }      
      }

      try {
          //Get directory containing CPU info
          File dir = new File("/sys/devices/system/cpu/");
          //Filter to only list the devices we care about
          File[] files = dir.listFiles(new CpuFilter());
          Log.d(TAG, "CPU Count: "+files.length);
          //Return the number of cores (virtual CPU devices)
          return files.length;
      } catch(Exception e) {
          //Print exception
          Log.d(TAG, "CPU Count: Failed.");
          e.printStackTrace();
          //Default to return 1 core
          return 1;
      }
  }
  
  @SuppressLint("NewApi")
private static EncoderProperties findHwEncoder(
      String mime, String[] supportedHwCodecPrefixes) {
    if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT)
      return null; // MediaCodec.setParameters is missing.

    for (int i = 0; i < MediaCodecList.getCodecCount(); ++i) {
      MediaCodecInfo info = MediaCodecList.getCodecInfoAt(i);
      if (!info.isEncoder()) {
        continue;
      }
      String name = null;
      for (String mimeType : info.getSupportedTypes()) {
        if (mimeType.equals(mime)) {
          name = info.getName();
          break;
        }
      }
      if (name == null) {
        continue;  // No HW support in this codec; try the next one.
      }
      Log.i(TAG, "Found candidate encoder " + name);
      
      if (name.equals(codec_disabled_name)) {	  
          int Maxfeq = getCurCpuMaxFreq();  
          int ncpu = getNumCores();  
          Log.i(TAG, "CurCpuMaxFreq: "+ Maxfeq +" NumCores: "+ncpu);
          if(Maxfeq<=1305 && ncpu<=8)
          {
              Log.e(TAG, "findHwEncoder: " + name +" ,but disable this hw codec.");
              return null;       	  
          }

        }
      
      // Check if this is supported HW encoder.
      boolean supportedCodec = false;
      for (String hwCodecPrefix : supportedHwCodecPrefixes) {
        if (name.startsWith(hwCodecPrefix)) {
          supportedCodec = true;
          break;
        }
      }
      if (!supportedCodec) {
        continue;
      }

      CodecCapabilities capabilities = info.getCapabilitiesForType(mime);
      for (int colorFormat : capabilities.colorFormats) {
        Log.v(TAG, "   Color: 0x" + Integer.toHexString(colorFormat));
      }

      // Check if codec supports either yuv420 or nv12.
      for (int supportedColorFormat : supportedColorList) {
        for (int codecColorFormat : capabilities.colorFormats) {
          if (codecColorFormat == supportedColorFormat) {
            // Found supported HW encoder.
            Log.e(TAG, "Found target encoder for mime " + mime + " : " + name +
                ". Color: 0x" + Integer.toHexString(codecColorFormat));
            return new EncoderProperties(name, codecColorFormat);
          }
        }
      }
    }
    return null;  // No HW VP8 encoder.
  }

  public static boolean isVp8HwSupported() {
    return findHwEncoder(VP8_MIME_TYPE, supportedVp8HwCodecPrefixes) != null;
  }

  public static boolean isH264HwSupported() {
    return findHwEncoder(H264_MIME_TYPE, supportedH264HwCodecPrefixes) != null;
  }

  public static boolean isH265HwSupported() {
	    return findHwEncoder(H265_MIME_TYPE, supportedH264HwCodecPrefixes) != null;
	  }
  
  private void checkOnMediaCodecThread() {
    if (mediaCodecThread.getId() != Thread.currentThread().getId()) {
      throw new RuntimeException(
          "MediaCodecVideoEncoder previously operated on " + mediaCodecThread +
          " but is now called on " + Thread.currentThread());
    }
  }

  static MediaCodec createByCodecName(String codecName) {
    try {
      // In the L-SDK this call can throw IOException so in order to work in
      // both cases catch an exception.
      return MediaCodec.createByCodecName(codecName);
    } catch (Exception e) {
      return null;
    }
  }

  // Return the array of input buffers, or null on failure.
  private ByteBuffer[] initEncode(
      VideoCodecType type, int width, int height, int kbps, int fps) {
    Log.i(TAG, "Java initEncode: " + type + " : " + width + " x " + height +
        ". @ " + kbps + " kbps. Fps: " + fps +
        ". Color: 0x" + Integer.toHexString(colorFormat));
    if (mediaCodecThread != null) {
      throw new RuntimeException("Forgot to release()?");
    }
    this.type = type;
    EncoderProperties properties = null;
    String mime = null;
    int keyFrameIntervalSec = 0;

    if (type == VideoCodecType.VIDEO_CODEC_VP8) {
      mime = VP8_MIME_TYPE;
      properties = findHwEncoder(VP8_MIME_TYPE, supportedVp8HwCodecPrefixes);
      keyFrameIntervalSec = 100;
    } else if (type == VideoCodecType.VIDEO_CODEC_H264) {
      mime = H264_MIME_TYPE;
      properties = findHwEncoder(H264_MIME_TYPE, supportedH264HwCodecPrefixes);
      keyFrameIntervalSec = 10;
    }
    else if (type == VideoCodecType.VIDEO_CODEC_H265) {
      mime = H265_MIME_TYPE;
      properties = findHwEncoder(H265_MIME_TYPE, supportedH265HwCodecPrefixes);
      keyFrameIntervalSec = 10;
    }
    if (properties == null) {
      throw new RuntimeException("Can not find HW encoder for " + type);
    }
    mediaCodecThread = Thread.currentThread();
    try {
      MediaFormat format = MediaFormat.createVideoFormat(mime, width, height);
      format.setInteger(MediaFormat.KEY_BIT_RATE, 1000 * kbps);
      format.setInteger(MediaFormat.KEY_PROFILE, 0x01);/**< Baseline profile */
      format.setInteger(MediaFormat.KEY_LEVEL, 0x20);   //Level 2
      format.setInteger(MediaFormat.KEY_BITRATE_MODE, VIDEO_ControlRateConstant);
      format.setInteger(MediaFormat.KEY_COLOR_FORMAT, properties.colorFormat);
      format.setInteger(MediaFormat.KEY_FRAME_RATE, fps);
      format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, keyFrameIntervalSec);
      Log.e(TAG, "  Format: " + format);
      mediaCodec = createByCodecName(properties.codecName);
      if (mediaCodec == null) {
        return null;
      }
      mediaCodec.configure(
          format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
      mediaCodec.start();
      colorFormat = properties.colorFormat;
      outputBuffers = mediaCodec.getOutputBuffers();
      ByteBuffer[] inputBuffers = mediaCodec.getInputBuffers();
      Log.e(TAG, "Input buffers: " + inputBuffers.length +
          ". Output buffers: " + outputBuffers.length);
      return inputBuffers;
    } catch (IllegalStateException e) {
      Log.e(TAG, "initEncode failed", e);
      return null;
    }
  }

  private boolean encode(
      boolean isKeyframe, int inputBuffer, int size,
      long presentationTimestampUs) {
    checkOnMediaCodecThread();
    try {
      if (isKeyframe) {
        // Ideally MediaCodec would honor BUFFER_FLAG_SYNC_FRAME so we could
        // indicate this in queueInputBuffer() below and guarantee _this_ frame
        // be encoded as a key frame, but sadly that flag is ignored.  Instead,
        // we request a key frame "soon".
        Log.i(TAG, "Sync frame request");
        Bundle b = new Bundle();
        b.putInt(MediaCodec.PARAMETER_KEY_REQUEST_SYNC_FRAME, 0);
        mediaCodec.setParameters(b);
      }
      mediaCodec.queueInputBuffer(
          inputBuffer, 0, size, presentationTimestampUs, 0);
      return true;
    }
    catch (IllegalStateException e) {
      Log.e(TAG, "encode failed", e);
      return false;
    }
  }

  private void release() {
    Log.d(TAG, "Java releaseEncoder");
    checkOnMediaCodecThread();
    try {
      mediaCodec.stop();
      mediaCodec.release();
    } catch (IllegalStateException e) {
      Log.e(TAG, "release failed", e);
    }
    mediaCodec = null;
    mediaCodecThread = null;
  }

  private boolean setRates(int kbps, int frameRateIgnored) {
    // frameRate argument is ignored - HW encoder is supposed to use
    // video frame timestamps for bit allocation.
    checkOnMediaCodecThread();
    Log.i(TAG, "setRates: " + kbps + " kbps. Fps: " + frameRateIgnored);
    try {
      Bundle params = new Bundle();
      params.putInt(MediaCodec.PARAMETER_KEY_VIDEO_BITRATE, 1000 * kbps);
      mediaCodec.setParameters(params);
      return true;
    } catch (IllegalStateException e) {
      Log.e(TAG, "setRates failed", e);
      return false;
    }
  }

  // Dequeue an input buffer and return its index, -1 if no input buffer is
  // available, or -2 if the codec is no longer operative.
  private int dequeueInputBuffer() {
    checkOnMediaCodecThread();
    try {
      return mediaCodec.dequeueInputBuffer(DEQUEUE_TIMEOUT);
    } catch (IllegalStateException e) {
      Log.e(TAG, "dequeueIntputBuffer failed", e);
      return -2;
    }
  }

  // Helper struct for dequeueOutputBuffer() below.
  private static class OutputBufferInfo {
    public OutputBufferInfo(
        int index, ByteBuffer buffer,
        boolean isKeyFrame, long presentationTimestampUs) {
      this.index = index;
      this.buffer = buffer;
      this.isKeyFrame = isKeyFrame;
      this.presentationTimestampUs = presentationTimestampUs;
    }

    private final int index;
    private final ByteBuffer buffer;
    private final boolean isKeyFrame;
    private final long presentationTimestampUs;
  }

  // Dequeue and return an output buffer, or null if no output is ready.  Return
  // a fake OutputBufferInfo with index -1 if the codec is no longer operable.
  private OutputBufferInfo dequeueOutputBuffer() {
    checkOnMediaCodecThread();
    try {
      MediaCodec.BufferInfo info = new MediaCodec.BufferInfo();
      int result = mediaCodec.dequeueOutputBuffer(info, DEQUEUE_TIMEOUT);
      // Check if this is config frame and save configuration data.
      if (result >= 0) {
        boolean isConfigFrame =
            (info.flags & MediaCodec.BUFFER_FLAG_CODEC_CONFIG) != 0;
        if (isConfigFrame) {
          Log.i(TAG, "Config frame generated. Offset: " + info.offset +
              ". Size: " + info.size);
          configData = ByteBuffer.allocateDirect(info.size);
          outputBuffers[result].position(info.offset);
          outputBuffers[result].limit(info.offset + info.size);
          configData.put(outputBuffers[result]);
          // Release buffer back.
          mediaCodec.releaseOutputBuffer(result, false);
          // Query next output.
          result = mediaCodec.dequeueOutputBuffer(info, DEQUEUE_TIMEOUT);
        }
      }
      if (result >= 0) {
        // MediaCodec doesn't care about Buffer position/remaining/etc so we can
        // mess with them to get a slice and avoid having to pass extra
        // (BufferInfo-related) parameters back to C++.
        ByteBuffer outputBuffer = outputBuffers[result].duplicate();
        outputBuffer.position(info.offset);
        outputBuffer.limit(info.offset + info.size);
        // Check key frame flag.
        boolean isKeyFrame =
            (info.flags & MediaCodec.BUFFER_FLAG_SYNC_FRAME) != 0;
        if (isKeyFrame) {
          Log.d(TAG, "Sync frame generated");
        }
        if (isKeyFrame && (type == VideoCodecType.VIDEO_CODEC_H264||type == VideoCodecType.VIDEO_CODEC_H265)) {
          Log.d(TAG, "Appending config frame of size " + configData.capacity() +
              " to output buffer with offset " + info.offset + ", size " +
              info.size);
          // For H.264 key frame append SPS and PPS NALs at the start
          ByteBuffer keyFrameBuffer = ByteBuffer.allocateDirect(
              configData.capacity() + info.size);
          configData.rewind();
          keyFrameBuffer.put(configData);
          keyFrameBuffer.put(outputBuffer);
          keyFrameBuffer.position(0);
          return new OutputBufferInfo(result, keyFrameBuffer,
              isKeyFrame, info.presentationTimeUs);
        } else {
          return new OutputBufferInfo(result, outputBuffer.slice(),
              isKeyFrame, info.presentationTimeUs);
        }
      } else if (result == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED) {
        outputBuffers = mediaCodec.getOutputBuffers();
        return dequeueOutputBuffer();
      } else if (result == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED) {
        return dequeueOutputBuffer();
      } else if (result == MediaCodec.INFO_TRY_AGAIN_LATER) {
        return null;
      }
      throw new RuntimeException("dequeueOutputBuffer: " + result);
    } catch (IllegalStateException e) {
      Log.e(TAG, "dequeueOutputBuffer failed", e);
      return new OutputBufferInfo(-1, null, false, -1);
    }
  }

  // Release a dequeued output buffer back to the codec for re-use.  Return
  // false if the codec is no longer operable.
  private boolean releaseOutputBuffer(int index) {
    checkOnMediaCodecThread();
    try {
      mediaCodec.releaseOutputBuffer(index, false);
      return true;
    } catch (IllegalStateException e) {
      Log.e(TAG, "releaseOutputBuffer failed", e);
      return false;
    }
  }
}
