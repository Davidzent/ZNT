/* Programmer Name: David guijosa
 * Assignment Start: 1/29/2019 12:16pm
 * Assignment Completion: 1/29/2019 12:40pm
 * Total Hours for Assignment: 20 min
 * Comments:
 */
package guijosa_david_trafficsignal;

public class Guijosa_David_TrafficSignal{    
    public static void main(String[] args){
        // TODO code application logic here
        System.out.println("All Teffic Signals");
        //print all traffic signals
        for(TrafficSignal signal: TrafficSignal.values()){
            System.out.printf("%-12s%-5d%-10s%n",signal,signal.getTime()
                    ,signal.getTerm()); 
        }
    }
    
}
