
#ifndef SC_SUNWELL_CHEAT_H
#define SC_SUNWELL_CHEAT_H

#include "Common.h"
#include "SharedDefines.h"
#include "Language.h"
#include "Player.h"
#include "Chat.h"

#include <unordered_map>

enum SunwellCheck
{
    CHECK_DOS_OPCODE = 0,
    CHECK_CAST_ABUSE = 1,
    MAX_CHECK_TYPES
};

enum SunwellAction
{
    SUN_ACTION_LOG  = 0,
    SUN_ACTION_KICK = 1,
    SUN_ACTION_BAN  = 2
};

class SunwellCheatData
{
public:
    SunwellCheatData();

    void    buildCheatReport( uint32 amount, SunwellCheck type );

    void    clearCheatReport( SunwellCheck type );
    uint32  getCheaterRepors( SunwellCheck type );

    void    setCheatTimer( uint32 time, SunwellCheck type );
    time_t  getCheatTimer( SunwellCheck type );

protected:
    uint32 m_cheaterReports[ MAX_CHECK_TYPES ];
    time_t m_cheaterTimer[ MAX_CHECK_TYPES ];
};

class SunwellCheat
{
public:
    static SunwellCheat* instance();

    //////////////////
    // Cleanup
    void cleanupReports(Player* player);
    //////////////////
    // opCounter
    void buildOpcodeReport(Player* player, uint16 opCode);
    //////////////////
    // goldAbuse
    void buildCastReport(Player* player, uint32 spellId);

private:
    typedef std::unordered_map<uint32, SunwellCheatData> CheatersDataMap;
    CheatersDataMap m_cheaterPlayers;
};

#define sSunwellCheatMgr SunwellCheat::instance()

#endif