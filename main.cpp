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
    CMAC newCmac;
    vector<vector<float> > a = {{1,0},{0,1},{1,1}};
    vector<float> labelA = {1,0,-1};
    newCmac.initCMAC(a,labelA,4,3);

    printf("---- predict,expect1 ----\n");
    vector<float> b = {1,0};
    newCmac.predict(b);

    printf("---- predict,expect0 ----\n");
    vector<float> c = {0,0.99};
    newCmac.predict(c);

    printf("---- predict,expect-1 ----\n");
    vector<float> d = {1,0.99};
    newCmac.predict(d);
    return 0;
}
