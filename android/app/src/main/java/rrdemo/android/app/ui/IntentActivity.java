package rrdemo.android.app.ui;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

import rrdemo.android.app.R;

public class IntentActivity extends AppCompatActivity {

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.intent_activity);
   }

   public void callActivityWithExtraData(View view) {
      EditText editData = (EditText) findViewById(R.id.intent_edit_data);
      IntentWithActivityActivity.startActivity(this, editData.getText().toString());
   }
}
