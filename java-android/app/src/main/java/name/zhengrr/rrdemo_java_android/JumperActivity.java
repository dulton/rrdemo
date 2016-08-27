package name.zhengrr.rrdemo_java_android;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class JumperActivity extends AppCompatActivity {

   /**
    * @param ctx Context.
    */
   public static void activityStart(Context ctx) {
      Intent intent = new Intent(ctx, JumperActivity.class);
      ctx.startActivity(intent);
   }

   EditText et = null;

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_jumper);

      Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
      setSupportActionBar(toolbar);

      FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
      fab.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(View view) {
            Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                  .setAction("Action", null).show();
         }
      });

      et = (EditText) findViewById(R.id.jumper_et);

      Button btnJumpToJumpedActivity
            = (Button) findViewById(R.id.jumper_btn_jump_to_jumped_activity);
      btnJumpToJumpedActivity.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(View v) {
            JumpedActivity.activityStart(JumperActivity.this, et.getText().toString());
         }
      });
   }

}