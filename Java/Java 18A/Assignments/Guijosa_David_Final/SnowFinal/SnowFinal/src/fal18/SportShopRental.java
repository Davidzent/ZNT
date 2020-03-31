/* Programmer Name: David guijosa
 * Assignment Start: 2/3/2019 1:00pm
 * Assignment Completion: 2/5/2019 2:12pm
 * Total Hours for Assignment: 4 hours
 * Comments:
 */
package fal18;

// 25 pts total (15 points for correct implementation (3 pts per section below), 10 points code passes all unit test).
// Refer to the UML class diagram for naming of all methods in this class: SportShopRentalUML.pdf

// 1. Create abstract class named SportShotRental.
abstract class SportShopRental{
// 2. a. Create private boolean member variable named newModel and initialize to false.
//    b. Create private double member variable named rentalCost and initialize to 25.0.
//    c. Create private long member variable named rentalNumber and initialize to 1.
    protected boolean newModel;
    protected double rentalCost;
    protected long rentalNumber;
    SportShopRental(){
        newModel=false;
        rentalCost=25.0f;
        rentalNumber=1;
    }
// 3. Create all getters and setters for private member variables created in step #2. Note below is specifics for data validation 
//    in specified setter methods below:
//    a. In setter method for setting rental cost, throw a new IllegalArgumentExcetion for
//       any rental cost that is less than or equal to zero, with the exception message: 
//       "RentalCost out of range"
//    b. In setter method for setting rental number, throw a new IllegalArgumentException for
//       any rental number that is less than 1 or greater than 999999999999, with the
//       exception message: "RentalNumber out of range"
    public boolean isNewModel(){
        return newModel;
    }
    public void setNewModel(boolean NewModel){
        this.newModel=NewModel;
    }
    public double getRentalCost(){
        return rentalCost;
    }
    public void setRentalCost(double rentalCost){
        try{
            if(rentalCost<=0) throw new Exception("RentalCost out of range");
            else this.rentalCost=rentalCost;
            }catch(Exception IllegalArgumentException){
            System.out.println(IllegalArgumentException);
        }  
    }
    public long getRentalNumber(){
        return rentalNumber;
    }
    public void setRentalNumber(long rentalNumber){
        try{
            if(rentalNumber<1||rentalNumber>999999999999L)throw new Exception("RentalNumber out of range");
            else this.rentalNumber=rentalNumber;
        }catch(Exception IllegalArgumentException){
            System.out.println(IllegalArgumentException);
        }  
    }
// 4. Create the overrided method named toString that returns a string in the format of:
//    "Rental #{1}, Cost: ${2}, New: {3}"
//    where:  {1} is the format specifier for integers,
//            {2} is the format specifier for doubles with width of 7 characters and 2 decimal places of precision,
//            {3} is the format specifier for boolean values.
    @Override
    public String toString(){
        String s=String.format("Rental #%d, Cost: $%7.2f, New: %b",rentalNumber
        ,rentalCost,newModel);
        return s;
    }
// 5. Create the abstract method lateCharge that takes no parameters and returns the late charge as a double.
    abstract double lateCharge();    
    
}



