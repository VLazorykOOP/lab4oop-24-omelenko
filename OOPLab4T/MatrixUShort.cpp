#include "MatrixUShort.h"

int MatrixUShort::objectCount = 0;

MatrixUShort::MatrixUShort() : UShortArray(nullptr), n(0), size(0), state(0) {
    objectCount++;
}

MatrixUShort::MatrixUShort(int size) : n(size), size(size), state(0) {
    try 
    {
        UShortArray = new VectorUShort[n];
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] = VectorUShort(size);
            UShortArray[i][i] = 1;
        }
        objectCount++;
    }
    catch (...) {
        state = 2;
        UShortArray = nullptr;
        n = size = 0;
    }
}

MatrixUShort::MatrixUShort(int rows, int cols) : n(rows), size(cols), state(0) {
    try 
    {
        UShortArray = new VectorUShort[n];
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] = VectorUShort(size);
        }
        objectCount++;
    }
    catch (...) 
    {
        state = 2;
        UShortArray = nullptr;
        n = size = 0;
    }
}

MatrixUShort::MatrixUShort(int rows, int cols, unsigned short value) : n(rows), size(cols), state(0) {
    try 
    {
        UShortArray = new VectorUShort[n];
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] = VectorUShort(size, i, value);
        }
        objectCount++;
    }
    catch (...) 
    {
        state = 2;
        UShortArray = nullptr;
        n = size = 0;
    }
}

MatrixUShort::MatrixUShort(const MatrixUShort& other) : n(other.n), size(other.size), state(other.state) {
    try 
    {
        UShortArray = new VectorUShort[n];
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] = other.UShortArray[i];
        }
        objectCount++;
    }
    catch (...) 
    {
        state = 2;
        UShortArray = nullptr;
        n = size = 0;
    }
}

MatrixUShort::~MatrixUShort() {
    delete[] UShortArray;
    objectCount--;
}

MatrixUShort& MatrixUShort::operator=(const MatrixUShort& other) 
{
    if (this != &other) 
    {
        delete[] UShortArray;
        n = other.n;
        size = other.size;
        state = other.state;
        try 
        {
            UShortArray = new VectorUShort[n];
            for (int i = 0; i < n; ++i)
            {
                UShortArray[i] = other.UShortArray[i];
            }
        }
        catch (...) 
        {
            state = 2;
            UShortArray = nullptr;
            n = size = 0;
        }
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator++() 
{
    for (int i = 0; i < n; ++i) 
    {
        ++UShortArray[i];
    }
    return *this;
}

MatrixUShort MatrixUShort::operator++(int) 
{
    MatrixUShort temp(*this);
    ++(*this);
    return temp;
}

MatrixUShort& MatrixUShort::operator--() 
{
    for (int i = 0; i < n; ++i) 
    {
        --UShortArray[i];
    }
    return *this;
}

MatrixUShort MatrixUShort::operator--(int) 
{
    MatrixUShort temp(*this);
    --(*this);
    return temp;
}

bool MatrixUShort::operator!() const {
    return n != 0 && size != 0;
}

MatrixUShort MatrixUShort::operator~() const {
    MatrixUShort result(n, size);
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            result.UShortArray[i][j] = ~UShortArray[i][j];
        }
    }
    return result;
}

MatrixUShort MatrixUShort::operator-() const 
{
    MatrixUShort result(n, size);
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            result.UShortArray[i][j] = -UShortArray[i][j];
        }
    }
    return result;
}

MatrixUShort MatrixUShort::operator+(const MatrixUShort& other) {
    MatrixUShort res(*this);
    if (n == other.n && size == other.size) 
    {
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < res.UShortArray[i].getSize(); j++)
            {
                res.UShortArray[i][j] += other.UShortArray[i][j];
            }
            //cout << UShortArray[i];
            //cout << other.UShortArray[i];
            //UShortArray[i] = UShortArray[i] + other.UShortArray[i];
            //cout << UShortArray[i];
        }
    }
    else 
    {
        res.state = 1;
    }
    return res;
}

