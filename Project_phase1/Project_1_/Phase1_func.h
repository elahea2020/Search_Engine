//
//  Phase1_func.h
//  Project_1_
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#ifndef __Project_1___Phase1_func__
#define __Project_1___Phase1_func__

#include <stdio.h>
#include <string>
#include <vector>

class Files
{
    std::string address;
public:
    std::string content;
    std::string name;
    Files(std::string address);
    void Cnt_Wrd(std::string target);
    void Rpl_Wrd(std::string target, std::string alter);
    void Prg_Wrd(std::string target);
};

void Find_adrs(std::string adrs, std::vector<Files>& dict_list);

void Prg_Wrd_Th(std::string content, std::string target, std::string name);

#endif /* defined(__Project_1___Phase1_func__) */
