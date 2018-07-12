

#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"
using namespace std;

int main(int argc, char *argv[]) {
    

    string inputName;
    cout << "Enter the name of the file with NO extension. (ie SimpleAdd, etc..)\n";
    cin >> inputName;
    Parser VMF(inputName);
    CodeWriter asmF(inputName);
        while(VMF.hasMoreCommands())
        {
            VMF.advance();
            if(VMF.commandType() == C_ARITHMETIC)
            {
                asmF.writeArithmetic(VMF.arg1());
//                if (VMF.arg1() == "add")
//                {
//                    cout << "INSIDE \n";
//                    asmF.writeArithmetic(VMF.arg1());
//                }
                //string arg = VMF.arg1();
                //if(arg.compare("add"))
                //{
                //    cout << "INSIDE ADD \n";
                 //   string arg = VMF.arg1();
                //cout << arg << ".. Size: " << arg.length() << endl;
                
                //}
                //else if(arg.compare("eq"))
                //{
                //    cout << "INSIDE EQ \n";
                //    asmF.writeArithmetic(VMF.arg1());
               //}
            }
            else if (VMF.commandType() == C_POP)
                asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
            else if (VMF.commandType() == C_PUSH)
                asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
        }
        cout<< "DONE: CHECK THE ASM FILE AND USE THE CPU EMULATOR TO TEST IT.\n";
        return 0;
}

