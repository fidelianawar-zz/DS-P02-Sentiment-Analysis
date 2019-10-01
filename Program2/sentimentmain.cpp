#include "sentimentmain.h"
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>

using namespace std;

//main method to run program execution

sentimentMain::sentimentMain()
{
    buffer = nullptr;
}
sentimentMain::~sentimentMain(){
    delete [] buffer;

}

void sentimentMain::readTrainFile(DSString trainFile){
    ifstream trainData(trainFile.c_str());
    if (!trainData.is_open()) {
        cerr << "Unable to open TeamA file" << endl;
        exit(1);   // call system to stop
    }
    //grabs first line
    char firstLine[30];

    //reads first line about column info
    trainData.getline(firstLine, 256);

    //reading until end of file
    while(trainData.eof()){
        for(int j = 0; j < 4; j++){
            if(j == 0){
                //rowNumbers.push_back(trainData.getline(buffer,256, ','));
            }
            if(j == 1){
                trainData.getline(buffer,256, ',');
                //ID.push_back();
            }
            if(j == 2){
                trainData.getline(buffer,256, ',');
               // userName.push_back();
            }
            if(j == 3){
                trainData.getline(buffer,256, ',');
               // tweet.push_back();
            }
        }
    }
}

