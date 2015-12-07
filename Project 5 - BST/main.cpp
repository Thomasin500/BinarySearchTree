#pragma once

///////////////////////////////////
//	Thomas Freeman
//	Data Structures Project 5 - Binary Search Tree
///////////////////////////////////

#include "bst.h"
#include <string>

using namespace std;

int main() {

	cout << "Thomas Freeman's Binary Search Tree Project\n\n";

	cout << "Tree 1: Integer\n";

	BinarySearchTree<int> bst;

	cout << "\nInsert in this order: 10, 15, 5, 12, 11, 7, 6, 0";

	bst.insert(10);
	bst.insert(15);
	bst.insert(5);
	bst.insert(12);
	bst.insert(11);
	bst.insert(7);
	bst.insert(6);
	bst.insert(0);

	cout << "\nDisplay pre-order: \n";
	bst.preorder(cout);

	cout << "\nDisplay in order: \n";
	bst.inorder(cout);

	cout << "\nDisplay post-order: \n";
	bst.postorder(cout);

	cout << "\nRemove 0";
	bst.remove(0);
	
	cout << "\n\nSearch for 7 (true): ";
	cout << bst.search(7);

	cout << "\nSearch for 0 (false): ";
	cout << bst.search(0);

	cout << "\n\nHeight of tree is: ";
	cout << bst.getHeight(bst._root);

	cout << "\n\nMaximum is : ";
	bst.getMaximum();

	cout << "\nMaximum is : ";
	bst.getMinimum();
	
	cout << "\n\n\n\nTree 2: String\n";

	BinarySearchTree<string> bst2;

	cout << "\nInsert in this order: hi, goodbye, welcome, come, go, find";

	bst2.insert("hi");
	bst2.insert("goodbye");
	bst2.insert("welcome");
	bst2.insert("come");
	bst2.insert("go");
	bst2.insert("find");

	cout << "\n\nDisplay pre-order: \n";
	bst2.preorder(cout);

	cout << "\nDisplay in order: \n";
	bst2.inorder(cout);

	cout << "\nDisplay post-order: \n";
	bst2.postorder(cout);

	cout << "\nSearch for hi (true): ";
	cout << bst2.search("hi");

	cout << "\nSearch for hello (false): ";
	cout << bst2.search("hello");

	cout << "\n\nSize of the tree is: ";
	cout << bst2.getSize(bst2._root);

	cout << "\n\n\n\nTesting Copy Constructor and Assignment Operator";
	cout << "\nBefore\n";

	bst.inorder(cout);

	BinarySearchTree<int> bst3;
	
	bst3 = bst;
	bst3.insert(9999);

	cout << "\nAfter" << endl;

	bst.inorder(cout);
	bst3.inorder(cout);
	
	cout << "\nBefore\n";	

	BinarySearchTree<int> bst4 = bst;

	bst4.insert(4567);

	cout << "\nAfter" << endl;

	bst.inorder(cout);
	bst4.inorder(cout);

	cout << "\n\nTesting done, press enter to exit";

	cin.ignore();

	return 1;
}