#ifndef TRINITY_PACKETLOG_H
#define TRINITY_PACKETLOG_H

#include "Common.h"

enum Direction
{
    CLIENT_TO_SERVER,
    SERVER_TO_CLIENT
};

class WorldPacket;

class PacketLog
{
public:
    PacketLog();
    ~PacketLog();

    void Initialize(const std::string& /*account*/);
    bool CanLogPacket() const { return (_file != nullptr); }
    void LogPacket(WorldPacket const& packet, Direction direction);

private:
    FILE* _file;
};

#endif