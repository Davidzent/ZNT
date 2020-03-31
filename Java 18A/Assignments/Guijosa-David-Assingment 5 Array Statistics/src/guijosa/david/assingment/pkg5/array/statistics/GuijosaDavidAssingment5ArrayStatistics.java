/**
 * Programmer Name: David Guijosa
 * Assignment Start: 6:50PM 1/18/2019
 * Assignment Completion: 8:30:PM 1/18/2019
 * Total Hours for Assignment: 1 hour 30 min
 * Comments:
 */
package guijosa.david.assingment.pkg5.array.statistics;

//import
import java.util.Scanner;

public class GuijosaDavidAssingment5ArrayStatistics {
    
    public static void main(String[] args) {
        // TODO code application logic here
        //scanner
        Scanner input=new Scanner(System.in);
        //declare and initialize variables
        int size=0;
        System.out.print("How many values of type double do you want to store "
                + "in the array : ");
        size=input.nextInt();
        double[]aray=new double[size];
        double max=0,min,med=0;
        double sds=0,sdf=0;
        //input array values
        for(int i=0;i<size;i++){
            System.out.print("Enter value #"+(i+1)+" ");
            aray[i]=input.nextDouble();
        }
        min=aray[0];
        //find minumum, maximum and average
        for(double i:aray){
            if(i>max)max=i;
            if(i<min)min=i;
            med+=i;
        }
        med/=size;
        //find standard deviation
        sdf=SDP(aray,med);
        sds=SDS(aray,med);
        //output
        System.out.printf("%nThe statistics for your user entered array is:%n");
        System.out.printf("-----------------------------------------------%n");
        System.out.printf("%33s%10.3f%n","Minimum:",min);
        System.out.printf("%33s%10.3f%n","Maximum:",max);
        System.out.printf("%33s%10.3f%n","Average:",med);
        System.out.printf("%33s%10.3f%n","Standart deviation (population):",sdf);
        System.out.printf("%33s%10.3f%n","Standart deviation (Sample):",sds);
    }
    public static double SDP(double[]aray, double median){
        double sdp=0;
        for(double i:aray){
        sdp+=Math.pow(Math.abs(i-median),2);    
        }
        sdp/=aray.length;
        sdp=Math.sqrt(sdp);
        return sdp;
    }
    public static double SDS(double[]aray,double med){
        double sds=0;
        for(double i:aray){
        sds+=Math.pow(Math.abs(i-med),2);    
        }
        sds/=(aray.length-1);
        sds=Math.sqrt(sds);
        return sds;
    }
}
