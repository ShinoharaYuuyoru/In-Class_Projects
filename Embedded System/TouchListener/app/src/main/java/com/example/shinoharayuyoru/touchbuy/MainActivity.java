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

public class MainActivity extends AppCompatActivity {

    public TextView textV_IP,textV_Port,textV_State;
    public Button button_Clear,button_Stop;
//    private LinearLayout list_Message;
//    private ScrollView scrollView;
    private TextView text_Message;
    private GLSurfaceView mView;

    public String IP = null;
    public int Port = 0;

    private ServerSocket mServerSocket;
    private Socket socket;
    private final float pi = (float)Math.acos(0.0)*2;
//    private double alpha[] = {pi/3,pi/3,pi/3};

    float[] a_x = {0f,0f,0f,2f,0f,0f};
    float[] a_y = {0f,0f,0f,0f,2f,0f};
    float[] a_z = {0f,0f,0f,0f,0f,2f};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textV_State = (TextView)findViewById(R.id.textState);
        textV_Port = (TextView)findViewById(R.id.textPort);
        button_Clear = (Button)findViewById(R.id.buttonClear);
        button_Stop = (Button)findViewById(R.id.buttonStop);

//        scrollView = (ScrollView)findViewById(R.id.scrollView);
//        list_Message = (LinearLayout)findViewById(R.id.linearList);
        text_Message = (TextView)findViewById(R.id.textMessage);

        //mView用于显示3D图像，当需要显示时同时去掉此部分注释和MyRenderer类的注释,同时去掉activity_main.xml文件中的一段GLSurfaceView的注释
       /* mView=(GLSurfaceView)findViewById(R.id.glview_1);
        mView.setRenderer(new MyRenderer());
        mView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);*/

        Intent intent = getIntent();
        Bundle bd = intent.getExtras();

        //  mView = new GLSurfaceView(this);

        Port = bd.getInt("portNum");

        textV_State.setText("listening...");
//        textV_IP.setText(IP);
        textV_Port.setText(String.valueOf(Port));

