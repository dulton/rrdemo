package name.zhengrr.rrdemo_java_android;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;

/**
 * Lifecycle Activity.
 */
public class LifecycleActivity extends AppCompatActivity {

   /**
    * The log tag in the class.
    */
   private static final String TAG = "LifecycleActivity";

   /**
    * @param ctx Context.
    */
   public static void activityStart(final Context ctx) {
      Intent intent = new Intent(ctx, LifecycleActivity.class);
      ctx.startActivity(intent);
   }

   @Override
   protected final void onCreate(final Bundle savedInstanceState) {
      Log.d(TAG, "onCreate()");
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_lifecycle);

      Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
      setSupportActionBar(toolbar);

      FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
      fab.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(final View view) {
            Snackbar.make(view, "Replace with your own action",
                  Snackbar.LENGTH_LONG).setAction("Action", null).show();
         }
      });
   }

   @Override
   protected final void onRestart() {
      Log.d(TAG, "onRestart()");
      super.onRestart();
   }

   @Override
   protected final void onStart() {
      Log.d(TAG, "onStart()");
      super.onStart();
   }

   @Override
   protected final void onResume() {
      Log.d(TAG, "onResume()");
      super.onResume();
   }

   @Override
   protected final void onPause() {
      Log.d(TAG, "onPause()");
      super.onPause();
   }

   @Override
   protected final void onStop() {
      Log.d(TAG, "onStop()");
      super.onStop();
   }

   @Override
   public final void onSaveInstanceState(
         final Bundle outState, final PersistableBundle outPersistentState) {
      Log.d(TAG, "onSaveInstanceState()");
      super.onSaveInstanceState(outState, outPersistentState);
   }

   @Override
   protected final void onDestroy() {
      Log.d(TAG, "onDestroy()");
      super.onDestroy();
   }

}
