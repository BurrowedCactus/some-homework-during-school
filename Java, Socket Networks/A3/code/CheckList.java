import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

public class CheckList implements Serializable {
	private static final long serialVersionUID = 1L;
	ArrayList<ArrayList<Boolean>> checkList;
	// the id of the other peer whom it should upload file to.
	int nextJobToWhom;
	// the id of the file that it will upload next.
	int nextJobFromWhich;
	// the index of the chunk of the file that it will upload next.
	int nextJobFromWhere;
	
	public CheckList() {
		checkList = new ArrayList<ArrayList<Boolean>>();
	}

	public void addList(int size) {
		checkList.add(new ArrayList<Boolean>(Collections.nCopies(size, true)));
	}

	private void update() {
		
	}
	
	public void updateTable(int index, CheckList other) {
		updateList(index, other.getList(index));
	}

	public void updateList(int index, ArrayList<Boolean> listToBeModified) {
		checkList.set(index, listToBeModified);
		update();
	}

	public ArrayList<Boolean> getList(int index) {
		return checkList.get(index);
	}

	public void removeList(int index) {
		checkList.remove(index);
	}

	public void markTrue(int id, int index) {
		checkList.get(id).set(index, true);
	}

	private void isAllTrue(ArrayList<Boolean> list, boolean result) {
		if (list.contains(Boolean.FALSE)) {
			result = false;
		}
	}

	public boolean isEverythingTrue() {
		boolean isComplete = true;
		checkList.forEach(list -> isAllTrue(list, isComplete));
		return isComplete;
	}
}
