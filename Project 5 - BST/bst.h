#pragma once

using namespace std;

#include <iostream>
#include <string>

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
		/*-----------------------------------------------------------------------
		Constructor for Node Class

		Precondition:  none
		Postcondition: Node Object is created
		-----------------------------------------------------------------------*/

		Node(const T& item) {

			data = item;
			left = NULL;
			right = NULL;
			parent = NULL;
		};
		/*-----------------------------------------------------------------------
		Specific Constructor for Node Class

		Precondition:  any class item
		Postcondition: Node Object is created with its data set to the item
		-----------------------------------------------------------------------*/

		~Node() {
		
			delete left;
			delete right;		
		}
		/*-----------------------------------------------------------------------
		Destructor for Node Class

		Precondition:  Node Object
		Postcondition: Node Object is deleted along with its child pointers
		-----------------------------------------------------------------------*/

		T getMinFromNode() {

			if (left == NULL) return data;

			else return left->getMaxFromNode();
		}
		/*-----------------------------------------------------------------------
		getMinFromNode

		Precondition:  none
		Postcondition: Returns the data member of the smallest node below this node
		-----------------------------------------------------------------------*/

		T getMaxFromNode() {

			if (right == NULL) return data;

			else return right->getMaxFromNode();
		}
		/*-----------------------------------------------------------------------
		getMaxFromNode

		Precondition:  none
		Postcondition: Returns the data member of the largest node below this node
		-----------------------------------------------------------------------*/

		bool insertUtil(const T & data) {

			if (this->data == data) return false; //does not allow for duplicate data entries 

			else if (data < this->data) {
			
				if (left == NULL) {

					left = new Node(data);
					return true;
				}

				else return left->insertUtil(data); //move down the tree more			
			}

			else if (data > this->data) {
			
				if (right == NULL) {
				
					right = new Node(data);
					return true;
				}

				else return right->insertUtil(data); //move down the tree another step			
			}
			
			return false;
		}
		/*-----------------------------------------------------------------------
		insertUtil

		Precondition:  data item of node to be inserted
		Postcondition: a helper function for the insert function
		-----------------------------------------------------------------------*/

		Node * removeUtil(Node * node, T data) {

			if (data < this->data) {

				if (left != NULL) {

					return left->removeUtil(this, data);
				}

				else return NULL;
			}

			else if (data > this->data) {

				if (right != NULL) {

					return right->removeUtil(this, data);
				}

				else return NULL;
			}

			else {

				if (left != NULL && right != NULL) {

					this->data = right->getMinFromNode();
					
					return right->removeUtil(this, this->data);
				}

				else if (node->left == this) {

					if (left != NULL) {

						node->left = left;
					}

					else node->left = right;

					return this;
				}

				else if (node->right == this) {

					if (left != NULL) {

						node->right = left;
					}

					else node->right = right;

					return this;
				}
			}
		}	
		/*-----------------------------------------------------------------------
		removeUtil

		Precondition:  data item of node to be removed
		Postcondition: a helper function for the remove function
		-----------------------------------------------------------------------*/
	};

