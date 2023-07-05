#include <iostream>
#include <vector>
using namespace std;

int largestAltitude(vector<int>& gain) {
        int current=0;
        int max=0;
        for(int i=0;i<gain.size();i++){
            current+=gain[i];
            if(current>max){
                max=current;
            }
        }
        return max;
}

int main(int argc, char const *argv[])
{
    /* code */
    vector<int> gain{-4,-3,-2,-1,4,3,2};

    cout<<largestAltitude(gain);

    return 0;
}
