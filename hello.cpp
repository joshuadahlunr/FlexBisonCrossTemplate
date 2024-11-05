#include <iostream>

#include <reflex/input.h>
#include "gen/parser.h"
#include "gen/scanner.h"

int yylex(reflex::Input* input /* = nullptr */) {
	static Lexer lexer;
	if(input) { lexer = Lexer(*input); return true; }
	else return lexer.lex();
}

void set_input(reflex::Input& input) {
	yylex(&input);
}
void set_input(reflex::Input&& input) {
	yylex(&input);
}

void flexTest(std::string string) {
	set_input(std::move(string));
	int	token;

	while((token=yylex()) != 0){
		switch(token){
			break; case PLUS: std::cout << "+" << std::endl;
			break; case MINUS: std::cout << "-" << std::endl;
			break; case MULT: std::cout << "*" << std::endl;
			break; case DIV: std::cout << "/" << std::endl;
			break; case SEMI: std::cout << ";" << std::endl;
			break; case OPEN: std::cout << "(" << std::endl;
			break; case CLOSE: std::cout << ")" << std::endl;
			break; case INTEGER: std::cout << yylval << std::endl;
			break; default: std::cout << "!ERROR!" << std::endl;
		}
	}
}

void bisonTest(std::string string) {
	set_input(string);
	yyparse();
}

int main() {
	flexTest("2 + 2; 4 / 2; 5 - 6;");
	bisonTest("2 + 2; 4 / 2; 5 - 6;");
}

void yyerror(const char* s) {
	std::cerr << s << std::endl;
}