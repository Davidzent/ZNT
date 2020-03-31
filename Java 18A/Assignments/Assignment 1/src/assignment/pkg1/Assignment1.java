/**
 * Programmer Name: DAvid Guijosa
 * Assignment Start: 4:00PM 1/2/2019
 * Assignment Completion: 10:45:AM 1/3/2019
 * Total Hours for Assignment: 1 hour
 * Comments:
 */
package assignment.pkg1;
//imports
import java.util.Scanner;
public class Assignment1 {

    public static void main(String[] args) {
        // TODO code application logic here
        //initialize scaner
        Scanner input=new Scanner(System.in);
        //variables
        float tax=0.0675f;        //sales tax percent
        float cntytx=0.0310f;     //county tax percent
        float ttslstx=0.0985f;    //total sales tax percernt
        float amount,
                prdsls,stttax,cntytax,tottax; //variable for each type of tax
        int year;
        String mnth;
        //input
        System.out.print("Enter the month name and the year: ");
        mnth=input.next();
        year=input.nextInt();
        System.out.print("Enter the amount collected in sales with tax: ");
        amount=input.nextFloat();
        //functions
        prdsls=amount/1.0985f; //sales
        cntytax=cntytx*prdsls; //county sales tax
        stttax=tax*prdsls;     //satate sales tax
        tottax=stttax+cntytax; //total sales tax
        //output
        System.out.printf("Month: %s %d %n", mnth,year);
        System.out.println("---------------------------");
        System.out.printf("Total Collected:  %,.2f%n", amount);
        System.out.printf("Sales:            %,.2f%n", prdsls);
        System.out.printf("County Sales Tax: %,.2f%n", cntytax);
        System.out.printf("Satate sale tax:  %,.2f%n", stttax);
        System.out.printf("Total Sales Tax:  %,.2f%n", tottax);
                
    }
    
}
