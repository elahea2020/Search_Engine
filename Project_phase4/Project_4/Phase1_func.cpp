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
#include "Porter_alg.h"

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
    //Copying the content of file in content string
    this->address = address;
    fin.open (this->address.c_str(), std::ios::in);
    std:: stringstream buffer;
    buffer << fin.rdbuf();
    this->content = buffer.str();
    fin.close();
    
    //Stemming the content
    stemfile(this->content, this->stmstr);
    this->stmstr.erase(stmstr.begin());       //deleting the space of the beginning
    
    //Deleting stop words
    Del_SWrd();
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

void Files::Del_SWrd()
{
    std::string SW[]={"a", "an", "and", "for", "is", "in", "of", "the", "with"};
    
    for (int i=0; i<this->stmstr.length(); i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(this->stmstr[i] == SW[j][0])
            {
                if (this->stmstr.substr(i,SW[j].size())==SW[j])
                {
                    if (i==0 || ((this->stmstr[i-1]< 'A' || this->stmstr[i-1]> 'Z') && (this->stmstr[i-1]< 'a' || this->stmstr[i-1]> 'z')))
                    {
                        if (i+SW[j].size()== '\0' || ((this->stmstr[i+SW[j].size()]< 'A' || this->stmstr[i+SW[j].size()]> 'Z') && (this->stmstr[i+SW[j].size()]< 'a' || this->stmstr[i+SW[j].size()]> 'z')))
                        {
                            this->stmstr.erase(i,SW[j].size()+1);
                            i--;
                        }
                    }
                }
            }
        }
    }
}

Words::Words(size_t num_file)
{
    this->type = letter;
    this->num_file = num_file;
    this->doc_bool = new bool[num_file];
    for (int i = 0; i < num_file ; i++)
    {
        doc_bool[i] = 0;
    }
}

Words::Words(char c)
{
    this->name += c;
    if (c == '(' || c == ')')
    {
        this->type = prnth;
    }
    else if (c == '!')
        this->type = NOT;
    else if (c == '&')
        this->type = AND;
    else if (c == '|')
        this->type = OR;
    
}

Words Words::operator&(Words w1)
{
    Words temp(this->num_file);
    for (int i = 0; i < this->num_file; i++)
    {
        temp.doc_bool[i] = this->doc_bool[i] & w1.doc_bool[i];
    }
    return temp;
}

Words Words::operator!()
{
    Words temp(this->num_file);
    for (int i = 0; i < this->num_file; i++)
    {
        temp.doc_bool[i] = ! (this->doc_bool[i]);
    }
    return temp;
}

Words Words::operator|(Words w1)
{
    Words temp(this->num_file);
    for (int i = 0; i < this->num_file; i++)
    {
        temp.doc_bool[i] = this->doc_bool[i] | w1.doc_bool[i];
    }
    return temp;
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

void Insert_Hash(std::vector<Files>& all_files, std::vector<Words> hash[], int size_hash)
{
    for (int i = 0; i < all_files.size() ; i++)
    {
        Files temp = all_files[i];
        int j = 0;
        while (j < temp.stmstr.size())
        {
            std::string word;
            int key = 0;
            while (temp.stmstr[j] != ' ')
            {
                word += temp.stmstr[j];
                key += temp.stmstr[j];
                j++;
            }
            key %= size_hash;
            //checks if the word exists in vector number [key]
            bool exist = 0;
            for (int p = 0; p < hash[key].size(); p++)
            {
                if (hash[key][p].name == word)
                {
                    exist = 1;
                    if (hash[key][p].doc_name[ hash[key][p].doc_name.size()-1 ] != temp.name)
                    {
                        hash[key][p].doc_frq ++;
                        hash[key][p].doc_name.push_back(temp.name);
                        hash[key][p].doc_bool[i] = 1;
                    }
                }
            }
            if (exist == 0)
            {
                Words a(all_files.size());
                a.name = word;
                a.doc_frq = 1;
                a.doc_name.push_back(temp.name);
                a.doc_bool[i] = 1;
                hash[key].push_back(a);
            }
            j++;
        }
    }
}

void Search_Hash(std::string target, std::vector<Words> hash[], int size_hash)
{
    int key = 0;
    std::string stmTrgt;
    stemfile(target, stmTrgt);
    stmTrgt.erase(stmTrgt.begin());
    stmTrgt.erase(stmTrgt.end() - 1);
    for (int i = 0; i < stmTrgt.length(); i++)
    {
        key += stmTrgt[i];
    }
    key %= size_hash;

    for (int i = 0; i < hash[key].size(); i++)
    {
        
        if (stmTrgt == hash[key][i].name)
        {
            std::cout << "\"" << target << "\"" << " exists in file(s) : \n";
            for(int j = 0; j < hash[key][i].doc_name.size(); j++)
            {
                std::cout << "\t\t" << hash[key][i].doc_name[j] << std::endl;
            }
            return;
        }
    }
    std::cout << "No such word! (or directory :P)\n";
}

void Rpl_Bool(std::string& input, std::string target, std::string alter)
{
    size_t pos = input.find(target);
    
    while (pos != std::string::npos)
    {
        if ((pos == 0) || (!isalpha(input[pos - 1]) && !isalpha(input[pos + target.length()])))
        {
            input.replace(pos, target.length(), alter);
        }
        pos = input.find(target, pos + 1);
    }
}

void Del_Spaces(std::string& input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ') {
            input.erase(input.begin() + i);
        }
    }
}

