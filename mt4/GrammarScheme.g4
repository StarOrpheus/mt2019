grammar GrammarScheme;

options {
    language = Cpp;
}

grammarSpec
    : grammarName header? fields? rules ;
grammarName
    : GRAMMAR IDENTIFIER SEMI;
header
    : HEADER code ;

fields
    : FIELDS SQUARE_OPEN field+ SQUARE_CLOSE;
field
    : wide_identifier+ SEMI ;

rules
    : grammarRule+ ;

grammarRule
    : tokenRule | syntaxRule ;

tokenRule
    : TOKEN_NAME COLON REGEX code? SKIP_RULE? SEMI ;

syntaxRule
    : IDENTIFIER argumentsWithType? COLON names SEMI ;
    
names
    : moreNames | names OR names | EPS;
moreNames
    : name+ code? ;
name
    : TOKEN_NAME | IDENTIFIER argument? ;

code                          : CODE ;
argument                      : ARGUMENT ;
argumentsWithType             : SQUARE_OPEN wideIdentsList SQUARE_CLOSE ;

wideIdentsList                : (wide_identifier | COMMA)+ ;

wide_identifier               : (IDENTIFIER | LESS | GREATER)
                              ;  // [.()<>0-9a-zA-Z*] ;

CIPHER                        : [0-9] ;
OR                            : '|' ;
COLON                         : ':' ;
SEMI                          : ';' ;
CURLY_OPEN                    : '{' ;
CURLY_CLOSE                   : '}' ;
OPEN                          : '(' ;
CLOSE                         : ')' ;
DOT                           : '.' ;
ASTERISK                      : '*' ;
SQUARE_OPEN                   : '[' ;
SQUARE_CLOSE                  : ']' ;
EQUALS_SIGN                   : '=' ;
COMMA                         : ',' ;
LESS                          : '<' ;
GREATER                       : '>' ;
GRAMMAR                       : 'grammar' ;
HEADER                        : 'header' ;
FIELDS                        : 'fields' ;
SKIP_RULE                     : '-> skip' ;
TOKEN_NAME                    : [A-Z_]+ ;
IDENTIFIER                    : [A-Z]?[a-z_]+ ;
CODE                          : CURLY_OPEN .+? CURLY_CLOSE ;
ARGUMENT                      : OPEN .+? CLOSE ;
REGEX                         : '\''.*?'\'' ;
EPS : 'EPS';

WHITESPACE                    : (' ' | '\t') -> skip;
NEWLINE                       : ('\r'? '\n' | '\r') -> skip;