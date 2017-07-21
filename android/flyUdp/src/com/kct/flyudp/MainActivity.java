package com.kct.flyudp;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.kct.flyudp.http.HttpClient;

import java.util.ArrayList;

public class MainActivity extends Activity {
	// TAG
	public static final String TAG = "KC";
	
	// RTMP,UDP Push Pull 选择
    public int nSelectType = 0;
    public CheckBox rtmp_pushSelect = null;
    public CheckBox rtmp_pullSelect = null;
    public CheckBox udp_pushSelect = null;
    public CheckBox udp_pullSelect = null;

    // 服务器列表
    public ListView mListSerIP = null;
    public ServerAdapter mServerAdapter = null;
    public int nSelectServer = 0;
    // RTMP服务器数据
    public ArrayList<String> mRtmpServerIp = new ArrayList<String>();
    public ArrayList<String> mRtmpServerList = new ArrayList<String>();
    // UDP服务器数据
    public ArrayList<String> mUDPServerIp = new ArrayList<String>();
    public ArrayList<String> mUDPServerList = new ArrayList<String>();
    
    // 服务器端口
    public EditText mEditSerPort = null;

    // 流ID
    public EditText mEditSerStream = null;
    public String strStreamRtmpPushId = "";
    public String strStreamRtmpPullId = "";
    public String strStreamUdpPushId = "";
    public String strStreamUdpPullId = "";
    // sessionId
    public String strPushSessionId = "";
    public String strPullSessionId = "";
    // flyCan选择
    public RadioGroup mRadioGroup = null;
    public int nSelectCan = 0;
    
