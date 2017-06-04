#include <iostream>
#include <cstring>
#include <string>

#include "dirent.h"

using namespace std;

void File_adrs(string adrs)
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
            cout<<ent->d_name<<endl;
        }
        else if (strcmp(ent->d_name, ".")!=0 && strcmp(ent->d_name, "..")!=0)
        {
           // cout<<"im in 2nd if";
            string p;
            p = adrs + "/" + ent->d_name;
            File_adrs(p);
        }
        
    }
    closedir(dir);
}

