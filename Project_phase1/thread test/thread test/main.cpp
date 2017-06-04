//
//  main.cpp
//  thread test
//
//  Created by Elahe on 12/21/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include <iostream>
#include <thread>
#include <vector>

void avr(int i){
    std::cout<<i<<" Hel"<<std::endl;
}

class tst_class
{
public:
  //  int x;
    void print(int i)
    {
        std::cout<</*x**/i;
    }
};
int main() {
//    std::vector<std::thread> th;
//    //std:: thread th;
//    for(int i = 0; i < 10; i++)
//    {
//        //std::thread th(avr, i);
//        th.push_back(std::thread(avr, i));
//    }
//    auto originalThread = th.begin();
//    
//    while(originalThread != th.end())
//    {
//        originalThread->join();
//        originalThread++;
//    }
//    for(int i = 0; i < 10; i++)
//    {
//        th[i].join();
//    }
    int i=12;
    std::thread t1(avr,i);
    t1.join();
    tst_class tst_1[100];
//   tst_1[0].x=12;
//   tst_1[0].print(i);
    std::thread t2(tst_1[0].print(i));
    t2.join();
    return 0;
}
