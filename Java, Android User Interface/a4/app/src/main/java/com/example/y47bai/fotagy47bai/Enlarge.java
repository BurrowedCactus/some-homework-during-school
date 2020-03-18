package com.example.y47bai.fotagy47bai;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.content.SharedPreferences;
import android.media.Image;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.TextView;

import java.io.InputStream;

public class Enlarge extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.enlarge);
        //setContentView(R.layout.disable_android_orientation_change);
        // Get the intent that started this activity
        // extract the intent value in int
        SetUp();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                SharedPreferences sp = getSharedPreferences("temp",MODE_PRIVATE);
                SharedPreferences.Editor spe = sp.edit();
                int which = getIntent().getIntExtra("which",0);
                spe.putFloat("my_ratings" + which,((RatingBar) findViewById(R.id.ratingBar10)).getRating());
                spe.apply();
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private class DownloadImageTask extends AsyncTask<String, Void, Bitmap> {
        ImageView bmImage;

        public DownloadImageTask(ImageView bmImage) {
            this.bmImage = bmImage;
        }

        protected Bitmap doInBackground(String... urls) {
            String urldisplay = urls[0];
            Bitmap mIcon11 = null;
            try {
                InputStream in = new java.net.URL(urldisplay).openStream();
                mIcon11 = BitmapFactory.decodeStream(in);
            } catch (Exception e) {
                Log.e("Error", e.getMessage());
                e.printStackTrace();
            }
            return mIcon11;
        }

        protected void onPostExecute(Bitmap result) {
            bmImage.setImageBitmap(result);
        }
    }

    void SetUp(){
        ImageView image = (ImageView) findViewById(R.id.imageView10);
        int which = getIntent().getIntExtra("which", 0);
        String url = main.URLList[which];
        new DownloadImageTask(image).execute(url);
        RatingBar ratingBar = findViewById(R.id.ratingBar10);
        ratingBar.setRating(getIntent().getFloatExtra("rate", 0));
    }

    protected void onSaveInstanceState(Bundle outState){
        outState.putFloat("rate", ((RatingBar) findViewById(R.id.ratingBar10)).getRating());
        super.onSaveInstanceState(outState);
    }
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);
        ImageView image = (ImageView) findViewById(R.id.imageView10);
        String url = main.URLList[getIntent().getIntExtra("which", 0)];
        new DownloadImageTask(image).execute(url);
        RatingBar rating = findViewById(R.id.ratingBar10);
        rating.setRating(savedInstanceState.getFloat("rate"));
    }
}