MatrixUShort MatrixUShort::operator+(const unsigned short& scalar) {
    for (int i = 0; i < n; ++i) 
    {
        UShortArray[i] += scalar;
    }
    return *this;
}

MatrixUShort MatrixUShort::operator-(const MatrixUShort& other) {
    MatrixUShort result(n, size);
    if (n == other.n && size == other.size) 
    {
        for (int i = 0; i < n; ++i) 
        {
            result.UShortArray[i] = UShortArray[i] - other.UShortArray[i];
        }
    }
    else 
    {
        result.state = 1;
    }
    return result;
}

MatrixUShort MatrixUShort::operator-(const unsigned short& scalar) {
    MatrixUShort result(*this);
    for (int i = 0; i < n; ++i) 
    {
        result.UShortArray[i] -= scalar;
    }
    return result;
}

MatrixUShort MatrixUShort::operator*(const MatrixUShort& other) {
    MatrixUShort result(n, other.size);
    if (size == other.n) 
    {
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < other.size; ++j) 
            {
                unsigned short sum = 0;
                for (int k = 0; k < size; ++k) 
                {
                    sum += UShortArray[i][k] * other.UShortArray[k][j];
                }
                result.UShortArray[i][j] = sum;
            }
        }
    }
    else {
        result.state = 1;
    }
    return result;
}

VectorUShort MatrixUShort::operator*(const VectorUShort& vec) {
    VectorUShort result(n);
    VectorUShort vec1(vec);
    unsigned short sum = 0;
    if (size == vec1.getSize()) 
    {
        for (int i = 0; i < n; ++i) 
        {
            sum = 0;
            for (int j = 0; j < size; ++j) 
            {
                sum += UShortArray[i][j] * vec1.getData(j);
                //cout << UShortArray[i][j] << endl;
                //cout << vec1.getData(j) << endl;
                //cout << sum << endl;
            }
            result[i] = static_cast<unsigned short>(sum);

            //cout << sum << endl;
            //cout << result[i] << endl;
        }
    }
    else 
    {
        result.setState(1);
    }
    //cout << result;
    return result;
}

MatrixUShort MatrixUShort::operator*(const unsigned short& scalar) {
    for (int i = 0; i < n; i++) 
    {
        UShortArray[i] *= scalar;
    }
    return *this;
}

MatrixUShort MatrixUShort::operator/(const unsigned short& scalar) {
    MatrixUShort result(*this);
    if (scalar != 0) 
    {
        for (int i = 0; i < n; ++i) 
        {
            result.UShortArray[i] /= scalar;
        }
    }
    else 
    {
        result.state = 1;
    }
    return result;
}

MatrixUShort MatrixUShort::operator%(const unsigned short& scalar) {
    MatrixUShort result(*this);
    if (scalar != 0) 
    {
        for (int i = 0; i < n; ++i) 
        {
            result.UShortArray[i] %= scalar;
        }
    }
    else 
    {
        result.state = 1;
    }
    return result;
}

