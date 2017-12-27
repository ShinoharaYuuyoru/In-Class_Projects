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

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLES10;

import android.opengl.GLSurfaceView;
import android.opengl.GLU;

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
public class HomePageActivity extends AppCompatActivity
{
    public Button Button_PortL;
    public Button Button_Producer;
    public Button Button_Calorie;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.home_page);

        Button_PortL=(Button)findViewById(R.id.ButtonPortL);

        Button_PortL.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View PortV)
            {
                Intent intentPortV = new Intent(getApplicationContext(),ConfigActivity.class);
                startActivity(intentPortV);
            }
        });

        Button_Calorie=(Button)findViewById(R.id.ButtonCalorieC);

        Button_Calorie.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View CalorieV)
            {
                Intent intentCalorieV = new Intent(getApplicationContext(),CalorieActivity.class);
                startActivity(intentCalorieV);
            }
        });

        Button_Producer=(Button)findViewById(R.id.ButtonProducer);

        Button_Producer.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View ProducerV)
            {
                Intent intentProducerV = new Intent(getApplicationContext(),ProducerActivity.class);
                startActivity(intentProducerV);
            }
        });
    }
}
