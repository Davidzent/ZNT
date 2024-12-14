import java.util.HashSet;
import java.util.Set;
import java.util.ArrayList;


public class app {
    public static void main(String[] args) {
        final long MOD = 1000000007;
        int N=3;
        ArrayList <Integer> validNums = new ArrayList<>();
        int numValid=0;
        int L = 99, R=99999;
        for(int i=L;i<=R;i++){
            if(isValidNum(i)){
                validNums.add(i);
                numValid++;
            }
        }
        long totalMatrices = 1;
        for (int i = 0; i < N * N; i++) {
            totalMatrices = (totalMatrices * (numValid - i)) % MOD;
        }

        System.out.println(totalMatrices);
        //961694504
    }

    public static boolean isValidNum(int n){
        int[] arr={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};

        Set<Integer> primes = new HashSet<>();
        for (int element : arr) {
            primes.add(element);
        }

        String s = Integer.toString(n);
        int sum=0;
        int number = 0;
        for(int i=0;i<s.length()-1;i++){
            sum+=s.charAt(i)-'0';
            number=Integer.parseInt(""+s.charAt(i)+s.charAt(i+1));
            if(!primes.contains(number))return false;
        }
        sum+=s.charAt(s.length()-1)-'0';
        return sum%3==0;
    }

}
