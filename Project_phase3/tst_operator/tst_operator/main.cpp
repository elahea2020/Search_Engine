//
//  main.cpp
//  tst_operator
//
//  Created by Elahe on 1/24/16.
//  Copyright (c) 2016 Elahe. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
class test
{
public:
    bool a[3];
    test operator!()
    {
        test temp;
        for (int i = 0 ; i < 3 ; i++)
        {
            temp.a[i] = ! a[i];
//            if(a[i] == 0)
//                temp.a[i] = 1;
//            else
//                temp.a[i] = 0;
        }
        return temp;
    }
};
union u
{
    char c;
    test khar;
};

enum Type {letter = -1, prnth, opr};

int main(int argc, const char * argv[])
{
    test salam;
    salam.a[0] = 1;
    salam.a[1] = 0;
    salam.a[2] = 0;
    salam = !salam;
    
//    enum types {hi, bye};
//    types a = hi;
//    int pri = -1;
//    if(a == pri + hi)
//        std::cout << "HI\n";
    
//    std:: cout <<salam.a[0] << salam.a[1]<< salam.a[2];
//    
//    int a = 2;
//    std::string str = "hello";
//    str[0] = a;
//    std::cout << str[0];
//    std::vector<u> uniontor;
//    u test1;
//    u test2;
//    test1.khar = salam;
//    test2.c = 'h';
//    uniontor.push_back(test1);
//    uniontor.push_back(test2);
//    Type a1 = letter++;
//    std::cout<<a1<<std::endl;
//    std::cout << uniontor[0].khar.a[0];//<<" "<<uniontor[1]<<"\n";
////    
//    std::cout << isalpha('a');
//    std::cout << isalpha('~');
    
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    int j = 0;
    v.erase(v.begin() + j);
    std::cout << v[1];
    //for(int i = 0; i < v.size(); i++)
    //    std::cout<<v[i] << " ";
    return 0;
}
