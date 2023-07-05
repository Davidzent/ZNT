package medium;

import java.util.HashMap;
import java.util.Map;

public class LongestPalindromicSubstring {
    static int start = 0;
    static int len = 0;

    public static String longestPalindrome(String s) {
        int[] ans = RecLongestPalindrome(s, s.length() / 2, 0, null);
        return s.substring(ans[1], ans[0] + ans[1]);
    }

    public static int[] RecLongestPalindrome(String s, int center, int direction, int[] max) {
        int[] ans = max;
        int[] temp = null;
        int left = center - 1;
        int right = center + 1;
        int pLeft;
        int pRight;

        while (left >= 0 && s.charAt(left) == s.charAt(center))left--;
        while (right < s.length() && s.charAt(right) == s.charAt(center))right++;
        
        pLeft = left;
        pRight = right;

        while ((pLeft >= 0 && pRight < s.length()) && s.charAt(pLeft) == s.charAt(pRight)) {
            pLeft--;
            pRight++;
        }

        if (ans == null)ans = new int[2];
        if (pRight - pLeft - 1 > ans[0]) {
            ans[0] = pRight - pLeft - 1;
            ans[1] = pLeft + 1;
        }
        if (direction != 1 && 2 * (left) > ans[0]) {
            temp = RecLongestPalindrome(s, left, -1, ans);
            if (temp[0] > ans[0])
                ans = temp;
        }
        if (direction != -1 && 2 * (s.length() - right) > ans[0]) {
            temp = RecLongestPalindrome(s, right, 1, ans);
            if (temp[0] > ans[0])
                ans = temp;
        }

        return ans;
    }

    public static void main(String[] args) {
        System.out.println(longestPalindrome("babad"));
    }
}
