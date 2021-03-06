package prohor33.ndk.asteroids;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;

public class DemoActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceView(this);
        setContentView(mGLView);
        System.out.println("DemoActivity::onCreate()");
    }

    @Override
    protected void onPause() {
    	System.out.println("DemoActivity::onPause()");
        super.onPause();
        mGLView.onPause();
    }
    
    @Override
    public void onBackPressed() {
    	System.out.println("DemoActivity::onBackPressed()");
    	nativeDone();
    	onPause();
    	finish();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("sanangeles");
    }
    
    private static native void nativeDone();
}

class DemoGLSurfaceView extends GLSurfaceView {
    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer();
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) {
        switch (event.getAction()) {
        case MotionEvent.ACTION_DOWN:
        	nativeTouch(event.getX(), event.getY());
        	break;        
        case MotionEvent.ACTION_MOVE:
        	nativeMove(event.getX(), event.getY());
        	break;
        case MotionEvent.ACTION_UP:
        	nativeUp(event.getX(), event.getY());
        	break;        	
        }
        return true;
    }

   @Override
    public void onPause() {
        super.onPause();
        nativePause();
    }

   @Override
    public void onResume() {
        super.onResume();
        nativeResume();
    }


    DemoRenderer mRenderer;

    private static native void nativePause();
    private static native void nativeResume();
    private static native void nativeTogglePauseResume();
    private static native void nativeTouch(float x, float y);
    private static native void nativeMove(float x, float y);
    private static native void nativeUp(float x, float y);    
}

class DemoRenderer implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //gl.glViewport(0, 0, w, h);
        nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private static native void nativeInit();
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();   
}
