package com.example.shinoharayuyoru.touchbuy;

/**
 * Created by ShinoharaYuyoru on 2016/11/28.
 */

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class ConfigActivity extends AppCompatActivity
{
    public EditText textV_Port;
    public Button Button_Start;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_config);

        textV_Port = (EditText)findViewById(R.id.editPort);
        Button_Start=(Button)findViewById(R.id.buttonStart);

        Button_Start.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                int portNum = Integer.parseInt(textV_Port.getText().toString().trim());
                Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                intent.putExtra("portNum",portNum);
                startActivity(intent);
            }
        });
    }
}
