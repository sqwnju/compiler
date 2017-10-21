#include <stdio.h>


#include "ParsingNode.h"
#include "lex.yy.h"
#include "syntax.tab.h"

void ParsingFinalPhase(char* filename)
{
	if(!ParsingSwitch) 
	{
		printf("\033[31mParsing %s over(with syntax or lexical error).\033[0m\n\n", filename);
	}
	else
	{
		SetDepthOfParsingTree(ParsingRoot, 0);
		PreorderPrintParsingTree(ParsingRoot);
		printf("\033[32mParsing %s over(No error).\033[0m\n\n", filename);
	}
	return;
}

int main(int argc, char** argv)
{
	int i;
	if (argc <= 1) return 1;
	if (argc < 2)
	{
		yyparse();
		if(!ParsingSwitch)
		{
			printf("\033[31mParsing over(with syntax or lexical error).\033[0m\n\n");
		}
		else
		{
			SetDepthOfParsingTree(ParsingRoot, 0);
			PreorderPrintParsingTree(ParsingRoot);
			printf("\033[32mParsing over(with no error).\033[0m\n\n");
		}
		return 0;
	}
	for (i = 1; i < argc; ++i)
	{
		
		FILE* f = fopen(argv[i], "r");
		if (!f)
		{
			perror(argv[i]);
			return 1;
		}
		yyrestart(f);

#if YYDEBUG == 1
		yydebug = 1;
#endif
		yylineno = 1;
		ParsingSwitch = true;
		printf("Parsing %s begin...\n", argv[i]);
		yyparse();
		fclose(f);

		ParsingFinalPhase(argv[i]);
		
	}

	return 0;
}