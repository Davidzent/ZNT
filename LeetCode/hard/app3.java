package hard;
import java.util.ArrayList;

public class app3 {
        public static int numTilePossibilities(String tiles) {
            int[] cnt = new int[26];
            for (char c : tiles.toCharArray()) {
                ++cnt[c - 'A'];
            }
            return countRec(cnt);
        }
        
        private static int countRec(int[] cnt) {
            int res = 0;
            for (int i = 0; i < cnt.length; ++i) {
                if (cnt[i] > 0) {
                    ++res;
                    --cnt[i];
                    res += countRec(cnt);
                    ++cnt[i];
                }
            }
            return res;
        }
            
        public static void main(String[] args){
            int test = numTilePossibilities("AAABBC");
            System.out.println(test);
        }
    
}


