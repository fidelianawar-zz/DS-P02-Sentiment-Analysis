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
                rowNumbers.push_back(buffer);
            }
            else if(j == 1){
                trainData.getline(buffer,500, ',');
                ID.push_back(buffer);

            }
            else if(j == 2){
                trainData.getline(buffer,500, ',');
                userName.push_back(buffer);
            }
            else if(j == 3){
                trainData.getline(buffer,500);
                tweet.push_back(buffer);
            }
        }
    }
}

void sentimentMain::storeWords(){

}

void sentimentMain::readTestFile(DSString testFile){
    ifstream testData(testFile.c_str());
    if (!testData.is_open()) {
        cerr << "Unable to open test file" << endl;
        exit(1);   // call system to stop
    }
    //grabs first line
    char firstLine[30];
}

