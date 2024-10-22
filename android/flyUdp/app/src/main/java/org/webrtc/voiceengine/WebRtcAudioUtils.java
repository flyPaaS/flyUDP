/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

package org.webrtc.voiceengine;

import java.lang.Thread;

import android.media.AudioManager;
import android.os.Build;
import android.util.Log;

public final class WebRtcAudioUtils {
	// Use 16kHz as the default sampling rate.
	private static final int SAMPLE_RATE_HZ = 16000;

	public static boolean runningOnJellyBeanOrHigher() {
		return Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN;
	}

	public static boolean runningOnJellyBeanMR1OrHigher() {
		return Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1;
	}

	public static boolean runningOnLollipopOrHigher() {
		return Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP;
	}

	/** Helper method for building a string of thread information. */
	public static String getThreadInfo() {
	    return "@[name=" + Thread.currentThread().getName()
	        + ", id=" + Thread.currentThread().getId() + "]";
	}

	/** Information about the current build, taken from system properties. */
	public static void logDeviceInfo(String tag) {
	    Log.i(tag, "Android SDK: " + Build.VERSION.SDK_INT + ", "
	        + "Release: " + Build.VERSION.RELEASE + ", "
	        + "Brand: " + Build.BRAND + ", "
	        + "Device: " + Build.DEVICE + ", "
	        + "Id: " + Build.ID + ", "
	        + "Hardware: " + Build.HARDWARE + ", "
	        + "Manufacturer: " + Build.MANUFACTURER + ", "
	        + "Model: " + Build.MODEL + ", "
	        + "Product: " + Build.PRODUCT);
	}

	/**
	 * Returns the native or optimal output sample rate for this device's
	 * primary output stream. Unit is in Hz.
	 */
	public static int GetNativeSampleRate(AudioManager audioManager) {
		/*if (!WebRtcAudioUtils.runningOnJellyBeanMR1OrHigher()) {
			return SAMPLE_RATE_HZ;
		}
		String sampleRateString = audioManager
				.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
		Log.i("WebRtc-Utils", "SampleRate = " + sampleRateString);
		return (sampleRateString == null) ? SAMPLE_RATE_HZ : Integer
				.parseInt(sampleRateString);*/
		
		 return SAMPLE_RATE_HZ;
	}
	
	public static String Brand() {
		return Build.BRAND;
	}
	
	public static String Model() {
		return Build.MODEL.replaceAll(" ", "");
	}
	
	public static String Board() {
		return Build.BOARD;
	}
	
	public static int SDK() {
		return Build.VERSION.SDK_INT;
	}
}
