#coding utf-8
import sys
import jinja2

CONSTANT = {'DELIMITER' : ':'}

class Definition:
    def __init__(self, regular_expression, type_name):
        self.regular_expression = regular_expression
        self.type_name = type_name

    def __str__(self):
        return self.regular_expression + " -> " + self.type_name

    def get_regular_expression(self):
        return self.regular_expression

    def get_type_name(self):
        return self.type_name

def main():
    if len(sys.argv) != 2:
        print("ArgumentError: Please input one definition file.")
        return
    try:
        definition_file = open(sys.argv[1])
    except FileNotFoundError:
        print("FileNotFoundError: Please check definition file name.")
        return 
    except:
        raise

    line = ''
    definition_list = []
    for line in definition_file:
        tokens = [token.strip(' \t\n\r') for token in line.split(CONSTANT['DELIMITER'])]
        definition_list.append(Definition(tokens[0], tokens[1]))
    for definition in definition_list:
        print(definition)

if __name__ == '__main__':
    main()
