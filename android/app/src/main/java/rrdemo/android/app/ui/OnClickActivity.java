package rrdemo.android.app.ui;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import rrdemo.android.app.R;

public class OnClickActivity extends AppCompatActivity {

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.onclick_activity);
   }

   /* public void *ON_CLICK_METHOD_NAME*(View view) { ... } */
   public void onClickByAttribute(View view) {
   }

}
