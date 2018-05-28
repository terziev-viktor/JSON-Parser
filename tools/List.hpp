#pragma once
#include <stdexcept>
#include <iostream>

#include "DynamicArray.hpp"

using std::cout;
using std::endl;

namespace tools
{
	// Class representing a simple dynamically allocated array of elements
	template<class T>
	class List : public DynamicArray<T>
	{
	public:
		List();
		~List();
	
		// class T should have a proper operator= implemented
		void add(T * item);
		// returns the item on <index> place. Throws out_of_range exception for invalid index
		// I dont return a const item because Fmibook should be able to edit items;
		T * getAt(unsigned int index) const;
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
		T * * buffer;
	
		void expand();
		void deleteBufferContent();
	};
	
	template<class T>
	inline List<T>::List()
	{
		this->size = INIT_SIZE;
		this->index = 0;
		this->buffer = new T*[this->size];
	}
	template<class T>
	inline List<T>::~List()
	{
		//for debug purpuses
		//cout << "~List()" << endl;
		this->deleteBufferContent();
	}
	template<class T>
	inline void List<T>::add(T * item)
	{
		if (!item)
		{
			throw std::invalid_argument("Invalid item");
		}
		if (this->index == this->size)
		{
			this->expand();
		}
		this->buffer[this->index] = item;
		++this->index;
	}
	
	template<class T>
	inline T * List<T>::getAt(unsigned int index) const
	{
		if (index >= this->index || index < 0)
		{
			throw std::out_of_range("Index out of range.");
		}
		return this->buffer[index];
	}
	
	template<class T>
	inline void List<T>::removeAt(unsigned int index)
	{
		if (this->index >= this->size)
		{
			throw std::out_of_range("Index of of range.");
		}
	
		delete this->buffer[index]; // deleting object at index
		for (unsigned int i = index; i < this->count() - 1; i++) // shift left all other 
		{
			buffer[i] = buffer[i + 1];
		}
		this->index = this->index - 1;
	}
	
	template<class T>
	inline const bool List<T>::isEmpty() const
	{
		return this->index == 0;
	}
	
	template<class T>
	inline void List<T>::clear()
	{
		for (int i = 0; i < this->index; i++)
		{
			delete this->buffer[i];
		}
		this->index = 0;
	}
	
	template<class T>
	inline const unsigned int List<T>::count() const
	{
		return this->index;
	}
	
	template<class T>
	inline void List<T>::expand()
	{
		T * * biggerBuffer = new T*[this->size * 2];
		this->size = this->size * 2;
		for (unsigned int i = 0; i < this->index; i++)
		{
			biggerBuffer[i] = this->buffer[i];
		}
		
		delete[] this->buffer; // deleting the array of pointers but not the objects that they are pointing to
		this->buffer = biggerBuffer;
	}
	template<class T>
	inline void List<T>::deleteBufferContent()
	{
		for (unsigned int i = 0; i < this->index; i++)
		{
			delete this->buffer[i];
		}
		delete[] this->buffer;
	}
}