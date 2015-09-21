/*
2-3 Tree API header file with function declaration 
Written by Suvigya Tripathi, 4/4/2015
*/

#include<iostream>
#include<assert.h>

using namespace std;


// 2-3 tree node (complete)

struct Node {
	int leftData;             // data item on "left" side of node
	int rightData;            // data item on "right" side of node
	short value;                 // number of data items (1 or 2)
	Node *left;      // left subtree
	Node *middle;    // middle subtree
	Node *right;     // right subtree
	Node *parent;    // parent (may not need)
};


class tree23 {
	Node *root;
	void doInorder(Node *);
	void Search(Node *, int);
	void helperFunc(Node *, int);  //helper function for insertion
	int* promote(int, int, int);   //sort the three elements passed in
	Node* splitNode(Node*, Node*, int); //split node
	void insertSecondItem(Node*, int); //insert a new item to a 2-node
	bool isLeaf(Node*);   //check if the node is leaf
	int childPosition(Node*, Node*);  //check if a node is parent's left, middle, or right child
	void printNode(Node*);   //print a node's value(s)
	Node* init(int); //create a new node

public:
	int treeHeight = 0;
	tree23() { root = NULL; };        // constructor
	void insert(int);                // insert an item
	void inorder(){
		doInorder(root);     // inorder traversal
		cout << endl;
	};

	void search1(int k){
		Search(root, k);	//Search a given data
		cout << endl;
	};

	int PrintTree();         // display the tree
};
