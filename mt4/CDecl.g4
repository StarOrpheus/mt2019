grammar CDecl;

storage_class_specifier
	: EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers_continuation
	| type_specifier declaration_specifiers_continuation
	| type_qualifier declaration_specifiers_continuation
	;

declaration_specifiers_continuation
    : EPS
    | declaration_specifiers
    ;

type_qualifier_list
	: type_qualifier type_qualifier_list_continuation
	;

type_qualifier_list_continuation
    : EPS
    | type_qualifier_list
    ;

pointer
	: EPS
	| POINTER pointer_continuation
	;

pointer_continuation
    : EPS
	| type_qualifier_list_continuation pointer
	;

direct_declarator
	: IDENTIFIER
	| OPEN_PARANTHESIS declarator CLOSE_PARANTHESIS
    ;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

declarator_list
	: declarator declarator_list_continuation
	;

declarator_list_continuation
    : EPS
    | declarator COMMA declarator_list
    ;

declaration
	: declaration_specifiers declaration_continuation
	| declarator_list SEMI
    ;

declaration_continuation
    : SEMI
    | declarator_list SEMI
    ;


STATIC
    : 'static'
    ;

EXTERN
    : 'extern'
    ;

AUTO
    : 'auto'
    ;

REGISTER
    : 'register'
    ;

VOID
    : 'void'
    ;

CHAR
    : 'char'
    ;

SHORT
    : 'short'
    ;

INT
    : 'int'
    ;

LONG
    : 'long'
    ;

FLOAT
    : 'float'
    ;

DOUBLE
    : 'double'
    ;

SIGNED
    : 'signed'
    ;

UNSIGNED
    : 'unsigned'
    ;

VOLATILE
    : 'volatile'
    ;

CONST
    : 'const'
    ;

IDENTIFIER
    : '[a-zA-Z_]+[a-zA-Z_0-9]*'
    ;

SEMI
    : ';'
    ;

POINTER
    : '\*'
    ;

OPEN_PARANTHESIS
    : '\('
    ;

CLOSE_PARANTHESIS
    : '\)'
    ;

COMMA
    : ','
    ;

EPS: 'EPS' ;
WHITESPACE : '[ \t\r\n]' -> skip ;