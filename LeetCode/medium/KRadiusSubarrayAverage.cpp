#include <iostream>
#include <vector>

using namespace std;

vector<int> getAverages(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> avg(n,-1);
    
    long sum=0;
    int center=k;
    int diameter=k*2; 

    for(int i=0;i<n;i++){
        sum+=nums[i];
        if(i>=diameter){
            avg[center]=sum/(diameter+1);
            sum-=nums[center-k];
            center++;
        }
    }

    return avg;
}

int main(int argc, char const *argv[])
{
    /* code */
    vector<int> nums{7,4,3,9,1,8,5,2,6};
    int k=3;

    vector<int> test = getAverages(nums,k);

    return 0;
}
