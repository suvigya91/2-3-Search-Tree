/*
Class 2-3 tree function definition
Written by Suvigya Tripathi,  4/4/2015
*/

#include"tree23.h"
#include<iostream>
#include<iomanip>
#include<vector>

using namespace std;


//create a new node
Node* tree23::init(int x){
	Node *node = new Node;
	node->leftData = x;
	node->value = 1;
	node->left = node->middle = node->right = node->parent = NULL;
	return node;
}

//print out a node's value(s)
void tree23::printNode(Node* n){
	if (n != NULL){  //print guard
		if (n->value == 1) cout << n->leftData << " ";
		else cout << n->leftData << " " << n->rightData << " ";
	}
}

//checks if a node is the leaf node
bool tree23::isLeaf(Node* n){
	return (n->left == NULL && n->right == NULL && n->middle == NULL);
}

//print all values in the tree form
int tree23::PrintTree(){
	int ht = -1;
	if (root == NULL) cout << "Empty is tree.";    

	else {

		vector<Node*> v;  //list to print
		vector<Node*> c;  //list to hold children of v, for later use
		v.push_back(root);  //first level
		while (!v.empty()){
			for (int i = 0; i< v.size(); i++){  //print all nodes
				cout << setw(3); printNode(v[i]); cout << ", ";
			}
			cout << endl;   //end this level
			for (int i = 0; i < v.size(); i++){ //find children of nodes in v
				if (v[i]->left) c.push_back(v[i]->left);
				if (v[i]->middle) c.push_back(v[i]->middle);
				if (v[i]->right) c.push_back(v[i]->right);
			}
			v.clear(); 
			v.swap(c); 
			c.clear();    
		}
	}
	cout << endl;
	return ht;
}

//output the inorder traversal of the tree. Prints in the form of left tree, parent node, middle tree, right tree
void tree23::doInorder(Node* n){
	if (root == NULL){  //print guard
		cout << "Empty tree." << endl;
	}
	else if (isLeaf(n)){    //the base case; if n is leaf
		printNode(n);
	}
	else {
		doInorder(n->left);  //inorder left child
		cout << n->leftData << " ";  //parent left data
		if (n->middle){
			doInorder(n->middle);    //inorder middle child
			cout << n->rightData << " "; //parent right data
		}
		doInorder(n->right); //inorder right child
	}
}

void tree23::Search(Node* a, int data){
	if (a == NULL){
		cout << "Element Not found";
	}
	else if (a->leftData == data || a->rightData == data){
		//return a;
		cout << "Element Found";
	}

	else if (a->leftData > data){
		Search(a->left, data);
	}

	else if (a->leftData < data && a->rightData > data){
		Search(a->middle, data);
	}
	else if (a->rightData < data){
		Search(a->right, data);
	}


}


//insert an item to the tree
void tree23::insert(int x){
	
	//corner case
	if (root == NULL){
		root = init(x);
	}

	else if (isLeaf(root)){
		if (root->value == 1){    //if it's a 2-node
			insertSecondItem(root, x);
		}
		else {    //it's a 3-node, split into two
			root = splitNode(root, init(x), 0);
			treeHeight++;
		}
	}

	else {
		helperFunc(root, x);
	}
}

//sort the three elements passed

int* tree23::promote(int m, int n, int x){
	int* middle = new int[3];
	if (x < m){ //m is the median
		middle[0] = x; middle[1] = m; middle[2] = n;
	}
	else if (x > n){  //n is the median
		middle[0] = m; middle[1] = n; middle[2] = x;
	}
	else{ //x is the median
		middle[0] = m; middle[1] = x; middle[2] = n;
	} return middle;
}

