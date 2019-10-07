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
    //rowNumbersTrain.printVector();

    classifyWords();
}

void sentimentMain::readTrainTargetFile(DSString target){

    ifstream targetData(target.c_str());
    if (!targetData.is_open()) {
        cerr << "Unable to open train target file" << endl;
        exit(1);   // call system to stop
    }

    //ignoring first line of file
    targetData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 11; i++){
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
    //cout << sentimentTrainTarget.at(0);
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
                    else if((!(tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123))){
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
                    else if((!(tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123))){
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

    //positiveWords.printVector();


    negativeWords.quickSort(0,negativeWords.getSize()-1);
    negativeWords.deleteRepeated();
    //negativeWords.printVector();

}

void sentimentMain::readTestFile(DSString test){
    ifstream targetData(test.c_str());
    if (!targetData.is_open()) {
        cerr << "Unable to open test file" << endl;
        exit(1);   // call system to stop
    }

    targetData.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                targetData.getline(buffer,500, ',');
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

    testTarget.ignore(256, '\n');

    //reading until end of file
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                testTarget.getline(buffer,500, ',');
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

    for(int i = 0; i < rowNumbersTest.getSize(); i++){
        DSString tempTweet = tweetTest.at(i);
        for(int j = 0; j < tempTweet.size(); j++){
            DSString word;
            if((tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                letterCounter++;
            }
            else if(!(tempTweet[j] > 64 && tempTweet[j] < 91) || (tempTweet[j] > 96 && tempTweet[j] < 123)){
                word = tempTweet.substring(startCounter, letterCounter);
                word.toLowerCase(word);
                letterCounter++;
                startCounter = letterCounter;
                wordsVectorTest.push_back(word);
                //newVector.push_back(wordsVectorTest);
                //wordsVectorTest.deleteElements();
            }
            for(int k = 0; k < wordsVectorTest.getSize(); k++){
                //if(positiveWords.binarySearch(wordsVectorTest.at(k)) == true){
                    positiveWordFrequency++;
                //}
            }
            for(int h = 0; h < wordsVectorTest.getSize(); h++){
               // if(negativeWords.binarySearch(wordsVectorTest.at(h)) == true){
                    negativeWordFrequency++;
               // }
            }
        }
        cout << positiveWordFrequency << endl;
        letterCounter = 0;
        startCounter = 0;

    }
     //wordsVectorTest.printVector();
}


//        letterCounter = 0;
//        startCounter = 0;
//        cout << "made it here" << endl;
//        newVector.push_back(wordsVectorTest);

//wordsVectorTest.deleteElements();


//    for(int i = 0; i < newVector.getSize(); i++){
//        newVector.at(i).quickSort(0,newVector.at(i).getSize()-1);
//        newVector.at(i).deleteRepeated();
//        newVector.at(i).printVector();
//    }

//    for(int i = 0; i < newVector.getSize(); i++){
//        for(int j = 0; j < newVector.at(i).getSize(); j++){
//            if(positiveWords.binarySearch(newVector.at(i).at(j))){
//                positiveFrequencyCounter++;
//            }
//        }
//    }

//    for(int i = 0; i < newVector.getSize(); i++){
//        for(int j = 0; j < newVector.at(i).getSize(); j++){
//            if(negativeWords.binarySearch(newVector.at(i).at(j))){
//                negativeFrequencyCounter++;
//            }
//        }
//    }










//    wordsVectorTest.quickSort(0, wordsVectorTest.getSize()-1);
//    wordsVectorTest.printVector();
//cout << positiveFrequencyCounter << endl;



//    for(int i = 0; i < positiveWords.getSize(); i++){

//       if(positiveWords.binarySearch(wordsVectorTest.at(i)) == true){
//            positiveFrequencyCounter++;
//       }
//   }

//}

//    for(int i = 0; i < negativeWords.getSize(); i++){
//        if(negativeWords.binarySearch(wordsVectorTest.at(i)) == true){
//            negativeFrequencyCounter++;
//        }
//    }

//    for(int i = 0; i < tweetTest.getSize(); i++){
//        if(positiveFrequencyCounter == negativeFrequencyCounter){
//            negativeTweet.push_back(tweetTest.at(i));
//        }
//        else if(positiveFrequencyCounter > negativeFrequencyCounter){
//            positiveTweet.push_back(tweetTest.at(i));
//        }
//        else if(negativeFrequencyCounter > positiveFrequencyCounter){
//            negativeTweet.push_back(tweetTest.at(i));
//        }

//    }
//    negativeTweet.printVector();

//}

//creation of output file
//void sentimentMain::createAccuracyFile(char* input){
//    ofstream accuracyOutput;
//    accuracyOutput.open(input);

//}




