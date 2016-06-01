grammar Gen;

file: name header? members? (definition ';')*;

name: 'grammar' IDENT ';';

header: '@header' BLOCK;
members: '@members' BLOCK;

definition: lexRule
          | parseRule;

parseRule locals [List<List<String>> alt, List<List<String>> ialt]
        @init {$alt = new ArrayList<>(); $ialt = new ArrayList<>(); }
        : PARSER_RULENAME (arg=ARGS)? ('returns' re=ARGS)? ':' parseExpr;


parseExpr locals [List<String> rules, List<String> input]
        @init {$rules = new ArrayList<>(); $input = new ArrayList<>();
        $parseRule::alt.add($rules); $parseRule::ialt.add($input);}
        : (ruleName {$rules.add($ruleName.rName); $input.add($ruleName.inp);})*
          ('|' parseExpr)?;

ruleName returns [String rName, String inp]
@init {$inp = "";}
    : LEXER_RULENAME {$rName = $LEXER_RULENAME.text;}
        (ARGS {$inp = $ARGS.text; $inp = $inp.substring(1, $inp.length()-1);})?
    | PARSER_RULENAME {$rName = $PARSER_RULENAME.text;}
        (ARGS {$inp = $ARGS.text;$inp = $inp.substring(1, $inp.length()-1);})?
    | translation {$rName = $translation.text;};

translation: BLOCK;


lexRule locals [List<String> literals, List<String> regs, boolean isSkipped]
    @init {$literals = new ArrayList<>(); $regs = new ArrayList<>();}
    : LEXER_RULENAME ':' lexExpr ('->' 'skip' {$isSkipped = true;})?;

lexExpr
       :
       | LITERAL {String s = $LITERAL.text; $lexRule::literals.add(s.substring(1, s.length() - 1));}('|' lexExpr)?
       | REG {$lexRule::regs.add($REG.text);}('|' lexExpr)?;


ARGS: '(' (.)+? ')';
BLOCK: '*/' (.)+? '/*' ;
REG: '"'(.)+?'"';
LEXER_RULENAME: [A-Z]+;
PARSER_RULENAME: [a-z][A-Za-z]*;
LITERAL: '\'' (~'\'')* '\'';
IDENT: ([a-zA-Z])([a-zA-Z0-9_])*;
WS: [ \t\r\n]+ -> skip;