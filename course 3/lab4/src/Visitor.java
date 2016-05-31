import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Created by vi34 on 25/05/16.
 */
public class Visitor extends GenBaseVisitor<ParseResult> {

    public ParseResult result = new ParseResult();


    @Override
    public ParseResult visitFile(GenParser.FileContext ctx) {
        visitChildren(ctx);
        return result;
    }

    @Override
    public ParseResult visitName(GenParser.NameContext ctx) {
        result.setName(ctx.IDENT().getText());
        return super.visitName(ctx);
    }

    @Override
    public ParseResult visitLexRule(GenParser.LexRuleContext ctx) {

        visitChildren(ctx);
        Terminal terminal = new Terminal(ctx.LEXER_RULENAME().getText());
        terminal.ranges = ctx.ranges;
        terminal.skip = ctx.isSkipped;
        terminal.literals = ctx.literals;
        result.addToken(terminal);
        return null;
    }

    @Override
    public ParseResult visitParseRule(GenParser.ParseRuleContext ctx) {
        visitChildren(ctx);
        NonTerminal nonTerminal = new NonTerminal();
        nonTerminal.name = ctx.PARSER_RULENAME().getText();
        nonTerminal.setRules(ctx.alt);
        nonTerminal.setrInputs(ctx.ialt);
        nonTerminal.setrInputs(nonTerminal.getrInputs().stream().map(l -> l.stream().map(s -> {
            s = s.replace("$my", "node");
            Pattern p = Pattern.compile("[$](.+?)\\.");
            Matcher m = p.matcher(s);
            StringBuffer sb = new StringBuffer();
            while (m.find())
                m.appendReplacement(sb, m.group(1).toLowerCase() + "T.");
            m.appendTail(sb);
            s = sb.toString();
            return s;
        }).collect(Collectors.toList())).collect(Collectors.toList()));

        String ret = "";
        if (ctx.re != null) {
            ret = ctx.re.getText();
            ret = ret.substring(2, ret.length() - 2);
            ret = ret.replaceAll(",", ";");
            ret += ";";
        }
        nonTerminal.ret = ret;

        String arg = "";
        if (ctx.arg != null) {
            arg = ctx.arg.getText();
            arg = arg.substring(1, arg.length() - 1);
        }
        nonTerminal.arg = arg;
        result.addNonTerm(nonTerminal);
        return null;
    }

    @Override
    public ParseResult visitTranslation(GenParser.TranslationContext ctx) {
        visitChildren(ctx);
        Translation translation = new Translation();
        String h = ctx.BLOCK().toString();
        h = h.substring(2, h.length() - 2);
        translation.setActions(h);
        translation.name = ctx.BLOCK().toString();
        result.rules.put(translation.name, translation);
        return null;
    }

    @Override
    public ParseResult visitHeader(GenParser.HeaderContext ctx) {
        visitChildren(ctx);
        String h = ctx.BLOCK().toString();
        result.setHeader(h.substring(2, h.length() - 2));
        return null;
    }

    @Override
    public ParseResult visitMembers(GenParser.MembersContext ctx) {
        visitChildren(ctx);
        String m = ctx.BLOCK().toString();
        result.setMembers(m.substring(2, m.length() - 2));
        return null;
    }

}
