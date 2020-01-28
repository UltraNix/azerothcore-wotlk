#pragma once

#include "Define.h"

#include "G3D/Vector3.h"

#include <string>

//! Quake3 fast inverse square root
//! https://en.wikipedia.org/wiki/Fast_inverse_square_root
inline float FastSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;              // evil floating point bit level hacking
    i = 0x5f375a86 - (i >> 1);      // what the fuck?
    x = *(float*)&i;                // convert bits back to float
    x = x * (1.5f - xhalf * x*x);   // Newton step, repeating increases accuracy
    return 1.0f / x;
}

class WorldObject;

struct Position
{
    Position(float x = 0, float y = 0, float z = 0, float o = 0)
        : m_positionX(x), m_positionY(y), m_positionZ(z), m_orientation(NormalizeOrientation(o)) { }

    operator G3D::Vector3() const
    {
        return { m_positionX, m_positionY, m_positionZ };
    }

    struct PositionXYZStreamer
    {
        explicit PositionXYZStreamer(Position& pos) : m_pos(&pos) {}
        Position* m_pos;
    };

    struct PositionXYZOStreamer
    {
        explicit PositionXYZOStreamer(Position& pos) : m_pos(&pos) {}
        Position* m_pos;
    };

    float m_positionX;
    float m_positionY;
    float m_positionZ;
    float m_orientation;

    //! Doesn't check for orientation changes
    bool operator==(Position const &a);

    inline bool operator!=(Position const &a)
    {
        return !(operator==(a));
    }

    void Relocate(float x, float y)
        { m_positionX = x; m_positionY = y;}
    void Relocate(float x, float y, float z)
        { m_positionX = x; m_positionY = y; m_positionZ = z; }
    void Relocate(float x, float y, float z, float orientation)
        { m_positionX = x; m_positionY = y; m_positionZ = z; m_orientation = orientation; }
    void Relocate(const Position &pos)
        { m_positionX = pos.m_positionX; m_positionY = pos.m_positionY; m_positionZ = pos.m_positionZ; m_orientation = pos.m_orientation; }
    void Relocate(const Position* pos)
        { m_positionX = pos->m_positionX; m_positionY = pos->m_positionY; m_positionZ = pos->m_positionZ; m_orientation = pos->m_orientation; }
    void RelocateOffset(const Position &offset);
    void SetOrientation(float orientation)
        { m_orientation = orientation; }

    inline float GetPositionX() const { return m_positionX; }
    inline float GetPositionY() const { return m_positionY; }
    inline float GetPositionZ() const { return m_positionZ; }
    inline float GetOrientation() const { return m_orientation; }

    inline const Position& GetPosition() const { return *this; }

    void GetPosition(float &x, float &y) const
        { x = m_positionX; y = m_positionY; }
    void GetPosition(float &x, float &y, float &z) const
        { x = m_positionX; y = m_positionY; z = m_positionZ; }
    void GetPosition(float &x, float &y, float &z, float &o) const
        { x = m_positionX; y = m_positionY; z = m_positionZ; o = m_orientation; }
    void GetPosition(Position* pos) const
    {
        if (pos)
            pos->Relocate(m_positionX, m_positionY, m_positionZ, m_orientation);
    }

    Position::PositionXYZStreamer PositionXYZStream()
    {
        return PositionXYZStreamer(*this);
    }
    Position::PositionXYZOStreamer PositionXYZOStream()
    {
        return PositionXYZOStreamer(*this);
    }

    bool IsPositionValid() const;

