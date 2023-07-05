public class RomanToInt {
    public static int romanToInt(String s) {
        // int sum=0;
        // char prev='\n';
        // for(int i=0;i<s.length();i++){
        //     if(i>0)prev=s.charAt(i-1);
        //     switch (s.charAt(i)){
        //         case 'M':
        //             if(prev=='C')sum+=800;  //-100 for previously added and current -100
        //             else sum+=1000;
        //             break;
        //         case 'D':
        //             if(prev=='C')sum+=300; //-100 for previously added and current -100
        //             else sum+=500;
        //             break;
        //         case 'C':
        //             if(prev=='X')sum+=80; //-10 for previously added and current -10
        //             else sum+=100;
        //             break;
        //         case 'L':
        //             if(prev=='X')sum+=30; //-10 for previously added and current -10
        //             else sum+=50;
        //             break;
        //         case 'X':
        //             if(prev=='I')sum+=8; //-1 for previously added and current -1
        //             else sum+=10;
        //             break;
        //         case 'V':
        //             if(prev=='I')sum+=3; //-1 for previously added and current -1
        //             else sum+=5;
        //             break;
        //         case 'I':sum+=1;break;
        //     }
        // }
        
        // return sum;

        int sum = 0;
        int number = 0;
        int prev = 0;

        for (int j = s.length() - 1; j >= 0; j--) {
            switch (s.charAt(j)) {
                case 'M' : number = 1000;break;
                case 'D' : number = 500;break;
                case 'C' : number = 100;break;
                case 'L' : number = 50;break;
                case 'X' : number = 10;break;
                case 'V' : number = 5;break;
                case 'I' : number = 1;break;
            }
            if (number < prev) {
                sum -= number;
            } else {
                sum += number;
            }
            prev = number;
        }
        return sum;
    }
    public static void main(String[] args) {
        System.out.println(romanToInt("MMMCMXCIX"));
    }
}
