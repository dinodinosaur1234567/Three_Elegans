#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "core/Loader/Loader.h"
#include "core/Logger/Logger.h"
#include "utils/Vector/Vector.h"
#include "utils/types/types.h"

void CompileNN(const char *nn_path, const char *cnn_path)
{
    FILE *input  = fopen(nn_path, "r");
    FILE *output = fopen(cnn_path, "wb");

    if(!input)
    {
        LogMessage(ERROR, "Failed to open input file: %s", nn_path);
        return;
    }

    if(!output)
    {
        LogMessage(ERROR, "Failed to create output file: %s", nn_path);
        fclose(input);
        return;
    }

    // ----- Lexer -----

    typedef enum
    {
        LABEL,
        STRING,
        NUMBER,
        NEW_LINE,
        COMMA,
        EQUALS,
        TAB,
        OBJECT_START,
        OBJECT_END,
        ARRAY_START,
        ARRAY_END

    } TokenType;

    typedef struct
    {
        TokenType type;
        char *value;
        uint32_t line;
        uint32_t column;

    } Token;

    Vector tokens;
    VecSpawn(&tokens, sizeof(Token));

    int c;
    uint32_t line = 1;
    uint32_t column = 1;

    while((c = fgetc(input)) != EOF)
    {
        switch (c)
        {
            case ' ':
                column++;
                break;

            case '\t':
            {
                Token t = {0};
                t.type = TAB;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case '\n':
            {
                Token t = {0};
                t.type = NEW_LINE;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                line++;
                column = 1;
            } break;

            case ',':
            {
                Token t = {0};
                t.type = COMMA;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case ':':
            {
                Token t = {0};
                t.type = EQUALS;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case '(':
            {
                Token t = {0};
                t.type = OBJECT_START;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case ')':
            {
                Token t = {0};
                t.type = OBJECT_END;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case '[':
            {
                Token t = {0};
                t.type = ARRAY_START;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case ']':
            {
                Token t = {0};
                t.type = ARRAY_END;
                t.line = line;
                t.column = column;

                VecPush(&tokens, &t);
                column++;
            } break;

            case '#':
                while ((c = fgetc(input)) != EOF && c != '\n');
                line++;
                column = 1;
                break;

            case '"':
            {
                Token t = {0};
                t.type = STRING;
                t.line = line;
                t.column = column;

                char buffer[256];
                int i = 0;

                while ((c = fgetc(input)) != EOF && c != '"' && c != '\n')
                {
                    if (i < 255)
                        buffer[i++] = c;

                    column++;
                }

                buffer[i] = '\0';
                t.value = strdup(buffer);

                VecPush(&tokens, &t);
            } break;

            default:
            {
                if (isalpha(c) || c == '_' || c == '\\')
                {
                    Token t = {0};
                    t.type = LABEL;
                    t.line = line;
                    t.column = column;

                    char buffer[256];
                    int i = 0;

                    buffer[i++] = c;

                    while ((c = fgetc(input)) != EOF && (isalnum(c) || c == '_' ))
                    {
                        if (i < 255)
                            buffer[i++] = c;

                        column++;
                    }

                    ungetc(c, input);

                    buffer[i] = '\0';
                    t.value = strdup(buffer);

                    VecPush(&tokens, &t);

                    continue;
                }

                if (isdigit(c))
                {
                    Token t = {0};
                    t.type = NUMBER;
                    t.line = line;
                    t.column = column;

                    char buffer[256];
                    int i = 0;

                    while (c != EOF && isdigit(c))
                    {
                        if (i < 255)
                            buffer[i++] = c;

                        c = fgetc(input);
                    }

                    buffer[i] = '\0';
                    t.value = strdup(buffer);

                    VecPush(&tokens, &t);

                    continue;
                }

            } break;
        }

        column++;
    }

    // Debugger
    LogMessage(MESSAGE, "========== TOKEN DEBUG ==========");

    const char *names[] =
    {
        "LABEL","STRING","NUMBER","NEW_LINE","COMMA",
        "EQUALS","TAB","OBJECT_START","OBJECT_END",
        "ARRAY_START","ARRAY_END"
    };

    Token *tokens_data = (Token *)tokens.data;

    for (index i = 0; i < tokens.count; i++)
    {
        Token *t = &tokens_data[i];

        LogMessage(MESSAGE, "[%u] %s | line=%u col=%u",
            i,
            names[t->type],
            t->line,
            t->column
        );

        if (t->value)
            LogMessage(MESSAGE, " | value=\"%s\"", t->value);

        LogMessage(MESSAGE, "\n");
    }

    LogMessage(MESSAGE, "=================================");

    // ----- Parser -----

    index i = 0;

    // Header
    if(tokens_data[0].type == LABEL && tokens_data[i].value == "HEADER")
    {
        if(tokens_data[1].type == EQUALS)
        {
            while(i < tokens.count)
            {

            }
        }
        else LogMessage(ERROR, "Expected comma after a label");
    }
    else LogMessage(ERROR, "Expected \"HEADER\"");

    fclose(input);
    fclose(output);
}