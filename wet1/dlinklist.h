/******************************************************************************
                                Singley Linked List
                                    Nir Tali
                                    20.02.19
 *****************************************************************************/
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
			DListNode(T* data = nullptr, DListNode* next = nullptr ,DListNode* prev = nullptr) : 
				data(new T(*m_data)), m_prev(prev), m_next(next) { }
			
			~DListNode() { delete m_data; m_next = nullptr; m_prev = nullptr; }

            DListNode* m_prev;
            DListNode* m_next;
            T* m_data;
        };

        DList();
        ~DList();

        DList(const DList& s) = delete;
        DList& operator=(const DList& rhs) = delete; 

        void pop(void);
        void remove(DListNode* node);

        DListNode* pushAfter(T* const data, DListNode* curr = nullptr);
		DListNode* pushBefore(T* const data, DListNode* curr = nullptr);

        size_t size(void) const;

        bool isEmpty(void) const;

		// template <typename Func>
		// void forEach(DListNode* start = m_start.m_next, DListNode* end = &m_end);

    private: 

        DListNode m_start;
        DListNode m_end;
    };

    template <class T>
    DList<T>::DList() 
	{ 
		m_start.m_next = &m_end;
		m_end.m_prev = &m_start;
	}
    
    template <class T>
    DList<T>::~DList(void)
    {
        while (!IsEmpty())
        {
            pop();
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
        while (iter)
        {
            counter++;   
            iter = iter->m_next;
        }

        return (counter);
    }

    template <class T>
	DList<T>::DListNode* DList<T>::pushAfter(T* const data, DListNode* curr)
    {
        DListNode* new_node = nullptr;
        if(!curr)
        {
            new_node = new DListNode(data, &m_start, &m_end);
            m_start.m_next = new_node;
			m_end.m_prev = new_node;
        }
        else
        {
            new_node = new DListNode(data, curr, curr->m_next);
            curr->m_next = new_node;
            curr->m_next->m_prev = new_node;
        }
        return new_node;

    }

	template <class T>
	DList<T>::DListNode* DList<T>::pushBefore(T* const data, DListNode* curr)
	{
		DListNode* new_node = nullptr;
		
		if (isEmpty())
		{
			new_node = new DListNode(data,  &m_start, &m_end);
			m_start.m_next = new_node;
			m_end.m_prev = new_node;
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
        Node *deleted_node = m_start.m_next; 

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

} // DS