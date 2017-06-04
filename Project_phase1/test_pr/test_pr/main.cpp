#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirent.h"
#include <iostream>
#include <fstream>

using namespace std;

void search_count(string file_name,string search)
{
//    ifstream fin(file_name,ios::in | ios::out);
//    
//    string dict;
//    
//    long long int counter=0,pos;
//    
//    while (!fin.eof())
//    {
//        getline(fin, dict);
//        pos=dict.find(search);
//        
//        while (pos!=string::npos)
//        {
//            counter++;
//            dict.erase(dict.begin(), dict.begin()+ pos + search.length());
//            pos=dict.find(search);
//        }
//        
//    }
//    cout << counter<<"\t";
    cout<<file_name<<search;
}

int file_name(string search)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            cout<<ent->d_name<<endl;
            search_count(ent->d_name,search);
            
        }
        
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    return 1;
}

int main()
{
    string s="hello";
    file_name(s);
    return 0;
    
}