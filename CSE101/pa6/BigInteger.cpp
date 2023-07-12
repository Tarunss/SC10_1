//-----------------------------------------------------------------------------
// BigInteger.cpp
// Tarun Sohal, CruzID: tsohal
// Implementation file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"
#include"BigInteger.h"
#define base (long)1000000000
#define power (int)9
// Class Constructors & Destructors ----------------------------------------

// removeZeros()
// helper function to remove zeros from front of lists
   void removeZeros(List&L) {
       L.moveFront();
       if(L.length() > 0) {
           while(L.front() == 0) {
               L.eraseAfter();
           }
       }
   }
// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    //digits = new List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    //check to see if string matches specifications
    if(s.empty()) {
        throw std::invalid_argument("BigInteger(): error: string passed is empty\n");
    }
    
    //now, we need to see if there is a sign on the front of string s
    if(s.front() == '+') {
        signum = 1;
        s.erase(0,1);
    }
    else if (s.front() == '-') {
        signum = -1;
        s.erase(0,1);
    }
    else {
        signum = 1;
    }
    //another check since it could be empty now
    if(s.empty()) {
        throw std::invalid_argument("BigInteger(): error: string passed is empty\n");
    }
    //signum is already set to 0 anyways

    //create the big integer list
    //first we loop through entire list
    std::string sub = "";
    int tracker = 0;
    digits.moveFront();
    //use an iterator object to iterate backwards
    for(auto it = s.crbegin(); it != s.crend(); ++it) {
        //prepend longs found to a new string 
        //check to see if (*it) is valid
        std::string s = "";
        s = (*it);
        char d = s[0];
        if(!std::isdigit(d)) {
            throw std::invalid_argument("error: string contains non-numbers\n");
            exit(EXIT_FAILURE);
        }
        sub =(*it)+sub;
        tracker++;
        if(tracker == power) {
            //if tracker is at power 2, turn sub into long, and push back to list
            long item = stol(sub);
            digits.insertAfter(item);
            //reset sub and tracker
            tracker = 0;
            sub = "";
        }
    }
    //now that we are at the front of string, check to see if sub is empty
        if(sub.length() != 0) {
            long item = stol(sub);
            digits.insertAfter(item);
        }
    //at this point, digits and signum should both be initialized and ready.
    //remove any front zero entries from the string
    removeZeros(digits);
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    //we need to copy signum and digits
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
} 

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    //first we should compare to see what signs N and this have
    //case where they have same sign 
    if(this->signum == N.signum) {
        //compare length of each digits() list
        if(this->digits.length() < N.digits.length()) {
            //if both lists are neg
           if(this->signum == -1) {
               return 1;
           }
            //else the lists are positive, so this is less
           else {
               return -1;
           }
        }
        //case where this->digits.length is greater than N.digits.length
        else if(this->digits.length() > N.digits.length()) {
            //if both lists are neg
            if(this->signum == -1) {
               return -1;
           }
            //else the lists are positive, so this is greater
           else {
               return 1;
           }
        }
        //case where lists are even in length
        else {
            //first check to see if lists are equal
            if(this->digits == N.digits) {
                return 0;
            }
            //iterate down from front of each list, if this <,> to N, return -1,1 respectivley
            List newN = List(N.digits);
            List newThis = List(this->digits);
            newN.moveFront();
            newThis.moveFront();
            for(int i = 0; i < newThis.length(); i++) {
                long thisEle = newThis.peekNext();
                long NEle = newN.peekNext();
                if(thisEle < NEle) {
                    return -1;
                }
                else if(thisEle > NEle) {
                    return 1;
                }
                //incrememnt the list
                newN.moveNext();
                newThis.moveNext();
            }
            // delete newN;
            // delete newThis;
        }
        //de allocate lists
    }
    //case where each bigint has different sign
    //just compare each signs
    else {
        if(this->signum == 1 && N.signum != 1) {
            return 1;
        }
        else if(this->signum == -1 && N.signum != -1) {
            return -1;
        }
    }
    return 0; //since we've iterated through the entire list and they've been the same, return 0
}

