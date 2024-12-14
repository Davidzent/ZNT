package test;
import java.util.Scanner;

public class app {
    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);

        int n;
        int[] a;
        int x;

        n = in.nextInt();
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
        x = in.nextInt();

        System.out.println(isSecure(n, a, x) ? "Seguro" : "Inseguro");

    }

    public static boolean isSecure(int n, int[] arr, int x) {
        int dif = 0;
        for (int i = 0, j = 1; i < n - 1; i++) {
            dif = Math.abs(arr[i] - arr[j]);
            if (dif > x)
                return false;
        }
        return true;
    }

}