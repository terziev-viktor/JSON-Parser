#pragma once
#include "tools\DynamicArray.hpp"
#include <stdexcept>
using std::cout;
using std::endl;
namespace tools
{
	template<class T>
	class Vector
	{
	public:
		Vector();
		~Vector();
		Vector(const Vector<T> & other);

		// class T should have a proper operator= implemented
		void add(const T & item);
		const T & getAt(unsigned int index) const;
		T & getAt(unsigned int index);
		void removeAt(unsigned int index);
		const bool isEmpty() const;
		// sets the index to 0. Does not delete objects
		void clear();
		// returns count of elements in the array
		const unsigned int count() const;
	private:
		static const unsigned int INIT_SIZE = 15;
		unsigned int size;
		unsigned int index;
		T * buffer;

		void expand();
	};

	template<class T>
	inline Vector<T>::Vector()
	{
		this->size = INIT_SIZE;
		this->index = 0;
		this->buffer = new T[INIT_SIZE];
	}

	template<class T>
	inline Vector<T>::~Vector()
	{
		delete[] this->buffer;
	}

	template<class T>
	inline Vector<T>::Vector(const Vector<T>& other)
	{
		this->size = other.count();
		this->index = other.count();
		this->buffer = new T[this->size];
		for (unsigned int i = 0; i < this->index; i++)
		{
			this->buffer[i] = other.getAt(i);
		}
	}

	template<class T>
	inline void Vector<T>::add(const T & item)
	{
		if (this->index == this->size)
		{
			this->expand();
		}
		this->buffer[index] = item;
		++index;
	}

	template<class T>
	inline const T & Vector<T>::getAt(unsigned int index) const
	{
		if (index < 0 || index >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline T & Vector<T>::getAt(unsigned int index)
	{
		if (index < 0 || index >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline void Vector<T>::removeAt(unsigned int at)
	{
		if (at < 0 || at >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		for (unsigned int i = at; i < this->index - 1; i++)
		{
			this->buffer[i] = this->buffer[i + 1];
		}
		--index;
	}

	template<class T>
	inline const bool Vector<T>::isEmpty() const
	{
		return this->index == 0;
	}

	template<class T>
	inline void Vector<T>::clear()
	{
		this->index = 0;
	}

	template<class T>
	inline const unsigned int Vector<T>::count() const
	{
		return this->index;
	}

	template<class T>
	inline void Vector<T>::expand()
	{
		T * biggerBuffer = new T[this->size * 2];
		this->size *= 2;
		for (size_t i = 0; i < this->index; i++)
		{
			biggerBuffer[i] = this->buffer[i];
		}
		delete[] this->buffer;
		this->buffer = biggerBuffer;
	}

}
