import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created by vi34 on 28/05/16.
 */
public class NonTerminal extends Symbol {
    private List<List<String>> rules;
    Set<Terminal> first;
    Set<Terminal> follow;
    List<Set<Terminal>> ruleFirst = new ArrayList<>();


    public void setRules(List<List<String>> rules) {
        this.rules = rules;
        rules.forEach((t) -> ruleFirst.add(new HashSet<>()));
    }

    public List<List<String>> getRules() {
        return rules;
    }

    @Override
    Set<Terminal> getFirst() {
        return first;
    }
}
