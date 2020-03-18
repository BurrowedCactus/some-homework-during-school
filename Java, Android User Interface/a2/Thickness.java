import java.awt.*;
import java.awt.event.*;
import java.awt.BasicStroke;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Thickness extends JPanel implements Observer {

	/**
	 * 
	 */
	private JComboBox thickness;
	private static final long serialVersionUID = 1L;
	Point M = new Point();
	private Model model;

	public Thickness(Model model) {
		this.model = model;
		model.addObserver((Observer) this);

		this.setMaximumSize(new Dimension(600, 2000));
		String[] thicknessStrings = { "S", "M", "L", "XL"};
		JLabel label = new JLabel("Choose Thickness");
		//Create the combo box, select item at index 4.
		//Indices start at 0, so 4 specifies the pig.
		thickness = new JComboBox(thicknessStrings);
		thickness.setSelectedIndex(3);
		this.add(label);
		this.add(thickness);
		thickness.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent arg0) {
				if (thickness.getSelectedItem() == "S") {
			          model.changeThickness(Model.S);
			    } else if (thickness.getSelectedItem() == "M") {
			          model.changeThickness(Model.M);
			    } else if (thickness.getSelectedItem() == "L") {
			          model.changeThickness(Model.L);
			    } else if (thickness.getSelectedItem() == "XL") {
			          model.changeThickness(Model.XL);
			    } else {}
			}	
		});
		// set the model 
		this.model = model;

		setVisible(true);
	}
	//public void actionPerformed(ActionEvent e) {
    //    JComboBox cb = (JComboBox)e.getSource();
    //    String petName = (String)cb.getSelectedItem();
    //    updateLabel(petName);
    //}

	@Override
	public void update(Model observable) {
		model = observable;
		if (model.getThicknessChosen() == Model.S && thickness.getSelectedItem() != "S") {
			thickness.setSelectedItem("S");
		} else if (model.getThicknessChosen() == Model.M && thickness.getSelectedItem() != "M") {
			thickness.setSelectedItem("M");
		} else if (model.getThicknessChosen() == Model.L && thickness.getSelectedItem() != "L") {
			thickness.setSelectedItem("L");
		} else if (model.getThicknessChosen() == Model.XL && thickness.getSelectedItem() != "XL") {
			thickness.setSelectedItem("XL");
		} else {
			
		}
		repaint();
	}

}
