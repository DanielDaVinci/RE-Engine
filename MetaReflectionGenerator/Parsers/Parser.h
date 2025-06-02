#pragma once
#include <string>
#include <llvm/Support/Casting.h>
#include "clang-c/Index.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/Decl.h"
#include "clang/AST/Expr.h"

using namespace clang;

class Parser
{
public:
    virtual bool Parse(CXCursor Cursor);
    virtual bool CanParse(CXCursor Cursor) const;
    
    static std::string GetAttributeName(const CXCursor& Cursor);
    
    template<typename DeclType>
    static const DeclType* GetCursorDecl(const CXCursor& Cursor)
    {
        return llvm::dyn_cast_or_null<const DeclType>(static_cast<const Decl*>(Cursor.data[0]));
    }
    
    static const Stmt* GetCursorStmt(const CXCursor& Cursor);
};
