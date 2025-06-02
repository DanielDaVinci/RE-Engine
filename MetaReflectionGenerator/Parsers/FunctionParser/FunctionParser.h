#pragma once
#include "MetaReflectionGenerator/Parsers/Parser.h"

namespace clang
{
    class FunctionDecl;
}

class FunctionParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;

    std::string GetName() const;
    
private:
    std::string FunctionName;
    const FunctionDecl* Function = nullptr;
};
