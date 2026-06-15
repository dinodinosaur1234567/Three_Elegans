#include "Core/Logger/Logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void LogMessage(Stream stream, const char *message, ...)
{
    va_list args;
    va_start(args, message);

    switch (stream)
    {
        case MESSAGE:
            printf("[INFO] ");
            break;

        case WARNING:
            printf("[WARN] ");
            break;

        case ERROR:
            printf("[ERROR] ");
            break;
    }

    vprintf(message, args);
    printf("\n");

    va_end(args);

    if (stream == ERROR)
    {
        exit(EXIT_FAILURE);
    }
}