package rrdemo.android.app.ui;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import rrdemo.android.app.R;

public class IntentWithActivityActivity extends AppCompatActivity {

   public final static String EXTRA_DATA = "rrdemo.android.IntentWithActivity.DATA";

   public static void startActivity(Context context, String data) {
      Intent intent = new Intent(context, IntentWithActivityActivity.class);
      intent.putExtra(EXTRA_DATA, data);
      context.startActivity(intent);
   }

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.intentwithactivity_activity);

      TextView dataView = (TextView) findViewById(R.id.intentwithactivity_dataview);
      Intent intent = getIntent();
      dataView.setText(intent.getStringExtra(EXTRA_DATA));
   }
}
