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
}

void sentimentMain::readTrainFile(DSString trainFile){
    ifstream trainData(trainFile.c_str());
    if (!trainData.is_open()) {
        cerr << "Unable to open train file" << endl;
        exit(1);   // call system to stop
    }

    trainData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 11; i++){
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
    storeWords();
}

void sentimentMain::storeWords(){

    DSVector<DSString> wordsVector;
    int nonLetterCounter = 0;
    int startCounter = 0;

    for(int i = 0; i < tweetTrain.getSize(); i++){

        DSString tempTweet = tweetTrain.at(i);
        for(int j = 0; j < tempTweet.size(); j++){

            DSString word;
            while((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                nonLetterCounter++;
            }
            word = tempTweet.substring(startCounter, nonLetterCounter);
            nonLetterCounter++;
            startCounter = nonLetterCounter;

            wordsVector.push_back(word);
        }
    }
    wordsVector.printVector();
}




void sentimentMain::readTestFile(DSString testFile){
    ifstream testData(testFile.c_str());
    if (!testData.is_open()) {
        cerr << "Unable to open test file" << endl;
        exit(1);   // call system to stop
    }

    testData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                testData.getline(buffer,500, ',');
                rowNumbersTest.push_back(buffer);
            }
            else if(j == 1){
                testData.getline(buffer,500, ',');
                IDTest.push_back(buffer);

            }
            else if(j == 2){
                testData.getline(buffer,500, ',');
                userNameTest.push_back(buffer);
            }
            else if(j == 3){
                testData.getline(buffer,500);
                tweetTest.push_back(buffer);
            }
        }
        tweetTest.printVector();
    }
}

