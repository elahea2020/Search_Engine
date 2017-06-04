//
//  main.cpp
//  hash_tst
//
//  Created by Elahe on 12/29/15.
//  Copyright (c) 2015 Elahe. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
class Words
{
public:
    std::string name;
    int doc_frq;
    std::vector<std::string> doc_name;
};

void Insert_Hash(std::string stmstr, std::vector<Words> hash[], int size_hash)
{

 
        int j = 0;
        while (j < stmstr.size())
        {
            std::string word;
            int key = 0;
            while (stmstr[j] != ' ')
            {
                word += stmstr[j];
                key += stmstr[j];
                j++;
            }
            key %= size_hash;
            //checks if the word exists in vector number [key]
            bool exist = 0;
            for (int p = 0; p < hash[key].size(); p++)
            {
                if (hash[key][p].name == word)
                {
                    exist = 1;
                    hash[key][p].doc_frq ++;
                    //hash[key][p].doc_name.push_back(temp.name);
                }
            }
            if (exist == 0)
            {
                Words a;
                a.name = word;
                a.doc_frq = 1;
                //a.doc_name.push_back(temp.name);
                hash[key].push_back(a);
            }
            j++;
        }
}

void Search_Hash(std::string target, std::vector<Words> hash[])
{
    int key = 0;
    std::string stmTrgt;
//    stemfile(target, stmTrgt);
    for (int i = 0; i < stmTrgt.length(); i++)
    {
        key += target[i];
    }
    
    for (int i = 0; i < hash[key].size(); i++)
    {
        if (stmTrgt == hash[key][i].name)
        {
            std::cout << target << " exists in file(s) : \n";
            for(int j = 0; j < hash[key][i].doc_name.size(); j++)
            {
                std::cout << "/t" << hash[key][i].doc_name[j] << std::endl;
            }
            return;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
