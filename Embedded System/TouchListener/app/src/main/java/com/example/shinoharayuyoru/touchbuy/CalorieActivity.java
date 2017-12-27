package com.example.shinoharayuyoru.touchbuy;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.graphics.Color;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLES10;

import android.opengl.GLSurfaceView;
import android.opengl.GLU;

import org.w3c.dom.Text;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;


/**
 * Created by ShinoharaYuyoru on 2016/12/01.
 */
public class CalorieActivity extends AppCompatActivity
{
    public RadioGroup WalkorRun;
    public EditText Time;
    public TextView Burn;
    public Button Button_CalorieC;
    public Button Button_ReturnH;
    public RadioButton Default;
    int temp=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_calorie);

        WalkorRun=(RadioGroup)this.findViewById(R.id.RadioGWalkorRun);
        WalkorRun.check(R.id.radioButtonWalking);
        temp = 255;

        Default = (RadioButton) WalkorRun.findViewById(WalkorRun.getCheckedRadioButtonId());

        Time=(EditText)this.findViewById(R.id.EditTextSportTime);
        Burn=(TextView)this.findViewById(R.id.TextViewResult);
        Button_CalorieC = (Button)findViewById(R.id.ButtonCaculate);
        Button_ReturnH = (Button)findViewById(R.id.ButtonReturn);


        WalkorRun.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if(Default.getId()==checkedId)
                {
                    temp=255;
                }
                else
                {
                    temp=655;
                }
            }
        });

        Button_CalorieC.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View Cal)
            {
                int burnedNum = 0;
                int sportTime = Integer.parseInt(Time.getText().toString().trim());
                burnedNum = temp*sportTime;
                String S = String.valueOf(burnedNum);
                CalorieActivity.this.Burn.setText("You have burned "+S+" calurie.");
            }
        });

        Button_ReturnH.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(getApplicationContext(),HomePageActivity.class);
                startActivity(intent);
            }
        });
    }
}