#include <iostream>
#include "vector.h"

static double ___;

vector::vector(unsigned int len) : length(len), array(new double[len])
{
	for (int i = 0; i < length; i++) array[i] = 0;
}

vector::vector(unsigned int len, double * arry) : length(len), array(new double[len])
{
	for (int i = 0; i < length; i++) array[i] = arry[i];
}

vector::vector(std::initializer_list<double> args) : length(args.size()), array(new double [args.size()])
{
	int i = 0;
	for (auto val : args) {
		array[i] = val;
		i++;
	}
}

vector::vector(const vector & obj):length(obj.length), array(new double[obj.length])
{
	for (int i = 0; i < length; i++)array[i] = obj[i];
}

double & vector::operator[](unsigned int idx)
{
	if (idx < length) {
		return array[idx];
	}
	else return ___;
}

const double vector::operator[](unsigned int idx) const
{
	if (idx < length) {
		return array[idx];
	}
	return 0;
}

vector vector::slice(unsigned int start, unsigned int len)const 
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

double operator*(const vector & vec1, const vector & vec2)
{
	double dot = 0.0;
	for (int i = 0; i < vec1.length; i++) {
		dot += vec1[i] * vec2[i];
	}

	return dot;
}

std::ostream & operator<<(std::ostream & os, const vector & obj)
{
	os << "{ ";
	for (int i = 0; i < obj.length; i++) os << obj[i] << ", ";
	os << "\b\b }";
	return os;
}

double summation(const vector & obj)
{
	int sum = 0;
	for (int i = 0; i < obj.length; i++) sum += obj[i];
	return sum;
}

vector map(std::function<double(double)> func, const vector & obj)
{
	vector vec(obj.length);

	for (int i = 0; i < obj.length; i++) {
		vec[i] = func(obj[i]);
	}

	return vec;
}

vector map2(std::function<double(double, double)> func, const vector & left, const vector & right)
{
	vector vec(left.length < right.length ? left.length : right.length);

	for (int i = 0; i < vec.length; i++) {
		vec[i] = func(left[i], right[i]);
	}

	return vec;
}

double foldr(std::function<double(double, double)> func, double g, const vector & obj)
{
	if (!obj.length) return g;
	return func(obj[0], foldr(func, g, obj.slice(1, obj.length - 1)));
}
