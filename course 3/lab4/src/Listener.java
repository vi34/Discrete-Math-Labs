/**
 * Created by vi34 on 25/05/16.
 */
public class Listener extends GenBaseListener {
    @Override
    public void enterName(GenParser.NameContext ctx) {
        System.out.println("IN NAME!");
    }
}
