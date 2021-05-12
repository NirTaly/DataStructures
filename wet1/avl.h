#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h>      /* size_t */
#include "exceptions.h"

namespace DS
{

	template <typename T>
	class AVL
	{
	public:
		AVL(): root(nullptr) {}
		~AVL();

		AVL(const AVL& ) = delete;
		AVL& operator=(const AVL& ) = delete;

		/*      
		* Return number of elements in AVL  
		* Complexity = O(n)
		*/
		size_t size() const;
		/*
		* Return boolean value is empty   
		* Complexity = O(1)
		*/
		bool isEmpty() const;

		/*
		* Insert element in AVL 
		* 0 on success (-1) on failure
		* Complexity = O(log(n))
		*/
		void insert(T *data);

		/*
		* Function Removes node that match operator==(node.data)
		* Function does not free user data
		* Complexity = O(log(n))
		*/
		void remove(T *data);
		
		/*
		* return the height of the AVL.
		* return 0 for empty AVL.
		* Complexity = O(1)
		*/
		size_t height() const;

		/*
		* Find function checks if <avl> includes <data>
		* Returns pointer to the data if found, NULL else.
		* if <data> == NULL, return NULL.
		* Complexity = O(log(n))
		*/
		T* find(T* data) const;  
		
		/*
		* return the first/last node by inorder
		* Returns pointer to the data if found, nullptr else.
		* if <data> == nullptr, return nullptr.
		* Complexity = O(log(n))
		*/
		T* getFirst() const;
		T* getLast() const;

		/*
		* Prints the AVL tree Inorder
		* Complexity = O(n)
		*/
		void print() const;

	private:
		struct AvlNode
		{	
			AvlNode() : height(0), left(nullptr), right(nullptr), parent(nullptr), data(nullptr) { }

			size_t height;
			AvlNode* left;
			AvlNode* right;
			AvlNode* parent; //#PC
			T* data;
		};

		void RecDestroyAVL(AvlNode* node);
		const size_t RecSize(AvlNode* node);

		AvlNode* root;
	};


/*******************************************************************************/
/*******************************************************************************/
	template <typename T>
	AVL<T>~AVL()
	{
		if (!isEmpty())
		{
			DestroyAVL(root);
		}
	}
	
	template <typename T>
	void RecDestroyAVL(AvlNode* node)
	{
		if (node)
		{	
			DestroyAVL(node->left);
			DestroyAVL(node->right);

			delete node->data;
			node->left = nullptr;
			node->right = nullptr;
			node->parent = nullptr;
		}
	}
/*******************************************************************************/
	
	template <typename T>
	bool AVL<T>::isEmpty() const
	{
		if(root == nullptr)
			return true;
			
		return false;
	}
/*******************************************************************************/

	template <typename T>
	size_t AVL<T>::size() const
	{
		if (isEmpty())
		{
			return 0;
		}
		
		return RecSize(root);
	}

	template <typename T>
	const size_t RecSize(AvlNode* node)
	{
		if (node == nullptr)
		{
			return (0);	
		}

		return (1 + RecSize(node->left) + RecSize(node->right));
	}
/*******************************************************************************/
	
	template <typename T>
	size_t AVL<T>::height() const
	{
		if (isEmpty())
		{
			return 0;
		}

		return root->height;
	}
/*******************************************************************************/

	template <typename T>
	bool AVL<T>::find(T* data) const
	{
		if(isEmpty())
		{	 
			throw AVLEmpty();
		}

		RecFind(root);
	}

	template <typename T>
	const bool RecFind(AvlNode* node, T* data)
	{
		if (node == nullptr)
		{
			return (false);	
		}

		bool left_tree = false;
		bool right_tree = false;

		if (*(node->data) == *data)
		{
			return true;
		}

		else if (*(node->data) < *data)
		{
			left_tree = RecFind(node->left);
		}
		else
		{
			right_tree = RecFind(node->right);
		}

		return (left_tree || right_tree);
	}
/*******************************************************************************/
	
	template <typename T>
	T* AVL<T>::getFirst() const
	{
		if (node == nullptr)
		{
			return (false);	
		}
		
		AvlNode* runner = root;
		while (runner->left)
		{
			runner = runner->left;
		}
		
		return runner->data;
	}

	template <typename T>
	T* AVL<T>::getLast() const
	{
		if (node == nullptr)
		{
			return (false);	
		}
		
		AvlNode* runner = root;
		while(runner->right)
		{
			runner = runner -> right;
		}	
		return runner->data;
	}
/*******************************************************************************/
	
} // namespace DS


#endif     /* __AVL_TREE_H__ */

