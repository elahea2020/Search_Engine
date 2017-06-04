//
//  Phase1_funcs.cpp
//  project
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include "Phase1_funcs.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "dirent.h"

using namespace std;


ifstream fin;
ofstream fout;

Files::Files(string address)
{
    this->address=address;
    fin.open(this->address.c_str(),ios::in);
    stringstream buffer;
    buffer <<fin.rdbuf();
    this->file_string=buffer.str();
    fin.close();
    copy_file_string = file_string;
}

// Files::over_write(string Input)
//{
//    fout.open(this->address.c_str(),ios::out);
//    stringstream buffer;
//    fout<<Input.c_str();
//    fout.close();
//}

void Address_of_Files(string adrs, vector<Files>& dict_list)
{
    DIR *dir;
    struct dirent *ent;
    
    if(opendir(adrs.c_str())!=NULL)
        dir = opendir(adrs.c_str());
    else
        dir=NULL;
    
    
    while( (ent = readdir(dir))!= NULL )
    {
        if (opendir((adrs + "/" + ent->d_name).c_str())==NULL)
        {
            //  cout<<"im in 1st if\t";
            string p;
            p = adrs + "/" + ent->d_name;
            //             Files a(p);
            Files a(p);
            dict_list.push_back(a);
            //cout<<ent->d_name<<endl;
        }
        else if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0)
        {
            // cout<<"im in 2nd if";
            string p;
            p = adrs + "/" + ent->d_name;
            Address_of_Files(p, dict_list);
        }
        
    }
    closedir(dir);
}



size_t search_count(string search, string file_string)
{
    
    size_t paragraph_counter=0;
    size_t search_counter=0;
    size_t pos_search=0;
    size_t pos_paragraph=0;
    
    pos_search=file_string.find(search);
    
    if ( (pos_search==0) || ( ( file_string[pos_search-1]<'A' || file_string[pos_search-1]>'Z' ) && (file_string[pos_search-1]<'a' || file_string[pos_search-1]>'z') ) )
    {
        if( ( file_string[pos_search+search.length()]<'A' || file_string[pos_search+search.length()]>'Z' ) && (file_string[pos_search+search.length()]<'a' || file_string[pos_search+search.length()]>'z') )
        {
            search_counter+=(pos_search!=string::npos);
        }
    }
    
    
    while (pos_search!=string::npos)
    {
        pos_paragraph=file_string.find("\n\n");
        
        paragraph_counter+=(pos_paragraph!=string::npos);
        
        if (pos_paragraph==string::npos)
        {
            pos_paragraph=file_string.length();
        }
        
        if (pos_search<pos_paragraph)
        {
            
            do
            {
                cout<<"found one in paragraph num"<<paragraph_counter<<endl;
                file_string.erase(file_string.begin(),file_string.begin()+pos_search+search.length());
                pos_paragraph-=pos_search +search.length();
                pos_search=file_string.find(search);
                
                if ( (pos_search==0) || ( ( file_string[pos_search-1]<'A' || file_string[pos_search-1]>'Z' ) && (file_string[pos_search-1]<'a' || file_string[pos_search-1]>'z') ) )
                {
                    if( ( file_string[pos_search+search.length()]<'A' || file_string[pos_search+search.length()]>'Z' ) && (file_string[pos_search+search.length()]<'a' || file_string[pos_search+search.length()]>'z') )
                    {
                        search_counter+=(pos_search!=string::npos);
                    }
                }
                
                
            }while (pos_search<pos_paragraph && pos_search!=string::npos);
            
        }
        
        else if(pos_paragraph!=string::npos)
        {
            file_string.erase(file_string.begin(),file_string.begin()+pos_paragraph+search.length());
            pos_search=file_string.find(search);
            
        }
        
        
    }
    printf("paragraph= %zu\n",paragraph_counter);
    return search_counter;
    
}

//void File_replace(string& file_string, string& search, string& rep)
//{
//    size_t pos_search = file_string.find(search);
//    while(pos_search != string::npos)
//    {
//        if ( (pos_search==0) || ( ( file_string[pos_search-1]<'A' || file_string[pos_search-1]>'Z' ) && (file_string[pos_search-1]<'a' || file_string[pos_search-1]>'z') ) )
//        {
//            if( ( file_string[pos_search+search.length()]<'A' || file_string[pos_search+search.length()]>'Z' ) && (file_string[pos_search+search.length()]<'a' || file_string[pos_search+search.length()]>'z') )
//            {
//                file_string.replace(pos_search, search.length(), rep);
//            }
//        }
//        pos_search = file_string.find(search, pos_search + 1);
//    }
//    
//    
//}

void File_replace(vector<Files>& dict_list, string search, string rep, int i)
{
    string file_string;
    
    file_string=dict_list[i].file_string;
    
    size_t pos_search = file_string.find(search);
    
    while( pos_search != string::npos)
    {
        if ( file_string[pos_search-1]== '\n' || (pos_search==0) || ( ( file_string[pos_search-1]<'A' || file_string[pos_search-1]>'Z' ) && (file_string[pos_search-1]<'a' || file_string[pos_search-1]>'z') ) )
        {
            if( ( file_string[pos_search+search.length()]== '\n' )|| ( ( file_string[pos_search+search.length()]<'A' || file_string[pos_search+search.length()]>'Z' ) && (file_string[pos_search+search.length()]<'a' || file_string[pos_search+search.length()]>'z') ))
            {
                file_string.replace(pos_search, search.length(), rep);
            }
        }
        pos_search = file_string.find(search, pos_search + 1);
    }
    dict_list[i].file_string=file_string;
    
}


