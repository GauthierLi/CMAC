//
// Created by shiny on 2021/11/5.
//
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;

template<typename T>
void writeFile(string fileName, vector<vector<T> > vec) {
    ofstream myFile(fileName);
    for(auto & i : vec){
        for(auto & j : i){
            myFile << j;
            myFile << " ";
        }
        myFile << "\n";
    }
}