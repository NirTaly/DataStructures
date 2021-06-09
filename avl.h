#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <stddef.h>      /* size_t */
#include "exceptions.h"

template <typename T>
T Max(T a, T b)
{
	return (a > b ? a : b);
}


/***
 * num of sons									[V]
 * Build recursive tree from merged array		[]
 * Get item number i							[]
*/


namespace DS
{
	template <typename T>
	class AVL
	{
	struct AvlNode; // declaration

	public:
		AVL(): m_root(nullptr), m_start(nullptr), m_end(nullptr), m_iter(nullptr) { }
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
		T* findData(T* data);
		T* findNext(T* data);

		/*
		* return the first/last node by inorder
		* Returns pointer to the data if found, nullptr else.
		* if <data> == nullptr, return nullptr.
		* Complexity = O(log(n))
		*/
		T* getFirst() const;
		T* getLast() const;
		
		/* iterate in O(1) for every func */
		T* AVLBegin();
		T* AVLNext();
		T* AVLEnd();
		
		/*
		* Travel inorder, and put the first i nodes in arr
		* Complexity = O(i)
		 */
		void inorder(size_t i, T** arr);
		
		void buildFromArray(T* array, int size);
		T getIRank(int i);

		/*
		* Prints the AVL tree Inorder
		* Complexity = O(n)
		*/
		void print() const;

	private:
	// AVL Node Structure
		struct AvlNode
		{	
			AvlNode(T* data, size_t height = 1, AvlNode* l = nullptr,AvlNode* r = nullptr,AvlNode* p = nullptr) : 
				data(new T(*data)), height(height), left(l), right(r), parent(p), left_sons(0), right_sons(0)
			{ }
			
			~AvlNode() { delete data; left = nullptr; right = nullptr; parent = nullptr;}

			T* data;
			size_t height; 
			AvlNode* left;
			AvlNode* right;
			AvlNode* parent;
			size_t left_sons;//rank
			size_t right_sons;//rank
		};
		
	// Aux Functions
		void RecDestroyAVL(AvlNode* node);
		size_t RecSize(AvlNode* node) const;
		AvlNode* RecFind(AvlNode* node, T* data);
		AvlNode* InsertRec(AvlNode* node, T* data);
		size_t NodeHeight(AvlNode* node) const;
		int BalanceFactor(AvlNode* node) const;
		AvlNode* AVLBalance(AvlNode* node);
		AvlNode* LRotate(AvlNode* node);
		AvlNode* RRotate(AvlNode* node);
		AvlNode* RightMostNode(AvlNode* node);
		AvlNode* LeftMostNode(AvlNode* node);
		AvlNode* RemoveRec(AvlNode* node, T* data);
		AvlNode* GetNode(T* data);
		AvlNode* AVLNext(AvlNode* node);
		T* GetNextData(AvlNode* node);
		AvlNode* buildRec(T* array, int start, int end);
		T RecGetI(AvlNode* node,int i);
		void  AVLPrintNode(AvlNode* node, size_t depth) const;

	// Private member
		AvlNode* m_root;
		AvlNode* m_start;
		AvlNode* m_end;
		AvlNode* m_iter;
	};


/*******************************************************************************/
/*******************************************************************************/
	template <typename T>
	AVL<T>::~AVL()
	{
		if (!isEmpty())
		{
			RecDestroyAVL(m_root);
		}
	} 
	