//split the node passed if it has 4 nodes
Node* tree23::splitNode(Node* n, Node* x, int pos){
	Node* nodeCache[4];    //cache children of nodes passed in
	//rearrange the position of these children for later hook up
	if (pos == 0){   //x left, x right, n middle, n right
		nodeCache[0] = x->left; nodeCache[1] = x->right;
		nodeCache[2] = n->middle; nodeCache[3] = n->right;
	}
	else if (pos == 2){   //n left, n middle, x left, x right
		nodeCache[0] = n->left; nodeCache[1] = n->middle;
		nodeCache[2] = x->left; nodeCache[3] = x->right;
	}
	else {    //n left, x left, x right, n right
		nodeCache[0] = n->left; nodeCache[1] = x->left;
		nodeCache[2] = x->right; nodeCache[3] = n->right;
	}
	int *middle = promote(n->leftData, n->rightData, x->leftData); //sort the passed nodes' values
	//reuse nodes to prevent memory leak
	Node* promo = init(middle[1]);   //new promoted node
	Node* l = init(middle[0]); //left child
	Node* r = init(middle[2]); //right child
	//parental relationship of first relative level
	promo->left = l; promo->right = r;
	l->parent = promo; r->parent = promo;
	//parental relationship of second relative level; hook up cached nodes
	if (nodeCache[0] != NULL){
		l->left = nodeCache[0]; l->right = nodeCache[1];
		nodeCache[0]->parent = nodeCache[1]->parent = l;
		r->left = nodeCache[2]; r->right = nodeCache[3];
		nodeCache[2]->parent = nodeCache[3]->parent = r;
	}
	return promo;
}

//insert a new item to a 2-node

void tree23::insertSecondItem(Node* n, int x){
	if (x < n->leftData){   //x should be on left
		n->rightData = n->leftData;
		n->leftData = x;
	}
	else {    //x should be on right
		n->rightData = x;
	} n->value = 2;
}

//check if the node is parent's left, middle or right child

int tree23::childPosition(Node*parento, Node*n){
	if (parento->left == n) return 0;    //if left child
	else if (parento->middle == n) return 1; //if middle child
	else return 2;  //if right child
}

//recursive helper function for insert()
void tree23::helperFunc(Node * n, int x){
	if (isLeaf(n)){ //base case; if n is a leaf
		if (n->value == 1){   //leaf has empty space
			insertSecondItem(n, x);
		}
		else {    //leaf is full; split it; promote the node to parent
			int pos = childPosition(n->parent, n);
			Node *promo = splitNode(n, init(x), pos);  //split the node
			while (n->parent != root){    //if parent is not root
				if (n->parent->value == 1){ //the parent is not full
					insertSecondItem(n->parent, promo->leftData);   //insert value to parent
					//rearrange leftover's linking
					int pos = childPosition(n->parent, n);
					if (pos == 0){ //if n is left child
						n->parent->left = promo->left;
						n->parent->middle = promo->right;
					}
					else if (pos == 2){   //if n is right child
						n->parent->middle = promo->left;
						n->parent->right = promo->right;
					}
					promo->left->parent = promo->right->parent = n->parent;
					break;  //insertion complete
				}
				else {    //continue to split parent's parent and so on
					pos = childPosition(n->parent, n);   //direction the split request comes from
					n = n->parent;  //go one level up
					promo = splitNode(n, promo, pos);   //split parent's parent
				}
			}
			if (n->parent == root){ //when trace to root
				pos = childPosition(n->parent, n);   //direction the split request comes from
				if (n->parent->value == 1){   //the root is not full
					insertSecondItem(n->parent, promo->leftData);
					if (pos == 0){ //if n is left child
						n->parent->left = promo->left;
						n->parent->middle = promo->right;
					}
					else if (pos == 2){   //if n is right child
						n->parent->middle = promo->left;
						n->parent->right = promo->right;
					}
					promo->left->parent = promo->right->parent = n->parent;
				}
				else {    //split the root
					pos = childPosition(n->parent, n);
					n = n->parent;
					root = splitNode(n, promo, pos);    //root will be updated
					treeHeight++;
				}
			}
		}
	}
	else {    //non-base case
		if (n->value == 1){   //2-node
			if (x < n->leftData) helperFunc(n->left, x);  //go left subtree
			else helperFunc(n->right, x);   //go right subtree
		}
		else {    //3-node
			if (x < n->leftData) helperFunc(n->left, x);  //go left subtree
			else if (x > n->rightData) helperFunc(n->right, x);  //go left subtree
			else helperFunc(n->middle, x);    //go middle subtree
		}
	}
}