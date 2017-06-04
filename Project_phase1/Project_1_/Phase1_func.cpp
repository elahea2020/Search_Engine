//
//  Phase1_func.cpp
//  Project_1_
//
//  Created by Elahe on 12/20/15.
//  Copyright (c) 2015 Elahe & Amineh. All rights reserved.
//

#include "Phase1_func.h"
#include "dirent.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

std::ifstream fin;
std::ofstream fout;

void Find_adrs(std::string adrs, std::vector<Files>& dict_list)
{
    DIR *dir;
    struct dirent *ent;
    
    if(opendir(adrs.c_str())!=NULL)
        dir = opendir(adrs.c_str());
    else
    {
        dir=NULL;
        Files a(adrs);
        a.name = "your file";
        dict_list.push_back(a);
        return;
    }
    
    while((ent = readdir(dir)) != NULL)
    {
        if (opendir((adrs + "/" + ent->d_name).c_str()) == NULL)
        {
            std::string p;
            p = adrs + "/" + ent->d_name;
            Files a(p);
            a.name = ent->d_name;
            dict_list.push_back(a);
        }
        else if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            std::string p;
            p = adrs + "/" + ent->d_name;
            Find_adrs(p, dict_list);
        }
    }
    
    closedir(dir);
}

Files::Files(std::string address)
{
    this->address = address;
    fin.open (this->address.c_str(), std::ios::in);
    std:: stringstream buffer;
    buffer << fin.rdbuf();
    this->content = buffer.str();
    fin.close();
}

void Files::Cnt_Wrd(std::string target)
{
    size_t counter = 0;
    size_t pos = this->content.find(target);
    
    while (pos != std::string::npos)
    {
        if ((pos == 0) || ((this->content[pos - 1] < 'A' || this->content[pos - 1] > 'Z') && (this->content[pos - 1] < 'a' || this->content[pos - 1] > 'z')))
        {
            if((this->content[pos + target.length()] < 'A' || this->content[pos + target.length()] > 'Z') && (this->content[pos + target.length()] < 'a' || this->content[pos + target.length()] > 'z'))
            {
                counter ++;
            }
        }
        pos = this->content.find(target, pos + 1);
    }

    std::cout << "Found "<< counter<< " "<< target<< " in file: "<< this->name<< std::endl;
}

void Files::Rpl_Wrd(std::string target, std::string alter)
{
    size_t pos = this-> content.find(target);
    
    while (pos != std::string::npos)
    {
        if ((pos == 0) || ((this->content[pos - 1] < 'A' || this->content[pos - 1] > 'Z') && (this->content[pos - 1] < 'a' || this->content[pos - 1] > 'z')))
        {
            if((this->content[pos + target.length()] < 'A' || this->content[pos + target.length()] > 'Z') && (this->content[pos + target.length()] < 'a' || this->content[pos + target.length()] > 'z'))
            {
                this->content.replace(pos, target.length(), alter);
            }
        }
        pos = this->content.find(target, pos + 1);
    }
    
    fout.open(this->address.c_str(),std::ios::out);
//    std:: stringstream buffer;
//    buffer.str() = this->content;
//    fout << buffer.str();
    fout<<this->content;
    fout.close();
}

void Files::Prg_Wrd(std::string target)
{
    size_t posT = this->content.find(target);
    size_t posP = this->content.find("\n\n");
    size_t cntrP = 1;
    size_t cntrT = 0;
    bool flag = 0; //This is so we don't print the file name twice
    
    while (posT != std::string::npos)
    {
        cntrT = 0;
        
        while (posT < posP)
        {
            if ((posT == 0) || ((this->content[posT - 1] < 'A' || this->content[posT - 1] > 'Z') && (this->content[posT - 1] < 'a' || this->content[posT - 1] > 'z')))
            {
                if((this->content[posT + target.length()] < 'A' || this->content[posT + target.length()] > 'Z') && (this->content[posT + target.length()] < 'a' || this->content[posT + target.length()] > 'z'))
                {
                    if(flag == 0)
                    {
                        std:: cout << "File: " << this->name << std::endl;
                        flag = 1;
                    }
                    cntrT++;
                }
            }
            posT = this->content.find(target, posT + 1);
        }
        
        if (cntrT!=0)
        {
            std::cout << "Found " << cntrT << " " << target << " in paragraph number: " << cntrP << std::endl;
        }
        
        cntrP++;
        posP = this->content.find("\n\n" , posP+1);

    
    }
}

void Prg_Wrd_Th(std::string content, std::string target, std::string name)
{
    size_t posT = content.find(target);
    size_t posP = content.find("\n\n");
    size_t cntrP = 1;
    size_t cntrT = 0;
    bool flag = 0; //This is so we don't print the file name twice
    
    while (posT != std::string::npos)
    {
        cntrT = 0;
        
        while (posT < posP)
        {
            if ((posT == 0) || ((content[posT - 1] < 'A' || content[posT - 1] > 'Z') && (content[posT - 1] < 'a' || content[posT - 1] > 'z')))
            {
                if((content[posT + target.length()] < 'A' || content[posT + target.length()] > 'Z') && (content[posT + target.length()] < 'a' || content[posT + target.length()] > 'z'))
                {
                    if(flag == 0)
                    {
                        std:: cout << "File: " << name << std::endl;
                        flag = 1;
                    }
                    cntrT++;
                }
            }
            posT = content.find(target, posT + 1);
        }
        
        if (cntrT!=0)
        {
            std::cout << "Found " << cntrT << " " << target << " in paragraph number: " << cntrP << std::endl;
        }
        
        cntrP++;
        posP = content.find("\n\n" , posP+1);
        
        
    }
}
