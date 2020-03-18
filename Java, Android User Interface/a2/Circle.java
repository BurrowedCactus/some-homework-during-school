import java.awt.Color;
import java.lang.Math;
import java.awt.Point;

/**
 *
 * @author yongy
 */
public class Circle extends ShapeBase implements Shape {

	public Circle(Point p, Color borderColorChosen, double thicknessChosen) {
		super(p, borderColorChosen, thicknessChosen);
	}

	public boolean clicked(Point p) {
		double x0 = p.getX();
		double y0 = p.getY();
		double x1 = point1.getX();
		double y1 = point1.getY();
		double x2 = point2.getX();
		double y2 = point2.getY();
		// center
		double xc = (x2 + x1) / 2;
		double yc = (y2 + y1) / 2;
		// radius
		double xr = (x2 - x1) / 2;
		double yr = (y2 - y1) / 2;
		if (xr == 0) {
			return false;
		}
		if (yr == 0) {
			return false;
		}
		return Math.hypot((x0 - xc) / xr, (y0 - yc) / yr) <= 1;
	}

	public int getType() {
		return 0;
	}


}
