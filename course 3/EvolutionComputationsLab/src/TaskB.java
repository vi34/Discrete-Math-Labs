import java.io.*;
import java.util.BitSet;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

/**
 * Created by vi34 on 16/11/15.
 */
public class TaskB {
    FastScanner in;
    PrintWriter out;

    public void solve() throws IOException {
        int m = in.nextInt();
        int n = in.nextInt();
        Set<String> s = new HashSet<>();
        for (int i = 0; i < m; ++i) {
            s.add(in.next());
        }
        String t = in.next();
        if (checkOnePointCrossover(s,t, n)) {
            out.println("YES");
            out.println("YES");
        } else {
            out.println("NO");
            out.println(checkTwoPointCrossover(s,t,n) ? "YES" : "NO");
        }
        out.println(checkUniformCrossover(s, t, n) ? "YES" : "NO");
    }

    boolean checkUniformCrossover(Set<String> s, String t, int n) {
        for (String left : s) {
            for (String right : s) {
                boolean find = true;
                for (int i = 0; i < t.length(); ++i) {
                    if (t.charAt(i) != left.charAt(i) && t.charAt(i) != right.charAt(i))
                    {
                        find = false;
                        break;
                    }
                }
                if (find) {
                    return true;
                }
             }
        }
        return false;
    }

    boolean checkTwoPointCrossover(Set<String> s, String t, int n) {
        for (String left : s) {
            if (left.charAt(0) != t.charAt(0))
                continue;
            int point = 0;
            while (point < n && left.charAt(point) == t.charAt(point)) {
                point++;
            }
            int point2 = n;
            while (point2 >= point && left.charAt(point2 - 1) == t.charAt(point2 - 1) ) {
                point2--;
            }
            final boolean[] find = {false};

            final int finalPoint = point;
            final int finalPoint1 = point2;
            s.forEach((String right) -> {
                if (right.substring(finalPoint, finalPoint1).equals(t.substring(finalPoint, finalPoint1))) {
                    find[0] = true;
                }
            });
            if (find[0]) return true;
        }
        return false;
    }

    boolean checkOnePointCrossover(Set<String> s, String t, int n) {
        for (String left : s) {
            if (left.charAt(0) != t.charAt(0))
                continue;
            int point = 0;
            while (point < n && left.charAt(point) == t.charAt(point)) {
                point++;
            }
            final boolean[] find = {false};

            final int finalPoint = point;
            s.forEach((String right) -> {
                if (right.substring(finalPoint).equals(t.substring(finalPoint))) {
                    find[0] = true;
                }
            });
            if (find[0]) return true;
        }
        return false;
    }


    public void run() {
        try {
            in = new FastScanner(new File("crossover.in"));
            out = new PrintWriter(new File("crossover.out"));

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
        new TaskB().run();
    }
}
