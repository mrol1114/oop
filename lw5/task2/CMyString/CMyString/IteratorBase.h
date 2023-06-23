#pragma once

#include <iostream>
#include <iterator>

template <bool IsConst>
class IteratorBase
{
	friend class IteratorBase<true>;
public:
	using MyType = IteratorBase< IsConst>;
	using value_type = std::conditional_t<IsConst, const char, char>;
	using reference = value_type&;
	using pointer = value_type*;
	using difference_type = ptrdiff_t;
	using iterator_category = std::random_access_iterator_tag;

	IteratorBase() = default;
	IteratorBase(const IteratorBase<false>& other)
		: m_item(other.m_item)
	{
	}

	reference& operator*() const
	{
		return *m_item;
	}

	MyType& operator++()
	{
		m_item++;
		return *this;
	}

	MyType& operator--()
	{
		m_item--;
		return *this;
	}

	size_t operator-(const MyType& other)
	{
		return abs(m_item - other.m_item);
	}

	MyType& operator++(int)
	{
		m_item++;
		return *this;
	}

	MyType& operator+=(difference_type offset)
	{
		m_item += offset;
		return *this;
	}

	MyType operator+(difference_type offset) const
	{
		MyType self(m_item);
		return self += offset;
	}

	bool operator==(const MyType& other) const
	{
		return m_item == other.m_item;
	}

	bool operator!=(const MyType& other) const
	{
		return !(m_item == other.m_item);
	}

	reference operator[](size_t index)const
	{
		return *(m_item + index);
	}

	friend MyType operator+(difference_type offset, const MyType& it)
	{
		return it + offset;
	}

public:
	IteratorBase(char* item)
		: m_item(item)
	{
	}

protected:
	char* m_item = nullptr;
};