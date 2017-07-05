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
    // 控件
    public ListView mListSerIP = null;
    public ServerAdapter mServerAdapter = null;
    public EditText mEditSerPort = null;
    public EditText mEditSerStream = null;
    public RadioGroup mRadioGroup = null;
    public TextView mTextView = null;
    // CAN选择
    public int nSelectCan = 0;
    public int nSelectServer = 0;
    // Push Pull 选择
    public int nSelectType = 0;
    public CheckBox pushSelect = null;
    public CheckBox pullSelect = null;
    // 流ID
    public String strStreamId = "";

    // 服务器数据
    public ArrayList<String> mServerIp = new ArrayList<String>();
    public ArrayList<String> mServerList = new ArrayList<String>();

    @Override
    protected void onResume() {
        super.onResume();
        if (nSelectType == 0) {
            // 生成5位流ID
            String strTime = String.valueOf(System.currentTimeMillis());
            mEditSerStream.setText(strTime.substring(8));
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 全屏显示
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        MainApplication.getInstance().mMainActivity = this;
        // 推拉流选择
        nSelectType = 0;
        pushSelect = (CheckBox)findViewById(R.id.push_select);
        pullSelect = (CheckBox)findViewById(R.id.pull_select);
        pushSelect.setChecked(true);
        pullSelect.setChecked(false);
        // 服务器地址
        mListSerIP = (ListView) findViewById(R.id.listServer);
        mServerAdapter = new ServerAdapter(this);
        mListSerIP.setAdapter(mServerAdapter);
        // 服务器端口和流ID
        mEditSerPort = (EditText) findViewById(R.id.udp_push_port);
        mEditSerStream = (EditText) findViewById(R.id.udp_push_stream);
        // 生成5位流ID
        String strTime = String.valueOf(System.currentTimeMillis());
        mEditSerStream.setText(strTime.substring(8));

        // 推拉流切换
        pushSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 0) {
                    return;
                }
                // 切换类型
                nSelectType = 0;
                // 生成新的ID
                String strTime = String.valueOf(System.currentTimeMillis());
                mEditSerStream.setText(strTime.substring(8));
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_push));
                pushSelect.setChecked(true);
                pullSelect.setChecked(false);
            }
        });
        pullSelect.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (nSelectType == 1) {
                    return;
                }
                // 切换类型
                nSelectType = 1;
                // 清空ID
                mEditSerStream.setText("");
                // 更新各种按键显示
                mTextView.setText(getString(R.string.app_udp_pull));
                pushSelect.setChecked(false);
                pullSelect.setChecked(true);
                // 关闭流
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        boolean bCan = (nSelectCan != 0);
                        String strResult = HttpClient.PushRelease(mServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamId, bCan);
                        if (strResult != null && !strResult.equals("")) {
                            Log.d("udpPush", "PushRelease resp = " + strResult);
                        }
                    }
                }).start();
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
                if (mServerList.size() <= 0) {
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
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            //
                            boolean bCan = (nSelectCan != 0);
                            strStreamId = mEditSerStream.getText().toString();
                            String strResult = HttpClient.PushRequest(mServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamId, bCan);
                            if (strResult != null && !strResult.equals("")) {
                                Log.d("udpPush", "PushRequest resp = " + strResult);
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
                            strStreamId = mEditSerStream.getText().toString();
                            String strResult = HttpClient.PullRequest(mServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamId, bCan);
                            if (strResult != null && !strResult.equals("")) {
                                Log.d("udpPush", "PullRequest resp = " + strResult);
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
        });

        // 启动获取数据
        new Thread(new Runnable() {
            @Override
            public void run() {
                String strResult = HttpClient.GetPushServer();
                if (strResult != null && !strResult.equals("")) {
                    Log.d("udpPush", "GetPushServer resp = " + strResult);
                    try {
                        JSONObject jsonRoot = new JSONObject(strResult);
                        if (jsonRoot.has("result")) {
                            String strSuc = jsonRoot.getString("result");
                            if (strSuc.equals("200")) {
                                // 数据
                                if (jsonRoot.has("ss")) {
                                    JSONArray array = jsonRoot.getJSONArray("ss");
                                    for (int i = 0;i < array.length();i++) {
                                        JSONObject obj = (JSONObject) array.get(i);
                                        if (obj != null) {
                                            String strIp = obj.getString("ssip");
                                            String strName = obj.getString("ssname");
                                            String strText = strIp + " (" + strName + ")";
                                            mServerIp.add(strIp);
                                            mServerList.add(strText);
                                        }
                                    }
                                    mHandler.sendEmptyMessage(1002);
                                    return;
                                }
                            }
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                mHandler.sendEmptyMessage(1003);
            }
        }).start();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (!strStreamId.equals("")) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    boolean bCan = (nSelectCan != 0);
                    String strResult = HttpClient.PushRelease(mServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamId, bCan);
                    if (strResult != null && !strResult.equals("")) {
                        Log.d("udpPush", "PushRelease resp = " + strResult);
                    }
                }
            }).start();
        }
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
                Intent mIntent = new Intent(MainActivity.this, VideoActivity.class);
                mIntent.putExtra("mode", nSelectType);
                mIntent.putExtra("stream", strStreamId);
                startActivity(mIntent);
            }
            if (msg.what == 1002) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_ip), Toast.LENGTH_SHORT).show();
                // 更新列表
                for (int i = 0;i < mServerList.size();i++) {
                    ServerClient st = new ServerClient();
                    st.setServer(mServerList.get(i));
                    if (nSelectServer == i) {
                        st.setIscheck(true);
                    }
                    else {
                        st.setIscheck(false);
                    }
                    mServerAdapter.clients.add(st);
                }
                mServerAdapter.notifyDataSetChanged();
            }
            if (msg.what == 1003) {
                Toast.makeText(MainActivity.this, getString(R.string.resp_udp_ip_fail), Toast.LENGTH_SHORT).show();
            }
            if (msg.what == 1004) {
            	if (!strStreamId.equals("")) {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            boolean bCan = (nSelectCan != 0);
                            String strResult = HttpClient.PushRelease(mServerIp.get(nSelectServer), mEditSerPort.getText().toString(), strStreamId, bCan);
                            if (strResult != null && !strResult.equals("")) {
                                Log.d("udpPush", "PushRelease resp = " + strResult);
                            }
                        }
                    }).start();
                }
            }
            super.handleMessage(msg);
        }
    };

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
