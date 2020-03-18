import java.awt.*;
import java.awt.event.*;

import javax.imageio.ImageIO;
import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.KeyStroke;
import javax.swing.border.Border;

public class Tool extends JPanel implements Observer {

	/**
	 * 
	 */
	private JButton buttonSe;
	private JButton buttonEr;
	private JButton buttonLi;
	private JButton buttonSq;
	private JButton buttonCi;
	private JButton buttonFi;
	private JButton fake;
	private static final long serialVersionUID = 1L;
	Point M = new Point();
	private Model model;
	private int which;
	public Tool(Model model) {
		super(new GridLayout(2,3));
		this.model = model;
		model.addObserver((Observer) this);
		this.setMinimumSize(new Dimension(100, 100));
		this.setPreferredSize(new Dimension(200, 400));
		this.setMaximumSize(new Dimension(200, 5000));
		
		
		buttonSe = new JButton("Select");
		buttonEr = new JButton("Erase");
		buttonLi = new JButton("Line");
		buttonSq = new JButton("Square");
		buttonCi = new JButton("Circle");
		buttonFi = new JButton("Fill");
		fake = new JButton();
		which = -1;
		/*
		try {
		    Image img = ImageIO.read(getClass().getResource("select.png"));
		    buttonSe.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
		try {
		    Image img = ImageIO.read(getClass().getResource("erase.png"));
		    buttonEr.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
		try {
		    Image img = ImageIO.read(getClass().getResource("line.png"));
		    buttonLi.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
		try {
		    Image img = ImageIO.read(getClass().getResource("square.png"));
		    buttonSq.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
		try {
		    Image img = ImageIO.read(getClass().getResource("circle.png"));
		    buttonCi.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
		try {
		    Image img = ImageIO.read(getClass().getResource("paint.png"));
		    buttonFi.setIcon(new ImageIcon(img));
		  } catch (Exception ex) {
		    System.out.println(ex);
		  }
*/
		// a GridBagLayout with default constraints centres
		// the widget in the window
		this.setLayout(new GridLayout(0,2));
		this.add(buttonSe);
		this.add(buttonEr);
		this.add(buttonLi);
		this.add(buttonSq);
		this.add(buttonCi);
		this.add(buttonFi);
		
		
		// set the model 
		this.model = model;
		
		
		// setup the event to go to the "controller"
		// (this anonymous class is essentially the controller)
		buttonSe.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.SELECT);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 0;
				buttonSe.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
			}
		});	
		
		buttonEr.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.ERASE);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 1;
				buttonEr.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
			}
		});
		buttonLi.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.LINE);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 2;
				buttonLi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
				
			}
		});
		buttonSq.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.SQUARE);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 3;
				buttonSq.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
				
			}
		});
		buttonCi.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.CIRCLE);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 4;
				buttonCi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
				
			}
		});
		buttonFi.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				model.changeTool(Model.PAINT);
				if (which == 0) {
					buttonSe.setBorder(fake.getBorder());
				} else if (which == 1) {
					buttonEr.setBorder(fake.getBorder());
				} else if (which == 2) {
					buttonLi.setBorder(fake.getBorder());
				} else if (which == 3) {
					buttonSq.setBorder(fake.getBorder());
				} else if (which == 4) {
					buttonCi.setBorder(fake.getBorder());
				} else if (which == 5) {
					buttonFi.setBorder(fake.getBorder());
				}
				which = 5;
				buttonFi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5)); 
				
			}
		});

		setVisible(true);
	}
	
	
	@Override
	public void update(Model observable) {
		model = observable;
		buttonSe.setBorder(fake.getBorder());
		buttonEr.setBorder(fake.getBorder());
		buttonLi.setBorder(fake.getBorder());
		buttonSq.setBorder(fake.getBorder());
		buttonCi.setBorder(fake.getBorder());
		buttonFi.setBorder(fake.getBorder());
		if (model.getToolChosen() == Model.SELECT) {
			which = 0;
			buttonSe.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		} else if (model.getToolChosen() == Model.ERASE) {
			which = 1;
			buttonEr.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		} else if (model.getToolChosen() == Model.LINE) {
			which = 2;
			buttonLi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		} else if (model.getToolChosen() == Model.SQUARE) {
			which = 3;
			buttonSq.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		} else if (model.getToolChosen() == Model.CIRCLE) {
			which = 4;
			buttonCi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		} else if (model.getToolChosen() == Model.PAINT) {
			which = 5;
			buttonFi.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));
		}
		
		repaint();
	}

}
