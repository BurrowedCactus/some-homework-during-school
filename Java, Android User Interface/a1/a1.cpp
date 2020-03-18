// CS 349 Fall 2018
// A1: Breakout code sample
// You may use any or all of this code in your assignment!
// See makefile for compiling instructions

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <utility>
#include <vector>
#include <sstream>
using namespace std;

// X11 structures
Display* display;
Window window;

// fixed frames per second animation
const int HEIGHT_NUM_OF_BLOCKS = 5;
const int LENGTH_NUM_OF_BLOCKS = 15;
double SPEED = 3.0;
int INIT_WINDOW_WIDTH = 1280;
int INIT_WINDOW_HEIGHT = 800;
int FPS = 60;
int MIN_BLOCK_X_INIT = 0;
int MIN_BLOCK_Y_INIT = 100;
int BLOCK_LENGTH = INIT_WINDOW_WIDTH * 7 / 8 /LENGTH_NUM_OF_BLOCKS;
int GAP = INIT_WINDOW_WIDTH /LENGTH_NUM_OF_BLOCKS - BLOCK_LENGTH;
int BLOCK_HEIGHT = INIT_WINDOW_HEIGHT/(7 * HEIGHT_NUM_OF_BLOCKS);
int BALLSIZE = BLOCK_HEIGHT/4;
int PADDLE_HEIGHT = 0.5 * BLOCK_HEIGHT;
int PADDLE_LENGTH = 2.0 * BLOCK_LENGTH;

// get current time
unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

//checks collision
bool checkCollide(int x1, int y1, int x2, int y2) {
	if (y1 - BALLSIZE + + BALLSIZE * 2 < y2){
		return false;
	} else if (y1 - BALLSIZE > y2 + BLOCK_HEIGHT){
		return false;
	} else if (x1 - BALLSIZE + BALLSIZE * 2 < x2){
		return false;
	} else if (x1 - BALLSIZE > BALLSIZE * 2 + BLOCK_LENGTH){
		return false;
	}
	return true;
}

struct Block{
	XPoint rectPos;
	int debug;
	Block(int i, int j, int de){
		rectPos.x = i;
		rectPos.y = j;
		debug = de;
	}
	int x() const {
		return rectPos.x;
	}
	int y() const {
		return rectPos.y;
	}
	void draw(Display* display, Window window, GC gc){
		XFillRectangle(display, window, gc, rectPos.x, rectPos.y, BLOCK_LENGTH, BLOCK_HEIGHT);
	}
	int l() const {
		return rectPos.x;
	}
	int r() const {
		return rectPos.x + BLOCK_LENGTH;
	}
	int u() const {
		return rectPos.y + BLOCK_HEIGHT;
	}
	int d() const {
		return rectPos.y;
	}

};

struct Paddle{
	XPoint rectPos;
	Paddle(){
		rectPos.x = 0;
		rectPos.y = INIT_WINDOW_HEIGHT * 6 / 7;
	}
	int x() const {
		return rectPos.x;
	}
	int y() const {
		return rectPos.y;
	}
	void move_left(XWindowAttributes w){
		rectPos.x -= 10;
		if (rectPos.x < 0){
			rectPos.x = 0;
		}
	}
	void move_right(XWindowAttributes w){
		rectPos.x += 10;
		if (rectPos.x + PADDLE_LENGTH > w.width){
			rectPos.x = INIT_WINDOW_WIDTH - PADDLE_LENGTH;
		}
	}
	
	int l() const {
		return rectPos.x;
	}
	int r() const {
		return rectPos.x + PADDLE_LENGTH;
	}
	int u() const {
		return rectPos.y + PADDLE_HEIGHT;
	}
	int d() const {
		return rectPos.y;
	}

	void draw(Display* display, Window window, GC gc){
		XDrawRectangle(display, window, gc, rectPos.x, rectPos.y, PADDLE_LENGTH, PADDLE_HEIGHT);
	}
};


