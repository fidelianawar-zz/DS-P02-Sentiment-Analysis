#define CATCH_CONFIG_RUNNER

#include "sentimentmain.h"
#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>

ifstream trainData;
ifstream trainTargetFile;
ifstream testData;
ifstream testTargetFile;

int runCatchTests(int argc, char* argv[1]){
    return Catch::Session().run(argc,argv);
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        return runCatchTests(argc, argv);
    }
    else{
        cout << "we got here";

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
}
