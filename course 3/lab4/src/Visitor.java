import java.util.HashSet;
import java.util.Set;

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
        result.addNonTerm(nonTerminal);
        return null;
    }
}
