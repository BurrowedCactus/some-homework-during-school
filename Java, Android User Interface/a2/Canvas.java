import java.awt.*;
import java.awt.event.*;
import java.awt.BasicStroke;
import javax.swing.JPanel;

public class Canvas extends JPanel implements Observer {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	Point M = new Point();
	private Model model;

	public Canvas(Model model) {
		this.model = model;
		model.addObserver((Observer) this);
		/*
		 * this.addActionListener(new ActionListener() { public void
		 * actionPerformed(ActionEvent e) { //model.incrementCounter(); } });
		 */
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				model.click(e.getPoint());
			}
		});
		this.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				model.release(e.getPoint());

			}
		});
		this.addMouseMotionListener(new MouseAdapter() {
			public void mouseDragged(MouseEvent e) {
				model.move(e.getPoint());
			}
		});
		setVisible(true);
	}

	// custom graphics drawing
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g); // JPanel paint
		Graphics2D g2 = (Graphics2D) g;
		for (int i = 0 ; i < model.getShapes().size(); ++i) {
			Shape shape = (Shape) model.getShapes().get(i);
			if (shape instanceof Line) {
				drawLine(g2, shape);
			} else if (shape instanceof Circle) {
				drawCircle(g2, shape);
			} else if (shape instanceof Square) {
				drawSquare(g2, shape);
			}
		}
		
		if (model.getCurentSelection() != -1) {
			Stroke old = g2.getStroke();
			Stroke dashed = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
			Shape select = model.getShapes().get(model.getCurentSelection()); 
			g2.setStroke(dashed);
			int x1 = (int) select.getPoint1().getX();
			int y1 = (int) select.getPoint1().getY();
			int x2 = (int) select.getPoint2().getX();
			int y2 = (int) select.getPoint2().getY();
			if (select instanceof Square) {
				g2.drawRect(x1-10, y1-10, x2-x1+20, y2-y1+20);
			} else {
				g2.drawRect(x1, y1, x2-x1, y2-y1);
			}
        	g2.setStroke(old);
		}
		
	}

	public void drawLine(Graphics2D g, Shape shape) {
		Point point1 = shape.getPoint1();
		Point point2 = shape.getPoint2();
		Color borderColorChosen = shape.getBorderColorChosen();
		double thicknessChosen = shape.getThicknessChosen();

		Color oldColor = g.getColor();
		// border
		g.setColor(borderColorChosen);
		g.setStroke(new BasicStroke((float) thicknessChosen));
		if (shape.getType() == 1) {
			g.drawLine((int) point1.getX(), (int) point1.getY(), (int) point2.getX(), (int) point2.getY());
		} else {
			g.drawLine((int) point2.getX(), (int) point1.getY(), (int) point1.getX(), (int) point2.getY());
		}
		g.setColor(oldColor);

	}

	public void drawSquare(Graphics2D g, Shape shape) {
		Point point1 = shape.getPoint1();
		Point point2 = shape.getPoint2();
		Color borderColorChosen = shape.getBorderColorChosen();
		double thicknessChosen = shape.getThicknessChosen();
		Color fillColorChosen = shape.getFillColorChosen();

		Color oldColor = g.getColor();
		// fill
		if (fillColorChosen != ShapeBase.COLOR_X) {
			g.setColor(fillColorChosen);
			g.fillRect((int) point1.getX(), (int) point1.getY(), (int) (point2.getX() - point1.getX()),
					(int) (point2.getY() - point1.getY()));
		}
		// border
		g.setColor(borderColorChosen);
		g.setStroke(new BasicStroke((float) thicknessChosen));
		g.drawRect((int) point1.getX(), (int) point1.getY(), (int) (point2.getX() - point1.getX()),
				(int) (point2.getY() - point1.getY()));

		g.setColor(oldColor);
	}

	// public Circle() {};
	public void drawCircle(Graphics2D g, Shape shape) {
		Point point1 = shape.getPoint1();
		Point point2 = shape.getPoint2();
		Color borderColorChosen = shape.getBorderColorChosen();
		double thicknessChosen = shape.getThicknessChosen();
		Color fillColorChosen = shape.getFillColorChosen();

		Color oldColor = g.getColor();
		// fill
		if (fillColorChosen != ShapeBase.COLOR_X) {
			g.setColor(fillColorChosen);
			g.fillOval((int) point1.getX(), (int) point1.getY(), (int) (point2.getX() - point1.getX()),
					(int) (point2.getY() - point1.getY()));
		}
		// border
		g.setColor(borderColorChosen);
		g.setStroke(new BasicStroke((float) thicknessChosen));
		g.drawOval((int) point1.getX(), (int) point1.getY(), (int) (point2.getX() - point1.getX()),
				(int) (point2.getY() - point1.getY()));

		g.setColor(oldColor);
	}

	@Override
	public void update(Model observable) {
		model = observable;
		repaint();
	}

}
