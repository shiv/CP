import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

class Bunker_and_Clients {

    static int countSetBits(long number) {
        int count = 0;
        while (number > 0) {
            count += number&1L;
            number>>=1L;
        }
        return count;
    }

    // Complete the banker_and_client function below.
    static int bankerAndClient(int c, int b, int[][] time) {

        int inf = (int)1e9 + 7;

        int[][] times = new int[b][c + 1];
        for (int i = 0; i < b; i++) {
            for (int j = 1; j < c + 1; j++) {
                times[i][j] = time[i][j - 1];
                times[i][j] += times[i][j - 1];
            }
        }

        int res = inf;
        int[][] dp = new int[1 << b][c + 1];
        for (int[] row: dp) {
            Arrays.fill(row, inf);
        }


        for (int i = 1; i < 1 << b; i++) {

            if (countSetBits(i) == 1) {
                for (int j = 0; ; j++) {
                    if ((i >> j & 1) != 0) {
                        for (int k = 0; k < c + 1; k++) {
                            dp[i][k] = times[j][k];
                        }
                        break;
                    }
                }
            }

            for (int j = 0; j < b; j++) {
                if ((i & (1 << j)) == 0) {
                    for (int k = 1; k <= c; k++) {
                        for (int l = k; l <= c; l++) {
                            int temp = dp[i][k - 1];
                            temp -= times[j][k - 1];
                            temp += times[j][l];
                            int idx = i | 1 << j;
                            dp[idx][l] = Math.min(dp[idx][l], temp);
                        }
                    }
                }
            }

            res = Math.min(res, dp[i][c]);
        }

        return res;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {

        Scanner in = new Scanner(System.in);
        int c = in.nextInt();
        int b = in.nextInt();
        int answer;
            int[][] M = new int[b][c];
            for(int i=0; i < b; i++)
                for(int j=0; j < c; j++)
                    M[i][j] = in.nextInt();
            answer= bankerAndClient(c,b,M);
        // Do not remove below line
        System.out.println(answer);
        // Do not print anything after this line

        scanner.close();
    }
}
