#pragma once
#include "MetaReflectionGenerator/Parsers/Parser.h"

using namespace clang;
class clang::FieldDecl;

class PropertyParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;

    std::string GetName() const;
    
private:
    std::string PropertyName;
    const FieldDecl* Field = nullptr;
};
