//-----------------------------------------------------------------------------
// Order.cpp
// Client file for Dictionary.cpp
// cruzID: tsohal
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
   size_t begin, end, line_length;
   ifstream in;
   ofstream out;
   string line;
   string token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   // create a new dictionary
   Dictionary D;
   int counter = 1;
   // read each line of input file, then count and print tokens 
   while( getline(in, line) )  {
      line_length = line.length();
      // get first token
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      D.setValue(token,counter);
      
      counter++;
   }
   //first print out key and value pairs
   out<<D<<endl;
   //now print out the inorder stuff
   string s = D.pre_string();
   //out<<"\n";
   out<<s<<endl;
   //D.clear();
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}