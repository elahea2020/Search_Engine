//
//  search_word.cpp
//  project
//
//  Created by Elahe on 12/18/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//



#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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
        pos_paragraph=file_string.find("\n");
        
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

int main()
{
    
    ifstream fin("1'.txt");
    stringstream buffer;
    buffer << fin.rdbuf();
    string s=buffer.str();
    cout<<s;
    
    
    cout<<endl<<search_count("I", s);
    fin.close();
    return 0;
}
