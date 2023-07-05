package medium;

public class LongestSubstringWithoutRepeatingCharacters {
    public static int lengthOfLongestSubstring(String s) {
        int ans = 0;           
        int currentBits;        //an integer value of the current character bits
        int PrevSetBits = 0;    //an integer value of the set bits this will be treated as an array of bits of size 32 int=4 bytes= 32bits same for the previous int
        int cnt=0;

        byte[] chars=s.getBytes();  //convert the string into an array of bytes where each byte represents a character 
                                    //basically it is to get the ascii value of every character in the string

        for (byte c : chars) {
            currentBits = 1 << c;       //left shift the character ascii value to one so that every character has a unique bit in a number
                                        //an int has 4 bytes = 32 bits which means that when you left shift 1 << 97 it would be the same as 1<<1 since 97%32=1
                                        //since we only have 26 character there will not be any issue with each character using the same bit

            if ((PrevSetBits & currentBits) != 0) {    //checks if the current bit for the character is set
                if(cnt>ans)ans=cnt;
                cnt=1;              
                PrevSetBits = currentBits;             //if it is set then set the "array of bits" to the current array of bits
            } else {
                cnt++;
                PrevSetBits += currentBits;            //if it is not set then add it to the "array of bits"
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        System.out.println(lengthOfLongestSubstring(" "));
    }
}
