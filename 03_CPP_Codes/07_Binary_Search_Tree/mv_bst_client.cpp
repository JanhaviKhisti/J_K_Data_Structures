
// Headers
#include 	<iostream>

#include "mv_bst.hpp"

int main(int argc, char** argv, char** envp)
{
	// Code
	BST_Tree<long long>* tree = new BST_Tree<long long>();

	for(int le = 0; le < 10; le++)
		tree->Insert( (le+1) * 10);

	tree->Inorder();
	std::cout << std::endl;
	tree->Preorder();
	std::cout << std::endl;
	tree->Postorder();
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Removed Data : " << tree->Remove(50);
	std::cout << std::endl << std::endl;

	tree->Inorder();
	std::cout << std::endl;
	tree->Preorder();
	std::cout << std::endl;
	tree->Postorder();
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}


