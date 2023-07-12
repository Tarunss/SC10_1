//-----------------------------------------------------------------------------
// Arithmetic.cpp
// Tarun Sohal, CruzID: tsohal
// Client program for BigInteger.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include<fstream>
using namespace std;

int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;
    size_t begin, end, line_length;
    string line;
    string token;
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
    //read the first line
    string firstLine = "";
    getline(in,firstLine);
    line_length = firstLine.length();
    //parse the first line of whitespace
    begin = min(firstLine.find_first_not_of(" ", 0), line_length);
    end = min(firstLine.find_first_of(" ", begin), line_length);
    token = firstLine.substr(begin, end-begin);
    //turn the first line into a bigInt
    // out<<token<<endl;
    // out<<endl;
    BigInteger A = BigInteger(token);
    //throw out the second line
    getline(in,firstLine);
    //get the last line
    getline(in,firstLine);
    line_length = firstLine.length();
    //parse the first line of whitespace
    begin = min(firstLine.find_first_not_of(" ", 0), line_length);
    end = min(firstLine.find_first_of(" ", begin), line_length);
    token = firstLine.substr(begin, end-begin);
    //out<<token<<endl;
    //turn it into a big integer
    BigInteger B = BigInteger(token);
    //at this point, do operations and print them to out
    //out << A and B
    out<<A<<endl;
    out<<endl;
    out<<B<<endl;
    out<<endl;
    //out A+B
    out<<A+B<<endl;
    out<<endl;
    //out A-B
    out<<A-B<<endl;
    out<<endl;
    //out A-A
    out<<A-A<<endl;
    out<<endl;
    //out 3A - 2B
    BigInteger mult1 = BigInteger("3");
    BigInteger mult2 = BigInteger("2");
    out<<(mult1*A) - (mult2*B)<<endl;
    out<<endl;
    //out A*B
    out<<A*B<<endl;
    out<<endl;
    //out A*A
    out<<A*A<<endl;
    out<<endl;
    //out B*B
    out<<B*B<<endl;
    out<<endl;
    //out 9A^4 + 16B^5
    mult1 = BigInteger("9");
    mult2 = BigInteger("16");
    BigInteger P = A*A*A*A;
    BigInteger K = B*B*B*B*B;
    out<<(mult1*P) + (mult2 * K)<<endl;

    //close files
    out.close();
    in.close();
}