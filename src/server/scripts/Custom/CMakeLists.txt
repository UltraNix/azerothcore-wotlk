# Copyright (C) 
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/BattleForUndercity/battle_for_undercity_alliance.cpp
  Custom/BattleForUndercity/battle_for_undercity_horde.cpp
  Custom/BattleForUndercity/battle_for_undercity.cpp
  Custom/BattleForUndercity/worldzone_trisfal_glades.cpp
  Custom/BattleForUndercity/battle_for_undercity.h

  Custom/OldScarletMonastery/boss_dessembrae.cpp
  Custom/OldScarletMonastery/boss_javier_voidbringer.cpp
  Custom/OldScarletMonastery/boss_madantul_rada.cpp
  Custom/OldScarletMonastery/boss_mazin_soulstealer.cpp
  Custom/OldScarletMonastery/boss_reast.cpp
  Custom/OldScarletMonastery/instance_old_scarlet_monastery.cpp
  Custom/OldScarletMonastery/old_scarlet_Monastery.cpp
  Custom/OldScarletMonastery/old_scarlet_monastery.h
  
  Custom/HazardCave/Lottery.cpp
  Custom/HazardCave/Lottery.h
  Custom/HazardCave/npc_hazard.cpp
  Custom/HazardCave/gambling.cpp
  
  Custom/Transmog/Transmog.cpp
)

message("  -> Prepared: Custom")
