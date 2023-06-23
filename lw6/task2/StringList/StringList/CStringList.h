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
	
	class BaseIterator
	{
		friend CStringList;
		BaseIterator(Node* node);

	public:
		using iterator_category = std::bidirectional_iterator_tag;

		BaseIterator() = default;
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;

	private:
		Node* m_node = nullptr;
	};

	class Iterator: public BaseIterator
	{
		friend CStringList;
		Iterator(Node* node);

	public:
		Iterator& operator++(int);
		Iterator& operator++();
		Iterator& operator--(int);
		std::string& operator*()const;
	};

	class ConstIterator: public BaseIterator
	{
		friend CStringList;
		ConstIterator(Node* node);

	public:
		ConstIterator& operator++(int);
		ConstIterator& operator++();
		ConstIterator& operator--(int);
		const std::string& operator*()const;
	};

	Iterator Erase(Iterator& it);
	Iterator Insert(Iterator& it, const std::string& value);

	Iterator begin();
	Iterator end();
	ConstIterator begin()const;
	ConstIterator end()const;

	//std::reverse_iterator<Iterator> rbegin();
	//std::reverse_iterator<Iterator> rend();

	ConstIterator cbegin()const;
	ConstIterator cend()const;

	//std::reverse_iterator<ConstIterator> crbegin()const;
	//std::reverse_iterator<ConstIterator> crend()const;

private:
	void DeleteItems(std::unique_ptr<Node>& firstNode);
	void CopyItems(const std::unique_ptr<Node>& fromFirstNode, Node* fromLastNode,
		std::unique_ptr<Node>& toFirstNode, Node*& toLastNode);

	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};