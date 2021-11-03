#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<map>
#include"dataKit.h"
#include"CMAC.h"
#include<ctime>
#define rand(x) rand()%x/(float)(100*x)
using namespace std;

int main(){
    srand((int)time(0));
    float *p1;
    CMAC newCmac;
    p1 = (float*)malloc(sizeof(float));
    *(p1+1) = 1.23;
    printf("%f\n", *(p1+1));

    vector<vector<float> > a = {{3,4,6},{4.5,6,8},{2,7,5}};
    vector<float> labelA = {1,0,1};

    newCmac.initCMAC(a,labelA,3,6);
    printf("before normalization\n");
    printVec2D(a);
    printf("after normalization\n");
    printVec2D(newCmac.dataSet);
    printf("print the qualification rules\n");
    for(auto & i : newCmac.qualVec){
        for(auto & j : i){
            printf("%lu \t",j);
        }
        printf("\n");
    }

    printf("qualification of data a[0]={3,4,6}(0.40000 0.00000 0.33333):\n");
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

    printf("random number: %f", rand(10));
    return 0;
}
