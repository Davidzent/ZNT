/* Programmer Name: David Guijosa
 * Assignment Start: 1:30
 * Assignment Completion: 2:30
 * Total Hours for Assignment: 1 hour
 * Comments:
 */
package guijosa_david_monthdays;
import java.util.Scanner;
public class Guijosa_David_MonthDays {
    public static void main(String[] args) {
        // TODO code application logic here
        //Scanner
        Scanner input=new Scanner(System.in);
        //variables here
        int month=0;
        int year=0;
        MonthDays Month=new MonthDays(0,0);
        //Ask for values
        System.out.print("Enter the month (1=January, 2=February,.."
                + "., 12=December): ");
        month=input.nextInt();
        System.out.println("Enter the year : ");
        year=input.nextInt();
        //Set values to class
        Month.setyr(year);
        Month.setmnth(month);
        //Output
        System.out.printf("%d/%d %4s %2d %4s%n",Month.gtmonth(),Month.gtyear(),
                "has",Month.getNumberOfDays(),"Days");
    }
    
}
