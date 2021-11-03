#include <cstdlib>
#include <cstdio>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "dataKit.h"

using namespace std;

void printVecOneD(vector<float> vec) {
    /** print 1D vector */
    for (float &it: vec) {
        printf("%.5f ", it);
    }
    printf("\n");

}

void printVec2D(vector<vector<float> > vec) {
    for (auto &it: vec) {
        for (float &it1: it) {
            printf("%.5f ", it1);
        }
        printf("\n");
    }
    printf("\n");
}

void printArr(float *p1, int len) {
    /**打印列表*/
    for (int i = 0; i < len; i++) {
        printf("%.3f ", p1[i]);
    }
    printf("\n");
}

float average(float *p1, int len) {
    /**求均值*/
    if (p1 == nullptr) {
        printf("error -1 : Null point!!!");
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    float avr = 0;
    for (int i = 0; i < len; i++) {
        avr += p1[i];
    }
    return avr / (float) len;
}

float vecAverage(vector<float> vec) {
    int num = vec.size();
    float result = 0;
    for (float &it: vec){
        result += it;
    }
    result = result / (float) num;
    return result;
}

int zscoreScaler(float *p1, int len) {
    /**0均值标准化*/
    if (p1 == nullptr) {
        printf("error -1: Null point!!!");
        return -1;
    }

    if (len == 0) {
        printf("error -2: lenth is 0!!!");
        return -2;
    }

    float avr = average(p1, len);

    float avrSquar = 0;
    for (int i = 0; i < len; i++) {
        avrSquar += (p1[i] - avr) * (p1[i] - avr);
    }
    avrSquar = avrSquar / (float) len;
    avrSquar = sqrt(avrSquar);

    for (int i = 0; i < len; i++) {
        p1[i] = (p1[i] - avr) / avrSquar;
    }
    return 0;
}

float findMinMax(float *p1, int len, int n) {
    /**Find minimum num, 0 represent minimum, 1 represent maximum.*/
    float Mini = p1[0];
    float Maxi = p1[0];

    for (int i = 0; i < len; i++) {
        if (Mini > p1[i]) Mini = p1[i];
        if (Maxi < p1[i]) Maxi = p1[i];
    }

    if (n == 0) {
        return Mini;
    } else if (n == 1) {
        return Maxi;
    } else {
        printf("error : please input right indication number!");
        return -99999;
    }
}

float vecFindMinMax(vector<float> p1, int id/**0为最小，1为最大*/){
    float min = 999999;
    float max = -999999;
    for(float & num: p1){
        min = min < num ? min : num;
        max = max > num ? max : num;
    }
    if (id == 0){
        return min;
    }else if(id == 1){
        return max;
    }
    printf("worry id!");
    return -1;
}

int minMaxScaler(float *p1, int len) {
    /** 离差标准化，放缩到0-1 */
    if (p1 == nullptr) {
        printf("error -1: Null point!!!");
        return -1;
    }

    if (len == 0) {
        printf("error -2: length is 0!!!");
        return -2;
    }
    float minimum = findMinMax(p1, len, 0);
    float maximum = findMinMax(p1, len, 1);

    if (minimum == maximum) {
        for (int i = 0; i < len; i++) {
            p1[i] = 1;
        }
    }

    for (int i = 0; i < len; i++) {
        p1[i] = (p1[i] - minimum) / (maximum - minimum);
    }
    return 0;
}

vector<float> vecMinMaxScaler(vector<float> p1){
    vector<float> result;
    float min = 0, max = 0;
    min = vecFindMinMax(p1);
    max = vecFindMinMax(p1, 1);
    for(float & num : p1){
        float tmp = (num - min)/(max - min);
        result.push_back(tmp);
    }
    return result;
}

void readCsv(char *fileName, int line_pre, int line_end, vector<vector<float> > &data/**out*/) {
    /**read csv as a matrix*/
    ifstream inFile(fileName, ios::in);
    string lineStr;
    vector<vector<string> > strArray;
    while (getline(inFile, lineStr)) {
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        while (getline(ss, str, ',')) {
            lineArray.push_back(str);
        }
        strArray.push_back(lineArray);
    }


    for (int i = line_pre; i < line_end; i++) {
        vector<float> tmp_vec;
        for (auto & it : strArray[i]) {
            stringstream stream;
            float tmp = 0.0;
            stream << it;
            stream >> tmp;
            tmp_vec.push_back(tmp);
        }
        data.push_back(tmp_vec);
    }

}


void OneDlinearRegression(vector<vector<float> > data, float *w/** out */, float *b/** out */) {
    /** get the parametres of linear regression*/
    // the form of data is a matrix of n*2
    float tmp_sum1 = 0.0, tmp_sumSquar = 0.0, tmp_sum2 = 0.0, tmp_average = 0.0, tmp_b = 0.0;
    int tmp_num = 0;
    for (auto & it1 : data) {
        tmp_average += it1[0];
        tmp_num++;
    }
    tmp_average = tmp_average / (float)tmp_num;

    for (auto & it1 : data) {
        tmp_sum1 += it1[1] * (it1[0] - tmp_average);
    }

    for (auto & it1 : data) {
        tmp_sumSquar += it1[0] * it1[0];
    }

    tmp_sum2 = tmp_num * tmp_average * tmp_average;

    *w = tmp_sum1 / (tmp_sumSquar - tmp_sum2);

    for (auto & it1 : data) {
        tmp_b += it1[1] - (*w) * (it1[0]);
    }
    tmp_b = tmp_b / tmp_num;
    *b = tmp_b;
}