void Boolean_Search(std::string& Sinput, int hash_size, std::vector<Words> hash[], size_t num_file, std::vector<Files>& all_files)
{
    std::vector<Words> Vinput;
    for (int i = 0; i < Sinput.length(); )
    {
        while (!isalpha(Sinput[i]) && i < Sinput.length()) //"&& i < Sinput.length()" was added to prevent any loops
        {
            Words a(Sinput[i]);
            Vinput.push_back(a);
            i++;
        }
        
        if (i < Sinput.length()) // to prevent Bad Access
        {
            std::string wrd, stmWrd;
            int key = 0;
            while (isalpha(Sinput[i]))
            {
                wrd += Sinput[i];
                i++;
            }
            stemfile(wrd, stmWrd);
            stmWrd.erase(stmWrd.begin());
            stmWrd.erase(stmWrd.end() - 1);
            for (int j = 0; j < stmWrd.length(); j++)
            {
                key += stmWrd[j];
            }
            key %= hash_size;
        
            bool flag = 0; //if the word doesn't exist in the Hash Data Structure
            for (int p = 0; p < hash[key].size(); p++)
            {
                if (stmWrd == hash[key][p].name)
                {
                    Vinput.push_back(hash[key][p]);
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                Words a(num_file);
                a.name = stmWrd;
                Vinput.push_back(a);
            }
        }
    }
    
    Rec_Prnth2(Vinput);
    std::cout << "The Result is:\n";
    bool flag = 0; // to check if there is going to be any results
    for (int i = 1; i < all_files.size(); i++) // i should start from 1 because first file is hidden
    {
        if (Vinput[0].doc_bool[i] == 1)
        {
            flag = 1;
            std::cout << "\t\t" << all_files[i].name << "\n";
        }
    }
    if (!flag) {
        std::cout << "Unfortunately, the result is not in any of the files.\n";
    }
}

void Boolean_oprt(std::vector<Words>& Vinput, size_t from, size_t end)
{
    if (Vinput[from].type == Words::prnth)
    {
        Vinput.erase(Vinput.begin()+end);
        Vinput.erase(Vinput.begin()+from);
        end -= 2;
    }
    
    for (int pri = 0; pri < 3; pri++) //priority of the operations: NOT, AND, OR
    {
        for (size_t j = from; j <= end; j++)
        {
            if (Vinput[j].type == pri + Words::NOT)
            {
                switch (pri) // To find out which operation must be done
                {
                    case 0:
                    {
                        Vinput[j] = !Vinput[j+1];
                        Vinput.erase(Vinput.begin() + j + 1);
                        end--;
                        break;
                    }
                    case 1:
                    {
                        Vinput[j-1] = Vinput[j-1] & Vinput[j+1];
                        Vinput.erase(Vinput.begin() + j, Vinput.begin() + j + 2);
                        end -= 2;
                        break;
                    }
                    case 2:
                    {
                        Vinput[j-1] = Vinput[j-1] | Vinput[j+1];
                        Vinput.erase(Vinput.begin() + j, Vinput.begin() + j + 2);
                        end -= 2;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}

void Rec_Prnth2(std::vector<Words>& Vinput) 
{
    size_t i = 0;
    size_t lastP = 0; // lastP is the position of the last open paranthesis
    bool flag = 0; // to see if input contains any paranthesis
    while (i < Vinput.size())
    {
        if (Vinput[i].name == "(")
        {
            flag = 1;
            lastP = i;
        }
        if (Vinput[i].name == ")")
        {
            Boolean_oprt(Vinput, lastP, i);
            break;
        }
        i++;
    }

    if (!flag) //there are no paranthesis
    {
        Boolean_oprt(Vinput, 0, Vinput.size() - 1);
    }
    else //Call itself again
        Rec_Prnth2(Vinput);
    return;
}

void Insert_Hash_Dict(std::vector<std::string> hash_dict[], int size_hash)
{
    std::string dictionary;
    fin.open("/Users/codeWorm/Documents/education/Sharif University /CSE/Fundemental of programming/project_codes/Project_phase4/Project_4/end_com");
    std:: stringstream buffer;
    buffer << fin.rdbuf();
    dictionary = buffer.str();
    fin.close();
    for(size_t i = 0; i < dictionary.length(); i++)
    {
        std::string word;
        int key = 0;
        while (dictionary[i] != '\n' && i < dictionary.length())
        {
            word += dictionary[i];
            key += dictionary[i];
            i++;
        }
        key %= size_hash;
        hash_dict[key].push_back(word);
    }
}

bool Search_Hash_Dict(std::string target, std::vector<std::string> hash_dict[], int size_hash)
{
    int key = 0;
    for (int i = 0; i < target.length(); i++)
    {
        key += target[i];
    }
    key %= size_hash;
    for (int i = 0; i < hash_dict[key].size(); i++)
    {
        if (hash_dict[key][i] == target)
        {
            return 1;
        }
    }
    return 0;
}

void Insert_keyboard (std::vector<char> keyboard[26])
{
    char a[4] = {'q', 'w', 's', 'z'}; keyboard[0].insert(keyboard[0].begin(), a, a + 4);
    char b[4] = {'v', 'g', 'h', 'n'}; keyboard[1].insert(keyboard[1].begin(), b, b + 4);
    char c[4] = {'x', 'd', 'f', 'v'}; keyboard[2].insert(keyboard[2].begin(), c, c + 4);
    char d[6] = {'s', 'e', 'r', 'f', 'c', 'x'}; keyboard[3].insert(keyboard[3].begin(), d, d + 6);
    char e[4] = {'w', 's', 'd', 'r'}; keyboard[4].insert(keyboard[4].begin(), e, e + 4);
    char f[6] = {'d', 'r', 't', 'g', 'v', 'c'}; keyboard[5].insert(keyboard[5].begin(), f, f + 6);
    char g[6] = {'f', 't', 'y', 'h', 'b', 'v'}; keyboard[6].insert(keyboard[6].begin(), g, g + 6);
    char h[6] = {'g', 'y', 'u', 'j', 'n', 'b'}; keyboard[7].insert(keyboard[7].begin(), h, h + 6);
    char i[4] = {'u', 'j', 'k', 'o'}; keyboard[8].insert(keyboard[8].begin(), i, i + 4);
    char j[6] = {'h', 'u', 'i', 'k', 'm', 'n'}; keyboard[9].insert(keyboard[9].begin(), j, j + 6);
    char k[5] = {'j', 'i', 'o', 'l', 'm'}; keyboard[10].insert(keyboard[10].begin(), k, k + 5);
    char l[3] = {'o', 'k', 'p'}; keyboard[11].insert(keyboard[11].begin(), l, l + 3);
    char m[3] = {'n', 'j', 'k'}; keyboard[12].insert(keyboard[12].begin(), m, m + 3);
    char n[4] = {'b', 'h', 'j', 'm'}; keyboard[13].insert(keyboard[13].begin(), n, n + 4);
    char o[4] = {'i', 'k', 'l', 'p'}; keyboard[14].insert(keyboard[14].begin(), o, o + 4);
    char p[2] = {'o', 'l'}; keyboard[15].insert(keyboard[15].begin(), p, p + 2);
    char q[2] = {'a', 'w'}; keyboard[16].insert(keyboard[16].begin(), q, q + 2);
    char r[4] = {'e', 'd', 'f', 't'}; keyboard[17].insert(keyboard[17].begin(), r, r + 4);
    char s[6] = {'a', 'w', 'e', 'd', 'x', 'z'}; keyboard[18].insert(keyboard[18].begin(), s, s + 6);
    char t[4] = {'r', 'f', 'g', 'y'}; keyboard[19].insert(keyboard[19].begin(), t, t + 4);
    char u[4] = {'y', 'h', 'j', 'i'}; keyboard[20].insert(keyboard[20].begin(), u, u + 4);
    char v[4] = {'c', 'f', 'g', 'b'}; keyboard[21].insert(keyboard[21].begin(), v, v + 4);
    char w[4] = {'q', 'a', 's', 'e'}; keyboard[22].insert(keyboard[22].begin(), w, w + 4);
    char x[4] = {'z', 's', 'd', 'c'}; keyboard[23].insert(keyboard[23].begin(), x, x + 4);
    char y[4] = {'t', 'g', 'h', 'u'}; keyboard[24].insert(keyboard[24].begin(), y, y + 4);
    char z[3] = {'a', 's', 'x'}; keyboard[25].insert(keyboard[25].begin(), z, z + 3);
}

void Smart_Search(std::string& word, std::vector<std::string> hash_dict[], std::vector<std::pair<std::string, std::string> >& mistakes, int size_hash , std::vector<char> keyboard[26])
{
    for (int i = 0; i < word.length(); i++)
        word[i] = tolower(word[i]);
    
    if (Search_Hash_Dict(word, hash_dict, size_hash))
    {
        return;
    }
    
    for (int i = 0; i < mistakes.size(); i++)
    {
                    std::cout <<mistakes[i].first<<"\t"<<mistakes[i].second<<"\n";
        
        if (word == mistakes[i].first)
        {
            std::cout<<"\t\t\t\t I KNOW YOU'RE STUPID\n";
            Print_Output_Choices(word, hash_dict, mistakes[i].second, size_hash, mistakes, keyboard);
            return;
        }
    }
    Make_Sugg(word, hash_dict, keyboard, size_hash, mistakes);
    return;
}

void Make_Sugg (std::string& word, std::vector<std::string> hash_dict[], std::vector<char> keyboard[26], int size_hash, std::vector<std::pair<std::string, std::string> >& mistakes)
{
    std::vector<std::string> suggestions;
    
    std::string temp = word;
    
    for(int i = 0; i < word.length(); i++) // Deletion of each letter
    {
        temp.erase(temp.begin() + i);
        if (Search_Hash_Dict(temp, hash_dict, size_hash))
        {
            suggestions.push_back(temp);
        }
        temp = word;
    }
    for(int i = 0; i < word.length(); i++) // Insertion of Alphabet
    {
        for (int j = 0; j < 26; j++)
        {
            temp.insert(i, 1, j+'a');
            if (Search_Hash_Dict(temp, hash_dict, size_hash))
            {
                suggestions.push_back(temp);
            }
            temp = word;
        }
    }
    for(int i = 0; i < word.length(); i++) // Replacement of Keyboard Mistakes
    {
        for (int j = 0; j < keyboard[word[i] - 'a'].size(); j++)
        {
            temp.replace(i, 1, 1, keyboard[word[i] - 'a'][j]);
            if (Search_Hash_Dict(temp, hash_dict, size_hash))
            {
                suggestions.push_back(temp);
            }
            temp = word;
        }
    }
    Print_Wrd_Sugg(word, hash_dict, suggestions, mistakes, size_hash);
}

void Print_Output_Choices (std::string& word, std::vector<std::string> hash_dict[],std::string strSugg, int size_hash, std::vector<std::pair<std::string, std::string> >& mistakes, std::vector<char> keyboard[26])
{
    std::cout << "Did you mean: " << strSugg <<"?\n";
    std::cout << "1) Yes.\n";
    std::cout << "2) No, suggest something else.\n";
    std::cout << "3) No, I meant what I said.\n";
    int stage;
    std::cin >> stage;
    
    switch (stage)
    {
        case 1:
        {
            for (int i = 0; i < mistakes.size(); i++)
            {
                if (mistakes[i].first == word)
                {
                    mistakes[i].second = strSugg;
                    return;
                }
            }
            std::pair<std::string, std::string> a;
            a.first = word;
            a.second = strSugg;
            mistakes.push_back(a);
            word = strSugg;
            return;
        }
        case 2:
        {
            Make_Sugg(word, hash_dict, keyboard, size_hash, mistakes);
            return;
        }
        case 3:
        {
            int key = 0;
            for (int i = 0; i < word.length(); i++)
            {
                key += word[i];
            }
            key %= size_hash;
            hash_dict[key].push_back(word);
            return;
        }
            
        default:
            return;
    }
}

void Print_Wrd_Sugg (std::string& word, std::vector<std::string> hash_dict[], std::vector<std::string> suggestions, std::vector<std::pair<std::string, std::string> >& mistakes , int size_hash)
{
    std::cout << "Did you mean any of these words?\n";
    for (int i = 0; i < suggestions.size(); i++)
    {
        std::cout << i+1 << ") " << suggestions[i] << std::endl;
    }
    std::cout << suggestions.size() + 1 << ") No, I meant what I said. \n";
    int stage;
    std::cin >> stage;
    if (stage == suggestions.size() + 1)
    {
        int key = 0;
        for (int i = 0; i < word.length(); i++)
        {
            key += word[i];
        }
        key %= size_hash;
        hash_dict[key].push_back(word);
        return;
    }
    else
    {
        for (int i = 0; i < mistakes.size(); i++)
        {
            if (mistakes[i].first == word)
            {
                mistakes[i].second = suggestions[stage - 1];
                return;
            }
        }
        std::pair<std::string, std::string> a;
        a.first = word;
        a.second = suggestions[stage - 1];
        mistakes.push_back(a);
        std::cout << mistakes[0].first << "\t\t" << mistakes[0].second << "\n";
        std::cout<<"\t\t\t\tMISTAKE SIZE = "<<mistakes.size()<<"\n";
        word = suggestions[stage - 1];
    }
}