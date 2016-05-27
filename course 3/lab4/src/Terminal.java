import java.util.ArrayList;
import java.util.List;

/**
 * Created by vi34 on 28/05/16.
 */
public class Terminal {
    List<String> literals = new ArrayList<>();
    List<String> ranges = new ArrayList<>();
    String name;
    boolean skip;

    public List<Character> getFirstSymbols() {
        List<Character> res = new ArrayList<>();
        literals.forEach((l) -> {res.add(l.charAt(0));});
        ranges.stream().map(s -> s.substring(1, s.length() - 1)).forEach(s -> {
            for (char c = s.charAt(0); c <= s.charAt(s.length() - 1); ++c) {
                res.add(c);
            }});
        return res;
    }

}
