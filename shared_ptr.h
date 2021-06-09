#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <stddef.h>      /* size_t */

namespace DS
{
	template <class T>
	class SharedPtr
	{
	public:
		explicit SharedPtr(T* ptr = nullptr): m_ref_count(new size_t(1)), m_data(ptr) { }
		~SharedPtr()
		{
			Destroy();
		}
		SharedPtr(const SharedPtr& other): m_ref_count(other.m_ref_count), m_data(other.m_data)
		{
			(*m_ref_count)++;
		}
		SharedPtr& operator=(const SharedPtr& other)
		{
			SharedPtr temp(other);

			Destroy();

			m_data = temp.m_data;
			m_ref_count = temp.m_ref_count;
			(*m_ref_count)++;
			
			return *this;
		}

		T& operator*() 
		{ 
			return (*m_data); 
		}
		T* operator->() 
		{ 
			return (m_data); 
		}

	private:
		size_t* m_ref_count;
		T* m_data;
		
		inline void Destroy()
		{
			if (--(*m_ref_count) == 0)
			{
				delete m_ref_count;
				delete m_data;
			}
		}
	};
} // namespace DS

#endif // __SHARED_PTR_H__
