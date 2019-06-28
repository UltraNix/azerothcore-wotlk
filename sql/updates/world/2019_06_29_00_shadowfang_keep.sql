-- Archmage Arugal
SET @ENTRY := 4275;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_archmage_arugal" WHERE `entry`=@ENTRY;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(@ENTRY, 0, 0, 'Who dares interfere with the Sons of Arugal?', 14, 0, 100, 0, 0, 0, 0, 'Archmage Arugal - Fenrus the Devourer dies'),
(@ENTRY, 1, 0, 'You, too, shall serve!', 14, 0, 100, 0, 0, 0, 0, 'Archmage Arugal - Aggro'),
(@ENTRY, 2, 0, 'Release your rage!', 14, 0, 100, 0, 0, 0, 0, 'Archmage Arugal - Transforms player into a Worgen'),
(@ENTRY, 3, 0, 'Another falls!', 14, 0, 100, 0, 0, 0, 0, 'Archmage Arugal - Killing a player');
DELETE FROM `creature_summon_groups` WHERE `summonerId`=@ENTRY;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`, `summonTime`) VALUES 
(@ENTRY, 0, 0, 4627, -148.199, 2165.647, 128.448, 1.026, 6, 60000),
(@ENTRY, 0, 0, 4627, -153.110, 2168.620, 128.448, 1.026, 6, 60000),
(@ENTRY, 0, 0, 4627, -145.905, 2180.520, 128.448, 4.183, 6, 60000),
(@ENTRY, 0, 0, 4627, -140.794, 2178.037, 128.448, 4.090, 6, 60000);

-- Wolf Master Nandos
SET @ENTRY := 3927;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_wolf_master_nandos" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;

-- Fenrus the Devourer
SET @ENTRY := 4274;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_fenrus_the_devourer" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;

-- Rethilgore
SET @ENTRY := 3914;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="boss_rethilgore" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;

-- Horde Prisoner
SET @ENTRY := 3849;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_shadowfang_prisoner" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
DELETE FROM `script_waypoint` WHERE `entry`=@ENTRY;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES 
(@ENTRY, 0, -250.923, 2116.26, 81.179, 0, 'SAY_FREE_AD'),
(@ENTRY, 1, -255.049, 2119.39, 81.179, 0, ''),
(@ENTRY, 2, -254.129, 2123.45, 81.179, 0, ''),
(@ENTRY, 3, -253.898, 2130.87, 81.179, 0, ''),
(@ENTRY, 4, -249.889, 2142.31, 86.972, 0, ''),
(@ENTRY, 5, -248.205, 2144.02, 87.013, 0, ''),
(@ENTRY, 6, -240.553, 2140.55, 87.012, 0, ''),
(@ENTRY, 7, -237.514, 2142.07, 87.012, 0, ''),
(@ENTRY, 8, -235.638, 2149.23, 90.587, 0, ''),
(@ENTRY, 9, -237.188, 2151.95, 90.624, 0, ''),
(@ENTRY, 10, -241.162, 2153.65, 90.624, 0, 'SAY_OPEN_DOOR_AD'),
(@ENTRY, 11, -241.13, 2154.56, 90.624, 5000, ''),
(@ENTRY, 12, -241.13, 2154.56, 90.624, 5000, 'SAY_POST1_DOOR_AD'),
(@ENTRY, 13, -241.13, 2154.56, 90.624, 25000, 'SAY_POST2_DOOR_AD');

-- Alliance Prisoner
SET @ENTRY := 3850;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_shadowfang_prisoner" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (21213, 21214);
DELETE FROM `script_waypoint` WHERE `entry`=@ENTRY;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES 
(@ENTRY, 0, -241.817, 2122.9, 81.179, 0, 'SAY_FREE_AS'),
(@ENTRY, 1, -247.139, 2124.89, 81.179, 0, ''),
(@ENTRY, 2, -253.179, 2127.41, 81.179, 0, ''),
(@ENTRY, 3, -253.898, 2130.87, 81.179, 0, ''),
(@ENTRY, 4, -249.889, 2142.31, 86.972, 0, ''),
(@ENTRY, 5, -248.205, 2144.02, 87.013, 0, ''),
(@ENTRY, 6, -240.553, 2140.55, 87.012, 0, ''),
(@ENTRY, 7, -237.514, 2142.07, 87.012, 0, ''),
(@ENTRY, 8, -235.638, 2149.23, 90.587, 0, ''),
(@ENTRY, 9, -237.188, 2151.95, 90.624, 0, ''),
(@ENTRY, 10, -241.162, 2153.65, 90.624, 0, 'SAY_OPEN_DOOR_AS'),
(@ENTRY, 11, -241.13, 2154.56, 90.624, 5000, 'cast'),
(@ENTRY, 12, -241.13, 2154.56, 90.624, 5000, 'SAY_POST_DOOR_AS'),
(@ENTRY, 13, -241.13, 2154.56, 90.624, 25000, '');

-- Arugal Voidwalker
SET @ENTRY := 4627;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_arugal_voidwalker" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
