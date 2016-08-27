package name.zhengrr.rrdemo_java_android;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.TextView;

public class JumpedActivity extends AppCompatActivity {

   /**
    * @param ctx Context.
    * @param txt Text.
    */
   public static void activityStart(Context ctx, String txt) {
      Intent intent = new Intent(ctx, JumpedActivity.class);
      intent.putExtra("extra_txt", txt);
      ctx.startActivity(intent);
   }

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_jumped);

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

      Intent intent = getIntent();
      TextView tv = (TextView) findViewById(R.id.jumped_tv);
      tv.setText(intent.getStringExtra("extra_txt"));
   }

}
