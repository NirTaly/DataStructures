#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h>      /* size_t */
#include "exceptions.h"

template <typename T>
T MAX(T a, T b)
{
	return (a > b ? a : b);
}

namespace DS
{

	template <typename T>
	class AVL
	{
	public:
		AVL(): m_root(nullptr) {}
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
		bool find(T* data) const;
		
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
			AvlNode(size_t height = 1,AvlNode* l = nullptr,AvlNode* r = nullptr,AvlNode* p = nullptr,T* data = nullptr) : 
				height(height), left(l), right(r), parent(p), data(data) { }

			size_t height;
			AvlNode* left;
			AvlNode* right;
			AvlNode* parent;
			T* data;
		};

		void RecDestroyAVL(AvlNode* node);
		size_t RecSize(AvlNode* node);
		AvlNode* InsertRec(typename AVL<T>::AvlNode* node, T* data);
		size_t NodeHeight(typename AVL<T>::AvlNode* node);
		int BalanceFactor(typename AVL<T>::AvlNode* node);
		AVL<T>::AvlNode* LRotate(AvlNode* node);
		AVL<T>::AvlNode* RRotate(AvlNode* node);
		AvlNode* RightMostNode(AvlNode* node);
		AvlNode* LeftMostNode(AvlNode* node);
		
		AvlNode* m_root;
	};


/*******************************************************************************/
/*******************************************************************************/
	template <typename T>
	AVL<T>::~AVL()
	{
		if (!isEmpty())
		{
			DestroyAVL(m_root);
		}
	} 
	
	template <typename T>
	void RecDestroyAVL(typename AVL<T>::AvlNode* node)
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
		if(m_root == nullptr)
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
		
		return RecSize(m_root);
	}

	template <typename T>
	size_t RecSize(typename AVL<T>::AvlNode* node)
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

		return m_root->height;
	}
/*******************************************************************************/

	template <typename T>
	bool AVL<T>::find(T* data) const
	{
		if(isEmpty())
		{	 
			throw AVLEmpty();
		}

		RecFind(m_root);
	}

	template <typename T>
	bool RecFind(typename AVL<T>::AvlNode* node, T* data)
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
		if (m_root == nullptr)
		{
			return (nullptr);	
		}
		
		return LeftMostNode(m_root);
	}

	template <typename T>
	T* AVL<T>::getLast() const
	{
		if (m_root == nullptr)
		{
			return (nullptr);	
		}
		
		return RightMostNode(m_root);
	}

/*******************************************************************************/
	template <typename T>
	void AVL<T>::insert(T *data)
	{
		if(isEmpty())
		{	 
			m_root = new AvlNode(0,nullptr,nullptr,nullptr,data);
			if (!m_root)
			{
				throw std::bad_alloc();
			}
		}

		m_root = InsertRec(m_root, data);
	}

	template <typename T>
	typename AVL<T>::AvlNode* InsertRec(typename AVL<T>::AvlNode* node, T* data)
	{
		/* insert to the right place */
		bool left_son = *(data) < *(node->data);
		bool right_son = *(data) > *(node->data);

		if ((right_son && node->right == nullptr) || 
			(left_son && node->left == nullptr))
		{
			typename AVL<T>::AvlNode* tmp = new typename AVL<T>::AvlNode(0,nullptr,nullptr,nullptr,data);
			if (!tmp)
			{
				throw std::bad_alloc();
			}

			if (right_son)
			{
				node->right = tmp;
				tmp->parent = node;
			}
			else
			{
				node->left = tmp;
				tmp->parent = node;
			}			
		}

		/* moving to the correct son */
		else if (right_son)
		{
			InsertRec(node->right, data);
		}
		else if (left_son)
		{
			InsertRec(node->left, data);
		}
		/*	Duplicate nodes are not allowed */
		else
		{
			throw AVLDuplicate();
		}

		/* height update */
		node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));
		
		/* balancing */
		return AVLBalance(node);
	}

	template <typename T>
	typename AVL<T>::AvlNode* AVLBalance(typename AVL<T>::AvlNode* node)
	{
		int balance_fac = BalanceFactor(node);
		
		if (balance_fac > 1)
		{
			if (BalanceFactor(node->right) < 0)
			{
				node->right = RRotate(node->right);
			}
			
			return (LRotate(node));
		}

		else if (balance_fac < -1)
		{
			if (BalanceFactor(node->left) > 0)
			{
				node->left = LRotate(node->left);
			}
			
			return (RRotate(node));
		}

		return (node);
	}

	template <typename T>
	typename AVL<T>::AvlNode* RRotate(typename AVL<T>::AvlNode* node)
	{
		typename AVL<T>::AvlNode* new_head = node->left;

		node->left = new_head->right;
		new_head->right->parent = node->parent;

		new_head->right = node;
		node->parent = new_head;

		node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));
		new_head->height = 1 + MAX(NodeHeight(new_head->left), NodeHeight(new_head->right));

		return (new_head);
	}

	template <typename T>
	typename AVL<T>::AvlNode* LRotate(typename AVL<T>::AvlNode* node)
	{
		typename AVL<T>::AvlNode* new_head = node->right;
		
		node->right = new_head->left;
		new_head->left->parent = node->right;

		new_head->left = node;
		node->parent = new_head;

		node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));
		new_head->height = 1 + MAX(NodeHeight(new_head->left), NodeHeight(new_head->right));

		return (new_head);
	}
	template <typename T>
	int BalanceFactor(typename AVL<T>::AvlNode* node)
	{
		return (NodeHeight(node->right) - NodeHeight(node->left));
	}
	
	template <typename T>
	size_t NodeHeight(typename AVL<T>::AvlNode* node)
	{
		if (node)
		{
			return (node->height);
		}

		return (0);
	}
/*******************************************************************************/
	void remove(T *data)
	{
		m_root = RemoveRec(m_root, data);
	}	

	template <typename T>
	typename AVL<T>::AvlNode* RemoveRec(typename AVL<T>::AvlNode* node, T* data)
	{	
		bool left_son = *(data) < *(node->data);
		bool right_son = *(data) > *(node->data);

		/* moving to the correct son */
		if (right_son)
		{
			node->right = RemoveRec(node->right, data);
		}
		else if (left_son)
		{
			node->left = RemoveRec(node->left, data);
		}
		else
		{
			/* one son or no sons */	
			if (!node->left || !node->right)
			{
				replacer = (node->left) ? (node->left) : (node->right);
				/* one son */
				if (replacer)
				{
					node->data = replacer->data;
					if (replacer == node->left)
					{
						node->left = nullptr; 
					}
					else
					{
						node->right = nullptr;
					}

					delete replacer;
					replacer = nullptr;
				}
				/* no sons */
				else
				{
					delete node;
					node = nullptr;
				}
			}
			/* two sons */
			else
			{
				replacer = RightMostNode(node->left);

				node->data = replacer->data;
				node->left = RemoveRec(node->left, node->data);
			}

		}
	}



	template <typename T>
	typename AVL<T>::AvlNode* RightMostNode(typename AVL<T>::AvlNode* node)
	{
		while (node->right)
		{
			node = node->right;
		}

		return (node);
	}
	
	template <typename T>
	typename AVL<T>::AvlNode* LeftMostNode(typename AVL<T>::AvlNode* node)
	{
		while (node->left)
		{
			node = node->left;
		}

		return (node);
	}
} // namespace DS


#endif     /* __AVL_TREE_H__ */

