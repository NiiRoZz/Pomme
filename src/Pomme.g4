grammar Pomme;

//parser

name        : NAME ':';


//lexer


DRAW        : 'draw' ;

STRING      : '"' .*? '"' ;

NAME        :  [a-zA-Z0-9\-_]+;

NEWLINE     : ('\r'? '\n' | '\r')+ ;
TAB         : ('\t' | '        ' | '    ' ) ;
WHITESPACE  : ' ' -> skip ;