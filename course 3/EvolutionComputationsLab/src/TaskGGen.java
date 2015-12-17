import com.sun.tools.javac.util.ArrayUtils;
import com.sun.tools.javac.util.Pair;

import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Created by vi34 on 15/12/15.
 */
public class TaskGGen {
    FastScanner in;
    PrintWriter out;
    Random random = new Random();
    Logger logger = Logger.getAnonymousLogger();
    final int POPULATION_SIZE = 20;
    final int ELITE_SIZE = 10;
    final int MUTATE_FREE_SIZE = 0;
    // p = 1 / ...
    final int PROB_MUTATE_START = 1;    // Disabled now
    final int PROB_MUTATE_TRANS = 4;
    final int PROB_MUTATE_HARD = 18;
    final int OUT_GENERATION = 1000;
    int foodCount = 0;
    int mutations;

    public class State implements Cloneable{
        int [] transition;
        int [] out;
        public State(int[] transition, int[] out) {
            this.transition = transition;
            this.out = out;
        }

        public Object clone() {
            Object res = null;
            try {
                res = super.clone();
                ((State)res).transition = Arrays.copyOf(transition, transition.length);
                ((State)res).out = Arrays.copyOf(out, out.length);
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }

            return res;
        }

    }

    class Automaton {
        int stateNum;
        int startState;
        State[] states;
        int fitness;

        Automaton(int statesNum) {
            this.stateNum = statesNum;
            states = new State[statesNum];
        }

        Automaton(Automaton other) {
            this.stateNum = other.stateNum;
            this.states = new State[stateNum];
            for (int i = 0; i < stateNum; ++i) {
                states[i] = (State) other.states[i].clone();
            }
            //this.states = other.states.clone();
            //this.states = Arrays.copyOf(other.states, stateNum);
            this.startState = other.startState;
            this.fitness = other.fitness;
        }

        public Automaton mutate() {
            int mutateStart = random.nextInt(PROB_MUTATE_START);
            int mutateTrans = random.nextInt(PROB_MUTATE_TRANS);
            int mutateHard = random.nextInt(PROB_MUTATE_HARD);
            if (mutateStart != 1 && mutateTrans != 1 && mutateHard != 1) {
                return this;
            }

            Automaton mutant = new Automaton(this);
            if (mutateStart == 10) {
                mutant.startState = random.nextInt(mutant.stateNum);
            }
            if (mutateTrans == 1) {
                int state = random.nextInt(mutant.stateNum);
                int ind = random.nextInt(2);
                mutant.states[state].out[ind] = random.nextInt(3);
                mutant.states[state].transition[ind] = random.nextInt(mutant.stateNum);
            }
            if (mutateHard == 1) {
                mutations++;
                int stateC = random.nextInt(mutant.stateNum);
                stateC = (stateC < 5) ? 5 : stateC;
                for (int i = 0; i < stateC; i++) {
                    int state = random.nextInt(mutant.stateNum);
                    mutant.states[state].out[0] = random.nextInt(3);
                    mutant.states[state].transition[0] = random.nextInt(mutant.stateNum);
                    mutant.states[state].out[1] = random.nextInt(3);
                    mutant.states[state].transition[1] = random.nextInt(mutant.stateNum);
                }
            }

            return mutant;
        }

        void print() {
            for (State state : states) {
                out.print((state.transition[0] + 1) + " " + (state.transition[1] + 1) + " ");
                out.println(translateOut(state.out[0]) + " " + translateOut(state.out[1]));
            }
        }

        private Character translateOut(int o) {
            switch (o) {
                case 0: return 'L';
                case 1: return 'R';
                case 2: return 'M';
            }
            return 0;
        }

    }

    private Pair<Automaton, Automaton> cross(Automaton first, Automaton second) {
        Automaton res1 = new Automaton(first);
        Automaton res2 = new Automaton(second);
        if (random.nextBoolean()) {
            res1.startState = second.startState;
            res2.startState = first.startState;
        }

        for (int i = 0; i < res1.stateNum; ++i) {
            int p00 = res1.states[i].transition[0];
            int p01 = res1.states[i].transition[1];
            int p10 = res2.states[i].transition[0];
            int p11 = res2.states[i].transition[1];
            int a00 = res1.states[i].out[0];
            int a01 = res1.states[i].out[1];
            int a10 = res2.states[i].out[0];
            int a11 = res2.states[i].out[1];
            int r = random.nextInt(4);
            switch (r) {
                case 0:
                    res1.states[i].transition[0] = p10;
                    res2.states[i].transition[0] = p00;
                    res1.states[i].out[0] = a10;
                    res2.states[i].out[0] = a00;
                    break;
                case 1:
                    res1.states[i].transition[1] = p11;
                    res2.states[i].transition[1] = p01;
                    res1.states[i].out[1] = a11;
                    res2.states[i].out[1] = a01;
                    break;
                case 2:
                    res1.states[i].transition[0] = p10;
                    res2.states[i].transition[0] = p00;
                    res1.states[i].transition[1] = p11;
                    res2.states[i].transition[1] = p01;
                    res1.states[i].out[0] = a10;
                    res2.states[i].out[0] = a00;
                    res1.states[i].out[1] = a11;
                    res2.states[i].out[1] = a01;
                    break;
                case 3: break;
            }
        }

        return new Pair<>(res1, res2);
    }

