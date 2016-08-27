package name.zhengrr.rrdemo_java_android;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_main);

      Button btnJumpToLifecycleActivity
            = (Button) findViewById(R.id.main_btn_jump_to_lifecycle_activity);
      btnJumpToLifecycleActivity.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(View v) {
            LifecycleActivity.activityStart(MainActivity.this);
         }
      });

      Button btnJumpToJumperActivity
            = (Button) findViewById(R.id.main_btn_jump_to_jumper_activity);
      btnJumpToJumperActivity.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(View v) {
            JumperActivity.activityStart(MainActivity.this);
         }
      });
   }

}
