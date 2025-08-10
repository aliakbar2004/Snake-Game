#include "objPosQuadHashing.h"

#include <iostream>
using namespace std;

objPosQuadHashing::objPosQuadHashing()
{
    // do you need anything here?     
}

objPosQuadHashing::objPosQuadHashing(int size) : objPosHashTable(size)
{
    // do you need to modify anything here?
}

objPosQuadHashing::~objPosQuadHashing()
{
    // do you need anything here?     
}

bool objPosQuadHashing::insert(const objPos &thisPos)
{
    // Insert thisPos into the Hash Table (if not already inserted) using Quadratic Probing

    // When inserting, using Symbol as a way to check if the table entry is occupied or free
    //    Symbol = 0 (FREE),   Symbol = 'v' (Occupied)
    // Compute the starting index using the primary hashing function and modulo tableSize.
    // 1) Compute h(x)
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    int firstFree = -1;
    // Quadratic probing: index = (hVal + i^2) mod tableSize.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i * i) % tableSize;
        
        if (myHashTable[index].getSym() == 'v')
        {
            if (myHashTable[index].getX() == thisPos.getX() &&
                myHashTable[index].getY() == thisPos.getY() &&
                myHashTable[index].getPF() == thisPos.getPF() &&
                myHashTable[index].getNum() == thisPos.getNum())
            {
                return false;  // Duplicate found.
            }
        }
        else
        {
            if (firstFree == -1)
                firstFree = index;
        }
    }
    if (firstFree != -1)
    {
        myHashTable[firstFree] = thisPos;
        myHashTable[firstFree].setSym('v');
        return true;
    }
    return false;

}

bool objPosQuadHashing::remove(const objPos &thisPos)  // lazy delete 
{
    // Remove thisPos from the Hash Table using Quadratic Probing

    // If found in the table, apply lazy deletion by setting Symbol = 0 (free), and return true
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.
    // Compute the starting index using the primary hash.
    // 1) Compute h(x)
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    // Scan entire probe sequence.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i * i) % tableSize;
        
        if (myHashTable[index].getSym() == 'v')
        {
            if (myHashTable[index].getX() == thisPos.getX() &&
                myHashTable[index].getY() == thisPos.getY() &&
                myHashTable[index].getPF() == thisPos.getPF() &&
                myHashTable[index].getNum() == thisPos.getNum())
            {
                myHashTable[index].setSym('\0');
                return true;
            }
        }
    }
    return false;
}

bool objPosQuadHashing::isInTable(const objPos &thisPos) const
{
    // Check if thisPos is in the Hash Table using Quadratic Probing

    // If found in the table, return true
        // Remember, finding the match is not enough.  The entry has to be VALID (symbol = 'v').
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily. 
    // Compute the starting index.
    // 1) Compute h(x)
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    // Scan entire probe sequence.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i * i) % tableSize;
        
        if (myHashTable[index].getSym() == 'v')
        {
            if (myHashTable[index].getX() == thisPos.getX() &&
                myHashTable[index].getY() == thisPos.getY() &&
                myHashTable[index].getPF() == thisPos.getPF() &&
                myHashTable[index].getNum() == thisPos.getNum())
            {
                return true;
            }
        }
    }
    return false;

}