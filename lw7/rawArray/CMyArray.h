#pragma once

#include <iostream>

template <class T>
class CMyArray
{
public:
	class Iterator;
	CMyArray(unsigned int size = 0)
	{
		m_arr = new T[size];
		m_size = size;
	}
	CMyArray(const CMyArray& arrObject)
	{
		m_arr = new T[arrObject.m_size];
		m_size = arrObject.m_size;

		memcpy(m_arr, arrObject.m_arr, m_size);
	}
	CMyArray(CMyArray&& arrObject)
		: m_arr(nullptr)
		, m_size(0)
	{
		m_arr = arrObject.m_arr;
		m_size = arrObject.m_size;

		arrObject.m_arr = nullptr;
		arrObject.m_size = 0;
	}

	~CMyArray()
	{
		delete[] m_arr;
	}

	unsigned int GetSize()const
	{
		return m_size;
	}

	T& operator[](unsigned int index)const
	{
		if (index < 0 || index >= m_size)
		{
			throw std::out_of_range("exceeding the boundaries");
		}

		return m_arr[index];
	}

	void Resize(unsigned int size)
	{
		T* arr = new T[size];

		for (unsigned int i = 0; i < size; i++)
		{
			if (i < m_size)
			{
				arr[i] = m_arr[i];
			}
			else
			{
				arr[i] = T{};
			}
		}

		delete[] m_arr;
		m_arr = arr;
		m_size = size;
	}

	void Clear()
	{
		delete[] m_arr;
		m_size = 0;
	}

	void PushBack(const T& element)
	{
		T* tmp = new T[m_size + 1];

		memcpy(tmp, m_arr, m_size);
		tmp[m_size] = element;
		m_size++;

		delete[] m_arr;
		m_arr = tmp;
	}

	Iterator begin()
	{
		return m_arr;
	}

	Iterator end()
	{
		return m_arr + m_size;
	}

	Iterator rbegin()
	{
		end();
	}

	Iterator rend()
	{
		begin();
	}

	CMyArray& operator=(const CMyArray& arrObject)
	{
		if (this != &arrObject)
		{
			T* tmp = new T[arrObject.m_size];

			m_size = arrObject.m_size;
			memcpy(tmp, arrObject.m_arr, m_size);

			delete[] m_arr;
			m_arr = tmp;
		}

		return *this;
	}

	CMyArray& operator=(CMyArray&& arrObject)
	{
		if (this != &arrObject)
		{
			delete[] m_arr;

			m_arr = arrObject.m_arr;
			m_size = arrObject.m_size;

			arrObject.m_arr = nullptr;
			arrObject.m_size = 0;
		}

		return *this;
	}

	class Iterator
	{
	public:
		Iterator(T* first) : m_curr(first) {}

		T& operator+(int num) { return *(m_curr + num); }
		T& operator-(int num) { return *(m_curr - num); }

		T& operator++(int) { return *(m_curr++); }
		T& operator--(int) { return *(m_curr--); }
		T& operator++() { return *(++m_curr); }
		T& operator--() { return *(--m_curr); }

		bool operator!=(const Iterator& it) { return m_curr != it.m_curr; }
		bool operator==(const Iterator& it) { return m_curr == it.m_curr; }

		T& operator*() { return *m_curr; }
	private:
		T* m_curr;
	};

private:
	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void DestroyItems(T* from, T* to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};