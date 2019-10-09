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
    ssize = strlen(x)+1;

}

DSString::DSString(const DSString& r){
    data = new char[strlen(r.data)+1];
    strcpy(data, r.data);
    ssize = r.ssize;
}

//destructor
DSString::~DSString(){
   delete [] data;
}

// DSString& operator= (const char*);
DSString& DSString::operator=(const char* r){
    delete [] data;
    data = new char[strlen(r)+1];
    strcpy(data,r);
    ssize = strlen(r)+1;
    return *this;
}

// DSString& operator= (const DSString&);
DSString& DSString::operator= (const DSString &q){
    delete [] data;
    data = new char[(strlen(q.data))+1];
    strcpy(data,q.data);
    ssize = q.ssize;
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

//DSString operator== (const char*)
bool DSString::operator== (const char* s){
    if(strcmp(this->data, s) == 0){
        return true;
    }
    else{
        return false;
    }
}

//bool operator== (const DSString&)
bool DSString::operator== (const DSString &object) const{
    if (strcmp(data, object.data) == 0){
        return true;
    }
    else{
        return false;
    }
}


//bool operator< (const char*);
bool DSString::operator< (const char *p){
    int n;
    n = strcmp(data,p);
    if(n < 0){
        return true;
    }
    else{
        return false;
    }

}

//bool operator< (const DSString&);
bool DSString::operator< (const DSString& r){
    int n;
    n = strcmp(data,r.data);
    if(n < 0){
        return true;
    }
    else{
        return false;
    }
}

//bool operator< (const char*);
bool DSString::operator> (const char *p){
    int n;
    n = strcmp(data,p);
    if(n > 0){
        return true;
    }
    else{
        return false;
    }

}

//bool operator< (const DSString&);
bool DSString::operator> (const DSString& r){
    int n;
    n = strcmp(data,r.data);
    if(n > 0){
        return true;
    }
    else{
        return false;
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

//DSString substring(int, int);
DSString DSString::substring(int beg, int end){
    const int length = end-beg+1;
    char* string1 = new char[length];
    if(end >= 0){
        for(int i = 0; i < (length-1); i++){
            string1[i] = data[beg+i];
        }
    }
    string1[length-1] = '\0';
    DSString sub = DSString(string1);
    delete [] string1;

    return sub;
}

//simply returns data
char* DSString::c_str(){
    return data;
}

std:: ostream& operator<< (std::ostream& OS, const DSString& s){
    OS << s.data;
    return OS;
}

//makes all letters lowercase
void DSString::toLowerCase(DSString capitals){
    for(int i = 0; i < capitals.size(); i++){
        if(capitals[i] > 64 && capitals[i] < 91){
            capitals[i] = capitals[i] + 32;
        }
    }
}

#endif
