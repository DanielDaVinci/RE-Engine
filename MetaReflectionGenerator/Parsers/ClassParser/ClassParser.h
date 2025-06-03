#pragma once

#include <vector>

#include "MetaReflectionGenerator/Parsers/Parser.h"

class FunctionParser;
class PropertyParser;

class ClassParser : public Parser
{
public:
    bool Parse(CXCursor Cursor) override;
    bool CanParse(CXCursor Cursor) const override;
    void Generate() const;
    
    void SetSolutionPath(const std::string& InSolutionPath);
    
    static CXChildVisitResult VisitChildRecursive(CXCursor Cursor, CXCursor Parent, CXClientData ClientData);

protected:
    std::string FilePath;
    std::string SolutionPath;
    
    void FillFile(std::ofstream& File) const;

    static std::string GetFilePath(CXCursor Cursor);
    static std::string GetFileNameFromPath(const std::string& FullPath);
    
private:
    std::string ClassName;
    std::string ParentClassName;
    bool bIsStructure = false;
    std::vector<std::shared_ptr<PropertyParser>> Properties;
    std::vector<std::shared_ptr<FunctionParser>> Functions;
    
};
