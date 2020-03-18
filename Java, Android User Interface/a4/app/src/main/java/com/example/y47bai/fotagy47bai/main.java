package com.example.y47bai.fotagy47bai;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.RatingBar;
import java.io.InputStream;



public class main extends AppCompatActivity {
       static String[] URLList = {
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/bunny.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/chinchilla.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/doggo.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/hamster.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/husky.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/kitten.png",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/loris.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/puppy.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/redpanda.jpg",
            "https://www.student.cs.uwaterloo.ca/~cs349/f18/assignments/images/sleepy.png",};


    @Override
    protected void onResume() {
        super.onResume();
        SharedPreferences sp = getSharedPreferences("temp",MODE_PRIVATE);
        SharedPreferences.Editor spe = sp.edit();
        if (sp.contains("my_ratings"+2)) {
            ImageView pic[] = new ImageView[10];
            pic[0] = (ImageView) findViewById(R.id.imageView);
            pic[1] = (ImageView) findViewById(R.id.imageView2);
            pic[2] = (ImageView) findViewById(R.id.imageView3);
            pic[3] = (ImageView) findViewById(R.id.imageView4);
            pic[4] = (ImageView) findViewById(R.id.imageView5);
            pic[5] = (ImageView) findViewById(R.id.imageView6);
            pic[6] = (ImageView) findViewById(R.id.imageView7);
            pic[7] = (ImageView) findViewById(R.id.imageView8);
            pic[8] = (ImageView) findViewById(R.id.imageView9);
            pic[9] = (ImageView) findViewById(R.id.imageViewA);
            for (int i = 0; i < 10; ++i) {
                new DownloadImageTask(pic[i]).execute(URLList[i]);
                pic[i].setVisibility(sp.getInt("my_pic_visibility" + i, View.GONE));
            }
            RatingBar rating[] = new RatingBar[11];
            rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
            rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
            rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
            rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
            rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
            rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
            rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
            rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
            rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
            rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
            //the filter
            rating[10] = (RatingBar) findViewById(R.id.ratingBar);
            for (int i = 0; i < 11; ++i) {
                rating[i].setRating(sp.getFloat("my_ratings" + i, 0));
                rating[i].setVisibility(sp.getInt("my_rating_visibility" + i, View.GONE));
            }
            rating[10].setVisibility(sp.getInt("my_rating_visibility" + 10, View.VISIBLE));
            spe.clear();
            spe.apply();
            buttonFilter();
        }


    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
        /*
        SharedPreferences sp = getSharedPreferences("temp",MODE_PRIVATE);
        SharedPreferences.Editor spe = sp.edit();
        spe.clear();
        spe.apply();
        */
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RatingBar ratingBar = (RatingBar) findViewById(R.id.ratingBar);
        ratingBar.setOnRatingBarChangeListener(new RatingBar.OnRatingBarChangeListener() {
            public void onRatingChanged(RatingBar ratingBar, float rating,
                                        boolean fromUser) {

                buttonFilter();
            }
        });

        ratingBarAddListener();
    }

    private void ratingBarAddListener(){
        RatingBar rating[] = new RatingBar[10];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        for(int i = 0; i < 10; ++i){
            final int x = i;
            rating[x].setOnRatingBarChangeListener(new RatingBar.OnRatingBarChangeListener() {
                public void onRatingChanged(RatingBar ratingBar, float rating,
                                            boolean fromUser) {

                    buttonRate(x);
                }
            });
        }
    }
    @Override
    protected void onSaveInstanceState(Bundle outState){
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        for(int i = 0; i < 10; ++i){
            outState.putInt("my_pic_visibility"+i,pic[i].getVisibility());
        }
        RatingBar rating[] = new RatingBar[11];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        //the filter
        rating[10] = (RatingBar) findViewById(R.id.ratingBar);
        for(int i = 0; i < 11; ++i){
            outState.putFloat("my_ratings"+i,rating[i].getRating());
            outState.putInt("my_rating_visibility"+i,rating[i].getVisibility());
        }
        super.onSaveInstanceState(outState);
    }
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        for(int i = 0; i < 10; ++i){
            new DownloadImageTask(pic[i]).execute(URLList[i]);
            pic[i].setVisibility(savedInstanceState.getInt("my_pic_visibility"+i));
        }
        RatingBar rating[] = new RatingBar[11];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        //the filter
        rating[10] = (RatingBar) findViewById(R.id.ratingBar);
        for(int i = 0; i < 11; ++i){
            rating[i].setRating(savedInstanceState.getFloat("my_ratings"+i));
            rating[i].setVisibility(savedInstanceState.getInt("my_rating_visibility"+i));
        }

    }


    //from https://stackoverflow.com/questions/5776851/load-image-from-url
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
    public void buttonLoad(View v){
        buttonClear(v);
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        for(int i = 0; i < 10; ++i){
            new DownloadImageTask(pic[i]).execute(URLList[i]);
        }

        RatingBar rating[] = new RatingBar[10];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        for(int i = 0; i < 10; ++i){
            pic[i].setVisibility(View.VISIBLE);
            rating[i].setVisibility(View.VISIBLE);
        }
    }
    public void buttonClear(View v){
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        RatingBar rating[] = new RatingBar[10];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        for(int i = 0; i < 10; ++i){
            pic[i].setImageResource(android.R.color.transparent);
            rating[i].setRating(0);
        }
        ((RatingBar) findViewById(R.id.ratingBar)).setRating(0);

        for(int i = 0; i < 10; ++i){
            pic[i].setVisibility(View.GONE);
            rating[i].setVisibility(View.GONE);
        }
    }

    private void buttonFilter(){

        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        RatingBar rating[] = new RatingBar[10];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        RatingBar boss = (RatingBar) findViewById(R.id.ratingBar);
        for(int i = 0; i < 10; ++i){
            if (rating[i].getRating() != boss.getRating()){
                pic[i].setVisibility(View.GONE);
                rating[i].setVisibility(View.GONE);
            } else {
                pic[i].setVisibility(View.VISIBLE);
                rating[i].setVisibility(View.VISIBLE);
            }
        }
    }

    private void buttonRate(int which){
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);
        RatingBar rating[] = new RatingBar[10];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        RatingBar boss = (RatingBar) findViewById(R.id.ratingBar);
