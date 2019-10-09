#define CATCH_CONFIG_RUNNER

#include "sentimentmain.h"
#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"
#include "sentimentmain.h"
#include <iostream>
#include <fstream>


int runCatchTests(int argc, char* argv[1]){
    return Catch::Session().run(argc,argv);
}

int main(int argc, char *argv[])
{
    ifstream trainData;
    ifstream trainTargetFile;
    ifstream testData;
    ifstream testTargetFile;

    if(argc == 1){
        return runCatchTests(argc, argv);
    }
    else{
        sentimentMain newGame;
        for(int i = 0; i < argc; i++){
            if(i == 1){
                trainData.open(argv[i]);
                trainTargetFile.open(argv[2]);
                newGame.readTrainTargetFile(argv[2]);
                newGame.readTrainFile(argv[i]);
            }
            else if(i == 3){
                testData.open(argv[i]);
                newGame.readTestFile(argv[i]);
            }
            else if(i == 4){
                testTargetFile.open(argv[i]);
                newGame.readTestTargetFile(argv[i]);
            }
            else if(i == 5){
                newGame.createAccuracyFile(argv[i]);
            }
        }
    }
}
