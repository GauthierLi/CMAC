#ifndef CMAC_H
#define CMAC_H
#include<vector>
#include<cstdlib>
using namespace std;


vector<vector<float> > transVec(vector<vector<float> > mat);
class CMAC
{
    public:
        float* origin = (float*)malloc(sizeof(float));
        vector<vector<float> > dataSet;
        vector<vector<vector<int> > > qualData;
        // qualVec is used for store the standard of qualification matrix
        vector<vector<int> > qualVec;
        vector<float> labels;

        // dimension of input data
        int numOfInput;
        // dimension of Tier
        int numOfTier;
        int numOfQualify;
        int numOfOutput;

        void normalization();
        void initCMAC(vector<vector<float> > dataSetI, vector<float> labelsI,
                           int numOfTierI/**层数*/,int numOfQualifyI, int numOfInputI);
        void getQualVec();
        vector<vector<int> > get1QualData(vector<float> data);
        void getAllQualData();
        int hash(vector<int>);


};

#endif // CMAC_H
