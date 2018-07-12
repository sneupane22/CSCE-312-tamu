
#include <iostream>
#include <vector>
#include "Parser.h"
#include "CodeWriter.h"
using namespace std;


//int main(int argc, char *argv[]) {
//    
//    
//    string inputName;
//    cout << "Enter the name of the file WITH extension. \n";
//    cin >> inputName;
//    vector <char> directory;
//    //get rid of extension
//    if(strchr(inputName.c_str(), '/'))
//    {
//        //get name of directory so we can use same name for output file
//        int i = 0;
//        while (inputName[i] != '/')
//        {
//            directory.push_back(inputName[i]);
//            ++i;
//        }
//        string directoryName(directory.begin(),directory.end());
//        
//        
//        // change up here it can work for multiple files in the same directory
//        Parser VMF(inputName);
//        CodeWriter asmF;
//        asmF.setFileName(directoryName);
//        while(VMF.hasMoreCommands())
//        {
//            VMF.advance();
//            if(VMF.commandType() == C_ARITHMETIC)
//                asmF.writeArithmetic(VMF.arg1());
//            else if (VMF.commandType() == C_POP)
//                asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
//            else if (VMF.commandType() == C_PUSH)
//                asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
//            else if (VMF.commandType() == C_LABEL)
//                asmF.writeLabel(VMF.arg1());
//            else if(VMF.commandType() == C_GOTO)
//                asmF.writeGoto(VMF.arg1());
//            else if(VMF.commandType() == C_IF)
//                asmF.writeIf(VMF.arg1());
//            else if(VMF.commandType() == C_FUNCTION)
//                asmF.writeFunction(VMF.arg1(), VMF.arg2());
//            else if(VMF.commandType() == C_RETURN)
//                asmF.writeReturn();
//            else if(VMF.commandType() == C_CALL)
//                asmF.writeCall(VMF.arg1(), VMF.arg2());
//            
//        }
//        
//        
//        
//    }
//    else{
//        // only when single file is entered
//        Parser VMF(inputName);
//        //delete vm extension
//        for(int i = 0; i<=2; ++i)
//            inputName.pop_back();
//        
//        CodeWriter asmF(inputName);
//        while(VMF.hasMoreCommands())
//        {
//            VMF.advance();
//            if(VMF.commandType() == C_ARITHMETIC)
//                asmF.writeArithmetic(VMF.arg1());
//            else if (VMF.commandType() == C_POP)
//                asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
//            else if (VMF.commandType() == C_PUSH)
//                asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
//            else if (VMF.commandType() == C_LABEL)
//                asmF.writeLabel(VMF.arg1());
//            else if(VMF.commandType() == C_GOTO)
//                asmF.writeGoto(VMF.arg1());
//            else if(VMF.commandType() == C_IF)
//                asmF.writeIf(VMF.arg1());
//            else if(VMF.commandType() == C_FUNCTION)
//                asmF.writeFunction(VMF.arg1(), VMF.arg2());
//            else if(VMF.commandType() == C_RETURN)
//                asmF.writeReturn();
//            else if(VMF.commandType() == C_CALL)
//                asmF.writeCall(VMF.arg1(), VMF.arg2());
//            
//        }
//        
//    }
//    
//
////    //cout << inputName << endl;
////    Parser VMF(inputName);
////    CodeWriter asmF(inputName);
////    while(VMF.hasMoreCommands())
////    {
////        VMF.advance();
////        if(VMF.commandType() == C_ARITHMETIC)
////            asmF.writeArithmetic(VMF.arg1());
////        else if (VMF.commandType() == C_POP)
////            asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
////        else if (VMF.commandType() == C_PUSH)
////            asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
////        else if (VMF.commandType() == C_LABEL)
////            asmF.writeLabel(VMF.arg1());
////        else if(VMF.commandType() == C_GOTO)
////            asmF.writeGoto(VMF.arg1());
////        else if(VMF.commandType() == C_IF)
////            asmF.writeIf(VMF.arg1());
////        else if(VMF.commandType() == C_FUNCTION)
////            asmF.writeFunction(VMF.arg1(), VMF.arg2());
////        else if(VMF.commandType() == C_RETURN)
////            asmF.writeReturn();
////        else if(VMF.commandType() == C_CALL)
////            asmF.writeCall(VMF.arg1(), VMF.arg2());
////
////    }
//    cout<< "DONE: CHECK THE ASM FILE AND USE THE CPU EMULATOR TO TEST IT.\n";
//    return 0;
//}




