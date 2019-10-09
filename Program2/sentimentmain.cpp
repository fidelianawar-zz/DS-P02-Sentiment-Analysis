#include "sentimentmain.h"
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>

using namespace std;

//main method to run program execution

sentimentMain::sentimentMain()
{
}

sentimentMain::~sentimentMain(){
    delete [] sentimentValue;
}

void sentimentMain::setSentiment(int _sentiment){
    sentiment = _sentiment;
}

int sentimentMain::getSentiment(){
    return sentiment;
}

void sentimentMain::readTrainFile(DSString trainFile){

    ifstream trainData(trainFile.c_str());
    if (!trainData.is_open()) {
        cerr << "Unable to open train file" << endl;
        exit(1);
    }

    trainData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 500000; i++){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                trainData.getline(buffer,500, ',');
                rowNumbersTrain.push_back(buffer);
            }
            else if(j == 1){
                trainData.getline(buffer,500, ',');
                IDTrain.push_back(buffer);

            }
            else if(j == 2){
                trainData.getline(buffer,500, ',');
                userNameTrain.push_back(buffer);
            }
            else if(j == 3){
                trainData.getline(buffer,500);
                tweetTrain.push_back(buffer);
            }
        }
    }
    classifyWords();
}

void sentimentMain::readTrainTargetFile(DSString target){

    ifstream targetData(target.c_str());
    if (!targetData.is_open()) {
        cerr << "Unable to open train target file" << endl;
        exit(1);
    }

    //ignoring first line of file
    targetData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 500000; i++){
        for(int j = 0; j < 3; j++){
            if(j == 0){
                targetData.getline(buffer,500, ',');
                rowNumbersTrainTarget.push_back(buffer);
            }
            else if(j == 1){
                targetData.getline(buffer,500, ',');
                sentimentTrainTarget.push_back(buffer);

            }
            else if(j == 2){
                targetData.getline(buffer,500);
                IDTrainTarget.push_back(buffer);
            }
        }
    }
}

void sentimentMain::classifyWords(){

    int letterCounter = 0;
    int startCounter = 0;

    for(int i = 0; i < rowNumbersTrain.getSize(); i++){
        if(rowNumbersTrain.at(i) == rowNumbersTrainTarget.at(i)){
            if(sentimentTrainTarget.at(i) == "0"){
                DSString tempTweet = tweetTrain.at(i);
                for(int j = 0; j < tempTweet.size(); j++){
                    DSString word;
                    if((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                        letterCounter++;
                    }
                    else if(!((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123))){
                        word = tempTweet.substring(startCounter, letterCounter);
                        word.toLowerCase(word);
                        letterCounter++;
                        startCounter = letterCounter;
                        positiveWords.push_back(word);
                    }
                }
                letterCounter = 0;
                startCounter = 0;
            }
            else if(sentimentTrainTarget.at(i) == "4"){
                DSString tempTweet = tweetTrain.at(i);

                for(int j = 0; j < tempTweet.size(); j++){
                    DSString word;
                    if((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                        letterCounter++;
                    }
                    else if(!((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123))){
                        word = tempTweet.substring(startCounter, letterCounter);
                        word.toLowerCase(word);
                        letterCounter++;
                        startCounter = letterCounter;
                        negativeWords.push_back(word);
                    }
                }
                letterCounter = 0;
                startCounter = 0;
            }
        }
    }

    positiveWords.quickSort(0,positiveWords.getSize()-1);
    positiveWords.deleteRepeated();

    negativeWords.quickSort(0,negativeWords.getSize()-1);
    negativeWords.deleteRepeated();
}

void sentimentMain::readTestFile(DSString test){
    ifstream targetData(test.c_str());

    if (!targetData.is_open()) {
        cerr << "Unable to open test file" << endl;
        exit(1);
    }

    bool running = true;

    targetData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; running; i++){
        if(!running){
            break;
        }
        for(int j = 0; j < 4; j++){
            if(j == 0){
                targetData.getline(buffer,500, ',');
                if(targetData.eof()){
                    running = false;
                    break;
                }
                rowNumbersTest.push_back(buffer);
            }
            else if(j == 1){
                targetData.getline(buffer,500, ',');
                IDTest.push_back(buffer);

            }
            else if(j == 2){
                targetData.getline(buffer,500, ',');
                userNameTest.push_back(buffer);
            }
            else if(j == 3){
                targetData.getline(buffer,500);
                tweetTest.push_back(buffer);
            }
        }
    }
    testAnalyzer();
}

void sentimentMain::readTestTargetFile(DSString target){
    ifstream testTarget(target.c_str());
    if (!testTarget.is_open()) {
        cerr << "Unable to open test target file" << endl;
        exit(1);   // call system to stop
    }
    bool running = true;
    testTarget.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; running; i++){
        if(!running){
            break;
        }
        for(int j = 0; j < 3; j++){
            if(j == 0){
                testTarget.getline(buffer,500, ',');
                if(testTarget.eof()){
                    running = false;
                    break;
                }
                rowNumbersTestTarget.push_back(buffer);
            }
            else if(j == 1){
                testTarget.getline(buffer,500, ',');
                sentimentTestTarget.push_back(buffer);

            }
            else if(j == 2){
                testTarget.getline(buffer,500);
                IDTestTarget.push_back(buffer);
            }
        }
    }
}