public:

	Node * _root; //pointer to root node of tree

	BinarySearchTree() {} //basic constructor of class

	BinarySearchTree(BinarySearchTree & toCopy) {

		cout << "Copy Constructor" << endl;
	
		copyBinarySearchTree(toCopy._root, _root);
	}
	/*-----------------------------------------------------------------------
	copy constructor 

	Precondition:  instaniated BST object
	Postcondition: this object is created and now contains the same data as the referenced node
	-----------------------------------------------------------------------*/

	~BinarySearchTree() {

		if (_root != NULL) {
		
			deleteBinarySearchTree(_root);
		}
	}
	/*-----------------------------------------------------------------------
	destructor

	Precondition:  BST objet
	Postcondition: calls the deleteBST function which deletes all nodes within the tree and then the root itself
	-----------------------------------------------------------------------*/

	bool isEmpty() const {
	
		if (_root == NULL) {
		
			return true;
		}

		else return false;	
	}
	/*-----------------------------------------------------------------------
	isEmpty

	Precondition:  none
	Postcondition: returns if the tree is empty or not
	-----------------------------------------------------------------------*/

	bool search(const T & data) const {
	
		Node * currentNode = _root;

		while (currentNode != NULL) {

			if (data == currentNode->data) {
					
				return true;
			}
			
			else if (data < currentNode->data) {

				currentNode = currentNode->left;
			}

			else if (data > currentNode->data) {

				currentNode = currentNode->right;
			}
		}

		return false;
	}
	/*-----------------------------------------------------------------------
	search

	Precondition:  data item of node to be searched for
	Postcondition: returns true if the data item exists within a node within the tree
	-----------------------------------------------------------------------*/

	T getMinimum() const {

		if (_root == NULL) return NULL;

		else if (_root->right == NULL) return _root->data;

		else {

			Node minNode;

			getMinimumHelper(_root, minNode);
			
			cout << "The minimum value in the tree is: " << minNode.data << endl;
		}
	}
	/*-----------------------------------------------------------------------
	getMinimum

	Precondition:  none
	Postcondition: returns the smallest node in the tree
	-----------------------------------------------------------------------*/

	T getMaximum() const {
	
		if (_root == NULL) return NULL;

		else if (_root->right == NULL) return _root->data;

		else {

			Node maxNode;

			getMaximumHelper(_root, maxNode);

			cout << "The maximum value in the tree is: " << maxNode.data << endl;

		}
	}
	/*-----------------------------------------------------------------------
	getMaximum

	Precondition:  none
	Postcondition: returns the largest node in the tree
	-----------------------------------------------------------------------*/

	int getHeight(Node * tree) const {
		
		if (tree == NULL) return -1;

		int leftDepth = getHeight(tree->left);
		int rightDepth = getHeight(tree->right);

		if (leftDepth > rightDepth) return leftDepth + 1;

		else return rightDepth + 1;
	}
	/*-----------------------------------------------------------------------
	getHeight

	Precondition:  a pointer to a node within the tree
	Postcondition: returns the number of layers in the tree
	-----------------------------------------------------------------------*/

	int getSize(Node * node) const {
	
		if (node == NULL) return 0;

		else {

			return (getSize(node->left) + getSize(node->right) + 1);
		}
	}
	/*-----------------------------------------------------------------------
	getSize

	Precondition:  pointer to a node
	Postcondition: returns the number of nodes in the tree
	-----------------------------------------------------------------------*/

	void inorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		inorderHelper(out, _root);

		out << endl;
	}
	/*-----------------------------------------------------------------------
	inorder

	Precondition:  out stream to be outputted to
	Postcondition: outputs the tree in order traverse
	-----------------------------------------------------------------------*/

	void postorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		postorderHelper(out, _root);

		out << endl;
	}
	/*-----------------------------------------------------------------------
	postorder

	Precondition:  out stream to be outputted to
	Postcondition: outputs the tree post order traverse
	-----------------------------------------------------------------------*/

	void preorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		preorderHelper(out, _root);

		out << endl;
	}
	/*-----------------------------------------------------------------------
	preorder

	Precondition:  out stream to be outputted to
	Postcondition: outputs the tree pre order traverse
	-----------------------------------------------------------------------*/

	bool insert(const T & data) {

		Node * currentNode = _root;
	
		if (_root == NULL) {
			
			_root = new Node(data);
			return true;
		}

		else _root->insertUtil(data);
	}
	/*-----------------------------------------------------------------------
	insert

	Precondition:  data item to be inserted
	Postcondition: calls the helper function insertUtil of the node class, node with data item is now inserted
	-----------------------------------------------------------------------*/

	bool remove(const T &data) {
	
		if (_root == NULL) return false;

		else {
		
			if (_root->data == data) {
			
				Node tempNode;
				tempNode.left = _root;
				Node * oldNode = _root->removeUtil(&tempNode, data);
				_root = tempNode.left;

				if (oldNode != NULL) {

					delete oldNode;
					return true;
				}

				else return false;
			}

			else {

				Node * oldNode = _root->removeUtil(NULL, data);

				if (oldNode != NULL) {

					delete oldNode;
					return true;
				}

				else return false;
			}		
		}	
	}
	/*-----------------------------------------------------------------------
	remove

	Precondition:  data item of node to be removed
	Postcondition: the reference node is now deleted
	-----------------------------------------------------------------------*/

	void displayGraphic(std::ostream& out, Node * node, int level) const {
	
		if (_root == NULL) out << "Tree is Empty\n\n";

		else {

			if (node != NULL) {

				displayGraphic(out, node->right, level + 1);

				cout << endl;

				if (node->data == _root->data) cout << "Root:  ";

				else {

					for (int i = 0; i < level; i++) {

						cout << "    ";
					}
				}

				out << node->data;

				displayGraphic(out, node->left, level + 1);
			}			
		}	
	}
	/*-----------------------------------------------------------------------
	displayGraphic

	Precondition:  out stream to be outputted to
	Postcondition: displays the tree graphaically horizontially
	-----------------------------------------------------------------------*/

	BinarySearchTree& operator=(const BinarySearchTree& rhs) {
	
		cout << "\n\nAssignment Operator\n\n";

		copyBinarySearchTree(rhs._root, _root);

		return *this;	
	}
	/*-----------------------------------------------------------------------
	operator '='

	Precondition:  the BST object RHS
	Postcondition: copies the RHS of the arguement to the LHS object
	-----------------------------------------------------------------------*/


