#pragma once
#include <iostream>

template<typename T>
class Vector
{
private:
	T* data;
	size_t size;
	size_t capacity;

	void copy(const Vector&);
	void destroy();
	void resize();
	T& at(size_t);

public:
	Vector();
	Vector(const Vector&);
	Vector<T>& operator=(const Vector&);
	~Vector();

	bool isEmpty() const;
	size_t getSize() const;
	size_t getCapacity() const;
	T operator[](size_t) const;
	T& operator[](size_t);

	void pop();
	void push_back(const T&);
	void pop_back();
	void clear();

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>&);
};

template<typename T>
void Vector<T>::copy(const Vector<T>& others)
{
	capacity = others.capacity;
	size = others.size;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = others.data[i];
	}
}

template<typename T>
void Vector<T>::destroy()
{
	delete[] data;
}

template<typename T>
void Vector<T>::resize()
{
	capacity *= 2;
	T* newBuffer = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newBuffer[i] = data[i];
	}
	destroy();
	data = newBuffer;
}

template<typename T>
Vector<T>::Vector()
{
	capacity = 8;
	size = 0;
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& others)
{
	copy(others);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& others)
{
	if (this != &others)
	{
		destroy();
		copy(others);
	}

	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	destroy();
}

template<typename T>
T& Vector<T>::at(size_t i)
{
	if (i < size)
	{
		return data[i];
	}
}

template<typename T>
T Vector<T>::operator[](size_t i) const
{
	return at(i);
}

template<typename T>
T& Vector<T>::operator[](size_t i)
{
	return at(i);
}


template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
inline size_t Vector<T>::getSize() const
{
	return this->size;
}

template<typename T>
inline size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

template<typename T>
inline void Vector<T>::pop()
{
	T* newBuffer = new T[size - 1];
	for (size_t i = 0; i < size - 1; i++) {
		newBuffer[i] = data[i + 1];
	}
	size--;
	delete[] data;
	data = newBuffer;
}

template<typename T>
void Vector<T>::push_back(const T& newElem)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = newElem;
}

template<typename T>
void Vector<T>::pop_back()
{
	size--;
}

template<typename T>
inline void Vector<T>::clear()
{
	delete[] data;
	data = new T[capacity];
	size = 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& current)
{
	for (int i = 0; i < current.getSize(); i++)
	{
		out << current[i] << " ";
	}
	out << "\n";
	return out;
}