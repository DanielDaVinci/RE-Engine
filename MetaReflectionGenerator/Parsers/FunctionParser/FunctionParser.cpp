#include "FunctionParser.h"

#include <iostream>
#include "clang/AST/Stmt.h"
#include "DebugLog/Public/Check/Check.h"
#include "MetaReflection/MetaReflection.h"

bool FunctionParser::Parse(CXCursor Cursor)
{
    Function = GetCursorDecl<FunctionDecl>(Cursor);
    RCheckReturn(Function, false);

    FunctionName = clang_getCString(clang_getCursorDisplayName(Cursor));
    std::cout << "Function: " << FunctionName << std::endl;

    return true;
}

bool FunctionParser::CanParse(CXCursor Cursor) const
{
    return clang_getCursorKind(Cursor) == CXCursor_CXXMethod && GetAttributeName(Cursor).starts_with(ATTRIBUTE_FUNCTION_NAME);
}

std::string FunctionParser::GetName() const
{
    return FunctionName;
}
