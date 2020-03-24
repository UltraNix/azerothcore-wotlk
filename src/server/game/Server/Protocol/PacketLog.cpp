#include "PacketLog.h"
#include "ByteBuffer.h"
#include "WorldPacket.h"
#include "Config.h"

PacketLog::PacketLog() : _file(nullptr) { }

PacketLog::~PacketLog()
{
    if (_file)
        fclose(_file);

    _file = nullptr;
}

void PacketLog::Initialize(const std::string& account)
{
    std::string logsDir = sConfigMgr->GetStringDefault("PacketSniffLogsDir", "");

    if (!logsDir.empty())
        if ((logsDir.at(logsDir.length() - 1) != '/') && (logsDir.at(logsDir.length() - 1) != '\\'))
            logsDir.push_back('/');

    std::string logname = sConfigMgr->GetStringDefault("PacketLogFile", "");
    if (!logname.empty())
        _file = fopen((logsDir + account + "_" + std::to_string(time(nullptr)) + "_" + logname).c_str(), "wb");
}

void PacketLog::LogPacket(WorldPacket const& packet, Direction direction)
{
    ByteBuffer data(4 + 4 + 4 + 1 + packet.size());
    data << int32(packet.GetOpcode());
    data << int32(packet.size());
    data << uint32(time(nullptr));
    data << uint8(direction);

    for (uint32 i = 0; i < packet.size(); i++)
        data << packet[i];

    fwrite(data.contents(), 1, data.size(), _file);
    fflush(_file);
}
