package com.kct.flyudp;

import java.util.ArrayList;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
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
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class EditActivity extends Activity {
	// TAG
	public static final String TAG = "KC";
	// 控件
	public RelativeLayout mBack = null;
	public TextView mDone = null;
	public EditText mRestApi = null;
	public EditText mCpsApi = null;
	// 码率列表
	public ListView mListSerIP = null;
    public ServerAdapter mServerAdapter = null;
    // 码率选择
    public int nSelectServer = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_edit);
        // 按钮
        mBack = (RelativeLayout)findViewById(R.id.rl_back);
        mDone = (TextView)findViewById(R.id.rl_set);
        // 服务器地址栏
        mRestApi = (EditText)findViewById(R.id.edit_rest_api);
        mCpsApi = (EditText)findViewById(R.id.edit_cps_api);
        mRestApi.setText(UIData.REST_API_BASE);
        mCpsApi.setText(UIData.CPS_URL_BASE);
        // 码率设置
        mListSerIP = (ListView) findViewById(R.id.listCode);
        mServerAdapter = new ServerAdapter(this);
        mListSerIP.setAdapter(mServerAdapter);
        // 返回按键
        mBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
        // 设置按键
        mDone.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 设置
            	String strRest = mRestApi.getText().toString();
            	String strCps = mCpsApi.getText().toString();
            	if (strRest.equals("") || strCps.equals("")) {
            		Toast.makeText(EditActivity.this, getString(R.string.app_edit_server), Toast.LENGTH_LONG).show();
                    return;
            	}
            	// 保存变量
            	UIData.REST_API_BASE = strRest;
            	UIData.CPS_URL_BASE = strCps;
            	UIData.nCodec = nSelectServer;
            	UIData.UpdateUrl();
            	
            	Log.e(TAG, "Done resp RTMP_GET_URL = " + UIData.RTMP_GET_URL);
            	Log.e(TAG, "Done resp UDP_GET_URL = " + UIData.UDP_GET_URL);
            	Log.e(TAG, "Done resp REST_API = " + UIData.REST_API);
            	//
            	if (MainApplication.getInstance().mMainActivity != null) {
        			MainApplication.getInstance().mMainActivity.mHandler.sendEmptyMessage(1006);
        		}
            	//
                finish();
            }
        });
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

    // ListItem数据类
    private class ServerClient {
        // 码率
        private String server = "";
        // Item是否选中
        private boolean ischeck = false;

        // 获取码率
        private String getServer() {
            return server;
        }
        // 设置码率
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
            
            ServerClient mServerClient1 = new ServerClient();
            mServerClient1.setServer("200kbps");
            mServerClient1.setIscheck((UIData.nCodec == 0));
            clients.add(mServerClient1);
            
            ServerClient mServerClient2 = new ServerClient();
            mServerClient2.setServer("300kbps");
            mServerClient2.setIscheck((UIData.nCodec == 1));
            clients.add(mServerClient2);
            
            ServerClient mServerClient3 = new ServerClient();
            mServerClient3.setServer("400kbps");
            mServerClient3.setIscheck((UIData.nCodec == 2));
            clients.add(mServerClient3);
            
            ServerClient mServerClient4 = new ServerClient();
            mServerClient4.setServer("500kbps");
            mServerClient4.setIscheck((UIData.nCodec == 3));
            clients.add(mServerClient4);
            
            ServerClient mServerClient5 = new ServerClient();
            mServerClient5.setServer("600kbps");
            mServerClient5.setIscheck((UIData.nCodec == 4));
            clients.add(mServerClient5);
            
            ServerClient mServerClient6 = new ServerClient();
            mServerClient6.setServer("700kbps");
            mServerClient6.setIscheck((UIData.nCodec == 5));
            clients.add(mServerClient6);
            
            ServerClient mServerClient7 = new ServerClient();
            mServerClient7.setServer("800kbps");
            mServerClient7.setIscheck((UIData.nCodec == 6));
            clients.add(mServerClient7);
            
            ServerClient mServerClient8 = new ServerClient();
            mServerClient8.setServer("1000kbps");
            mServerClient8.setIscheck((UIData.nCodec == 7));
            clients.add(mServerClient8);
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
