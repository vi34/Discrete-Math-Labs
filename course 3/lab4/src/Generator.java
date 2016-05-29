import groovy.text.SimpleTemplateEngine;
import org.antlr.v4.runtime.ANTLRFileStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.LexerInterpreter;
import org.antlr.v4.tool.Grammar;

import java.io.IOException;
import java.io.Writer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

/**
 * Created by vi34 on 25/05/16.
 */
public class Generator {
    private static SimpleTemplateEngine engine = new SimpleTemplateEngine();
    private static final String LEX_TEMPLATE = "templates/Lexer.tmpl";
    private static final String TOKENS_TEMPLATE = "templates/Token.tmpl";
    private static Path outDir;
    public static void main(String[] args) throws Exception {
        Grammar grammar = Grammar.load("src/Gen.g4");
        LexerInterpreter lexEngine = grammar.createLexerInterpreter(new ANTLRFileStream("tests/lab2"));
        CommonTokenStream tokens = new CommonTokenStream(lexEngine);
        GenParser parser = new GenParser(tokens);
        ParseResult result = new Visitor().visit(parser.file());
        generate(result);

    }

    public static void generate(ParseResult parseResult) throws Exception {
        outDir = Paths.get("result", parseResult.getName());
        if (Files.notExists(outDir)) {
            try {
                Files.createDirectory(outDir);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        LLChecker checker = new LLChecker(parseResult.rules, parseResult.nonTerms,
                parseResult.nonTerms.get(0).name);
        if (!checker.isLL()) {
            throw new Exception("Grammar is not LL");
        }

        genTokens(parseResult);
        genLexer(parseResult);

        parseResult.nonTerms.forEach(nt -> System.out.printf("%1$-4s: %2$-14s %3$14s\n", nt.name, nt.first,nt.follow));
    }

    private static void genLexer(ParseResult parseResult) {
        Path lexerFile = outDir.resolve(parseResult.getName() + "Lexer.java");
        writeTemplate(lexerFile, Paths.get(LEX_TEMPLATE), parseResult.getBindings());
    }

    private static void genTokens(ParseResult parseResult) {
        writeTemplate(outDir.resolve("Token.java"), Paths.get(TOKENS_TEMPLATE), parseResult.getBindings());
    }

    private static void writeTemplate(Path out, Path template, Map<String, Object> bindings) {
        try (Writer writer = Files.newBufferedWriter(out)){
            engine.createTemplate(template.toFile())
                    .make(bindings)
                    .writeTo(writer);
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }


}
