import java.util.Set;

/**
 * Created by vi34 on 28/05/16.
 */
public abstract class Symbol {
    public String name;
    abstract Set<Terminal> getFirst();
}
