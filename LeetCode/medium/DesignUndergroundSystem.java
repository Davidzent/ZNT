package medium;

import java.util.HashMap;
import java.util.Map;

public class DesignUndergroundSystem {

    public static void main(String[] args) {
        UndergroundSystem undergroundSystem = new UndergroundSystem();
        undergroundSystem.checkIn(45, "Leyton", 3);
        undergroundSystem.checkIn(32, "Paradise", 8);
        undergroundSystem.checkIn(27, "Leyton", 10);
        undergroundSystem.checkOut(45, "Waterloo", 15);  // Customer 45 "Leyton" -> "Waterloo" in 15-3 = 12
        undergroundSystem.checkOut(27, "Waterloo", 20);  // Customer 27 "Leyton" -> "Waterloo" in 20-10 = 10
        undergroundSystem.checkOut(32, "Cambridge", 22); // Customer 32 "Paradise" -> "Cambridge" in 22-8 = 14
        double temp = undergroundSystem.getAverageTime("Paradise", "Cambridge"); // return 
        System.out.println(temp);
        temp =undergroundSystem.getAverageTime("Leyton", "Waterloo");
        System.out.println(temp);

        undergroundSystem.checkIn(10, "Leyton", 24);
        temp = undergroundSystem.getAverageTime("Leyton", "Waterloo"); 
        System.out.println(temp);

        undergroundSystem.checkOut(10, "Waterloo", 38);  // Customer 10 "Leyton" -> "Waterloo" in 38-24 = 14
        temp = undergroundSystem.getAverageTime("Leyton", "Waterloo");    // return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12 + 14) / 3 = 12
        System.out.println(temp);
    }
}
