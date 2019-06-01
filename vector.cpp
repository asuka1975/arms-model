#include <iostream>
#include "vector.h"

static int ___;

vector::vector(unsigned int len) : length(len), array(new int[len])
{
	for (int i = 0; i < length; i++) array[i] = 0;
}

vector::vector(unsigned int len, int * arry) : length(len), array(new int[len])
{
	for (int i = 0; i < length; i++) array[i] = arry[i];
}

vector::vector(std::initializer_list<int> args) : length(args.size()), array(new int [args.size()])
{
	int i = 0;
	for (int val : args) {
		array[i] = val;
		i++;
	}
}

vector::vector(const vector & obj):length(obj.length), array(new int[obj.length])
{
	for (int i = 0; i < length; i++)array[i] = obj[i];
}

int & vector::operator[](unsigned int idx)
{
	if (idx < length) {
		return array[idx];
	}
	else return ___;
}

const int vector::operator[](unsigned int idx) const
{
	if (idx < length) {
		return array[idx];
	}
	return 0;
}

vector vector::slice(unsigned int start, unsigned int len)
{
	vector vec(len);
	for (int i = start; i < start + len; i++) {
		vec[i - start] = (*this)[i];
	}

	return vec;
}

vector & vector::operator=(const vector & obj)
{
	for (int i = 0; i < length; i++) (*this)[i] = obj[i];
	return *this;
}

vector operator+(const vector & vec1, const vector & vec2)
{
	vector vec(vec1.length);
	for (int i = 0; i < vec.length; i++)vec[i] = vec1[i] + vec2[i];
	return vec;
}

vector operator-(const vector & vec1, const vector & vec2)
{
	vector vec(vec1.length);
	for (int i = 0; i < vec.length; i++)vec[i] = vec1[i] - vec2[i];
	return vec;
}

std::ostream & operator<<(std::ostream & os, const vector & obj)
{
	os << "{ ";
	for (int i = 0; i < obj.length; i++) os << obj[i] << ", ";
	os << "\b\b }";
	return os;
}

int summation(const vector & obj)
{
	int sum = 0;
	for (int i = 0; i < obj.length; i++) sum += obj[i];
	return sum;
}