MatrixUShort& MatrixUShort::operator+=(const MatrixUShort& other) {
    if (n == other.n && size == other.size) 
    {
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] += other.UShortArray[i];
        }
    }
    else 
    {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator+=(const unsigned short& scalar) {
    for (int i = 0; i < n; ++i) 
    {
        UShortArray[i] += scalar;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator-=(const MatrixUShort& other) {
    if (n == other.n && size == other.size) 
    {
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] -= other.UShortArray[i];
        }
    }
    else 
    {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator-=(const unsigned short& scalar) {
    for (int i = 0; i < n; ++i) 
    {
        UShortArray[i] -= scalar;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator*=(const MatrixUShort& other) {
    *this = *this * other;
    return *this;
}

MatrixUShort& MatrixUShort::operator*=(const VectorUShort& vec) {
    VectorUShort result = *this * vec;
    if (result.getState() == 0) 
    {
        // Assuming we want to store result in a compatible way, but matrix *= vector is unusual
        state = 1; // Not standard operation
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator*=(const unsigned short& scalar) {
    for (int i = 0; i < n; i++) 
    {
        UShortArray[i] *= scalar;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator/=(const unsigned short& scalar) {
    if (scalar != 0) 
    {
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] /= scalar;
        }
    }
    else 
    {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator%=(const unsigned short& scalar) {
    if (scalar != 0) 
    {
        for (int i = 0; i < n; ++i) 
        {
            UShortArray[i] %= scalar;
        }
    }
    else 
    {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator>>=(const MatrixUShort& other) {
    if (n == other.n && size == other.size) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < size; ++j) {
                UShortArray[i][j] >>= other.UShortArray[i][j];
            }
        }
    }
    else {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator>>=(const unsigned short& scalar) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) {
            UShortArray[i][j] >>= scalar;
        }
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator<<=(const MatrixUShort& other) {
    if (n == other.n && size == other.size) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < size; ++j) {
                UShortArray[i][j] <<= other.UShortArray[i][j];
            }
        }
    }
    else {
        state = 1;
    }
    return *this;
}

MatrixUShort& MatrixUShort::operator<<=(const unsigned short& scalar) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) {
            UShortArray[i][j] <<= scalar;
        }
    }
    return *this;
}

bool MatrixUShort::operator==(const MatrixUShort& other) {
    if (n != other.n || size != other.size) return false;
    for (int i = 0; i < n; ++i) 
    {
        if (!(UShortArray[i] == other.UShortArray[i])) return false;
    }
    return true;
}

bool MatrixUShort::operator!=(const MatrixUShort& other) {
    return !(*this == other);
}

bool MatrixUShort::operator>(const MatrixUShort& other) {
    if (n != other.n || size != other.size) return false;
    for (int i = 0; i < n; ++i) 
    {
        if (UShortArray[i] <= other.UShortArray[i]) return false;
    }
    return true;
}

bool MatrixUShort::operator>=(const MatrixUShort& other) {
    if (n != other.n || size != other.size) return false;
    for (int i = 0; i < n; ++i) 
    {
        if (UShortArray[i] < other.UShortArray[i]) return false;
    }
    return true;
}

bool MatrixUShort::operator<(const MatrixUShort& other) {
    if (n != other.n || size != other.size) return false;
    for (int i = 0; i < n; ++i) 
    {
        if (UShortArray[i] >= other.UShortArray[i]) return false;
    }
    return true;
}

bool MatrixUShort::operator<=(const MatrixUShort& other) {
    if (n != other.n || size != other.size) return false;
    for (int i = 0; i < n; ++i) 
    {
        if (UShortArray[i] > other.UShortArray[i]) return false;
    }
    return true;
}

VectorUShort& MatrixUShort::operator[](int index) {
    if (index >= 0 && index < n) 
    {
        state = 0;
        return UShortArray[index];
    }
    state = 1;
    return UShortArray[n - 1]; // Повертаємо останній елемент при помилці
}

void MatrixUShort::operator()() {
    std::cout << *this;
}

std::istream& operator>>(std::istream& is, MatrixUShort& matrix) {
    int rows, cols;
    std::cout << "Enter rows and columns: ";
    is >> rows >> cols;
    MatrixUShort temp(rows, cols);
    for (int i = 0; i < rows; ++i) {
        std::cout << "Enter row " << i + 1 << " (" << cols << " elements): ";
        is >> temp.UShortArray[i];
    }
    matrix = temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const MatrixUShort& matrix) {
    if (matrix.n == 0 || matrix.size == 0) {
        os << "Empty matrix\n";
        return os;
    }
    for (int i = 0; i < matrix.n; ++i) {
        os << matrix.UShortArray[i];
    }
    return os;
}

MatrixUShort operator>>(const MatrixUShort& matrix, unsigned short shift) {
    MatrixUShort result(matrix);
    result >>= shift;
    return result;
}

MatrixUShort operator<<(const MatrixUShort& matrix, unsigned short shift) {
    MatrixUShort result(matrix);
    result <<= shift;
    return result;
}