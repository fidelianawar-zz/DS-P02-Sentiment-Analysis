#include "sentimentmain.h"
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>

using namespace std;

ifstream trainData;
ifstream trainTargetFile;
ifstream testData;
ifstream testTargetFile;

//main method to run program execution
int main(int argc, char *argv[])
{
    argc = 5;
    sentimentMain newGame;

    for(int i = 0; i < argc; i++){
        if(i == 1){
            trainData.open(argv[i]);
            newGame.readTrainFile(argv[i]);
        }
        else if(i == 2){
            trainTargetFile.open(argv[i]);
            newGame.readTrainTargetFile(argv[i]);
        }
        else if(i == 3){
            testData.open(argv[i]);
            newGame.readTestFile(argv[i]);
        }
        //trying to see if fifth argument is vlow, creating output file
        else if(i == 4){
            testTargetFile.open(argv[i]);
            newGame.readTestTargetFile(argv[i]);
        }
    }
}
sentimentMain::sentimentMain()
{
    buffer = nullptr;
}
sentimentMain::~sentimentMain(){
    delete [] buffer;

}

void sentimentMain::readTrainFile(DSString trainFile){
    if (!trainData.is_open()) {
        cerr << "Unable to open TeamA file" << endl;
        exit(1);   // call system to stop
    }

    ifstream trainData(trainFile.c_str());

    //grabs first line
    char firstLine[30];

    //reads first line about column info
    trainData.getline(firstLine, 256);

    while(trainData.eof()){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                trainData.getline(buffer,256, ',');
                rowNumbers.push_back();
            }
            if(j == 1){
                trainData.getline(buffer,256, ',');
                ID.push_back();
            }
            if(j == 2){
                trainData.getline(buffer,256, ',');
                userName.push_back();
            }
            if(j == 3){
                trainData.getline(buffer,256, ',');
                tweet.push_back();
            }
        }
    }
}

