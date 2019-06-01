#pragma once

#include <functional>

class vector {
public:
	vector(unsigned int length);
	vector(unsigned int lenght, double* arry);
	vector(std::initializer_list<double> args);
	vector(const vector& obj);
	double& operator[](unsigned int idx);
	const double operator[](unsigned int idx)const;
	friend vector operator+(const vector& vec1, const vector& vec2);
	friend vector operator-(const vector& vec1, const vector& vec2);
	friend double operator*(const vector& vec1, const vector& vec2);
	vector slice(unsigned int start, unsigned int len)const;
	vector& operator=(const vector& obj);
	friend std::ostream& operator<<(std::ostream& os, const vector& obj);
	friend double summation(const vector& obj);
	friend vector map(std::function<double(double)> func, const vector& obj);
	friend vector map2(std::function<double(double, double)> func, const vector& left, const vector& right);
	friend double foldr(std::function<double(double, double)> func, double g, const vector& obj);
private:
	double* array;
	const unsigned int length;
};