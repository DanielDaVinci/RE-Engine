#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Subsystem/RSubsystem.h"

class RMeshSubsystem : public RSubsystem
{
public:
    using RSubsystem::RSubsystem;
    
    static std::shared_ptr<RMeshSubsystem> Get();

    std::shared_ptr<RMesh> GetMesh(const std::string& MeshPath);
    
private:
    std::unordered_map<std::string, std::shared_ptr<RMesh>> LoadedMeshes;
    
};
