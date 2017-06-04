//
//  main.cpp
//  project
//
//  Created by Elahe on 12/18/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Phase1_funcs.h"

int main()
{
    
    vector<Files> dict_list;
    string address="/Users/codeWorm/Documents/education/Sharif University /CSE/Fundemental of programming/project_codes/project/1";
    Address_of_Files(address, dict_list);
    string search;
    string replace;
    int stage=0;
    cin>>stage;
    cin>>search;
    
    if (stage==3)
    {
        cin>>replace;
        for (int i=0;i<dict_list.size();i++)
        {
 //           File_replace(dict_list[i].file_string, search, replace);
        }
    }
    
    else
    {
        for (int i=0;i<dict_list.size();i++)
        {
            cout<<search_count(search, dict_list[i].copy_file_string);
        }
    }
    
    
    
    return 0;
    
}