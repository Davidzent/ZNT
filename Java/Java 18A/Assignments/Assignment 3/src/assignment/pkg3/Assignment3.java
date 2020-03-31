/**
 * Programmer Name: David Guijosa
 * Assignment Start: 1:00PM 1/9/2019
 * Assignment Completion: 1:30:PM 1/9/2019
 * Total Hours for Assignment: 30 Min
 * Comments:
 */
package assignment.pkg3;

//import
import java.util.Scanner;
     
public class Assignment3 {
       
    public static void main(String[] args) {
        // TODO code application logic here
        //initialize scaner
        Scanner input=new Scanner(System.in);
        //declare and initialize variables
        float total=0;
        float next=0;
        float prev=0.01f;
        int loop=1;
        int days=0;
        while(days<=0||days>45){
            System.out.print("For how many days will the pay double? ");
            days=input.nextInt();
            if(days<=0)System.out.println("The value should be greater than 0 and less than 45");
        }
        //output & calculations
        System.out.println("Days                              Total Pay");
        System.out.println("-------------------------------------------");
        while(loop<=days){
            total+=prev;
            next=prev*2;
            System.out.printf("%4d             $%20.2f %n",loop,prev);
            prev=next;
            loop++;
        }
        System.out.println("-------------------------------------------");
        System.out.printf("Total:           $%20.2f %n",total);
    }
    
}
