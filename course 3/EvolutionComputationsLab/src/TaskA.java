import javafx.util.Pair;

import java.util.*;
import java.io.*;
import java.util.function.Function;

public class TaskA {
    FastScanner in;
    PrintWriter out;

    public void solve() throws IOException {
        int n = in.nextInt();
        int m = in.nextInt();
        double p = 1.0/n;
        double q = 1.0 - p;
        for (int i = 0; i < m; ++i) {
            String a = in.next();
            String b = in.next();
            int count = 0;
            for (int j = 0; j < n; ++j) {
                if (a.charAt(j) != b.charAt(j)) {
                    count++;
                }
            }
            out.printf("%.9f\n", Math.pow(p,count) * Math.pow(q,n - count));
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("mutation.in"));
            out = new PrintWriter(new File("mutation.out"));

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }

    public static void main(String[] arg) {
        new TaskA().run();
    }
}