#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSString{
private:
    char* data;
    int ssize;

public:
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    DSString& operator= (const char*);
    DSString& operator= (const DSString&);
    DSString operator+ (const DSString&);
    DSString& operator+= (const DSString&);
    bool operator== (const char*);
    bool operator== (const DSString&);
    bool operator< (const char*);
    bool operator< (const DSString&);
    char& operator[] (const int);

    int size();

    DSString substring(int a, int b);

    char* c_str();

    friend std:: ostream& operator<< (std::ostream&, const DSString&);

};

#endif // DSSTRING_H
