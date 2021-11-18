/*
 * Michael and David
 */

#include "timeseries.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

/*
 * This class contain the data from the file
 */
TimeSeries::TimeSeries(const char *CSVfileName) {
    //initialize the map
    this->matrix = new map<string, vector<float>>;
    setName(CSVfileName);
    //extract the data from the file.
    readCSVFile(CSVfileName);
}

void TimeSeries::setName(const char *name) {
    char *fileName = new char[strlen(name) + 1];
    strcpy(fileName, name);
    this->csvName = fileName;
}

const char *TimeSeries::getName() {
    return this->csvName;
}


void TimeSeries::loadDataFromCSVFile(const char *CSVfileName) {
    ifstream CSVfile(CSVfileName);
    if (!CSVfile.is_open()) {
        throw runtime_error("couldn't open this file.");
    }
    //in this vector I save all the lines.
    vector<string> values;
    //getting the first line from the file (the names of the features).
    getline(CSVfile, line);
    //creating vector with the name of the features.
    this -> featuresNames = dataSeparation(line, ',');

    //getting all tje lines with values.
    while (getline(CSVfile, line)) {
        values = dataSeparation(line, ',');
        // add the date to the map
        add(line, values);
    }
    CSVfile.close();
}

void TimeSeries::add(string line, vector<string> vec) {
    for (int i = 0; i < featuresNames.size(); ++i) {
        //pushing this value to its suitable vector according to the name of the feature.
        matrix[feature_name[i]].push_back(stof(vec[i]));
    }
}

vector<string> TimeSeries::dataSeparation(string line, char delim) {
    stringstream s(line);
    string str;
    vector<string> vec;
    //separate the line into word without punctuation.
    while (getline(s, str, delim)) {
        vec.push_back(str);
    }
    return vec;
}

vector<float> TimeSeries::getValues(string str) const {
    return getDataTable()[str];
}

const vector <string> TimeSeries::getFeatureNames() const{
    return this->featuresNames;
}

map<string, vector<float>> TimeSeries::getMatrix() const { {
        return matrix;
}

TimeSeries::~TimeSeries(){
        delete this->csvName
}
;