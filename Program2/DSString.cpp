#ifndef DSSTRING
#define DSSTRING

#include <iostream>
#include <cstring>
#include <DSString.h>

using namespace std;

DSString::DSString(){
    data=nullptr;
    ssize=0;
}

DSString::DSString(const char* x){
    data = new char[strlen(x)+1];
    strcpy(data, x);
}

DSString::DSString(const DSString& r){
    if(this==&r)
        return;
    data = new char[strlen(r.data)+1];
    strcpy(data, r.data);
}

DSString::~DSString(){
    delete [] data;
}

// DSString& operator= (const char*);
DSString& DSString::operator=(const char* r){
    delete [] data;
    data = new char[strlen(r)+1];
    strcpy(data,r);
    return *this;
}

// DSString& operator= (const DSString&);
DSString& DSString::operator= (const DSString &q){
    data = new char[strlen(q.data)+1];
    strcpy(data,q.data);
    return *this;
}

//DSString operator+ (const DSString&);
DSString DSString::operator+(const DSString &q)
{
    DSString s;
    s.data = new char[strlen(data)+strlen(q.data)+1];
    strcpy(s.data,data);
    strcat(s.data,q.data);
    return s;
}

//DSString operator- (const DSString&);
DSString DSString::operator-(const DSString &q)
{
    DSString s;
    s.data = new char[strlen(data)-strlen(q.data)+1];
    strncpy(s.data,data, strlen(data)-strlen(q.data));
    return s;
}


//DSString& operator+= (const DSString&)
DSString& DSString::operator+= (const DSString& p){
    char* temp = this -> data;
    this->data = new char[strlen(temp) + strlen(p.data) + 1];
    strcpy(this->data, temp);
    strcat(this->data, p.data);
    delete[] temp;
    return *this;
}

//DSString& operator+= (const DSString&)
DSString& DSString::operator-= (const DSString& p){
    char* temp = this -> data;
    this->data = new char[strlen(data) - strlen(p.data) + 1];
    strncpy(this->data, temp, strlen(p.data));
    delete[] temp;
    return *this;
}

bool DSString::operator== (const char* s){
    if(strcmp(this->data, s) == 0){
        return true;
    }
}

bool DSString::operator== (const DSString &object) const{
    if(strlen(data) != strlen(object.data)){
        return false;
    }
    for(int i = 0; i < strlen(data); i++){
        if(data[i] != object.data[i]){
            return false;
        }
        return true;
    }
}

//bool operator< (const char*);
bool DSString::operator< (const char *p){
    if(data < p){
        return true;
    }
}
//bool operator< (const DSString&);
bool DSString::operator< (const DSString& r){
    int minLength;
    if(strlen(data) < strlen(r.data)){
        minLength = strlen(data);
    }
    else{
        minLength = strlen(r.data);
    }
    for(int i = 0; i < minLength; i++){
        if(data[i] < r.data[i]){
            return true;
        }
        else if(data[i] > r.data[i]){
            return false;
        }
    }
    if(strlen(data) < strlen(r.data)){
        return true;
    }
    else{
        return false;
    }
}

//bool operator< (const char*);
bool DSString::operator> (const char *p){
    if(data > p){
        return true;
    }
}
//bool operator< (const DSString&);
bool DSString::operator> (const DSString& r){
    if(data > r.data){
        return true;
    }
}

//char& operator[] (const int);
char& DSString::operator[] (const int j){
    return *(data+j);
}

//int size();
int DSString::size(){
    return ssize;
}


/* DSString substring(int a, int b)
 * parameter a: starting position
 * parameter b: num of char to copy into substring that is returned
 * b+ : count forward from a, b- : count backaward
 */
DSString DSString::substring(int beg, int end){
    if(beg >= 0 && end > beg){
        char* temp = new char[end-beg+1];
        int length = end - beg;
        strncpy(temp, data, length);
        DSString res(temp);

        delete [] temp;
        return res;
    }
}

//simply returns data
char* DSString::c_str(){
    return data;
}

std:: ostream& operator<< (std::ostream& OS, const DSString& s){
    OS << s.data;
    return OS;
}


#endif
