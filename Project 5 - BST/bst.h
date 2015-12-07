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

		Node(const T& item) {

			data = item;
			left = NULL;
			right = NULL;
			parent = NULL;
		};

		~Node() {
		
			delete left;
			delete right;		
		}

		T getMinFromNode() {

			if (left == NULL) return data;

			else return left->getMaxFromNode();
		}

		T getMaxFromNode() {

			if (right == NULL) return data;

			else return right->getMaxFromNode();
		}

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
	};

public:

	Node * _root;

	BinarySearchTree() {}

	BinarySearchTree(BinarySearchTree & toCopy) {

		cout << "Copy Constructor" << endl;
	
		copyBinarySearchTree(toCopy._root, _root);
	}

	~BinarySearchTree() {

		if (_root != NULL) {
		
			deleteBinarySearchTree(_root);
		}
	}

	bool isEmpty() const {
	
		if (_root == NULL) {
		
			return true;
		}

		else return false;	
	}

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

	T getMinimum() const {

		if (_root == NULL) return NULL;

		else if (_root->right == NULL) return _root->data;

		else {

			Node minNode;

			getMinimumHelper(_root, minNode);
			
			cout << "The minimum value in the tree is: " << minNode.data << endl;
		}
	}

	T getMaximum() const {
	
		if (_root == NULL) return NULL;

		else if (_root->right == NULL) return _root->data;

		else {

			Node maxNode;

			getMaximumHelper(_root, maxNode);

			cout << "The maximum value in the tree is: " << maxNode.data << endl;

		}
	}

	int getHeight(Node * tree) const {
		
		if (tree == NULL) return -1;

		int leftDepth = getHeight(tree->left);
		int rightDepth = getHeight(tree->right);

		if (leftDepth > rightDepth) return leftDepth + 1;

		else return rightDepth + 1;
	}

	int getSize(Node * node) const {
	
		if (node == NULL) return 0;

		else {

			return (getSize(node->left) + getSize(node->right) + 1);
		}
	}

	void inorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		inorderHelper(out, _root);

		out << endl;
	}

	void postorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		postorderHelper(out, _root);

		out << endl;
	}

	void preorder(std::ostream & out) const {
	
		if (_root == NULL) {

			out << "Tree is empty\n\n";
			return;
		}

		preorderHelper(out, _root);

		out << endl;
	}

	bool insert(const T & data) {

		Node * currentNode = _root;
	
		if (_root == NULL) {
			
			_root = new Node(data);
			return true;
		}

		else _root->insertUtil(data);
	}

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

	BinarySearchTree& operator=(const BinarySearchTree& rhs) {
	
		cout << "\n\nAssignment Operator\n\n";

		copyBinarySearchTree(rhs._root, _root);

		return *this;	
	}

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

	void getMinimumHelper(Node * currentNode, Node & minNode) const {
		
		while (currentNode->left != NULL) {

			currentNode = currentNode->left;
		}

		minNode.data = currentNode->data;
	}

	void getMaximumHelper(Node * currentNode, Node & maxNode) const {

		while (currentNode->right != NULL) {

			currentNode = currentNode->right;
		}

		maxNode.data = currentNode->data;
	}

	void inorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		inorderHelper(out, currentNode->left);
		out << currentNode->data << " ";
		inorderHelper(out, currentNode->right);
	
	}

	void preorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		out << currentNode->data << " ";
		preorderHelper(out, currentNode->left);
		preorderHelper(out, currentNode->right);

	}

	void postorderHelper(std::ostream & out, Node * currentNode) const {
	
		if (currentNode == NULL) return;

		postorderHelper(out, currentNode->left);
		postorderHelper(out, currentNode->right);
		out << currentNode->data << " ";

	}

	//used by destructor
	void deleteBinarySearchTree(Node * &subtreeRoot) {

		delete _root;
	}
};