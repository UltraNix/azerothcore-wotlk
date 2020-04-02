#pragma once

#include "WardenDefines.hpp"

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class World;

namespace WardenParserWin
{
    class ThreadedWardenParser
    {
    public:
        ThreadedWardenParser() = default;

        void Initialize(size_t /*threadsCount*/);
        void Shutdown();

        void AddMessage(Requestee /*who*/, std::string /*message*/);
        void GrabAllReports(World* /*world*/);

    protected:
        void ParseMessage(ParseRequest request);
        void SplitAddonMessage(std::string& /*_message*/, std::string& /*_prefix*/, std::string& /*_body*/, uint32 /*tabPosition*/, uint32 /*prefixSize*/);
        bool ParseDebugStackMessage(std::string _message);

        ParseRequestQueue    m_queue;
        ParseGeneratorPool   m_pool;
    private:
        std::unordered_map<uint64, std::vector<WardenLuaResult>> _parseResultStore;
        std::mutex resultsLock;
    };

    ThreadedWardenParser& GetWardenParser();
}
