package hard;
import java.util.HashMap;
import java.util.Map;

public class app8 { 
        public static String minWindow(String s, String t) {
            if(s.length()==0||t.length()==0)return "";

            int unique=0;
            int matches=0;
            int left=0;
            int right=0;
            int cnt=0;
            int smllSize=-1;
            int smllStart=0;
            int smllEnd=0;

            char c;
            Map <Character, Integer> uniqueC = new HashMap<Character, Integer>();
            Map <Character, Integer> window = new HashMap<Character, Integer>();
            
            for(int i=0;i<t.length();i++){
                cnt = uniqueC.getOrDefault(t.charAt(i), 0);
                uniqueC.put(t.charAt(i), ++cnt);
            }

            unique=uniqueC.size();

            while(right<s.length()){
                c=s.charAt(right);
                cnt=window.getOrDefault(c, 0)+1;
                if(uniqueC.containsKey(c)&&cnt==uniqueC.get(c).intValue()){
                    matches++;
                }
                window.put(c, cnt);

                while(matches==unique){
                    c=s.charAt(left);
                    cnt=window.get(c);
                    if(uniqueC.containsKey(c)&&cnt<=uniqueC.get(c).intValue()){
                        matches--;
                    }
                    window.put(c, --cnt);

                    if(smllSize==-1||smllSize>right-left+1){
                        smllSize=right-left+1;
                        smllStart=left;
                        smllEnd=right;
                    }
                    left++;
                }

                right++;
            }
            return smllSize==-1?"":s.substring(smllStart, smllEnd+1);
        }
        public static void main(String[] args){
            String test = minWindow("a","aa");
            System.out.println(test);
        }
}


