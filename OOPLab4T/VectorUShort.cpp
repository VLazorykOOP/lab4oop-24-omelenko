#include "VectorUShort.h"
#include <string>
int VectorUShort::objectCount = 0;
const double EpsCalculations = 1.e-5;
unsigned short VectorUShort::badIndexRef = 0;

// States:
// 0 - working
// 1 - index out of bounds
// 2 - out of memory

VectorUShort::VectorUShort()
{
	data = new unsigned short[1];
	data[0] = 0;
	num = 1;
	state = 0;
	objectCount++;
}

VectorUShort::VectorUShort(int n) {
	if (n <= 0) n = 2;  // default num =2;
	num = n;
	data = new unsigned short[n];
	for (int i = 0; i < n; i++) 
	{
		data[i] = 0;
	}
	objectCount++;
	state = 0;
}

VectorUShort::VectorUShort(int n, unsigned short el)
{
	if (n <= 0) n = 2;  // default num =2;
	num = n;
	data = new unsigned short[n];
	data[0] = el;
	for (int i = 1; i < n; i++) 
	{
		data[i] = 0;
	}
	objectCount++;
	state = 0;
}

VectorUShort::VectorUShort(int n, int i, unsigned short el)
{
	if (n <= 0) n = 2;  // default num =2;
	num = n;
	data = new unsigned short[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = 0;
	}
	data[i] = el;
	objectCount++;
	state = 0;
}

VectorUShort::VectorUShort(const VectorUShort& obj)
{
	data = obj.data;
	num = obj.num;
	state = obj.state;
	objectCount++;
}

VectorUShort& VectorUShort::operator=(const VectorUShort& s) {
	if (this == &s) return *this;
	if (num != s.num)
	{
		if (data) delete[] data;
		num = s.num;
		data = new unsigned short[num];
		state = 1;
	}
	for (int i = 0; i < num; i++) data[i] = s.data[i];
	return *this;
}
VectorUShort& VectorUShort::operator=(VectorUShort&& s) noexcept
{
	if (this == &s) return *this;
	num = s.num; state = s.state;
	if (this->data != nullptr) delete[] data;
	data = s.data;
	s.num = 0; s.data = nullptr; s.state = -1;
	return *this;
}

bool VectorUShort::operator!() const   // true : exist data[i] != 0
{
	for (int i = 0; i < num; i++)
		if (data[i] > EpsCalculations)
			return true;
	return false;
}
bool VectorUShort::operator~() const  // true : all  data[i] != 0
{
	for (int i = 0; i < num; i++)
		if (data[i] < EpsCalculations)
			return false;
	return true;
}

unsigned short& VectorUShort::operator[](int index)
{
	if (index >= 0 && index < num) return data[index];
	cout << " Error : operator[] - index out of range \n";
	state = 1;
	return badIndexRef;
}

VectorUShort& VectorUShort::operator++()
{
	for (int i = 0; i < num; i++) data[i] += 1;
	return *this;
}
VectorUShort& VectorUShort::operator++(int)
{
	for (int i = 0; i < num; i++) data[i] += unsigned short(1);
	return *this;
}

VectorUShort& VectorUShort::operator+=(const VectorUShort& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++)
	{
		//cout << data[i] << endl;
		//cout << b.data[i] << endl;
		data[i] += b.data[i];
		//cout << data[i] << endl;
	}
	else
	{
		cout << " Warning: data vectors of different sizes are used in operation += \n";
		if (num < b.num) {
			unsigned short* tmp;
			tmp = new unsigned short[b.num];
			for (i = 0; i < num; i++) tmp[i] = data[i] + b.data[i];
			for (; i < b.num; i++) tmp[i] = b.data[i];
			num = b.num;
			if (data != nullptr) delete[] data;
			data = tmp;
		}
		else for (i = 0; i < b.num; i++) data[i] += b.data[i];
	}
	return *this;
}
VectorUShort& VectorUShort::operator+=(const unsigned short& b)
{
	if (num > 0) {
		for (int i = 0; i < num; i++) data[i] += b;
	}
	return *this;
}

