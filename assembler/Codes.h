//
//  Codes.h
//  assembler
//
//  Created by Mitesh Patel on 3/24/16.
//  Copyright (c) 2016 TAMU. All rights reserved.
//

#ifndef assembler_Codes_h
#define assembler_Codes_h



#include <map>
#include <string>

using namespace std;

class Dest {
    private:
        map<string, string> codes;
    public:
        Dest();
        string getBinaryCode(string m) {return codes[m];} // return binary code of the operation/variable/jump
};

Dest::Dest() {
    codes["null"] = "000"; //<"null","000">
    codes["M"]="001";// <"M","001">.. etc
    codes["D"]="010";
    codes["MD"]="011";
    codes["A"]="100";
    codes["AM"]="101";
    codes["AD"]="110";
    codes["AMD"]="111";
}

class Comp {
    private:
        map<string, string> codes;
    public:
        Comp();
        string getBinaryCode(string m) {return codes[m];}
};

Comp::Comp() {
    //abit = 0
    codes["0"]="101010";
    codes["1"]="111111";
    codes["-1"]="111010";
    codes["D"]="001100";
    codes["A"]="110000";	
    codes["!D"]="001101";
    codes["!A"]="110001";	
    codes["-D"]="001111";
    codes["-A"]="110011";	
    codes["D+1"]="011111";
    codes["A+1"]="110111";	
    codes["D-1"]="001110";
    codes["A-1"]="110010";	
    codes["D+A"]="000010";	
    codes["D-A"]="010011";	
    codes["A-D"]="000111";
    codes["D&A"]="000000";
    codes["D|A"]="010101";
    // abit=1
    codes["M"]="110000";
    codes["!M"]="110001";
    codes["-M"]="110011";
    codes["M+1"]="110111";
    codes["M-1"]="110010";
    codes["D+M"]="000010";
    codes["D-M"]="010011";
    codes["M-D"]="000111";
    codes["D&M"]="000000";
    codes["D|M"]="010101";
}

class Jump {
    private:
        map<string, string> codes;
    public:
        Jump();
        string getBinaryCode(string m) {return codes[m];}
};

Jump::Jump() {
    codes["null"] = "000";
    codes["JGT"]="001";
    codes["JEQ"]="010";
    codes["JGE"]="011";
    codes["JLT"]="100";
    codes["JNE"]="101";
    codes["JLE"]="110";
    codes["JMP"]="111";
}











#endif
