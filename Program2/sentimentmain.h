#ifndef SENTIMENTMAIN_H
#define SENTIMENTMAIN_H
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "DSVector.h"


class sentimentMain
{
private:
public:

    DSVector<DSString> rowNumbers;
    DSVector<DSString> ID;
    DSVector<DSString> userName;
    DSVector<DSString> tweet;
    char buffer[1000];

    sentimentMain();
    ~sentimentMain();

    void readTrainFile(DSString train);
    void readTrainTargetFile(DSString target);
    void readTestFile(DSString test);
    void readTestTargetFile(DSString target);

    void storeWords(DSVector<DSString> tweet);

    /*int *tweetIDTrain;
    int *tweetIDTarget*/;
};

#endif // SENTIMENTMAIN_H
