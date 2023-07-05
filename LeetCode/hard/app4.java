package hard;
public class app4 {
        // public static int isContinue(char[] sc,char toCopy, char endPat,int startPos){
        //     if(sc[startPos]!=toCopy||sc[startPos]==endPat)return startPos;
        //     for(int i=startPos;i<sc.length;i++){
        //         if(i+1<sc.length&&(sc[i+1]!=toCopy||sc[i+1]==endPat)){
        //             return i+1;
        //         }
        //     }
        //     return sc.length;
        // }

        // public static boolean isMatch(String s, String p) {
        //     char[] sc=s.toCharArray();
        //     char[] pc=p.toCharArray();
        //     int pSize = p.length();
        //     int sSize = s.length();

        //     int x=0;
        //     int j=0;

        //     char next='a';
        //     char endPat='\n';

        //     int tryEnd=-1;

            
        //     while(j<sSize&&x<pSize){
        //         if(x+1<pSize)next=pc[x+1];
                
        //         if(pc[x]==sc[j]||pc[x]=='.'||next=='*'){
        //             if(next=='*'){
        //                 if(pc[x]=='.'&&x+2<pSize)endPat=pc[x+2];
        //                 tryEnd=isContinue(sc, pc[x],endPat, j);
        //                 x++;
        //                 next='a';
        //                 endPat='\n';
        //                 if(tryEnd==-1){
        //                     if(x<pSize-1)return false;
        //                 }
        //                 else j=tryEnd;
        //             }else{
        //                 j++;
        //             }
        //             x++;
        //             if(x>=pSize&&j>=sSize)return true;
        //         }
        //         else{
        //             j++;
        //         }
        //     }
        //     while(x<pSize){
        //         if(x+1<pSize&&pc[x+1]=='*')x+=2;
        //         else return false;
        //     }
        //     if(x>=pSize&&j>=sSize)return true;
        //     return false;
        // }

            
        public static void main(String[] args){
            boolean test = isMatch("aaaab","a*b*b");
            System.out.println(test);
        }
    
        public static boolean isMatch(String text, String pattern) {
            if (pattern.isEmpty()) return text.isEmpty();
            boolean first_match = (!text.isEmpty() &&
                                   (pattern.charAt(0) == text.charAt(0) || pattern.charAt(0) == '.'));
    
            if (pattern.length() >= 2 && pattern.charAt(1) == '*'){
                return (isMatch(text, pattern.substring(2)) ||
                        (first_match && isMatch(text.substring(1), pattern)));
            } else {
                return first_match && isMatch(text.substring(1), pattern.substring(1));
            }
        }
}


