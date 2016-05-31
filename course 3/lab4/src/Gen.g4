grammar Gen;

file: name header? members? (definition ';')*;

name: 'grammar' IDENT ';';

header: '@header' BLOCK;
members: '@members' BLOCK;

definition: lexRule
          | parseRule;

parseRule locals [List<List<String>> alt = new ArrayList<>();]
        : PARSER_RULENAME ':' parseExpr;

parseExpr locals [List<String> rules = new ArrayList<>();]
        @init {$parseRule::alt.add($rules);}
        : (ruleName {$rules.add($ruleName.text);})*
          ('|' parseExpr)?;

ruleName
    : LEXER_RULENAME
    | PARSER_RULENAME;


lexRule locals [List<String> literals, List<String> ranges, boolean isSkipped]
    @init {$literals = new ArrayList<>(); $ranges = new ArrayList<>();}
    : LEXER_RULENAME ':' lexExpr ('->' 'skip' {$isSkipped = true;})?;

lexExpr
       :
       | LITERAL {String s = $LITERAL.text; $lexRule::literals.add(s.substring(1, s.length() - 1));}('|' lexExpr)?
       | RANGE {$lexRule::ranges.add($RANGE.text);}('|' lexExpr)?;


BLOCK: '*/' (.)+? '\\*' ;
RANGE: '['[A-Za-z0-9]'-'[A-Za-z0-9]']';
LEXER_RULENAME: [A-Z]+;
PARSER_RULENAME: [a-z][A-Za-z]*;
LITERAL: '\'' (~'\'')* '\'';
IDENT: ([a-zA-Z])([a-zA-Z0-9_])*;
WS: [ \t\r\n]+ -> skip;