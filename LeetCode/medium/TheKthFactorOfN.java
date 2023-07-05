package medium;

public class TheKthFactorOfN {
    public static int kthFactor(int n, int k) {
        int cnt=0;
        // int mid=n/2;
        for(int i=1;i<=n;i++){
            if(n%i==0)cnt++;
            if(cnt==k)return i;
        }

        return -1;
    }
    
    public static void main(String[] args) {
        System.out.println(kthFactor(4, 4));
    }
}
