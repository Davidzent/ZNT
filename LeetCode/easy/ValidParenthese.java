import java.util.Stack;

public class ValidParenthese {
    public static boolean isValid(String s) {
        int cnt=0;
        char c='\n';
        Stack<Character> current = new Stack();
        for(int i=0;i<s.length();i++){
            switch(s.charAt(i)){
                case '(':case '[':case '{':cnt++;current.push(s.charAt(i));break;
                case')':c='(';
                case']':c=c=='\n'?'[':c;
                case'}':c=c=='\n'?'{':c;
                    cnt--;
                    if(current.empty()||current.peek()!=c)return false;
                    current.pop();
                    c='\n';
                    break;
            }

        }
        if(cnt!=0)return false;
        return true;
    }
    public static void main(String[] args) {
        System.out.println(isValid("()[]{}"));
    }
}
