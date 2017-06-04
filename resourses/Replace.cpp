#include<iostream>
#include<string>
using namespace std;

void File_replace(string& file_string, string& search, string& rep)
{
     size_t pos_search = file_string.find(search);
     while(pos_search != string::npos)
     {
          if ( (pos_search==0) || ( ( file_string[pos_search-1]<'A' || file_string[pos_search-1]>'Z' ) && (file_string[pos_search-1]<'a' || file_string[pos_search-1]>'z') ) )
          {
               if( ( file_string[pos_search+search.length()]<'A' || file_string[pos_search+search.length()]>'Z' ) && (file_string[pos_search+search.length()]<'a' || file_string[pos_search+search.length()]>'z') )
               {
                   file_string.replace(pos_search, search.length(), rep);
               }
               }
          pos_search = file_string.find(search, pos_search + 1);
     }
 }

int main(){
    string s = "Needle are only good for Needles";
    string str = "Needle";
    string rep = "Books";
    File_replace(s, str, rep);
    cout<<s<<endl;
    cin>>s;
    
}
