#pragma once

#include <chrono>
#include <vector>
#include <thread>

#include "Threading/SyncQueue.hpp"

namespace WardenParserWin
{
    struct Requestee
    {
        uint32_t accountId;
        uint64 characterGUID;
    };

    using ParseRequest = std::pair<Requestee, std::string >;
    using ParseGeneratorPool = std::vector< std::thread >;
    using ParseRequestQueue = Threading::SyncQueue< ParseRequest >;

    class ThreadedWardenParser
    {
    public:
        ThreadedWardenParser();

        void Initialize(size_t /*threadsCount*/);

        void Shutdown();

        void AddMessage(Requestee /*who*/, std::string /*message*/);

    protected:
        void ParseMessage(ParseRequest request);
        void SplitAddonMessage(std::string& /*_message*/, std::string& /*_prefix*/, std::string& /*_body*/, uint32 /*tabPosition*/, uint32 /*prefixSize*/);
        bool ParseDebugStackMessage(std::string _message);

        std::atomic_bool    m_shutdown;

        ParseRequestQueue    m_queue;
        ParseGeneratorPool   m_pool;
    };

    ThreadedWardenParser& GetWardenParser();
}