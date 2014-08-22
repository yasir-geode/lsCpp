/************************************************************************************

   FileName:   gkumar_quiz.cpp
   Executable: gkumar_quix.exe
   Date:       08-21-2014

   A program to list all the subdirectories and files recursively under a given
   directory

   
   Instruction:
               Compile: g++ gkumar_quiz.cpp -o gkumar_quiz.exe
               Run:     ./gkumar_quiz.exe <pathName> <o for normal output 
                         and 1 for sorted output>

************************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

/************************************************************************************ 

   Name:        node
   Type:        Structure
   Description: A structure to store files or directory information
   Fields:      name: name of the file or directory
                type: "F" for file and "D" for directory
                size: size of the file, 0 for directory
                time: last modified time in unix format               
************************************************************************************/
struct node
{
  string name;   
  string type; 
  unsigned long long size;
  unsigned long long time;
};

/************************************************************************************

   Name:        compareNode
   Type:        Method
   Description: A method to compare two node objects based on their name
   Return Type: Bool
   Argument:    a: Reference to constant objects of node type
                b: Reference to constant objects of node type
************************************************************************************/
bool compareNode(const node &a, const node &b)
{
   int res = a.name.compare(b.name);
   if(res < 0)
     return true;
   else
     return false;
}

/************************************************************************************

  Name:        listDir
  Type:        Method
  Description: A method to list all the subdirectories and files under a 
               given directory 
  Return Type: void
  Argument:    name:      Path to the directory 
               ans:       vector of node objects to store details of files or dir. 
               lastSlash: To avoid redundant '/' in path

************************************************************************************/
void listdir(const char *name, vector<node> &ans, bool lastSlash)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    struct tm      *tm;
    time_t rawtime;
 
    if (!(dir = opendir(name))) 
    {   
        cout<<"Couldn't open the file or dir"<<name<<"\n";
        return;
    }
    if (!(entry = readdir(dir)))
    {
        cout<<"Couldn't read the file or dir"<<name<<"\n";
        return;
    }

    do 
    {
        string slash="";
        if(!lastSlash)
          slash = "/";
      
        string parent(name);
        string file(entry->d_name);
        string final = parent + slash + file;
        if(stat(final.c_str(), &statbuf)==-1)
        {
            cout<<"Couldn't get the stat info of file or dir: "<<final<<"\n";
            return;
        }
        tm = localtime(&statbuf.st_mtime);
        unsigned long long time = mktime(tm);

        if (entry->d_type == DT_DIR) //its a directoru
        {
            //skip the . and .. directory
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            struct node tmp;
            tmp.name = final;
            tmp.type = "D";
            tmp.size = 0;
            tmp.time = time;
            ans.push_back(tmp);
            listdir(final.c_str(), ans, false);
        } 
        else //its a file  
        {
            struct node tmp;
            tmp.name = final;
            tmp.type = "F";
            tmp.size = statbuf.st_size;
            tmp.time = time;
            ans.push_back(tmp);
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

/************************************************************************************

   Name:        main
   Type:        Method
   Description: Starting point of program
   Return Type: int
   Argument:    argc: stores number of argument passed in command line
                argv: list of all argument passed in command line 

************************************************************************************/
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
      cout<<"Usage: \n";
      cout<<"./gkumar_quiz.exe <inputDirectory> <isSorted>\n";
      cout<<"inputDirectory: Path to any dir or file\n";
      cout<<"isSorted: 0 for normal output and 1 for sorted output\n";
      return 0;
    }
    vector<node> ans;
    bool lastSlash = false;

    //check the last slash if any to avoid redundant / 
    if(argv[1][strlen(argv[1])-1]=='/')
      lastSlash = true;

    //store all the subdirectories in vector
    listdir(argv[1], ans, lastSlash);

    //sort when user wants 
    if(string(argv[2]).compare(string("1"))==0)
      sort(ans.begin(), ans.end(), compareNode);

    //output the result to standard output
    for(int i=0; i<ans.size(); i++)
    {
      cout<<ans[i].name<<","<<ans[i].type<<","<<ans[i].size<<","<<ans[i].time<<"\n";
    }
    return 0;
}
