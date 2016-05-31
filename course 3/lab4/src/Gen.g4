grammar Gen;

file: name header? members? (definition ';')*;

name: 'grammar' IDENT ';';

header: '@header' BLOCK;
members: '@members' BLOCK;

definition: lexRule
          | parseRule;

parseRule locals [List<List<String>> alt, List<List<String>> ialt]
        @init {$alt = new ArrayList<>(); $ialt = new ArrayList<>(); }
        : PARSER_RULENAME (arg=ARGS)? ('returns' re=BLOCK)? ':' parseExpr;


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


lexRule locals [List<String> literals, List<String> ranges, boolean isSkipped]
    @init {$literals = new ArrayList<>(); $ranges = new ArrayList<>();}
    : LEXER_RULENAME ':' lexExpr ('->' 'skip' {$isSkipped = true;})?;

lexExpr
       :
       | LITERAL {String s = $LITERAL.text; $lexRule::literals.add(s.substring(1, s.length() - 1));}('|' lexExpr)?
       | RANGE {$lexRule::ranges.add($RANGE.text);}('|' lexExpr)?;


ARGS: '(' (.)+? ')';
BLOCK: '*/' (.)+? '/*' ;
RANGE: '['[A-Za-z0-9]'-'[A-Za-z0-9]']';
LEXER_RULENAME: [A-Z]+;
PARSER_RULENAME: [a-z][A-Za-z]*;
LITERAL: '\'' (~'\'')* '\'';
IDENT: ([a-zA-Z])([a-zA-Z0-9_])*;
WS: [ \t\r\n]+ -> skip;