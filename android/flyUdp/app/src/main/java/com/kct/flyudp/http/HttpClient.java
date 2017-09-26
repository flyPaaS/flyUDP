package com.kct.flyudp.http;

import android.annotation.SuppressLint;

import com.kct.flyudp.UIData;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.BasicHttpEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.json.JSONObject;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by zhouwq on 2017/3/8/008.
 * 和服务器交互接口
 */

@SuppressWarnings("deprecation")
public class HttpClient {
    // RTMP 请求sessionId
    public static String RtmpCreate(String ip, String port, String sessionId) {
        try {
            // 构造请求参数
            String mTimestamp = DateToStr();
            EncryptUtil mEncryptUtil = new EncryptUtil();
            String sig = getSignature(UIData.Sid, UIData.Token, mTimestamp, mEncryptUtil);
            // 构造请求 URL
            String url = UIData.REST_API;
            url += "/Accounts/";
            url += UIData.Sid;
            url += "/session/create?sig=";
            url += sig;
            // 构造请求 Body
            JSONObject json = new JSONObject();
            JSONObject jsonobj = new JSONObject();
            json.put("appId", UIData.AppId);
            json.put("sessionId", sessionId);
            json.put("policy", "1");
            json.put("hopNum", "0");
            json.put("routeNum", "1");
            json.put("protocol", "tcp");
            json.put("srcIp", UIData.LOCAL_IP);
            json.put("dstIp", ip);
            json.put("dstPort", port);
            jsonobj.put("sessionInfo", json);
            String body = jsonobj.toString();
            // POST POST 接口
            HttpPost mHttpPost = new HttpPost(url);
            mHttpPost.setHeader("Accept", "application/json");
            mHttpPost.setHeader("Content-Type", "application/json;charset=utf-8");
            String src = UIData.Sid + ":" + mTimestamp;
            String auth = mEncryptUtil.base64Encoder(src);
            mHttpPost.setHeader("Authorization", auth);
            if (body != null && body.length() > 0) {
                BasicHttpEntity requestBody = new BasicHttpEntity();
                requestBody.setContent(new ByteArrayInputStream(body.getBytes("UTF-8")));
                requestBody.setContentLength(body.getBytes("UTF-8").length);
                mHttpPost.setEntity(requestBody);
            }
            DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpPost);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    // RTMP 释放sessionId
    public static String RtmpRelease(String sessionId) {
        try {
            // 构造请求参数
            String mTimestamp = DateToStr();
            EncryptUtil mEncryptUtil = new EncryptUtil();
            String sig = getSignature(UIData.Sid, UIData.Token, mTimestamp, mEncryptUtil);
            // 构造请求 URL
            String url = UIData.REST_API;
            url += "/Accounts/";
            url += UIData.Sid;
            url += "/session/release?sig=";
            url += sig;
            // 构造请求 Body
            JSONObject json = new JSONObject();
            JSONObject jsonobj = new JSONObject();
            json.put("appId", UIData.AppId);
            json.put("sessionId", sessionId);
            jsonobj.put("sessionInfo", json);
            String body = jsonobj.toString();
            // POST POST 接口
            HttpPost mHttpPost = new HttpPost(url);
            mHttpPost.setHeader("Accept", "application/json");
            mHttpPost.setHeader("Content-Type", "application/json;charset=utf-8");
            String src = UIData.Sid + ":" + mTimestamp;
            String auth = mEncryptUtil.base64Encoder(src);
            mHttpPost.setHeader("Authorization", auth);
            if (body != null && body.length() > 0) {
                BasicHttpEntity requestBody = new BasicHttpEntity();
                requestBody.setContent(new ByteArrayInputStream(body.getBytes("UTF-8")));
                requestBody.setContentLength(body.getBytes("UTF-8").length);
                mHttpPost.setEntity(requestBody);
            }
            DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpPost);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    // 组建请求
    public static String PushRequest(String ip, String port, String stream, boolean bCan) {
        String url = "http://";
        url += ip;
        url += ":";
        url += port;
        url += "/udprelay/v1/streamPush?streamId=";
        url += stream;
        url += "&streamCan=";
        if (bCan) {
            url += "1";
        } else {
            url += "0";
        }

        HttpGet mHttpGet = new HttpGet(url);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 释放请求
    public static String PushRelease(String ip, String port, String stream, boolean bCan) {
        String url = "http://";
        url += ip;
        url += ":";
        url += port;
        url += "/udprelay/v1/streamRelease?streamId=";
        url += stream;
        url += "&streamCan=";
        if (bCan) {
            url += "1";
        } else {
            url += "0";
        }

        HttpGet mHttpGet = new HttpGet(url);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 组建请求
    public static String PullRequest(String ip, String port, String stream, boolean bCan) {
        String url = "http://";
        url += ip;
        url += ":";
        url += port;
        url += "/udprelay/v1/streamPull?streamId=";
        url += stream;
        url += "&streamCan=";
        if (bCan) {
            url += "1";
        } else {
            url += "0";
        }

        HttpGet mHttpGet = new HttpGet(url);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 释放请求
    public static String PullRelease(String ip, String port, String stream, boolean bCan) {
        String url = "http://";
        url += ip;
        url += ":";
        url += port;
        url += "/udprelay/v1/pullStop?streamId=";
        url += stream;
        url += "&streamCan=";
        if (bCan) {
            url += "1";
        } else {
            url += "0";
        }

        HttpGet mHttpGet = new HttpGet(url);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 获取本地IP
    public static String GetLocalIP() {
        HttpGet mHttpGet = new HttpGet(UIData.GET_LOCAL_IP);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 获取RTMP URL
    public static String GetRtmpServer() {
        HttpGet mHttpGet = new HttpGet(UIData.RTMP_GET_URL);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 获取UDP URL
    public static String GetUdpServer() {
        HttpGet mHttpGet = new HttpGet(UIData.UDP_GET_URL);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 获取可用的UDP拉流服务器和流ID
    public static String GetPullServer(String strIp, int nPort) {
        String strUrl = "http://" + strIp + ":" + String.valueOf(nPort) + "/udprelay/v1/getStreamList?";
        HttpGet mHttpGet = new HttpGet(strUrl);
        mHttpGet.setHeader("Accept", "application/json");
        mHttpGet.setHeader("Content-Type", "application/json;charset=utf-8");
        DefaultHttpClient mDefaultHttpClient = new DefaultHttpClient();
        try {
            HttpResponse mHttpResponse = mDefaultHttpClient.execute(mHttpGet);
            HttpEntity mHttpEntity = mHttpResponse.getEntity();
            if (mHttpEntity != null) {
                return EntityUtils.toString(mHttpEntity, "UTF-8");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    // 获取MD5加密后的数据
    private static String getSignature(String accountSid, String authToken, String timestamp, EncryptUtil encryptUtil) throws Exception {
        String sig = accountSid + authToken + timestamp;
        return encryptUtil.md5Digest(sig);
    }

    @SuppressLint("SimpleDateFormat")
    private static String DateToStr() {
        SimpleDateFormat formatter = new SimpleDateFormat("yyyyMMddHHmmss");
        return formatter.format(new Date());
    }
}
