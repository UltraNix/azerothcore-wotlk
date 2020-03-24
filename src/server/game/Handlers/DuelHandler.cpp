
#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player       = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog->outDebug(LOG_FILTER_PACKETIO, "WORLD: Received CMSG_DUEL_ACCEPTED");
    ;//sLog->outStaticDebug("Player 1 is: %u (%s)", player->GetGUIDLow(), player->GetName().c_str());
    ;//sLog->outStaticDebug("Player 2 is: %u (%s)", plTarget->GetGUIDLow(), plTarget->GetName().c_str());

    time_t now = time(nullptr);
    player->duel->startTimer = now;
    plTarget->duel->startTimer = now;

    bool ResetDone = false; // To prevent reset Cooldown's twice.

    if (sWorld->getBoolConfig(CONFIG_DUEL_MOD))
    {
        switch (player->GetAreaId())
        {
             case 12:   // Elwynn Forest
             case 14:   // Durotar
             case 1296: // Durotar
             case 4570: // Dalaran (Circle of Wills)
                 player->DuelMod();
                 plTarget->DuelMod();
                 ResetDone = true;
                 break;
             default:
                 break;
        }

        if (!ResetDone)
        {
            switch (plTarget->GetAreaId())
            {
                case 12:   // Elwynn Forest
                case 14:   // Durotar
                case 1296: // Durotar
                case 4570: // Dalaran (Circle of Wills)
                    player->DuelMod();
                    plTarget->DuelMod();
                    break;
                default:
                    break;
            }
        }
    }

    player->SendDuelCountdown(3000);
    plTarget->SendDuelCountdown(3000);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_DUEL_CANCELLED");
    uint64 guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    GetPlayer()->DuelComplete(DUEL_INTERRUPTED);
}
