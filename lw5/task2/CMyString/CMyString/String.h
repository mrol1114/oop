#pragma once

#include "IteratorBase.h"

class String
{
public:
	String();

	String(const char* pString);
	String(const char* pString, size_t length);
	String(String const& other);
	String(String&& other)noexcept;
	String(std::string const& stlString);
	String(char*&& pString);

	~String();

	size_t GetLength()const;
	const char* GetStringData()const;
	String SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	String& operator=(const String& other);
	String& operator=(String&& other)noexcept;
	String& operator+=(const String& other);

	String operator+(const String& other)const;
	String operator+(const std::string& other)const;
	String operator+(const char* const& other)const;

	bool operator==(const String& other)const;
	bool operator!=(const String& other)const;
	bool operator<=(const String& other)const;
	bool operator>=(const String& other)const;
	bool operator>(const String& other)const;
	bool operator<(const String& other)const;

	char& operator[](size_t index);
	const char& operator[](size_t index)const;

	friend std::ostream& operator<<(std::ostream& stream, const String& str);
	friend std::istream& operator>>(std::istream& stream, String& str);

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator begin();
	iterator end();
	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

	const_iterator begin()const;
	const_iterator end()const;
	std::reverse_iterator<const_iterator> rbegin()const;
	std::reverse_iterator<const_iterator> rend()const;

	const_iterator cbegin()const;
	const_iterator cend()const;
	std::reverse_iterator<const_iterator> rcbegin()const;
	std::reverse_iterator<const_iterator> rcend()const;

private:
	char* m_chars = nullptr;
	size_t m_size = 0;
};