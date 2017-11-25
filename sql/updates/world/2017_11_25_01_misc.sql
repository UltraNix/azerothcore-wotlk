-- add CREATURE_FLAG_EXTRA_NO_XP_AT_KILL to some low health NPCs
UPDATE `creature_template` SET `flags_extra`=`flags_extra` | 0x00000040 WHERE `entry` IN (
    11446, -- Gordok Spirit
    4196, -- Silithid Swarm
    5409, -- Harvester Swarm
    27866, -- Honeybee
    2462, -- Flesh Eating Worm
    2475, -- Sloth
    2479, -- Sludge
    2540, -- Dalaran Serpent
    2623, -- Spirit of Old
    7768, -- Witherbark Bloodling
    7769, -- Hazzali Parasite
    10925, -- Rotting Worm
    21420, -- Corrupt Water Totem
    21703, -- Corrupt Fire Totem
    21704, -- Corrupt Earth Totem
    21705, -- Corrupt Air Totem
    5779, -- Summoned Viper
    28938, -- Charged Sentry Totem
    22486, -- Greater Earthbind Totem
    34116, -- Shadowy Fish
    2630, -- Earthbind Totem
    2667, -- Ward of Laze
    3968, -- Sentry Totem
    6066, -- Earthgrab Totem
    8510, -- Atal'ai Totem
    14370, -- Cadaverous Worm
    17887, -- Void Critter
    21073, -- Enraged Earthen Soul
    21097, -- Enraged Fiery Soul
    21109, -- Enraged Watery Soul
    21116, -- Enraged Airy Soul
    22285, -- Draenei Tomb Guardian
    19637, -- Draenei Earth Totem
    24745, -- Pure Energy
    30391, -- Healthy Mushroom
    30435, -- Poisonous Mushroom
    31273, -- Dying Berserker
    31304, -- Dying Soldier
    31461, -- Healthy Mushroom (1)
    31462, -- Poisonous Mushroom (1)
    35255, -- Death Shade
    37750, -- Dwarf Earth Totem
    37767, -- Orc Earth Totem
    37768, -- Troll Earth Totem
    40187, -- Vanira's Sentry Totem
    30178, -- Ahn'kahar Swarmer
    30338, -- Ahn'kahar Swarmer
    20665, -- Voidwalker Summoner (1)
    12381, -- Ley Sprite
    12382, -- Mana Sprite
    31447, -- Ahn'kahar Swarmer (1)
    31448, -- Ahn'kahar Swarmer  (1)
    4958, -- Haunting Spirit
    19833, -- Venomous Snake
    19921, -- Viper
    14761, -- Creeping Doom
    24338, -- Amani Snake
    25113, -- Crafty Snake
    24279, -- Animated Plague Slime
    24757, -- Fjord Rock Snake
    29444, -- Drakkari Snake
    29637, -- Crafty Snake
    32778, -- Crafty Snake (1)
    28735, -- Skittering Swarmer
    32593, -- Skittering Swarmer
    4952, -- Theramore Combat Dummy
    30268, -- Webbed Crusader
    30273, -- Webbed Crusader
    22487, -- Greater Poison Cleansing Totem
    31614, -- Skittering Swarmer (1)
    14486, -- Scourge Footsoldier
    6107, -- Shade
    29209, -- Carrion Beetle
    29364, -- Void Sentry
    2887, -- Prismatic Exile
    3527, -- Healing Stream Totem
    3573, -- Mana Spring Totem
    3906, -- Healing Stream Totem II
    3907, -- Healing Stream Totem III
    3908, -- Healing Stream Totem IV
    3909, -- Healing Stream Totem V
    4377, -- Darkmist Hatchling
    5873, -- Stoneskin Totem
    5874, -- Strength of Earth Totem
    5913, -- Tremor Totem
    5919, -- Stoneskin Totem II
    5920, -- Stoneskin Totem III
    5921, -- Strength of Earth Totem II
    5922, -- Strength of Earth Totem III
    5923, -- Poison Cleansing Totem
    5924, -- Cleansing Totem
    5925, -- Grounding Totem
    5926, -- Frost Resistance Totem
    5927, -- Fire Resistance Totem
    5929, -- Magma Totem
    6016, -- Elemental Protection Totem
    6017, -- Lava Spout Totem
    7366, -- Stoneskin Totem IV
    7367, -- Stoneskin Totem V
    7368, -- Stoneskin Totem VI
    7403, -- Strength of Earth Totem IV
    7412, -- Frost Resistance Totem II
    7413, -- Frost Resistance Totem III
    7414, -- Mana Spring Totem II
    7415, -- Mana Spring Totem III
    7416, -- Mana Spring Totem IV
    7424, -- Fire Resistance Totem II
    7425, -- Fire Resistance Totem III
    7464, -- Magma Totem II
    7465, -- Magma Totem III
    7466, -- Magma Totem IV
    7467, -- Nature Resistance Totem
    7468, -- Nature Resistance Totem II
    7469, -- Nature Resistance Totem III
    7486, -- Grace of Air Totem
    7487, -- Grace of Air Totem II
    9687, -- Windwall Totem
    9688, -- Windwall Totem II
    9689, -- Windwall Totem III
    10467, -- Mana Tide Totem
    10577, -- Crypt Scarab
    11100, -- Mana Tide Totem II
    11101, -- Mana Tide Totem III
    14663, -- Corrupted Stoneskin Totem VI
    14664, -- Corrupted Healing Stream Totem V
    15304, -- Ancient Mana Spring Totem
    15363, -- Spirit Totem
    15447, -- Wrath of Air Totem
    15463, -- Grace of Air Totem III
    15464, -- Strength of Earth Totem V
    15470, -- Stoneskin Totem VII
    15474, -- Stoneskin Totem VIII
    15479, -- Strength of Earth Totem VI
    15484, -- Magma Totem V
    15487, -- Fire Resistance Totem IV
    15489, -- Mana Spring Totem V
    15492, -- Windwall Totem IV
    15803, -- Tranquil Air Totem
    16903, -- Blistering Oozeling
    17987, -- Strength of Earth
    18176, -- Tainted Earthgrab Totem
    18177, -- Tainted Stoneskin Totem
    18235, -- Corrupted Healing Stream Totem
    18236, -- Corrupted Air Totem
    19225, -- Strength of the Storm Totem
    19440, -- Eye of Grillok
    20479, -- Unstable Shroom
    21134, -- Eye of the Citadel
    21331, -- Thorny Growth
    21992, -- Strength of Earth Totem
    22134, -- Shadowmoon Eye of Kilrogg
    22282, -- Witness of Doom
    22369, -- Dread Relic Thrall
    15486, -- Frost Resistance Totem IV
    15488, -- Healing Stream Totem VI
    15490, -- Nature Resistance Totem IV
    17061, -- Mana Tide Totem IV
    17967, -- Crypt Scarab
    18178, -- Tainted Fire Totem
    18691, -- Shadow Totem
    19638, -- Draenei Water Totem
    19639, -- Draenei Air Totem
    21994, -- Stoneskin Totem
    19430, -- Test Elemental Totem
    23206, -- Akkarai Hatchling
    23366, -- Test Shroom
    24133, -- Ancient Grimtotem Spirit Guide
    25731, -- Ancient Grimtotem Spirit Wolf
    26111, -- Grimtotem Spirit Wolf
    31186, -- Mana Spring Totem VI
    24045, -- Water Spirit Totem
    24219, -- Baby Riven Widow
    24339, -- Scarlet Growth
    25284, -- Nerub'ar Victim
    25423, -- Infested Victim
    27556, -- Mindless Ghoul
    27712, -- Mindless Ghoul
    27737, -- Risen Zombie
    27909, -- Darkweb Victim
    30647, -- Strength of Earth Totem VII
    31129, -- Strength of Earth Totem VIII
    31166, -- Magma Totem VI
    31167, -- Magma Totem VII
    31168, -- V
    31169, -- Fire Resistance Totem V
    31170, -- Fire Resistance Totem VI
    31171, -- Frost Resistance Totem V
    31172, -- Frost Resistance Totem VI
    31173, -- Nature Resistance Totem V
    31174, -- Nature Resistance Totem VI
    31175, -- Stoneskin Totem IX
    31176, -- Stoneskin Totem X
    31181, -- Healing Stream Totem VII
    31182, -- Healing Stream Totem VIII
    31185, -- Healing Stream Totem IX
    31189, -- Mana Spring Totem VII
    31190, -- Mana Spring Totem VIII
    32820, -- Wild Turkey
    32956, -- Lonely Turkey
    34686, -- Healing Stream Totem
    37810, -- Healing Stream Totem
    36542, -- Unstable Healing Stream Totem
    36556, -- Unstable Wrath of Air Totem
    36550, -- Unstable Stoneskin Totem
    37749, -- Dwarf Air Totem
    37752, -- Dwarf Water Totem
    37766, -- Orc Air Totem
    37769, -- Troll Air Totem
    37772, -- Orc Water Totem
    37773, -- Troll Water Totem
    38180, -- Cleansing Totem
    31208, -- Risen Zombie (1)
    22474, -- Unstable Fel-Imp
    22379, -- Serpentshrine Parasite
    28630, -- Blood Maggot
    2946, -- Puppet of Helcular
    5781, -- Silithid Creeper Egg
    6386, -- Ward of Zanzil
    7785, -- Ward of Zum'rah
    7849, -- Mobile Alert System
    7915, -- Walking Bomb
    9496, -- Gorishi Egg
    10383, -- Broken Cadaver
    10388, -- Spiteful Phantom
    10389, -- Wrath Phantom
    10411, -- Eye of Naxxramas
    10482, -- Risen Lackey
    12276, -- Hive'Zora Egg
    14386, -- Wandering Eye of Kilrogg
    14434, -- Alarm-o-Bot
    14884, -- Parasitic Serpent
    15546, -- Hive'Zara Swarmer
    17680, -- Webbed Creature
    18372, -- Rough Stone Statue
    18734, -- Coarse Stone Statue
    18735, -- Heavy Stone Statue
    18736, -- Solid Stone Statue
    18737, -- Dense Stone Statue
    20214, -- Arakkoa Egg
    20805, -- Void Waste Globule
    20806, -- Seeping Sludge Globule
    21185, -- Nether Whelp Egg
    21265, -- Parasitic Fleshling
    21306, -- Cursed Scarab
    21428, -- Corrupted Water Elemental
    21435, -- Shadow Horror
    21459, -- Wyrmcult Dragon Egg
    21706, -- Corrupted Fire Elemental
    21707, -- Corrupted Air Elemental
    21708, -- Corrupted Earth Elemental
    22315, -- Deathforge Mine
    22355, -- Netherweb Victim
    14635, -- Sleepy Dark Iron Worker
    16286, -- Spore
    17706, -- Felsteel Boar
    18738, -- Primal Stone Statue
    23826, -- Creeping Flames
    24210, -- Riven Widow Cocoon
    25293, -- Nerub'ar Egg Sac
    25295, -- Nerub'ar Swarmer
    25377, -- Brittle Skeleton
    25422, -- Mystical Webbing
    25444, -- Magmoth Fire Totem
    25534, -- En'kilah Blood Globe
    26086, -- Transport Orb
    27604, -- Frail Construct
    28104, -- Enraged Skeleton
    28413, -- Nerubian Cocoon
    28524, -- Worn Bloodworm
    28948, -- Malmortis
    29272, -- Dwarven Golem
    30110, -- Hungry Penguin
    31251, -- Shadow Vault Skirmisher
    31257, -- Ebon Blade Winged Defender
    36568, -- Crazed Apothecary
    29213, -- Anub'ar Darter
    29349, -- Anub'ar Darter
    26736, -- Azure Skyrazor
    26761, -- Crazed Mana-Wyrm
    30518, -- Azure Skyrazor (1)
    30521, -- Crazed Mana-Wyrm (1)
    31647, -- Carrion Beetle (1)
    11197, -- Mindless Skeleton
    16427, -- Soldier of the Frozen Wastes
    26238, -- Khorium Boar
    27981, -- Malformed Ooze
    31388, -- Malformed Ooze (1)
    16488, -- Arcane Anomaly
    17503, -- Woeful Healer
    6575, -- Scarlet Trainee
    14350, -- Hydroling
    15163, -- Nightmare Illusion
    19731, -- Nether Beast
    19958, -- White Seedling
    19962, -- Blue Seedling
    19964, -- Red Seedling
    19969, -- Green Seedling
    17829, -- Lykul Hatchling
    21866, -- Reanimated Spirit
    31518, -- Void Sentry (1)
    32665, -- Crystalline Tangler
    39190, -- Wicked Spirit
    17283, -- Astral Spark
    29321, -- Ichor Globule
    25598, -- Volatile Felfire Fiend
    25958, -- Volatile Felfire Fiend Sunwell
    27709, -- Drakkari Invader
    27753, -- Drakkari Invader
    27754, -- Drakkari Invader
    25362 -- warsong boar
);


