import java.io.*;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Created by vi34 on 17/11/15.
 */
public class TaskC {
    FastScanner in;
    PrintWriter out;

    public class Tree {
        int n;
        Node[] nodes;
        Node root;
        private int k;
        Tree(int n) {
            nodes = new Node[n];
            Arrays.setAll(nodes, (int i) -> new Node());
            root = nodes[0];
            k = 5;
        }

        class Node {
            Node left;
            Node right;
            Node parent;
            int predicate;
            int num;
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        Tree tree = new Tree(n);
        for (int i = 0; i < n; ++i) {
            String type = in.next();
            if (type.equals("leaf")) {
                tree.nodes[i].predicate = in.nextInt();
            } else {
                tree.nodes[i].predicate = in.nextInt();
                tree.nodes[i].left = tree.nodes[in.nextInt() - 1];
                tree.nodes[i].left.parent = tree.nodes[i];
                tree.nodes[i].right = tree.nodes[in.nextInt() - 1];
                tree.nodes[i].right.parent = tree.nodes[i];
             }
        }

        predicates = new HashMap<>();
        dfs(tree.root);

        printTree(tree);


    }

    Map<Integer, Boolean> predicates;

    void dfs(Tree.Node node) {
        if (node.left != null) {
            if (predicates.containsKey(node.predicate)) {
                boolean iAmLeft = (node.parent.left == node);
                if (!predicates.get(node.predicate)) {
                    if (iAmLeft) {
                        node.parent.left = node.left;
                        node.left.parent = node.parent;
                        dfs(node.left);
                    } else {
                        node.parent.right = node.left;
                        node.left.parent = node.parent;
                        dfs(node.left);
                    }
                } else {
                    if (iAmLeft) {
                        node.parent.left = node.right;
                        node.right.parent = node.parent;
                        dfs(node.right);
                    } else {
                        node.parent.right = node.right;
                        node.right.parent = node.parent;
                        dfs(node.right);
                    }
                }
            } else {
                predicates.put(node.predicate, false);
                dfs(node.left);
                predicates.put(node.predicate, true);
                dfs(node.right);
                predicates.remove(node.predicate);
            }
        }
    }

    void printTree (Tree tree) {
        LinkedList<Tree.Node> queue = new LinkedList<>();
        queue.addFirst(tree.root);
        int counter = 0;
        while (!queue.isEmpty()) {
            Tree.Node cur = queue.removeLast();
            cur.num = counter++;
            if (cur.left != null) {
                queue.addFirst(cur.left);
                queue.addFirst(cur.right);
            }
        }
        out.println(counter);
        queue.addFirst(tree.root);
        while (!queue.isEmpty()) {
            Tree.Node cur = queue.removeLast();
            if (cur.left != null) {
                out.println("choice " + (cur.predicate) + " " + (cur.left.num + 1) + " " + (cur.right.num + 1));
                queue.addFirst(cur.left);
                queue.addFirst(cur.right);
            } else {
                out.println("leaf " + (cur.predicate));
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("trees.in"));
            out = new PrintWriter(new File("trees.out"));
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
        new TaskC().run();
    }
}
