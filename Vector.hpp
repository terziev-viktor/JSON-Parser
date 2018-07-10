#pragma once
#include <stdexcept>
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
		T & operator[](unsigned int index);
		const T & operator[](unsigned int index) const;
		bool operator==(const Vector<T> & other) const;
		Vector<T> & operator+=(const Vector<T> & other);
		Vector<T> & operator-=(unsigned int count);

		int index_of(const T & item) const;
		void remove_at(unsigned int index);
		bool is_empty() const;
		// sets the index to 0. Does not delete objects
		void clear();
		// returns count of elements in the array
		unsigned int count() const;
		unsigned int capacity() const;
		Vector<T>& operator=(const Vector<T>& other);

		class Iterator
		{
		private:
			T * front; // start of data array
			T * current; // position of pointer to data 
			unsigned int size; // size of data array
			T * end; // end of data array
		public:
			Iterator(T * start, unsigned int size)
			{
				this->front = start;
				this->current = start;
				this->size = size;
				this->end = start + size;
			}
			Iterator(const Iterator & other)
			{
				this->front = other.front;
				this->current = other.current;
				this->size = other.size;
				this->end = other.end;
			}
			const T * first() const
			{
				return this->front;
			}
			const T * last() const
			{
				return this->last;
			}
			void next()
			{
				++this->current;
			}

			bool has_next() const
			{
				return this->current < this->last;
			}
			bool is_done() const
			{
				return this->current >= this->front + this->size;
			}
			const Iterator operator++(int)
			{
				const Iterator tmp(*this);
				++this;
				return tmp;
			}
			Iterator & operator++()
			{
				++this->current;
				return *this;
				
			}
			const Iterator & operator--(int)
			{
				Iterator tmp = *this;
				--this->current;
				return tmp;
			}
			Iterator & operator--()
			{
				--this->current;
				return *this;
			}
			T * operator->()
			{
				return this->current;
			}
			T & operator*()
			{
				return *this->current;
			}
			bool operator<(int i)
			{
				return current < (this->front + i);
			}
			bool operator>(int i)
			{
				return current > (this->front + i);
			}
			bool operator==(int i)
			{
				return current == (this->front + i);
			}
			bool operator>=(int i)
			{
				return current >= (this->front + i);
			}
			bool operator<=(int i)
			{
				return current <= (this->front + i);
			}
		};

		Iterator createIterator() const
		{
			Iterator i(this->buffer, this->index);
			return i;
		}
	private:
		static const unsigned int INIT_SIZE = 15;
		unsigned int size;
		unsigned int index;
		T * buffer = nullptr;

		void expand();
	};

	template<class T>
	inline Vector<T>::Vector()
		:size(INIT_SIZE),index(0)
	{
		this->buffer = new T[INIT_SIZE];
	}

	template<class T>
	inline Vector<T>::~Vector()
	{
		if (this->buffer)
		{
			delete[] this->buffer;
		}
	}

	template<class T>
	inline Vector<T>::Vector(const Vector<T>& other)
	{
		this->clear();
		this->size = other.count();
		this->index = other.count();
		this->buffer = new T[this->size];
		for (unsigned int i = 0; i < this->index; i++)
		{
			this->buffer[i] = other[i];
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
	inline T & Vector<T>::operator[](unsigned int index)
	{
		if (index < 0 || index >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline const T & Vector<T>::operator[](unsigned int index) const
	{
		if (index < 0 || index >= this->index)
		{
			throw std::out_of_range("Index out of range");
		}
		return this->buffer[index];
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
	{
		this->clear();
		this->index = other.count();
		this->size = other.capacity();
		for (unsigned int i = 0; i < this->index; i++)
		{
			this->add(other[i]);
		}
		return *this;
	}

	template<class T>
	inline bool Vector<T>::operator==(const Vector<T>& other) const
	{
		for (size_t i = 0; i < other.index; i++)
		{
			if (!(this->buffer[i] == other.buffer[i]))
			{
				return false;
			}
		}
		return true;
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
	{
		unsigned int count = other.count();
		for (unsigned int i = 0; i < count; i++)
		{
			this->add(other[i]);
		}
		return *this;
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator-=(unsigned int count)
	{
		if (count >= this->index)
		{
			this->index = 0;
		}
		else
		{
			this->index -= count;
		}
	}

	template<class T>
	inline int Vector<T>::index_of(const T & item) const
	{
		int ind = -1;
		for (unsigned int i = 0; i < this->count(); i++)
		{
			if ((*this)[i] == item)
			{
				return i;
			}
		}
		return ind;
	}

	template<class T>
	inline void Vector<T>::remove_at(unsigned int at)
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
	inline bool Vector<T>::is_empty() const
	{
		return this->index == 0;
	}

	template<class T>
	inline void Vector<T>::clear()
	{
		this->index = 0;
		this->size = 0;
		delete[] this->buffer;
	}

	template<class T>
	inline unsigned int Vector<T>::count() const
	{
		return this->index;
	}

	template<class T>
	inline unsigned int Vector<T>::capacity() const
	{
		return this->size;
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

	template<class T>
	std::ostream & operator<<(std::ostream & os, const Vector<T> & v)
	{
		os << '(';
		for (unsigned int i = 0; i < v.count() - 1; i++)
		{
			os << v[i] << "\n";
		}
		os << v[v.count() - 1] << ')';
		return os;
	}
}