// Helper procedures -------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    //iterate through entire list, make each long negative
    L.moveFront();
    for(int i = 0; i < L.length(); i++) {
        long item  = L.peekNext();
        //negate item
        item = -item;
        L.setAfter(item);
        L.moveNext();
    }
}
// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    //add up all the elements of A and B into S
    //iterate through A and B, add elements to i'th area in S
    A.moveBack();
    B.moveBack();
    //find out which list is shorter
    int lengthShort;
    int lengthLong;
    //need a reference to the longer of the lists
    List* longList;
    if(A.length() > B.length()) {
        lengthShort = B.length();
        longList = &A;
        lengthLong = A.length();
    }
    else {
        lengthShort = A.length();
        lengthLong = B.length();
        longList = &B;
    }
    //check to see what the sign passed was.
    //if sign of list is negative
    if(sgn == -1) {
        //turn every number into negative
        negateList(B);
    }
    //else, assume sign is positive
    S.moveBack();
    int Slength = S.length();
    //iterate through shorter list, add elements together
    for(int lengthShort2 = lengthShort; lengthShort2 > 0; lengthShort2--) {
        //use peekPrev to get elements
        long a = A.peekPrev();
        long b = B.peekPrev();
        //add the elements together
        long c = a+b;
        if(Slength > 0) {
            //set before cursor to new element
            S.setBefore(c);
            S.movePrev();
            A.movePrev();
            B.movePrev();
            Slength--;
        } 
        //else, we are at front of list, we insert new elements
        else {
            S.insertAfter(c);
            A.movePrev();
            B.movePrev();
        }
    }
    //now that we have iterated through short list, just iterate throught the rest of longList
    //and add the variables of longList to S
    int length = lengthLong - lengthShort;
    S.moveFront();
    for(length; length > 0; length--) {
        long a = longList->peekPrev();
        S.insertAfter(a);
        longList->movePrev();
    }
    //now we check to see if there are any zeros at the end: if so, we can pop them right now
    S.moveFront();
    if(S.length() > 0) {
        while(S.front() == 0) {
            //remove 0s from front of list
            S.eraseAfter();
            if(S.length() <= 0) {
                break;
            }
        }
    }
    // at this point, list should be fully copied
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
    //we know that if the leftmost number is negative, the list is negative as well
    //if L is empty, return 0
    if(L.length() == 0) {
        return 0;
    }
    long carry = 0;
    L.moveBack();
    //iterate through entire list
    for(int i = L.length(); i > 0; i--) {
        //if carry variable is set
        long x = L.peekPrev();
        if(carry != 0) {
            //add carry to i'th element
            x = x+carry;
            L.setBefore(x);
            //unset carry
            carry = 0;
        }
        //check to see if carry is needed(ADD)
        //ADD CASE (x is greater than base)
        if(x >= base) {
            //find out how large carry is
            long j = x/base;
            //subtract base from x
            L.setBefore(x-(base * j));
            //set carry variable
            carry = j;
        }
        //(SUB CASE) (x is less than zero)
        else if(x < 0) {
            long j = x; //this will be a neg number
            //if x evenly divides into base, we only carry j-1 times
            if(x % base == 0) {
                j = j/base;
            }
            //else, we do j = j/base -1
            else {
                j = j/base -1;
            }
            L.setBefore(x + (base * (-j)));
            //set carry variable
            carry = j;
        }
        L.movePrev();
    }
    //out of normalize main loop. check to see if carry < or > than 0
    if(carry > 0) {
        //add carry to the front of the list
        L.moveFront();
        L.insertAfter(carry);
        //we return a 1 to signal that the list is positive
        return 1;
    }
    //if carry is negative, fucky wucky time
    if(carry < 0) {
        //need to subtract base * carry from front digit to get original
        L.moveFront();
        L.setAfter((L.front()) - (base * (-carry)));
        //negate list
        negateList(L);
        //normalize L again
        normalizeList(L);
        //at this point, we know L is negative, so we return a -1
        return -1;
    }
    return 1;
}
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    //go to back of list, insertAfter(0) p amount of times
    L.moveBack();
    for(int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    //iterate through entire list, multiply each element by m
    L.moveFront();
    for(int i = 0; i < L.length(); i++) {
        long item  = L.peekNext();
        //negate item
        item = item * m;
        L.setAfter(item);
        L.moveNext();
    }
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    //just clear the list and make signum = 0;
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if(signum != 0) {
        signum = -signum;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    //ADD cases
    //case where this is pos, N is neg
    BigInteger S = BigInteger();
    if(N.signum == -1 && this->signum != -1) {
        sumList(S.digits, this->digits, N.digits, -1);
        int z = normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = z;
    }
    //case where both are pos
    else if(N.signum != -1 && this->signum != -1) {
        sumList(S.digits,this->digits,N.digits,1);
        int z = normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = z;
    }
    //case where this is neg, N is pos (-A+B = B-A)
    else if(N.signum != -1 && this->signum == -1) {
        sumList(S.digits,N.digits,this->digits,-1);
        int z = normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = z;
    }
    //case where both lists are negative
    else if(N.signum == -1 && this->signum == -1){
        sumList(S.digits, N.digits,this->digits,1);
        normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = -1;
    }
    return S;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger S = BigInteger();
    //case where this is pos, N is neg (A - -B) == (A+B)
    if(N.signum == -1 && this->signum != -1) {
        sumList(S.digits, this->digits, N.digits, 1);
        normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = 1;
    }
    //case where both are pos (A-B)
    else if(N.signum != -1 && this->signum != -1) {
        sumList(S.digits,this->digits,N.digits,-1);
        int z = normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = z;
    }
    //case where this is neg, N is pos ((-A-B) = -(A+B))
    else if(N.signum != -1 && this->signum == -1) {
        sumList(S.digits,this->digits,N.digits,1);
        normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = -1;
    }
    //case where both lists are negative (-A--B) == (B-A)
    else if(N.signum == -1 && this->signum == -1){
        sumList(S.digits,N.digits,this->digits,-1);
        int z = normalizeList(S.digits);
        removeZeros(S.digits);
        S.signum = z;
    }
    return S;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
   //testing scalarMult and normalize
   BigInteger P = BigInteger();
   //copy the lists from N and this
   List A = this->digits;
   List B = N.digits;
   //if either of these lists are empty, just return empty list
   if(A.length() == 0 || B.length() == 0) {
       P.signum = 0;
       return P;
   }
   //we are multiplying this and N, then putting in the product 
   //iterate through the length of list B
   int shiftCount = 0;
   B.moveBack();
   for(int i = B.length(); i > 0; i--) {
       //iterate through entire list of A
       long elemB = B.peekPrev();
       //do the scalar mult
       A = this->digits;
       scalarMultList(A,elemB);
       //shift the list 
       shiftList(A,shiftCount);
       //sum A into P.digits
       sumList(P.digits,P.digits,A,1);
       //normalize the product
       normalizeList(P.digits);
       //increment counters
       shiftCount++;
       B.movePrev();
   }
   //set the sign of P
   //remove any extra zeros
   removeZeros(P.digits);
   if(this->signum == -1 && N.signum == -1) {
       P.signum = 1;
   }
   else if(this->signum == -1 || N.signum == -1) {
       P.signum = -1;
   }
   else if(P.digits.length() == 0) {
       P.signum = 0;
   }
   else {
       P.signum = 1;
   }
   return P;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    //basically, just go through and do the opposite of constructor
    std::string bigString = "";
    //go through and turn each number into a string
    this->digits.moveFront();
    for(int i = 0; i < this->digits.length(); i++) {
        //check to see if number of digits is less than power
        long digit = this->digits.peekNext();
        std::string d = std::to_string(digit);
        //while length of string is less than # of digits required
        while(d.length() < power) {
            //append zeros to front of d
            d = "0"+d;
        }
        //add that substring to front of bigString
        bigString+=d;
        this->digits.moveNext();
    }
    //pop unneccesary zeros from bigString
    while(bigString.front() == '0') {
        bigString.erase(0,1);
    }
    //add the sign
    if(this->signum == -1) {
        bigString = "-"+bigString;
    }
    if(bigString.length() == 0) {
        //if list is empty, just print a 0
        bigString+='0';
    }
    return bigString;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if(A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if(A.compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
if(A.compare(B) == 1) {
        return false;
    }
    return true;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
if(A.compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
if(A.compare(B) == -1) {
        return false;
    }
    return true;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}


// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    return A = A.add(B);
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    return A = A.sub(B);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    return A = A.mult(B);
}