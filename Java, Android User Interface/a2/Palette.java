import java.awt.*;
import java.awt.event.*;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;

public class Palette extends JPanel implements Observer {
	private JButton buttonA = new JButton("");
	private JButton buttonB = new JButton("");
	private JButton buttonC = new JButton("");
	private JButton buttonD = new JButton("");
	private JButton buttonE = new JButton("");
	private JButton buttonF = new JButton("");
	private JButton fake = new JButton("");
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	Point M = new Point();
	private Model model;
	private int which;
	public Palette(Model model) {
		this.model = model;
		model.addObserver((Observer) this);
		this.setMinimumSize(new Dimension(100, 100));
		this.setPreferredSize(new Dimension(200, 400));
		this.setMaximumSize(new Dimension(200, 5000));
		

		buttonA.setBackground(Model.COLOR_1);
		buttonB.setBackground(Model.COLOR_2);
		buttonC.setBackground(Model.COLOR_3);
		buttonD.setBackground(Model.COLOR_4);
		buttonE.setBackground(Model.COLOR_5);
		buttonF.setBackground(Model.COLOR_6);
		which = -1;

		// a GridBagLayout with default constraints centres
		// the widget in the window
		this.setLayout(new GridLayout(0,2));
		this.add(buttonA);
		this.add(buttonB);
		this.add(buttonC);
		this.add(buttonD);
		this.add(buttonE);
		this.add(buttonF);
		
		// set the model 
		this.model = model;
		
		// setup the event to go to the "controller"
		// (this anonymous class is essentially the controller)
		buttonA.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_1);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 0;
				buttonA.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});	
		buttonB.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_2);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 1;
				buttonB.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});
		buttonC.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_3);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 2;
				buttonC.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});
		buttonD.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_4);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 3;
				buttonD.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});
		buttonE.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_5);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 4;
				buttonE.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});
		buttonF.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeColor(Model.COLOR_6);
				if (which == 0) {
					buttonA.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonB.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonC.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonD.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonE.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonF.setBorder(fake.getBorder());
				}
				which = 5;
				buttonF.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
			}
		});

		setVisible(true);
	}

	// custom graphics drawing
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g); // JPanel paint
		Graphics2D g2 = (Graphics2D) g;
		
		
	}

	
	@Override
	public void update(Model observable) {
		model = observable;
		buttonA.setBorder(fake.getBorder());
		buttonB.setBorder(fake.getBorder());
		buttonC.setBorder(fake.getBorder());
		buttonD.setBorder(fake.getBorder());
		buttonE.setBorder(fake.getBorder());
		buttonF.setBorder(fake.getBorder());
		if (model.getColorChosen() == Model.COLOR_1) {
			which = 0;
			buttonA.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		} else if (model.getColorChosen() == Model.COLOR_2) {
			which = 1;
			buttonB.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		} else if (model.getColorChosen() == Model.COLOR_3) {
			which = 2;
			buttonC.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		} else if (model.getColorChosen() == Model.COLOR_4) {
			which = 3;
			buttonD.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		} else if (model.getColorChosen() == Model.COLOR_5) {
			which = 4;
			buttonE.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		} else if (model.getColorChosen() == Model.COLOR_6) {
			which = 5;
			buttonF.setBorder(BorderFactory.createLineBorder(Color.CYAN, 5));
		}
		
		repaint();
	}

}
