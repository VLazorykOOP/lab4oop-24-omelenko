#include <iostream>
#include "Tasks.h"
#include "VectorUShort.h"
#include "BusSchedule.h"
#include <cassert>
#include <string>
#include "MatrixUShort.h"

using namespace std;

int task1()
{
cout << "=== Starting VectorUShort Test Suite ===\n\n";

// Test 1: Default Constructor
cout << "Test 1: Default Constructor\n";
VectorUShort v1;
cout << "v1: " << v1 << "Expected: [0]\n";
assert(v1[0] == 0 && "Default constructor should initialize with one zero element");

// Test 2: Constructor with size
cout << "\nTest 2: Constructor with size (n=3)\n";
VectorUShort v2(3);
cout << "v2: " << v2 << "Expected: [0, 0, 0]\n";
assert(v2[0] == 0 && v2[1] == 0 && v2[2] == 0 && "Size constructor should initialize with zeros");

// Test 3: Constructor with size and element
cout << "\nTest 3: Constructor with size (n=3) and element (5)\n";
VectorUShort v3(3, 5);
cout << "v3: " << v3 << "Expected: [5, 0, 0]\n";
assert(v3[0] == 5 && v3[1] == 0 && v3[2] == 0 && "Element constructor should set first element");

// Test 4: Copy Constructor
cout << "\nTest 4: Copy Constructor\n";
VectorUShort v4(v3);
cout << "v4 (copy of v3): " << v4 << "Expected: [5, 0, 0]\n";
assert(v4[0] == 5 && v4[1] == 0 && v4[2] == 0 && "Copy constructor should create identical vector");

// Test 5: Assignment Operator
cout << "\nTest 5: Assignment Operator\n";
VectorUShort v5;
v5 = v3;
cout << "v5 (assigned v3): " << v5 << "Expected: [5, 0, 0]\n";
assert(v5[0] == 5 && v5[1] == 0 && v5[2] == 0 && "Assignment operator should copy vector");

// Test 6: Move Assignment Operator
cout << "\nTest 6: Move Assignment Operator\n";
VectorUShort v6;
v6 = VectorUShort(2, 10);
cout << "v6 (moved): " << v6 << "Expected: [10, 0]\n";
assert(v6[0] == 10 && v6[1] == 0 && "Move assignment should transfer data");

// Test 7: Index Operator (valid and invalid)
cout << "\nTest 7: Index Operator\n";
v3[1] = 7;
cout << "v3 after v3[1] = 7: " << v3 << "Expected: [5, 7, 0]\n";
assert(v3[1] == 7 && "Index operator should set value");
cout << "Accessing invalid index (v3[5]): ";
v3[5]; // Should print error and set state to 1
assert(v3.getState() == 1 && "Invalid index should set state to 1");

// Test 8: Increment Operators
cout << "\nTest 8: Increment Operators\n";
++v3;
cout << "v3 after ++v3: " << v3 << "Expected: [6, 8, 1]\n";
assert(v3[0] == 6 && v3[1] == 8 && v3[2] == 1 && "Prefix increment should add 1");
v3++;
cout << "v3 after v3++: " << v3 << "Expected: [7, 9, 2]\n";
assert(v3[0] == 7 && v3[1] == 9 && v3[2] == 2 && "Postfix increment should add 1");

// Test 9: Addition Operators
cout << "\nTest 9: Addition Operators\n";
VectorUShort v7(3, 2); // [2, 0, 0]
v7 += v3; // v3 = [7, 9, 2]
cout << "v7 after v7 += v3: " << v7 << "Expected: [9, 9, 2]\n";
assert(v7[0] == 9 && v7[1] == 9 && v7[2] == 2 && "Vector addition should sum elements");
VectorUShort v8 = v7 + VectorUShort(3, 1);
cout << "v8 = v7 + [1, 0, 0]: " << v8 << "Expected: [10, 9, 2]\n";
assert(v8[0] == 10 && "Vector + vector should sum correctly");
v8 += (unsigned short)5;
cout << "v8 after v8 += 5: " << v8 << "Expected: [15, 14, 7]\n";
assert(v8[0] == 15 && "Scalar addition should add to all elements");

// Test 10: Subtraction Operators
cout << "\nTest 10: Subtraction Operators\n";
VectorUShort v9(3, 10); // [10, 0, 0]
v9 -= VectorUShort(3, 2); // [2, 0, 0]
cout << "v9 after v9 -= [2, 0, 0]: " << v9 << "Expected: [8, 0, 0]\n";
assert(v9[0] == 8 && "Vector subtraction should subtract elements");
VectorUShort v10 = v9 - (unsigned short)3;
cout << "v10 = v9 - 3: " << v10 << "Expected: [5, 0, 0]\n";
assert(v10[0] == 5 && "Scalar subtraction should subtract from all elements");

// Test 11: Multiplication Operators
cout << "\nTest 11: Multiplication Operators\n";
VectorUShort v11(3, 2); // [2, 0, 0]
v11 *= VectorUShort(3, 3); // [3, 0, 0]
cout << "v11 after v11 *= [3, 0, 0]: " << v11 << "Expected: [6, 0, 0]\n";
assert(v11[0] == 6 && "Element-wise multiplication should multiply elements");
VectorUShort v12 = v11 * (unsigned short)2;
cout << "v12 = v11 * 2: " << v12 << "Expected: [12, 0, 0]\n";
assert(v12[0] == 12 && "Scalar multiplication should multiply all elements");

// Test 12: Division Operators
cout << "\nTest 12: Division Operators\n";
VectorUShort v13(3, 10); // [10, 0, 0]
v13 /= VectorUShort(3, 2); // [2, 0, 0]
cout << "v13 after v13 /= [2, 0, 0]: " << v13 << "Expected: [5, 0, 0]\n";
assert(v13[0] == 5 && "Element-wise division should divide elements");
cout << "Attempting division by zero: ";
v13 /= (unsigned short)0; // Should print error
VectorUShort v14 = v13 / (unsigned short)5;
cout << "v14 = v13 / 5: " << v14 << "Expected: [1, 0, 0]\n";
assert(v14[0] == 1 && "Scalar division should divide all elements");

// Test 13: Modulo Operator
cout << "\nTest 13: Modulo Operator\n";
VectorUShort v15(3, 7); // [7, 0, 0]
v15 %= VectorUShort(3, 3); // [3, 0, 0]
cout << "v15 after v15 %= [3, 0, 0]: " << v15 << "Expected: [1, 0, 0]\n";
assert(v15[0] == 1 && "Modulo should compute remainders");

// Test 14: Logical Operators
cout << "\nTest 14: Logical Operators\n";
VectorUShort v16(3, 0); // [0, 0, 0]
VectorUShort v17(3, 1); // [1, 0, 0]
cout << "!v16 (all zeros): " << !v16 << " Expected: 0\n";
assert(!v16 == false && "Operator ! should return false for all zeros");
cout << "!v17 (some non-zero): " << !v17 << " Expected: 1\n";
assert(!v17 == true && "Operator ! should return true for some non-zero");
cout << "~v17 (not all non-zero): " << ~v17 << " Expected: 0\n";
assert(~v17 == false && "Operator ~ should return false if not all non-zero");
cout << "v16 || v17: " << (v16 || v17) << " Expected: 1\n";
assert((v16 || v17) == true && "Operator || should return true if either has elements");
cout << "v16 && v17: " << (v16 && v17) << " Expected: 1\n";
assert((v16 && v17) == true && "Operator && should return true if both have elements");

// Test 15: Comparison Operators
cout << "\nTest 15: Comparison Operators\n";
VectorUShort v18(3, 5); // [5, 0, 0]
VectorUShort v19(3, 6); // [6, 0, 0]
cout << "v18 == v18: " << (v18 == v18) << " Expected: 1\n";
assert(v18 == v18 && "Vectors should be equal to themselves");
cout << "v18 != v19: " << (v18 != v19) << " Expected: 1\n";
assert(v18 != v19 && "Different vectors should not be equal");
cout << "v18 < v19: " << (v18 < v19) << " Expected: 1\n";
assert(v18 < v19 && "Vector with smaller max should be less");
cout << "v19 > v18: " << (v19 > v18) << " Expected: 1\n";
assert(v19 > v18 && "Vector with larger max should be greater");

// Test 16: Decrement Operators
cout << "\nTest 16: Decrement Operators\n";
VectorUShort v20(3, 5); // [5, 0, 0]
--v20;
cout << "v20 after --v20: " << v20 << "Expected: [4, 0, 0]\n";
assert(v20[0] == 4 && "Prefix decrement should subtract 1");
v20--;
cout << "v20 after v20--: " << v20 << "Expected: [3, 0, 0]\n";
assert(v20[0] == 3 && "Postfix decrement should subtract 1");

// Test 17: Display Function
cout << "\nTest 17: Display Function\n";
cout << "Calling v20(): ";
v20();
// Manual verification: Check console output for correct format

// Test 18: Object Count
cout << "\nTest 18: Object Count\n";
int count = VectorUShort::getObjectCount();
cout << "Object count: " << count << "\n";
assert(count > 0 && "Object count should be positive after creating vectors");

cout << "\n=== All Tests Completed ===\n";
return 2;
}

