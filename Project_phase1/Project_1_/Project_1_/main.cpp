//
//  main.cpp
//  Project_1_
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Phase1_func.h"

int main()
{
    std:: string address;
    address = "/Users/codeWorm/Desktop/data 2";
    std:: vector <Files> all_files;
    Find_adrs(address, all_files);
    int stage;
    std:: cout<< "Choose one of the following actions:\n";
    std:: cout<< "1) Count the repetitions of a word\n";
    std:: cout<< "2) Replace a word\n";
    std:: cout<< "3) Find the paragraph of a word\n";
    std:: cin>> stage;
    std:: string target;
    std:: cout<<"Enter your word\n";
    std:: cin>> target;
    
    std:: vector <std::thread> th;
    
    switch (stage)
    {
        case 1:
        {
            for (int i = 0; i < all_files.size(); i++)
            {
                all_files[i].Cnt_Wrd(target);
            }
            break;
        }
            
        case 2:
        {
            std::string alter;
            std::cout<<"Enter the second word\n";
            std::cin>> alter;
            for (int i = 0; i < all_files.size(); i++)
            {
                all_files[i].Rpl_Wrd(target, alter);
            }
            break;
        }
            
        case 3:
        {

//          **** the following code run the third case in the ordinary way ***
//            for (int i = 0; i < all_files.size(); i++)
//            {
//                all_files[i].Prg_Wrd(target);
//            }
            
////            ***** thread way *****
            for (int i = 0; i < all_files.size(); i++)
            {
          //      std:: thread t1(Prg_Wrd_Th,all_files[i].content, target, all_files[i].name);
                
               th.push_back(std:: thread (Prg_Wrd_Th,all_files[i].content, target, all_files[i].name));
            }
            std::vector<std::thread>::iterator originalThread = th.begin();
            while(originalThread != th.end())
            {
                originalThread -> join();
                originalThread ++;
            }
            break;
        }
            
        default:
        {
            std:: cout << "We're Shakh and we know it!\n";
            break;
        }
    }
    
    return 0;
}
