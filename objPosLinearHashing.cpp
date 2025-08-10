#include "objPosLinearHashing.h"

#include <iostream>
using namespace std;

objPosLinearHashing::objPosLinearHashing()
{
    // do you need anything here?     
}

objPosLinearHashing::objPosLinearHashing(int size) : objPosHashTable(size)
{
    // do you need to modify anything here?
}

objPosLinearHashing::~objPosLinearHashing()
{
    // do you need anything here?     
}

bool objPosLinearHashing::insert(const objPos &thisPos)
{
    // Insert thisPos into the Hash Table (if not already inserted) using Linear Probing

    // When inserting, using Symbol as a way to check if the table entry is occupied or free
    //    Symbol = 0 (FREE),   Symbol = 'v' (Occupied)
    // Compute the initial hash index using the provided primary hashing function.
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    int firstFree = -1;
    // Scan the entire probe sequence.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i) % tableSize;
        
        if (myHashTable[index].getSym() == 'v')
        {
            // Check for duplicate by comparing key fields.
            if (myHashTable[index].getX() == thisPos.getX() &&
                myHashTable[index].getY() == thisPos.getY() &&
                myHashTable[index].getPF() == thisPos.getPF() &&
                myHashTable[index].getNum() == thisPos.getNum())
            {
                return false;  // Duplicate found.
            }
        }
        else // Slot is free (or was deleted)
        {
            if (firstFree == -1)
                firstFree = index;
            // Do not break; continue scanning for possible duplicates.
        }
    }
    if (firstFree != -1)
    {
        myHashTable[firstFree] = thisPos;   // Use assignment operator.
        myHashTable[firstFree].setSym('v');   // Mark as occupied.
        return true;
    }
    return false; // No free slot found within MAX_PROBING_COUNT.
    
}

bool objPosLinearHashing::remove(const objPos &thisPos)
{
    // Remove thisPos from the Hash Table using Linear Probing

    // If found in the table, apply lazy deletion by setting Symbol = 0 (free), and return true
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.    
    // Compute the initial hash index.
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    // Scan the entire probe sequence.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i) % tableSize;
        
        if (myHashTable[index].getSym() == 'v')
        {
            if (myHashTable[index].getX() == thisPos.getX() &&
                myHashTable[index].getY() == thisPos.getY() &&
                myHashTable[index].getPF() == thisPos.getPF() &&
                myHashTable[index].getNum() == thisPos.getNum())
            {
                myHashTable[index].setSym('\0');  // Lazy deletion.
                return true;
            }
        }
        // Continue scanning even if a free slot is encountered.
    }
    return false;  // Item not found.
}

bool objPosLinearHashing::isInTable(const objPos &thisPos) const
{
    // Check if thisPos is in the Hash Table using Linear Probing

    // If found in the table, return true
        // Remember, finding the match is not enough.  The entry has to be VALID (symbol = 'v').
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.  
    // Compute the initial hash index.
    // 1) Compute h(x)
    int hVal = calculateHashing(thisPos.getPF(), thisPos.getNum()) % tableSize;
    // Scan the entire probe sequence.
    for (int i = 0; i < MAX_PROBING_COUNT; i++)
    {
        int index = (hVal + i) % tableSize;
        
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
        // Do not stop at free slots—continue scanning.
    }
    return false;

}