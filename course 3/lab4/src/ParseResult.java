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
    List<Terminal> litTokens = new ArrayList<>();
    List<String> allLiterals = new ArrayList<>();
    List<Terminal> regTokens = new ArrayList<>();
    List<String> allRegs = new ArrayList<>();

    public Map<String, Object> getBindings () {
        initRegsAndLiterals();
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

    public void initRegsAndLiterals() {
        allLiterals = new ArrayList<>();
        litTokens = new ArrayList<>();
        regTokens = new ArrayList<>();
        allRegs = new ArrayList<>();
        tokens.forEach(t-> {
            t.literals.forEach(lit -> {
                allLiterals.add(lit);
                litTokens.add(t);
            });
            t.regs.forEach(reg -> {
                allRegs.add(reg);
                regTokens.add(t);
            });
        });

        bindings.put("allRegs", allRegs);
        bindings.put("regTokens", regTokens);
        bindings.put("allLiterals", allLiterals);
        bindings.put("litTokens", litTokens);
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
        bindings.put("header", "");
        bindings.put("members", "");
        bindings.put("litTokens", litTokens);


    }
}
