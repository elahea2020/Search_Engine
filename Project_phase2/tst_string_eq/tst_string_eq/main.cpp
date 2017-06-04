//
//  main.cpp
//  tst_string_eq
//
//  Created by Elahe on 12/25/15.
//  Copyright (c) 2015 Elahe. All rights reserved.
//

#include <iostream>
#include <string>
int main()
{
    std::string s1="HEllo asfasf asdas";
    std::string s2="HEllo";
    std::cout<<(s1.substr(0,s2.length())==s2);
    return 0;
}
