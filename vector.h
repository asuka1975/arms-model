#pragma once

class vector {
public:
	vector(unsigned int length);
	vector(unsigned int lenght, int* arry);
	vector(std::initializer_list<int> args);
	vector(const vector& obj);
	int& operator[](unsigned int idx);
	const int operator[](unsigned int idx)const;
	friend vector operator+(const vector& vec1, const vector& vec2);
	friend vector operator-(const vector& vec1, const vector& vec2);
	vector slice(unsigned int start, unsigned int len);
	vector& operator=(const vector& obj);
	friend std::ostream& operator<<(std::ostream& os, const vector& obj);
	friend int summation(const vector& obj);
private:
	int* array;
	const unsigned int length;
};