template <class T>
class BinarySearchTree {
private:
	class Node {
	public:
		T data;
		Node * left;
		Node * right;
		Node * parent;
		Node() :left(NULL), right(NULL), parent(NULL) {};
		Node(const T& item) {
			data = item;
			left = NULL;
			right = NULL;
			parent = NULL;
		};
	};
public:
	BinarySearchTree();
	BinarySearchTree(BinarySearchTree&);
	~BinarySearchTree();
	bool isEmpty() const;
	bool search(const T&) const;
	T getSuccessor(const T&) const;
	T getPredecessor(const T&) const;
	T getMinimum() const;
	T getMaximum() const;
	int getHeight() const;
	int getSize() const;
	void inorder(std::ostream&) const;
	void postorder(std::ostream&) const;
	void preorder(std::ostream&) const;
	bool insert(const T&);
	bool remove(const T&);
	void displayGraphic(std::ostream&) const;
	BinarySearchTree& operator=(const BinarySearchTree& rhs);
private:
	Node * _root;
	// Additional private functions implemented as needed
};