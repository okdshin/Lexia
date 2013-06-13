#coding utf-8
import sys
import os
import jinja2

CONSTANT = {'DELIMITER' : ':',
'IGNORE_KEYWORD' : 'LEXIA_IGNORE',
'LEXICAL_ANALYZER_TEMPLATE_FILE' : 'resource/Lexer.h',
'TOKEN_TYPE_FILE':'resource/TokenType.h'}
class Definition:
    def __init__(self):
        self.regular_expression = ""
        self.type_name = ""

    def __init__(self, regular_expression, type_name):
        self.regular_expression = regular_expression
        self.type_name = type_name

    def __str__(self):
        return '\"' + self.regular_expression + '" -> ' + self.type_name

    def get_regular_expression(self):
        return self.regular_expression.replace('"', '\\"')

    def get_type_name(self):
        return self.type_name

def main():
    if len(sys.argv) != 2:
        print("ArgumentError: Please input one definition file.")
        return
    try:
        definition_file = open(sys.argv[1], 'r')
    except FileNotFoundError:
        print("FileNotFoundError: Please check definition file name.")
        return 

    line = ''
    definition_list = []
    ignore_reg = ''
    for line in definition_file:
        tokens = [token.strip(' \t\n\r') for token in line.split(CONSTANT['DELIMITER'])]
        while len(tokens) is not 2:
            print('DEBUG: ouch!! delimiter is used. but ... OK. Only last one is used as delimiter.')
            tokens[0] = tokens[0] + CONSTANT['DELIMITER'] + tokens[1]
            tokens.pop(1)
        if len(tokens) is not 2:
            print("ouch!! delimiter error!")
            return
        if tokens[1] == CONSTANT['IGNORE_KEYWORD']:
            ignore_reg = tokens[0]
        else:
            definition_list.append(Definition(tokens[0], tokens[1]))
    reg_code_template = jinja2.Template('\t\tregular_expression_token_list.push_back(\n\t\t\tToken::Create(TokenType::{{ t }}(), Word("^{{ r }}")));')
    for definition in definition_list:
        print(definition)
    print('ignore', ignore_reg)

    reg_code = '\n'.join(
        [reg_code_template.render(
            t=definition.get_type_name(), 
            r=definition.get_regular_expression().replace('\\', '\\\\')) 
                for definition in definition_list])
 
    try: 
        open('Lexer.h', 'w').write(
            jinja2.Template(
                open(os.path.join(os.path.dirname(sys.executable), CONSTANT['LEXICAL_ANALYZER_TEMPLATE_FILE']), 'r').read() 
            ).render(
                ignore_regular_expression=ignore_reg, 
                regular_expression_code=reg_code))

    except FileNotFoundError:
        print("FileNotFoundError: LexicalAnalyzer template file not found.")
        return 
    
    token_type_code_template = jinja2.Template('\tstatic auto {{ t }}() -> TokenType { return TokenType("{{ t }}"); }')
    type_code = '\n'.join(
        [token_type_code_template.render(
            t=definition.get_type_name(), 
            r=definition.get_regular_expression().replace('\\', '\\\\')) 
                for definition in definition_list])
    try: 
        open('TokenType.h', 'w').write(
            jinja2.Template(
                open(os.path.join(os.path.dirname(sys.executable), CONSTANT['TOKEN_TYPE_FILE']), 'r').read() 
            ).render(token_type_code=type_code))

    except FileNotFoundError:
        print("FileNotFoundError: TokenType template file not found.")
        return 


if __name__ == '__main__':
    main()
