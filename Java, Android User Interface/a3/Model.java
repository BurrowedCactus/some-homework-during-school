
import java.awt.Point;
import java.io.*;
import java.util.*;

public class Model implements Serializable {
	/** The observers that are watching this model for changes. */
	private ArrayList<Observer> observers;
	// private ArrayList<Shape> shapes;
	private MyEllipse[] shapes;
	private boolean clickSelected;
	private int curentSelection;
	private Point start;

	private static int cheat_x = 500;
	private static int cheat_y = 300;
	/**
	 * Create a new model.
	 */
	public Model() {
		this.observers = new ArrayList<Observer>();
		init();
	}

	public void init() {
		clickSelected = false;
		curentSelection = -1;
		shapes = new MyEllipse[14];
		//body 
		shapes[0] = new MyEllipse(cheat_x,cheat_y,100,300,true);
		//left big
		shapes[1] = new MyEllipse(cheat_x-180,cheat_y,200,50,true);
		shapes[2] = new MyEllipse(cheat_x-30,cheat_y+250,50,200,true);
		//left small
		shapes[3] = new MyEllipse(cheat_x-380,cheat_y,200,50,true);
		shapes[4] = new MyEllipse(cheat_x-30,cheat_y+450,50,200,true);
		//hand + foot
		shapes[5] = new MyEllipse(cheat_x-420,cheat_y,40,40,true);
		shapes[6] = new MyEllipse(cheat_x-85,cheat_y+650,100,40,true);
		//right big
		shapes[7] = new MyEllipse(cheat_x+80,cheat_y,200,50,true);
		shapes[8] = new MyEllipse(cheat_x+70,cheat_y+250,50,200,true);
		//right small
		shapes[9] = new MyEllipse(cheat_x+280,cheat_y,200,50,true);
		shapes[10] = new MyEllipse(cheat_x+70,cheat_y+450,50,200,true);
		//hand + foot
		shapes[11] = new MyEllipse(cheat_x+480,cheat_y,40,40,true);
		shapes[12] = new MyEllipse(cheat_x+75,cheat_y+650,100,40,true);
		//head
		shapes[13] = new MyEllipse(cheat_x,cheat_y-100,100,100,true);
		notifyObservers();
	}

	// returns the index of the top shape containing point p in list shapes,
	// returns -1 if no shapes contain the point.
	private int top(Point p) {
		/*
		for (int i = 0; i < 14; ++i) {
			if (shapes[i].contains(p)) {
				return i;
			}
		}
		*/
		if (shapes[0].contains(p)) {
			return 0;
		}
		return -1;
	}

	public void click(Point p) {
		
		int i = top(p);
		if (i == -1) {
			clickSelected = false;
		} else {
			clickSelected = true;
			curentSelection = i;
			start = p;
		}
		notifyObservers();
	}

	public void release(Point p) {
		clickSelected = false;
		notifyObservers();
	}

	public void move(Point p) {
		if (clickSelected) {
			if (curentSelection == 0) {
				for (int i = 0; i < 14; ++i) {
					shapes[i].move(start, p);
					
				}
				start = p;
			}
		}
		notifyObservers();
	}

	/**
	 * Add an observer to be notified when this model changes.
	 */
	public void addObserver(Observer observer) {
		this.observers.add(observer);
	}

	/**
	 * Remove an observer from this model.
	 */
	public void removeObserver(Observer observer) {
		this.observers.remove(observer);
	}

	/**
	 * Notify all observers that the model has changed.
	 */
	public void notifyObservers() {
		for (Observer observer : this.observers) {
			observer.update(this);
		}
	}

	public MyEllipse[] getShapes() {
		return shapes;
	}

	public void setShapes(MyEllipse[] shapes) {
		this.shapes = shapes;
	}

	public int getCurentSelection() {
		return curentSelection;
	};
}
