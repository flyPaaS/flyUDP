package com.kct.flyudp;

/**
 * Created by zhouwq on 2017/6/16/016.
 * 数据类
 */

public class UIData {
    public static final String ACTION_NETWORK_STATE = "udp.push.network";
    public static final String ACTION_KEY = "network";
    
    // URL
    public static String REST_API_BASE = "60.205.137.243:80";
    public static String CPS_URL_BASE = "59.110.10.28:8097";
    
    // 获取本地公网IP
    public static String GET_LOCAL_IP = "http://" + CPS_URL_BASE + "/v3/getnatip?";
    public static String LOCAL_IP = "";

    // RTMP Rest API URL
    public static String REST_API = "http://" + REST_API_BASE + "/2017-03-28";
	// RTMP 获取接入服务器地址
    public static String RTMP_GET_URL = "http://" + CPS_URL_BASE + "/v3/getsrslist?";
    // UDP 获取接入服务器地址
    public static String UDP_GET_URL = "http://" + CPS_URL_BASE + "/v3/getudprelay?";
    
    // 更新URL
    public static void UpdateUrl() {
    	GET_LOCAL_IP = "http://" + CPS_URL_BASE + "/v3/getnatip?";
    	REST_API = "http://" + REST_API_BASE + "/2017-03-28";
    	RTMP_GET_URL = "http://" + CPS_URL_BASE + "/v3/getsrslist?";
    	UDP_GET_URL = "http://" + CPS_URL_BASE + "/v3/getudprelay?";
    }
    
    // RTMP Rest API 参数
    public static boolean bOut = true;
    public static String Sid = bOut ? "b64e977c108810429b9056208059d362" : "809d2c33e8ba713460083ee65de42a71";
    public static String Token = bOut ? "cd1e4ce88775dcaf8bbf9236e9811c4a" : "980e7daebdf7fc4aa6f55bda74b41d17";
    public static String AppId = bOut ? "424c285552334a86ae671463dfeca811" : "cac7d7ae1d3040b886b2766d69ce11b3";
    public static void UpdateSid() {
    	Sid = bOut ? "b64e977c108810429b9056208059d362" : "809d2c33e8ba713460083ee65de42a71";
        Token = bOut ? "cd1e4ce88775dcaf8bbf9236e9811c4a" : "980e7daebdf7fc4aa6f55bda74b41d17";
        AppId = bOut ? "424c285552334a86ae671463dfeca811" : "cac7d7ae1d3040b886b2766d69ce11b3";
    }

	// 码率选择
	// 0--200kbps
	// 1--300kbps
	// 2--400kbps
	// 3--500kbps
	// 4--600kbps
	// 5--700kbps
    // 6--800kbps
    // 7--900kbps
    // 8--1000kbps
	public static int nCodec = 0;
}
