/**
 * Author: Guijosa, David
 * January 2, 2019 4:00 PM
 * Purpose:
 */
package javaapplication2;
//libraries
import java.util.Scanner;
//Class
public class JavaApplication2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner input=new Scanner(System.in);
        System.out.print("Enter an interger: ");
        int number1 = input.nextInt();
        
        System.out.print("Enter another interger: ");
        int number2 = input.nextInt();
        
        int sum=number1+number2;
        
        System.out.printf("Sum is %d%n", sum);
    }
    
}
