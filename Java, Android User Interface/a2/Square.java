
import java.awt.*;

public class Square extends ShapeBase implements Shape {

	public Square(Point p, Color borderColorChosen, double thicknessChosen) {
		super(p, borderColorChosen, thicknessChosen);
	}

	public boolean clicked(Point p) {
		double x0 = p.getX();
		double y0 = p.getY();
		double x1 = point1.getX();
		double y1 = point1.getY();
		double x2 = point2.getX();
		double y2 = point2.getY();
		if (Math.abs(x2 - x1) < 5) {
			// length too short
		}
		if (Math.abs(y2 - y1) < 5) {
			// height too short
		}
		return (x1 <= x0) && (x0 <= x2) && (y1 <= y0) && (y0 <= y2);
	}

	public int getType() {
		return 0;
	}
}
