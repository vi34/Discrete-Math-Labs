import com.sun.org.apache.xerces.internal.impl.xpath.regex.Match;

import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by vi34 on 31/05/16.
 */
public class Translation extends Symbol {
    Set<Terminal> first = new HashSet<>();
    String actions;

    Translation() {
        first.add(new Terminal("EPS"));
    }

    void setActions(String a) {
        actions = a.replace("$this", "node");
        Pattern p = Pattern.compile("[$](.+?)\\.");
        Matcher m = p.matcher(actions);
        StringBuffer s = new StringBuffer();
        while (m.find())
            m.appendReplacement(s, m.group(1).toLowerCase() + "T.");
        m.appendTail(s);
        actions = s.toString();
    }

    @Override
    Set<Terminal> getFirst() {
        return first;
    }
}
