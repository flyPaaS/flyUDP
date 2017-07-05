package com.kct.flyudp.http;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import java.io.IOException;

/**
 * Created by zhouwq on 2017/3/8/008.
 * 和服务器交互接口
 */

@SuppressWarnings("deprecation")
public class HttpClient {

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
        }
        else {
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
        }
        else {
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
        }
        else {
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

    public static String GetPushServer() {
        String url = "http://59.110.10.28:8097/v3/getudprelay?";
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
}
