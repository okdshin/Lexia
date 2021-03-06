#coding utf-8
import sys
import os
import jinja2

CONSTANT = {'DELIMITER' : ':',
'IGNORE_KEYWORD' : 'LEXIA_IGNORE',
'SYNTAX_TOKEN' : 'LEXIA_SYNTAX_TOKEN',
'RESOURCE_DIRECTORY': 'resource',
'LEXICAL_ANALYZER_TEMPLATE_FILE' : 'Lexer.h',
'TOKEN_TYPE_CODE_TEMPLATE':'\tstatic auto {{ t }}() -> TokenType { return TokenType("{{ t }}"); }',
'REGULAR_CODE_TEMPLATE':'\t\tregular_expression_token_list.push_back(\n\t\t\tToken(TokenType::{{ t }}(), Word("\\\\A{{ r }}")));',
'SYNTAX_TOKEN_CODE_TEMPLATE':'\tstatic auto {{s}}_TOKEN() -> Token{\n\t\treturn Token(TokenType::{{t}}(), Word("{{w}}"));\n\t}'
}
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
    token_type_list = []
    syntax_token_list = []
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
        elif tokens[0] == CONSTANT['SYNTAX_TOKEN']:
            syntax_token_list.append(tokens[1])
            token_type_list.append(tokens[1])
        else:
            definition_list.append(Definition(tokens[0], tokens[1]))
            token_type_list.append(tokens[1])
    print('ignore', ignore_reg)
    for definition in definition_list:
        print(definition)
    for syntax_token in syntax_token_list:
        print('syntax_token', syntax_token)

    token_type_code_template = jinja2.Template(CONSTANT['TOKEN_TYPE_CODE_TEMPLATE'])
    type_code = '\n'.join(
        [token_type_code_template.render(t=token_type) for token_type in token_type_list])
    
    reg_code_template = jinja2.Template(CONSTANT['REGULAR_CODE_TEMPLATE'])
    reg_code = '\n'.join(
        [reg_code_template.render(
            t=definition.get_type_name(), 
            r=definition.get_regular_expression().replace('\\', '\\\\')) 
                for definition in definition_list])
 
    syntax_token_code_template = jinja2.Template(CONSTANT['SYNTAX_TOKEN_CODE_TEMPLATE'])
    syntax_code = '\n'.join(
        [syntax_token_code_template.render(
            s=syntax_token,
            t=syntax_token, 
            w=syntax_token) 
                for syntax_token in syntax_token_list])
    try: 
        open(CONSTANT['LEXICAL_ANALYZER_TEMPLATE_FILE'], 'w').write(
            jinja2.Template(
                open(os.path.join(os.path.dirname(sys.executable), CONSTANT['RESOURCE_DIRECTORY'], CONSTANT['LEXICAL_ANALYZER_TEMPLATE_FILE']), 'r').read() 
            ).render(
                token_type_code=type_code,
                ignore_regular_expression=ignore_reg.replace('\\', '\\\\'), 
                regular_expression_code=reg_code,
                syntax_token_code=syntax_code))

    except FileNotFoundError:
        print("FileNotFoundError: LexicalAnalyzer template file not found.")
        return 

if __name__ == '__main__':
    main()
