#include "String.h"
#include <algorithm>

namespace
{
	const char NULL_SYMBOL = '\0';

	void DeleteChars(char*& chars)
	{
		if (chars)
		{
			delete[] chars;
		}
	}

	void Copy(const char* const& from, char* to, size_t size, size_t offSet = 0)
	{
		for (size_t curPos = 0; curPos < size; curPos++)
		{
			to[offSet + curPos] = from[curPos];
		}
	}

	void CopyChars(const char* const& from, char*& to, size_t size)
	{
		size_t maxSize = size == SIZE_MAX ? strlen(from) : size;
		to = new char[maxSize + 1];
		Copy(from, to, size);

		to[maxSize] = NULL_SYMBOL;
	}

	String ConcatChars(const char* const& first, size_t firstSize, const char* const& second, size_t secondSize)
	{
		char* newChars = new char[firstSize + secondSize + 1];

		try
		{
			Copy(first, newChars, firstSize);
			Copy(second, newChars, secondSize, firstSize);
			newChars[firstSize + secondSize] = NULL_SYMBOL;
		}
		catch (...)
		{
			DeleteChars(newChars);
			throw;
		}

		return { newChars };
	}

	bool IsLower(const char* first, size_t firstSize, const char* second, size_t secondSize)
	{
		for (size_t curPos = 0; curPos < firstSize; curPos++)
		{
			if (curPos > secondSize)
			{
				return false;
			}
			if (first[curPos] < second[curPos])
			{
				return true;
			}
			if (first[curPos] > second[curPos])
			{
				return false;
			}
		}

		return firstSize < secondSize;
	}
	
	bool IsEqual(const char* first, size_t firstSize, const char* second, size_t secondSize)
	{
		if (firstSize != secondSize)
		{
			return false;
		}

		for (size_t curPos = 0; curPos < firstSize; curPos++)
		{
			if (first[curPos] != second[curPos])
			{
				return false;
			}
		}

		return true;
	}
}

String::String()
{
	m_chars = new char[1];
	m_chars[0] = NULL_SYMBOL;
}

String::String(const char* pString)
{
	try
	{
		CopyChars(pString, m_chars, strlen(pString));
		m_size = strlen(pString);
	}
	catch (...)
	{
		DeleteChars(m_chars);
		throw;
	}
}

String::String(char*&& pString)
{
	m_chars = std::move(pString);
	m_size = strlen(pString);
}

String::String(const char* pString, size_t length)
{
	try
	{
		CopyChars(pString, m_chars, length);
		m_size = length;
	}
	catch (...)
	{
		DeleteChars(m_chars);
		throw;
	}
}

String::String(String const& other)
{
	try
	{
		CopyChars(other.m_chars, m_chars, other.GetLength());
		m_size = other.GetLength();
	}
	catch (...)
	{
		DeleteChars(m_chars);
		throw;
	}
}

String::String(String&& other)noexcept
	: m_chars(other.m_chars)
	, m_size(other.m_size)
{
	other.m_chars = nullptr;
	other.m_size = 0;
}

String::String(std::string const& stlString)
{
	try
	{
		CopyChars(stlString.c_str(), m_chars, stlString.size());
		m_size = stlString.size();
	}
	catch (...)
	{
		DeleteChars(m_chars);
		throw;
	}
}

String::~String()
{
	DeleteChars(m_chars);
}

size_t String::GetLength()const
{
	return m_size;
}

const char* String::GetStringData()const
{
	return m_chars;
}

String String::SubString(size_t start, size_t length)const
{
	if (start >= m_size)
	{
		throw std::out_of_range("exceeding the boundaries");
	}

	return {m_chars + start, length == SIZE_MAX || start + length > m_size ? m_size : length};
}

void String::Clear()
{
	if (m_chars)
	{
		DeleteChars(m_chars);

		m_chars = new char[1];
		m_chars[0] = NULL_SYMBOL;
		m_size = 0;
	}
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		char* prevChars = m_chars;
		try
		{
			CopyChars(other.m_chars, m_chars, other.GetLength());
			DeleteChars(prevChars);
		}
		catch (...)
		{
			m_chars = prevChars;
		}
	}

	return *this;
}

String& String::operator=(String&& other)noexcept
{
	if (this != &other)
	{
		DeleteChars(m_chars);
		m_chars = other.m_chars;
		m_size = other.m_size;

		other.m_chars = nullptr;
		other.m_size = 0;
	}

	return *this;
}

char& String::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("exceeding the boundaries");
	}

	return m_chars[index];
}

const char& String::operator[](size_t index)const
{
	if (index >= m_size)
	{
		throw std::out_of_range("exceeding the boundaries");
	}

	return m_chars[index];
}

String String::operator+(const String& other)const
{
	return ConcatChars(m_chars, GetLength(), other.m_chars, other.GetLength());
}

String String::operator+(const std::string& other)const
{
	return ConcatChars(m_chars, GetLength(), other.c_str(), other.size());
}

String String::operator+(const char* const& other)const
{
	return ConcatChars(m_chars, GetLength(), other, strlen(other));
}

String& String::operator+=(const String& other)
{
	String res = *this + other;

	DeleteChars(m_chars);
	m_chars = res.m_chars;
	res.m_chars = nullptr;
	m_size = res.m_size;

	return *this;
}

bool String::operator==(const String& other)const
{
	return IsEqual(m_chars, GetLength(), other.m_chars, other.GetLength());
}

bool String::operator!=(const String& other)const
{
	return !(*this == other);
}

bool String::operator<(const String& other)const
{
	return IsLower(m_chars, GetLength(), other.m_chars, other.GetLength());
}

bool String::operator>(const String& other)const
{
	return !(*this <= other);
}

bool String::operator<=(const String& other)const
{
	return *this < other || *this == other;
}

bool String::operator>=(const String& other)const
{
	return !(*this < other);
}

std::ostream& operator<<(std::ostream& stream, const String& str)
{
	stream << str.m_chars;
	return stream;
}

std::istream& operator>>(std::istream& stream, String& str)
{
	std::string input;
	stream >> input;
	str = input;

	return stream;
}

String::iterator String::begin()
{
	return { m_chars };
}

String::iterator String::end()
{
	return { m_chars + m_size };
}

std::reverse_iterator<String::iterator> String::rbegin()
{
	return std::make_reverse_iterator(this->end());
}

std::reverse_iterator<String::iterator> String::rend()
{
	return std::make_reverse_iterator(this->begin());
}

String::const_iterator String::begin()const
{
	return { m_chars };
}

String::const_iterator String::end()const
{
	return { m_chars + m_size };
}

std::reverse_iterator<String::const_iterator> String::rbegin()const
{
	return std::make_reverse_iterator(this->cend());
}

std::reverse_iterator<String::const_iterator> String::rend()const
{
	return std::make_reverse_iterator(this->cbegin());
}

String::const_iterator String::cbegin()const
{
	return { m_chars };
}

String::const_iterator String::cend()const
{
	return { m_chars + m_size };
}

std::reverse_iterator<String::const_iterator> String::rcbegin()const
{
	return std::make_reverse_iterator(this->cend());
}

std::reverse_iterator<String::const_iterator> String::rcend()const
{
	return std::make_reverse_iterator(this->cbegin());
}
