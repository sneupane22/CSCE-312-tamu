
#ifndef VM_TRANSLATOR_CodeWriter_h
#define VM_TRANSLATOR_CodeWriter_h

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include "Parser.h"
using namespace std;



class CodeWriter{
    
public:
    CodeWriter(string outFileName);
    CodeWriter();
    ~CodeWriter();
    void setFileName(string outfileName);
    void writeArithmetic(string commandSeg);
    void writePushPop(commands cpushORcpop, string segment, int index);
    string output_fileName; // need for outFileName
    
    
    //functions needed for project 8
    void writeInit();
    void writeInitBoot();
    void writeLabel(string label);
    void writeGoto(string label);
    void writeIf(string label);
    void writeCall(string functionName, int numArgs);
    void writeReturn();
    void writeFunction(string functionName, int numLocals);
    //------
    
    
    void setOutputFileName(string outputName);
    void popGeneralPurposeRegister (int registerNum);// pops using General purpose register rams 13-15
    void push(string location, int index_P);
    void pop(string location, int index_P);
private:

    string functionName_;
    ofstream outFile;
    int labelNumber; // keep track of where label is
    int increm;

};


CodeWriter:: CodeWriter(string outFileName){
    
    labelNumber = 0;
    increm = 0;
    output_fileName = outFileName;
    outFileName = outFileName + ".asm"; // add the .asm extension
    outFile.open(outFileName.c_str());
    if (!outFile.is_open())
        cerr << "Error: Cannot open " << outFileName << endl;
    writeInit(); // write init no boot
}

CodeWriter::CodeWriter(){
    labelNumber = 0;
    increm = 0;
}


CodeWriter::~CodeWriter(){
    if (outFile.is_open())
        outFile.close();
}

// set new file with boot , only should be called when directories called
void CodeWriter::setFileName(string outFileName){
    
    if (outFile.is_open()) // close just incase 
        outFile.close();
    

    //string s = outFileName;
    //s.erase(s.find_last_of("."), string::npos);
    //outFileName = s + ".asm"; // add the .asm extension
    
    //output_fileName = outFileName;
    //outFileName = outFileName + ".asm"; // add the .asm extension
    
    
    output_fileName = outFileName;
    if(increm == 0)
    {
        outFileName = outFileName + ".asm";
        outFile.open(outFileName.c_str());
        writeInitBoot();

    }
    if (!outFile.is_open())
        cerr << "Error: Cannot open " << outFileName << endl;


    
}

void CodeWriter::writeArithmetic(string commandSeg){
    //cout << commandSeg << endl;
    //cout << commandSeg << endl;
    //cout << "Size : " << commandSeg.length() << endl;;
    //commandSeg.erase(std::remove(commandSeg.begin(), commandSeg.end(), '\r'), commandSeg.end());
    

    //cout << commandSeg << endl;
    if(commandSeg == "add"){
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //ADD
        outFile << "M=D+M" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
    
    }
    else if (commandSeg == "sub"){
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //SUB
        outFile << "M=M-D" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
    }
    else if (commandSeg == "neg"){
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //NEG
        outFile << "M=-M" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
    }
    else if (commandSeg == "not"){
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //NOT
        outFile << "M=!M" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
    }
    else if (commandSeg == "and"){
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //AND
        outFile << "M=D&M" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
    }
    else if (commandSeg == "or"){
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        //OR
        outFile << "M=D|M" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
    }
    else if (commandSeg == "eq"){
        //SET RETURN
        outFile << "@RETURN" << labelNumber << endl;
        outFile << "D=A" << endl;
        outFile <<  "@R15" << endl;
        outFile << "M=D" << endl;
        
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        outFile << "D=D-M" << endl;
        outFile << "M=0" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
        //EQ
        outFile << "@LABELT" << endl;
        outFile << "D;JEQ" << endl;
        outFile << "(RETURN" << labelNumber << ")" << endl;
        labelNumber++;
    }
    else if (commandSeg == "gt"){
        //SET RETURN
        outFile << "@RETURN" << labelNumber << endl;
        outFile << "D=A" << endl;
        outFile <<  "@R15" << endl;
        outFile << "M=D" << endl;
        
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        outFile << "D=D-M" << endl;
        outFile << "M=0" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
        //GT
        outFile << "@LABELT" << endl;
        outFile << "D;JLT" << endl;
        outFile << "(RETURN" << labelNumber << ")" << endl;
        labelNumber++;
        
    }
    else if (commandSeg == "lt"){
        //SET RETURN
        outFile << "@RETURN" << labelNumber << endl;
        outFile << "D=A" << endl;
        outFile <<  "@R15" << endl;
        outFile << "M=D" << endl;
        
        //POP TOP to REGISTER D
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        outFile << "D=M" << endl;
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        outFile << "D=D-M" << endl;
        outFile << "M=0" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
        //GT
        outFile << "@LABELT" << endl;
        outFile << "D;JGT" << endl;
        outFile << "(RETURN" << labelNumber << ")" << endl;
        labelNumber++;
    
    }
}