int task2()
{
    cout << "=== Testing class BusSchedule ===\n\n";

    cout << "Test 1: Empty schedule\n";
    BusSchedule schedule;
    cout << schedule;
    assert(schedule.getCodeError() == 0 && "Starting error code must be 0");

    // Test 2: Додавання рейсів
    cout << "\nTest 2: Adding journey\n";
    schedule.addEntry("F123", Time(10, 30));
    schedule.addEntry("F456", Time(15, 45));
    cout << schedule;
    assert(schedule.getCodeError() == 0 && "Adding shouldn't throw an error");

    // Test 3: Доступ через оператор []
    cout << "\nTest 3: Operator []\n";
    Time& t1 = schedule["F123"];
    cout << "Time for F123: " << t1.hours << ":" << t1.minutes << "\n";
    assert(t1.hours == 10 && t1.minutes == 30 && schedule.getCodeError() == 0 && "Access to existing journey");

    Time& t2 = schedule["F999"];
    cout << "Time for F999: " << t2.hours << ":" << t2.minutes << "\n";
    assert(schedule.getCodeError() == 1 && "Unknown journey should make CodeError=1");

    // Test 4: Доступ через оператор ()
    cout << "\nTest 4: Operator ()\n";
    Time& t3 = schedule("F456");
    cout << "Time for F456: " << t3.hours << ":" << t3.minutes << "\n";
    assert(t3.hours == 15 && t3.minutes == 45 && schedule.getCodeError() == 0 && "Access through () to an existing journey");

    Time& t4 = schedule("F000");
    cout << "Time for F000: " << t4.hours << ":" << t4.minutes << "\n";
    assert(schedule.getCodeError() == 1 && "Unknown journey thorugh () should make CodeError=1");

    // Test 5: Введення/виведення
    cout << "\nTest 5: Input/output\n";
    BusSchedule newSchedule;
    // Симулюємо введення: зазвичай це інтерактивно, тут просто додаємо
    newSchedule.addEntry("F789", Time(12, 0));
    cout << newSchedule;
    assert(newSchedule.getCodeError() == 0 && "Input shouldn't throw an error");

    cout << "\n=== Testing succeded ===\n";
	return 3;
}

