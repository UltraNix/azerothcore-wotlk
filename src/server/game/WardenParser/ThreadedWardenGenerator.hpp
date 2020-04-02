#pragma once

#include "WardenDefines.hpp"

class ThreadedWardenGenerator
{
public:
    ThreadedWardenGenerator() = default;

    void                Initialize(size_t threadsCount);
    void                Shutdown();

    AsyncLuaCodeResult  RequestLuaCode(RequestData data);

protected:
    void                PrepareLuaCode(LuaRequest& request);

    LuaRequestQueue    m_queue;
    LuaGeneratorPool   m_pool;

    void ReplaceAll(std::string& source, const std::string& from, const std::string& to);
};

ThreadedWardenGenerator & GetLuaGenerator();

