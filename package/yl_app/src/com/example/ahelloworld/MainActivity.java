package com.example.ahelloworld;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Button;
import android.widget.FrameLayout;
import android.hardware.Camera;
import android.hardware.Camera.AutoFocusCallback;
import android.hardware.Camera.PictureCallback;

public class MainActivity extends Activity implements View.OnClickListener,
													  View.OnTouchListener,
													  Camera.PictureCallback,
													  Camera.AutoFocusCallback{
	static final String TAG = "yuanlei";
	Camera mCamera;
	CameraUI mUI;
	CameraHandler mHandler ;
	static boolean mIsPreview = false;
	static final int MSG_OPEN_CAMERA = 1;
	static final int MSG_START_PREVIEW = 2;
	static final int MSG_STOP_PREVIEW = 3;
	static final int MSG_TAKE_PICTURE = 4;
	static final int MSG_AUTO_FOCUS = 5;
	private static final String WeakReference = null;
	Object mLock = new Object();
	public class CameraHandler extends Handler {

		CameraHandler(Looper loop){
			super(loop);
		}
		
		@Override
		public void handleMessage(Message msg){
			switch (msg.what){
			case MSG_OPEN_CAMERA:
				mCamera = Camera.open((int)msg.arg1);
				break;
			case MSG_START_PREVIEW:
				try {
					mCamera.setPreviewDisplay(mUI.getSurfaceHolder());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				mCamera.startPreview();
				break;
			case MSG_STOP_PREVIEW:
				mCamera.stopPreview();
				break;
			case MSG_TAKE_PICTURE:
				mCamera.takePicture(null, null, (PictureCallback)msg.obj);
				break;
			case MSG_AUTO_FOCUS:
				mCamera.autoFocus((AutoFocusCallback)msg.obj);
				break;
			}
		}
	}
	
	class BatteryReceiver extends BroadcastReceiver{  
		  
        @Override  
        public void onReceive(Context context, Intent intent) {  
            // TODO Auto-generated method stub  
            //判断它是否是为电量变化的Broadcast Action  
            if(Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())){  
                //获取当前电量  
                int level = intent.getIntExtra("level", 0);  
                //电量的总刻度  
                int scale = intent.getIntExtra("scale", 100);  
				//把它转成百分比  
                synchronized(mLock){
                	((TextView)(findViewById(R.id.txt1))).setText("电池电量为"+((level*100)/scale)+"%");  
                }
            }  
        }  
          
    }  
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		HandlerThread ht = new HandlerThread("Camera Hanlder Thread");
		ht.start();
		mHandler = new CameraHandler(ht.getLooper());
		findViewById(R.id.button_send).setOnClickListener(this);
		findViewById(R.id.button_preview).setOnClickListener(this);
		findViewById(R.id.button_take_picture).setOnClickListener(this);
        mUI = new CameraUI(this, (FrameLayout)findViewById(R.id.preview_container));  
		mUI.getSurfaceView().setOnTouchListener(this);
		mHandler.obtainMessage(MSG_OPEN_CAMERA, 1, 0).sendToTarget();
		
        IntentFilter intentFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);  
        BatteryReceiver batteryReceiver = new BatteryReceiver();  
        registerReceiver(batteryReceiver, intentFilter);  
	}
		
/////////////////////implement interface	
	@Override
	public void onClick(View v){
		switch(v.getId()){
		case R.id.button_send:
			java.lang.ref.WeakReference<MainActivity> ref = new java.lang.ref.WeakReference<MainActivity>(this);
			if(ref.get() != null)
				((TextView)(ref.get().findViewById(R.id.txt1))).setText(stringFromJNI());;
				
				BatteryManager bs = (BatteryManager)this.getSystemService(Context.BATTERY_SERVICE);
				Intent i = new Intent();
				Toast.makeText(getApplicationContext(), "yuanlei", Toast.LENGTH_LONG).show();
			break;
		case R.id.button_preview:
			if(mIsPreview) {
				mHandler.sendEmptyMessage(MSG_STOP_PREVIEW);
				((Button)findViewById(R.id.button_preview)).setText(R.string.start_preview);
				mIsPreview = false;
			} else {
				mHandler.obtainMessage(MSG_START_PREVIEW).sendToTarget();
				((Button)findViewById(R.id.button_preview)).setText(R.string.stop_preview);
				mIsPreview = true;
			}
			break;
		case R.id.button_take_picture:
			mHandler.obtainMessage(MSG_TAKE_PICTURE, 0, 0,this).sendToTarget();
			break;
		}
	}
	
	@Override
	public boolean onTouch(View v, MotionEvent event){
		mHandler.obtainMessage(MSG_AUTO_FOCUS, this).sendToTarget();
		return true;
	}
	
	@Override
	public void onAutoFocus(boolean success, Camera camera) {
		
	}
	
	@Override
	public void onPictureTaken(byte[] data, Camera camera) {
		// 获取Jpeg图片，并保存在sd卡上
		File pictureFile = new File("/sdcard/" + System.currentTimeMillis()
				+ ".jpg");
		try {
			FileOutputStream fos = new FileOutputStream(pictureFile);
			fos.write(data);
			fos.close();
			
		} catch (Exception e) {
			Log.v(TAG, "yuanlei keep picture fail");
		}
	}
//////////////////////
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		return super.onOptionsItemSelected(item);
	}
	
	public void preview() {
		
	}
	
    public native String  stringFromJNI();
//    public native String  getNumberOfYl();
	static{
		System.loadLibrary("helloWorld");
	}
}
