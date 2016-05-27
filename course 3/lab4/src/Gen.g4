grammar Gen;

file: name (definition ';')*;

name: 'grammar' IDENT ';';

definition: lexRule
          | parseRule;

parseRule: 'R';

lexRule locals [List<String> literals, List<String> ranges, boolean isSkipped]
    @init {$literals = new ArrayList<>(); $ranges = new ArrayList<>();}
    : LEXER_RULENAME ':' lexExpr ('->' 'skip' {$isSkipped = true;})?;

lexExpr
       :
       | LITERAL {String s = $LITERAL.text; $lexRule::literals.add(s.substring(1, s.length() - 1));}('|' lexExpr)?
       | RANGE {$lexRule::ranges.add($RANGE.text);}('|' lexExpr)?;



RANGE: '['[A-Za-z0-9]'-'[A-Za-z0-9]']';
LEXER_RULENAME: [A-Z]+;
LITERAL: '\'' (~'\'')* '\'';
IDENT: ([a-zA-Z])([a-zA-Z0-9_])*;
WS: [ \t\r\n]+ -> skip;