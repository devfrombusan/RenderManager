package com.example.android.RenderManagerTest;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;



/*
* 샘플 코드는 cpp/SampleScene/SampleScene.cpp 에 구현되어 있습니다.
* */

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("RenderManagerTest");
    }

    MainRender GLES;
    Thread UpdateThread;
    Thread RenderThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Init();

        CopyBinary(this, R.raw.white_box, "whiteBox.bdt");

        GLES = new MainRender(this);

        RenderThread = new Thread() {
            @Override
            public void run() {
                super.run();
                while (!Thread.currentThread().isInterrupted()) {
                    try {
                        Render();
                        sleep(10);
                    } catch (InterruptedException e) {
                        currentThread().interrupt();
                        break;
                    }
                }
            }
        };


        UpdateThread = new Thread() {
            @Override
            public void run() {
                super.run();
                while (!Thread.currentThread().isInterrupted()) {
                    try {
                        Update();
                        sleep(1);
                    } catch (InterruptedException e) {
                        currentThread().interrupt();
                        break;
                    }
                }
                finishAffinity();
            }
        };

        RenderThread.start();
        UpdateThread.start();

        setContentView(GLES);
    }

    @Override
    protected void onDestroy() {
        System.runFinalization();
        System.exit(0);
        super.onDestroy();
    }

    public void CopyBinary(Context context, int resID, String Filename) {
        try {
            isExist(this, resID, Filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void isExist(Context context, int resID, String Filename) throws IOException {
        File TargetFile = new File(Filename);
        if (!TargetFile.exists()) {
            Copy(context, resID, Filename);
        }
    }

    public void Copy(Context context, int resID, String Filename) throws IOException {

        String StoragePath = context.getFilesDir().getAbsolutePath() + "/" + Filename;

        FileOutputStream Output = context.openFileOutput(Filename, Context.MODE_PRIVATE);
        InputStream Stream = getResources().openRawResource(resID);
        int Readbyte;

        byte[] buffer = new byte[1024];

        while ((Readbyte = Stream.read(buffer)) != -1) {
            Output.write(buffer, 0, Readbyte);
        }

        Output.flush();
        Output.close();
        Stream.close();
    }

    public native void Init();
    public native void Render();
    public native void Update();
}