VectorUShort VectorUShort::operator+(const VectorUShort& b)
{
	*this += b;
	return *this;
}
VectorUShort VectorUShort::operator+(const unsigned short& b)
{
	*this += b;
	return *this;
}

VectorUShort& VectorUShort::operator-=(const VectorUShort& b)
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) data[i] -= b.data[i];
	else {
		cout << " Warning: data vectors of different sizes are used in operation -= \n";
		if (num < b.num) {
			unsigned short* tmp;
			tmp = new unsigned short[b.num];
			for (i = 0; i < num; i++) tmp[i] = data[i] - b.data[i];
			for (; i < b.num; i++) tmp[i] = -b.data[i];
			num = b.num;
			if (data != nullptr) delete[] data;
			data = tmp;
		}
		else 	for (i = 0; i < b.num; i++) data[i] -= b.data[i];
	}
	return *this;
}
VectorUShort& VectorUShort::operator-=(const unsigned short& b)
{
	if (num > 0) 
	{
		for (int i = 0; i < num; i++)
		{
			if (data[i] - b > 0)
			{
				data[i] -= b;
			}
		}
	}
	return *this;
}

VectorUShort VectorUShort::operator-(const VectorUShort& b)
{
	*this -= b;
	return *this;
}
VectorUShort VectorUShort::operator-(const unsigned short& b)
{
	*this -= b;
	return *this;
}

VectorUShort& VectorUShort::operator*=(const VectorUShort& b)  //  r= a0*b0+a1*b1+...+an-1*bn-1
{
	if (num != b.num) { cout << " Error : data vectors of different sizes are used in operation *= \n"; return *this; }
	for (int i = 0; i < num; i++) data[i] = data[i] * b.data[i];
	return *this;
}
VectorUShort& VectorUShort::operator%=(const  VectorUShort& b)  // (a0*b0, a1*b1,...,an-1*bn-1)
{
	if (num != b.num) { cout << " Error : data vectors of different sizes are used in operation %= \n"; return *this; }
	for (int i = 0; i < num; i++)
	{
		if (b.data[i] == 0)
		{
			cout << "\n\nError: division by zero\n\n";
		}
		else
		{
			data[i] %= b.data[i];
		}
	}
	return *this;
}
VectorUShort& VectorUShort::operator*=(const unsigned short& b) {
	for (int i = 0; i < num; i++)
	{
		data[i] *= b;
	}
	return *this;
}
VectorUShort VectorUShort::operator%(const VectorUShort& b)  // (a0*b0, a1*b1,...,an-1*bn-1)
{
	*this %= b;
	return *this;
}
VectorUShort VectorUShort::operator*(const unsigned short& b) {

	*this *= b;
	return *this;
}
VectorUShort VectorUShort::operator*(const VectorUShort& b)  //  r= a0*b0+a1*b1+...+an-1*bn-1
{
	int i;
	if (num == b.num) for (i = 0; i < num; i++) data[i] *= b.data[i];
	else
	{
		cout << " Warning: data vectors of different sizes are used in operation += \n";
		if (num < b.num) {
			unsigned short* tmp;
			tmp = new unsigned short[b.num];
			for (i = 0; i < num; i++) tmp[i] = data[i] * b.data[i];
			for (; i < b.num; i++) tmp[i] = b.data[i];
			num = b.num;
			if (data != nullptr) delete[] data;
			data = tmp;
		}
		else for (i = 0; i < b.num; i++) data[i] *= b.data[i];
	}
	return *this;
}
VectorUShort& VectorUShort::operator/=(const VectorUShort& b)  // (a0/b0, a1/b1,...,an-1/bn-1)
{
	if (num != b.num || ~b) {
		cout << " Error: data vectors of different sizes are used or b is zer0 opreation %= \n";
		return *this;
	}
	for (int i = 0; i < num; i++)
	{
		if (b.data[i] == 0)
		{
			cout << "\n\nError: division by zero\n\n";
		}
		else
		{
			data[i] /= b.data[i];
		}
	}
	return *this;
}
VectorUShort& VectorUShort::operator/=(const unsigned short& b)
{
	if (fabs(b) < EpsCalculations)
	{
		cout << " Error Vector opreation /= b \n";
	}
	else for (int i = 0; i < num; i++) data[i] /= b;
	return *this;
}
VectorUShort VectorUShort::operator/(const VectorUShort& b)  // (a0/b0, a1/b1,...,an-1/bn-1)
{
	*this /= b;
	return *this;
}
VectorUShort VectorUShort::operator/(const unsigned short& b) {

	*this /= b;
	return *this;
}

