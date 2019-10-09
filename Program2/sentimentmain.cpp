#include "sentimentmain.h"
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>

using namespace std;

sentimentMain::sentimentMain()
{
}

sentimentMain::~sentimentMain(){
    delete [] sentimentValue;
}

//reading in train data, parsing 4 elements into respective vectors
void sentimentMain::readTrainFile(DSString trainFile){

    ifstream trainData(trainFile.c_str());
    if (!trainData.is_open()) {
        cerr << "Unable to open train file" << endl;
        exit(1);
    }

    trainData.ignore(256, '\n');

    //reading in 700000 lines of train data
    for(int i = 0; i < 700000; i++){
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

//reading in train target data to later use to match sentiment score with
void sentimentMain::readTrainTargetFile(DSString target){

    ifstream targetData(target.c_str());
    if (!targetData.is_open()) {
        cerr << "Unable to open train target file" << endl;
        exit(1);
    }

    //ignoring first line of file
    targetData.ignore(256, '\n');

    for(int i = 0; i < 700000; i++){
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

//classify the words of the train data into positiveWords vector and negativeWords vector,
//depending on if the sentiment value of the tweet was 4 or 0 respectively
void sentimentMain::classifyWords(){

    int letterCounter = 0;
    int startCounter = 0;

    for(int i = 0; i < rowNumbersTrain.getSize(); i++){
        if(rowNumbersTrain.at(i) == rowNumbersTrainTarget.at(i)){
            //if sentiment is positive, add words to positiveWords vector
            if(sentimentTrainTarget.at(i) == "0"){
                DSString tempTweet = tweetTrain.at(i);
                for(int j = 0; j < tempTweet.size(); j++){
                    DSString word;
                    //comparing to ensure only characters within ASCII range of alphabet a-z/A-Z are accounted for
                    if((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                        letterCounter++;
                    }

                    //if character not within ASCII range, cut off here using substring
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

            //if sentiment is negative, add words to negativeWords vector
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

    //quicksorting the postive and negative words vectors so that we can perform binary search on them
    positiveWords.quickSort(0,positiveWords.getSize()-1);
    positiveWords.deleteRepeated();

    negativeWords.quickSort(0,negativeWords.getSize()-1);
    negativeWords.deleteRepeated();
}

//reading test data in order to test our algorithm with
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

//reading test target data in order to match ID numbers later to calculate accuracy
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

//testing the algorithm on the entire list of test data
void sentimentMain::testAnalyzer(){
    int letterCounter = 0;
    int startCounter = 0;
    int positiveWordFrequency = 0;
    int negativeWordFrequency = 0;
    sentimentValue  = new DSString[rowNumbersTest.getSize()];

    //performing same check as in classify words to ensure only characters within ASCII range are accounted for
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

        //performing quickSort on vector and deleting repeated elements
        wordsVectorTest.quickSort(0,(wordsVectorTest.getSize() - 1));
        wordsVectorTest.deleteRepeated();

        //performing binary search on positive/negative words vector in order to find specific words from the tweet
        for(int k = 0; k < wordsVectorTest.getSize(); k++){
            if(positiveWords.binarySearch(wordsVectorTest.at(k)) == true){
                positiveWordFrequency++;
            }
        }

        //incrementing counters of +/- frequencies
        for(int m = 0; m < wordsVectorTest.getSize(); m++){
            if(negativeWords.binarySearch(wordsVectorTest.at(m)) == true){
                negativeWordFrequency++;
            }
        }

        //if there are more positive words or if pos=neg, classify word as positive
        if(positiveWordFrequency >= negativeWordFrequency){
            positiveTweet.push_back(tweetTest.at(i));
            sentimentValue[i] = "4";
        }

        //else, classify word as negative
        else if(negativeWordFrequency > positiveWordFrequency){
            negativeTweet.push_back(tweetTest.at(i));
            sentimentValue[i] = "0";
        }

        //reset frequencies to be used by future words of tweet
        positiveWordFrequency = 0;
        negativeWordFrequency = 0;

        //delete elements for future tweets
        wordsVectorTest.deleteElements();

        letterCounter = 0;
        startCounter = 0;
    }
}

//create output file displaying accuracy rating
void sentimentMain::createAccuracyFile(char *input){

    ofstream outputFile;
    outputFile.open(input);

    float accuracyOutput = 0.0;
    float accuracyCounter = 0.0;
    float totalRows = (float)positiveTweet.getSize();

    DSVector<DSString> score;

    for(int i = 0; i < positiveTweet.getSize(); i++){
        if(sentimentTestTarget.at(i) == sentimentValue[i]){
            accuracyCounter++;
            score.push_back("c");
        }
        else{
            score.push_back("i");
        }
    }

    //i sorry my accuracy isn't great :(
    accuracyOutput = (accuracyCounter/totalRows);
    outputFile << accuracyOutput << endl;

    for(int i = 0; i < positiveTweet.getSize(); i++){
        outputFile << IDTestTarget.at(i) << "," << score.at(i) << endl;
    }
}
