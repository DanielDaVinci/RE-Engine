#include "PropertyParser.h"

#include <iostream>
#include <clang/AST/DeclTemplate.h>
#include <clang/Sema/CodeCompleteConsumer.h>

#include "MetaReflection/MetaReflection.h"

bool PropertyParser::Parse(CXCursor Cursor)
{
    Field = GetCursorDecl<FieldDecl>(Cursor);
    if (!Field)
    {
        return false;
    }

    PropertyName = clang_getCString(clang_getCursorDisplayName(Cursor));
    std::cout << "Property: " << PropertyName << std::endl;

    return true;
}

bool PropertyParser::CanParse(CXCursor Cursor) const
{
    return clang_getCursorKind(Cursor) == CXCursor_FieldDecl && GetAttributeName(Cursor).starts_with(ATTRIBUTE_PROPERTY_NAME);
}

std::string PropertyParser::GetName() const
{
    return PropertyName;
}
