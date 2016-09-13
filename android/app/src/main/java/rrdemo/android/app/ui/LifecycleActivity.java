package rrdemo.android.app.ui;

import android.os.Bundle;
import android.os.PersistableBundle;
import android.support.v7.app.AppCompatActivity;

import rrdemo.android.app.R;

public class LifecycleActivity extends AppCompatActivity {

   /* ANDROID ===onCreate()==> CREATED
    *                             >=onStart()=> STARTED
    *                         onRestart()          >=onResume()=> RESUMED
    *                             ^             PAUSED <==onPause()=='
    * DESTROYED <=onDestroy()= STOPPED <=onStop()=='
    */

   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.lifecycle_activity);
   }

   @Override
   protected void onStart() {
      super.onStart();
   }

   @Override
   protected void onResume() {
      super.onResume();
   }

   @Override
   protected void onPause() {
      super.onPause();
   }

   @Override
   protected void onStop() {
      super.onStop();
   }

   @Override
   protected void onRestart() {
      super.onRestart();
   }

   @Override
   protected void onDestroy() {
      super.onDestroy();
   }

   /* ... RESUMED =onSaveInstanceState()=onPause()=> PAUSED ...
    * ANDROID =onCreate()=onRestoreInstanceState()=> CREATED ...
    */

   @Override
   public void onSaveInstanceState(Bundle outState, PersistableBundle outPersistentState) {
      super.onSaveInstanceState(outState, outPersistentState);
   }

   @Override
   protected void onRestoreInstanceState(Bundle savedInstanceState) {
      super.onRestoreInstanceState(savedInstanceState);
   }
}
