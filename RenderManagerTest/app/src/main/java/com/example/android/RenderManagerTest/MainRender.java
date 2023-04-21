package com.example.android.RenderManagerTest;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainRender extends GLSurfaceView implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("RenderManagerTest");
    }

    public MainRender(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        setRenderer(this);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Render();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Render();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        Render();
    }

    public native void Render();
}