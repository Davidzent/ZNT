package hard;
import java.util.Scanner;

public class app {

    public static boolean isSpecial(String text) {
        String tempText = alterText(text);
        return text.equals(tempText);
      }
      
      public static String alterText(String inputText) {
        if(inputText == null || inputText.isEmpty()) {
          return inputText;
        }
        String a = inputText.charAt(inputText.length() - 1) +
        alterText(inputText.substring(0, inputText.length() - 1));;
        return a;
      }
    public static void main(String[] args){
        String a="aaabbb";
        boolean test = isSpecial(a);
        a=a;
    }

    
      
      
}