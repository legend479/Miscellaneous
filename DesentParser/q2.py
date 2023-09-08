import pytest
import json
##################### BOILERPLATE BEGINS ############################

# Token types enumeration
##################### YOU CAN CHANGE THE ENUMERATION IF YOU WANT #######################
class TokenType:
    IDENTIFIER = "IDENTIFIER"
    KEYWORD = "KEYWORD"
    INTEGER = "INTEGER"
    FLOAT = "FLOAT"
    SYMBOL = "SYMBOL"

# Token hierarchy dictionary
token_hierarchy = {
    "if": TokenType.KEYWORD,
    "else": TokenType.KEYWORD,
    "print": TokenType.KEYWORD
}


# helper function to check if it is a valid identifier
def is_valid_identifier(lexeme):
    if not lexeme:
        return False

    # Check if the first character is an underscore or a letter
    if not (lexeme[0].isalpha() or lexeme[0] == '_'):
        return False

    # Check the rest of the characters (can be letters, digits, or underscores)
    for char in lexeme[1:]:
        if not (char.isalnum() or char == '_'):
            return False

    return True


# Tokenizer function
def tokenize(source_code):
    tokens = []
    position = 0

    while position < len(source_code):
        # Helper function to check if a character is alphanumeric
        def is_alphanumeric(char):
            return char.isalpha() or char.isdigit() or (char=='_')

        char = source_code[position]

        # Check for whitespace and skip it
        if char.isspace():
            position += 1
            continue

        # Identifier recognition
        if char.isalpha():
            lexeme = char
            position += 1
            while position < len(source_code) and is_alphanumeric(source_code[position]):
                lexeme += source_code[position]
                position += 1

            if lexeme in token_hierarchy:
                token_type = token_hierarchy[lexeme]
            else:
                # check if it is a valid identifier
                if is_valid_identifier(lexeme):
                    token_type = TokenType.IDENTIFIER
                else:
                    raise ValueError(f"Invalid identifier: {lexeme}")

        # Integer or Float recognition
        elif char.isdigit():
            lexeme = char
            position += 1

            is_float = False
            while position < len(source_code):
                next_char = source_code[position]
                # checking if it is a float, or a full-stop
                if next_char == '.':
                    if (position + 1 < len(source_code)):
                        next_next_char = source_code[position+1]
                        if next_next_char.isdigit():
                            is_float = True

                # checking for illegal identifier
                elif is_alphanumeric(next_char) and not next_char.isdigit():
                    while position < len(source_code) and is_alphanumeric(source_code[position]):
                        lexeme += source_code[position]
                        position += 1
                    if not is_valid_identifier(lexeme):
                        raise ValueError(f"Invalid identifier: {str(lexeme)}\nIdentifier can't start with digits")

                elif not next_char.isdigit():
                    break

                lexeme += next_char
                position += 1

            token_type = TokenType.FLOAT if is_float else TokenType.INTEGER

        # Symbol recognition
        else:
            lexeme = char
            position += 1
            token_type = TokenType.SYMBOL

        tokens.append((token_type, lexeme))

    return tokens

########################## BOILERPLATE ENDS ###########################

def isOp1(tokens):
    global lookahead
    global booluu
    if(tokens[lookahead][1] in ["+", "-", "*", "/", "^", "<", ">", "="]):
        return True
    return False

def isY(tokens):
    global lookahead
    global booluu
    if(tokens[lookahead][0] in [TokenType.IDENTIFIER, TokenType.INTEGER, TokenType.FLOAT, TokenType.KEYWORD] and tokens[lookahead][1] not in ["if", "else"]):
        return True
    return False

def A(tokens):
    global lookahead
    global Error_Warning_Array
    global LastWarningPos
    global ElseErrorFlag
    if(lookahead >= len(tokens)):
        Error_Warning_Array.append(f"Syntax Error: Unexpected end of input at position {lookahead}")
        LastWarningPos = lookahead
        return False

    if(isY(tokens)):
        lookahead += 1

        if(lookahead >= len(tokens)):
            Error_Warning_Array.append(f"Syntax Error: Unexpected end of input at position {lookahead}")
            LastWarningPos = lookahead
            return False
        
        if(isOp1(tokens)):
            lookahead += 1

            if(lookahead >= len(tokens)):
                return False
            
            return A(tokens)
        else:
            bool1 = Statement(tokens)
            if(not ElseErrorFlag):
                ElseErrorFlag = not bool1
            # if(not bool1): ElseErrorFlag = True
            if(lookahead < len(tokens) and tokens[lookahead][1] == "else"):
                lookahead += 1
                bool2 = Statement(tokens)
                return bool1 and bool2
            else:
                return bool1
            
    else:
        Error_Warning_Array.append(f"Syntax Error: Expected Y at position {lookahead} instead got token type {tokens[lookahead][0]} and token value {tokens[lookahead][1]}")
        LastWarningPos = lookahead
        return False

def Statement(tokens):
    global lookahead
    global Error_Warning_Array
    global LastWarningPos
 

    if(lookahead >= len(tokens)):
        if(tokens[lookahead-1][0] not in [TokenType.IDENTIFIER, TokenType.INTEGER, TokenType.FLOAT, TokenType.KEYWORD] and tokens[lookahead][1] not in ["if", "else"]):
            LastWarningPos = lookahead
        Error_Warning_Array.append(f"Syntax Error: Unexpected end of input at position {lookahead}")
        return False

    if(tokens[lookahead][1]=='if'):
        lookahead+=1
        return A(tokens)
    
    elif(isY(tokens)):
        lookahead+=1
        Statement(tokens) 
        return True
    
    else:
        Error_Warning_Array.append(f"Syntax Error: Expected 'if' or Y at position {lookahead} instead got token type {tokens[lookahead][0]} and token value {tokens[lookahead][1]}")
        if(tokens[lookahead-1][0] not in [TokenType.IDENTIFIER, TokenType.INTEGER, TokenType.FLOAT, TokenType.KEYWORD] and tokens[lookahead][1] not in ["if", "else"]):
            LastWarningPos = lookahead
        return False

def checkGrammar(tokens):
    global lookahead 
    global Error_Warning_Array
    global LastWarningPos
    global ElseErrorFlag

    ElseErrorFlag = False
    lookahead = 0
    LastWarningPos = -1

    Error_Warning_Array = []

    if(len(tokens) == 0):
        print("Syntax Error: Empty Input")
        return False
    
    Statement(tokens)

    if(ElseErrorFlag):
        print("Syntax Error: Incomplete Clause before 'else' KEYWORD")
        return False
    
    if(LastWarningPos == len(tokens)):
        for i in range(len(Error_Warning_Array)-1):
            print(Error_Warning_Array[i].replace("Syntax Error", "Syntax Warning"))
        print(Error_Warning_Array[-1])
        return False

    if(lookahead < len(tokens)):
        # print errors
        for error in Error_Warning_Array:
            print(error)
        
    elif (lookahead == len(tokens)):
        for error in Error_Warning_Array:
            print(error.replace("Syntax Error", "Syntax Warning"))
    
    return (lookahead == len(tokens))
  

# Test the tokenizer
if __name__ == "__main__":
    source_code = "if x + 3.1 print else if test else if x + 3 * 4 < 2 ok"
    tokens = tokenize(source_code)
# 
    if(checkGrammar(tokens)):  # You are tasked with implementing the function checkGrammar
        for token in tokens:
            print(f"Token Type: {token[0]}, Token Value: {token[1]}")