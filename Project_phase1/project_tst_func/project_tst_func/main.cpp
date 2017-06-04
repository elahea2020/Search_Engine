//
//  main.cpp
//  project_tst_func
//
//  Created by Elahe on 12/18/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    string filename="1.txt";
    ifstream fin;
    fin(filename);
    
    ofstream fout;
    string dict,search;
    cin>>search;
    long long int counter=0,pos;
    while (!fin.eof())
    {
        getline(fin, dict);
        pos=dict.find(search);
        
        while (pos!=string::npos)
        {
            counter++;
            dict.erase(dict.begin(), dict.begin()+ pos + search.length());
            pos=dict.find(search);
        }

    }
    
    return 0;
}
