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
    std::string content; /* The content of file*/
    std::string stmstr; /* The stemmed content by Porter algorithm*/
    std::string name;
    Files(std::string address);
    void Cnt_Wrd(std::string target);
    void Rpl_Wrd(std::string target, std::string alter);
    void Prg_Wrd(std::string target);
    void Del_SWrd();
};

class Words
{
public:
    std::string name;
    int doc_frq;
    size_t num_file;
    std::vector<std::string> doc_name; //Phase 2
    bool* doc_bool; //Phase 3: 0 = not exist, 1 = exists in doc
    enum Types {letter, prnth, NOT, AND, OR};
    Types type;
    Words(size_t num_file);
    Words(char c);
    Words operator&(Words w1);
    Words operator!();
    Words operator|(Words w1);
};

void Find_adrs(std::string adrs, std::vector<Files>& dict_list);

void Prg_Wrd_Th(std::string content, std::string target, std::string name);

void Insert_Hash(std::vector<Files>& all_files, std::vector<Words> hash[], int size_hash);

void Search_Hash(std::string target, std::vector<Words> hash[], int size_hash);

void Rpl_Bool (std::string& input, std::string target, std::string alter);

void Del_Spaces(std::string& input);

void Boolean_Search (std::string& Sinput, int hash_size, std::vector<Words> hash[], size_t num_file, std::vector<Files>& all_files);

void Boolean_oprt(std::vector<Words>& Vinput, size_t from, size_t end);

void Rec_Prnth2(std::vector<Words>& Vinput);

#endif /* defined(__Project_1___Phase1_func__) */
