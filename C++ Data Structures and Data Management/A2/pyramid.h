#ifndef PYRAMID_H
#define PYRAMID_H


class pyramid {
public:
	/**
	 * Create a new empty max-oriented pyramid with room for up to N items
	 * */
	explicit pyramid(int N);

	/**
	 * Destructor
	 * */
	~pyramid();
	/**
	 * Return the index of the left child of the item at given index
	 * or -1 if it does not exist.
	 * requires 0 <= index < size.
	 * */
	int leftChild(int index);

	/**
	 * Return the index of the right child of the item at given index
	 * or -1 if it does not exist.
	 * requires 0 <= index < size.
	 * */
	int rightChild(int index);

	/**
	 * Return the index of the left parent of the item at given index
	 * or -1 if it does not exist.
	 * requires 0 <= index < size.
	 * */
	int leftParent(int index);

	/**
	 * Return the index of the right parent of the item at given index
	 * or -1 if it does not exist.
	 * requires 0 <= index < size.
	 * */
	int rightParent(int index);

	/**
	 * Return the item (its value/priority) stored at the given index.
	 */
	int getItem(int index);

	/**
	 * Return the number of items stored in this pyramid
	 */
	int getSize();

	/**
	 * Inserts a new item with value/priority x into the pyramid.
	 * May not be called if size() == N.
	 */
	void insert(int x);

	/**
	 * Removes and returns an item from the pyramid with maximal priority.
	 * (Ties are broken arbitrarily.)
	 * May not be called if size() == 0.
	 */
	int deleteMax();
private:
	void formatUp (int index);
	void formatDown (int index);
	int *A;
	int size;
};


#endif //PYRAMID_H
