#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <stddef.h>      /* size_t */
#include "exceptions.h"

namespace DS
{

	template <typename T>
	class Vector
	{

	public:
		Vector(size_t capacity = 4);
		~Vector();

		Vector(const Vector& vec);
		Vector& operator=(const Vector& vec);

		T& get(size_t i);
		void set(size_t i, T other);

		/*
		* Push/Pop element to/from Vector 
		* Complexity = O(1)
		*/
		void pushBack(T element);
		void popBack();

		void reserve(size_t new_capacity);
		void doubleSize();

		T& operator[](size_t i);
		const T& operator[](size_t i) const;
		/*      
		* Return number of elements in Vector  
		* Complexity = O(1)
		*/
		size_t size() const;
		size_t capacity() const;
		
	private:
		T* array;
		size_t m_capacity;
		size_t m_size;
	};

	template <typename T>
	Vector<T>::Vector(size_t capacity) : array(new T[capacity]), m_capacity(capacity), m_size(0)
	{	}
	
	template <typename T>
	Vector<T>::Vector(const Vector<T>& vec) : array(new T[vec.m_capacity]), m_capacity(vec.m_capacity), m_size(vec.m_size)
	{
		for (int i = 0; i < m_capacity; i++)
		{
			array[i] = vec.array[i];
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& vec)		// specific for non-shrinking vector
	{
		for (size_t i = 0; i < vec.m_capacity; i++)
		{
			array[i] = vec.array[i];
		}

		return *this;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		delete[] array;
	}

	template <typename T>
	T& Vector<T>::get(size_t i)
	{
		return array[i];
	}

	template <typename T>
	void Vector<T>::set(size_t i, T other)
	{
		array[i] = other;
	}

	template <typename T>
	void Vector<T>::pushBack(T element)
	{
		if (m_size == m_capacity)
		{
			doubleSize();
		}

		array[m_size] = element;
		m_size++;
	}

	template <typename T>
	void Vector<T>::popBack()
	{
		if (0 == m_size)
		{
			throw VectorEmpty();
		}

		else if (4*m_size < m_capacity)
		{
			reserve(m_capacity / 2);
		}

		m_size--;
	}

	template <typename T>
	void Vector<T>::reserve(size_t new_capacity)
	{
		if(new_capacity < m_size)
		{
			throw Failure();
		}

		T* new_array = new T[new_capacity];
		memcpy((void*)new_array, (void*)array, m_capacity * sizeof(T));
		delete[] array;
		array = new_array;
	}

	template <typename T>
	void Vector<T>::doubleSize()
	{
		reserve(2*m_capacity);
	}
	
	template <typename T>
	T& Vector<T>::operator[](size_t i)
	{
		return array[i];
	}
	
	template <typename T>
	const T& Vector<T>::operator[](size_t i) const
	{
		return array[i];
	}

	template <typename T>
	size_t Vector<T>::size() const
	{
		return m_size;
	}

	template <typename T>
	size_t Vector<T>::capacity() const
	{
		return m_capacity;
	}


} // namespace DS


#endif     /* __VECTOR_H__ */