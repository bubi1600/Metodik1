#include "int_buffer.h"
#include <algorithm>

int_buffer::int_buffer(size_t size) : sz(size), ptr(new int[size]) {};

int_buffer::int_buffer(const int* source, size_t size) : sz(size), ptr(new int[size])
{
	std::copy(source, source + size, ptr);
};

int_buffer::int_buffer(const int_buffer& rhs) : sz(rhs.size()), ptr(new int[rhs.size()])
{
	std::copy(rhs.begin(), rhs.end(), begin());
};

int_buffer::int_buffer(int_buffer&& rhs) : sz(rhs.sz), ptr(rhs.ptr)
{
	rhs.ptr = nullptr;
	rhs.sz = 0;
};

int_buffer& int_buffer::operator =(const int_buffer& rhs)
{
	int_buffer temp(rhs);

	swap(temp);

	return *this;
};

int_buffer& int_buffer::operator =(int_buffer&& rhs)
{
	swap(rhs);

	return *this;
};

int& int_buffer::operator [](size_t index)
{
	return ptr[index];
};

const int& int_buffer::operator [](size_t index) const
{
	return ptr[index];
};

size_t int_buffer::size() const
{
	return sz;
};

int* int_buffer::begin()
{
	return ptr;
};

int* int_buffer::end()
{
	return ptr + sz;
};

const int* int_buffer::begin() const
{
	return ptr;
};

const int* int_buffer::end() const
{
	return ptr + sz;
};

int_buffer::~int_buffer()
{
	if (ptr != nullptr) delete[] ptr;
};

void int_buffer::swap(int_buffer& swap_with)
{
	std::swap(sz, swap_with.sz);
	std::swap(ptr, swap_with.ptr);
};