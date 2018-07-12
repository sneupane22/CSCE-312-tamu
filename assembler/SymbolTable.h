//
//  SymbolTable.h
//  assembler
//
//  Created by Mitesh Patel on 3/24/16.
//  Copyright (c) 2016 TAMU. All rights reserved.
//

#ifndef assembler_SymbolTable_h
#define assembler_SymbolTable_h


#include <map>
#include <string>

using namespace std;

class SymbolTable
{
    private:
        map<string, int> table;
    public:
        SymbolTable(){};
        void addEntry(string s, int address){table[s] = address;} //add to map table
        bool contains(string s) {return (table.find(s) != table.end());} // does it contain already?
        string getAddress(string s){return getBinary(table[s]);}// gets the address and returns a binary number in string
    
        //need to get the binary number associated with the address. This is for the A instruction
        string getBinary(int address);
};

string SymbolTable::getBinary(int address) {
    string binaryNum = "000000000000000";
    int n = 14; // start at the end of the binary number
    while(address) {
        binaryNum[n--] = address & 1 ? '1' : '0';
        address >>= 1;
    }
    return binaryNum;
}



#endif
