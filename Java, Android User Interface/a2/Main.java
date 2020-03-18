import javax.swing.*;

import java.awt.BorderLayout;
//import java.awt.*;
//import java.awt.event.*;
//import java.awt.geom.*;
import java.awt.Dimension;
import java.awt.GridLayout;
//import java.awt.event.*;
import java.awt.event.*;
import javax.swing.*;

public class Main {
	
	public static void main(String[] args) {
		
		JFrame frame = new JFrame("A2");
		Model model = new Model();
		
		Menu V_Menu = new Menu(model);
		V_Menu.setJMenuBar(frame);
		
		//components
		frame.getContentPane().setLayout(new GridLayout());
		JPanel mainPanel = new JPanel();
		frame.add(mainPanel);
		
		//left for tools, right for canvas.
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.X_AXIS));
		JPanel toolPanel = new JPanel();
		JPanel drawPanel = new JPanel();
		mainPanel.add(toolPanel);
		mainPanel.add(drawPanel);
		
		//for tools:
		toolPanel.setLayout(new BoxLayout(toolPanel, BoxLayout.Y_AXIS));
		Tool V_tool = new Tool(model);
		Palette V_color = new Palette(model);
		Thickness V_thickness = new Thickness(model);
		toolPanel.add(V_tool);
		toolPanel.add(Box.createRigidArea(new Dimension(0,35)));
		toolPanel.add(V_color);
		toolPanel.add(Box.createVerticalGlue());
		toolPanel.add(V_thickness);
		
		//for canvas:
		drawPanel.setLayout(new BorderLayout());
		Canvas V_canvas = new Canvas(model);
		V_canvas.setMaximumSize(V_canvas.getPreferredSize());
		V_canvas.setMinimumSize(V_canvas.getPreferredSize());
		//drawPanel.add(V_canvas);
		JScrollPane scrollPane = new JScrollPane(V_canvas);
		drawPanel.setPreferredSize(new Dimension(1400, 1000));
		drawPanel.add(scrollPane, BorderLayout.CENTER);
		

		model.addObserver(V_canvas);
		model.addObserver(V_Menu);
		//model.addObserver(V_tool);
		//model.addObserver(V_color);
		//model.addObserver(V_thickness);
		model.notifyObservers();
/*
		JPanel p = new JPanel(new GridLayout(1, 1));
		frame.getContentPane().add(p);
		p.add(V_canvas);
*/
		//p.add(view);
		//p.add(view2);
		

		frame.setMinimumSize(new Dimension(640, 480));
		frame.setPreferredSize(new Dimension(1600, 1200));
		frame.setMaximumSize(new Dimension(1601, 1201));
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}
}
