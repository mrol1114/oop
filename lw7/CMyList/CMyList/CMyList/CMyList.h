#pragma once

template <class T>
class CMyList
{
public:

	int GetSize()const
	{
		return m_size;
	}

	void PushBack()
	{

	}

	void PushTop()
	{

	}

	class Iterator
	{

	};

private:
	struct Node
	{
		T elm;
		Node* next;
		Node* prev;
	};

	unsigned int m_size;
	Node first;
	
};