//int main(int argc, char *argv[])
//{
//    CodeWriter asm1;
//    Parser vm1;
//    for(int i=1;i<argc;i++)
//    {
//        string filename = argv[i];
//        int dot = filename.find(".",0);
//        if(dot == -1)
//        {
//            asm1.setOutputFileName(filename); // directory name is the output .asm file name
//        }
//        else
//        {
//            filename = filename.substr(0,dot);
//            vm1.setFileName(filename);
//            asm1.setFileName(filename);
//        }
//        while (vm1.hasMoreCommands())
//        {
//            vm1.advance();
//            if (vm1.commandType() == C_ARITHMETIC)
//            {
//                asm1.writeArithmetic(vm1.arg1());
//            }
//            else if (vm1.commandType() == C_POP)
//            {
//                asm1.writePushPop(C_POP, vm1.arg1(), vm1.arg2());
//            }
//            else if (vm1.commandType() == C_PUSH)
//            {
//                asm1.writePushPop(C_PUSH, vm1.arg1(), vm1.arg2());
//            }
//            else if (vm1.commandType() == C_LABEL)
//            {
//                asm1.writeLabel(vm1.arg1());
//            }
//            else if(vm1.commandType() == C_GOTO)
//            {
//                asm1.writeGoto(vm1.arg1());
//            }
//            else if(vm1.commandType() == C_IF)
//            {
//                asm1.writeIf(vm1.arg1());
//            }
//            else if(vm1.commandType() == C_FUNCTION)
//            {
//                asm1.writeFunction(vm1.arg1(), vm1.arg2());
//            }
//            else if(vm1.commandType() == C_RETURN)
//            {
//                asm1.writeReturn();
//            }
//            else if(vm1.commandType() == C_CALL)
//            {
//                asm1.writeCall(vm1.arg1(), vm1.arg2());
//            }
//        }
//    }
//}







