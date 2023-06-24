#include "CStringList.h"
#include <iostream>

using namespace std;

CStringList::CStringList(const CStringList& other)
{
	if (this != &other)
	{
		CopyItems(other.m_firstNode, other.m_lastNode, m_firstNode, m_lastNode);
		m_size = other.m_size;
	}
}

CStringList::CStringList(CStringList&& other)noexcept
{
	if (this != &other)
	{
		Clear();
		swap(m_size, other.m_size);
		swap(m_firstNode, other.m_firstNode);
		swap(m_lastNode, other.m_lastNode);
	}
}

CStringList::~CStringList()
{
	Clear();
}

size_t CStringList::GetSize()const
{
	return m_size;
}

bool CStringList::Empty()const
{
	return m_size == 0;
}

void CStringList::PushBack(const std::string& data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();

	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;

	++m_size;
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = make_unique<Node>(data, nullptr, nullptr);

	if (m_firstNode)
	{
		swap(m_firstNode, newNode);
		m_firstNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
		m_lastNode = m_firstNode.get();
	}

	++m_size;
}

void CStringList::Clear()
{
	DeleteItems(m_firstNode);

	m_size = 0;
}

CStringList& CStringList::operator =(const CStringList& other)
{
	if (this != &other)
	{
		CopyItems(other.m_firstNode, other.m_lastNode, m_firstNode, m_lastNode);
		m_size = other.m_size;
	}

	return *this;
}

CStringList& CStringList::operator =(CStringList&& other)
{
	return *this = other;
}

std::string& CStringList::GetBackElement()
{
	if (!m_lastNode)
	{
		throw logic_error("list is empty");
	}

	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement()const
{
	if (!m_lastNode)
	{
		throw logic_error("list is empty");
	}
	
	return m_lastNode->data;
}

void CStringList::CopyItems(const std::unique_ptr<Node>& fromFirstNode, Node* fromLastNode,
	std::unique_ptr<Node>& toFirstNode, Node*& toLastNode)
{
	auto newFirstNode = make_unique<Node>(fromFirstNode->data, nullptr, nullptr);
	Node* newLastNode = newFirstNode.get();

	try
	{
		CStringList::const_iterator it(fromFirstNode.get());
		while ((it++).m_node)
		{
			auto newNode = make_unique<Node>(*it, newLastNode, nullptr);

			newLastNode->next = move(newNode);
			newLastNode = newLastNode->next.get();
		}
	}
	catch (...)
	{
		DeleteItems(newFirstNode);
		throw;
	}

	toFirstNode = move(newFirstNode);
	toLastNode = newLastNode;
}

void CStringList::DeleteItems(std::unique_ptr<Node>& node)
{
	std::unique_ptr<Node> next;
	while (node)
	{
		next = move(node->next);
		node->data.clear();
		node->prev = nullptr;
		node = nullptr;
		node = move(next);
	}
}

CStringList::iterator CStringList::Erase(CStringList::iterator& it)
{
	if (it.m_node)
	{
		Node* prev = it.m_node->prev;
		Node* next = it.m_node->next.get();

		if (prev)
		{
			prev->next = move(it.m_node->next);
		}
		else
		{
			m_firstNode = move(it.m_node->next);
		}

		it.m_node = nullptr;
		if (next)
		{
			it.m_node = next;
			it.m_node->prev = prev;
		}
		else
		{
			m_lastNode = it.m_node ? it.m_node : prev;
		}
		m_size--;
	}
	else
	{
		throw std::logic_error("trying to erase empty value of list");
	}

	return it;
}

CStringList::iterator CStringList::Insert(CStringList::iterator& it, const std::string& value)
{
	if (it.m_node)
	{
		if (m_firstNode.get() == it.m_node)
		{
			PushFront(value);
			return begin();
		}
		if (it == end())
		{
			PushBack(value);
			return iterator(m_lastNode);
		}

		Node* prevNode = it.m_node->prev;
		auto newNode = std::make_unique<Node>(value, prevNode, nullptr);
		newNode->next = move(prevNode->next);
		auto resultIterator = iterator(newNode.get());
		prevNode->next = move(newNode);

		++m_size;
		return resultIterator;
	}
	else
	{
		throw std::logic_error("trying to insert in empty position");
	}

	return it;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode.get());
}

CStringList::iterator CStringList::end()
{
	return iterator(m_lastNode->next.get());
}

CStringList::const_iterator CStringList::begin()const
{
	return const_iterator(m_firstNode.get());
}

CStringList::const_iterator CStringList::end()const
{
	return const_iterator(m_lastNode->next.get());
}

std::reverse_iterator<CStringList::iterator> CStringList::rbegin()
{
	return std::make_reverse_iterator(iterator(m_lastNode->next.get()));
}

std::reverse_iterator<CStringList::iterator> CStringList::rend()
{
	return std::make_reverse_iterator(iterator(m_firstNode.get()));
}

std::reverse_iterator<CStringList::const_iterator> CStringList::rbegin()const
{
	return std::make_reverse_iterator(const_iterator(m_lastNode->next.get()));
}

std::reverse_iterator<CStringList::const_iterator> CStringList::rend()const
{
	return std::make_reverse_iterator(const_iterator(m_firstNode.get()));
}

CStringList::const_iterator CStringList::cbegin()const
{
	return const_iterator(m_firstNode.get());
}

CStringList::const_iterator CStringList::cend()const
{
	return const_iterator(m_lastNode->next.get());
}

std::reverse_iterator<CStringList::const_iterator> CStringList::crbegin()const
{
	return std::make_reverse_iterator(const_iterator(m_lastNode->next.get()));
}

std::reverse_iterator<CStringList::const_iterator> CStringList::crend()const
{
	return std::make_reverse_iterator(const_iterator(m_firstNode.get()));
}