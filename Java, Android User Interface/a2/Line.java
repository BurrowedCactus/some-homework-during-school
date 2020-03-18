
import java.awt.*;
import java.lang.Math;
public class Line extends ShapeBase implements Shape {
	public Line(Point p, Color borderColorChosen, double thicknessChosen) {
		super(p, borderColorChosen, thicknessChosen);
	}

	// https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
	// by Joshua
	private double distance(double x, double y, double x1, double y1, double x2, double y2) {

		double A = x - x1;
		double B = y - y1;
		double C = x2 - x1;
		double D = y2 - y1;

		double dot = A * C + B * D;
		double len_sq = C * C + D * D;
		double param = -1;
		if (len_sq != 0) // in case of 0 length line
			param = dot / len_sq;

		double xx, yy;

		if (param < 0) {
			xx = x1;
			yy = y1;
		} else if (param > 1) {
			xx = x2;
			yy = y2;
		} else {
			xx = x1 + param * C;
			yy = y1 + param * D;
		}

		var dx = x - xx;
		var dy = y - yy;
		return Math.sqrt(dx * dx + dy * dy);
	}

	public boolean clicked(Point p) {
		double x0 = p.getX();
		double y0 = p.getY();
		double x1 = click1.getX();
		double y1 = click1.getY();
		double x2 = click2.getX();
		double y2 = click2.getY();
		return distance(x0, y0, x1, y1, x2, y2) <= CLICK_DISTANCE;
	}
	
	// if type == 1 the line is drawn like "\"
        // if type == 2 the line is drawn like "/"
	public int getType() {
		if ((point1.getX() == click1.getX() && point1.getY() == click1.getY()) || (point1.getX() == click2.getX() && point1.getY() == click2.getY())){
			return 1;
		} else {
			return 2;
		}
	}


}
