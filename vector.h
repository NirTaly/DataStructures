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

		Vector(const Vector& ) = delete;
		Vector& operator=(const Vector& ) = delete;

		T& get(size_t i);
		void set(size_t i, const T& other);

		// VectorProxy operator[](size_t pos);  
        // bool operator[](size_t pos) const; // for const obj.

		/*
		* Push/Pop element to/from Vector 
		* Complexity = O(1)
		*/
		void pushBack(T element);
		void popBack();

		void reserve(size_t new_capacity);
		void doubleSize();

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

		// class VectorProxy
		// {
		// public:
		// 	VectorProxy(Vector& bit_arr, size_t pos): m_bit_arr(bit_arr), m_pos(pos) 
		// 	{ }

		// 	// Invoked when proxy is used to modify the value.
		// 	VectorProxy& operator=(T value)  // b1[1] = true;
		// 	{
		// 		m_vector.array[m_pos] = value;
		// 		return *this; 
		// 	}

		// 	// Invoked when proxy is used to read the value.
		// 	operator bool() const // if (b1[1]) { ... }
		// 	{
		// 		return (m_vector.array[m_pos]);
		// 	}

		// 	VectorProxy& operator=(const VectorProxy& other) // b1[1] = b2[5]
		// 	{

		// 		// *this = bool(other);

		// 		// return (*this);
		// 	}
		// private:
		// 	Vector& m_vector;
		// 	size_t m_pos;
		// };
	};

	template <typename T>
	Vector<T>::Vector(size_t capacity) : array(new T[capacity]), capacity(capacity), m_size(0)
	{	}
	
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
	void Vector<T>::set(size_t i, const T& other)
	{
		T tmp(other);

		swap(array[i], tmp);
	}

	template <typename T>
	void Vector<T>::pushBack(T element)
	{
		if (m_size == capacity)
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

		else if (4*m_size < capacity)
		{
			reserve(capacity / 2);
		}

		m_size--;

		return (0);
	}

	template <typename T>
	void Vector<T>::reserve(size_t new_capacity)
	{
		if(new_capacity < m_size)
		{
			throw Failure();
		}

		T* new_array = new T[new_capacity];
		memcpy(new_array, array, capacity * sizeof(T));
		delete[] array;
		array = new_array;
	}

	template <typename T>
	void Vector<T>::doubleSize()
	{
		reserve(2*capacity);
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