/*
        Drawable oldDraw = pic[which].getDrawable();
        float oldRate = rating[which].getRating();
        for (int i = which + 1; i < 10; ++i){
            if (rating[i].getRating() == oldRate) {
                pic[which].setImageDrawable(pic[i].getDrawable());
                rating[which].setRating(rating[i].getRating());
                which = i;
            }
        }
        pic[which].setImageDrawable(oldDraw);
        pic[which].setVisibility(View.GONE);
        rating[which].setRating(oldRate);
        rating[which].setVisibility(View.GONE);
*/
        buttonFilter();
    }

    public void enlarge(View v){
        ImageView pic[] = new ImageView[10];
        pic[0] = (ImageView) findViewById(R.id.imageView);
        pic[1] = (ImageView) findViewById(R.id.imageView2);
        pic[2] = (ImageView) findViewById(R.id.imageView3);
        pic[3] = (ImageView) findViewById(R.id.imageView4);
        pic[4] = (ImageView) findViewById(R.id.imageView5);
        pic[5] = (ImageView) findViewById(R.id.imageView6);
        pic[6] = (ImageView) findViewById(R.id.imageView7);
        pic[7] = (ImageView) findViewById(R.id.imageView8);
        pic[8] = (ImageView) findViewById(R.id.imageView9);
        pic[9] = (ImageView) findViewById(R.id.imageViewA);

        RatingBar rating[] = new RatingBar[11];
        rating[0] = (RatingBar) findViewById(R.id.ratingBar2);
        rating[1] = (RatingBar) findViewById(R.id.ratingBar3);
        rating[2] = (RatingBar) findViewById(R.id.ratingBar4);
        rating[3] = (RatingBar) findViewById(R.id.ratingBar5);
        rating[4] = (RatingBar) findViewById(R.id.ratingBar6);
        rating[5] = (RatingBar) findViewById(R.id.ratingBar7);
        rating[6] = (RatingBar) findViewById(R.id.ratingBar8);
        rating[7] = (RatingBar) findViewById(R.id.ratingBar9);
        rating[8] = (RatingBar) findViewById(R.id.ratingBarA);
        rating[9] = (RatingBar) findViewById(R.id.ratingBarB);
        rating[10] = (RatingBar) findViewById(R.id.ratingBar);

        int which = -1;
        float rate = -1;

        for(int i = 0; i < 10; ++i){
            if (v.getId() == pic[i].getId()) {
                which = i;
                rate = rating[i].getRating();
                break;
            }
        }



        if (which >= 0 && rate >= 0) {
            SharedPreferences sp = getSharedPreferences("temp",MODE_PRIVATE);
            SharedPreferences.Editor spe = sp.edit();
            Intent intent = new Intent(this, Enlarge.class);
            for(int i = 0; i < 10; ++i){
                spe.putInt("my_pic_visibility"+i,pic[i].getVisibility());
                intent.putExtra("my_pic_visibility"+i,pic[i].getVisibility());
            }
            for(int i = 0; i < 11; ++i){
                spe.putFloat("my_ratings"+i,rating[i].getRating());
                spe.putInt("my_rating_visibility"+i,rating[i].getVisibility());
                intent.putExtra("my_ratings"+i,rating[i].getRating());
                intent.putExtra("my_rating_visibility"+i,rating[i].getVisibility());
            }
            intent.putExtra("which", which);
            intent.putExtra("rate", rate);
            spe.apply();
            startActivity(intent);
        }

    }
}
