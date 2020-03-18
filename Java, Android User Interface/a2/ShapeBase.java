
import java.awt.Color;
import java.awt.Point;
import java.lang.Math;

public abstract class ShapeBase {
	protected static final int CLICK_DISTANCE = 10;
	protected static final Color COLOR_X = new Color(255, 255, 255, 255);
	protected Point click1;
	protected Point click2;
	protected Point point1;
	protected Point point2;
	protected Color borderColorChosen;
	protected double thicknessChosen;
	protected Color fillColorChosen;


	
	public ShapeBase(Point p, Color borderColor, double thickness) {
		click1 = new Point();
		click2 = new Point();
		point1 = new Point();
		point2 = new Point();
		click1.setLocation(p.getX(), p.getY());
		click2.setLocation(p.getX(), p.getY());
		point1.setLocation(p.getX(), p.getY());
		point2.setLocation(p.getX(), p.getY());
		borderColorChosen = borderColor;
		thicknessChosen = thickness;
		fillColorChosen = COLOR_X;
	}

	public void Shape_finish(Point p) {
		click2 = p;
		point1.setLocation(Math.min(click1.getX(), click2.getX()), Math.min(click1.getY(), click2.getY()));
		point2.setLocation(Math.max(click1.getX(), click2.getX()), Math.max(click1.getY(), click2.getY()));
	}
	
	public void move(Point drag, Point p) {
		double dx = p.getX() - drag.getX();
		double dy = p.getY() - drag.getY();
		click1.translate((int)dx, (int)dy);
		click2.translate((int)dx, (int)dy);
		point1.translate((int)dx, (int)dy);
		point2.translate((int)dx, (int)dy);
	}
	public void changeBorder(Color colorChosen) {
		borderColorChosen = colorChosen;
	}
	public void changeThicknessChosen(double thickness) {
		thicknessChosen = thickness;
	}
	
	public void fill(Color fillColor) {
		fillColorChosen = fillColor;
	}

	public Color getFillColorChosen() {
		return fillColorChosen;
	}

	public Color getBorderColorChosen() {
		return borderColorChosen;
	}

	public double getThicknessChosen() {
		return thicknessChosen;
	}

	public void setFillColorChosen(Color a) {
		fillColorChosen = a;
	}

	public void setBorderColorChosen(Color a) {
		borderColorChosen = a;
	}

	public void setThicknessChosen(int a) {
		thicknessChosen = a;
	}

	public Point getPoint1() {
		return point1;
	}

	public Point getPoint2() {
		return point2;
	}

}
