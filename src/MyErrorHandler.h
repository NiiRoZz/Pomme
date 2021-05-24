#pragma once

#include "ErrorHandler.h"

namespace Pomme
{
    class MyErrorHandler : public ErrorHandler
    {
        virtual void handleUnexpectedToken(int expectedKind, const JJString& expectedToken, Token *actual, PommeLexer *parser) override
        {
            error_count++;
            fprintf(stderr, "Expecting %s at: %d:%d but got %s\n", addUnicodeEscapes(expectedToken).c_str(), actual->beginLine, actual->beginColumn, addUnicodeEscapes(actual->image).c_str());
        }
        virtual void handleParseError(Token *last, Token *unexpected, const JJSimpleString& production, PommeLexer *parser) override
        {
            error_count++;
            fprintf(stderr, "Encountered: %s at: %d:%d while parsing: %s\n", addUnicodeEscapes(unexpected->image).c_str(), unexpected->beginLine, unexpected->beginColumn, production.c_str());
        }
    };
}