void CodeWriter:: writePushPop(commands cpushORcpop, string segment, int index){
    if (cpushORcpop == C_PUSH)
    {
        //ie push constant 5 where segment is "constant" and index is the number 5
        if(segment == "constant")
        {
            outFile << "@" << index << endl; // for example this line would be @5
            outFile << "D=A" << endl;
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            
            //INCREMENT SP
            outFile << "@SP" << endl;
            outFile << "AM=M+1" << endl;
        }
        else if(segment == "static"){
            outFile << "@" << output_fileName << "." << index << endl; //ie push static 7 --> @f.7
            outFile<< "D=M" << endl;
            outFile << "@SP" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
            outFile << "@SP" << endl;
            outFile << "M=M+1" << endl;
        }
        else if(segment == "local") // ie push local 5
            push("LCL",index);
        else if (segment == "argument")// ie push argument 5
            push("ARG",index);
        else if (segment == "that")
            push("THAT",index);
        else if (segment == "this")
            push("THIS",index);
        else if (segment == "pointer")
            push("3",index); //pointer segment are mapped on ram locations 3-4
        else if (segment == "temp")
            push("5",index); //temp segment are mapped on ram locations 5-12
        
        
    }
    else if (cpushORcpop == C_POP)
    {
        if (segment == "static")
        {
            outFile << "@" << output_fileName << "." << index << endl;
            outFile << "D=A" << endl;
            outFile << "@R13" << endl;
            outFile << "M=D" << endl;
            outFile << "@SP" << endl;
            outFile << "M=M-1" << endl;
            outFile << "A=M" << endl;
            outFile << "D=M" << endl;
            outFile << "@R13" << endl;
            outFile << "A=M" << endl;
            outFile << "M=D" << endl;
        }
        else if (segment == "local")
            pop("LCL",index);
        else if (segment == "argument")
            pop("ARG",index);
        else if (segment == "this")
            pop("THIS",index);
        else if (segment == "that")
            pop("THAT",index);
        else if (segment == "pointer")
            pop("3",index);
        else if (segment == "temp")
            pop("5",index);
  
    }
    
    
    
    
}

void CodeWriter::popGeneralPurposeRegister (int registerNum){
    assert(registerNum >= 13 && registerNum <= 15); // die if not between these two values
    outFile << "@" << registerNum << endl;
    outFile << "M=D" << endl;
    
}

void CodeWriter::push(string location, int index_P){
    if(location == "3" || location == "5")
    {
        //PUSH for POINTER AND TEMP
        outFile << "@" << location << endl;
        outFile << "D=A" << endl;
        outFile << "@" << index_P << endl;
        outFile << "A=D+A" << endl;
        outFile << "D=M" << endl;
        outFile << "@SP" << endl;
        outFile << "A=M" << endl;
        outFile << "M=D" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
    }
    else{
        
        outFile << "@" << location << endl;
        outFile << "D=M" << endl;
        outFile << "@" << index_P << endl;
        outFile << "A=D+A" << endl;
        outFile << "D=M" << endl;
        outFile << "@SP" << endl;
        outFile << "A=M" << endl;
        outFile << "M=D" << endl;
        
        //INCREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M+1" << endl;
        
    }
}

