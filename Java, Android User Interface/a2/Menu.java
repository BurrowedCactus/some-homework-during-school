import java.awt.*;
import java.awt.event.*;
import java.awt.BasicStroke;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

public class Menu extends JPanel implements Observer {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	Point M = new Point();
	private Model model;
	private JMenuBar menuBar;
	private JMenu menu1, menu2;
	private JMenuItem restart, save, load, clearSelection;
	private JMenuItem fullSize, fitToWindow;
	public Menu(Model model) {
		this.model = model;
		model.addObserver((Observer) this);
		
		
		//JMenuItem menuItem;
		//Create the menu bar.
		menuBar = new JMenuBar();

		//Build the first menu.
		menu1 = new JMenu("File");
		menu1.setText("File");
		menuBar.add(menu1);
		
		restart = new JMenuItem("file - new");
		save = new JMenuItem("file - save");
		load = new JMenuItem("file - load");
		clearSelection = new JMenuItem("clear selection");
		menu1.add(restart);
		menu1.add(save);
		menu1.add(load);
		menu1.add(clearSelection);
		
		//Build second menu in the menu bar.
		menu2 = new JMenu("View");
		menu2.setText("View");
		menuBar.add(menu2);
		
		fullSize = new JMenuItem("view - full size");
		fitToWindow = new JMenuItem("view - fit to window");
		menu2.add(fullSize);
		menu2.add(fitToWindow);
		
		restart.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				model.init();
			}
		});
		
		clearSelection.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				model.deselect();
			}
		});
		
		setVisible(true);
	}
	public void setJMenuBar(JFrame jf) {
		jf.setJMenuBar(menuBar);
	}

	@Override
	public void update(Model observable) {
		model = observable;
		repaint();
	}

}
