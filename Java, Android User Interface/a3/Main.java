import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.*;

public class Main {
	
	public static void main(String[] args) {
		
		JFrame frame = new JFrame("A3");
		Model model = new Model();
		frame.getContentPane().setLayout(new BorderLayout());
		
		JMenuBar menuBar = new JMenuBar();
		JMenu file = new JMenu("file");
		JMenuItem reset = new JMenuItem("reset");
		reset.setAccelerator(KeyStroke.getKeyStroke('R', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		JMenuItem quit = new JMenuItem("quit");
		quit.setAccelerator(KeyStroke.getKeyStroke('Q', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		file.add(reset);
		file.addSeparator();
		file.add(quit);
		menuBar.add(file);
		frame.add(menuBar, BorderLayout.NORTH);
		
		Canvas V_canvas = new Canvas(model);
		frame.add(V_canvas);
		model.addObserver(V_canvas);
		model.notifyObservers();
		
		reset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				model.init();
			}
		});
		quit.addActionListener(new ActionListener() {
	        public void actionPerformed(ActionEvent event) {
	            System.exit(0);
	        }

	    });
		
		frame.setMinimumSize(new Dimension(640, 480));
		frame.setPreferredSize(new Dimension(1600, 1200));
		frame.setMaximumSize(new Dimension(1601, 1201));
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}
}
