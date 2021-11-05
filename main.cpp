#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<map>
#include"dataKit.h"
#include"CMAC.h"
#include"readAndWrite.cpp"
#include<ctime>
#include<vector>
#include<cmath>
#define rand(x) rand()%x/(float)x
using namespace std;
vector<vector<float> > plotData;

void setTestData(vector<vector<float> > *a, vector<float> *labelA, int num){
    srand(time(0));
    int i = 0;
    while(i++ <= num){
        float tmp = rand(1000);
        vector<float> tmpVec;
        tmpVec.push_back(tmp);
        a->push_back(tmpVec);
        tmpVec.push_back(sin(4*3.1415926*tmp));
        labelA->push_back(sin(4*3.1415926*tmp));
        plotData.push_back(tmpVec);
    }
}

void createTestSet(vector<float> *testSet){
    vector<vector<float> > a;
    vector<float> labelA;
    setTestData(&a, &labelA, 100);
    for(auto & i : a){
        testSet->push_back(i[0]);
    }
}

int main(){
    CMAC newCmac;
    vector<vector<float> > a;
    vector<float> labelA;
    setTestData(&a, &labelA, 1000);
    newCmac.initCMAC(a,labelA,10,100,50);


    vector<float> b = {a[0][0]};
    printf("---- predict,expect %f ----\n", b[0]*b[0]);
    newCmac.predict(b);

    vector<float> c = {0.51};
    printf("---- predict,expect %f ----\n",c[0]*c[0]);
    newCmac.predict(c);

    vector<float> d = {0.62};
    printf("---- predict,expect %f ----\n",d[0]*d[0]);
    newCmac.predict(d);

//    printVecOneD(newCmac.errorVec);
    writeFile("origin.txt",plotData);
    vector<vector<float> > testData;
    vector<float> tmpVec;

    // create test data and outputs with txt file
    createTestSet(&tmpVec);
    for(auto & i : tmpVec){
        vector<float> tempvec2;
        tempvec2.push_back(i);
        tempvec2.push_back(newCmac.predict(tempvec2,0));
        testData.push_back(tempvec2);
    }
    writeFile("testData.txt", testData);
    return 0;
}
