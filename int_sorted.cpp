#include "int_sorted.h"
#include <algorithm>

int_sorted::int_sorted(const int* source, size_t size): buff(source, size) 
{
	if (size <= 1) return;

	int_sorted temp = sort(source, source + size);

	buff = std::move(temp.buff);
}

size_t int_sorted::size() const 
{
	return buff.size();
}

int* int_sorted::insert(int value) 
{
	int_buffer tmp(buff.size() + 1);

	int* ptr2 = tmp.begin();

	for(const int* i = buff.begin(); i != buff.end(); i++) {

		if (value < *i) break;

		ptr2++;
	}

	*ptr2 = value;

	const int* preval = buff.begin();

	int* newval = buff.begin();

	for (; preval != buff.end(); ++preval, ++newval) {

		if (newval == ptr2) ++newval;

		*newval = *preval;
	}

	buff = std::move(tmp);

	return ptr2;
}

const int* int_sorted::begin() const 
{
	return buff.begin();
}

const int* int_sorted::end() const 
{
	return buff.end();
}


int_sorted int_sorted::merge(const int_sorted& merge_with) const 
{
	int_buffer merge(size() + merge_with.size());

	const int* A = begin();
	const int* B = merge_with.begin();
	int* C = merge.begin();

	for(; A != end() && B != merge_with.end(); C++)
	{
		if(*A < *B)
		{
			*C = *A;
			A++;
		}
		else
		{
			*C = *B;
			B++;
		}
	}

	for (; A != end(); A++, C++)
	{
		*C = *A;
	}
	for (; B != end(); B++, C++)
	{
		*C = *B;
	}
	
	int_sorted ret(nullptr, 0);

	ret.buff = std::move(merge);

	return ret;
}

int_sorted int_sorted::sort(const int* begin, const int* end) 
{
	if (begin == end) return int_sorted(nullptr, 0);

	if (begin == end - 1) return int_sorted(begin, 1);

	ptrdiff_t half = (end - begin) / 2; //pointer diff type

	const int* mid = begin + half;

	return sort(begin, mid).merge(sort(mid, end));
}