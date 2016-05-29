import java.util.List;
import java.util.Set;

/**
 * Created by vi34 on 28/05/16.
 */
public class NonTerminal extends Symbol {
    List<List<String>> rules;
    Set<Terminal> first;
    Set<Terminal> follow;


    @Override
    Set<Terminal> getFirst() {
        return first;
    }
}
