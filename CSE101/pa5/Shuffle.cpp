//-----------------------------------------------------------------------------
// tsohal
// Shuffle.cpp
// A client program for the List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"List.h"
#include<iomanip>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
using namespace std;

#define MAX_LEN 300
void shuffle(List& D) {
   //shuffle should split the deck into 2, and merge into new deck
   List* A = new List();
   //split list D into A (first half) and B(second half)
   if(D.length() != 0) {
      //check to see if deck is even or odd
      D.moveFront();
      int half = D.length()/2;
      for(int i = 0; i <half; i++) {
         int data = D.moveNext();
         A->insertBefore(data);
         //delete first half from D
         D.eraseBefore();
      }
      // cout<<"LISTS ARE" <<endl;
      // cout<<(*A)<<endl;
      // cout<<D<<endl;
      //List A is the left deck, list D is the right
      //now, merge together
      A->moveFront();
      D.moveFront();
      if(A->length() != 0) {
         for(int i = 0; i < A->length(); i++) {
            D.moveNext();
            int d = A->moveNext();
            D.insertBefore(d);
         }
         //cout<<A<<endl;
         //cout<<D<<endl;
      }
   }
   delete A;
}
int main(int argc, char * argv[]){
   //argv will have programname at 0, and if 1 is a >, it will take in another
   //file name that we will write to, called out
   ofstream out;
   string amountString = argv[1];
   int amount = std::stoi(amountString);
   if(argc == 2) {
      //code for shuffle (to stdout)
      cout<<"deck size"<<"       ";
      cout<<"shuffle count" <<endl;
      cout<<"------------------------------"<<endl;
      List* deck = new List();
      for(int i = 0; i < amount; i++) {
         //create deck
         deck->insertBefore(i);
         //create a copy of current deck (for comparisons)
         List* shuffleDeck = new List(*deck);
         shuffle(*shuffleDeck);
         int amountShuffle = 1;
         while(!((*shuffleDeck) == (*deck))) {
            shuffle(*shuffleDeck);
            amountShuffle++;
            // cout<<*shuffleDeck<<endl;
            // cout<<*deck<<endl;
         }
         if(i+1 < 10) {
            cout<<" "<<i+1<<"               "<<amountShuffle<<endl;
         }
         else if(i+1>= 100) {
            cout<<" "<<i+1<<"             "<<amountShuffle<<endl;
         }
         else {
            cout<<" "<<i+1<<"              "<<amountShuffle<<endl;
         }
         delete shuffleDeck;
      } 
      delete deck;
   }
   else if (argc == 4) {
      //same code, but to file
      out.open(argv[3]);
      //code for shuffle (to stdout)
      out<<"deck size"<<"       ";
      out<<"shuffle count" <<endl;
      out<<"------------------------------"<<endl;
      List* deck = new List();
      for(int i = 0; i < amount; i++) {
         //create deck
         deck->insertBefore(i);
         //create a copy of current deck (for comparisons)
         List* shuffleDeck = new List(*deck);
         shuffle(*shuffleDeck);
         int amountShuffle = 1;
         while(!((*shuffleDeck) == (*deck))) {
            shuffle(*shuffleDeck);
            amountShuffle++;
            // cout<<*shuffleDeck<<endl;
            // cout<<*deck<<endl;
         }
         if(i+1 < 10) {
            out<<" "<<i+1<<"               "<<amountShuffle<<endl;
         }
         else if(i+1>= 100) {
            out<<" "<<i+1<<"             "<<amountShuffle<<endl;
         }
         else {
            out<<" "<<i+1<<"              "<<amountShuffle<<endl;
         }
         delete shuffleDeck;
      } 
      delete deck;
      out.close();
   }
   else {
      cerr<<"correct usage: " << "shuffle" <<"<# (of shuffles) >" << "<outfile> OR"
      <<"shuffle <#>" <<endl;
      return (EXIT_FAILURE);
   } 
   
}
//shuffle function