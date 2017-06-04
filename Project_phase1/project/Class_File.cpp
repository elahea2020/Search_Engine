//
//  Class_File.cpp
//  project
//
//  Created by Elahe on 12/19/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include "Class_File.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace::std;

ifstream fin;
ofstream fout;
class Files
{
    
    public:
    
        string address;
        string file_string;
        string copy_file_string;
        Files(string address)
        {
            this->address=address;
            fin.open(this->address.c_str(),ios::in);
            stringstream buffer;
            buffer <<fin.rdbuf();
            this->file_string=buffer.str();
            fin.close();
            copy_file_string = file_string;
        }
    
    
    
    
};
