#include "ClassParser.h"

#include <direct.h>
#include <format>
#include <fstream>
#include <iostream>

#include "DebugLog/Public/Check/Check.h"
#include "MetaReflection/MetaReflection.h"
#include "MetaReflectionGenerator/Generator/ReflectionGenerator.h"
#include "MetaReflectionGenerator/Parsers/FunctionParser/FunctionParser.h"
#include "MetaReflectionGenerator/Parsers/PropertyParser/PropertyParser.h"

using namespace clang;

bool ClassParser::Parse(CXCursor Cursor)
{
    std::cout << "------- PARSED CLASS -------" << std::endl;
    
    bIsStructure = clang_getCursorKind(Cursor) == CXCursor_StructDecl;
    FilePath = GetFilePath(Cursor);
    ClassName = clang_getCString(clang_getCursorDisplayName(Cursor));
    std::cout << "Class: " << ClassName << std::endl;
    
    clang_visitChildren(Cursor, VisitChildRecursive, this);
    
    std::cout << "----------------------------" << std::endl;
    
    return true;
}

bool ClassParser::CanParse(CXCursor Cursor) const
{
    return clang_getCursorKind(Cursor) == CXCursor_ClassDecl && GetAttributeName(Cursor).starts_with(ATTRIBUTE_CLASS_NAME) ||
        clang_getCursorKind(Cursor) == CXCursor_StructDecl && GetAttributeName(Cursor).starts_with(ATTRIBUTE_STRUCT_NAME);
}

void ClassParser::SetSolutionPath(const std::string& InSolutionPath)
{
    SolutionPath = InSolutionPath;
}

CXChildVisitResult ClassParser::VisitChildRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
{
    ClassParser* This = static_cast<ClassParser*>(ClientData);
    RCheckReturn(This, CXChildVisit_Break);
    
    const CXCursorKind CursorKind = clang_getCursorKind(Cursor);
    if (CursorKind == CXCursor_CXXBaseSpecifier)
    {
        This->ParentClassName = clang_getCString(clang_getCursorDisplayName(Cursor));
    }
    if (CursorKind == CXCursor_FieldDecl)
    {
        const std::shared_ptr<PropertyParser> Parser = std::make_shared<PropertyParser>();
        if (Parser->CanParse(Cursor))
        {
            Parser->Parse(Cursor);
            This->Properties.push_back(Parser);
        }
    }
    else if (CursorKind == CXCursor_CXXMethod)
    {
        const std::shared_ptr<FunctionParser> Parser = std::make_shared<FunctionParser>();
        if (Parser->CanParse(Cursor))
        {
            Parser->Parse(Cursor);
            This->Functions.push_back(Parser);
        }
    }
    
    return CXChildVisit_Continue;
}

void ClassParser::Generate() const
{
    std::cout << "------- GENERATED CLASS -------" << std::endl;
    
    const std::string FileName = GetFileNameFromPath(FilePath);
    const std::string GeneratedDirectoryPath = SolutionPath + ReflectionGenerator::GenerateDirectoryName + "\\";
    const std::string GeneratedFilePath = GeneratedDirectoryPath + FileName + "." + ReflectionGenerator::GeneratedFileExtension;
    std::cout << "File Path: " << FilePath << std::endl;
    std::cout << "Generated File Path: " << GeneratedFilePath << std::endl;

    ReflectionGenerator::CreateDirectoryIfNoExists(GeneratedDirectoryPath);
    std::ofstream GeneratedFile(GeneratedFilePath, std::ios::trunc);
    RCheckReturn(GeneratedFile.is_open());
    FillFile(GeneratedFile);

    GeneratedFile.close();

    std::cout << "-------------------------------" << std::endl;
}

void ClassParser::FillFile(std::ofstream& File) const
{
    File << "#pragma once" << std::endl;
    File << "#include \"MetaReflection/MetaReflection.h\"" << std::endl;
    File << std::endl;

    File << "#ifdef GENERATED_BODY" << std::endl;
    File << "#undef GENERATED_BODY" << std::endl;
    File << "#endif" << std::endl;
    File << std::endl;

    File << "#define GENERATED_BODY(...)" << "\\" << std::endl;

    File << "public:" << "\\" << std::endl;
    if (!ParentClassName.empty())
    {
        std::string SecondPart = ParentClassName;
        auto Index = SecondPart.rfind(':');
        if (Index != -1)
        {
            SecondPart = SecondPart.substr(Index + 1, SecondPart.size() - Index - 1);
        }
        
        File << "\t" << std::format("using {}::{};", ParentClassName, SecondPart) << "\\" << std::endl;
        File << "\t" << "std::string GetClassName() const override { return \"" << ClassName << "\" ; }" << "\\" << std::endl;
    }
    else
    {
        File << "\t" << "virtual std::string GetClassName() const { return \"" << ClassName << "\" ; }" << "\\" << std::endl;
    }
    File << "\t" << "static std::string GetStaticClassName() { return \"" << ClassName << "\" ; }" << "\\" << std::endl;
    
    File << "private:" << "\\" << std::endl;
    File << "\t" << std::format("using ThisClass = {};", ClassName);
    if (!ParentClassName.empty())
    {
        File << "\\" << std::endl;
        File << "\t" << std::format("using SuperClass = {};", ParentClassName);
    }
    File << "\\" << std::endl;
    File << "\t" << std::format("friend struct refl_impl::metadata::type_info__<{}>;", ClassName) << "\\" << std::endl;
    if (bIsStructure)
    {
        File << "public:" << std::endl;
    }
    else
    {
        File << "private:" << std::endl;
    }
    File << std::endl;

    File << "#ifdef META_REFLECT" << std::endl;
    File << "#undef META_REFLECT" << std::endl;
    File << "#endif" << std::endl;
    File << std::endl;

    File << "#define META_REFLECT(...)" << "\\" << std::endl;
    File << "REFL_AUTO(" << "\\" << std::endl;
    
    File << "\t" << "type(" << ClassName;
    if (!ParentClassName.empty())
    {
        File << ", " << "bases<" << ParentClassName << ">";
    }
    File << ")";
    
    for (const auto& Property : Properties)
    {
        RCheckContinue(Property);
        File << ", " << "\\" << std::endl;
        File << "\t" << "field(" << Property->GetName() << ", " << "Serializable()" << ")";
    }
    for (const auto& Function : Functions)
    {
        RCheckContinue(Function);
        File << ", " << "\\" << std::endl;
        File << "\t" << "func(" << Function->GetName() << ")" ;
    }
    File << "\\" << std::endl << ")" << std::endl;
}

std::string ClassParser::GetFilePath(CXCursor Cursor)
{
    CXSourceLocation location = clang_getCursorLocation(Cursor);
    
    CXFile File;
    unsigned line, column, offset;
    clang_getFileLocation(location, &File, &line, &column, &offset);
    RCheckReturn(File, {});
    
    return clang_getCString(clang_File_tryGetRealPathName(File));
}

std::string ClassParser::GetFileNameFromPath(const std::string& FullPath)
{
    const auto IndexStart = FullPath.rfind("\\");
    const auto IndexEnd = FullPath.rfind(".");
    return FullPath.substr(IndexStart + 1, IndexEnd - IndexStart - 1);
}
