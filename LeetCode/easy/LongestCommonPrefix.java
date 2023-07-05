public class LongestCommonPrefix {
    public static String longestCommonPrefix(String[] strs) {
        if(strs.length==0)return "";
        else{
            String guess = strs[0]; //assume everything matches
            
            for(int i = 1; i < strs.length; i++){
                while(strs[i].indexOf(guess) !=0){  //try to find a match
                    guess = guess.substring(0, guess.length()-1); //if it doesn't find it then it removes one from the end till it finds it
                }
            }
            return guess;
        }
    }

    public static void main(String[] args) {
        String[] temp = {"flower","flow","flight"};
        System.out.println(longestCommonPrefix(temp));
        
    }
}
