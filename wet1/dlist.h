/******************************************************************************
                                Double Linked List
                               Nir Tali Roee Latzres
                                    19.5.21
 *****************************************************************************/
#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__

#include <stddef.h>      /* size_t */
#include <iostream>      // size_t

using std::size_t;

namespace DS
{
    template <class T>
    class DList
    {
    public:
		struct DListNode
        {
			DListNode(T* data = nullptr, DListNode* prev = nullptr ,DListNode* next = nullptr) : 
				m_data(nullptr), m_prev(prev), m_next(next) 
            { 
                if (data)
                {
                    m_data = new T(*data);
                }
            }
			
			~DListNode() 
            { 
                if (m_data)
                {
                    delete m_data; 
                }
                m_next = nullptr; 
                m_prev = nullptr; 
            }

            T* m_data;
            DListNode* m_prev;
            DListNode* m_next;
        };

        DList();
        ~DList();

        DList(const DList& d);
        DList& operator=(const DList& rhs) = delete; 

        void pop(void);
        void remove(DListNode* node);

        // if curr == nullptr -> insert to the end of the list
        DListNode* pushAfter(T* const data, DListNode* curr = nullptr);
		// if curr == nullptr -> insert to the start of the list
        DListNode* pushBefore(T* const data, DListNode* curr = nullptr);

        size_t size(void) const;

        bool isEmpty(void) const;

        DListNode* begin();
        DListNode* end();
        void print();
    private: 
    
        DListNode m_start;
        DListNode m_end;
    };

    template <class T>
    DList<T>::DList()
	{ 
		m_start.m_next = &m_end;
		m_start.m_prev = nullptr;

		m_end.m_prev = &m_start;
		m_end.m_next = nullptr;
	}
    
    template <class T>
    DList<T>::~DList(void)
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    template <class T>
    DList<T>::DList(const DList<T>& list)
    {
        m_start.m_next = &m_end;
		m_start.m_prev = nullptr;
		m_end.m_prev = &m_start;
		m_end.m_next = nullptr;

        DListNode* runner = list.begin();
        DListNode* new_runner = &m_start;

        while (runner != list.m_end)
        {
            new_runner = pushAfter(runner->data,new_runner);
            runner = runner->m_next;
        }
    }

    template <class T>
    bool DList<T>::isEmpty(void) const
    {
        return (&m_end == m_start.m_next);
    }

    template <class T>
    size_t DList<T>::size(void) const
    {
        size_t counter = 0;

        DListNode* iter = m_start.m_next;
        while (iter != &m_end)
        {
            counter++;   
            iter = iter->m_next;
        }

        return (counter);
    }


    template <class T>
	typename DList<T>::DListNode* DList<T>::pushAfter(T* const data, DListNode* curr)
    {
        DListNode* new_node = nullptr;
        if(!curr)
        {
            new_node = new DListNode(data, m_end.m_prev, m_end);
			m_end.m_prev->m_next = new_node;
            m_end.m_prev = new_node;
        }
        else
        {
            new_node = new DListNode(data, curr, curr->m_next);
            curr->m_next->m_prev = new_node;
            curr->m_next = new_node;
        }

        return new_node;

    }

	template <class T>
	typename DList<T>::DListNode* DList<T>::pushBefore(T* const data, DListNode* curr)
	{
		DListNode* new_node = nullptr;
		
		if (!curr)
		{
			new_node = new DListNode(data,  &m_start,  m_start.m_next);
			m_start.m_next->m_prev = new_node;
			m_start.m_next = new_node;
		}
		else
		{
			new_node = new DListNode(data, curr->m_prev, curr);
			curr->m_prev->m_next = new_node;
			curr->m_prev = new_node;
		}
		
		return new_node;
	}

    template <class T>
    void DList<T>::pop(void)
    {
        DListNode* deleted_node = m_start.m_next; 

        if (deleted_node != &m_end)
        {
            m_start.m_next = deleted_node->m_next;
			deleted_node->m_next->m_prev = &m_start;

            delete deleted_node;
        }
    }

    template <class T>
    void DList<T>::remove(DListNode* node)
    {
		if (node != &m_end)
		{
			node->m_prev->m_next = node->m_next;
			node->m_next->m_prev = node->m_prev;

        	delete node;
		}
        

    }

    template <class T>
    typename DList<T>::DListNode* DList<T>::begin()
    {
        return m_start.m_next;
    } 

    template <class T>
    typename DList<T>::DListNode* DList<T>::end()
    {
        return &m_end;
    }    

    template <class T>
    void DList<T>::print()
    {
        for (DListNode* runner = m_start.m_next; runner != &m_end; runner = runner->m_next)
        {
            std::cout << *(runner->m_data) << " ";
        }
        std::cout << std::endl;
    }


} // DS

#endif     /* __DOUBLE_LINKED_LIST_H__ */
