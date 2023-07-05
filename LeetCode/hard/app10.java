package hard;
import java.util.Arrays;
import java.util.BitSet;

public class app10 { 
        public static int minCost(int n, int[] cuts) {
            int ans=0;
            int size=cuts.length;
            int start=0;
            int mid=n/2;
            int prevMid=n;
            int closest=0;
            int current=0;
            int[] sortCuts = Arrays.copyOf(cuts, size);
            BitSet cut = new BitSet(size);
            
            Arrays.sort(sortCuts);

            while(mid>0){
                for(int i=1;i<size;i++){
                    current=sortCuts[i]>mid?-1:0;
                    current=Math.abs(mid-sortCuts[i])+current;
                    closest=sortCuts[start]>mid?-1:0;
                    closest=Math.abs(mid-sortCuts[start])+closest;
                    
    
                    if(current<closest){
                        start=i;
                    }else if(current==closest){
                        if(start-1<0||i+1>=size||sortCuts[start]-sortCuts[start-1]<sortCuts[i+1]-sortCuts[i]){
                            start=i;
                        }
                    }
                }     
                cut.nextSetBit(0);
                mid/=2;
            }
                         
            
            return 0;
        }
        public static void main(String[] args){
            int size=9;
            int[] arr = {5,6,1,4,2};
            System.out.println(minCost(size,arr));
        }
}