        button_Clear.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                text_Message.setText("");
            }
        });

        button_Stop.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                stop();
            }
        });

        tcpserver_start();
    }

    Thread tcpserver = null;
    FileOutputStream fout = null;
    public void tcpserver_start()
    {
        tcpserver=new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    Log.i("Shinohara","port:" + Port);
                    mServerSocket = new ServerSocket(Port);
                    socket = mServerSocket.accept();
                    String str_ip;
                    str_ip=socket.getInetAddress().toString();
                    Date dt= new Date();
                    String str_dt= new SimpleDateFormat("-MM-dd-HH-mm-ss-SSS").format(dt);
                    String rootdir=(Environment.getExternalStorageDirectory()).getAbsolutePath();
                    File file = new File(rootdir+"/detection");
                    if (!file.exists()) {//若文件夹不存在，则创建一个文件夹
                        try {
                            file.mkdir();
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                    fout=new FileOutputStream(rootdir+"/detection/"+str_ip+str_dt+".txt");//创建打开日志文件
                    Message msg1=new Message();
                    msg1.what=2;
                    msg1.obj=str_ip;
                    mHandler.sendMessage(msg1);
                    InputStream inputStream = socket.getInputStream();
                    byte buffer[] = new byte[1024 * 4];
                    int temp=0;
                    while ((temp = inputStream.read(buffer)) != -1) {//接收数据
                        String textmsg=new String(buffer, 1, temp-2);
                        Date dt1= new Date();
                        String str_dt1= new SimpleDateFormat("\tMM-dd-HH-mm-ss-SSS").format(dt1);

                        fout.write(buffer,1,temp-3);//写入日志
                        fout.write(str_dt1.getBytes(),0,str_dt1.length());
                        fout.flush();
                        Message msg=new Message();//将接收到的数据发送到主线程，在Handler mHandler = new Handler()的case 1中进行处理
                        msg.what=1;
                        msg.obj=textmsg;
                        mHandler.sendMessage(msg);
                    }
                    mServerSocket.close();
                    mHandler.obtainMessage(3).sendToTarget();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
            };
        });
        tcpserver.start();
    }

    public void stop()
    {
        try {
            socket.close();
            // tcpserver.();
            fout.close();
            mHandler.obtainMessage(3).sendToTarget();
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.finish();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {
            stop();
            return false;
        }
        return super.onKeyDown(keyCode, event);
    }

    int count=0;
    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case 1:
                    String data=msg.obj.toString().trim();//主线程获得socket线程的数据

                    text_Message.setText(data);//界面中显示接收到的数据

                    /*
                    int tab_index=data.indexOf('\t');//字符串处理，将数据分为若干段，获得值
                    String str_x=data.substring(0,tab_index).trim();
                    data=data.substring(tab_index+1);
                    tab_index=data.indexOf('\t');
                    String str_y=data.substring(0,tab_index).trim();
                    data=data.substring(tab_index+1);
                    String str_z=data.trim();
                    String str_msg="x:"+str_x+" y:"+str_y+" z:"+str_z;
                    Log.d("zxq",str_msg);

                    double Vx=Double.parseDouble(str_x);//将数值字符串转换为实数，电压值
                    double Vy=Double.parseDouble(str_y);
                    double Vz=Double.parseDouble(str_z);
                    Vx=(Vx-0.73)/0.28;//计算三个方向的加速度值
                    Vy=(Vy-0.77)/0.28;
                    Vz=(Vz-0.788)/0.28;


                    Vx=Vx<1?Vx:0.9999999;//加速度阈值处理
                    Vx=Vx>-1?Vx:-0.9999999;

                    Vy=Vy<1?Vy:0.9999999;
                    Vy=Vy>-1?Vy:-0.9999999;

                    Vz=Vz<1?Vz:0.9999999;
                    Vz=Vz>-1?Vz:-0.9999999;
                    alpha[0]=Math.acos(Vx);//计算角度
                    alpha[1]=Math.acos(Vy);
                    alpha[2]=Math.acos(Vz);

                    double temp_cos2,temp_cos1,temp_sin1;//临时变量，用于计算向量
                    temp_cos2=Math.cos(alpha[1]);
                    temp_cos1=Math.cos(alpha[0]);
                    temp_sin1=Math.sin(alpha[0]);

                    a_x[3]=0f;//计算芯片的x方向在世界坐标系中的坐标
                    a_x[4]=(float)temp_sin1;
                    a_x[5]=(float)temp_cos1;

                    double temp_a_yx;//计算芯片的y方向在世界坐标系中的坐标
                    a_y[5]=(float)temp_cos2;
                    a_y[4]=(float)(-temp_cos2*temp_cos1/temp_sin1);
                    temp_a_yx=1-temp_cos2*temp_cos2-a_y[4]*a_y[4];
                    temp_a_yx=temp_a_yx>0?temp_a_yx:0;
                    a_y[3]=(float)Math.sqrt(temp_a_yx);

                    Log.i("zxq","alpha x:"+alpha[0]*180/pi+"\nalpha y:"+alpha[1]*180/pi+"\n" +
                            "alpha z:"+alpha[2]*180/pi+"\n"+"1:x=("+a_x[3]+","+a_x[4]+","+a_x[5]+") y=("+a_y[3]+","+a_y[4]+","+a_y[5]+")\n");

                    double temp_len=a_y[3]*a_y[3]+a_y[4]*a_y[4]+a_y[5]*a_y[5];
                    temp_len=Math.sqrt(temp_len);

                    a_y[3]=(float)(a_y[3]/temp_len);//y坐标向量单位化
                    a_y[4]=(float)(a_y[4]/temp_len);
                    a_y[5]=(float)(a_y[5]/temp_len);

                    Log.i("zxq","2:x=("+a_x[3]+","+a_x[4]+","+a_x[5]+") y=("+a_y[3]+","+a_y[4]+","+a_y[5]+")\n");

                    str_msg+="\nalpha x:"+alpha[0]*180/pi+"\nalpha y:"+alpha[1]*180/pi+"\n" +
                            "alpha z:"+alpha[2]*180/pi+"\n";
                    textmsg.setText(str_msg);
                    Log.d("zxq",str_msg);

                   */
                    break;
                case 2:
                    textV_IP.setText(msg.obj.toString());
                    textV_State.setText("conected");
                    break;
                case 3:
                    textV_State.setText("disconected");
                    textV_State.setTextColor(Color.RED);
                    break;

                default:
                    break;
            }
        }
    };

    //以下部分为用于滚动屏幕
   /* public void showmsg(String msg) {
        textmsg.setText(textmsg.getText() + msg + "\n");
        scrollToBottom();
    }


    Handler scrollHandler;

    public void scrollToBottom() {

        scrollHandler = new Handler();

        scrollHandler.post(new Runnable() {
            public void run() {

                if (scrollview == null || list_msg == null) {
                    Log.i("scrollToBottom", "scroll or inner is null");
                    return;
                }

                int offset = list_msg.getMeasuredHeight()
                        - scrollview.getHeight();
                if (offset < 0) {
                    offset = 0;
                }

                scrollview.scrollTo(0, offset);
            }
        });
    }*/


    //以下部分为OpenGL，显示3D图像

    /*class MyRenderer implements GLSurfaceView.Renderer
    {

        public void onSurfaceCreated(GL10 gl, EGLConfig config)
        {
            // Set the background frame color
            //GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            //GLES20.glVertexAttribPointer();
            gl.glClearColor(0, 0, 0, 1);
            //启用顶点缓冲区
            gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
          //  GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
          //  GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        }

        public void onDrawFrame(GL10 gl)
        {

            gl.glClear(GL10.GL_COLOR_BUFFER_BIT);//清除颜色缓冲区

            //模型视图矩阵
            gl.glMatrixMode(gl.GL_MODELVIEW);
            gl.glLoadIdentity();

            GLU.gluLookAt(gl, 5,5, 5, 0, 0, 0, 0,0,1);

            *//**
     * 画三角形
     * 绘制数组
     * 三角形坐标
     *//*
            float[] coords = {
                    1f,0f,1f,
                    -1f,0f,1f,
                    1f,0f,-1f,
                    -1f,0f,-1f,
            };
            float[] axio_x={0f,0f,0f,2f,0f,0f};
            float[] axio_y={0f,0f,0f,0f,2f,0f};
            float[] axio_z={0f,0f,0f,0f,0f,2f};








            //分配字节缓冲区控件,存放顶点坐标数据

            float chip[]=new float[12];

            chip[0]=a_x[3]+a_y[3];
            chip[1]=a_x[4]+a_y[4];
            chip[2]=a_x[5]+a_y[5];

            chip[3]=a_x[3]-a_y[3];
            chip[4]=a_x[4]-a_y[4];
            chip[5]=a_x[5]-a_y[5];

            chip[6]=a_y[3]-a_x[3];
            chip[7]=a_y[4]-a_x[4];
            chip[8]=a_y[5]-a_x[5];

            chip[9]=-chip[0];
            chip[10]=-chip[1];
            chip[11]=-chip[2];


           *//* ByteBuffer ibb = ByteBuffer.allocateDirect(coords.length * 4);
            ibb.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbb = ibb.asFloatBuffer();//放置顶点坐标数组
            fbb.put(coords);
            ibb.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(0.5f, 0.5f, 0.5f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibb);
            gl.glDrawArrays(GL10.GL_TRIANGLE_STRIP, 0, 4);//绘制四边形*//*

            ByteBuffer ibb = ByteBuffer.allocateDirect(chip.length * 4);
            ibb.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbb = ibb.asFloatBuffer();//放置顶点坐标数组
            fbb.put(chip);
            ibb.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(0.5f, 0.5f, 0.5f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibb);
            gl.glDrawArrays(GL10.GL_TRIANGLE_STRIP, 0, 4);//绘制四边形

            //分配字节缓冲区控件,存放顶点坐标数据
            ByteBuffer ibbx = ByteBuffer.allocateDirect(axio_x.length * 4);
            ibbx.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbbx = ibbx.asFloatBuffer();//放置顶点坐标数组
            fbbx.put(axio_x);
            ibbx.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(1f, 0.5f, 0.5f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibbx);
            gl.glDrawArrays(GL10.GL_LINES, 0, 2);//绘制x轴

            //分配字节缓冲区控件,存放顶点坐标数据
            ByteBuffer ibby = ByteBuffer.allocateDirect(axio_y.length * 4);
            ibby.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbby = ibby.asFloatBuffer();//放置顶点坐标数组
            fbby.put(axio_y);
            ibby.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(0.5f,1f,  0.5f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibby);
            gl.glDrawArrays(GL10.GL_LINES, 0, 2);//绘制y轴


            //分配字节缓冲区控件,存放顶点坐标数据
            ByteBuffer ibbz = ByteBuffer.allocateDirect(axio_z.length * 4);
            ibbz.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbbz = ibbz.asFloatBuffer();//放置顶点坐标数组
            fbbz.put(axio_z);
            ibbz.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f( 0.5f, 0.5f,1f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibbz);
            gl.glDrawArrays(GL10.GL_LINES, 0, 2);//绘制x轴


            //分配字节缓冲区控件,存放顶点坐标数据
            ByteBuffer ibbx1 = ByteBuffer.allocateDirect(a_x.length * 4);
            ibbx1.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbbx1 = ibbx1.asFloatBuffer();//放置顶点坐标数组
            fbbx1.put(a_x);
            ibbx1.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(1f, 0.6f, 0.6f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibbx1);
            gl.glDrawArrays(GL10.GL_LINES, 0, 2);//绘制x轴

            //分配字节缓冲区控件,存放顶点坐标数据
            ByteBuffer ibby1 = ByteBuffer.allocateDirect(a_y.length * 4);
            ibby1.order(ByteOrder.nativeOrder());//设置顺序(本地顺序)
            FloatBuffer fbby1 = ibby1.asFloatBuffer();//放置顶点坐标数组
            fbby1.put(a_y);
            ibby1.position(0);//定位指针的位置,从该位置开始读取顶点数据
            gl.glColor4f(0.6f,1f,  0.6f, 1f);//设置绘图时的颜色
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, ibby1);
            gl.glDrawArrays(GL10.GL_LINES, 0, 2);//绘制y轴



        }

        public void onSurfaceChanged(GL10 gl, int width, int height)
        {
            gl.glViewport(0, 0, width, height);


            //矩阵模式,投影矩阵,openGL基于状态机
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //加载单位矩阵
            gl.glLoadIdentity();
            //平截头体(最后一个f表示他是浮点数的类型)
           // gl.glFrustumf(-0.5f, 0.5f, -0.5f, 0.5f, 2f, 10);
            gl.glOrthof(-2f, 2f, -2f, 2f, 2f, 10);

        }
    }*/
}
