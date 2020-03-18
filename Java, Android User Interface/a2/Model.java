
import java.awt.Color;
import java.awt.Point;
import java.io.*;
import java.util.*;

public class Model implements Serializable {
	private static final long serialVersionUID = 1L;
	public static final int UNDEF = -1;
	public static final int SELECT = 0;
	public static final int ERASE = 1;
	public static final int LINE = 2;
	public static final int CIRCLE = 3;
	public static final int SQUARE = 4;
	public static final int PAINT = 5;
	public static Color COLOR_1 = Color.BLACK;
	public static Color COLOR_2 = Color.WHITE;
	public static Color COLOR_3 = Color.BLUE;
	public static Color COLOR_4 = Color.GREEN;
	public static Color COLOR_5 = Color.YELLOW;
	public static Color COLOR_6 = Color.RED;
	public static final Color COLOR_X = new Color(255, 255, 255, 255);
	public static final double S = 1;
	public static final double M = 2;
	public static final double L = 3;
	public static final double XL = 4;

	/** The observers that are watching this model for changes. */
	private ArrayList<Observer> observers;
	private ArrayList<Shape> shapes;
	private int toolChosen;
	private Color colorChosen;
	private double thicknessChosen;
	private boolean firstPointDrawn;
	private boolean clickSelected;
	private int curentSelection;
	private Point drag;

	/**
	 * Create a new model.
	 */
	public Model() {
		this.observers = new ArrayList<Observer>();
		init();
	}

	public void init() {
		this.setShapes(new ArrayList<Shape>());
		toolChosen = UNDEF;
		colorChosen = COLOR_X;
		thicknessChosen = XL;
		firstPointDrawn = false;
		curentSelection = -1;
		drag = new Point();
		clickSelected = false;
		notifyObservers();
	}

	public void save(){
		try {
			File f = new File("save");
			FileOutputStream fos = new FileOutputStream(f);
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(observers);
			oos.writeObject(shapes);
		} catch(Exception FileNotFoundException) {
			
		}
	}

	public void load(){
		try {
			init();
			File f = new File("save");
			FileInputStream fis = new FileInputStream(f);
			ObjectInputStream ois = new ObjectInputStream(fis);
			observers = (ArrayList<Observer>) ois.readObject();
			shapes = (ArrayList<Shape>) ois.readObject();
			notifyObservers();
		} catch(FileNotFoundException FNFE) {
			
		} catch(IOException IOE) {
			
		} catch(ClassNotFoundException CNFE) {
			
		}
	}
	
	// returns the index of the top shape containing point p in list shapes,
	// returns -1 if no shapes contain the point.
	private int top(Point p) {
		for (int i = shapes.size() - 1; i >= 0; --i) {
			if ((shapes.get(i)).clicked(p)) {
				return i;
			}
		}
		return -1;
	}

	public void changeTool(int change) {
		toolChosen = change;
		notifyObservers();
	}

	public void changeColor(Color change) {
		colorChosen = change;
		if (curentSelection != -1) {
			if (toolChosen == SELECT) {
				shapes.get(curentSelection).changeBorder(colorChosen);
			} else if (toolChosen == PAINT) {
				shapes.get(curentSelection).fill(colorChosen);
			}
		}
		notifyObservers();
	}

	public void changeThickness(double thick) {
		thicknessChosen = thick;
		if (curentSelection != -1) {
			shapes.get(curentSelection).changeThicknessChosen(thicknessChosen);
		} else {
			
		}
		notifyObservers();
	}

	public void deselect() {
		curentSelection = -1;
		notifyObservers();
	}

	public void click(Point p) {
		if (toolChosen == LINE && colorChosen != COLOR_X) {
			shapes.add(new Line(p, colorChosen, thicknessChosen));
			firstPointDrawn = true;
		} else if (toolChosen == SQUARE && colorChosen != COLOR_X) {
			shapes.add(new Square(p, colorChosen, thicknessChosen));
			firstPointDrawn = true;
		} else if (toolChosen == CIRCLE && colorChosen != COLOR_X) {
			shapes.add(new Circle(p, colorChosen, thicknessChosen));
			firstPointDrawn = true;
		} else if (toolChosen == SELECT) {
			int i = top(p);
			if (i == -1) {
				// nothing is at the point, do nothing
				clickSelected = false;
			} else {
				clickSelected = true;
				colorChosen = shapes.get(i).getBorderColorChosen();
				thicknessChosen = shapes.get(i).getThicknessChosen();
				curentSelection = i;
				drag = p;
			}
		} else if (toolChosen == ERASE) {
			int i = top(p);
			if (i == -1) {
				// nothing is at the point, do nothing
			} else {
				getShapes().remove(i);
				if (curentSelection == i) {
					curentSelection = -1;
				}
			}
		} else if (toolChosen == PAINT) {
			int i = top(p);
			if (i == -1) {
				// nothing is at the point, do nothing
			} else {
				getShapes().get(i).fill(colorChosen);
			}
		}
		notifyObservers();
	}

	public void release(Point p) {
		if (toolChosen == LINE || toolChosen == SQUARE || toolChosen == CIRCLE) {
			if (firstPointDrawn) {
				getShapes().get(getShapes().size() - 1).Shape_finish(p);
				firstPointDrawn = false;

			}
		} else {

		}
		clickSelected = false;
		notifyObservers();
	}

	public void move(Point p) {
		if (toolChosen == LINE || toolChosen == SQUARE || toolChosen == CIRCLE) {
			if (firstPointDrawn) {
				getShapes().get(getShapes().size() - 1).Shape_finish(p);
			} else {
				// user is trying to find a spot to draw the first point, do nothing
			}
		} else if (toolChosen == SELECT) {
			if (curentSelection == -1) {
				// nothing is at the point, do nothing
			} else {
				if (clickSelected) {
					getShapes().get(curentSelection).move(drag, p);
					drag = p;

				}
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

	public List<Shape> getShapes() {
		return shapes;
	}

	public void setShapes(ArrayList<Shape> shapes) {
		this.shapes = shapes;
	}

	public Color getColorChosen() {
		return colorChosen;
	};

	public double getThicknessChosen() {
		return thicknessChosen;
	};

	public int getToolChosen() {
		return toolChosen;
	};

	public int getCurentSelection() {
		return curentSelection;
	};
}
