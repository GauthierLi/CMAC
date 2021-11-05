#ifndef CMAC_H
#define CMAC_H
#include<vector>
#include<cstdlib>
#include<map>
using namespace std;

template <typename T>
vector<vector<T> > transVec(vector<vector<T> > mat);
class CMAC
{
    public:
        float* origin = nullptr;
        vector<vector<float> > dataSet;
        vector<float> labels;
        // use to recording the min and max to scale the data
        vector<float> mini , maxi ;

        vector<vector<vector<int> > > qualData;
        // qualVec is used for store the standard of qualification matrix
        vector<vector<int> > qualVec;

        //used to map qualData to real address
        map<int, float> storageUnit;

        //use to storage the changing of the error
        vector<float> errorVec;

        // dimension of input data
        int numOfInput;
        // dimension of Tier
        int numOfTier;
        int numOfEpoch;
        int numOfQualify;

        //print all information of parameters
        void lookLook();

        void normalization();
        void initCMAC(vector<vector<float> > dataSetI, vector<float> labelsI,
                           int numOfTierI/**层数*/,int numOfQualifyI,int epoch, float learnRate=0.2);
        void getQualVec();
        vector<vector<int> > get1QualData(vector<float> data);
        void getAllQualData();

        // mapping to real location
        int vec2Int(vector<int> myVec, int indexOfTier);
        int hash(vector<int> myVec, int indexOfTier);

        // propagation forward
        void learnOnce(vector<vector<int> > aData, float label, float learnRate=0.2);
        void learnAll(float learnRate = 0.2);

        float predict(vector<float> vec, int show = 1);
};

#endif // CMAC_H
