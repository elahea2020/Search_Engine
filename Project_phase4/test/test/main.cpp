//
//  main.cpp
//  test
//
//  Created by Elahe on 1/29/16.
//  Copyright (c) 2016 Elahe. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

std::ifstream fin;
void test1 (std::vector<std::pair<std::string, std::string> > &mistakes)
{
    std::pair<std::string, std::string> a;
    a.first = "hello";
    a.second = "world";
    mistakes.push_back(a);
    std::cout<<mistakes[0].first << mistakes[0].second;
    std::cout<<"\n\t\t\tMISTAKE SIZE = "<<mistakes.size()<<"\n";
}
std::ofstream fout;
int main()
{
////    std::vector<char> v;
////    char arr[4] = {'a', 'b', 'c'};
//////    v.insert(v.begin(), arr, arr+3);
//////    
//////    std::cout << v[0] << v[1] <<v[2];
//////
////    char a = tolower('A');
////    std::cout << tolower('A') << a;
//    
////    std::string str = "hello"; str.erase(str.begin()+2);
////    str.insert(str.length(), 1, 'a');
////    int j = 1;
////    str.replace(j+2, 1,1, 'x');
////    std::cout<< str;
//    std::string dictionary;
//   // fin.open("/Users/codeWorm/Documents/education/Sharif University /CSE/Fundemental of programming/project_codes/Project_phase4/test/test/eng_com.txt",std::ios::in);
//    fin.open("/khar");
//    std:: stringstream buffer;
//    buffer << fin.rdbuf();
//    dictionary = buffer.str();
//    std::cout << "dictionary is:\n" << dictionary << "dictionary is finished!\n";
//    fin.close();
    
    std::vector<std::pair<std::string, std::string> > mistakes;
    test1 (mistakes);
    std::cout<<mistakes[0].first << mistakes[0].second;
    std::cout<<"\n\t\t\tMISTAKE SIZE = "<<mistakes.size()<<"\n";
//    fout.open("mistakes",std::ios::out);
//    fout<<&mistakes;
//    fout.close();
    std::string hel = "hey khare aziz";
    fout.open("mistakes");
    fout<<hel;
    fout.close();
    
    return 0;
}
