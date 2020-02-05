# DS-P02-Sentiment-Analysis

Built a sentiment classifier in C++ to classify over 1 million Twitter tweets as positive or negative sentiment. Trained
the classifier using data set with pre-classified members and tested classifier on un-labeled tweets to determine its accuracy.

Implemented custom templated String and Vector classes which were incorporated into the functionality of the program. Along with
various Catch tests using TDD.

Final version of the program runs from the command line with the following arguments:
  >./classifier.out dev-train-data.csv dev-train-target.csv dev-test-data.csv dev-test-target.csv Output.txt
