
#ifndef SUNWELLCORE_WORLDPACKET_H
#define SUNWELLCORE_WORLDPACKET_H

#include "Common.h"
#include "ByteBuffer.h"

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket()                                       : ByteBuffer(0), m_opcode(0)
        {
        }
        explicit WorldPacket(uint16 opcode, size_t res=200) : ByteBuffer(res), m_opcode(opcode) { }
                                                            // copy constructor
        WorldPacket(const WorldPacket &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode)
        {
        }

        WorldPacket & operator=( const WorldPacket & buf ) noexcept
        {
            ByteBuffer::operator=( buf );
            m_opcode = buf.m_opcode;
            return *this;
        }

        WorldPacket( WorldPacket && buf ) noexcept
            : ByteBuffer( std::move( buf ) )
            , m_opcode( buf.m_opcode)
        {
        }

        WorldPacket & operator=( WorldPacket && buf ) noexcept
        {
            ByteBuffer::operator=( std::move( buf ) );
            m_opcode = buf.m_opcode;
            return *this;
        }

        void Initialize(uint16 opcode, size_t newres=200)
        {
            clear();
            _storage.reserve(newres);
            m_opcode = opcode;
        }

        uint16 GetOpcode() const { return m_opcode; }
        void SetOpcode(uint16 opcode) { m_opcode = opcode; }

    protected:
        uint16 m_opcode;
};
#endif

