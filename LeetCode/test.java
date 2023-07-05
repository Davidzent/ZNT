import java.awt.AWTException;
import java.awt.Robot;
import java.util.HashMap;
import java.util.Map;

public class test {
    public static void main(String[] args) throws AWTException {
        String s=" contain elements that describe objects in the world, such as computers, folders, objects, managed resources, and even people. These elements have names and, like the fields in a database, changing values.";
        char c='a';
        Map<Character, Integer> map = new HashMap<Character, Integer>();
        
        for(int i=0;i<26;i++){
            map.put((char)((int)c+i), 65+i);
        }

        map.put(' ', 32);
        map.put('\t', 16);
        map.put('\'',192);
        map.put('?',191);
        map.put('!',49);
        map.put('.',110);
        map.put(',',108);

        Robot robot = new Robot();
        robot.delay(2000);


        for(int i=0;i<s.length();i++){ 
            robot.delay(500);
            c=s.charAt(i);
            if(c>='A'&&c<='Z'||c=='?'||c=='!')robot.keyPress(map.get('\t'));
            robot.keyPress(map.get(c));
            robot.keyRelease(map.get(c));
            if(c>='A'&&c<='Z'||c=='?'||c=='!')robot.keyRelease(map.get('\t'));

        }


        
    }
}