	template <typename T>
	void AVL<T>::RecDestroyAVL(AvlNode* node)
	{
		if (node)
		{	
			RecDestroyAVL(node->left);
			RecDestroyAVL(node->right);

			delete node;
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
	size_t AVL<T>::RecSize(AvlNode* node) const
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
	T* AVL<T>::findData(T* data)
	{
		if(isEmpty())
		{	 
			throw AVLEmpty();
		}

		AvlNode* found = RecFind(m_root, data);
		if (!found)
		{
			throw AVLNotFound();
		}

		return (found->data);
	}
	
	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::RecFind(AvlNode* node, T* data)
	{
		if (node == nullptr)
		{
			return (nullptr);	
		}

		if (*(node->data) == *data)
		{
			return node;
		}

		else if (*(node->data) > *data)
		{
			return RecFind(node->left, data);
		}
		else
		{
			return RecFind(node->right, data);
		}
	}
/*******************************************************************************/
	
	template <typename T>
	T* AVL<T>::getFirst() const
	{
		if (m_root == nullptr)
		{
			throw AVLEmpty();
		}

		return m_start->data;
	}

	template <typename T>
	T* AVL<T>::getLast() const
	{
		if (m_root == nullptr)
		{
			throw AVLEmpty();
		}
		
		return m_end->data;
	}

/*******************************************************************************/
	template <typename T>
	void AVL<T>::insert(T* data)
	{
		if(isEmpty())
		{	 
			m_root = new AvlNode(data);
			m_start = m_root;
			m_end = m_root;
			
			return;
		}

		m_root = InsertRec(m_root, data);
		m_start = LeftMostNode(m_root);
		m_end = RightMostNode(m_root);
	}

	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::InsertRec(AvlNode* node, T* data)
	{
		/* insert to the right place */
		bool is_left_son = *(data) < *(node->data);
		bool is_right_son = *(data) > *(node->data);

		if ((is_right_son && node->right == nullptr) || 
			(is_left_son && node->left == nullptr))
		{
			AvlNode* tmp = new AvlNode(data);

			if (is_right_son)
			{
				node->right = tmp;
				tmp->parent = node;
				node->right_sons++;
			}
			else
			{
				node->left = tmp;
				tmp->parent = node;
				node->left_sons++;
			}			
		}

		/* moving to the correct son */
		else if (is_right_son)
		{
			node->right = InsertRec(node->right, data);
			node->right_sons++;
		}
		else if (is_left_son)
		{
			node->left = InsertRec(node->left, data);
			node->left_sons++;
		}
		/*	Duplicate nodes are not allowed */
		else
		{
			throw AVLDuplicate();
		}
		
		/* height update */
		node->height = 1 + Max(NodeHeight(node->left), NodeHeight(node->right));
		
		/* balancing */
		node = AVLBalance(node);

		return node;
	}

	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::AVLBalance(AvlNode* node)
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
	typename AVL<T>::AvlNode* AVL<T>::RRotate(AvlNode* node)
	{
		AvlNode* new_head = node->left;

		node->left = new_head->right;
		new_head->right = node;


		//rank control
		node->left_sons = new_head->right_sons;
		new_head->right_sons += node->right_sons + 1;
		//
		
		if (node->left)
		{
			node->left->parent = node;
		}

		new_head->parent = node->parent;
		node->parent = new_head;

		node->height = 1 + Max(NodeHeight(node->left), NodeHeight(node->right));
		new_head->height = 1 + Max(NodeHeight(new_head->left), NodeHeight(new_head->right));

		return (new_head);
	}

	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::LRotate(AvlNode* node)
	{
		AvlNode* new_head = node->right;
		
		node->right = new_head->left;
		new_head->left = node;

		//rank control
		node->right_sons = new_head->left_sons;
		new_head->left_sons += node->left_sons + 1;
		//
		
		if (node->right)
		{
			node->right->parent = node;
		}

		new_head->parent = node->parent;
		node->parent = new_head;

		node->height = 1 + Max(NodeHeight(node->left), NodeHeight(node->right));
		new_head->height = 1 + Max(NodeHeight(new_head->left), NodeHeight(new_head->right));

		return (new_head);
	}
	template <typename T>
	int AVL<T>::BalanceFactor(AvlNode* node) const
	{
		return (NodeHeight(node->right) - NodeHeight(node->left));
	}
	
	template <typename T>
	size_t AVL<T>::NodeHeight(AvlNode* node) const
	{
		if (node)
		{
			return (node->height);
		}

		return (0);
	}
/*******************************************************************************/
	template <typename T>
	void AVL<T>::remove(T *data)
	{
		if (isEmpty())
		{
			throw AVLEmpty();
		}
		
		m_root = RemoveRec(m_root, data);

		m_start = LeftMostNode(m_root);
		m_end = RightMostNode(m_root);
	}	

	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::RemoveRec(AvlNode* node, T* data)
	{	
		if (nullptr == node)
		{
			throw AVLNotFound();
		}
	
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
			AVL<T>::AvlNode* replacer = nullptr;
			
			/* one son or no sons */	
			if (!node->left || !node->right)
			{
				replacer = (node->left) ? (node->left) : (node->right);
				/* one son */
				if (replacer)
				{														
					delete (node->data);
					node->data = new T(*(replacer->data));

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
					return node;
				}
			}
			/* two sons */
			else
			{
				replacer = RightMostNode(node->left);

				delete (node->data);
				node->data = new T(*(replacer->data));
				node->left = RemoveRec(node->left, node->data);
			}
		}

		/* Height Update */
		node->height = 1 + Max(NodeHeight(node->left), NodeHeight(node->right));

		/* balancing */
		node = AVLBalance(node);

		return (node);
	}

/*******************************************************************************/


	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::RightMostNode(AvlNode* node)
	{
		if (node)
		{
			while (node->right)
			{
				node = node->right;
			}
		}

		return (node);
	}
	
	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::LeftMostNode(AvlNode* node)
	{
		if (node)
		{
			while (node->left)
			{
				node = node->left;
			}
		}

		return (node);
	}
/*******************************************************************************/
	template <typename T>
	T* AVL<T>::AVLBegin()
	{
		m_iter = m_start;
		return m_iter->data;
	}
	
	template <typename T>
	typename AVL<T>::AvlNode* AVL<T>::AVLNext(AvlNode* node)
	{
		if (node == m_end)
		{
			return nullptr;
		}
		
		if (node->right)
		{
			node = node->right;

			return LeftMostNode(node);
		}

		while (node->parent != nullptr &&
			node->parent->right  &&
			node == node->parent->right)
		{
			node = node->parent;
		}

		return node->parent;
	}
	template <typename T>
	T* AVL<T>::AVLNext()
	{
		m_iter = AVLNext(m_iter);
		if (m_iter == nullptr)
		{
			return nullptr;
		}
		
		return m_iter->data;
	}

	template <typename T>
	T* AVL<T>::AVLEnd()
	{
		return m_end->data;
	}

	template <typename T>
	void AVL<T>::inorder(size_t i, T** arr)
	{
		size_t counter = 0;
		
		for (m_iter = m_start; m_iter && counter < i; m_iter = AVLNext(m_iter))
		{
			arr[counter++] = m_iter->data;
		}

		if (m_iter == m_end && i > counter)
		{
			throw Failure();
		}
	}

	template <typename T>
	T* AVL<T>::findNext(T* data)
	{
		AvlNode* node = RecFind(m_root, data);
		if (!node)
		{
			throw AVLNotFound();
		}
		
		AvlNode* next = AVLNext(node);
		if (!next)
		{
			throw AVLNextNotFound();
		}

		return next->data;
	}
	
/*******************************************************************************/

template <typename T>
void AVL<T>::buildFromArray(T* array, int size)
{
    m_root = buildRec(array, 0, size-1);
	m_start = LeftMostNode(m_root);
	m_end = RightMostNode(m_root);
}

template <typename T>
typename AVL<T>::AvlNode* AVL<T>::buildRec(T* array, int start, int end)
{
	if (start > end) 
	{
		return nullptr;
	}
    	
    int mid = (start + end)/2;
	
    AvlNode* node = new AvlNode(&array[mid]);
  
    node->left = buildRec(array, start, mid - 1); 
  
    node->right = buildRec(array, mid + 1, end); 
  
	/* Parent, NumOfSons Update*/
	if (node->right)
	{
		node->right->parent = node;
		node->right_sons = node->right->right_sons + node->right->left_sons + 1;
	}
	if (node->left)
	{
		node->left->parent = node;
		node->left_sons = node->left->right_sons + node->left->left_sons + 1;
	}
	
	/* Height Update */
	node->height = 1 + Max(NodeHeight(node->left), NodeHeight(node->right));

    return node; 
}

/*******************************************************************************/

	template <typename T>
	T AVL<T>::getIRank(int i)
	{
		if (isEmpty())
		{
			throw AVLEmpty();
		}
		else if (i < 0 || i > int(size()))
		{
			throw Failure();
		}
		
		return RecGetI(m_root, i);
	}

	template <typename T>
	T AVL<T>::RecGetI(AvlNode* node, int i)
	{
		int choice = node->left_sons - i;
		if (choice == 0)
		{
			return *(node->data);
		}
		else if (choice > 0)
		{
			return RecGetI(node->left, i);
		}
		else
		{
			return RecGetI(node->right, i - node->left_sons - 1);
		}
	}
/*******************************************************************************/
	template <typename T>
	void  AVL<T>::AVLPrintNode(AvlNode* node, size_t depth) const
	{
		size_t i = 0;
		for (i = 0; i < depth; ++i)
		{
			std::cout << "│  ";
		}
		if (nullptr != node)
		{
			std::cout << "├╴ " << *(node->data) << " left: " << node->left_sons << " right: " << node->right_sons << std::endl;
			AVLPrintNode(node->left, depth + 1);
			AVLPrintNode(node->right, depth + 1);
		} else {
			std::cout << "├╴ X" << std::endl;
		}
	}

	template <typename T>
	void AVL<T>::print() const
	{
		if (nullptr != m_root)
		{
			std::cout << "\nStart Print:" << std::endl;
			std::cout << "├╴ " << *(m_root->data) << " left: " << m_root->left_sons << " right: " << m_root->right_sons << std::endl;

			AVLPrintNode(m_root->left, 1);
			AVLPrintNode(m_root->right, 1);
		}
	}

} // namespace DS


#endif     /* __AVL_TREE_H__ */

