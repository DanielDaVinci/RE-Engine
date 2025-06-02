#include "DebugLog/Public/Check/Check.h"
#include "Generator/ReflectionGenerator.h"

int main (int argc, char** argv)
{
    RCheckReturn(argc >= 2, -1);
    
    const std::string SolutionPath = argv[1];
    RCheckReturn(!SolutionPath.empty(), -1);
    
    auto Generator = std::make_shared<ReflectionGenerator>();
    RCheckReturn(Generator, -1);

    Generator->Generate(SolutionPath);

    return 0;
}