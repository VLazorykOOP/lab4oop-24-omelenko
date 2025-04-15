#ifndef VECTOR_U_SHORT_H
#define VECTOR_U_SHORT_H

#pragma once
#include <iostream>

using namespace std;

class VectorUShort
{
private:
	unsigned short* data;
	int num;
	int state;
	static int objectCount;
	static unsigned short badIndexRef;
public:
	VectorUShort();
	VectorUShort(int n);
	VectorUShort(int n, unsigned short el);
	VectorUShort(int n, int i, unsigned short el);
	VectorUShort(const VectorUShort& obj);
	~VectorUShort() { if (data) delete[] data; };

	int getState() const { return state; }
	int getSize() const { return num; }
	unsigned short getData(int i) const { return data[i]; }
	static int getObjectCount() { return objectCount; }
	void setState(int a) { state = a; }
	void setSize(int a) { num = a; }
	void setData(int i, unsigned short el) { data[i] = el; };

	VectorUShort& operator=(const VectorUShort& s);
	VectorUShort& operator=(VectorUShort&& s) noexcept;
	friend istream& operator>>(istream& is, VectorUShort& s);
	friend ostream& operator<<(ostream& os, VectorUShort& s);
	friend  VectorUShort& operator--(VectorUShort&);
	friend  VectorUShort& operator--(VectorUShort&, int);
	// reload operators
	bool operator!() const;
	bool operator~() const;

	VectorUShort& operator++();
	VectorUShort& operator++(int);

	VectorUShort& operator+=(const VectorUShort& s);
	VectorUShort& operator+=(const unsigned short& s);
	VectorUShort  operator+(const VectorUShort& b);
	VectorUShort  operator+(const unsigned short& b);

	VectorUShort& operator-=(const VectorUShort& s);
	VectorUShort& operator-=(const unsigned short& s);
	VectorUShort  operator-(const VectorUShort& b);
	VectorUShort  operator-(const unsigned short& b);

	VectorUShort& operator%=(const VectorUShort& b);
	VectorUShort& operator*=(const VectorUShort& b);
	VectorUShort& operator*=(const unsigned short& b);
	VectorUShort  operator%(const VectorUShort& b);
	VectorUShort  operator*(const VectorUShort& b);
	VectorUShort  operator*(const unsigned short& b);

	VectorUShort& operator/=(const VectorUShort& b);
	VectorUShort& operator/=(const unsigned short& b);
	VectorUShort  operator/(const VectorUShort& b);
	VectorUShort  operator/(const unsigned short& b);
	
	unsigned short& operator[](int index);
	bool operator||(const VectorUShort& b);
	friend bool operator&&(const VectorUShort& a, const VectorUShort& b);
	bool operator==(const VectorUShort& a);
	bool operator!=(const VectorUShort& a);

	bool operator>(const VectorUShort& a);
	bool operator<(const VectorUShort& a);
	bool operator>=(const VectorUShort& a);
	bool operator<=(const VectorUShort& a);

	void operator()();
};

#endif