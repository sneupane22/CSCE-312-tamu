//
//  main.cpp
//  assembler
//
//  Created by Mitesh Patel on 3/24/16.
//  Copyright (c) 2016 TAMU. All rights reserved.
//


#include "SymbolTable.h"
#include "Codes.h"
#include "Parser.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main()
{
  
    string input_name;
    cout << "Enter the name of the file(ie. Add.asm, Max.asm etc..) ";
    cin >> input_name;
    ifstream inputFile(input_name.c_str());
    
    
    
    
    
    
    // initial pass through the file
    Dest dest_mnemonics;
    Comp comp_mnemonics;
    Jump jump_mnemonics;
    
    Parser parser(inputFile, dest_mnemonics, comp_mnemonics,jump_mnemonics);
    SymbolTable symbol_Table;
    int instrCounter = 0;
    while(parser.hasMoreCommands()) {
        parser.advance();
        switch(parser.commandType()) {
                // we only want the labels on the first pass so only take care of L command
            case L_COMMAND:
                symbol_Table.addEntry(parser.symbol(),instrCounter);
                break;
            default:
                // L commands should not be counted
                instrCounter++;
        }
    }
    
    
    // this part is the second pass
    // reset file used by parser
    inputFile.close();
    inputFile.open(input_name.c_str()); // open again
    Parser parserSecond(inputFile, dest_mnemonics, comp_mnemonics,jump_mnemonics);
    
    int extension = input_name.find(".asm");
    input_name = input_name.substr(0, extension); // get rid of asm part of input
    ofstream out((input_name + ".hack").c_str());
    string sym;
    int reg;
    int RAM_init = 16; // initial address for variables start at 16
    
    // Predefined symbols
    symbol_Table.addEntry("SP", 0);
    symbol_Table.addEntry("LCL", 1);
    symbol_Table.addEntry("ARG", 2);
    symbol_Table.addEntry("THIS", 3);
    symbol_Table.addEntry("THIS", 4);
    symbol_Table.addEntry("R0", 0);
    symbol_Table.addEntry("R1", 1);
    symbol_Table.addEntry("R2", 2);
    symbol_Table.addEntry("R3", 3);
    symbol_Table.addEntry("R4", 4);
    symbol_Table.addEntry("R5", 5);
    symbol_Table.addEntry("R6", 6);
    symbol_Table.addEntry("R7", 7);
    symbol_Table.addEntry("R8", 8);
    symbol_Table.addEntry("R9", 9);
    symbol_Table.addEntry("R10",10);
    symbol_Table.addEntry("R11",11);
    symbol_Table.addEntry("R12",12);
    symbol_Table.addEntry("R13",13);
    symbol_Table.addEntry("R14",14);
    symbol_Table.addEntry("R15",15);
    symbol_Table.addEntry("SCREEN", 16384);
    symbol_Table.addEntry("KBD", 24576);
    
    
    while(parserSecond.hasMoreCommands()) {
        parserSecond.advance();
        switch(parserSecond.commandType()) {
            case A_COMMAND: // deal with a command
                sym = parserSecond.symbol();
                if(!isdigit(sym[0])) {
                    if(symbol_Table.contains(sym)) {
                        // its a label then
                        out << "0"<< symbol_Table.getAddress(sym)<< "\n"; // a instruction starts with 0
                    }
                    else {
                        // it's a variable
                        symbol_Table.addEntry(sym, RAM_init);
                        out << "0"<< symbol_Table.getBinary(RAM_init++)<< "\n";
                    }
                }
                else {
                    int constant = 0;
                    for(int i = 0; i < sym.size(); i++) {
                        constant *= 10;
                        constant += sym[i] - '0';
                    }
                    out << "0"<< symbol_Table.getBinary(constant)<< "\n";
                }
                break;
            case C_COMMAND: // deal with c command
                if(parserSecond.comp().find("M") != string::npos)
                    reg = 1;
                else
                    reg = 0;
                out << "111" << reg << comp_mnemonics.getBinaryCode(parserSecond.comp())<< dest_mnemonics.getBinaryCode(parserSecond.dest())<< jump_mnemonics.getBinaryCode(parserSecond.jump())<< "\n";
                break;
            case L_COMMAND:
                // ignore L commands.
                break;
        }
    }
    
    inputFile.close();
    out.close();
    cout << "Done successfully. Check the hack file.\n";
    return 0;
    
}