bool VectorUShort::operator||(const VectorUShort& b)
{
	if (this->num > 0 || b.num > 0) return true;
	return false;
}

bool VectorUShort::operator==(const VectorUShort& s)
{
	bool ret = true;
	if (num != s.num) return false;
	for (int i = 0; i < num && ret; i++) 
		if (data[i] - s.data[i] != 0) ret = false;
	return ret;
}

bool VectorUShort::operator!=(const VectorUShort& s)
{
	return !(*this == s);
}

istream& operator>>(istream& is, VectorUShort& s) {
	for (int i = 0; i < s.num; i++)
	{
#if defined(_MSC_VER)
		is >> s.data[i];
#else 
		double re;
		is >> re;
		s.data[i] = re;
#endif		
	}
	return is;
};
ostream& operator<<(ostream& os, VectorUShort& s) {
	for (int i = 0; i < s.num; i++)
		os << s.data[i] << '\t';
	os << endl;
	return os;
}

VectorUShort& operator--(VectorUShort& s)
{
	s -= 1.0;
	return s;
}

VectorUShort&  operator--(VectorUShort& s, int)
{
	s -= unsigned short(1);
	return s;
}

bool  operator&&(const VectorUShort& a, const VectorUShort& b)
{
	if (a.num > 0 && b.num > 0) return true;
	return false;

}

bool VectorUShort::operator>(const VectorUShort& a)
{
	unsigned short max = 0;
	unsigned short amax = 0;
	if (num > 0 && a.num > 0) 
	{
		for (int i = 0; i < num; i++)
			if (data[i] > max)
				max = data[i];
		for (int i = 0; i < a.num; i++)
			if (a.data[i] > amax)
				amax = a.data[i]; 
		
		if (max > amax) return true;
	}
	return false;
}
bool VectorUShort::operator<(const VectorUShort& a)
{
	unsigned short max = 0;
	unsigned short amax = 0;
	if (num > 0 && a.num > 0)
	{
		for (int i = 0; i < num; i++)
			if (data[i] > max)
				max = data[i];
		for (int i = 0; i < a.num; i++)
			if (a.data[i] > amax)
				amax = a.data[i];

		if (max > amax) return false;
	}
	return true;
}
bool VectorUShort::operator>=(const VectorUShort& a)
{
	unsigned short max = 0;
	unsigned short amax = 0;
	if (num > 0 && a.num > 0)
	{
		for (int i = 0; i < num; i++)
			if (data[i] >= max)
				max = data[i];
		for (int i = 0; i < a.num; i++)
			if (a.data[i] >= amax)
				amax = a.data[i];

		if (max >= amax) return true;
	}
	return false;
}
bool VectorUShort::operator<=(const VectorUShort& a)
{
	unsigned short max = 0;
	unsigned short amax = 0;
	if (num > 0 && a.num > 0)
	{
		for (int i = 0; i < num; i++)
			if (data[i] >= max)
				max = data[i];
		for (int i = 0; i < a.num; i++)
			if (a.data[i] >= amax)
				amax = a.data[i];

		if (max >= amax) return false;
	}
	return true;
}

void VectorUShort::operator()()
{
	for (int i = 0; i < num; i++)
	{
		cout << "data[" + to_string(i) + "] = " + to_string(data[i]) + "\n";
	}
	cout << "Num = " + to_string(num) + "\n";
	cout << "State = " + to_string(state) + "\n";
}