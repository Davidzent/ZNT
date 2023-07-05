package hard;
public class app6 {
    public static int firstMissingPositive(int[] nums) {
        int size=nums.length;
        int min;
        int i=0;       
        boolean[] chck = new boolean[size+2];

        for(i=0;i<size;i++){
            if(nums[i]<=size&&nums[i]>0)chck[nums[i]]=true;
        }

        System.gc();
        i=0;
        while(true){
            if(!chck[++i])return i;
        }
        
        // int size=nums.length;
        // int min;
        // BitSet chck = new BitSet(size);

        // for(int num:nums){
        //     if(num<=size&&num>0)chck.set(num-1);
        // }
        // min=chck.nextClearBit(0);
        // return min+1;
    }
    public static void main(String[] args){
        int[] list = {1,2,2,2};
        int test = firstMissingPositive(list);
        System.out.println(test);
    }
}
