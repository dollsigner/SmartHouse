package com.example.SmartHousefinal;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	public WebView cameraView;
	
	public TextView textTemperature;
	public TextView textHumidity;
	public TextView textFire;
	
	final private int TEMP = 0;
	final private int HUMI = 1;
	final private int FIRE = 2;
	final private int LIVING = 3;
	final private int RESTAU = 4;
	final private int UPSTAIRS = 5;
	final private int BATH = 6;

	
	public Button buttonLivingroom;
	public Button buttonRestaurant;
	public Button buttonUpstairs;
	public Button buttonBathroom;
	
	public Handler textHandler;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		cameraView = (WebView) findViewById(R.id.webView1);
		cameraView.loadUrl("http://192.168.31.20:8080/stream.html");
		cameraView.setWebViewClient(new WebViewClient());
		
		textTemperature = (TextView) findViewById(R.id.textTemperature);
		textHumidity = (TextView) findViewById(R.id.textHumidity);
		textFire = (TextView) findViewById(R.id.textFire);
		
		buttonLivingroom = (Button) findViewById(R.id.buttonLivingroom);
		buttonRestaurant = (Button) findViewById(R.id.buttonRestaurant);
		buttonUpstairs = (Button) findViewById(R.id.buttonUpstairs);
		buttonBathroom = (Button) findViewById(R.id.buttonBathroom);
		
		textHandler = new Handler(){
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				switch(msg.what)
				{
					case TEMP:
						textTemperature.setText(msg.obj.toString());
						break;
					case HUMI:
						textHumidity.setText(msg.obj.toString());
						break;
					case FIRE:
						textFire.setText(msg.obj.toString());
						break;
				}
			}
		};
		
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					Socket client = new Socket("192.168.31.20",8088);
					OutputStream out = client.getOutputStream();
					String outMsg = "textClient";
					out.write(outMsg.getBytes());
					InputStream in = client.getInputStream();
					while(true)
					{
						int len;
						String res;
						byte[] data = new byte[128];
						len = in.read(data);
						res = new String(data,0,len);
						String[] resSplit = res.split(" ",2);
					
						
						Message msg = new Message();
						if(resSplit[0].equals("temperature"))
						{
							msg.what = TEMP;
							String str1 = "ÎÂ¶È: ";
							String str2 = "¡ãc";
							msg.obj = str1 + resSplit[1] + str2;
						}else if(resSplit[0].equals("humidity"))
						{
							msg.what = HUMI;
							String str1 = "Êª¶È: ";
							String str2 = "%";
							msg.obj = str1 + resSplit[1] + str2;
						}else if(resSplit[0].equals("fire"))
						{
							//OFF ÎÞ»ð¾¯
							//ON ÓÐ»ð¾¯
							msg.what = FIRE;
							if(resSplit[1].equals("ON"))
							{
								msg.obj = "»ð¾¯: ·¢ÏÖ»ðÇé£¡£¡£¡";
							}else
							{
								msg.obj = "»ð¾¯: »ðÔÖ¼à²âÖÐ£¡£¡£¡";
							}
						}
						
						textHandler.sendMessage(msg);
					}
			
				} catch (IOException e) {
					// TODO: handle exception
					e.printStackTrace();
				}
			}
		}).start();
	}
	
	public void clickDemo(View v) {
		Message msg = new Message();
		msg.what = 0;
		msg.obj = "ÎÂ¶È: 20¡ãc";
		textHandler.sendMessage(msg);
	}
	
	public void buttonClientHandler(String device){
		final String command = device;
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					Socket client = new Socket("192.168.31.20",8088);
					OutputStream out = client.getOutputStream();
					out.write(command.getBytes());
					
				} catch (IOException e) {
					// TODO: handle exception
					e.printStackTrace();
				}
		
			}
		}
		).start();
	}
	
	
	public void buttonClick(View v)
	{
		switch(v.getId())
		{
			case R.id.buttonLivingroom:
				buttonClientHandler("livingroomLight");
				break;
			case R.id.buttonRestaurant:
				buttonClientHandler("restaurantLight");
				break;
			case R.id.buttonUpstairs:
				buttonClientHandler("upstairsLight");
				break;
			case R.id.buttonBathroom:
				buttonClientHandler("bathroomLight");
				break;
		}
	}
	
	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
