import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created by vi34 on 28/05/16.
 */
public class Terminal extends Symbol {
    List<String> literals = new ArrayList<>();
    List<String> ranges = new ArrayList<>();
    private Set<Terminal> first;
    boolean skip;

    Terminal(String name) {
        this.name = name;
        first = new HashSet<>();
        first.add(this);
    }

    public List<String> getSymbols() {
        List<String> res = new ArrayList<>();
        literals.forEach((l) -> {res.add(l);});
        ranges.stream().map(s -> s.substring(1, s.length() - 1)).forEach(s -> {
            for (char c = s.charAt(0); c <= s.charAt(s.length() - 1); ++c) {
                res.add("" + c);
            }});
        return res;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Terminal terminal = (Terminal) o;

        if (skip != terminal.skip) return false;
        if (literals != null ? !literals.equals(terminal.literals) : terminal.literals != null) return false;
        return ranges != null ? ranges.equals(terminal.ranges) : terminal.ranges == null;

    }

    @Override
    public int hashCode() {
        int result = literals != null ? literals.hashCode() : 0;
        result = 31 * result + (ranges != null ? ranges.hashCode() : 0);
        result = 31 * result + (skip ? 1 : 0);
        return result;
    }

    @Override
    Set<Terminal> getFirst() {
        return first;
    }

    @Override
    public String toString() {
        return name;
    }
}
