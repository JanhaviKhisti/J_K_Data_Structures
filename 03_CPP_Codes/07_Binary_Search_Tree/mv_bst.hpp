
#pragma once

// Headers
#include <iostream>

#ifndef  	SUCCESS
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

// Class Node
template <typename Node_T>
class Node
{
private:
	Node_T m_data;
	Node* 	m_left;
	Node* 	m_right;
	Node*  	m_parent;

	Node() : m_data((Node_T)0), m_left(nullptr), m_right(nullptr), m_parent(nullptr)
	{
		// Code
	}

	Node(Node_T initData) : m_data(initData), m_left(nullptr), m_right(nullptr), m_parent(nullptr)
	{
		// Code
	}

	~Node()
	{
		m_left = nullptr;
		m_right = nullptr;
		m_parent = nullptr;
	}

	template <typename Tree_T>
	friend class BST_Tree;
};

template <typename Tree_T>
class BST_Tree
{
private:
	typedef int ret_t;

	Node<Tree_T>* 	m_root;
	size_t  		m_size;

	ret_t 	GenericInsert(Tree_T new_data)
	{
		Node<Tree_T>* prunner = m_root;

		while(true)
		{
			if(prunner->m_data == new_data)
			{
				std::cerr << "Data Already Present." << std::endl;
				return(FAILURE);
			}
			else if(new_data < prunner->m_data)
			{
				if(nullptr == prunner->m_left)
				{
					prunner->m_left = new Node<Tree_T>(new_data);
					prunner->m_left->m_parent = prunner;
					break;
				}
				prunner = prunner->m_left;
			}
			else
			{
				if(nullptr == prunner->m_right)
				{
					prunner->m_right = new Node<Tree_T>(new_data);
					prunner->m_right->m_parent = prunner;
					break;
				}
				prunner = prunner->m_right;
			}
		}

		m_size++;

		return(SUCCESS);
	}

	Node<Tree_T>* Successor(Node<Tree_T>* node)
	{
		// Code
		Node<Tree_T>* prunner = node->m_right;

		while(prunner->m_left)
			prunner = prunner->m_left;

		return(prunner);
	}

	Node<Tree_T>* Predecessor(Node<Tree_T>* node)
	{
		// Code
		Node<Tree_T>* prunner = node->m_left;

		while(prunner->m_right)
			prunner = prunner->m_right;

		return(prunner);
	}

	Tree_T 	GenericRemove(Tree_T e_data)
	{
		// Code
		Node<Tree_T>* prunner = m_root;
		Tree_T to_return_data = (Tree_T)0;

		while(prunner)
		{
			if(e_data == prunner->m_data)
				break;
			else if(e_data < prunner->m_data)
				prunner = prunner->m_left;
			else
				prunner = prunner->m_right;
		}

		if(nullptr == prunner)
			return((Tree_T)0);

		// Case 1: Both Children not present
		if( nullptr == prunner->m_left &&
			nullptr == prunner->m_right)
			to_return_data = prunner->m_data;

		// Case 2 : Left Child Present
		if( nullptr != prunner->m_left)
		{
			Node<Tree_T>* predecessor = Predecessor(prunner);

			to_return_data = prunner->m_data;
			prunner->m_data = predecessor->m_data;

			prunner = predecessor;
		}

		// Case 3 : Right Child Present
		if(nullptr != prunner->m_right)
		{
			Node<Tree_T>* successor = Successor(prunner);

			to_return_data = prunner->m_data;
			prunner->m_data = successor->m_data;

			prunner = successor;
		}

		if(nullptr == prunner->m_parent)
		{
			m_root = nullptr;
		}
		else if( prunner == prunner->m_parent->m_left)
		{
			if(prunner->m_right)
			{
				prunner->m_parent->m_left = prunner->m_right;
			}
			else
			{
				prunner->m_parent->m_left = prunner->m_left;
			}
		}
		else
		{
			if(prunner->m_left)
			{
				prunner->m_parent->m_right = prunner->m_left;
			}
			else
			{
				prunner->m_parent->m_right = prunner->m_right;
			}
		}

		// Check for left child or right child
		if(prunner->m_left)
			prunner->m_left->m_parent = prunner->m_parent;
		else if(prunner->m_right)
			prunner->m_right->m_parent = prunner->m_parent;

		Node<Tree_T>* temp = prunner->m_parent;

		if(prunner)
		{
			delete(prunner);
			prunner = nullptr;
		}

		prunner = temp;

		m_size--;

		return(to_return_data);
	}

	void InorderRecusive(Node<Tree_T>* node)
	{
		if(node->m_left)
			InorderRecusive(node->m_left);

		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "}->";

		if(node->m_right)
			InorderRecusive(node->m_right);
	}

	void  	PreorderRecursive(Node<Tree_T>* node)
	{
		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "}->";

		if(node->m_left)
			PreorderRecursive(node->m_left);

		if(node->m_right)
			PreorderRecursive(node->m_right);

	}

	void PostorderRecursive(Node<Tree_T>* node)
	{
		if(node->m_left)
			PostorderRecursive(node->m_left);

		if(node->m_right)
			PostorderRecursive(node->m_right);

		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "}->";
	}

	void PostorderDestroy(Node<Tree_T>* node)
	{
		if(node->m_left)
			PostorderDestroy(node->m_left);

		if(node->m_right)
			PostorderDestroy(node->m_right);

		std::cout << "Deleting : ";
		std::cout << node->m_data;
		std::cout << std::endl;

		if(node)
		{
			delete(node);
			node = nullptr;
		}
	}

	void  	InorderIterative(Node<Tree_T>* node);
	void  	PreorderIterative(Node<Tree_T>* node);
	void  	PostorderIterative(Node<Tree_T>* node);

public:
	// Default Constructor
	BST_Tree() : m_root(nullptr), m_size(0)
	{
		// Code
	}

	~BST_Tree()
	{
		if(root)
		{
			PostorderDestroy(m_root);
			m_root = nullptr;
		}

		m_size = 0;
	}

	ret_t Insert(Tree_T new_data)
	{
		if(nullptr == m_root)
		{
			m_root = new Node<Tree_T>(new_data);
		}
		else
		{
			return( GenericInsert(new_data) );
		}

		return(SUCCESS);
	}

	Tree_T Remove(Tree_T e_data)
	{
		if(nullptr == m_root)
		{
			std::cerr << "ERROR: Tree Not Found." << std::endl;
			return((Tree_T)0);
		}
		else
		{
			return( GenericRemove(e_data) );
		}
	}

	void Inorder()
	{
		// Code
		if(nullptr == m_root)
		{
			std::cerr << "ERROR: Tree Not Found." << std::endl;
			return;
		}

		std::cout << "Inorder Recursive Traversal : " << std::endl;
		std::cout << "{START}->";
		InorderRecusive(m_root);
		std::cout << "{END}";
	}

	void 	Preorder()
	{
		// Code
		if(nullptr == m_root)
		{
			std::cerr << "ERROR: Tree Not Found." << std::endl;
			return;
		}

		std::cout << "Preorder Recursive Traversal : " << std::endl;
		std::cout << "{START}->";
		PreorderRecursive(m_root);
		std::cout << "{END}";
	}

	void  	Postorder()
	{
		// Code
		if(nullptr == m_root)
		{
			std::cerr << "ERROR : Tree Not Found." << std::endl;
			return;
		}

		std::cout << "Postorder Recursive Traversal : " << std::endl;
		std::cout << "{START}->";
		PostorderRecursive(m_root);
		std::cout << "{END}";
	}

};


