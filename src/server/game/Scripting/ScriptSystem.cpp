

#include "ScriptSystem.h"
#include "ObjectMgr.h"
#include "DatabaseEnv.h"
#include "ScriptMgr.h"
#include "Creature.h"

SystemMgr* SystemMgr::instance()
{
    static SystemMgr instance;
    return &instance;
}

void SystemMgr::LoadScriptWaypoints()
{
    uint32 oldMSTime = getMSTime();

    // Drop Existing Waypoint list
    m_mPointMoveMap.clear();

    uint64 uiCreatureCount = 0;

    // Load Waypoints
    QueryResult result = WorldDatabase.Query("SELECT COUNT(entry) FROM script_waypoint GROUP BY entry");
    if (result)
        uiCreatureCount = result->GetRowCount();

    sLog->outString("TSCR: Loading Script Waypoints for " UI64FMTD " creature(s)...", uiCreatureCount);

    //                                     0       1         2           3           4           5
    result = WorldDatabase.Query("SELECT entry, pointid, location_x, location_y, location_z, waittime FROM script_waypoint ORDER BY pointid");

    if (!result)
    {
        sLog->outString(">> Loaded 0 Script Waypoints. DB table `script_waypoint` is empty.");
        sLog->outString();
        return;
    }

    uint32 count = 0;

    do
    {
        Field* pFields = result->Fetch();
        ScriptPointMove temp;

        temp.uiCreatureEntry   = pFields[0].GetUInt32();
        uint32 uiEntry         = temp.uiCreatureEntry;
        temp.uiPointId         = pFields[1].GetUInt32();
        temp.fX                = pFields[2].GetFloat();
        temp.fY                = pFields[3].GetFloat();
        temp.fZ                = pFields[4].GetFloat();
        temp.uiWaitTime        = pFields[5].GetUInt32();

        CreatureTemplate const* pCInfo = sObjectMgr->GetCreatureTemplate(temp.uiCreatureEntry);

        if (!pCInfo)
        {
            sLog->outErrorDb("TSCR: DB table script_waypoint has waypoint for non-existant creature entry %u", temp.uiCreatureEntry);
            continue;
        }

        if (!pCInfo->ScriptID)
            sLog->outErrorDb("TSCR: DB table script_waypoint has waypoint for creature entry %u, but creature does not have ScriptName defined and then useless.", temp.uiCreatureEntry);

        m_mPointMoveMap[uiEntry].push_back(temp);
        ++count;
    } while (result->NextRow());

    sLog->outString(">> Loaded %u Script Waypoint nodes in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void SystemMgr::LoadScriptSplineChains()
{
    uint32 oldMSTime = getMSTime();

    m_mSplineChainsMap.clear();

    //                                                     0       1        2             3               4
    QueryResult resultMeta = WorldDatabase.Query("SELECT entry, chainId, splineId, expectedDuration, msUntilNext FROM script_spline_chain_meta ORDER BY entry asc, chainId asc, splineId asc");
    //                                                  0       1         2       3   4  5  6
    QueryResult resultWP = WorldDatabase.Query("SELECT entry, chainId, splineId, wpId, x, y, z FROM script_spline_chain_waypoints ORDER BY entry asc, chainId asc, splineId asc, wpId asc");
    if (!resultMeta || !resultWP)
    {
        sLog->outString("Loaded spline chain data for 0 chains, consisting of 0 splines with 0 waypoints. DB tables `script_spline_chain_meta` and `script_spline_chain_waypoints` are empty.");
        sLog->outString();
    }
    else
    {
        uint32 chainCount = 0, splineCount = 0, wpCount = 0;
        do
        {
            Field* fieldsMeta = resultMeta->Fetch();
            uint32 entry = fieldsMeta[0].GetUInt32();
            uint8 chainId = fieldsMeta[1].GetUInt8(), splineId = fieldsMeta[2].GetUInt8();
            std::vector<SplineChainLink>& chain = m_mSplineChainsMap[{ entry, chainId }];

            if (splineId != chain.size())
            {
                sLog->outErrorDb("Creature #%u: Chain %u has orphaned spline %u, skipped.", entry, chainId, splineId);
                continue;
            }

            uint32 expectedDuration = fieldsMeta[3].GetUInt32(), msUntilNext = fieldsMeta[4].GetUInt32();
            chain.push_back(SplineChainLink(expectedDuration, msUntilNext));

            if (splineId == 0)
                ++chainCount;
            ++splineCount;
        } while (resultMeta->NextRow());

        do
        {
            Field* fieldsWP = resultWP->Fetch();
            uint32 entry = fieldsWP[0].GetUInt32();
            uint8 chainId = fieldsWP[1].GetUInt8(), splineId = fieldsWP[2].GetUInt8(), wpId = fieldsWP[3].GetUInt8();
            float posX = fieldsWP[4].GetFloat(), posY = fieldsWP[5].GetFloat(), posZ = fieldsWP[6].GetFloat();
            auto it = m_mSplineChainsMap.find({entry,chainId});
            if (it == m_mSplineChainsMap.end())
            {
                sLog->outErrorDb("Creature #%u has waypoint data for spline chain %u. No such chain exists - entry skipped.", entry, chainId);
                continue;
            }

            std::vector<SplineChainLink>& chain = it->second;
            if (splineId >= chain.size())
            {
                sLog->outErrorDb("Creature #%u has waypoint data for spline (%u,%u). The specified chain does not have a spline with this index - entry skipped.", entry, chainId, splineId);
                continue;
            }
            SplineChainLink& spline = chain[splineId];
            if (wpId != spline.Points.size())
            {
                sLog->outErrorDb("Creature #%u has orphaned waypoint data in spline (%u,%u) at index %u. Skipped.", entry, chainId, splineId, wpId);
                continue;
            }
            spline.Points.emplace_back(posX, posY, posZ);
            ++wpCount;
        } while (resultWP->NextRow());

        sLog->outString("Loaded spline chain data for %u chains, consisting of %u splines with %u waypoints in %u ms", chainCount, splineCount, wpCount, GetMSTimeDiffToNow(oldMSTime));
        sLog->outString();
    }
}

ScriptPointVector const* SystemMgr::GetPointMoveList(uint32 creatureEntry) const
{
    PointMoveMap::const_iterator itr = m_mPointMoveMap.find(creatureEntry);

    if (itr == m_mPointMoveMap.end())
        return nullptr;

    return &itr->second;
}

std::vector<SplineChainLink> const* SystemMgr::GetSplineChain(Creature const* who, uint16 id) const
{
    return GetSplineChain(who->GetEntry(), id);
}

std::vector<SplineChainLink> const* SystemMgr::GetSplineChain(uint32 entry, uint16 chainId) const
{
    auto it = m_mSplineChainsMap.find({ entry, chainId });
    if (it == m_mSplineChainsMap.end())
        return nullptr;
    return &it->second;
}