void sentimentMain::testAnalyzer(){

    int letterCounter = 0;
    int startCounter = 0;
    int positiveWordFrequency = 0;
    int negativeWordFrequency = 0;
    sentimentValue  = new DSString[rowNumbersTest.getSize()];

    for(int i = 0; i < rowNumbersTest.getSize(); i++){
        DSString tempTweet = tweetTest.at(i);
        for(int j = 0; j < tempTweet.size(); j++){
            DSString word;
            if((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                letterCounter++;
            }
            else if(!((tempTweet[startCounter] > 64 && tempTweet[startCounter] < 91) || (tempTweet[startCounter] > 96 && tempTweet[startCounter] < 123))){
                letterCounter++;
                startCounter++;
            }
            else if(!((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123))){
                word = tempTweet.substring(startCounter, letterCounter);
                word.toLowerCase(word);
                letterCounter++;
                startCounter = letterCounter;
                wordsVectorTest.push_back(word);
            }
        }

        wordsVectorTest.quickSort(0,(wordsVectorTest.getSize() - 1));
        wordsVectorTest.deleteRepeated();

        for(int k = 0; k < wordsVectorTest.getSize(); k++){
            if(positiveWords.binarySearch(wordsVectorTest.at(k)) == true){
                positiveWordFrequency++;
            }
        }
        for(int m = 0; m < wordsVectorTest.getSize(); m++){
            if(negativeWords.binarySearch(wordsVectorTest.at(m)) == true){
                negativeWordFrequency++;
            }
        }

        if(positiveWordFrequency >= negativeWordFrequency){
            positiveTweet.push_back(tweetTest.at(i));
            sentimentValue[i] = "4";
        }

        else if(negativeWordFrequency > positiveWordFrequency){
            negativeTweet.push_back(tweetTest.at(i));
            sentimentValue[i] = "0";
        }

        positiveWordFrequency = 0;
        negativeWordFrequency = 0;

        wordsVectorTest.deleteElements();

        letterCounter = 0;
        startCounter = 0;
    }
}

void sentimentMain::createAccuracyFile(char *input){

    ofstream outputFile;
    outputFile.open(input);

    float accuracyOutput = 0.0;
    float accuracyCounter = 0.0;

    DSVector<DSString> score;

    for(int i = 0; i < rowNumbersTestTarget.getSize(); i++){
        if(sentimentTestTarget.at(i) == sentimentValue[i]){
            accuracyCounter++;
            score.push_back("c");
        }
        else{
            score.push_back("i");
        }
    }
    accuracyOutput = (accuracyCounter/(float)rowNumbersTestTarget.getSize());
    outputFile << accuracyOutput << endl;

    for(int i = 0; i < rowNumbersTestTarget.getSize(); i++){
        outputFile << IDTestTarget.at(i) << "," << score.at(i) << endl;
    }
}
