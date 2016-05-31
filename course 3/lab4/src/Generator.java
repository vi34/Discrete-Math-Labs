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
    private static final String PARSER_TEMPLATE = "templates/Parser.tmpl";
    private static final String TREE_TEMPLATE = "templates/Tree.tmpl";
    private static Path outDir;
    public static void main(String[] args) throws Exception {
        Grammar grammar = Grammar.load("src/Gen.g4");
        LexerInterpreter lexEngine = grammar.createLexerInterpreter(new ANTLRFileStream("tests/arith"));
        CommonTokenStream tokens = new CommonTokenStream(lexEngine);
        GenParser parser = new GenParser(tokens);
        ParseResult result = new Visitor().visit(parser.file());
        generate(result, "s");

    }

    public static void generate(ParseResult parseResult, String startRule) throws Exception {
        outDir = Paths.get("result", parseResult.getName());
        if (Files.notExists(outDir)) {
            try {
                Files.createDirectory(outDir);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        LLChecker checker = new LLChecker(parseResult.rules, parseResult.nonTerms, startRule);
        if (!checker.isLL()) {
            throw new Exception("Grammar is not LL");
        }

        parseResult.setStart(startRule);
        genFile(parseResult, parseResult.getName() + "Tree.java", TREE_TEMPLATE);
        genFile(parseResult, "Token.java", TOKENS_TEMPLATE);
        genFile(parseResult, parseResult.getName() + "Lexer.java", LEX_TEMPLATE); // TODO: more than one symbol tokens
        genFile(parseResult, parseResult.getName() + "Parser.java", PARSER_TEMPLATE); // TODO: same symbols in expression

        System.out.println(parseResult.getBindings().get("header"));
        parseResult.nonTerms.forEach(nt -> {
            System.out.printf("%1$-4s: %2$-14s %3$14s\n", nt.name, nt.first,nt.follow);
            for (int i = 0; i < nt.getRules().size(); ++i) {
                System.out.printf("%1$20s: %2$s\n", nt.getRules().get(i), nt.ruleFirst.get(i));
                System.out.printf("rINP: %1$20s: %2$s\n", nt.getrInputs().get(i), nt.ruleFirst.get(i));
            }
            System.out.println();
        });
    }

    private static void genFile(ParseResult parseResult, String name, String template) {
        Path outFile = outDir.resolve(name);
        writeTemplate(outFile, Paths.get(template), parseResult.getBindings());
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
