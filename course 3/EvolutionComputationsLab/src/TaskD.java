import java.awt.*;
import java.io.*;
import java.time.LocalDate;
import java.util.*;
import java.util.concurrent.Executor;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadPoolExecutor;

/**
 * Created by vi34 on 23/11/15.
 */
public class TaskD  {
    FastScanner in;
    PrintWriter out;

    class Vertex {
        Vertex edges[] = new Vertex[2];
        Character out;
        int ind;
    }

    Set<Integer> answer;
    BitSet memorize;
    BitSet visited;
    int m;
    public void solve() throws IOException {
        answer = new TreeSet<>();
        m = in.nextInt();
        m++;
        int n = in.nextInt();

        memorize = new BitSet(n * m);
        visited = new BitSet(n * m);

        Vertex[] automaton = new Vertex[n];
        Arrays.setAll(automaton, (int i) -> new Vertex());
        for (int i = 0; i < n; ++i) {
            int t0 = in.nextInt();
            int t1 = in.nextInt();
            Character b = in.next().charAt(0);
            automaton[i].edges[0] = automaton[t0 - 1];
            automaton[i].edges[1] = automaton[t1 - 1];
            automaton[i].out = b;
            automaton[i].ind = i + 1;
        }
        z = in.next();
        for (Vertex vertex : automaton) {
            if (walk(vertex, 0)) {
                answer.add(vertex.ind);
            }
        }
        out.print(answer.size() + " ");
        for (Integer i : answer) {
            out.print(i + " ");
        }
    }
    String z;

    boolean walk(Vertex v, int ind) {
        if (visited.get((v.ind - 1)*m + ind)) {
            return memorize.get((v.ind - 1)*m + (ind));
        }
        visited.set((v.ind - 1)*m + ind);
        if (ind == m - 1) {
            memorize.set((v.ind - 1)*m + ind);
            return true;
        }
        for (Vertex neighbor : v.edges) {
            if (neighbor.out == z.charAt(ind)) {
                if (walk(neighbor, ind + 1)) {
                    memorize.set((v.ind - 1)*m + ind);
                    return true;
                }
            }
        }
        return false;
    }

    public void run() {
        try {
            in = new FastScanner(new File("start.in"));
            out = new PrintWriter(new File("start.out"));

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
        new TaskD().run();
    }
}
