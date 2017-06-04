//
//  File_names.cpp
//  project
//
//  Created by Elahe on 12/18/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include "search_word.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "dirent.h"
#include <iostream>


using namespace std;

int file_name(string search)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/Users/codeWorm/Documents/education/Sharif University /CSE/Fundemental of programming/project/stupiddata/")) != NULL)
    {
        /* print all the files and directories within directory */

        while ((ent = readdir (dir)) != NULL)
        {
            cout<<ent->d_name<<"\t";
            cout<<search_count(search,ent->d_name)<<endl;
            
        }
        closedir (dir);
        return 1;
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
}