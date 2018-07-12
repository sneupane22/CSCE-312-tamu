//
//  Parser.h
//  assembler
//
//  Created by Mitesh Patel on 3/24/16.
//  Copyright (c) 2016 TAMU. All rights reserved.
//

#ifndef assembler_Parser_h
#define assembler_Parser_h
#include <fstream>
#include <string>
#include <exception>
#include "Codes.h"

enum CommandType {
    A_COMMAND, C_COMMAND, L_COMMAND
};

class Parser {
    private:
        string currentLine; // need to keep track of current line we on
        ifstream& inputFile;
        CommandType type;
        string _symbol;
        string _dest;
        string _comp;
        string _jump;
    
        Dest& dest_mnemonics;
        Comp& comp_mnemonics;
        Jump& jump_mnemonics;
    
        int position;           // need to keep track of position
        int lineNumber;			// need to keep track of line number of the asm file
    
        void skipWS(); // skip white space, so advance position until there is no white space
        string extractSymbol();
        void handleComment(); // deal with comments
        void handleA_Cmd(); // deal with the A command
        void handleC_Cmd(); // deal with the C command
        void handleL_Cmd(); // deal with the L command
    
public:
        Parser(ifstream& f, Dest& dm,Comp& cm, Jump& jm)
            :inputFile(f), dest_mnemonics(dm), comp_mnemonics(cm),jump_mnemonics(jm), position(0), lineNumber(0) {}
        ~Parser(){inputFile.close();};
        bool hasMoreCommands();
        void advance();
        CommandType commandType() {	return type; }
    
        //getters
        string symbol(){ return _symbol; }
        string dest(){ return _dest; }
        string comp(){ return _comp; }
        string jump(){ return _jump; }
};

void Parser::skipWS() {
    while(isspace(currentLine[position]))
        position++; // go next until no space
}

string Parser::extractSymbol() {
    string sym;
    char c;
    
    while(position < currentLine.size()) {
        c = currentLine[position]; // set the character c to whatever data our position is on
        if(!isalnum(c) && c != '_' && c != '.' && c != '$' && c != ':') // symbol will start with a character
            break;
        sym += c; //  append each character to get symbol
        position++;
    }
    return sym;
}

void Parser::handleComment() {
    position++; // increment position
    if(currentLine[position] == '/') // if starts with a / then its definetly gonna be a comment
    {
        position = currentLine.size();
        return;
    }
}


void Parser::handleA_Cmd() {
    position++;	// the @ symbol is read
    skipWS();
    string sym;
    if(!isdigit(currentLine[position])) // if its not a digit then must be a symbol
        sym = extractSymbol();
    else {
        // it's a number.
        while(isdigit(currentLine[position]))
            sym += currentLine[position++];
    }
    
    skipWS();
    position = currentLine.size();
    _symbol = sym;
    type = A_COMMAND; // set type
}

void Parser::handleC_Cmd() {
    
    skipWS();
    int state = 0;
    char c;
    string s;
    
    int dest_pos = position, comp_pos = position, jump_pos = position;
    
    // state is guaranteed to be 3 by the time we're done
    while(state < 3) {
        if(position >= currentLine.size())
            c = 0;		// end is when c=0
        else
            c = currentLine[position];
        
        if(isspace(c)) {
            position++;
            continue;
        }
        
        if(state == 0) {
            switch(c)
            {
                case '=':
                    _dest = s;
                    s = "";
                    comp_pos = jump_pos = position;
                    state = 1;
                    position++;
                    continue;
                case ';':
                case '/':
                case 0:		// end
                    _dest = "null";
                    _comp = s;
                    s = "";
                    jump_pos = position;
                    state = 2;
                    position++;
                    continue;
            }
        }
        else if(state == 1) {
            switch(c) {
                case ';':
                case '/':
                case 0:		// end
                    _comp = s;
                    s = "";
                    jump_pos = position;
                    state = 2;
                    position++;
                    continue;
            }
        }
        else if(state == 2) {
            switch(c) {
                case '/':
                case 0:		// end
                    if(s == "")
                        _jump = "null";
                    else
                        _jump = s;
                    state = 3;
            }
        }
        
        s += c;
        position++;
    }
    
    type = C_COMMAND;
    position = currentLine.size();
    
}

void Parser::handleL_Cmd() {
    position++;			// '(' is read
    skipWS();
    
    string label = extractSymbol();
    // position is after the end of the label
    position++;
    skipWS();
    
    _symbol = label;
    type = L_COMMAND;
    position = currentLine.size();
}

bool Parser::hasMoreCommands() {
    if(!inputFile) return false;
    
    skipWS();
    if(position ==currentLine.size())
        getline(inputFile, currentLine);
    else {
        return true;
    }
    
    position = 0;
    
    skipWS();
    // check for empty lines
    if(position == currentLine.size())
        return hasMoreCommands();
    
    if(currentLine[position] == '/')
    {
        handleComment();
        return hasMoreCommands();
    }
    
    return true;
}




void Parser::advance() {
    switch(currentLine[position]) {
            
        case '(':		// L_COMMAND
            handleL_Cmd();
            break;
        case '@':		// A_COMMAND
            handleA_Cmd();
            break;
        default:	// C_COMMAND
            handleC_Cmd();
            break;
    }
    lineNumber++;
}












#endif