private: 

	// Additional private functions implemented as needed

	void copyBinarySearchTree(Node * original, Node *& copy) {

		if (original == NULL) {

			copy = NULL;
		}

		else {

			copy = new Node();
			copy->data = original->data;
			copy->parent = original->parent;
			copyBinarySearchTree(original->left, copy->left);
			copyBinarySearchTree(original->right, copy->right);
		}
	}
	/*-----------------------------------------------------------------------
	copyBinarySearchTree

	Precondition:  the original and tocopy nodes of the tree
	Postcondition: util function that will copy the RHS tree to the LHS
	-----------------------------------------------------------------------*/

	void getMinimumHelper(Node * currentNode, Node & minNode) const {
		
		while (currentNode->left != NULL) {

			currentNode = currentNode->left;
		}

		minNode.data = currentNode->data;
	}
	/*-----------------------------------------------------------------------
	getMinimumHelper

	Precondition:  the current and minimum node of the tree
	Postcondition: a helper function for getminimum, sets the minimum value in the node
	-----------------------------------------------------------------------*/

	void getMaximumHelper(Node * currentNode, Node & maxNode) const {

		while (currentNode->right != NULL) {

			currentNode = currentNode->right;
		}

		maxNode.data = currentNode->data;
	}
	/*-----------------------------------------------------------------------
	getMaximumHelper

	Precondition:  the current and maximum node of the tree
	Postcondition: a helper function for getMaximum, sets the maximum value in the node
	-----------------------------------------------------------------------*/

	void inorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		inorderHelper(out, currentNode->left);
		out << currentNode->data << " ";
		inorderHelper(out, currentNode->right);
	
	}
	/*-----------------------------------------------------------------------
	inorderHelper

	Precondition:  the out stream and current node of the tree
	Postcondition: a helper function for inorder, outputs the tree in order trasversal
	-----------------------------------------------------------------------*/

	void preorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		out << currentNode->data << " ";
		preorderHelper(out, currentNode->left);
		preorderHelper(out, currentNode->right);

	}
	/*-----------------------------------------------------------------------
	preorderHelper

	Precondition:  the out stream and current node of the tree
	Postcondition: a helper function for inorder, outputs the tree pre order trasversal
	-----------------------------------------------------------------------*/

	void postorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		postorderHelper(out, currentNode->left);
		postorderHelper(out, currentNode->right);
		out << currentNode->data << " ";

	}
	/*-----------------------------------------------------------------------
	postorderHelper

	Precondition:  the out stream and current node of the tree
	Postcondition: a helper function for inorder, outputs the tree in post order trasversal
	-----------------------------------------------------------------------*/

	//used by destructor
	void deleteBinarySearchTree(Node * &subtreeRoot) {

		delete _root;
	}
	/*-----------------------------------------------------------------------
	deleteBinarySearchTree

	Precondition:  the node of the root of the tree
	Postcondition: a helper function for the destructor, deletes the root of the tree and will recursively call the deletion of the rest of the tree (C++ standard)
	-----------------------------------------------------------------------*/
};