#pragma once

#include "WardenDefines.hpp"
#include <mutex>

namespace WardenParserWin
{
    class ThreadedWardenParser
    {
    public:
        ThreadedWardenParser();

        void Initialize(size_t /*threadsCount*/);

        void Shutdown();

        void AddMessage(Requestee /*who*/, std::string /*message*/);
        void GrabAllReports(World* /*world*/);

    protected:
        void ParseMessage(ParseRequest request);
        void SplitAddonMessage(std::string& /*_message*/, std::string& /*_prefix*/, std::string& /*_body*/, uint32 /*tabPosition*/, uint32 /*prefixSize*/);
        bool ParseDebugStackMessage(std::string _message);

        std::atomic_bool    m_shutdown;

        ParseRequestQueue    m_queue;
        ParseGeneratorPool   m_pool;
    private:
        std::unordered_map<uint64, std::vector<WardenLuaResult>> _parseResultStore;
        std::mutex resultsLock;
    };

    ThreadedWardenParser& GetWardenParser();
}