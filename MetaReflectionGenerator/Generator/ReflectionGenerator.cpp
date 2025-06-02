#include "ReflectionGenerator.h"

#include <filesystem>
#include <iostream>

#include "clang-c/Index.h"
#include "DebugLog/Public/Check/Check.h"
#include "MetaReflectionGenerator/Parsers/ClassParser/ClassParser.h"

void ReflectionGenerator::Generate(const std::string& InSolutionPath)
{
    RCheckReturn(!InSolutionPath.empty());
    SolutionPath = InSolutionPath;

    ParseFiles();
    GenerateFiles();
}

void ReflectionGenerator::ParseFiles()
{
    auto FilePaths = FindHeaderFiles(SolutionPath);
    for (int i = 0; i < FilePaths.size(); i++)
    {
        ParseFile(FilePaths[i]);
        
        std::cout << std::format("Parse [{}/{}]: {}", i + 1, FilePaths.size(), GetFileName(FilePaths[i])) << std::endl;
    }
}

void ReflectionGenerator::ParseFile(const std::string& InFilePath)
{
    RCheckReturn(!InFilePath.empty());
    const char *args[] =
    {
        "-std=c++20",
        "-xc++",
        "-I../",
        "-D",
        "METAREFLECT=1"
    };

    CXIndex Index = clang_createIndex (false, false);
    CXTranslationUnit Unit = clang_parseTranslationUnit(
        Index, // CIdx
        InFilePath.c_str(), // source_filename
        args, // command_line_args
        std::size(args), // num_command_line_args
        nullptr, // unsave_files
        0, // num_unsaved_files
        CXTranslationUnit_DetailedPreprocessingRecord | 
        CXTranslationUnit_IncludeAttributedTypes |
        CXTranslationUnit_SkipFunctionBodies |
        CXTranslationUnit_KeepGoing);
    RCheckReturn(Unit);
    
    CXCursor RootCursor = clang_getTranslationUnitCursor(Unit);
    clang_visitChildren(RootCursor, VisitRecursive, this);
    
    clang_disposeTranslationUnit(Unit);
    clang_disposeIndex(Index);
}

void ReflectionGenerator::GenerateFiles() const
{
    for (const std::shared_ptr<ClassParser>& ClassParser : ClassParsers)
    {
        RCheckContinue(ClassParser);
        ClassParser->Generate();
    }
}

CXChildVisitResult ReflectionGenerator::VisitRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
{
    ReflectionGenerator* This = static_cast<ReflectionGenerator*>(ClientData);
    RCheckReturn(This, CXChildVisit_Break);
    
    const CXSourceLocation Location = clang_getCursorLocation( Cursor );
    if(clang_Location_isFromMainFile(Location) == 0)
    {
        return CXChildVisit_Continue;
    }
    
    const CXCursorKind CursorKind = clang_getCursorKind( Cursor );
    if (CursorKind == CXCursor_ClassDecl)
    {
        std::shared_ptr<ClassParser> Parser = std::make_shared<ClassParser>();
        if (Parser->CanParse(Cursor))
        {
            Parser->SetSolutionPath(This->SolutionPath);
            Parser->Parse(Cursor);
            This->ClassParsers.push_back(Parser);
        }
    }
    
    clang_visitChildren( Cursor, VisitRecursive, This );
    return CXChildVisit_Continue;
}

std::vector<std::string> ReflectionGenerator::FindHeaderFiles(const std::string& InDirectory)
{
    std::vector<std::string> HeaderFiles;
    for (const auto& Entry : std::filesystem::recursive_directory_iterator(InDirectory))
    {
        if (!IsInExceptionDirectory(Entry) && Entry.is_regular_file() && Entry.path().extension() == ".h")
        {
            HeaderFiles.push_back(Entry.path().string());
        }
    }

    return HeaderFiles;
}

bool ReflectionGenerator::IsInExceptionDirectory(const std::filesystem::path& Path)
{
    for (const auto& Part : Path)
    {
        for (const auto& Directory : ExceptionDirectories)
        {
            if (Part == Directory)
            {
                return true;
            }
        }
    }
    return false;
}

std::string ReflectionGenerator::GetFileName(const std::string& FilePath)
{
    const auto Index = FilePath.rfind("\\");
    return FilePath.substr(Index + 1, FilePath.size() - Index - 1);
}
