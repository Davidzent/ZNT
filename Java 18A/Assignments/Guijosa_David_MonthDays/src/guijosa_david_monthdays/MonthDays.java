
package guijosa_david_monthdays;

public class MonthDays {
    //Variables
    int year;
    int month;
    int[] days;
    //constructor
    MonthDays(int year,int month){
        this.year=year;
        this.month=month;
        days=new int[]{31,28,31,30,31,30,31,31,30,31,30,31};
    }
    //seters
    public void setyr(int year){
        try{
            if(year<0)throw new Exception();
            else this.year=year;
        }catch(Exception IllegalArgumentException){
            System.out.println("Year must be between greater than 0. "
                    + "Program terminating.");
            System.exit(0);
        }
    }
    public void setmnth(int month){
        try{
            if(month<1||month>12)throw new Exception ();
            else this.month=month;
        }catch(Exception IllegalArgumentException){
            System.out.println("Month must be between 1 and 12."
                    + " Program terminating.");
            System.exit(0);
        }
        
    }
    //getters
    public int gtmonth(){
        return month;
    }
    public int gtyear(){
        return year;
    }
    public int getNumberOfDays(){
        if(month==2){
            if(year%100==0?(year%400==0?true:false):(year%4==0?true:false)){
                System.out.println("HI");
                return (days[month-1]+1);
            }
        }
        return days[month-1];
    } 
}
