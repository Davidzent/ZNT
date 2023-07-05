
#include <vector>
#include <iostream>
using namespace std;


int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime);
int calTime(int pos, vector<int>&manager,vector<int>& informTime,vector<int>& timeToReach);

int main(int argc, char** argv) {
    int n=22;
    int headID=7;
    vector<int> manager     {12,7,  18, 11, 13,21, 12, -1, 6,5,  14,13, 14, 9,  20, 13,11,1,1,  2,  3,  19};
    vector<int> informTime  {0, 540,347,586,0, 748,824,486,0,777,0, 202,653,713,454,0, 0, 0,574,735,721,772};

    numOfMinutes(n,headID,manager,informTime);



    //9132
    return 0;
}

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime){
    int max=0;
    int temp;
    
    vector<int> timeToReach;
    timeToReach.resize(n);
    for(int i=0;i<n;i++){
        timeToReach[i]=-1;
    }
    timeToReach[headID]=0;

    for(int i=0;i<n;i++){
        temp=calTime(i,manager,informTime,timeToReach);
        max=temp>max?temp:max;

    }

    return max;
}

int calTime(int pos, vector<int>&manager,vector<int>& informTime,vector<int>& timeToReach){
    if(timeToReach[pos]!=-1){
        return timeToReach[pos];
    }
    int timeToCurPos = calTime(manager[pos],manager,informTime,timeToReach);
    timeToReach[pos]=timeToCurPos + informTime[manager[pos]];


    return timeToReach[pos];
}