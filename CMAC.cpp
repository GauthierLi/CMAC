#include "CMAC.h"
#include "dataKit.h"
#include <cmath>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<ctime>
#define rand(x) rand()%x/(float)(100*x)
using namespace std;

template <typename T>
vector<vector<T> > transVec(vector<vector<T> > mat){
    //转置
    vector<vector<T> > tempVec;
    int col;
    col = mat[0].size();
    int row = mat.size();
    for(int i = 0; i<row; i++){
        vector<T> tmptmpVec;
        for(int j = 0; j < col; j++){
            tmptmpVec.push_back(mat[j][i]);
        }
        tempVec.push_back(tmptmpVec);
    }
    return tempVec;
}

void CMAC::initCMAC(vector<vector<float> > dataSetI, vector<float> labelsI,int numOfTierI/**层数*/,int numOfQualifyI){
    printf("processing deal with dataset\n");
    CMAC::dataSet = move(dataSetI);
    printf("processing deal with labels\n");
    CMAC::labels = move(labelsI);
    printf("processing deal with tiers\n");
    CMAC::numOfTier = numOfTierI;
    printf("processing deal with qualify\n");
    CMAC::numOfQualify = numOfQualifyI;
    CMAC::numOfInput = (int) CMAC::dataSet[0].size();

    // init with normalize all data
    printf("processing deal with normalization\n");
    normalization();
    // get the standard of qualification matrix
    printf("processing deal with get qualify standard\n");
    getQualVec();
    // qualified all data
    printf("processing deal with qualify all data\n");
    getAllQualData();

    lookLook();
    printf("processing deal with learning\n");
    learnAll();
}

void CMAC::lookLook(){
    printf("--------------------- all data and labels -----------------------\n");
    printf("print all modified data:\n");
    int count = 0;
    for(auto & i : CMAC::qualData){
        for(auto & j : i){
            printf("[");
            for(auto & k : j){
                printf("%d ", k);
            }
            printf("],");
        }
        printf("label: %f",CMAC::labels[count++]);
        printf("\n");
    }
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
    result = transVec(result);
    return result;
}

void CMAC::getAllQualData() {
    for(auto & i : CMAC::dataSet){
        CMAC::qualData.push_back(get1QualData(i));
    }
}

int CMAC::vec2Int(vector<int> myVec, int indexOfVec) {
    /*
     * first modified myvec into a real num, like 101011,
     * to avoid the conflict of 0101 and 00101, we use a
     * bias of indexOfVec * 10^(myVec.size())
     *
     * parameter indexOfVec represent the index of index of variable,
     * like x= [x_1,x_2,x_3,...,]
     * */
    int lenth = (int)myVec.size();
    int numberAfterModify = (int)pow(10., (float)lenth) * indexOfVec;
    for(int i = 0; i < lenth; i++){
        numberAfterModify += (int)pow(10., (float)(lenth - i - 1)) * myVec[i];
    }
    return numberAfterModify;
}

int CMAC::hash(vector<int> myVec, int indexOfVec) {
    srand((int)time(0));
    int numberAfterModify = CMAC::vec2Int(myVec, indexOfVec);
    //printf("%d\n", numberAfterModify);
    if (CMAC::storageUnit.find(numberAfterModify) == CMAC::storageUnit.end()){
        float randNum = rand(10);
        CMAC::storageUnit[numberAfterModify] = randNum;
    }
    return 0;
}

void CMAC::learnOnce(vector<vector<int>> aData, float label, float learnRate) {
    float result = 0.;
    float count = (float)aData.size();
    int index = 0;
    for(auto & i : aData){
        int numberAfterModify = CMAC::vec2Int(i, index);
        CMAC::hash(i, index);
        result += CMAC::storageUnit[numberAfterModify];
        index++;
    }
    float error = label - result;
    index = 0;
    for(auto & i : aData){
        int numberAfterModify = CMAC::vec2Int(i, index);
        CMAC::storageUnit[numberAfterModify] = learnRate * error / count;
    }
}

void CMAC::learnAll(float learnRate) {
    printf("in\n");
    int mountOfData = (int) CMAC::qualData.size();
    for(int i = 0; i < mountOfData; i++){
        printf("learning %d\n", i);
        CMAC::learnOnce(CMAC::qualData[i], CMAC::labels[i], learnRate);
    }
}