SET @PATH_ID:= 6096 * 10;
UPDATE `creature_template` SET `spell3` = 56524, `spell1` = 56504 WHERE `entry` = 30301;
UPDATE `creature_template` SET `dmg_multiplier` = 4.5 WHERE `entry` = 30300;
UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = 6096;

DELETE FROM `creature_addon` WHERE `guid` = 6096;
INSERT INTO `creature_addon` VALUES
(6096, @PATH_ID, 0, 0, 0, 0, "");

DELETE FROM `waypoint_data` WHERE `id` = @PATH_ID;
INSERT INTO `waypoint_data` VALUES
(@PATH_ID,1 ,8015.629883, -126.514999, 865.718994, 0, 0, 2, 0, 100, 0),
(@PATH_ID,2 ,8046.919434, -116.348328, 862.508667, 0, 0, 2, 0, 100, 0),
(@PATH_ID,3 ,8085.373535, -106.077789, 859.335938, 0, 0, 2, 0, 100, 0),
(@PATH_ID,4 ,8123.215332, -100.236504, 855.699768, 0, 0, 2, 0, 100, 0),
(@PATH_ID,5 ,8162.164063, -94.2243580, 851.325073, 0, 0, 2, 0, 100, 0),
(@PATH_ID,6 ,8201.378906, -97.0324550, 847.744324, 0, 0, 2, 0, 100, 0),
(@PATH_ID,7 ,8256.535156, -102.373978, 842.648804, 0, 0, 2, 0, 100, 0),
(@PATH_ID,8 ,8306.835938, -96.7136540, 828.823364, 0, 0, 2, 0, 100, 0),
(@PATH_ID,9 ,8347.981445, -90.0185930, 821.797729, 0, 0, 2, 0, 100, 0),
(@PATH_ID,10,8403.133789, -91.9595640, 804.513916, 0, 0, 2, 0, 100, 0),
(@PATH_ID,11,8415.268555, -33.8821450, 800.037231, 0, 0, 2, 0, 100, 0),
(@PATH_ID,12,8362.960938, 2.0558600  , 806.914001, 0, 0, 2, 0, 100, 0),
(@PATH_ID,13,8303.921875, 8.2497230  , 822.242798, 0, 0, 2, 0, 100, 0),
(@PATH_ID,14,8232.710938, -10.6273830, 838.026489, 0, 0, 2, 0, 100, 0),
(@PATH_ID,15,8197.586914, -13.8175000, 847.106995, 0, 0, 2, 0, 100, 0),
(@PATH_ID,16,8155.230469, -25.3149590, 856.394836, 0, 0, 2, 0, 100, 0),
(@PATH_ID,17,8108.338379, -47.3235240, 861.329407, 0, 0, 2, 0, 100, 0),
(@PATH_ID,18,8070.712402, -62.2236520, 863.960205, 0, 0, 2, 0, 100, 0);

