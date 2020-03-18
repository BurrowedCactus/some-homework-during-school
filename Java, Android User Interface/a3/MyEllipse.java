

import java.awt.Point;
import java.awt.geom.Ellipse2D;

public class MyEllipse extends Ellipse2D.Double {
	private boolean movable;

	MyEllipse(double x, double y, double w, double h, boolean move) {
		super(x, y, w, h);
		movable = move;
	}

	public void move(Point start, Point end) {
		if (movable) {
			double dx = end.getX() - start.getX();
			double dy = end.getY() - start.getY();
			x += dx;
			y += dy;
		}
	}

}
