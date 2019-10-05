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

    DSVector<DSString> rowNumbersTrain;
    DSVector<DSString> IDTrain;
    DSVector<DSString> userNameTrain;
    DSVector<DSString> tweetTrain;

    DSVector<DSString> rowNumbersTest;
    DSVector<DSString> IDTest;
    DSVector<DSString> userNameTest;
    DSVector<DSString> tweetTest;

    char buffer[1000];

    sentimentMain();
    ~sentimentMain();

    void readTrainFile(DSString train);
    void readTrainTargetFile(DSString target);
    void readTestFile(DSString test);
    void readTestTargetFile(DSString target);

    void storeWords();

    /*int *tweetIDTrain;
    int *tweetIDTarget*/;
};

#endif // SENTIMENTMAIN_H
