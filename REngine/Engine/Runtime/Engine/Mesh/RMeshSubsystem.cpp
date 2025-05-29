#include "RMeshSubsystem.h"

#include "RMesh.h"

std::shared_ptr<RMeshSubsystem> RMeshSubsystem::Get()
{
    return GetSubsystem<RMeshSubsystem>();
}

std::shared_ptr<RMesh> RMeshSubsystem::GetMesh(const std::string& MeshPath)
{
    if (!LoadedMeshes.contains(MeshPath))
    {
        const std::shared_ptr<RMesh> LoadedMesh = NewObject<RMesh>();
        RCheckReturn(LoadedMesh, nullptr);
        LoadedMesh->LoadMesh(MeshPath);
        
        LoadedMeshes[MeshPath] = LoadedMesh;
    }

    return LoadedMeshes[MeshPath];
}
