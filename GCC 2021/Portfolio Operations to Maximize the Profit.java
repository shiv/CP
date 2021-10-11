import java.util.*;
import java.io.*;

class Solution {
    static FastScanner sc = new FastScanner();
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String [] args) throws IOException {

        int n = sc.nextInt();
        int m = sc.nextInt();
        int mx = sc.nextInt();
        int[] x = new int[n + 1];
        int[] y = new int[m + 1];
        for (int i = 1; i <= n; i++) {
            x[i] = sc.nextInt();
        }
        for (int i = 1; i <= m; i++) {
            y[i] = sc.nextInt();
        }

        int res = 0;
        int i = 1, j = 0, sum = 0;
        while (i <= n) {
            sum += x[i];
            while (sum > mx && j >= 1) {
                sum -= y[j];
                j -= 1;
            }
            while (j < m && sum + y[j + 1] <= mx) {
                sum += y[j + 1];
                j += 1;
            }
            if (sum > mx) {
                break;
            }
            res = Math.max(res, i + j);
            i += 1;
        }
        out.println(res);
        out.flush();
    }

    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {
            while (!st.hasMoreTokens())
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}