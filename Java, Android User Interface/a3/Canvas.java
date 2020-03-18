import java.awt.*;
import java.awt.event.*;
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
		for (int i = 0; i < 14; ++i) {
			g2.draw(model.getShapes()[i]);
		}
	}

	
	@Override
	public void update(Model observable) {
		model = observable;
		repaint();
	}

}
