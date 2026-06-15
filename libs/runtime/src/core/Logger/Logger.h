#pragma once

typedef enum
{
    MESSAGE,
    WARNING,
    ERROR
} Stream;

void LogMessage(Stream stream, const char *message, ...);