struct Ball{
	XPoint ballPos;
	XPoint ballDir;
	Ball(){
		ballPos.x = 50;
		ballPos.y = INIT_WINDOW_HEIGHT * 6 / 7 - PADDLE_HEIGHT;
		ballDir.x = 0;
		ballDir.y = SPEED;
	}
	void draw(Display* display, Window window, GC gc){
		XFillArc(display, window, gc, 
				ballPos.x - BALLSIZE/2, ballPos.y - BALLSIZE/2, 
				BALLSIZE, BALLSIZE, 0, 360*64);
	}
	bool touch(const Block& block){
		if (r() < block.l() || block.r() < l() ||
		    u() < block.d() || block.u() < d()){
			return false;
		} else {
			if (abs(r() - block.l()) + abs(ballDir.x) > BLOCK_LENGTH + BALLSIZE ||
			    abs(l() - block.r()) + abs(ballDir.x) > BLOCK_LENGTH + BALLSIZE){
				ballDir.x = -ballDir.x;
			}
			if (abs(u() - block.d()) + abs(ballDir.y) > BLOCK_HEIGHT + BALLSIZE ||
			    abs(d() - block.u()) + abs(ballDir.y) > BLOCK_HEIGHT + BALLSIZE){
				ballDir.y = -ballDir.y;
			}
			return true;
		}
	}
	bool touch(const Paddle& paddle){
		if (r() < paddle.l() || paddle.r() < l() ||
		    u() < paddle.d() || paddle.u() < d()){
			return false;
		} else {
			ballDir.y = -ballDir.y;
			ballDir.x = SPEED * (ballPos.x - (paddle.l() + PADDLE_LENGTH/2)) * 2 / PADDLE_LENGTH;
			return true;
		}
	}
	void move(){
		ballPos.x += ballDir.x;
		ballPos.y += ballDir.y;
	}
	void speed_up(){
		if (SPEED < 10){
			++SPEED;
			ballDir.x *= SPEED/(SPEED - 1);
			ballDir.y *= SPEED/(SPEED - 1);
		}
	}
	void speed_down(){
		if (SPEED > 1){
			--SPEED;
			ballDir.x *= SPEED/(SPEED + 1);
			ballDir.y *= SPEED/(SPEED + 1);;
		}

	}

	int x() const {
		return ballPos.x;
	}
	int y() const {
		return ballPos.y;
	}
	int vx() const {
		return ballDir.x;
	}
	int vy() const {
		return ballDir.y;
	}
	int l() const {
		return ballPos.x - BALLSIZE/2;
	}
	int r() const {
		return ballPos.x + BALLSIZE/2;
	}
	int u() const {
		return ballPos.y + BALLSIZE/2;
	}
	int d() const {
		return ballPos.y - BALLSIZE/2;
	}
	void check_boundary(XWindowAttributes w){
		if (r() > w.width || l() < 0){
			ballDir.x = -ballDir.x;
		}
		if (u() > w.height){
			throw "out of bottom boundary";
		}
		if (d() < 0){
			ballDir.y = -ballDir.y;
		}
	}

};

