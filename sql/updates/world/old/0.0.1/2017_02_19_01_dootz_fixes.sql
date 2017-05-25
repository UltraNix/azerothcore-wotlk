-- NPC: Spirit of Ar'tor| Author: Shon-su - NPC powinien pojawić się po wykonaniu questa Demonic Crystal Prisons
DELETE FROM `spell_area` WHERe `area` = 3752;
INSERT INTO `spell_area` VALUES 
(60197, 3752, 10528, 0, 0, 0, 2, 1, 64, 0),
(60194, 3752, 0, 10528, 0, 0, 2, 1, 0, 11);
-- NPC: Franclorn Forgewright | Author: Shon-su - NPC powinien być widoczny tylko dla martwych graczy
UPDATE `creature_template` SET `npcflag`=32771, `AIName`='' WHERE `entry`=8888;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 8888  AND `source_type` = 0;
UPDATE `creature_template_addon` SET `auras`=10848 WHERE `entry` IN (8888);
-- Quest: Gluttonous Lurkers| Author: Shon-su - unimożliwiono zbieranie wielokrotnie itemu z jednego npc
UPDATE `smart_scripts` SET `event_type` = 73, `event_param1` = 0, `event_param2` = 0, `event_param3` = 0, `event_param4` = 0 WHERE `entryorguid` = 28202;
-- NPC: Gutripper| Author: Shon-su - dodano odporność na CC
UPDATE `creature_template` SET `mechanic_immune_mask` = 8389712 WHERE `entry` = 18257;
-- Object: Dark Coffer| Author: Shon-su - dodano loot table
SET @COFFER := 160845;
DELETE FROM `gameobject_loot_template` WHERE `entry` = @COFFER;
INSERT INTO `gameobject_loot_template` VALUES
(@COFFER, 11751, -42, 0, 0, 1, 2),
(@COFFER, 11752, -40, 0, 0, 1, 2),
(@COFFER, 11753, -30, 0, 0, 1, 1),
(@COFFER, 1, 100, 0, 0, -6000, 1),
(@COFFER, 4500, 2, 0, 0, 1, 2),
(@COFFER, 3914, 2, 0, 0, 1, 1),
(@COFFER, 7910, 1.8, 0, 0, 1, 2),
(@COFFER, 7909, 1.5, 0, 0, 1, 1),
(@COFFER, 15282, 1.3, 0, 0, 1, 2),
(@COFFER, 8308, 1.3, 0, 0, 1, 1),
(@COFFER, 12713, 1.3, 0, 0, 1, 2),
(@COFFER, 10105, 1.3, 0, 0, 1, 1);
-- Quest: Naxxramas| Author: Shon-su - usunięto questy dotyczące starej wersji Naxxramas
DELETE FROM `creature_queststarter` WHERE `quest` IN (9237,9236,9235,9234);
DELETE FROM `creature_questender` WHERE `quest` IN (9237,9236,9235,9234);

