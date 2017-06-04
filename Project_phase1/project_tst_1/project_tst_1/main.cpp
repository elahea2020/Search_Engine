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
    //search.insert(0," ");
    //    search.insert(search.length()," ");
    //    cout<<"."<<search<<"."<<endl;
    size_t paragraph_counter=0;
    size_t search_counter=0;
    size_t pos_search=0;
    size_t pos_paragraph=0;
    
    pos_search=file_string.find(search);
    
    search_counter+=(pos_search!=string::npos);
    
    //    cout<<"search_counter= "<<search_counter<<endl;
    
    while (pos_search!=string::npos)
    {
        //cout<<"paragraphs= "<<paragraph_counter<<endl;
        pos_paragraph=file_string.find("\n");
        
        paragraph_counter+=(pos_paragraph!=string::npos);
        
        if (pos_paragraph==string::npos)
        {
            pos_paragraph=file_string.length();
        }
        
        if (pos_search<pos_paragraph)
        {
            //            paragraph_counter++;
            
            do
            {
                cout<<"found one in paragraph num"<<paragraph_counter<<endl;
                file_string.erase(file_string.begin(),file_string.begin()+pos_search+search.length());
                //                cout<<file_string<<endl;
                pos_paragraph-=pos_search +search.length();
                pos_search=file_string.find(search);
                if (pos_search!=string::npos)
                {
                    search_counter++;
                    //                    cout<<"found one in paragraph num"<<paragraph_counter<<endl;
                }
                
                
            }while (pos_search<pos_paragraph && pos_search!=string::npos);
            
        }
        
        else if(pos_paragraph!=string::npos)
        {
            file_string.erase(file_string.begin(),file_string.begin()+pos_paragraph+search.length());
            //            cout<<file_string<<endl;
            //paragraph_counter++;
            pos_search=file_string.find(search);
            //search_counter+=(pos_search!=string::npos);
        }
        //cout<<"search_counter "<<search_counter<<endl;
        
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
    //    cout<<s1.find("l");
    return 0;
}