    public void solve() throws IOException {
        int m = in.nextInt();
        int n = in.nextInt();
        int k = in.nextInt();
        boolean[][] field = new boolean[m][m];
        for (int i = 0; i < m; ++i) {
            String line = in.next();
            for (int j = 0; j < m; ++j) {
                if (line.charAt(j) == '*') {
                    field[i][j] = true;
                    foodCount++;
                }
            }
        }

        Automaton[] population = new Automaton[POPULATION_SIZE];
        for (int i = 0; i < population.length; i++) {
            population[i] = genAutomaton(n);
        }

        Automaton result;
        long generation = 0;
        int[] pFitness = new int[POPULATION_SIZE];
        long[] partSum = new long[POPULATION_SIZE];
        gen: while (true) {
            generation++;

            if ((generation % OUT_GENERATION) == 0) System.err.print("Generation: " + generation + " ");
            Automaton[] nextPopulation = new Automaton[POPULATION_SIZE];
            for (int i = 0; i < population.length; ++i) {
                boolean[][] fieldCopy = new boolean[m][m];
                for (int j = 0; j < field.length; ++j) {
                    fieldCopy[j] = Arrays.copyOf(field[j], m);
                }
                pFitness[i] = fitness(population[i], fieldCopy, k);
                partSum[i] = pFitness[i];
                population[i].fitness = pFitness[i];
                if (i > 0) partSum[i] += partSum[i - 1];
                if (pFitness[i] == foodCount + field.length*2) {
                    result = population[i];
                    break gen;
                }
            }
            long sum = partSum[partSum.length - 1];
            if (sum == 0) {
                for (int i = 0; i < population.length; ++i) {
                    population[i] = genAutomaton(n);
                }
                if (generation % OUT_GENERATION == 0) System.err.println("BEST: 0 of " + (foodCount + field.length*2 )+ "AVG: 0");
                continue;
            }
            for (int i = 0; i < POPULATION_SIZE; ++i) {
                long rnd = Math.abs(random.nextLong()) % sum;
                int ind = Arrays.binarySearch(partSum, rnd);
                if (ind < 0) {
                    ind = -(ind + 1);
                }
                nextPopulation[i] = population[ind];
            }
            Arrays.sort(nextPopulation, (Automaton a, Automaton b) -> b.fitness - a.fitness);
            if (generation % OUT_GENERATION == 0) System.err.println("BEST: " + nextPopulation[0].fitness +
                    " of " + (foodCount + field.length*2 ) + " AVG: " + sum/POPULATION_SIZE + " MUT: " + mutations);
            for (int i = ELITE_SIZE; i < POPULATION_SIZE; i += 2) {
                Pair<Automaton, Automaton> cross = cross(nextPopulation[i - ELITE_SIZE], nextPopulation[i + 1 - ELITE_SIZE]);
                nextPopulation[i] = cross.fst;
                nextPopulation[i + 1] = cross.snd;
            }
            mutations = 0;
            for (int i = MUTATE_FREE_SIZE; i < POPULATION_SIZE; ++i) {
                nextPopulation[i] = nextPopulation[i].mutate();
            }
            population = nextPopulation;
        }
        result.print();

    }

    enum Orientation {
        Left(0),
        Up(1),
        Right(2),
        Bottom(3);

        private final int dir;

        Orientation(int i) {
            dir = i;
        }

        Orientation next() {
            return Orientation.values()[(dir + 1) % 4];
        }

        Orientation prev() {
            return Orientation.values()[(4 + dir - 1) % 4];
        }
    }

    private int fitness (Automaton automaton, boolean[][] field, int k) {
        int eaten = 0;
        int curState = automaton.startState;
        int antX = 0;
        int antY = 0;
        Orientation orientation = Orientation.Right;
        for (int i = 0; i < k; ++i) {
            int pX = antX;
            int pY = antY;
            if (orientation == Orientation.Right) {
                pX = (pX + 1) % (field.length);
            } else if (orientation == Orientation.Bottom) {
                pY = (pY + 1) % (field.length);
            } else if (orientation == Orientation.Left) {
                pX = (field.length + pX - 1) % (field.length);
            } else if (orientation == Orientation.Up) {
                pY = (field.length + pY - 1) % (field.length);
            }
            int haveFood = 0;
            if (field[pX][pY]) {
                haveFood = 1;
            }
            int action = automaton.states[curState].out[haveFood];
            curState = automaton.states[curState].transition[haveFood];
            switch (action) {
                case 0: orientation = orientation.prev(); break;
                case 1: orientation = orientation.next(); break;
                case 2:
                    antX = pX;
                    antY = pY;
                    if (field[antX][antY]) {
                        field[antX][antY] = false;
                        eaten++;
                    }
            }
        }
        if (eaten != foodCount) {
            for (int i = 0; i < field.length; ++i) {
                for (int j = 0; j < field.length; ++j) {
                    if (field[i][j]) {
                        return eaten - (Math.abs(antX - i) + Math.abs(antY - j)) + field.length*2;
                    }
                }
            }
        }
        return eaten + field.length*2;
    }

    public Automaton genAutomaton(int n) {
        Automaton automaton = new Automaton(n);
        automaton.startState = random.nextInt(n);
        for (int i = 0; i < automaton.states.length; ++i) {
            automaton.states[i] = new State(new int[]{random.nextInt(n),random.nextInt(n)},
                    new int[]{random.nextInt(3),random.nextInt(3)});
        }
        return automaton;
    }


    public void run() {
        try {
            in = new FastScanner(new File("antTest4.in"));
            out = new PrintWriter(new File("antTest4.out"));

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

        double nextDouble() {return Double.parseDouble(next());}
    }

    public static void main(String[] arg) {
        new TaskGGen().run();
    }
}
