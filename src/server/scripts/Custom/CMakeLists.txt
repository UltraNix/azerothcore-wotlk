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
  
  Custom/Transmog/Transmog.cpp
  Custom/cs_custom.cpp
  Custom/item_custom.cpp
  Custom/npcs_custom.cpp
  Custom/spell_custom.cpp

# Disabled
# Custom/OldScarletMonastery/boss_dessembrae.cpp
# Custom/OldScarletMonastery/boss_javier_voidbringer.cpp
# Custom/OldScarletMonastery/boss_madantul_rada.cpp
# Custom/OldScarletMonastery/boss_mazin_soulstealer.cpp
# Custom/OldScarletMonastery/boss_reast.cpp
# Custom/OldScarletMonastery/instance_old_scarlet_monastery.cpp
# Custom/OldScarletMonastery/old_scarlet_Monastery.cpp
# Custom/OldScarletMonastery/old_scarlet_monastery.h

)

message("  -> Prepared: Custom")
