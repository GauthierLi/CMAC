#include<bits/stdc++.h>
#include<iostream>
#include"dataKit.h"
#include"CMAC.h"
using namespace std;

int main(){
    float *p1;
    CMAC newCmac;
    p1 = (float*)malloc(sizeof(float));
    *(p1+1) = 1.23;
    printf("%f\n", *(p1+1));

    vector<vector<float> > a = {{1,23,456},{45,6,14},{2,43,5}};
    vector<float> labelA = {1,0,1};

    newCmac.initCMAC(a,labelA,3,9,3);
    printf("before normalization\n");
    printVec2D(a);
    newCmac.normalization();
    printf("after normalization\n");
    printVec2D(newCmac.dataSet);
    printf("print the qualification rules\n");
    for(auto & i : newCmac.qualVec){
        for(auto & j : i){
            printf("%lu \t",j);
        }
        printf("\n");
    }

    printf("qualification of data a[0]={1,23,456}(0.00000 0.45946 1.00000):\n");
    for(auto & i : newCmac.get1QualData(newCmac.dataSet[0])){
        for(auto & j : i){
            printf("%lu \t",j);
        }
        printf("\n");
    }

    printf("print all data which is after modified\n");
    for(auto & i : newCmac.qualData){
        for(auto & j : i){
            printf("[");
            for(auto & k : j){
                printf("%d ", k);
            }
            printf("],");
        }
        printf("\n");
    }


    return 0;
}
