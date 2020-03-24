
#ifndef _MMAP_FACTORY_H
#define _MMAP_FACTORY_H

#include "Define.h"
#include "MMapManager.h"
#include "DetourAlloc.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "Map.h"

#include <unordered_map>

namespace MMAP
{
    enum MMAP_LOAD_RESULT
    {
        MMAP_LOAD_RESULT_ERROR,
        MMAP_LOAD_RESULT_OK,
        MMAP_LOAD_RESULT_IGNORED,
    };

    // static class
    // holds all mmap global data
    // access point to MMapManager singleton
    class MMapFactory
    {
        public:
            static MMapManager* createOrGetMMapManager();
            static void clear();
            static bool IsPathfindingEnabled(const Map* map, bool force = false);
            static void InitializeDisabledMaps();
            static bool forbiddenMaps[1000];
    };
}

#endif

