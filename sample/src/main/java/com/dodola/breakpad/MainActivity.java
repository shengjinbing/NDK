package com.dodola.breakpad;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Toast;

import com.sample.breakpad.BreakpadInit;

import java.io.File;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;


public class MainActivity extends Activity {
    private static final int WRITE_EXTERNAL_STORAGE_REQUEST_CODE = 100;

    static {
        System.loadLibrary("crash-lib");
    }


    private File externalReportPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                    this,
                    new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                    WRITE_EXTERNAL_STORAGE_REQUEST_CODE);
        } else {
            initExternalReportPath();
        }

        findViewById(R.id.crash_btn)
                .setOnClickListener(
                        new View.OnClickListener() {
                            @Override
                            public void onClick(View view) {
                                initBreakPad();
                                crash();
                                // copy core dump to sdcard
                            }
                        });

        findViewById(R.id.dynamic_btn)
                .setOnClickListener(
                        new View.OnClickListener() {
                            @Override
                            public void onClick(View view) {
                                /*Toast.makeText(getApplicationContext(),
                                        dynamicJavaFunc(77)+""
                                ,Toast.LENGTH_LONG).show();*/
                            }
                        });
    }

    /**
     * 一般来说，crash捕获初始化都会放到Application中，这里主要是为了大家有机会可以把崩溃文件输出到sdcard中
     * 做进一步的分析
     */
    private void initBreakPad() {
        if (externalReportPath == null) {
            externalReportPath = new File(getFilesDir(), "crashDump");
            if (!externalReportPath.exists()) {
                externalReportPath.mkdirs();
            }
        }
        BreakpadInit.initBreakpad(externalReportPath.getAbsolutePath());
    }

    @Override
    public void onRequestPermissionsResult(
            int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        initExternalReportPath();
    }

    private void initExternalReportPath() {
        externalReportPath = new File(Environment.getExternalStorageDirectory(), "crashDump");
        if (!externalReportPath.exists()) {
            externalReportPath.mkdirs();
        }
    }



    /*********************************************************************************/


    /**
     *  1、JNI 与 NDK 区别
     *  JNI：JNI是一套编程接口，用来实现Java代码与本地的C/C++代码进行交互；
     *  NDK: NDK是Google开发的一套开发和编译工具集，可以生成动态链接库，主要用于Android的JNI开发
     *
     */

    //静态注册
    public native void crash();

    //public native int dynamicJavaFunc(int i);
}