void CodeWriter::pop(string location, int index_P){
    
    
    if(location == "3" || location == "5"){
        //POP for strings with length 3 or 5 so ARG, LCL, etc
        outFile << "@" << location << endl;
        outFile << "D=A" << endl;
        outFile << "@" << index_P << endl;
        outFile << "D=D+A" << endl;
        
        popGeneralPurposeRegister(13); // pop R13
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        outFile << "D=M" << endl;
        outFile << "@R13" << endl;
        outFile << "A=M" << endl;
        outFile << "M=D" << endl;
    }
    else{
        // POP for POINTER AND TEMP
        outFile << "@" << location << endl;
        outFile << "D=M" << endl;
        outFile << "@" << index_P << endl;
        outFile << "D=D+A" << endl;
        
        popGeneralPurposeRegister(13); // pop R13
        
        //DECREMENT SP
        outFile << "@SP" << endl;
        outFile << "AM=M-1" << endl;
        
        outFile << "D=M" << endl;
        outFile << "@R13" << endl;
        outFile << "A=M" << endl;
        outFile << "M=D" << endl;
    }
}



void CodeWriter::writeInit(){
    outFile << "@256" << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@init" << increm << endl;
    outFile << "0;JMP" << endl;
    outFile << "(LABELT)" << endl;
    
    //DECREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M-1" << endl;
    
    outFile << "M=-1" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    outFile << "@R15" << endl;
    outFile << "A=M" << endl;
    outFile << "0;JMP" << endl;
    
    outFile << "(init" << increm << ")" << endl;
    //writeCall("Sys.init",0);
    // UN COMMENTED TO WORK FOR BASICLOOP, FIBBONACISERI , and SIMPLE FUNCTION writeCall("Sys.init",0);
    increm++;
}

void CodeWriter::writeInitBoot(){
    outFile << "@256" << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "M=D" << endl;
    
    outFile << "@init" << increm << endl;
    outFile << "0;JMP" << endl;
    outFile << "(LABELT)" << endl;
    
    //DECREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M-1" << endl;
    
    outFile << "M=-1" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    outFile << "@R15" << endl;
    outFile << "A=M" << endl;
    outFile << "0;JMP" << endl;
    
    outFile << "(init" << increm << ")" << endl;
    writeCall("Sys.init",0); //boot
    increm++;
}

void CodeWriter::writeLabel(string label)
{
    outFile << "(" << functionName_ << "$" << label << ")" << endl;
}

void CodeWriter::writeGoto(string label)
{
    if(label != functionName_) // set labels within the function
    {
        outFile << "@" << functionName_ << "$" << label << endl;
        outFile << "0;JMP" << endl;
    }
    else // label is the functionName_, thus go to the function
    {
        outFile << "@" << label << endl;
        outFile << "0;JMP" << endl;
    }
}

void CodeWriter::writeIf(string label)
{
    //POP TOP to REGISTER D
    outFile << "@SP" << endl;
    outFile << "AM=M-1" << endl;
    outFile << "D=M" << endl;
    
    outFile << "@" << functionName_ << "$" << label << endl;
    outFile << "D;JNE" << endl; // jmp if top of val on stack is not 0
}


