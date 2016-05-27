import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by vi34 on 26/05/16.
 */
public class ParseResult {
    private Map<String, Object> bindings = new HashMap<>();
    public ArrayList<Terminal> tokens = new ArrayList<>();

    public Map<String, Object> getBindings () {
        return bindings;
    }

    void setName(String name) {
        bindings.put("name", name);
    }

    String getName() {
        return (String)bindings.get("name");
    }

    ParseResult() {
        bindings.put("tokens", tokens);
    }
}
