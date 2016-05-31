package vi34.lib;

import java.io.InputStream;
import java.text.ParseException;

/**
 * Created by vi34 on 31/05/16.
 */
public interface Parser {
     Tree parse(InputStream is) throws ParseException;
}
