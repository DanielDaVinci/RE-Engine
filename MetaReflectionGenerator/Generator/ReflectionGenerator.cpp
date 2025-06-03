#include "ReflectionGenerator.h"

#include <direct.h>
#include <filesystem>
#include <fstream>
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

void ReflectionGenerator::CreateDirectoryIfNoExists(const std::string& Path)
{
    struct stat info;
    
    if (stat(Path.c_str(), &info) != 0)
    {
#ifdef _WIN32
        int result = _mkdir(Path.c_str());
#else
        int result = mkdir(path.c_str(), 0777);
#endif
        RCheckReturn(result == 0);
    }
    else if (!(info.st_mode & S_IFDIR))
    {
        std::cerr << "Path exists but is not a directory: " << Path << std::endl;
    }
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

void ReflectionGenerator::GenerateCommonFile() const
{
    std::cout << "------- GENERATED COMMON CLASS -------" << std::endl;
    
    const std::string GeneratedDirectoryPath = SolutionPath + GenerateDirectoryName + "\\";
    const std::string GeneratedFilePath = GeneratedDirectoryPath + "ReflectionCommon" + "." + GeneratedFileExtension;
    std::cout << "Generated File Path: " << GeneratedFilePath << std::endl;
    
    CreateDirectoryIfNoExists(GeneratedDirectoryPath);
    std::ofstream GeneratedFile(GeneratedFilePath, std::ios::trunc);
    RCheckReturn(GeneratedFile.is_open());
    
    GeneratedFile.close();
    
    std::cout << "-------------------------------" << std::endl;
}

// void ReflectionGenerator::FillCommonFile(std::ofstream& File) const
// {
//     File << "#pragma once" << std::endl;
//     File << 
// }

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
    
    std::shared_ptr<ClassParser> Parser = std::make_shared<ClassParser>();
    if (Parser->CanParse(Cursor))
    {
        Parser->SetSolutionPath(This->SolutionPath);
        Parser->Parse(Cursor);
        This->ClassParsers.push_back(Parser);
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
