import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * Created by vi34 on 28/05/16.
 */
public class LLChecker {
    Map<String, Symbol> bind;
    List<NonTerminal> nonTerminals;
    final Terminal EPS = new Terminal("EPS");
    final Terminal END = new Terminal("END");
    NonTerminal start;

    public LLChecker(Map<String, Symbol> bind, List<NonTerminal> nonTerminals, String start) {
        this.bind = bind;
        this.nonTerminals = nonTerminals;
        this.start = (NonTerminal) bind.get(start);

    }

    boolean isLL() {
        // TODO: delete useless symbols
        computeFirst();
        computeFollow();
        for (NonTerminal nt: nonTerminals) {
            for (List<String> r1 : nt.rules) {
                for (List<String> r2 : nt.rules){
                    if (r1 == r2)
                        continue;
                    Set<Terminal> f1 = rightFirst(r1);
                    Set<Terminal> f2 = rightFirst(r2);
                    f1.retainAll(f2);
                    if (f1.size() > 0)
                        return false;
                    if (f1.contains(EPS)) {
                        f2.retainAll(nt.follow);
                        if (f2.size() > 0)
                            return false;
                    }
                }
            }
        }
        return true;
    }

    Set<Terminal> rightFirst(List<String> rule) {
        Set<Terminal> res = new HashSet<>();
        if (rule.size() == 0) {
            res.add(EPS);
        }
        for (String s: rule) {
            Symbol symb = bind.get(s);
            res.addAll(symb.getFirst());
            if (!symb.getFirst().contains(EPS))
                break;
        }
        return res;
    }


    private void computeFirst() {
        nonTerminals.forEach(nt -> {
            nt.first = new HashSet<>();
        });
        boolean changed = true;
        while (changed) {
            changed = false;
            for (NonTerminal nt : nonTerminals) {
                for (List<String> rule: nt.rules) {
                    Set<Terminal> first = rightFirst(rule);
                    int sz = nt.first.size();
                    nt.first.addAll(first);
                    if (sz != nt.first.size()) {
                        changed = true;
                    }
                }
            }
        }
    }

    void computeFollow() {
        nonTerminals.forEach(nt -> {
            nt.follow = new HashSet<>();
        });

        start.follow.add(END);
        boolean changed = true;
        while (changed) {
            changed = false;
            for (NonTerminal nt : nonTerminals) {
                for (List<String> rule: nt.rules) {
                    for (int i = 0; i < rule.size(); ++i) {
                        Symbol symbol = bind.get(rule.get(i));
                        if (symbol instanceof Terminal)
                            continue;
                        NonTerminal b = (NonTerminal) symbol;
                        Set<Terminal> first;
                        if (i == rule.size() - 1) {
                            first = EPS.getFirst();
                        } else {
                            Symbol next = bind.get(rule.get(i + 1));
                            first = next.getFirst();
                        }
                        int sz = b.follow.size();
                        b.follow.addAll(first.stream().filter(t-> !t.name.equals("EPS")).collect(Collectors.toList()));
                        if (first.contains(EPS)) {
                            b.follow.addAll(nt.follow);
                        }
                        if (sz != b.follow.size()) {
                            changed = true;
                        }

                    }
                }
            }
        }


    }
}