int main(int argc, char *argv[]) {
    
    string fileORDirect;
    cout << "Are you entering a single vm file or a directory? **** input should be \"single\" or \"directory\" (No quotes)\n";
    cin >> fileORDirect;


        if(fileORDirect == "directory")
        {
            cout << endl;
            int fileCount = 0;
            string inputName;
            cout << "Enter the name of the directory and the file within that directory. (ie NestedCall/Sys.vm .. etc)  \n";
            cin >> inputName;
            ++fileCount;

            vector <string> nameHandle;
            // get rid of .vm so for example NestedCall/Sys.vm --> NestedCall/Sys
            string fileNameHandler = inputName;
            for(int i = 0; i<=2; ++i)
                fileNameHandler.pop_back();
            //get everything after the / character
            string actualFile = fileNameHandler.substr(fileNameHandler.find("/") + 1);
            nameHandle.push_back(actualFile);
            
            
            vector <string> fileNames;
            fileNames.push_back(inputName);
            
            //----------
            //get name of directory so we can use same name for output file
            vector <char> directory;
            int i = 0;
            while (inputName[i] != '/')
            {
                directory.push_back(inputName[i]);
                ++i;
            }
            string directoryName(directory.begin(),directory.end());
            //----------
            
            string inputName2;
            while (inputName2 != "done")
            {
                cout << endl;
                cout << "Enter another file from the directory or input \"done\" if you do not wish to input anymore. (ie NestedCall/Sys.vm) \n";
                cin >> inputName2;
                if (inputName2 != "done")
                {
                    ++fileCount;
                    fileNames.push_back(inputName2);
                    string fileNameHandler = inputName2;
                    for(int i = 0; i<=2; ++i)
                        fileNameHandler.pop_back();
                    //get everything after the / character
                    string actualFile = fileNameHandler.substr(fileNameHandler.find("/") + 1);
                    nameHandle.push_back(actualFile);
                }
            }
            
            
            if (fileCount == 1){ // if the user enters only one file from the directoy then do this.
                cout << endl;
                cout << "File(s) Entered: \n";
                cout << inputName << endl;
                Parser VMF(inputName);
                CodeWriter asmF;
                asmF.setFileName(directoryName);
                asmF.output_fileName = nameHandle[0];
                while(VMF.hasMoreCommands())
                {
                    VMF.advance();
                    if(VMF.commandType() == C_ARITHMETIC)
                        asmF.writeArithmetic(VMF.arg1());
                    else if (VMF.commandType() == C_POP)
                        asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
                    else if (VMF.commandType() == C_PUSH)
                        asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
                    else if (VMF.commandType() == C_LABEL)
                        asmF.writeLabel(VMF.arg1());
                    else if(VMF.commandType() == C_GOTO)
                        asmF.writeGoto(VMF.arg1());
                    else if(VMF.commandType() == C_IF)
                        asmF.writeIf(VMF.arg1());
                    else if(VMF.commandType() == C_FUNCTION)
                        asmF.writeFunction(VMF.arg1(), VMF.arg2());
                    else if(VMF.commandType() == C_RETURN)
                        asmF.writeReturn();
                    else if(VMF.commandType() == C_CALL)
                        asmF.writeCall(VMF.arg1(), VMF.arg2());
                    
                }
                cout << endl;
                cout<< "DONE: CHECK THE ASM FILE AND USE THE CPU EMULATOR TO TEST IT.\n";
            }
            else if (fileCount > 1){ // if more than one file entered
                cout << endl;
                cout << "File(s) Entered: \n";
                for (int i = 0; i<fileNames.size(); ++i)
                    cout << fileNames[i] << endl;

                CodeWriter asmF;
                asmF.setFileName(directoryName);
                
                for (int i = 0; i<fileNames.size(); ++i)
                {
                    if (fileNames.size() == nameHandle.size())
                    {
                        Parser VMF(fileNames[i]);
                        asmF.output_fileName = nameHandle[i];
                        while(VMF.hasMoreCommands())
                        {
                            VMF.advance();
                            if(VMF.commandType() == C_ARITHMETIC)
                            {
                                asmF.writeArithmetic(VMF.arg1());
                                //cout << VMF.arg1() << endl;
                            }
                            else if (VMF.commandType() == C_POP)
                                asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
                            else if (VMF.commandType() == C_PUSH)
                                asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
                            else if (VMF.commandType() == C_LABEL)
                                asmF.writeLabel(VMF.arg1());
                            else if(VMF.commandType() == C_GOTO)
                                asmF.writeGoto(VMF.arg1());
                            else if(VMF.commandType() == C_IF)
                                asmF.writeIf(VMF.arg1());
                            else if(VMF.commandType() == C_FUNCTION)
                                asmF.writeFunction(VMF.arg1(), VMF.arg2());
                            else if(VMF.commandType() == C_RETURN)
                                asmF.writeReturn();
                            else if(VMF.commandType() == C_CALL)
                                asmF.writeCall(VMF.arg1(), VMF.arg2());
                            
                        }
                    }
                    
                }
                cout << endl;
                cout<< "DONE: CHECK THE ASM FILE AND USE THE CPU EMULATOR TO TEST IT.\n";
            }
            
            
        }
        else if (fileORDirect == "single"){
            cout << endl;
            string inputName;
            cout << "Enter the name of the file WITH extension. (ie BasicLoop.vm) \n";
            cin >> inputName;
            
            cout << endl << endl;
            cout << "File(s) Entered: \n";
            cout << inputName << endl << endl;;
            // only when single file is entered
            Parser VMF(inputName);
            //delete vm extension
            for(int i = 0; i<=2; ++i)
                inputName.pop_back();
            
            CodeWriter asmF(inputName);
            while(VMF.hasMoreCommands())
            {
                VMF.advance();
                if(VMF.commandType() == C_ARITHMETIC)
                {
                    asmF.writeArithmetic(VMF.arg1());
                    //cout << VMF.arg1() << endl;
                }
                else if (VMF.commandType() == C_POP)
                    asmF.writePushPop(C_POP, VMF.arg1(),VMF.arg2());
                else if (VMF.commandType() == C_PUSH)
                    asmF.writePushPop(C_PUSH, VMF.arg1(), VMF.arg2());
                else if (VMF.commandType() == C_LABEL)
                    asmF.writeLabel(VMF.arg1());
                else if(VMF.commandType() == C_GOTO)
                    asmF.writeGoto(VMF.arg1());
                else if(VMF.commandType() == C_IF)
                    asmF.writeIf(VMF.arg1());
                else if(VMF.commandType() == C_FUNCTION)
                    asmF.writeFunction(VMF.arg1(), VMF.arg2());
                else if(VMF.commandType() == C_RETURN)
                    asmF.writeReturn();
                else if(VMF.commandType() == C_CALL)
                    asmF.writeCall(VMF.arg1(), VMF.arg2());
                
            }
            cout<< "DONE: CHECK THE ASM FILE AND USE THE CPU EMULATOR TO TEST IT.\n";
            
        }
        else
            cerr << "Error: Please input \"single\" if you wish to input a single file or enter \"directory\" for a directory.\n";

    

    return 0;
}