    // 设置按键
    public TextView mTextEdit = null;
    // 推拉流按键
    public TextView mTextView = null;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 全屏显示
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        MainApplication.getInstance().mMainActivity = this;
        // 业务类型选择
        nSelectType = 0;
        rtmp_pushSelect = (CheckBox)findViewById(R.id.rtmp_push_select);
        rtmp_pullSelect = (CheckBox)findViewById(R.id.rtmp_pull_select);
        udp_pushSelect = (CheckBox)findViewById(R.id.udp_push_select);
        udp_pullSelect = (CheckBox)findViewById(R.id.udp_pull_select);
        rtmp_pushSelect.setChecked(true);
        rtmp_pullSelect.setChecked(false);
        udp_pushSelect.setChecked(false);
        udp_pullSelect.setChecked(false);
        // 设置按键
        mTextEdit = (TextView)findViewById(R.id.view_edit);
        // 服务器地址
        mListSerIP = (ListView) findViewById(R.id.listServer);
        mServerAdapter = new ServerAdapter(this);
        mListSerIP.setAdapter(mServerAdapter);
        // 服务器端口和流ID
        mEditSerPort = (EditText) findViewById(R.id.udp_push_port);
        mEditSerStream = (EditText) findViewById(R.id.udp_push_stream);
        UpdatePortCtrl();
        UpdateStreamCtrl(true);
        // 设置
        mTextEdit.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent mIntent = new Intent(MainActivity.this, EditActivity.class);
                startActivity(mIntent);
			}
		});
        
        // 推拉流切换
        rtmp_pushSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 0) {
                    return;
                }
                // 切换类型
                nSelectType = 0;
                // 更新参数
                UpdateServer();
                UpdatePortCtrl();
                UpdateStreamCtrl(false);
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_push));
                // 更新UI显示
                rtmp_pushSelect.setChecked(true);
                rtmp_pullSelect.setChecked(false);
                udp_pushSelect.setChecked(false);
                udp_pullSelect.setChecked(false);
            }
        });
        rtmp_pullSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 1) {
                    return;
                }
                // 切换类型
                nSelectType = 1;
                // 更新参数
                UpdateServer();
                UpdatePortCtrl();
                UpdateStreamCtrl(false);
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_pull));
                // 更新UI显示
                rtmp_pushSelect.setChecked(false);
                rtmp_pullSelect.setChecked(true);
                udp_pushSelect.setChecked(false);
                udp_pullSelect.setChecked(false);
            }
        });
        
        udp_pushSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 2) {
                    return;
                }
                // 切换类型
                nSelectType = 2;
                // 更新参数
                UpdateServer();
                UpdatePortCtrl();
                UpdateStreamCtrl(false);
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_push));
                // 更新UI显示
                rtmp_pushSelect.setChecked(false);
                rtmp_pullSelect.setChecked(false);
                udp_pushSelect.setChecked(true);
                udp_pullSelect.setChecked(false);
            }
        });
        udp_pullSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 3) {
                    return;
                }
                // 切换类型
                nSelectType = 3;
                // 更新参数
                UpdateServer();
                UpdatePortCtrl();
                UpdateStreamCtrl(false);
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_pull));
                // 更新UI显示
                rtmp_pushSelect.setChecked(false);
                rtmp_pullSelect.setChecked(false);
                udp_pushSelect.setChecked(false);
                udp_pullSelect.setChecked(true);              
            }
        });

        // 单选框是否flyCan
        mRadioGroup = (RadioGroup)findViewById(R.id.rg);
        mRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (checkedId == R.id.rb1)
                {
                    nSelectCan = 0;
                }
                else if (checkedId == R.id.rb2) {
                    nSelectCan = 1;
                }
            }
        });
        
        // 按钮
        mTextView = (TextView) findViewById(R.id.push_btn);
        mTextView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if (nSelectType == 0 || nSelectType == 1) {
            		// RTMP
            		if (mRtmpServerList.size() <= 0) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_ip), Toast.LENGTH_LONG).show();
                        return;
                    }
                    if (mEditSerPort.getText().toString().isEmpty()) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_port), Toast.LENGTH_LONG).show();
                        return;
                    }
                    if (mEditSerStream.getText().toString().isEmpty()) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_stream), Toast.LENGTH_LONG).show();
                        return;
                    }
					if (nSelectType == 0) {
						// Rtmp Push
						new Thread(new Runnable() {
							@Override
							public void run() {
								strStreamRtmpPushId = mEditSerStream.getText().toString();
								boolean bCan = (nSelectCan != 0);
								if (bCan) {
									// 判断内外网
									if (UIData.REST_API_BASE.contains("192.168.")) {
										UIData.bOut = false;
										UIData.UpdateSid();
									} else {
										UIData.bOut = true;
										UIData.UpdateSid();
									}
									// Rest
									String strUrl = mRtmpServerIp.get(nSelectServer);
									String[] strTmp = strUrl.split(":");
									String strResult = HttpClient.RtmpCreate(strTmp[0], mEditSerPort.getText().toString(), strStreamRtmpPushId);
									if (strResult != null && !strResult.equals("")) {
										Log.e(TAG, "RtmpCreate resp = " + strResult);
										try {
											JSONObject jsonRoot = new JSONObject(strResult);
											if (jsonRoot.has("resp")) {
												JSONObject jsonChild = jsonRoot.getJSONObject("resp");
												if (jsonChild.has("respCode")) {
													String strCode = jsonChild.getString("respCode");
													if (strCode.equals("000000")) {
														if (jsonChild.has("sessionId")) {
															strPushSessionId = jsonChild.getString("sessionId");
														}
														if (jsonChild.has("routes")) {
															JSONObject strObj = jsonChild.getJSONObject("routes");
															MainApplication.getInstance().strRouteId = strObj.getString("routeid");
															MainApplication.getInstance().strSrcIp = strObj.getString("srcApIp");
															MainApplication.getInstance().strSrcPort = strObj.getString("srcApPort");
															MainApplication.getInstance().strDstIp = strObj.getString("dstApIp");
															MainApplication.getInstance().strDstPort = strObj.getString("dstApPort");
															mHandler.sendEmptyMessage(1001);
															return;
														}
													}
												}
											}
										} catch (JSONException e) {
											e.printStackTrace();
										}
									}
									mHandler.sendEmptyMessage(1000);
								} else {
									mHandler.sendEmptyMessage(1001);
								}
							}
						}).start();
					} else {
						// Rtmp Pull
						new Thread(new Runnable() {
							@Override
							public void run() {
								strStreamRtmpPullId = mEditSerStream.getText().toString();
								boolean bCan = (nSelectCan != 0);
								if (bCan) {
									// 判断内外网
									if (UIData.REST_API_BASE.contains("192.168.")) {
										UIData.bOut = false;
										UIData.UpdateSid();
									} else {
										UIData.bOut = true;
										UIData.UpdateSid();
									}
									// Rest
									String strUrl = mRtmpServerIp.get(nSelectServer);
									String[] strTmp = strUrl.split(":");
									String strResult = HttpClient.RtmpCreate(strTmp[0], mEditSerPort.getText().toString(), strStreamRtmpPullId);
									if (strResult != null && !strResult.equals("")) {
										Log.e(TAG, "RtmpCreate resp = " + strResult);
										try {
											JSONObject jsonRoot = new JSONObject(strResult);
											if (jsonRoot.has("resp")) {
												JSONObject jsonChild = jsonRoot.getJSONObject("resp");
												if (jsonChild.has("respCode")) {
													String strCode = jsonChild.getString("respCode");
													if (strCode.equals("000000")) {
														if (jsonChild.has("sessionId")) {
															strPullSessionId = jsonChild.getString("sessionId");
														}
														if (jsonChild.has("routes")) {
															JSONObject strObj = jsonChild.getJSONObject("routes");
															MainApplication.getInstance().strRouteId = strObj.getString("routeid");
															MainApplication.getInstance().strSrcIp = strObj.getString("srcApIp");
															MainApplication.getInstance().strSrcPort = strObj.getString("srcApPort");
															MainApplication.getInstance().strDstIp = strObj.getString("dstApIp");
															MainApplication.getInstance().strDstPort = strObj.getString("dstApPort");
															mHandler.sendEmptyMessage(1001);
															return;
														}
													}
												}
											}
										} catch (JSONException e) {
											e.printStackTrace();
										}
									}
									mHandler.sendEmptyMessage(1000);
								} else {
									mHandler.sendEmptyMessage(1001);
								}
							}
						}).start();
					}
				}
                if (nSelectType == 2 || nSelectType == 3) {
                	// UDP
                	if (mUDPServerList.size() <= 0) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_ip), Toast.LENGTH_LONG).show();
                        return;
                    }
                    if (mEditSerPort.getText().toString().isEmpty()) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_port), Toast.LENGTH_LONG).show();
                        return;
                    }
                    if (mEditSerStream.getText().toString().isEmpty()) {
                        Toast.makeText(MainActivity.this, getString(R.string.str_udp_stream), Toast.LENGTH_LONG).show();
                        return;
                    }
                    
                    if (nSelectType == 2) {
                    	new Thread(new Runnable() {
                            @Override
                            public void run() {
                                //
                                boolean bCan = (nSelectCan != 0);
                                strStreamUdpPushId = mEditSerStream.getText().toString();
                                String strResult = HttpClient.PushRequest(mUDPServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamUdpPushId, bCan);
                                if (strResult != null && !strResult.equals("")) {
                                    Log.e(TAG, "PushRequest resp = " + strResult);
                                    try {
                                        JSONObject jsonRoot = new JSONObject(strResult);
                                        if (jsonRoot.has("apinfo")) {
                                            JSONObject jsonChild = jsonRoot.getJSONObject("apinfo");
                                            if (jsonChild.has("ip")) {
                                                MainApplication.getInstance().strIp = jsonChild.getString("ip");
                                            }
                                            if (jsonChild.has("aport")) {
                                                MainApplication.getInstance().straPort = jsonChild.getString("aport");
                                            }
                                            if (jsonChild.has("vport")) {
                                                MainApplication.getInstance().strvPort = jsonChild.getString("vport");
                                            }
                                            mHandler.sendEmptyMessage(1001);
                                            return;
                                        }
                                    } catch (JSONException e) {
                                        e.printStackTrace();
                                    }
                                }
                                mHandler.sendEmptyMessage(1000);
                            }
                        }).start();
                    }
                    else {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                //
                                boolean bCan = (nSelectCan != 0);
                                strStreamUdpPullId = mEditSerStream.getText().toString();
                                String strResult = HttpClient.PullRequest(mUDPServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamUdpPullId, bCan);
                                if (strResult != null && !strResult.equals("")) {
                                    Log.e(TAG, "PullRequest resp = " + strResult);
                                    try {
                                        JSONObject jsonRoot = new JSONObject(strResult);
                                        if (jsonRoot.has("apinfo")) {
                                            JSONObject jsonChild = jsonRoot.getJSONObject("apinfo");
                                            if (jsonChild.has("ip")) {
                                                MainApplication.getInstance().strIp = jsonChild.getString("ip");
                                            }
                                            if (jsonChild.has("aport")) {
                                                MainApplication.getInstance().straPort = jsonChild.getString("aport");
                                            }
                                            if (jsonChild.has("vport")) {
                                                MainApplication.getInstance().strvPort = jsonChild.getString("vport");
                                            }
                                            mHandler.sendEmptyMessage(1001);
                                            return;
                                        }
                                    } catch (JSONException e) {
                                        e.printStackTrace();
                                    }
                                }
                                mHandler.sendEmptyMessage(1000);
                            }
                        }).start();
                    }
                }
            }
        });
        // 获取服务器地址
        GetServerList();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        MainApplication.getInstance().mMainActivity = null;
    }

    @SuppressLint("HandlerLeak")
    public Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            if (msg.what == 1000) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_fail), Toast.LENGTH_SHORT).show();
            }
            if (msg.what == 1001) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_ok), Toast.LENGTH_SHORT).show();
                // 启动选择Client界面
                if (nSelectType == 0) {
                	Intent mIntent = new Intent(MainActivity.this, RtmpVideoActivity.class);
                    mIntent.putExtra("mode", nSelectType);
                    mIntent.putExtra("stream", strStreamRtmpPushId);
                    if (nSelectCan == 0) {
                    	String strUrl = mRtmpServerIp.get(nSelectServer);
						String[] strTmp = strUrl.split(":");
                    	mIntent.putExtra("dstIp", strTmp[0]);
                        mIntent.putExtra("dstPort", strTmp[1]);
                    } else {
                    	mIntent.putExtra("dstIp", MainApplication.getInstance().strSrcIp);
                        mIntent.putExtra("dstPort", MainApplication.getInstance().strSrcPort);
                    }
                    startActivity(mIntent);
                }
                if (nSelectType == 1) {
                	Intent mIntent = new Intent(MainActivity.this, RtmpPlayActivity.class);
                    mIntent.putExtra("mode", nSelectType);
                    mIntent.putExtra("stream", strStreamRtmpPullId);
                    if (nSelectCan == 0) {
                    	String strUrl = mRtmpServerIp.get(nSelectServer);
						String[] strTmp = strUrl.split(":");
                    	mIntent.putExtra("dstIp", strTmp[0]);
                        mIntent.putExtra("dstPort", strTmp[1]);
                    } else {
                    	mIntent.putExtra("dstIp", MainApplication.getInstance().strSrcIp);
                        mIntent.putExtra("dstPort", MainApplication.getInstance().strSrcPort);
                    }
                    startActivity(mIntent);
                }
                if (nSelectType == 2) {
                	Intent mIntent = new Intent(MainActivity.this, VideoActivity.class);
                    mIntent.putExtra("mode", nSelectType);
                    mIntent.putExtra("stream", strStreamUdpPushId);
                    startActivity(mIntent);
                }
                if (nSelectType == 3) {
                	Intent mIntent = new Intent(MainActivity.this, VideoActivity.class);
                    mIntent.putExtra("mode", nSelectType);
                    mIntent.putExtra("stream", strStreamUdpPullId);
                    startActivity(mIntent);
                }
            }
            if (msg.what == 1002) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_ip), Toast.LENGTH_SHORT).show();
                // 更新服务器列表
                UpdateServer();
            }
            if (msg.what == 1003) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_ip_fail), Toast.LENGTH_SHORT).show();
            }
            if (msg.what == 1004) {
            	if (nSelectType == 0) {
            		if (!strPushSessionId.equals("")) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                String strResult = HttpClient.RtmpRelease(strPushSessionId);
                                if (strResult != null && !strResult.equals("")) {
                                    Log.e(TAG, "RtmpRelease resp = " + strResult);
                                }
                                strPushSessionId = "";
                                mHandler.sendEmptyMessage(1005);
                            }
                        }).start();
                    }
                }
                if (nSelectType == 1) {
                	if (!strPullSessionId.equals("")) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                String strResult = HttpClient.RtmpRelease(strPullSessionId);
                                if (strResult != null && !strResult.equals("")) {
                                    Log.e(TAG, "RtmpRelease resp = " + strResult);
                                }
                                strPullSessionId = "";
                                mHandler.sendEmptyMessage(1005);
                            }
                        }).start();
                    }
                }
                if (nSelectType == 2) {
                	if (!strStreamUdpPushId.equals("")) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                boolean bCan = (nSelectCan != 0);
                                String strResult = HttpClient.PushRelease(mUDPServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamUdpPushId, bCan);
                                if (strResult != null && !strResult.equals("")) {
                                    Log.e(TAG, "PushRelease resp = " + strResult);
                                }
                                mHandler.sendEmptyMessage(1005);
                            }
                        }).start();
                    }
                }
                if (nSelectType == 3) {
                	// 更新流ID
                	mHandler.sendEmptyMessage(1005);
                }
            }
            if (msg.what == 1005) {
            	// 更新流ID
                UpdateStreamCtrl(true);
            }
            if (msg.what == 1006) {
            	// 更新配置
            	GetServerList();
            }
            super.handleMessage(msg);
        }
    };
    
    // 获取服务器地址
    private void GetServerList() {
    	// 启动获取数据
        new Thread(new Runnable() {
            @Override
            public void run() {
            	// 获取IP
            	String strResult = HttpClient.GetLocalIP();
            	if (strResult != null && !strResult.equals("")) {
					Log.e(TAG, "GetLocalIP resp = " + strResult);
					try {
						JSONObject jsonRoot = new JSONObject(strResult);
						if (jsonRoot.has("ipaddr")) {
							UIData.LOCAL_IP = jsonRoot.getString("ipaddr");
						}
					} catch (JSONException e) {
						e.printStackTrace();
					}
            	}
            	
				boolean bSuc = false;
				// 获取RTMP服务器的URL
				strResult = HttpClient.GetRtmpServer();
				if (strResult != null && !strResult.equals("")) {
					Log.e(TAG, "GetRtmpServer resp = " + strResult);
					try {
						JSONObject jsonRoot = new JSONObject(strResult);
						if (jsonRoot.has("result")) {
							String strSuc = jsonRoot.getString("result");
							if (strSuc.equals("200")) {
								// 数据
								if (jsonRoot.has("ss")) {
									mRtmpServerIp.clear();
									mRtmpServerList.clear();
									JSONArray array = jsonRoot.getJSONArray("ss");
									for (int i = 0; i < array.length(); i++) {
										JSONObject obj = (JSONObject) array.get(i);
										if (obj != null) {
											String strIp = obj.getString("ssip");
											String strName = obj.getString("ssname");
											String strText = strIp + " (" + strName + ")";
											mRtmpServerIp.add(strIp);
											mRtmpServerList.add(strText);
										}
									}
									bSuc = true;
								}
							}
						}
					} catch (JSONException e) {
						e.printStackTrace();
					}
				}
				// 获取UDP服务器的URL
				strResult = HttpClient.GetUdpServer();
				if (strResult != null && !strResult.equals("")) {
					Log.e(TAG, "GetUdpServer resp = " + strResult);
					try {
						JSONObject jsonRoot = new JSONObject(strResult);
						if (jsonRoot.has("result")) {
							String strSuc = jsonRoot.getString("result");
							if (strSuc.equals("200")) {
								// 数据
								if (jsonRoot.has("ss")) {
									mUDPServerIp.clear();
									mUDPServerList.clear();
									JSONArray array = jsonRoot.getJSONArray("ss");
									for (int i = 0; i < array.length(); i++) {
										JSONObject obj = (JSONObject) array.get(i);
										if (obj != null) {
											String strIp = obj.getString("ssip");
											String strName = obj.getString("ssname");
											String strText = strIp + " (" + strName + ")";
											mUDPServerIp.add(strIp);
											mUDPServerList.add(strText);
										}
									}
									bSuc = true;
								}
							}
						}
					} catch (JSONException e) {
						e.printStackTrace();
					}
				}
				if (bSuc) {
					mHandler.sendEmptyMessage(1002);
				} else {
					mHandler.sendEmptyMessage(1003);
				}
            }
        }).start();
    }
    
    // 更新服务器列表
    private void UpdateServer() {
		if (nSelectType == 0 || nSelectType == 1) {
			mServerAdapter.clients.clear();
			for (int i = 0; i < mRtmpServerList.size(); i++) {
				ServerClient st = new ServerClient();
				st.setServer(mRtmpServerList.get(i));
				if (nSelectServer == i) {
					st.setIscheck(true);
				} else {
					st.setIscheck(false);
				}
				mServerAdapter.clients.add(st);
			}
		}
		if (nSelectType == 2 || nSelectType == 3) {
			mServerAdapter.clients.clear();
			for (int i = 0; i < mUDPServerList.size(); i++) {
				ServerClient st = new ServerClient();
				st.setServer(mUDPServerList.get(i));
				if (nSelectServer == i) {
					st.setIscheck(true);
				} else {
					st.setIscheck(false);
				}
				mServerAdapter.clients.add(st);
			}
		}
        mServerAdapter.notifyDataSetChanged();
    }
    
    // 更新端口
    private void UpdatePortCtrl() {
		if (nSelectType == 0) {
			mEditSerPort.setText("1935");
			mEditSerPort.setEnabled(false);
		}
		if (nSelectType == 1) {
			mEditSerPort.setText("1935");
			mEditSerPort.setEnabled(false);
		}
		if (nSelectType == 2) {
			mEditSerPort.setText("8095");
			mEditSerPort.setEnabled(false);
		}
		if (nSelectType == 3) {
			mEditSerPort.setText("8095");
			mEditSerPort.setEnabled(false);
		}
    }
    
    // 更新流
    private void UpdateStreamCtrl(boolean bReset) {
    	if (bReset) {
    		String strTime = String.valueOf(System.currentTimeMillis());
			strStreamRtmpPushId = strTime.substring(8);
			strStreamRtmpPullId = "";
			strStreamUdpPushId = strTime.substring(8);
			strStreamUdpPullId = "";
    	}
    	if (nSelectType == 0) {
            mEditSerStream.setText(strStreamRtmpPushId);
            mEditSerStream.setEnabled(false);
		}
		if (nSelectType == 1) {
            mEditSerStream.setText(strStreamRtmpPullId);
            mEditSerStream.setEnabled(true);
		}
		if (nSelectType == 2) {
            mEditSerStream.setText(strStreamUdpPushId);
            mEditSerStream.setEnabled(false);
		}
		if (nSelectType == 3) {
            mEditSerStream.setText(strStreamUdpPullId);
            mEditSerStream.setEnabled(true);
		}
    }
    
    // ListItem数据类
    private class ServerClient {
        // 服务器地址
        private String server = "";
        // Item是否选中
        private boolean ischeck = false;

        // 获取服务器地址
        private String getServer() {
            return server;
        }
        // 设置服务器地址
        private void setServer(String ser) {
            this.server = ser;
        }

        // 获取是否选中
        private boolean getIscheck() {
            return ischeck;
        }
        // 设置是否选中
        private void setIscheck(boolean ischeck) {
            this.ischeck = ischeck;
        }
    }
    // 定义适配器
    private class ServerAdapter extends BaseAdapter {
        // Item 数据结构
        private LayoutInflater mInflater = null;
        private ArrayList<ServerClient> clients = new ArrayList<ServerClient>();
        // Item 控件结构
        private final class ServerHolder {
            private TextView serverName;
            private CheckBox servercb;
        }

        // 默认构造
        private ServerAdapter(Context context) {
            mInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            clients.clear();
        }

        public int getCount() {
            return clients.size();
        }

        public Object getItem(int arg0) {
            return clients.get(arg0);
        }

        public long getItemId(int arg0) {
            return arg0;
        }

        @SuppressLint("InflateParams")
		public View getView(final int position, View convertView, ViewGroup parent) {
            ServerHolder holder;
            // 设置Item布局
            if (null == convertView) {
                holder = new ServerHolder();
                convertView = mInflater.inflate(R.layout.list_server, null);
                holder.servercb = (CheckBox) convertView.findViewById(R.id.list_cb);
                holder.serverName = (TextView) convertView.findViewById(R.id.list_item);
                convertView.setTag(holder);
            } else {
                holder = (ServerHolder)convertView.getTag();
            }

            holder.serverName.setText(clients.get(position).getServer());
            if (clients.size() > position) {
                holder.servercb.setChecked(clients.get(position).getIscheck());
            }

            // 处理点击Item事件
            holder.servercb.setOnClickListener(new View.OnClickListener() {

                @Override
                public void onClick(View v) {
                    for (int i = 0; i < clients.size(); i++) {
                        clients.get(i).setIscheck(false);
                    }
                    if (clients.size() > position) {
                        clients.get(position).setIscheck(((CompoundButton) v).isChecked());
                        nSelectServer = position;
                    }
                    notifyDataSetChanged();
                }
            });
            return convertView;
        }
    }
}