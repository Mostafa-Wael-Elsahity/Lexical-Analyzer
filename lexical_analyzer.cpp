#include <bits/stdc++.h>

using namespace std;

enum TokenType
{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    NUMERIC_CONSTANT,
    CHARACTER_CONSTANT,
    STRING_LITERAL, // Added string token
    SPECIAL_CHARACTER,
    COMMENT,
    WHITE_SPACE,
    NEWLINE
};

struct Token
{
    TokenType type;
    string lexeme;
};

class Lexer
{
public:
    Lexer(const string &code) : code(code), index(0) {}

    vector<Token> analyze()
    {
        vector<Token> tokens;
        while (index < code.length())
        {
            char currentChar = code[index];

            if (isspace(currentChar))
            {
                handleWhiteSpace();
            }
            else if (currentChar == '\n')
            {
                handleNewline();
            }
            else if (isalpha(currentChar) || currentChar == '_')
            {
                handleIdentifierOrKeyword();
            }
            else if (isdigit(currentChar))
            {
                handleNumericConstant();
            }
            else if (currentChar == '\'' || currentChar == '\"')
            {
                handleCharacterOrStringLiteral();
            }
            else if (isOperator(currentChar))
            {
                handleOperator();
            }
            else if (isSpecialCharacter(currentChar))
            {
                handleSpecialCharacter();
            }
            else if (currentChar == '/')
            {
                handleComment();
            }
            else
            {
                // Unknown character
                advance();
            }
        }

        return tokens;
    }

private:
    string code;
    size_t index;

    bool isOperator(char ch)
    {
        string operators = "+-*/^%=><!&|";
        return operators.find(ch) != string::npos;
    }


    bool isSpecialCharacter(char ch)
    {
        string specialChars = "(){}[];,:.";
        return specialChars.find(ch) != string::npos;
    }


    void advance()
    {
        ++index;
    }

    void handleWhiteSpace()
    {
        while (isspace(code[index]))
        {
            advance();
        }
    }

    void handleNewline()
    {
        advance();
        // Tokenize newline
        Token token{NEWLINE, "\n"};
        cout << "Type: NEWLINE, Lexeme: " << token.lexeme << endl;
    }

    void handleIdentifierOrKeyword()
    {
        string lexeme;
        while (isalnum(code[index]) || code[index] == '_')
        {
            lexeme += code[index];
            advance();
        }

        unordered_set<string> keywords{
            "char", "if", "else", "while", "for", "return", "bool",
            "true", "false", "main", "do", "switch", "case", "default",
            "break", "continue", "sizeof", "enum", "typedef", "struct", "union",
            "const", "volatile", "extern", "register", "static", "inline", "restrict",
            "auto", "signed", "unsigned", "short", "long", "double", "float"};
        TokenType type = keywords.count(lexeme)? KEYWORD : IDENTIFIER;

        Token token{type, lexeme};
        cout << "Type: " << getTypeString(type) << ", Lexeme: " << token.lexeme << endl;
    }

    void handleNumericConstant()
    {
        string lexeme;
        while (isdigit(code[index]))
        {
            lexeme += code[index];
            advance();
        }

        Token token{NUMERIC_CONSTANT, lexeme};
        cout << "Type: NUMERIC_CONSTANT, Lexeme: " << token.lexeme << endl;
    }

    void handleCharacterOrStringLiteral()
    {
        char quote = code[index];
        string lexeme;
        lexeme += quote;
        advance();

        while (code[index] != quote && code[index] != '\0' && code[index] != '\n')
        {
            lexeme += code[index];
            advance();
        }

        if (code[index] == quote)
        {
            lexeme += code[index];
            advance();
            TokenType type = (quote == '\'') ? CHARACTER_CONSTANT : STRING_LITERAL;
            Token token{type, lexeme};
            cout << "Type: " << getTypeString(type) << ", Lexeme: " << token.lexeme << endl;
        }
        else
        {
            // Unterminated character or string literal
            cout << "Error: Unterminated character or string literal." << endl;
        }
    }

    void handleOperator()
    {
        string lexeme;
        while (isOperator(code[index]))
        {
            lexeme += code[index];
            advance();
        }

        Token token{OPERATOR, lexeme};
        cout << "Type: OPERATOR, Lexeme: " << token.lexeme << endl;
    }

    void handleSpecialCharacter()
    {
        string lexeme;
        while (isSpecialCharacter(code[index]))
        {
            lexeme += code[index];
            advance();
        }

        Token token{SPECIAL_CHARACTER, lexeme};
        cout << "Type: SPECIAL_CHARACTER, Lexeme: " << token.lexeme << endl;
    }

    void handleComment()
    {
        advance();
        if (code[index] == '/')
        {
            // Single-line comment
            while (code[index] != '\0' && code[index] != '\n')
            {
                advance();
            }
        }
        else if (code[index] == '*')
        {
            // Multi-line comment
            advance(); // Skip '*'
            while (code[index] != '\0')
            {
                if (code[index] == '*' && code[index + 1] == '/')
                {
                    advance(); // Skip '*'
                    advance(); // Skip '/'
                    break;
                }
                advance();
            }
        }

        // Tokenize comment
        Token token{COMMENT, ""};
        cout << "Type: COMMENT, Lexeme: " << token.lexeme << endl;
    }

    string getTypeString(TokenType type)
    {
        switch (type)
        {
        case KEYWORD:
            return "KEYWORD";
        case IDENTIFIER:
            return "IDENTIFIER";
        case OPERATOR:
            return "OPERATOR";
        case NUMERIC_CONSTANT:
            return "NUMERIC_CONSTANT";
        case CHARACTER_CONSTANT:
            return "CHARACTER_CONSTANT";
        case STRING_LITERAL:
            return "STRING_LITERAL";
        case SPECIAL_CHARACTER:
            return "SPECIAL_CHARACTER";
        case COMMENT:
            return "COMMENT";
        case WHITE_SPACE:
            return "WHITE_SPACE";
        case NEWLINE:
            return "NEWLINE";
        default:
            return "UNKNOWN";
        }
    }
};

int main()
{
    // Example C code
    string code = "int main() {int a = 5; float b = 3.14; char c = 'a';return 0;string str = \"Hello, World!\";}";

    // cin>>code; // enter your code after you uncomment this line 
    // Create lexer and perform lexical analysis
    Lexer lexer(code);
    lexer.analyze();

    return 0;
}
