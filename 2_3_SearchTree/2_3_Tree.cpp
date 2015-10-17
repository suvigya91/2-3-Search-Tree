/*
2-3 Tree Symbol Table API which has following functions:

insert(key)  //inserts key in the table
PrintTree()  //prints tree
search(key)  //searches key in the tree
treeHeight   //variable to display height
inorder()    //inorder traversal
**********************************************************************************
Include the following files in the project before executing:
tree23.h
tree23.cpp
2_3_Tree.cpp

To excute this code, please enter in following format on the command prompt
	2_3_SearchTree.exe <input_file_path>
eg:
	2_3_SearchTree.exe C:\Acads\Sem_2\DSA\dataset-problem2-hw2\data1.1024
*/

#include<string>
#include "tree23.h"
#include<fstream>



int main(int argc, char** argv) {
	ifstream ffile; //creating file pointer
	string firstFile = argv[1];
	ffile.open(firstFile, ios::in);
	
	if (!ffile.is_open()){
		cout << "file not opened\n";
	}

	else{
		int str;
		tree23 t23;

		//2-3 tree construction
		cout << "Tree construction started....!!!\n";
		while (ffile >> str)
		{
			t23.insert(str);
		}

		cout << "Tree constructed....!!!\n";
		int in;
		cout << "Select\n 1. Print tree\n 2. Inorder traversal\n 3. Height of Tree\n 4. Search\n 5. Quit\n";
		while (cin >> in){
			switch (in){
			case 1:
				cout << "\n";
				t23.PrintTree();
				break;

			case 2:
				cout << "\n";
				t23.inorder();
				break;

			case 3:
				cout << "\n";
				cout << "height: " << t23.treeHeight << "\n";
				break;
			case 4:
				cout << "\n";
				int p;
				cout << "Enter number to be searched: ";
				cin >> p;
				cout << "\n";
				t23.search1(p);
				break;

			case 5:
				return 0;
			default:
				cout << "\nError Input";
			}
		}
	}
	return 0;
}