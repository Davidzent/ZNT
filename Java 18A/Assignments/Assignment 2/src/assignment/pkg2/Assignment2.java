/**
 * Programmer Name: David Guijosa
 * Assignment Start: 11:00aM 1/9/2019
 * Assignment Completion: 11:15:AM 1/9/2019
 * Total Hours for Assignment: 15 min
 * Comments:
 */

package assignment.pkg2;
//imports 
import java.util.Scanner;
public class Assignment2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        //initialize scaner
        Scanner input=new Scanner(System.in);
        //initialize values
        int num1,num2,num3,num4; //input values
        int max,min;             //maximum and minimum
        //declare variables
        max=0;
        min=0;
        System.out.print("Enter number 1 :");
        num1=input.nextInt();
        System.out.print("Enter number 2 :");
        num2=input.nextInt();
        System.out.print("Enter number 3 :");
        num3=input.nextInt();
        System.out.print("Enter number 4 :");
        num4=input.nextInt();
        //find max and min
        if(num1>=num2&&num1>=num3&&num1>=num4)max=num1;
        else if(num2>=num3&&num2>=num4&&num2>=num1)max=num2;
        else if(num2>=num4&&num3>=num1&&num3>=num2)max=num3;
        else if(num3>=num1&&num4>=num2&&num4>=num3)max=num4;
        if(num1<=num2&&num1<=num3&&num1<=num4)min=num1;
        else if(num2<=num3&&num2<=num4&&num2<=num1)min=num2;
        else if(num2<=num4&&num3<=num1&&num3<=num2)min=num3;
        else if(num3<=num1&&num4<=num2&&num4<=num3)min=num4;
        
        System.out.printf("Your entered number 1 %d%n",num1);
        System.out.printf("Your entered number 2 %d%n",num2);
        System.out.printf("Your entered number 3 %d%n",num3);
        System.out.printf("Your entered number 4 %d%n",num4);
        System.out.printf("your maximum number is %d%n",max);
        System.out.printf("Yout lowest number is %d%n",min);
    }
    
}
