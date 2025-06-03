#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "clang-c/Index.h"

class ClassParser;

class ReflectionGenerator
{
public:
    static inline std::string GenerateDirectoryName = "Generated";
    static inline std::string GeneratedFileExtension = "generated.h";
    
    void Generate(const std::string& InSolutionPath);

    static void CreateDirectoryIfNoExists(const std::string& Path);

protected:
    void ParseFiles();
    void ParseFile(const std::string& InFilePath);
    void GenerateCommonFile() const;
    // void FillCommonFile(std::ofstream& File) const;
    void GenerateFiles() const;
    
    static CXChildVisitResult VisitRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData);
    static std::vector<std::string> FindHeaderFiles(const std::string& InDirectory);
    static bool IsInExceptionDirectory(const std::filesystem::path& Path);

    static std::string GetFileName(const std::string& FilePath);
    
private:
    static inline std::vector<std::string> ExceptionDirectories = { "ThirdParty", "Generated" };
    
    std::string SolutionPath;
    std::vector<std::shared_ptr<ClassParser>> ClassParsers;
    
};
