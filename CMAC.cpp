#include "CMAC.h"
#include "dataKit.h"
#include <utility>
#include<vector>
#include<cstdlib>
#include<iostream>
using namespace std;

vector<vector<float> > transVec(vector<vector<float> > mat){
    //转置
    vector<vector<float> > tempVec;
    int col;
    col = mat[0].size();
    int row = mat.size();
    for(int i = 0; i<row; i++){
        vector<float> tmptmpVec;
        for(int j = 0; j < col; j++){
            tmptmpVec.push_back(mat[j][i]);
        }
        tempVec.push_back(tmptmpVec);
    }
    return tempVec;
}

void CMAC::initCMAC(vector<vector<float> > dataSetI, vector<float> labelsI,int numOfTierI/**层数*/,int numOfQualifyI){
    CMAC::dataSet = move(dataSetI);
    CMAC::labels = move(labelsI);
    CMAC::numOfTier = numOfTierI;
    CMAC::numOfQualify = numOfQualifyI;
    CMAC::numOfInput = (int) CMAC::dataSet[0].size();

    // init with normalize all data
    normalization();
    // get the standard of qualification matrix
    getQualVec();
    // qualified all data
    getAllQualData();

    //init the origin pointer
    int numOfAC = 0;
    for(auto & i : qualVec){
        numOfAC += ((int)i.size() + 1)*((int)i.size() + 1);
    }
    printf("num of ac %d \n",numOfAC);
    CMAC::origin = (float *) malloc(sizeof(float) * numOfAC);
}

void CMAC::normalization(){
    vector<vector<float> > datasetT = transVec(CMAC::dataSet);
    for(auto & v : datasetT){
        v = vecMinMaxScaler(v);
    }
    datasetT = transVec(datasetT);
    CMAC::dataSet = datasetT;
}

void CMAC::getQualVec() {
    for(int i = 0; i < CMAC::numOfTier; i++){
        vector<int> tmpVec;
        CMAC::qualVec.push_back(tmpVec);
    }
    for(int i = 0; i < CMAC::numOfQualify - 1; i++){
        int row = i % CMAC::numOfTier;
        CMAC::qualVec[row].push_back(i+1);
    }
}

vector<vector<int> > CMAC::get1QualData(vector<float> data) {
    vector<vector<int> > result;
    for(auto & i : data){
        vector<int> tmp;
        for(int j = 0; j < CMAC::numOfTier; j++){
            int tmpInt = 0;
            for(auto & k : CMAC::qualVec[j]){
                if (10*i >= k){
                    tmpInt++;
                }else{
                    break;
                }
            }
            tmp.push_back(tmpInt);
        }
        result.push_back(tmp);
    }
    return result;
}

void CMAC::getAllQualData() {
    for(auto & i : CMAC::dataSet){
        CMAC::qualData.push_back(get1QualData(i));
    }
}

int CMAC::hash(vector<int>) {

    return 0;
}

