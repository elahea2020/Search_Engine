//
//  main.cpp
//  tst_void_del
//
//  Created by Elahe on 12/25/15.
//  Copyright (c) 2015 Elahe. All rights reserved.
//

#include <iostream>
void Del_SWrd(std::string& stmstr)
{
    std::string SW[]={"a", "an", "and", "for", "is", "in", "of", "the", "with"};
    
    for (int i=0; i<stmstr.length(); i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(stmstr[i] == SW[j][0])
            {
                if (stmstr.substr(i,SW[j].size())==SW[j])
                {
                    if (i==0 || ((stmstr[i-1]< 'A' || stmstr[i-1]> 'Z') && (stmstr[i-1]< 'a' || stmstr[i-1]> 'z')))
                    {
                        if (i+SW[j].size()== '\0' || ((stmstr[i+SW[j].size()]< 'A' || stmstr[i+SW[j].size()]> 'Z') && (stmstr[i+SW[j].size()]< 'a' || stmstr[i+SW[j].size()]> 'z')))
                        {
                            stmstr.erase(i,SW[j].size()+1);
                            i--;
                        }
                    }
                }
            }
        }
    }
    
}

int main() {
    std::string s1="and I am an Amineh a apple for andy isi in";
    Del_SWrd(s1);
    std::cout<<s1;
    return 0;
}
