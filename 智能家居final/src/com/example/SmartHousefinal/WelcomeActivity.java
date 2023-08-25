package com.example.SmartHousefinal;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class WelcomeActivity extends Activity {

	public TextView textView;
	
	public Handler h;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_welcome);
		
		textView = (TextView)findViewById(R.id.textView);
		h = new Handler(){
			public void handleMessage(Message msg)
			{
				super.handleMessage(msg);
				textView.setText(msg.what + "s");
			}
		};
		
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				for(int i = 5; i > 0; i--)
				{
					Message msg = new Message();
					msg.what = i;
					h.sendMessage(msg);
					
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				
				Intent intent = new Intent(WelcomeActivity.this,MainActivity.class);
				startActivity(intent);
			}
		}).start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.welcome, menu);
		return true;
	}

}
