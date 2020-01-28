#include "MovementInfo.h"
#include "Log.h"

#include <ctime>

void MovementInfo::OutDebug()
{
    sLog->outString("MOVEMENT INFO");
    sLog->outString("guid " UI64FMTD, guid);
    sLog->outString("flags %u", flags);
    sLog->outString("flags2 %u", flags2);
    sLog->outString("time %u current time " UI64FMTD "", flags2, uint64(::time(nullptr)));
    sLog->outString("position: `%s`", pos.ToString().c_str());
    if (flags & MOVEMENTFLAG_ONTRANSPORT)
    {
        sLog->outString("TRANSPORT:");
        sLog->outString("guid: " UI64FMTD, transport.guid);
        sLog->outString("position: `%s`", transport.pos.ToString().c_str());
        sLog->outString("seat: %i", transport.seat);
        sLog->outString("time: %u", transport.time);
        if (flags2 & MOVEMENTFLAG2_INTERPOLATED_MOVEMENT)
            sLog->outString("time2: %u", transport.time2);
    }

    if ((flags & (MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_FLYING)) || (flags2 & MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING))
        sLog->outString("pitch: %f", pitch);

    sLog->outString("fallTime: %u", fallTime);
    if (flags & MOVEMENTFLAG_FALLING)
        sLog->outString("j_zspeed: %f j_sinAngle: %f j_cosAngle: %f j_xyspeed: %f", jump.zspeed, jump.sinAngle, jump.cosAngle, jump.xyspeed);

    if (flags & MOVEMENTFLAG_SPLINE_ELEVATION)
        sLog->outString("splineElevation: %f", splineElevation);
}