int task3()
{
    cout << "=== Testing MatrixUShort ===\n\n";

    cout << "Test 1: Default Constructor\n";
    MatrixUShort m1;
    cout << m1;
    assert(m1.getRows() == 0 && m1.getCols() == 0 && m1.getCodeError() == 0);

    cout << "\nTest 2: Identity Matrix (size=2)\n";
    MatrixUShort m2(2);
    cout << m2;
    assert(m2[0][0] == 1 && m2[1][1] == 1 && m2.getCodeError() == 0);

    cout << "\nTest 3: Matrix (2x3)\n";
    MatrixUShort m3(2, 3);
    cout << m3;
    assert(m3.getRows() == 2 && m3.getCols() == 3 && m3.getCodeError() == 0);

    cout << "\nTest 4: Matrix (2x2, value=5)\n";
    MatrixUShort m4(2, 2, 5);
    cout << m4;
    assert(m4[0][0] == 5 && m4[1][1] == 5 && m4.getCodeError() == 0);

    cout << "\nTest 5: Copy Constructor\n";
    MatrixUShort m5(m4);
    cout << m5;
    assert(m5 == m4 && m5.getCodeError() == 0);

    cout << "\nTest 6: Assignment Operator\n";
    MatrixUShort m6;
    m6 = m4;
    cout << m6;
    assert(m6 == m4 && m6.getCodeError() == 0);

    cout << "\nTest 7: Increment Operators\n";
    ++m4;
    cout << m4;
    assert(m4[0][0] == 6 && m4.getCodeError() == 0);
    m4++;
    cout << m4;
    assert(m4[0][0] == 7 && m4.getCodeError() == 0);

    cout << "\nTest 8: Decrement Operators\n";
    --m4;
    cout << m4;
    assert(m4[0][0] == 6 && m4.getCodeError() == 0);
    m4--;
    cout << m4;
    assert(m4[0][0] == 5 && m4.getCodeError() == 0);

    cout << "\nTest 9: Unary Operators\n";
    cout << "!m4: " << !m4 << "\n";
    assert(!m4 == true);

    cout << "\nTest 10: Arithmetic Operators\n";
    MatrixUShort m9(2, 2, 2);
    MatrixUShort m10 = m4 + m9;
    cout << "m4 + m9:\n" << m10;
    assert(m10[0][0] == 7 && m10.getCodeError() == 0);
    MatrixUShort m11 = m4 * 2;
    cout << "m4 * 2:\n" << m11;
    assert(m11[0][0] == 10 && m11.getCodeError() == 0);

    cout << "\nTest 11: Matrix-Vector Multiplication\n";
    VectorUShort v(2, 3);
    VectorUShort v2 = m4 * v;
    //VectorUShort v2(2);
    //v2.setData(0, (m4 * v).getData(0));
    //v2.setData(1, (m4 * v).getData(1));
    cout << "m4 * v:\n" << v2;
    assert(v2.getState() == 0);

    cout << "\nTest 13: Comparison Operators\n";
    cout << "m4 == m4: " << (m4 == m4) << "\n";
    assert(m4 == m4);
    cout << "m4 != m9: " << (m4 != m9) << "\n";
    assert(m4 != m9);

    cout << "\nTest 14: Indexing\n";
    m4[0][0] = 10;
    cout << m4;
    assert(m4[0][0] == 10 && m4.getCodeError() == 0);
    m4[10];
    assert(m4.getCodeError() == 1);

    cout << "\nTest 15: Object Count\n";
    cout << "Number of matrices: " << MatrixUShort::getNumMatrix() << "\n";
    assert(MatrixUShort::getNumMatrix() > 0);

    cout << "\n=== Testing Completed ===\n";
	return 4;
}