void error(string s){
	cerr << s << endl;
	exit(1);
}
// entry point
int main( int argc, char *argv[] ) {
	if (argc >= 2){
		int input;
		istringstream iss(argv[1]);
		iss >> input;
		if (input < 10){
			FPS = 10;
		} else if (input > 60){
			FPS = 60;
		} else {
			FPS = input;
		}
	}
	if (argc >= 3){
		int input;
		istringstream iss(argv[2]);
		iss >> input;
		if (input < 1){
			SPEED = 1;
		} else if (input > 10){
			SPEED = 10;
		} else {
			SPEED = input;
		}

	}
	// create window
	display = XOpenDisplay("");
	if (display == NULL) exit (-1);
	int screennum = DefaultScreen(display);
	long background = WhitePixel(display, screennum);
	long foreground = BlackPixel(display, screennum);
	XColor yellow, brown, red, green, blue;
	Colormap colormap = XDefaultColormap(display, screennum);

	if (XAllocNamedColor(display, colormap, "yellow", &yellow, &yellow) == 0) 
		error("ERROR: XAllocNamedColor: failed to allocated yellow");
	if (XAllocNamedColor(display, colormap, "brown", &brown, &brown) == 0) 
		error("ERROR: XAllocNamedColor: failed to allocated brown");
	if (XAllocNamedColor(display, colormap, "red", &red, &red) == 0) 
		error("ERROR: XAllocNamedColor: failed to allocated red");
	if (XAllocNamedColor(display, colormap, "green", &green, &green) == 0) 
		error("ERROR: XAllocNamedColor: failed to allocated green");
	if (XAllocNamedColor(display, colormap, "blue", &blue, &blue) == 0) 
		error("ERROR: XAllocNamedColor: failed to allocated blue");
	window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                            10, 10, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, 2, foreground, background);

	// set events to monitor and display window
	XSelectInput(display, window, ButtonPressMask | KeyPressMask);
	XFlush(display);
	XMapRaised(display, window);

	// create gc for drawing
	GC gc = XCreateGC(display, window, 0, 0);
	GC gcred = XCreateGC(display, window, 0, 0);
	GC gcblue = XCreateGC(display, window, 0, 0);
	GC gcgreen = XCreateGC(display, window, 0, 0);
	GC gcbrown = XCreateGC(display, window, 0, 0);
	GC gcyellow = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gcred , red.pixel);
	XSetForeground(display, gcblue, blue.pixel);
	XSetForeground(display, gcgreen, green.pixel);
	XSetForeground(display, gcbrown, brown.pixel);
	XSetForeground(display, gcyellow, yellow.pixel);

	XWindowAttributes w;
	XGetWindowAttributes(display, window, &w);
	XSizeHints *hints = XAllocSizeHints();
	hints->min_width = INIT_WINDOW_WIDTH;
	hints->min_height = INIT_WINDOW_HEIGHT;
	hints->max_width = INIT_WINDOW_WIDTH;
	hints->max_height = INIT_WINDOW_HEIGHT;
	hints->flags = PMinSize|PMaxSize;
	XSetWMNormalHints(display, window, hints);
	XFree(hints);

	// save time of last window paint
	unsigned long lastRepaint = 0;

	// event handle for current event
	XEvent event;
	int score = 0;
	double coeff = FPS/60.0;

	// intro
	XClearWindow(display, window);
	string line1, line2, line3, line4, line5, line6;
	for (int i = 960; i >= 60; --i){
		if (XPending(display) > 0) { 
			XNextEvent( display, &event );
			switch ( event.type ) {
					case ButtonPress:
					case KeyPress: 
						KeySym key;
						char text[10];
						int j = XLookupString( (XKeyEvent*)&event, text, 10, &key, 0 );	
						// move right
						if ( j == 1 && text[0] == 'e' ) {
							i = 0;
						}
						break;
			}
		}
		if (i == 0){
			break;
		}
		XClearWindow(display, window);
		ostringstream oss;
		oss << i/60;
		line1 = "Press 'e' to skip info and start now.";
		line2 = "Game starts in " + oss.str() + " seconds.";
		line3 = "Name : Yongyuan Bai";
		line4 = "Userid : y47bai";
		line5 = "Press'a' to move the paddle to the left, press 'd' to move to the right.";
		line6 = "Although 3 is the recommended speed, you can press 'w' to increase the ball speed, 's' to decrease the ball speed.";
		const char* line1_c = line1.c_str();
		const char* line2_c = line2.c_str();
		const char* line3_c = line3.c_str();
		const char* line4_c = line4.c_str();
		const char* line5_c = line5.c_str();
		const char* line6_c = line6.c_str();
		XDrawString(display, window, gc, 100, 100, line1_c, line1.length());
		XDrawString(display, window, gc, 100, 200, line2_c, line2.length());
		XDrawString(display, window, gc, 100, 300, line3_c, line3.length());
		XDrawString(display, window, gc, 100, 400, line4_c, line4.length());
		XDrawString(display, window, gc, 100, 500, line5_c, line5.length());
		XDrawString(display, window, gc, 100, 600, line6_c, line6.length());
		XFlush( display );
		usleep(1000000 / 60);
	}

    	//game loop
	while (true){
	
		bool over = false;
		bool win = false;
		bool lose = false;
		bool restart = false;
        	int refresh_count = 0;
		int next_frame = 0;

		Ball ball;
		Paddle paddle;
		std::vector<Block> blocks [HEIGHT_NUM_OF_BLOCKS];
		for (int i = 0; i < HEIGHT_NUM_OF_BLOCKS; ++i){
			int y = MIN_BLOCK_Y_INIT + i * (BLOCK_HEIGHT + GAP);
			for (int j = 0; j < LENGTH_NUM_OF_BLOCKS; ++j){
				int x = MIN_BLOCK_X_INIT + j * (BLOCK_LENGTH + GAP);
				blocks[i].push_back(Block(x, y, i * HEIGHT_NUM_OF_BLOCKS + j));
			}
		}

        // event loop
		while ( !over ) {
			// process if we have any events
			if (XPending(display) > 0) { 
				XNextEvent( display, &event ); 
				switch ( event.type ) {

				// mouse button press
					case ButtonPress:
						//cout << "CLICK" << endl;
						break;

					case KeyPress: // any keypress
						KeySym key;
						char text[10];
						int i = XLookupString( (XKeyEvent*)&event, text, 10, &key, 0 );	

						// move right
						if ( i == 1 && text[0] == 'd' ) {
							paddle.move_right(w);
						}
						// move left
						if ( i == 1 && text[0] == 'a' ) {
							paddle.move_left(w);
						} 
						// speed up
						if ( i == 1 && text[0] == 'w' ) {
							ball.speed_up();
						} 
						// move left
						if ( i == 1 && text[0] == 's' ) {
							ball.speed_down();
						} 

						// quit game
						if ( i == 1 && text[0] == 'q' ) {
							XCloseDisplay(display);
							exit(0);
						}
						break;
				}
			}
			unsigned long end = now();	// get current time in microsecond
			
			//draw
		
			int temp = refresh_count * coeff;
			if (temp == next_frame){
				XClearWindow(display, window);
				ostringstream oss1;
				ostringstream oss2;
				ostringstream oss3;
				oss1 << FPS;
				oss2 << score;
				oss3 << SPEED;
				string FPS_s = "FPS: " + oss1.str();
				string score_s = "score: " + oss2.str();
				string speed_s = "ball speed: " + oss3.str();
				const char * FPS_c = FPS_s.c_str();
				const char * score_c = score_s.c_str();
				const char * speed_c = speed_s.c_str();
				XDrawString(display, window, gc, 10, 10, FPS_c, FPS_s.length());
				XDrawString(display, window, gc, 10, 20, score_c, score_s.length());
				XDrawString(display, window, gc, 10, 30, speed_c, speed_s.length());
				//oss.clear();
				paddle.draw(display, window, gc);
				ball.draw(display, window, gc);
				for (int i = 0; i < HEIGHT_NUM_OF_BLOCKS; ++i){
					for(std::vector<Block>::iterator it = blocks[i].begin(); it != blocks[i].end(); ++it){
						if (i % 5 == 0){
							it->draw(display, window, gcred);
						} else if (i % 5 == 1){
							it->draw(display, window, gcyellow);
						} else if (i % 5 == 2){
							it->draw(display, window, gcgreen);
						} else if (i % 5 == 3){
							it->draw(display, window, gcblue);
						} else {
							it->draw(display, window, gcbrown);
						}

					}
				}
				XFlush( display );
				++next_frame;
				if (next_frame == FPS){
					next_frame = 0;
				}
			}
			++refresh_count;
			if (refresh_count == 60){
				refresh_count = 0;
			}

			// update ball position
			ball.move();
			ball.touch(paddle);
			try {
				ball.check_boundary(w);
			} catch (...){
				lose = true;
				over = true;
			}

			// blocks
			int remain = 0;
			for (int i = 0; i < HEIGHT_NUM_OF_BLOCKS; ++i){
				for(std::vector<Block>::iterator it = blocks[i].begin(); it != blocks[i].end(); ++it){
					++remain;
					if (ball.touch(*it)){
						score += 100;
						blocks[i].erase(it);
						break;
					}
				}
			}
			if (remain == 0){
				win = true;
				over = true;
			}
			
			lastRepaint = now(); // remember when the paint happened
			// IMPORTANT: sleep for a bit to let other processes work
			if (XPending(display) == 0) {
				usleep(1000000 / 60 - (now() - lastRepaint));
			}
		}
		//event loop ends
		XClearWindow(display, window);
		string message;
		ostringstream oss;
		oss << score;
		if (win){
			message = "You win! Your score is: " + oss.str() + ". Press Q to quit or R to restart";
		} else if (lose){
			score = 0;
			message = "You loss. Your score is: " + oss.str() + ". Press Q to quit or R to restart";
		} else {
			message = "Your score is: " + oss.str() + ". Press Q to quit or R to restart";
		}
		const char* message_c = message.c_str();
		XDrawString(display, window, gc, 10, 20, message_c, message.length());
		// game end, recieve player input to continue or end
		while (!restart){
			if (XPending(display) > 0) {
				XNextEvent( display, &event ); 
					switch ( event.type ) {
						case ButtonPress:
							break;
						case KeyPress: // any keypress
							KeySym key;
							char text[10];
							int i = XLookupString( (XKeyEvent*)&event, text, 10, &key, 0 );
							// quit game
							if ( i == 1 && text[0] == 'q' ) {
								XCloseDisplay(display);
								exit(0);
							}
							if ( i == 1 && text[0] == 'r' ) {
								restart = true;
							}
							break;
						}
			} else {
				usleep(1000000 / 60);
			}
		}
	//restart is true, restart the game.
	} 
	//game loop ends
	XCloseDisplay(display);
}
