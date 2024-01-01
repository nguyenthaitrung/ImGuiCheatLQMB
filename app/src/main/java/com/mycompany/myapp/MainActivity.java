package com.mycompany.myapp;
 
import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Button;
import android.view.View.OnClickListener;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.app.Dialog;
import android.widget.FrameLayout;
import android.view.Gravity;

public class MainActivity extends Activity {
	/*
    static {
		System.loadLibrary("VM");
	}
	*/
    
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
    
        
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        
        Toast.makeText(getApplication(), event.getUnicodeChar() + "", Toast.LENGTH_SHORT).show();
        
        return super.dispatchKeyEvent(event);
    }
    
    
    
    
    }
