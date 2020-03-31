/* Programmer Name: David guijosa
 * Assignment Start: 1/29/2019 12:16pm
 * Assignment Completion:
 * Total Hours for Assignment:
 * Comments:
 */
package guijosa_david_trafficsignal;

public enum TrafficSignal {
    //declare constants of enum type
    RED(120,"seconds"),
    GREEN(120,"seconds"),
    YELLOW(20,"seconds"),
    WALK(60,"seconds"),
    DONT_WALK(50,"seconds");
    //intance fields
    private final int time;
    private final String term;
    //enum constructor
    TrafficSignal(int time, String term){
        this.time=time;
        this.term=term;
    }
    //accessor for field title
    public String getTerm(){
        return term;
    }
    public int getTime(){
        return time;
    }
}
