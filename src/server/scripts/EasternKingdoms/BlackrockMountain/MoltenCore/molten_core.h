/*
 * Copyright (C) 
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEF_MOLTEN_CORE_H
#define DEF_MOLTEN_CORE_H

enum Encounters
{
    BOSS_LUCIFRON                   = 0,
    BOSS_MAGMADAR                   = 1,
    BOSS_GEHENNAS                   = 2,
    BOSS_GARR                       = 3,
    BOSS_SHAZZRAH                   = 4,
    BOSS_BARON_GEDDON               = 5,
    BOSS_SULFURON_HARBINGER         = 6,
    BOSS_GOLEMAGG_THE_INCINERATOR   = 7,
    BOSS_MAJORDOMO_EXECUTUS         = 8,
    BOSS_RAGNAROS                   = 9,
    MAX_ENCOUNTER,
};

enum Actions
{
    ACTION_START_RAGNAROS       = 0,
    ACTION_START_RAGNAROS_ALT   = 1,
};

Position const RagnarosSummonPos = { 838.510f, -829.840f, -232.000f, 2.00000f };
Position const MajordomoDefeatPos = { 758.089f, -1176.71f, -118.640f };
Position const SummonPositions[10] =
{
    { 758.089f, -1176.71f, -118.640f, 3.12414f },
    { 737.945f, -1156.48f, -118.945f, 4.46804f },
    { 752.520f, -1191.02f, -118.218f, 2.49582f },
    { 752.953f, -1163.94f, -118.869f, 3.70010f },
    { 738.814f, -1197.40f, -118.018f, 1.83260f },
    { 746.939f, -1194.87f, -118.016f, 2.21657f },
    { 747.132f, -1158.87f, -118.897f, 4.03171f },
    { 757.116f, -1170.12f, -118.793f, 3.40339f },
    { 755.910f, -1184.46f, -118.449f, 2.80998f }
};
Position const MajordomoPath[4] = 
{
    { 838.790771f, -810.536194f, -229.509171f },
    { 834.175598f, -811.452026f, -228.992126f },
    { 831.079590f, -816.023193f, -229.023270f }
};

enum Creatures
{
    NPC_LUCIFRON                    = 12118,
    NPC_MAGMADAR                    = 11982,
    NPC_GEHENNAS                    = 12259,
    NPC_GARR                        = 12057,
    NPC_SHAZZRAH                    = 12264,
    NPC_BARON_GEDDON                = 12056,
    NPC_SULFURON_HARBINGER          = 12098,
    NPC_GOLEMAGG_THE_INCINERATOR    = 11988,
    NPC_MAJORDOMO_EXECUTUS          = 12018,
    NPC_RAGNAROS                    = 11502,
    NPC_FLAMEWAKER_HEALER           = 11663,
    NPC_FLAMEWAKER_ELITE            = 11664,
    NPC_SON_OF_FLAME                = 12143,                  
    NPC_FLAME_OF_RAGNAROS           = 13148,
};

enum GameObjects
{
    GO_CACHE_OF_THE_FIRELORD        = 179703,
    GO_LAVA_STEAM                   = 178107,
};

enum Data
{
    DATA_RAGNAROS_ADDS  = 0,
};

#endif