void CodeWriter::writeCall(string functionName, int numArgs)
{
    // Push return value from label below onto the stack
    outFile << "@RETURN" << labelNumber << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    // Push LCL of calling function onto the stack
    outFile << "@LCL" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    // Push ARG of calling function onto the stack
    outFile << "@ARG" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    // Push THIS of calling function onto the stack
    outFile << "@THIS" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    // Push THAT of calling function onto the stack
    outFile << "@THAT" << endl;
    outFile << "D=M" << endl;
    outFile << "@SP" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    //INCREMENT SP
    outFile << "@SP" << endl;
    outFile << "AM=M+1" << endl;
    
    // reposition ARG
    outFile << "@" << numArgs << endl;
    outFile << "D=A" << endl;
    outFile << "@SP" << endl;
    outFile << "D=M-D" << endl;
    outFile << "@5" << endl;
    outFile << "D=D-A" << endl;
    outFile << "@ARG" << endl;
    outFile << "M=D" << endl;
    
    // reposition LCL
    outFile << "@SP" << endl;
    outFile << "D=M" << endl;
    outFile << "@LCL" << endl;
    outFile << "M=D" << endl;
    
    // transfer control
    outFile << "@" << functionName << endl;
    outFile << "0;JMP" << endl;
    
    // declare label for return address
    outFile << "(RETURN" << labelNumber++ << ")" << endl;
    labelNumber++;
}


void CodeWriter::writeReturn(){
    
    // TEMP is a temporary variable
    outFile << "@LCL" << endl;
    outFile << "D=M" << endl;
    outFile << "@TEMP" << endl;
    outFile << "M=D" << endl;
    
    // Put the return address in a temp variable
    outFile << "@5" << endl;
    outFile << "D=A" << endl;
    outFile << "@TEMP" << endl;
    outFile << "A=M-D" << endl;
    outFile << "D=M" << endl;
    outFile << "@RET" << endl;
    outFile << "M=D" << endl;
    
    // Reposition the return value for the caller
    //POP TOP to REGISTER D
    outFile << "@SP" << endl;
    outFile << "AM=M-1" << endl;
    outFile << "D=M" << endl;
    
    outFile << "@ARG" << endl;
    outFile << "A=M" << endl;
    outFile << "M=D" << endl;
    
    // Restore SP of the caller
    outFile << "@ARG" << endl;
    outFile << "D=M+1" << endl;
    outFile << "@SP" << endl;
    outFile << "M=D" << endl;
    
    // Restore THAT of the caller
    outFile << "@TEMP" << endl;
    outFile << "A=M-1" << endl;
    outFile << "D=M" << endl;
    outFile << "@THAT" << endl;
    outFile << "M=D" << endl;
    
    // Restore THIS of the caller
    outFile << "@2" << endl;
    outFile << "D=A" << endl;
    outFile << "@TEMP" << endl;
    outFile << "A=M-D" << endl;
    outFile << "D=M" << endl;
    outFile << "@THIS" << endl;
    outFile << "M=D" << endl;
    
    // Restore ARG of the caller
    outFile << "@3" << endl;
    outFile << "D=A" << endl;
    outFile << "@TEMP" << endl;
    outFile << "A=M-D" << endl;
    outFile << "D=M" << endl;
    outFile << "@ARG" << endl;
    outFile << "M=D" << endl;
    
    // Restore LCL of the caller
    outFile << "@4" << endl;
    outFile << "D=A" << endl;
    outFile << "@TEMP" << endl;
    outFile << "A=M-D" << endl;
    outFile << "D=M" << endl;
    outFile << "@LCL" << endl;
    outFile << "M=D" << endl;
    
    // go to return-address
    outFile << "@RET" << endl;
    outFile << "A=M" << endl;
    outFile << "0;JMP" << endl;
}

void CodeWriter::writeFunction(string functionName, int numLocals)
{
    functionName_ = functionName;
    
    // Declare a label for the function entry
    outFile << "(" << functionName << ")" << endl;
    
    // initialize all the local varibles to 0
    for(int i=0;i<numLocals;i++)
        writePushPop(C_PUSH,"constant",0);
}

void CodeWriter::setOutputFileName(string outFileName)
{
    output_fileName = outFileName;
    outFileName = outFileName + ".asm";
    outFile.open(outFileName.c_str());
    if (!outFile.is_open())
        cerr << "Error: Cannot open " << outFileName << endl;
    writeInit();
    increm++;
}


#endif