    float GetExactDist2dSq(float x, float y) const
        { float dx = m_positionX - x; float dy = m_positionY - y; return dx*dx + dy*dy; }
    float GetExactDist2d(const float x, const float y) const
    {
        return FastSqrt(GetExactDist2dSq(x, y));
    }
    float GetExactDist2dSq(const Position* pos) const
        { float dx = m_positionX - pos->m_positionX; float dy = m_positionY - pos->m_positionY; return dx*dx + dy*dy; }
    float GetExactDist2d(const Position* pos) const
        { return FastSqrt(GetExactDist2dSq(pos)); }
    float GetExactDistSq(float x, float y, float z) const
        { float dz = m_positionZ - z; return GetExactDist2dSq(x, y) + dz*dz; }
    float GetExactDist(float x, float y, float z) const
        { return FastSqrt(GetExactDistSq(x, y, z)); }
    float GetExactDistSq(const Position* pos) const
        { float dx = m_positionX - pos->m_positionX; float dy = m_positionY - pos->m_positionY; float dz = m_positionZ - pos->m_positionZ; return dx*dx + dy*dy + dz*dz; }
    float GetExactDist(const Position* pos) const
        { return FastSqrt(GetExactDistSq(pos)); }

    inline float GetExactDist2dSq(Position const& pos) const
    {
        return GetExactDist2dSq(&pos);
    }

    inline float GetExactDistSq(Position const& pos) const
    {
        return GetExactDistSq(&pos);
    }
    void GetPositionOffsetTo(const Position & endPos, Position & retOffset) const;

    float GetAngle(const Position* pos) const;
    float GetAngle(float x, float y) const;
    float GetRelativeAngle(const Position* pos) const
        { return GetAngle(pos) - m_orientation; }
    float GetRelativeAngle(float x, float y) const { return GetAngle(x, y) - m_orientation; }
    void GetSinCos(float x, float y, float &vsin, float &vcos) const;

    bool IsInDist2d(float x, float y, float dist) const
        { return GetExactDist2dSq(x, y) < dist * dist; }
    bool IsInDist2d(const Position* pos, float dist) const
        { return GetExactDist2dSq(pos) < dist * dist; }
    bool IsInDist(float x, float y, float z, float dist) const
        { return GetExactDistSq(x, y, z) < dist * dist; }
    bool IsInDist(const Position* pos, float dist) const
        { return GetExactDistSq(pos) < dist * dist; }

    bool IsWithinBox(const Position& center, float xradius, float yradius, float zradius) const;
    bool HasInArc(float arcangle, const Position* pos, float targetRadius = 0.0f) const;
    bool HasInLine(WorldObject const* target, float width) const;
    std::string ToString() const;

    static float RandomOrientation()
    {
        return frand(0.0f, 2 * M_PI);
    }

    // modulos a radian orientation to the range of 0..2PI
    static float NormalizeOrientation(float o)
    {
        // fmod only supports positive numbers. Thus we have
        // to emulate negative numbers
        if (o < 0)
        {
            float mod = o *-1;
            mod = fmod(mod, 2.0f * static_cast<float>(M_PI));
            mod = -mod + 2.0f * static_cast<float>(M_PI);
            return mod;
        }
        return fmod(o, 2.0f * static_cast<float>(M_PI));
    }
};

ByteBuffer& operator>>(ByteBuffer& buf, Position::PositionXYZOStreamer const& streamer);
ByteBuffer& operator<<(ByteBuffer& buf, Position::PositionXYZStreamer const& streamer);
ByteBuffer& operator>>(ByteBuffer& buf, Position::PositionXYZStreamer const& streamer);
ByteBuffer& operator<<(ByteBuffer& buf, Position::PositionXYZOStreamer const& streamer);


#define MAPID_INVALID 0xFFFFFFFF

class WorldLocation : public Position
{
public:
    explicit WorldLocation(uint32 _mapid = MAPID_INVALID, float _x = 0, float _y = 0, float _z = 0, float _o = 0)
        : m_mapId(_mapid) { Relocate(_x, _y, _z, _o); }
    WorldLocation(const WorldLocation &loc) { WorldRelocate(loc); }

    void WorldRelocate(const WorldLocation &loc)
    {
        m_mapId = loc.GetMapId();
        Relocate(loc);
    }

    uint32 GetMapId() const
    {
        return m_mapId;
    }

    WorldLocation GetWorldLocation() const
    {
        return *this;
    }

    uint32 m_mapId;
};

