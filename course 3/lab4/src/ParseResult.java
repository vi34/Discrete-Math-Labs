import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by vi34 on 26/05/16.
 */
public class ParseResult {
    private Map<String, Object> bindings = new HashMap<>();
    public List<Terminal> tokens = new ArrayList<>();
    public List<NonTerminal> nonTerms = new ArrayList<>();
    Map<String, Symbol> rules = new HashMap<>();

    public Map<String, Object> getBindings () {
        return bindings;
    }

    void addToken(Terminal t) {
        tokens.add(t);
        rules.put(t.name, t);
    }

    void addNonTerm(NonTerminal nt) {
        nonTerms.add(nt);
        rules.put(nt.name, nt);
    }

    void setHeader(String header) {
        bindings.put("header", header);
    }

    void setMembers(String members) {
        bindings.put("members", members);
    }

    void setStart(String start) {
        bindings.put("start", start);
    }

    void setName(String name) {
        bindings.put("name", name);
    }

    String getName() {
        return (String)bindings.get("name");
    }

    ParseResult() {
        bindings.put("tokens", tokens);
        bindings.put("nonTerms", nonTerms);
        bindings.put("rules", rules);
    }
}
