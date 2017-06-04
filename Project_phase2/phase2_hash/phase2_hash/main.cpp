//
//  main.cpp
//  phase2_hash
//
//  Created by Elahe on 12/29/15.
//  Copyright (c) 2015 Elahe. All rights reserved.
//

#include <iostream>

class Files
{
    std::string address;
public:
    std::string content; /* The content of file*/
    std::string stmstr; /* The stemmed content by Porter algorithm*/
    std::string name;
    Files(std::string address);
    void Cnt_Wrd(std::string target);
    void Rpl_Wrd(std::string target, std::string alter);
    void Prg_Wrd(std::string target);
    void Del_SWrd();
};

void insert_hash(Files f)
{
    
}

int main()
{
    
    return 0;
}
