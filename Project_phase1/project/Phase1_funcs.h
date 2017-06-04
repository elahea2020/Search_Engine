//
//  Phase1_funcs.h
//  project
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#ifndef __project__Phase1_funcs__
#define __project__Phase1_funcs__

#include <string>
#include <vector>

using namespace std;


class Files
{
    
public:
    
    string address;
    string file_string;
    string copy_file_string;
    
    Files(string address);    
//    Files over_write(string Input);
};

void Address_of_Files(string adrs, vector<Files>& dict_list);

size_t search_count(string search,string file_name);

void File_replace(vector<Files>& dict_list, string search, string rep, int i);

#endif /* defined(__project__Phase1_funcs__) */
