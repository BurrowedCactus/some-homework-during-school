
import java.awt.Color;
import java.awt.Point;

public interface Shape {
	public abstract boolean clicked(Point p);

	public abstract void Shape_finish(Point p);

	public abstract void fill(Color c);
	
	public abstract Point getPoint1();

	public abstract Point getPoint2();

	public abstract Color getBorderColorChosen();

	public abstract double getThicknessChosen();

	public abstract Color getFillColorChosen();

	public abstract int getType();

	public abstract void move(Point drag, Point p);

	public abstract void changeBorder(Color colorChosen);

	public abstract void changeThicknessChosen(double thicknessChosen);
}
