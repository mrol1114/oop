#pragma once

#include <iostream>
#include <iterator>

template <class T>
class CMyArray
{
	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		using MyType = IteratorBase< IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
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

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}

	public:
		IteratorBase(T* item)
			: m_item(item)
		{
		}

	protected:
		T* m_item = nullptr;
	};

public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		CopyArrayValues(arr);
	}

	CMyArray(CMyArray&& arr)noexcept
	{
		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_endOfCapacity = arr.m_endOfCapacity;

		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_end;
	}

	T& operator[](size_t index)const
	{
		if (index < 0 || m_begin + index >= m_end)
		{
			throw std::out_of_range("exceeding the boundaries");
		}

		return *(m_begin + index);
	}

	void Resize(size_t size)
	{
		if (m_begin + size > m_end)
		{
			if (m_begin + size > m_endOfCapacity)
			{
				auto newBegin = RawAlloc(size);
				T* newEnd = newBegin;

				try
				{
					CopyItems(m_begin, m_end, newBegin, newEnd);
					T* limit = newEnd + size - GetSize();
					for (; newEnd < limit; newEnd++)
					{
						new (newEnd) T();
					}
				}
				catch (...)
				{
					DeleteItems(newBegin, newEnd);
					throw;
				}

				DeleteItems(m_begin, m_end);

				m_begin = newBegin;
				m_end = newEnd;
			}
			else
			{
				for (; m_end < m_begin + size; m_end++)
				{
					new (m_end) T();
				}
			}
		}
		else
		{
			auto newBegin = RawAlloc(size);
			T* newEnd = newBegin;

			try
			{
				CopyItems(m_begin, m_begin + size, newBegin, newEnd);
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}

			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
		}

		m_endOfCapacity = m_end;
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_end = nullptr;
		m_begin = nullptr;
		m_endOfCapacity = nullptr;
	}

	void PushBack(const T& element)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = GetNewCapacityValue();

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				new (newEnd) T(element);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(element);
			++m_end;
		}
	}

	CMyArray& operator=(const CMyArray& arr)
	{
		if (this != &arr)
		{
			CopyArrayValues(arr);
		}

		return *this;
	}

	CMyArray& operator=(CMyArray&& arr)
	{
		if (this != &arr)
		{
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;

			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}

		return *this;
	}

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator begin()
	{
		return { m_begin };
	}

	iterator end()
	{
		return { m_end };
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::make_reverse_iterator(this->end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::make_reverse_iterator(this->begin());
	}

	const_iterator begin() const
	{
		return { m_begin };
	}

	const_iterator end() const
	{
		return { m_end };
	}

	std::reverse_iterator<const_iterator> rbegin() const
	{
		return std::make_reverse_iterator(this->cend());
	}

	std::reverse_iterator<const_iterator> rend() const
	{
		return std::make_reverse_iterator(this->cbegin());
	}

	const_iterator cbegin() const
	{
		return { m_begin };
	}

	const_iterator cend() const
	{
		return { m_end };
	}

	std::reverse_iterator<const_iterator> crbegin() const
	{
		return std::make_reverse_iterator(this->cend());
	}

	std::reverse_iterator<const_iterator> crend() const
	{
		return std::make_reverse_iterator(this->cbegin());
	}

private:

	void CopyArrayValues(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	size_t GetNewCapacityValue()
	{
		return std::max(size_t(1), GetSize() * 2);
	}

	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}

	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};