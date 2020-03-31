/**
 * Programmer Name: David Guijosa
 * Assignment Start: 6:07PM 1/18/2019
 * Assignment Completion: 6:50:PM 1/18/2019
 * Total Hours for Assignment: 50 Min
 * Comments:
 */

package guijosa_david_perfectnumbers;

//import
import java.util.Scanner;

public class Guijosa_David_PerfectNumbers {

    public static void main(String[] args) {
        // TODO code application logic here\
        //scanner
        Scanner input=new Scanner(System.in);
        //declare and initialize variables
        int num=0;
        String factors;
        while(num<2||num>100000){
        System.out.print("Enter the largest number (between 2 and 100000)"
                + " that you want to display : ");
        num=input.nextInt();}
        //find factors for each number
        for(int i=2;i<num;i++){
            factors=null;
            factors=isPerfect(i);
            if(factors!=null){
                System.out.printf("%d is Perfect %n    "
                        + "    Factors:%s%n",i,factors);
            }
        }
    }
    public static String isPerfect(int number){
        int sum=0;
        String factors=" "; 
        for(int i=1;i<number;i++){
            if(number%i==0){sum=sum+i;
            factors+=i+" ";
            }
        }
        if(sum==number)return factors;
        return null;
    }
}

