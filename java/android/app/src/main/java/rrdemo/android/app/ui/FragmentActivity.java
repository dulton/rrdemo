package rrdemo.android.app.ui;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import rrdemo.android.app.R;


public class FragmentActivity extends AppCompatActivity {

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.fragment_activity);
   }
}
