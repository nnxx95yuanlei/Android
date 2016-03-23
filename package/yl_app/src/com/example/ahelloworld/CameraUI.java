package com.example.ahelloworld;

import android.app.Activity;
import android.graphics.RectF;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;

public class CameraUI implements SurfaceHolder.Callback {
	static final String TAG = "yuanleiUI";
	static private SurfaceView surfaceView;
	static private SurfaceHolder surfaceHolder;
	static private MainActivity mActivity;
	static private View rootView;
	public CameraUI(MainActivity activity,View parent){
		mActivity = activity;
		rootView = parent;
		surfaceView = (SurfaceView) rootView.findViewById(R.id.surface_preview);
		surfaceHolder = surfaceView.getHolder();
		surfaceHolder.addCallback(this);
		surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

		Log.v(TAG, "yuanlei cameraUI");
//		surfaceHolder.addOnLayoutChangeListener(mLayoutListener);
	}

	
    public SurfaceHolder getSurfaceHolder() {
        return surfaceHolder;
    }
    
    public SurfaceView getSurfaceView() {
    	return surfaceView;
    }
    // SurfaceHolder callbacks
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.v(TAG, " yuanlei surfaceChanged22222222222222: width =" + width + ", height = " + height);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.v(TAG, "yuanlei surfaceCreated22222222222");
        surfaceHolder = holder;
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.v(TAG, "yuanlei surfaceDestroyed222222222222");
        surfaceHolder = null;
    }
	
	
	
}
