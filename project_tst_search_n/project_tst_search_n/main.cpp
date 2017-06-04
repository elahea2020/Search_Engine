//
//  main.cpp
//  project_tst_search_n
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string search="hel";
    string target="hel hello Iam ,hello,hel  hel .hel. hel ";
    int counter=0;
    size_t pos;
//    printf("%d %d %d %d",'a','z','A','Z');
    while (target.find(search)!=string::npos)
    {
        pos=target.find(search);
        //cout<<"pos after find is: "<<pos<<endl;
        if ( (pos==0) || ( ( target[pos-1]<'A' || target[pos-1]>'Z' ) && (target[pos-1]<'a' || target[pos-1]>'z') ) )
        {
            //cout<<"Bin Im If\n";
            if( ( target[pos+search.length()]<'A' || target[pos+search.length()]>'Z' ) && (target[pos+search.length()]<'a' || target[pos+search.length()]>'z') )
                {
                    cout<<"pos is: "<<pos<<endl;
                counter++;
                }
        }
        target.erase(target.begin(),target.begin()+pos+search.length());
        cout<<"Im in while"<<endl;
    }
    cout<<counter;
    return 0;
}
