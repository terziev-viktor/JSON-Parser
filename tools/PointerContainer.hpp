#pragma once
#include <stdexcept>

namespace tools
{
	// Class representing a simple dynamically allocated array of elements
	template<class T>
	class PointerContainer
	{
	public:
		PointerContainer();
		PointerContainer(const PointerContainer & other);
		~PointerContainer();
	
		// keeps the pointer but the user is resposible for its life
		void add(T * item);
		// sets a pointer at a valid position. Valid means it shoul already exist
		void set_at(unsigned int index, T * new_item, bool __delete);
		// checks is the PointerContainer has no ponters
		bool is_empty() const;
		// sets the index to 0. Deletes objects
		void clear();
		// deletes all objects that keeps pointers to
		void delete_all_content();
		// returns count of elements in the array
		unsigned int count() const;
		// deletes the element at position index
		void delete_at(unsigned int index);
		
		const T * operator[](unsigned int index) const;
		T * operator[](unsigned int index);
		operator bool();
		bool operator !();
	private:
		static const unsigned int INIT_SIZE = 15;
		unsigned int size;
		unsigned int index;
		T * * buffer = nullptr;
		
		void expand();
	};
	
	template<class T>
	inline PointerContainer<T>::PointerContainer()
	{
		this->size = INIT_SIZE;
		this->index = 0;
		this->buffer = new T*[this->size];
	}
	template<class T>
	inline PointerContainer<T>::PointerContainer(const PointerContainer & other)
	{
		this->clear();
		this->size = other.size;
		this->index = other.index;
		this->buffer = new T*[this->size];
		for (unsigned int i = 0; i < this->index; i++)
		{
			this->buffer[i] = other.buffer[i];
		}
	}
	template<class T>
	inline PointerContainer<T>::~PointerContainer()
	{
		this->clear();
	}
	template<class T>
	inline void PointerContainer<T>::add(T * item)
	{
		if (this->index == this->size)
		{
			this->expand();
		}
		this->buffer[this->index] = item;
		++this->index;
	}

	template<class T>
	inline void PointerContainer<T>::set_at(unsigned int index, T * new_item, bool __delete)
	{
		if (index >= 0 && index < this->index)
		{
			if (__delete)
			{
				delete this->buffer[index];
			}
			this->buffer[index] = new_item;
			return;
		}
		throw std::out_of_range("Index out of range");
	}
	
	template<class T>
	inline bool PointerContainer<T>::is_empty() const
	{
		return this->index == 0;
	}
	
	template<class T>
	inline void PointerContainer<T>::clear()
	{
		if (this->buffer)
		{
			delete[] this->buffer;
		}
		this->index = 0;
		this->size = 0;
	}
	
	template<class T>
	inline unsigned int PointerContainer<T>::count() const
	{
		return this->index;
	}

	template<class T>
	inline void PointerContainer<T>::delete_at(unsigned int n)
	{
		if (n < 0 || n >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		delete this->buffer[n];
		for (unsigned int i = n; i < this->index - 1; i++)
		{
			this->buffer[i] = this->buffer[i + 1];
		}
		--this->index;
	}

	template<class T>
	inline const T * PointerContainer<T>::operator[](unsigned int index) const
	{
		if (index >= this->size)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline T * PointerContainer<T>::operator[](unsigned int index)
	{
		if (index >= this->size)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline PointerContainer<T>::operator bool()
	{
		return this->index != 0;
	}

	template<class T>
	inline bool PointerContainer<T>::operator!()
	{
		return this->index == 0;
	}
	
	template<class T>
	inline void PointerContainer<T>::expand()
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
	inline void PointerContainer<T>::delete_all_content()
	{
		for (unsigned int i = 0; i < this->index; i++)
		{
			delete this->buffer[i];
		}
		this->index = 0;
	}
}