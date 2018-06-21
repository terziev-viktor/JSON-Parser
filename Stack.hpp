#pragma once

namespace tools
{
	template<class T>
	class Stack
	{
	public:
		Stack();
		~Stack();
		Stack(const Stack<T> & other);
		
		void print(std::ostream & os) const;

		// class T should have a proper operator= implemented
		void push(const T & item);
		// returns the top item.
		T pop();
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
	inline Stack<T>::Stack()
	{
		this->size = INIT_SIZE;
		this->index = 0;
		this->buffer = new T[INIT_SIZE];
	}

	template<class T>
	inline Stack<T>::~Stack()
	{
		delete[] this->buffer;
	}

	template<class T>
	inline Stack<T>::Stack(const Stack<T>& other)
	{
		this->size = other.count();
		this->index = other.count();
		this->buffer = new T[this->size];
		for (unsigned int i = 0; i < this->index; i++)
		{
			this->buffer[i] = other.buffer[i];
		}
	}

	template<class T>
	inline void Stack<T>::print(std::ostream & os) const
	{
		os << "|--\n";
		for (size_t i = 0; i < this->index; i++)
		{
			os << this->buffer[i] << '\n';
		}
		os << "--|";
	}

	template<class T>
	inline void Stack<T>::push(const T & item)
	{
		if (this->index == this->size)
		{
			this->expand();
		}
		this->buffer[index] = item;
		++index;
	}

	template<class T>
	inline T Stack<T>::pop()
	{
		--this->index;
		return this->buffer[index];
	}

	template<class T>
	inline const bool Stack<T>::isEmpty() const
	{
		return this->index == 0;
	}

	template<class T>
	inline void Stack<T>::clear()
	{
		this->index = 0;
	}

	template<class T>
	inline const unsigned int Stack<T>::count() const
	{
		return this->index;
	}

	template<class T>
	inline void Stack<T>::expand()
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

	template<class T>
	std::ostream & operator<<(std::ostream & os, Stack<T> & stack)
	{
		stack.print(os);
		return os;
	}
}


