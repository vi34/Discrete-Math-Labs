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
        Terminal terminal = new Terminal();
        visitChildren(ctx);
        terminal.name = ctx.LEXER_RULENAME().getText();
        terminal.ranges = ctx.ranges;
        terminal.skip = ctx.isSkipped;
        terminal.literals = ctx.literals;
        result.tokens.add(terminal);
        return null;
    }

    @Override
    public ParseResult visitLexExpr(GenParser.LexExprContext ctx) {
        return super.visitLexExpr(ctx);
    }
}
