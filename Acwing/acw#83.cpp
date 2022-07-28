class Solution {
public:
    int maxDiff(vector<int>& nums) {
        if(nums.size()<2) return 0;
        int cmin=nums[0],ans=0;
        for(int i=1;i<(int)nums.size();i++) {
            ans=max(ans,nums[i]-cmin);
            cmin=min(cmin,nums[i]);
        }
        return ans;
    }
};
