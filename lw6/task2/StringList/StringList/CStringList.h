#pragma once

#include <string>
#include <memory>
#include <iterator>
#include <algorithm>

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
		friend class CStringList;
	public:
		using MyType = IteratorBase< IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_node(other.m_node)
		{
		}

		reference& operator*() const
		{
			return m_node->data;
		}

		MyType& operator++()
		{
			m_node = m_node->next.get();
			return *this;
		}

		MyType& operator++(int)
		{
			m_node = m_node->next.get();
			return *this;
		}

		MyType& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}

		MyType& operator--(int)
		{
			m_node = m_node->prev;
			return *this;
		}

		bool operator==(const MyType& other)const
		{
			return m_node == other.m_node;
		}

		bool operator!=(const MyType& other)const
		{
			return !(m_node == other.m_node);
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}
		
	public:
		IteratorBase(Node* item)
			: m_node(item)
		{
		}

	protected:
		Node* m_node = nullptr;
	};

public:

	CStringList() = default;
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;

	~CStringList();

	size_t GetSize()const;
	bool Empty() const;
	void PushBack(const std::string& data);
	void PushFront(const std::string& data);
	void Clear();
	std::string& GetBackElement();
	std::string const& GetBackElement()const;

	CStringList& operator =(const CStringList& other);
	CStringList& operator =(CStringList&& other);

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator Erase(iterator& it);
	iterator Insert(iterator& it, const std::string& value);

	iterator begin();
	iterator end();
	const_iterator begin()const;
	const_iterator end()const;

	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();
	std::reverse_iterator<const_iterator> rbegin()const;
	std::reverse_iterator<const_iterator> rend()const;

	const_iterator cbegin()const;
	const_iterator cend()const;
	std::reverse_iterator<const_iterator> crbegin()const;
	std::reverse_iterator<const_iterator> crend()const;

private:
	void DeleteItems(std::unique_ptr<Node>& firstNode);
	void CopyItems(const std::unique_ptr<Node>& fromFirstNode, Node* fromLastNode,
		std::unique_ptr<Node>& toFirstNode, Node*& toLastNode);

	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};