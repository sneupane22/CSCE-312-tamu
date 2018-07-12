

#ifndef VM_TRANSLATOR_Parser_h
#define VM_TRANSLATOR_Parser_h

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


enum commands {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, C_NULL};

class Parser
{
public:
    Parser(string infileName); //open input file
    ~Parser();
    bool hasMoreCommands();
    void advance();
    commands commandType();
    string arg1();
    int arg2();
    
private:
    string input_fileName; // need for inFileName
    ifstream inFile;
    string currentCommand; // keep track of the current command

    
};


//constructor just opens file
Parser :: Parser(string inFileName){
    input_fileName = inFileName; // set inFile to the file name passed
    inFileName = inFileName + ".vm"; // set the input name to have the extension vm
    inFile.open(inFileName.c_str()); //open file
}


//destructor just closes file
Parser :: ~Parser(){
    
    if(inFile.is_open())
        inFile.close();
}

bool Parser::hasMoreCommands(){
    
    return !inFile.eof();
}

void Parser::advance(){
    if (hasMoreCommands()){
        getline(inFile, currentCommand); // save in current command
        currentCommand.erase(remove(currentCommand.begin(), currentCommand.end(), '\r'), currentCommand.end());
        //keep advancing until you havent reached a comment or whitespace
        while (((currentCommand.substr(0,2) == "//") || (currentCommand.substr(0,1) == "")) && hasMoreCommands())
        {
            getline(inFile, currentCommand);
            currentCommand.erase(remove(currentCommand.begin(), currentCommand.end(), '\r'), currentCommand.end());
        }
        
    }
    
}


// checking for the nine commands
//push constant 7
//push constant 8
//add
commands Parser::commandType(){
    currentCommand.erase(remove(currentCommand.begin(), currentCommand.end(), '\r'), currentCommand.end());
    if((currentCommand.substr(0,3) == "add"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,3) == "sub"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,3) == "neg"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,3) == "and"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,3) == "not"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,2) == "eq"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,2) == "gt"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,2) == "lt"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,2) == "or"))
        return C_ARITHMETIC;
    else if ((currentCommand.substr(0,2) == "if"))
        return C_IF;
    else if ((currentCommand.substr(0,3) == "pop"))
        return C_POP;
    else if ((currentCommand.substr(0,4) == "push"))
        return C_PUSH;
    else if ((currentCommand.substr(0,4) == "goto"))
        return C_GOTO;
    else if ((currentCommand.substr(0,4) == "call"))
        return C_CALL;
    else if ((currentCommand.substr(0,5) == "label"))
        return C_LABEL;
    else if ((currentCommand.substr(0,6) == "return"))
        return C_RETURN;
    else if ((currentCommand.substr(0,8) == "function"))
        return C_FUNCTION;
    
    
    return C_NULL;
}

//push constant 5 example arg 1 would get the word constant
string Parser::arg1(){

    commands CMD = commandType(); // get the command
    if(CMD != C_RETURN) // only execute if not C_RETURN since thats what the instructions suggests
    {
        int space_1 = currentCommand.find(" ",0);
        int space_2 = currentCommand.find(" ", space_1 + 1);
        string argument1 = currentCommand.substr(space_1 + 1, space_2 - space_1 - 1);
        return argument1;
    }
    return "WHY IS IT NOT WRKING";
}

// push constant 5 example arg 2 gets the index which is number 5
int Parser::arg2(){
    
    commands CMD = commandType();
    if(CMD == C_PUSH || CMD == C_POP || CMD == C_FUNCTION || CMD == C_CALL){
        
        int space_1 = currentCommand.find(" ",0);
        int space_2 = currentCommand.find(" ", space_1 + 1);
        int space_3 = currentCommand.find(" ", space_2 + 1);
        string argument2 = currentCommand.substr(space_2 + 1, space_3 - space_2 - 1 );
        //convert string to int
        int argument2INT = stoi(argument2);
        return argument2INT;
    }
    
    return 0;
}


#endif
