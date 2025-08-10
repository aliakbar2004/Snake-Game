#include <iostream>
#include "objPosHashTable.h"

// Provided Code for Model Code Integration
////////////////////////////////////////////////

// uncomment this line when integrating with model code
#include "./Lab5-Model/inc/MacUILib.h"

using namespace std;

objPosHashTable::objPosHashTable()
{
    // create the hash table with default size (TABLE_SIZE)

    // By default, all elements in the table should be initialized to:
    //  x = 0, y = 0, prefix = '\0' (0), number = 0, symbol = '\0' (0)
    // 1) Set tableSize to the default TABLE_SIZE (e.g., from a #define or static const)
    tableSize = TABLE_SIZE;

    // 2) Allocate the hash table
    myHashTable = new objPos[tableSize];

    // 3) Initialize all elements
    for(int i = 0; i < tableSize; i++)
    {
        myHashTable[i].setX(0);
        myHashTable[i].setY(0);
        myHashTable[i].setPF('\0');   // prefix = 0
        myHashTable[i].setNum(0);
        myHashTable[i].setSym('\0');  // symbol = 0
    }
}

objPosHashTable::objPosHashTable(int size)
{
    // create the hash table with the custom size (size)

    // By default, all elements in the table should be initialized to:
    //  x = 0, y = 0, prefix = '\0' (0), number = 0, symbol = '\0' (0)
    // 1) Set tableSize to the provided size
    tableSize = size;

    // 2) Allocate the hash table
    myHashTable = new objPos[tableSize];

    // 3) Initialize all elements
    for(int i = 0; i < tableSize; i++)
    {
        myHashTable[i].setX(0);
        myHashTable[i].setY(0);
        myHashTable[i].setPF('\0');
        myHashTable[i].setNum(0);
        myHashTable[i].setSym('\0');
    }
}

objPosHashTable::~objPosHashTable()
{
    // remove the hash table
    // 1) Deallocate the array
    delete[] myHashTable;
    myHashTable = nullptr;
}

int objPosHashTable::calculateHashing(int prefix, int number) const
{
    // calculate the hash index using the prefix and number.

    // Formula: Add all digits of the number and the integer value of the ASCII prefix.

    // Ex. prefix = 'A'(65), number = 37
    //     return value = 6 + 5 + 3 + 7 = 21
        // Sums the digit values of 'prefix' (ASCII integer) and 'number'.
    // Example: prefix = 'A'(65) -> digits are 6 and 5; number=37 -> digits 3 and 7 => total = 6+5+3+7=21.

    int sum = 0;
    // Sum digits of prefix
    int temp = prefix;
    while (temp != 0)
    {
        sum += temp % 10;
        temp /= 10;
    }
    // Sum digits of number
    temp = number;
    while (temp != 0)
    {
        sum += temp % 10;
        temp /= 10;
    }
    return sum;

}

double objPosHashTable::getLambda() const
{
    // calculate the load factor of the hash table
        // Sums the digit values of 'prefix' (ASCII integer) and 'number'.
    // Example: prefix = 'A'(65) -> digits are 6 and 5; number=37 -> digits 3 and 7 => total = 6+5+3+7=21.
    int occupied = 0;
    for (int i = 0; i < tableSize; i++)
    {
        if(myHashTable[i].getSym() != '\0')
            occupied++;
    }
    return static_cast<double>(occupied) / tableSize;

}

void objPosHashTable::printMe() const
{
    // Provided for verbose mode in Test.cpp
    // comment the entire for-loop out when integrating with the model code.
    for(int i = 0; i < tableSize; i++)
    {
        cout << "[" << i << "]  " << myHashTable[i].getPF() << myHashTable[i].getNum() << " " << myHashTable[i].getSym() << endl;     
    }



    // Provided Code for Model Code Integration
    ////////////////////////////////////////////////

    // uncomment the following lines when integrating with model code

    // MacUILib_printf("[ ");
    // for(int i = 0; i < TABLE_SIZE; i++)
    // {
    //     if(myHashTable[i].getSym() != 0)
    //         MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    // }
    // MacUILib_printf("] L=%.2f", getLambda());

    // You will also need to #include "MacUILib.h" when integrating with the model code.
    
}