DELETE FROM `disables` WHERE `entry` IN (9237,9236,9235,9234);
INSERT INTO `disables` VALUES
(1, 9237, 0, '','','Deprecated Quest '),
(1, 9236, 0, '','','Deprecated Quest '),
(1, 9235, 0, '','','Deprecated Quest '),
(1, 9234, 0, '','','Deprecated Quest ');
-- Quest: Just Following Orders| Author: Shon-su - Poprawiono resetowanie się NPC
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28217 AND `id` = 16;
INSERT INTO `smart_scripts` VALUES
(28217, 0, 16, 0, 10, 0, 100, 0, 1, 20, 10000, 15000, 11, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - OOC Los - Add Aura');
-- NPC: Fordragon Hold| Author: Shon-su - Poprawiono zachowanie npc-ów w Fordragon Hold
UPDATE `creature_template` SET `faction` = 2040 WHERE `entry` IN(27518,27576,2754,27519,27538);
-- Quest: Ruthless Cunning| Author: Shon-su - poprawiono działanie quest itemu
UPDATE `conditions` SET `ConditionValue1` = 17147 WHERE `ElseGroup` = 3 AND `SourceEntry` = 32307 AND `ConditionTypeOrreference` = 29;
UPDATE `conditions` SET `ConditionValue1` = 17146 WHERE `ElseGroup` = 2 AND `SourceEntry` = 32307 AND `ConditionTypeOrreference` = 29;
-- Quest: Evil Dravs Near| Author: Shon-su - poprawiono zaliczanie questa
UPDATE `quest_template` SET `SpecialFlags` = 0 WHERE `id` = 10923;
-- NPC: Tua'kea| Author: Afgan - dodanie animacji
-- Tua'kea http://wotlk.openwow.com/npc=26245
SET @GUID = 108023;
SET @PATH := @GUID * 10;

UPDATE creature_template SET MovementType=2 WHERE entry=26245;

DELETE FROM waypoint_data WHERE id=@PATH;
INSERT INTO waypoint_data (id,point,position_x,position_y,position_z, orientation, delay, action) VALUES
(@PATH, 1, 2728.969971, 935.776001, 0.223537, 3.508110, 900000, 0),
(@PATH, 2, 2725.669678, 935.673706, 0.151242, 0, 0, 0),
(@PATH, 3, 2723.665771, 940.981506, 0.132434, 0, 0, 0),
(@PATH, 4, 2717.235352, 945.446838, 0.199544, 0, 0, 0),
(@PATH, 5, 2709.003662, 951.448914, 0.132410, 2.748710, 300000, 0),
(@PATH, 6, 2716.692627, 949.006226, 0.132410, 0, 0, 0),
(@PATH, 7, 2721.197510, 940.112305, 0.147814 , 0, 0, 0);
DELETE FROM creature_addon WHERE guid=@GUID;
INSERT INTO creature_addon (guid,path_id,mount,bytes1,bytes2,emote,auras) VALUES
(@GUID, @PATH, 0, 0, 0, 0, '');
-- NPC: Razomaw Wolf| Author: baric - poprawiono aggro
-- Issue 8514: Razormane Wolves - add and bind to Razormane Hunters
-- Razormane Hunters in the Barrens (9 guids) are all missing the Wolves that path with them
-- create a Razormane Wolf pet (#3939) for each of the 9 Razormane Hunters (#3265)
SET @GUID := (SELECT MAX(guid) from creature) +100; 
-- insert 9 razormane wolves into new guids (@GUID to @GUID+8) with invalid xyz coords (we don't know them yet)
DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID+8;
INSERT INTO `creature` (`guid`,`id`,`map`,`position_x`,`position_y`, `position_z`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID  ,3939,1,0,0,0,90,120,1),
(@GUID+1,3939,1,0,0,0,90,120,1),
(@GUID+2,3939,1,0,0,0,90,120,1),
(@GUID+3,3939,1,0,0,0,90,120,1),
(@GUID+4,3939,1,0,0,0,90,120,1),
(@GUID+5,3939,1,0,0,0,90,120,1),
(@GUID+6,3939,1,0,0,0,90,120,1),
(@GUID+7,3939,1,0,0,0,90,120,1),
(@GUID+8,3939,1,0,0,0,90,120,1);
-- bind the wolves to the 9 razormane hunters (id 3265)
DELETE FROM `creature_formations` WHERE `leaderGUID` BETWEEN 20301 AND 20309;
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`) VALUES 
(20301,20301,0,0,2),
(20301,@GUID,4,60,2),
(20302,20302,0,0,2),
(20302,@GUID+1,4,60,2),
(20303,20303,0,0,2),
(20303,@GUID+2,4,60,2),
(20304,20304,0,0,2),
(20304,@GUID+3,4,60,2),
(20305,20305,0,0,2),
(20305,@GUID+4,4,60,2),
(20306,20306,0,0,2),
(20306,@GUID+5,4,60,2),
(20307,20307,0,0,2),
(20307,@GUID+6,4,60,2),
(20308,20308,0,0,2),
(20308,@GUID+7,4,60,2),
(20309,20309,0,0,2),
(20309,@GUID+8,4,60,2);
-- now set the wolf pets to the same xyz as their leader
UPDATE `creature` c1,`creature` c2,`creature_formations` cf SET c1.`position_x`=c2.`position_x`,c1.`position_y`=c2.`position_y`,c1.`position_z`=c2.`position_z` WHERE c1.`guid`=cf.`memberGUID` AND c2.`guid`=cf.`leaderGUID` AND c1. `guid` BETWEEN @GUID AND @GUID+8;
DELETE FROM smart_scripts WHERE entryorguid = 3265 AND id = 2;
-- Item: Defender of the Timbermaw| Author: Shon-su - poprawiono zachowanie guardiana
SET @ENTRY := 15720;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 6000, 8000, 2000, 4000, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Timbermaw Ancestor - In Combat - Cast Lightning Bolt'),
(@ENTRY, 0, 1, 0, 74, 0, 100, 0, 0, 50, 120000, 120000, 11, 23381, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 'Timbermaw Ancestor  - On Friendly Between 0-40% Health - Cast \'Healing Touch\'');
-- Instance: Blackrock Depths| Author: Shon-su - Poprawiono zadawanie obrażeń przez Ironhand Guardian 
UPDATE `creature_template` SET `faction` = 16 WHERE `entry` = 8982;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 8982 AND `id` IN (2,3);
INSERT INTO `smart_scripts` VALUES
(8982, 0, 2, 3, 4, 0, 100, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ironhand Guardian - On Agro - Auto attack off'),
(8982, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ironhand Guardian - On Agro - Disable Combat Movement');
-- Quest: Killing Time| Author: Shon-su - dodano portal
SET @VARIAN := 29611;
SET @JAINA := 32346;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @VARIAN;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @VARIAN;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @JAINA AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(@VARIAN, 0, 0, 0, 19, 0, 100, 0, 13371, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, @JAINA, 10, 0, 0, 0, 0, 0, 'Varian - On Quest The Killing Time Accepted - Set data 1 1'),
(@JAINA, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 50, 176501, 20, 0, 0, 0, 0, 8, 0, 0, 0, -8445.07, 335.8, 122.162, 0, 'Jaina - On Data Set 1 1 - Summon GO');
-- NPC: Faction Leaders| Author: Shon-su - dodanie umiejętności
SET @TYRANDE:= 7999;
SET @MAGNI:= 2784;
SET @VARIAN:= 29611;
SET @VELEN:= 17468;
SET @MEKKA:= 7937;
SET @VOLJIN:= 10540;
SET @THERON:= 16802;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (@TYRANDE, @MAGNI, @VELEN, @MEKKA, @VOLJIN, @THERON);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@TYRANDE, @MAGNI, @MEKKA, @VELEN, @VOLJIN, @THERON);
DELETE FROM `smart_scripts` WHERE `entryorguid` = @VARIAN AND `id` IN (1,2);
INSERT INTO `smart_scripts` VALUES
(@TYRANDE, 0, 0, 0, 0, 0, 100, 0, 4000, 8000, 2000, 3000, 6, 20691, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tyrande - IC - Cast Cleave'),
(@TYRANDE, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 20690, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tyrande - IC - Cast Moonfire'),
(@TYRANDE, 0, 2, 0, 0, 0, 100, 0, 30000, 35000, 20000, 23000, 6, 20687, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tyrande - IC - Cast Starfall'),
(@TYRANDE, 0, 3, 0, 0, 0, 100, 0, 10000, 11000, 9000, 10000, 6, 20688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tyrande - IC - Cast Searing Arrow'),
-- Magni
(@MAGNI, 0, 0, 0, 0, 0, 100, 0, 25000, 28000, 20000, 22000, 6, 19135, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Magni - IC - Cast Avatar'),
(@MAGNI, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 20686, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Magni - IC - Cast Knock Away'),
(@MAGNI, 0, 2, 0, 0, 0, 100, 0, 10000, 11000, 10000, 11000, 6, 20685, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Magni - IC - Cast Storm Bolt'),
-- Varian
(@VARIAN, 0, 1, 0, 0, 0, 100, 0, 20000, 21000, 20000, 21000, 6, 59688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Varian - IC - Cast Heroic Leap'),
(@VARIAN, 0, 2, 0, 0, 0, 100, 0, 10000, 12000, 10000, 11000, 6, 41056, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Varian - IC - Cast Whirlwind'),
-- Velen
(@VELEN, 0, 0, 0, 0, 0, 100, 0, 4000, 8000, 2000, 3000, 6, 59703, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Velen - IC - Cast Holy Smite'),
(@VELEN, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 59700, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Velen - IC - Cast Holy Blast'),
(@VELEN, 0, 2, 0, 0, 0, 100, 0, 30000, 35000, 20000, 23000, 6, 59701, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Velen - IC - Cast Holy Nowa'),
(@VELEN, 0, 3, 0, 0, 0, 100, 0, 10000, 11000, 9000, 10000, 6, 33542, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Velen - IC - Cast Staff Strike'),
-- Mekkatorque
(@MEKKA, 0, 0, 0, 0, 0, 100, 0, 25000, 28000, 20000, 22000, 6, 9143, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Mekkatorque - IC - Cast Bomb'),
(@MEKKA, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 22739, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Mekkatorque - IC - Cast Goblin Dragon Gun'),
(@MEKKA, 0, 2, 0, 0, 0, 100, 0, 10000, 11000, 10000, 11000, 6, 22742, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Mekkatorque - IC - Cast shrink Ray'),
-- Voljin
(@VOLJIN, 0, 0, 0, 0, 0, 100, 0, 4000, 8000, 2000, 3000, 6, 17146, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Voljin - IC - Cast SW Pain'),
(@VOLJIN, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 16097, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Voljin - IC - Cast Hex'),
(@VOLJIN, 0, 2, 0, 0, 0, 100, 0, 30000, 35000, 20000, 23000, 6, 17289, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Voljin - IC - Cast Shadow Shock'),
(@VOLJIN, 0, 3, 0, 0, 0, 100, 0, 10000, 11000, 9000, 10000, 6, 17820, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Voljin - IC - Cast Veil of Shadow'),
-- Lorthemar
(@THERON, 0, 0, 0, 0, 0, 100, 0, 4000, 8000, 2000, 3000, 6, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Theron - IC - Cast Cleave'),
(@THERON, 0, 1, 0, 0, 0, 100, 0, 15000, 16000, 10000, 11000, 6, 59715, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Theron - IC - Cast Arcane Shock'),
(@THERON, 0, 2, 0, 0, 0, 100, 0, 30000, 35000, 20000, 23000, 6, 33385, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Theron - IC - Cast Mana Burn'),
(@THERON, 0, 3, 0, 0, 0, 100, 0, 10000, 11000, 9000, 10000, 6, 33384, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Theron - IC - Cast Mass Charm');
-- NPC: Nargle Lashcord| Author: Shon-su - dodanie Deadly Offhandów
SET @VENDOR:= 31863;
DELETE FROM `npc_vendor` WHERE `entry` = @VENDOR AND `item` IN(42531, 42537, 42525);
INSERT INTO `npc_vendor` VALUES
(@VENDOR, 0, 42531, 0, 0, 2467),
(@VENDOR, 0, 42537, 0, 0, 2467),
(@VENDOR, 0, 42525, 0, 0, 2467);
-- Quest: Herzul Bloodmark| Author: Shon-su - poprawiono ścieżkę
SET @CGUID := 13990;
SET @PATH := @CGUID * 10;
UPDATE `creature_addon` SET `path_id` = @PATH WHERE `guid` = @CGUID;
UPDATE `creature` SET `MovementType` = 2 WHERE `guid` IN (@CGUID, 13992, 13991);
DELETE FROM `creature_formations` WHERE `leaderGUID` = @CGUID;
INSERT INTO `creature_formations` VALUES
(@CGUID, @CGUID, 0, 0, 2, 0, 0),
(@CGUID, 13992, 3, 30, 2, 0, 0),
(@CGUID, 13991, 3, 330, 2, 0, 0);

DELETE FROM `waypoint_data` WHERE `id` = @PATH;
INSERT INTO `waypoint_data` VALUES
(@PATH, 1,-1167.060059, -2042.270020, 92.182,  0, 0, 0, 0, 100, 0),   
(@PATH, 2,-1167.060059, -2042.270020, 92.182343 ,   0, 0, 0, 0, 100, 0),
(@PATH, 3,-1115.250977, -2000.933472, 88.074669 ,   0, 0, 0, 0, 100, 0),
(@PATH, 4,-1075.614624, -1966.162842, 89.834351 ,   0, 0, 0, 0, 100, 0),
(@PATH, 5,-1032.646729, -1932.198120, 91.397469 ,   0, 0, 0, 0, 100, 0),
(@PATH, 6,-996.964600,  -1950.800903, 91.725700  ,   0, 0, 0, 0, 100, 0),
(@PATH, 7,-965.362183,  -2000.947144, 88.523796  ,   0, 0, 0, 0, 100, 0),
(@PATH, 8,-939.511353,  -2020.107056, 85.249176  ,   0, 0, 0, 0, 100, 0),
(@PATH, 9,-876.588013,  -2034.674561, 81.717384  ,   0, 0, 0, 0, 100, 0),
(@PATH, 10,-901.093933,  -2089.843506, 86.544563  ,  0, 0, 0, 0, 100, 0),
(@PATH, 11,-929.044067,  -2102.534668, 85.716042  ,  0, 0, 0, 0, 100, 0),
(@PATH, 12,-972.408508,  -2102.732666, 81.487144  ,  0, 0, 0, 0, 100, 0),
(@PATH, 13,-1037.780640, -2178.701660, 82.814201 ,  0, 0, 0, 0, 100, 0),
(@PATH, 14,-1072.068359, -2275.740234, 88.150352 ,  0, 0, 0, 0, 100, 0),
(@PATH, 15,-1141.038086, -2274.550049, 86.149559 ,  0, 0, 0, 0, 100, 0),
(@PATH, 16,-1150.815796, -2224.878662, 83.605606 ,  0, 0, 0, 0, 100, 0),
(@PATH, 17,-1147.792725, -2108.937256, 86.589485 ,  0, 0, 0, 0, 100, 0),
(@PATH, 18,-1135.039063, -2067.484619, 85.218536 ,  0, 0, 0, 0, 100, 0),
(@PATH, 19,-1166.833008, -2042.467041, 92.163780 ,  0, 0, 0, 0, 100, 0);
-- Npc: Kuk'uq| Author: Shon-su - dodano animacje
UPDATE `creature` SET `equipment_id` = 3 WHERE `id` = 27185;

DELETE FROM `creature_equip_template` WHERE `entry` = 27185 AND `id` = 3;
INSERT INTO `creature_equip_template` VALUES
(27185, 3, 5956, 0, 0, 1);

SET @KALUAK:= 27185;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @KALUAK;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN( @KALUAK, @KALUAK * 100);
INSERT INTO `smart_scripts` VALUES
(@KALUAK, 0, 0, 0, 1, 0, 100, 0, 300000, 300000, 100000, 200000, 80, @KALUAK * 100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2756.53, 851.73, 6.71, 4.52, ''),
(@KALUAK * 100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 71, 0, 0, 14535, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 17, 432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 4, 0, 0, 0, 100, 0, 120000, 120000, 120000, 120000, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2760.01, 854.72, 6.67, 5.2,''),
(@KALUAK * 100, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 71, 0, 0, 13611, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 17, 432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 7, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 59, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2802.43, 857.14, 1.06, 5.07, ''),
(@KALUAK * 100, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 10, 0, 0, 0, 100, 0, 40000, 40000, 40000, 40000, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 11, 0, 0, 0, 100, 0, 0, 0, 0, 0, 71, 0, 0, 5956, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(@KALUAK * 100, 9, 12, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 17, 233, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `npc_vendor` WHERE `entry` = 27185 AND `item` = 39995;
-- Quest: Stunning View| Author: Shon-su - dodano możliwość zmiany w ghoula
DELETE FROM `conditions` WHERE `SourceGroup` = 10111 AND `ElseGroup` = 3;
INSERT INTO `conditions` VALUES
(15, 10111, 0, 0, 3, 9, 0, 13160, 0, 0, 0, 0, 0, '','');
-- Quest: Abduction| Author: Shon-su - quest zostanie zaliczony dopiero po doprowadzeniu moba do npc (C++)
-- NPC: Guards| Author: Shon-su - dodanie Truesight Vision
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 1756;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 466 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1756;
INSERT INTO `smart_scripts` VALUES 
(466, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 18950, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Reset - Cast Invisibility and Stealth Detection'),
(1756, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 18950, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Reset - Cast Invisibility and Stealth Detection');
-- Item: Deadly Gladiator's Waraxe| Author: Shon-su - poprawienie ceny
UPDATE `npc_vendor` SET `ExtendedCost` = 2392 WHERE `item` = 42237 AND `entry` = 31863;
-- #101
UPDATE `pool_gameobject` SET `chance` = 75 WHERE `description` LIKE "%Lesser Bloodstone Deposit%";
-- #111
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 14843;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 14843;
INSERT INTO `smart_scripts` VALUES
(14843, 0, 0, 0, 62, 0, 100, 0, 6214, 0, 0, 0, 5, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `game_event_creature` WHERE `guid` = 54395;
INSERT INTO `game_event_creature` VALUES
(3, 54395),
(4, 54395),
(5, 54395);
-- #147
UPDATE `creature_template` SET `faction` = 1639, `speed_run` = 1.1 WHERE `entry` = 17238; -- 1638
UPDATE `smart_scripts` SET `event_param1` = 2500, `event_param2` = 2500 WHERE `entryorguid` = 1723300 AND `id` = 0;
UPDATE `smart_scripts` SET `event_param1` = 6000, `event_param2` = 6000 WHERE `entryorguid` = 1723300 AND `id` = 1;
UPDATE `smart_scripts` SET `event_param1` = 11000, `event_param2` = 11000 WHERE `entryorguid` = 1723300 AND `id` = 2;
UPDATE `smart_scripts` SET `event_param1` = 10000, `event_param2` = 10000 WHERE `entryorguid` = 1723300 AND `id` = 3;
UPDATE `smart_scripts` SET `event_param1` = 10000, `event_param2` = 10000 WHERE `entryorguid` = 1723300 AND `id` = 4;
-- #442
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 27061;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 27061;
INSERT INTO `smart_scripts` VALUES
(27061, 0, 0, 0, 28, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Xink Shredder - On passenger removed - Despawn');
-- #701
UPDATE `creature` SET `equipment_id` = 1 WHERE `guid` = 88076;
-- #702
DELETE FROM `creature_loot_template` WHERE `item` = 11114;
INSERT INTO `creature_loot_template` VALUES
(6503, 11114, -25, 0, 0, 1, 1),
(6501, 11114, -25, 0, 0, 1, 1),
(6502, 11114, -25, 0, 0, 1, 1),
(9164, 11114, -25, 0, 0, 1, 1),
(6504, 11114, -25, 0, 0, 1, 1);