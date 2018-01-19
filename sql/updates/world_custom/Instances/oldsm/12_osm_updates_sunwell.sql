DELETE FROM `spell_script_names` WHERE `spell_id` IN (43657, 56897, 26659, 39028);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(43657, "spell_electrical_storm_damage"),
(56897, "spell_storm_call_old_scarlet"),
(26659, "spell_sam_test_aura"),
(39028, "spell_lightning_discharge_osm");


UPDATE `creature_template` SET `ScriptName` = "npc_storm_call_trigger_OSM", `name` = "storm call trigger", `modelid1` = 11686, `flags_extra` = 128 WHERE `entry` = 400045;

UPDATE `creature_template` SET `name` = "Arthur", `subname` = "", `ScriptName` = "", `flags_extra` = 128 WHERE `entry` = 400046;
UPDATE `creature_template` SET `name` = "Simon", `subname` = "", `ScriptName` = "", `flags_extra` = 128 WHERE `entry` = 400049;
UPDATE `creature_template` SET `Health_mod` = 25000 WHERE `entry` = 400008;

UPDATE `creature_template` SET `Health_mod` = 11.5 WHERE `entry` IN (400026, 400027, 400028);
UPDATE `creature_template` SET `attackpower` = 449 WHERE `entry` = 400031;
UPDATE `creature_template` SET `attackpower` = 500, `health_mod` = 54.72 WHERE `entry` = 400023;
UPDATE `creature_template` SET `health_mod` = 54.72 WHERE `entry` = 400025;
UPDATE `creature_template` SET `health_mod` = 54.72 WHERE `entry` = 400024;
UPDATE `creature_template` SET `health_mod` = 12.45 WHERE `entry` = 400020;
UPDATE `creature_template` SET `health_mod` = 450 WHERE `entry` = 400022;
UPDATE `creature_template` SET `health_mod` = 80 WHERE `entry` IN (400050, 400051, 400052, 400053);
UPDATE `creature_template` SET `health_mod` = 100 WHERE `entry` = 400054;
UPDATE `creature_template` SET `mindmg` = 150, `maxdmg` = 300 WHERE `entry` = 400050;
UPDATE `creature_template` SET `mindmg` = 550, `maxdmg` = 600, `dmg_multiplier` = 100 WHERE `entry` = 400022;
UPDATE `creature_template` SET `mindmg` = 250, `maxdmg` = 300, `dmg_multiplier` = 100 WHERE `entry` = 400023;
UPDATE `creature_template` SET `mindmg` = 300, `maxdmg` = 310 WHERE `entry` = 400031;
UPDATE `creature_template` SET `mindmg` = 100, `maxdmg` = 120 WHERE `entry` IN (400026, 400027, 400028);
UPDATE `creature_template` SET `Health_mod` = 455 WHERE `entry` = 400000;
UPDATE `creature_template` SET `Health_mod` = 5 WHERE `entry` = 400001;
UPDATE `creature_template` SET `Health_mod` = 90 WHERE `entry` = 400002;
UPDATE `creature_template` SET `Health_mod` = 11 WHERE `entry` = 400004;
UPDATE `creature_template` SET `health_mod` = 15 WHERE `entry` = 400005;
UPDATE `creature_template` SET `health_mod` = 11.25 WHERE `entry` = 400006;
UPDATE `creature_template` SET `health_mod` = 450 WHERE `entry` = 400041;
UPDATE `creature_template` SET `health_mod` = 585, `mindmg` = 700, `maxdmg` = 800 WHERE `entry` = 400040;
UPDATE `creature_template` SET `health_mod` = 1100 WHERE `entry` = 400010;
UPDATE `creature_template` SET `health_mod` = 30 WHERE `entry` = 400015;
UPDATE `creature_template` SET `health_mod` = 3 WHERE `entry` = 400016;
UPDATE `creature_template` SET `health_mod` = 825 WHERE `entry` = 400043;

UPDATE `creature_template` SET `lootid` = 100013 WHERE `entry` IN (400050, 400051, 400052, 400053, 400054);

UPDATE `creature_template` SET `mingold` = 10000000, `maxgold` = 10000000 WHERE `entry` = 400022;
UPDATE `creature_template` SET `mingold` = 12500000, `maxgold` = 12500000 WHERE `entry` = 400000;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400008;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400041;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400043;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400010;

UPDATE `creature_template` SET `name` = "Prince Val’sameth", `subname` = "<The San’layn>", `modelid1` = 25541 WHERE `entry` = 400022;
UPDATE `creature_template` SET `subname` = "<The Unforseen>" WHERE `entry` = 400000;
UPDATE `creature_template` SET `subname` = "<The Gatekeeper>" WHERE `entry` = 400008;
UPDATE `creature_template` SET `name` = "Va’Thanui", `subname` = "<Void Lord>" WHERE `entry` IN (400041, 400040);

UPDATE `creature_template` SET `lootid` = 100007 WHERE `entry` = 400022;
UPDATE `creature_template` SET `lootid` = 100008 WHERE `entry` = 400000;
UPDATE `creature_template` SET `lootid` = 100009 WHERE `entry` = 400008;
UPDATE `creature_template` SET `lootid` = 100010 WHERE `entry` = 400041;
UPDATE `creature_template` SET `lootid` = 100011 WHERE `entry` = 400043;
UPDATE `creature_template` SET `lootid` = 100012 WHERE `entry` = 400010;

DELETE FROM `npc_text` WHERE `ID` = 16777213;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES 
(16777213, "You’re just in time, $n! We cannot let the Scourge control a Void Lord, there would be unforseen consequences! We need to hurry and stop the ritual before it’s too late. Unfortunately, old part of the Monastery was cut off and there’s no way in. I will teleport you myself.", 'Greetings, $n.', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 1);

DELETE FROM `gossip_menu` WHERE `entry` = 65006;
INSERT INTO `gossip_menu` VALUES
(65006, 16777213);

UPDATE `gossip_menu_option` SET `option_text` = "We are ready. Teleport us in." WHERE `menu_id` = 65006;

SET @MAZIN:= 400022;
DELETE FROM `creature_text` WHERE `entry` = @MAZIN;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@MAZIN, 0, 0, 'What is that smell!? eww!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 1, 0, "Uhh.. strangers.. I''m Prince Val’sameth, are you here to fight me?", 12, 0, 100, 11, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 2, 0, 'Fine, we will fight but first let me show you my collection... my collection of souls.', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 3, 0, 'My powers allow me to steal part of someone soul without killing him, they''re not the real deal, but strong enough to kill you!', 12, 0, 100, 11, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 4, 0, 'Go''el also known as Thrall. Warchief of the Orcish Horde!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 5, 0, 'Dark Ranger, Mistress Sylvanas!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 6, 0, 'Founder of the Cult of the Damned, Kel''Thuzad!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 7, 0, 'The end is near!', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 8, 0, 'Killing is not so easy as the innocent believe $n', 12, 0, 100, 0, 0, 0, 'Old SM boss1'),
(@MAZIN, 8, 1, 'There will be killing till the score is paid $n', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 8, 2, 'Killing makes me feel good $n', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 9, 0, 'The death of the soul is more painful than that of the body. Javier.. Matar! MATARLOS A TODOS!', 14, 0, 100, 0, 0, 0, 'Old SM boss 1');

DELETE FROM `creature_equip_template` WHERE `entry` = 400043;

UPDATE `creature_template` SET `health_mod` = 40 WHERE `entry` = 400009;
UPDATE `creature_template` SET `mindmg` = 638, `maxdmg` = 680, `dmg_multiplier` = 90, `health_mod` = 1000 WHERE `entry` = 400008;

UPDATE `creature_template` SET `subname` = "" WHERE `subname` LIKE "%The risen%";

SET @LOOT_ID:= 100007;
DELETE FROM creature_loot_template WHERE entry IN (@LOOT_ID + 0, @LOOT_ID + 1, @LOOT_ID + 2, @LOOT_ID + 3, @LOOT_ID + 4, @LOOT_ID + 5, @LOOT_ID + 6);
INSERT INTO creature_loot_template VALUES
(@LOOT_ID + 0, 23162, 100, 1, 1, 1, 1),
(@LOOT_ID + 0, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 0, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 0, 43599, 40, 1, 4, 1, 1),
(@LOOT_ID + 0, 32566, 25, 1, 5, 1, 1),
(@LOOT_ID + 0, 22114, 25, 1, 6, 1, 1),
(@LOOT_ID + 0, 39656, 20, 1, 7, 1, 1),
(@LOOT_ID + 0, 54068, 10, 1, 8, 1, 1),
(@LOOT_ID + 0, 22591, 2, 1, 9, 1, 1),

(@LOOT_ID + 1, 23709, 100, 1, 1, 1, 1),
(@LOOT_ID + 1, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 1, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 1, 43599, 45, 1, 4, 1, 1),
(@LOOT_ID + 1, 34499, 25, 1, 5, 1, 1),
(@LOOT_ID + 1, 49665, 25, 1, 6, 1, 1),
(@LOOT_ID + 1, 49663, 20, 1, 7, 1, 1),
(@LOOT_ID + 1, 46778, 10, 1, 8, 1, 1),
(@LOOT_ID + 1, 43651, 8, 1, 9, 1, 1),
(@LOOT_ID + 1, 22691, 3, 1, 10, 1, 1),

(@LOOT_ID + 2, 23705, 100, 1, 1, 1, 1),
(@LOOT_ID + 2, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 2, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 2, 43599, 50, 1, 4, 1, 1),
(@LOOT_ID + 2, 38301, 25, 1, 5, 1, 1),
(@LOOT_ID + 2, 49646, 25, 1, 6, 1, 1),
(@LOOT_ID + 2, 34492, 20, 1, 7, 1, 1),
(@LOOT_ID + 2, 33809, 14, 1, 8, 1, 1),
(@LOOT_ID + 2, 43651, 10, 1, 9, 1, 1),
(@LOOT_ID + 2, 22951, 4, 1, 10, 1, 1), 
(@LOOT_ID + 2, 1, 2, 1, 0, -@LOOT_ID, 1),

(@LOOT_ID + 3, 38309, 100, 1, 1, 1, 1),
(@LOOT_ID + 3, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 3, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 3, 43599, 55, 1, 4, 1, 1),
(@LOOT_ID + 3, 54452, 25, 1, 5, 1, 1),
(@LOOT_ID + 3, 39286, 25, 1, 6, 1, 1),
(@LOOT_ID + 3, 54847, 20, 1, 7, 1, 1),
(@LOOT_ID + 3, 37719, 16, 1, 8, 1, 1),
(@LOOT_ID + 3, 22691, 5, 1, 9, 1, 1), 
(@LOOT_ID + 3, 1, 4, 1, 0, -@LOOT_ID, 1),

(@LOOT_ID + 4, 38311, 100, 1, 1, 1, 1),
(@LOOT_ID + 4, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 4, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 4, 43599, 60, 1, 4, 1, 1),
(@LOOT_ID + 4, 45063, 25, 1, 5, 1, 1),
(@LOOT_ID + 4, 49343, 25, 1, 6, 1, 1),
(@LOOT_ID + 4, 13584, 20, 1, 7, 1, 1),
(@LOOT_ID + 4, 54069, 20, 1, 8, 1, 1),
(@LOOT_ID + 4, 22691, 9, 1, 9, 1, 1),
(@LOOT_ID + 4, 13262, 5, 1, 10, 1, 1),
(@LOOT_ID + 4, 25596, 3, 1, 11, 1, 1), 
(@LOOT_ID + 4, 1, 6, 1, 0, -@LOOT_ID, 1),

(@LOOT_ID + 5, 38313, 100, 1, 1, 1, 1),
(@LOOT_ID + 5, 38233, 100, 1, 2, 10, 10),
(@LOOT_ID + 5, 46779, 100, 1, 3, 10, 10),
(@LOOT_ID + 5, 23162, 100, 1, 4, 1, 1),
(@LOOT_ID + 5, 49287, 25, 1, 5, 1, 1),
(@LOOT_ID + 5, 21176, 25, 1, 6, 1, 1),
(@LOOT_ID + 5, 22691, 25, 1, 7, 1, 1),
(@LOOT_ID + 5, 13262, 20, 1, 8, 1, 1),
(@LOOT_ID + 5, 25596, 15, 1, 9, 1, 1), 
(@LOOT_ID + 5, 43599, 100, 1, 10, 1, 1),
(@LOOT_ID + 5, 1, 20, 1, 0, -@LOOT_ID, 1),

(@LOOT_ID + 6, 37701, 6, 1, 1, 1, 2),
(@LOOT_ID + 6, 33470, 6, 1, 2, 2, 7),
(@LOOT_ID + 6, 33445, 6, 1, 3, 1, 1),
(@LOOT_ID + 6, 34054, 6, 1, 4, 1, 1),
(@LOOT_ID + 6, 33454, 6, 1, 5, 1, 1),
(@LOOT_ID + 6, 33424, 5, 1, 6, 1, 1),
(@LOOT_ID + 6, 33403, 5, 1, 7, 1, 1),
(@LOOT_ID + 6, 33365, 5, 1, 8, 1, 1),
(@LOOT_ID + 6, 33370, 5, 1, 9, 1, 1),
(@LOOT_ID + 6, 33379, 5, 1, 10, 1, 1),
(@LOOT_ID + 6, 39220, 5, 1, 11, 1, 1),
(@LOOT_ID + 6, 33422, 5, 1, 12, 1, 1),
(@LOOT_ID + 6, 43852, 5, 1, 13, 1, 1),
(@LOOT_ID + 6, 43463, 1.5, 1, 14, 1, 1),
(@LOOT_ID + 6, 43464, 1.5, 1, 15, 1, 1),
(@LOOT_ID + 6, 37091, 1.5, 1, 16, 1, 1),
(@LOOT_ID + 6, 37092, 1.5, 1, 17, 1, 1),
(@LOOT_ID + 6, 37097, 1.5, 1, 18, 1, 1),
(@LOOT_ID + 6, 37098, 1.5, 1, 19, 1, 1),
(@LOOT_ID + 6, 37093, 1.5, 1, 20, 1, 1),
(@LOOT_ID + 6, 37094, 1.5, 1, 21, 1, 1),
(@LOOT_ID + 6, 43465, 1.5, 1, 22, 1, 1),
(@LOOT_ID + 6, 43466, 1.5, 1, 23, 1, 1),
(@LOOT_ID + 6, 36059, 1.33, 1, 24, 1, 1),
(@LOOT_ID + 6, 36035, 1.33, 1, 25, 1, 1),
(@LOOT_ID + 6, 36043, 1.33, 1, 26, 1, 1),
(@LOOT_ID + 6, 43297, 1.33, 1, 27, 1, 1),
(@LOOT_ID + 6, 36394, 1.33, 1, 28, 1, 1),
(@LOOT_ID + 6, 36274, 1.33, 1, 29, 1, 1),
(@LOOT_ID + 6, 36270, 1.33, 1, 30, 1, 1),
(@LOOT_ID + 6, 36267, 1.33, 1, 31, 1, 1),
(@LOOT_ID + 6, 36268, 1.33, 1, 32, 1, 1),
(@LOOT_ID + 6, 36271, 1.33, 1, 33, 1, 1),
(@LOOT_ID + 6, 36272, 1.33, 1, 34, 1, 1),
(@LOOT_ID + 6, 36273, 1.33, 1, 35, 1, 1),
(@LOOT_ID + 6, 36051, 1.33, 1, 36, 1, 1),
(@LOOT_ID + 6, 36052, 1.33, 1, 37, 1, 1),
(@LOOT_ID + 6, 36296, 1.33, 1, 38, 1, 1),
(@LOOT_ID + 6, 41788, 0.28, 1, 39, 1, 1),
(@LOOT_ID + 6, 41780, 0.28, 1, 40, 1, 1),
(@LOOT_ID + 6, 41786, 0.28, 1, 41, 1, 1),
(@LOOT_ID + 6, 41777, 0.28, 1, 42, 1, 1),
(@LOOT_ID + 6, 41789, 0.28, 1, 43, 1, 1),
(@LOOT_ID + 6, 41781, 0.28, 1, 44, 1, 1),
(@LOOT_ID + 6, 41783, 0.28, 1, 45, 1, 1),
(@LOOT_ID + 6, 41778, 0.28, 1, 46, 1, 1),
(@LOOT_ID + 6, 41782, 0.28, 1, 47, 1, 1),
(@LOOT_ID + 6, 41784, 0.28, 1, 48, 1, 1),
(@LOOT_ID + 6, 41779, 0.28, 1, 49, 1, 1),
(@LOOT_ID + 6, 41785, 0.28, 1, 50, 1, 1),
(@LOOT_ID + 6, 41787, 0.28, 1, 51, 1, 1),
(@LOOT_ID + 6, 37781, 0.28, 1, 52, 1, 1),
(@LOOT_ID + 6, 37761, 0.28, 1, 53, 1, 1),
(@LOOT_ID + 6, 37794, 0.28, 1, 54, 1, 1),
(@LOOT_ID + 6, 37771, 0.28, 1, 55, 1, 1),
(@LOOT_ID + 6, 45548, 0.19, 1, 56, 1, 1),
(@LOOT_ID + 6, 45540, 0.19, 1, 57, 1, 1),
(@LOOT_ID + 6, 45605, 0.19, 1, 58, 1, 1),
(@LOOT_ID + 6, 45542, 0.19, 1, 59, 1, 1),
(@LOOT_ID + 6, 45549, 0.19, 1, 60, 1, 1),
(@LOOT_ID + 6, 46138, 0.19, 1, 61, 1, 1),
(@LOOT_ID + 6, 45544, 0.19, 1, 62, 1, 1),
(@LOOT_ID + 6, 45539, 0.19, 1, 63, 1, 1),
(@LOOT_ID + 6, 45547, 0.19, 1, 64, 1, 1),
(@LOOT_ID + 6, 45543, 0.19, 1, 65, 1, 1),
(@LOOT_ID + 6, 45541, 0.19, 1, 66, 1, 1),
(@LOOT_ID + 6, 37254, 0.19, 1, 67, 1, 1),
(@LOOT_ID + 6, 46340, 0.15, 1, 69, 1, 1),
(@LOOT_ID + 6, 46351, 0.15, 1, 70, 1, 1),
(@LOOT_ID + 6, 46346, 0.15, 1, 71, 1, 1),
(@LOOT_ID + 6, 46345, 0.15, 1, 72, 1, 1),
(@LOOT_ID + 6, 46347, 0.15, 1, 73, 1, 1),
(@LOOT_ID + 6, 46341, 0.15, 1, 74, 1, 1),
(@LOOT_ID + 6, 46343, 0.15, 1, 75, 1, 1),
(@LOOT_ID + 6, 46342, 0.15, 1, 76, 1, 1),
(@LOOT_ID + 6, 46344, 0.15, 1, 77, 1, 1),
(@LOOT_ID + 6, 46350, 0.15, 1, 78, 1, 1),
(@LOOT_ID + 6, 45538, 0.15, 1, 79, 1, 1),
(@LOOT_ID + 6, 40409, 0.14, 1, 80, 1, 1),
(@LOOT_ID + 6, 40408, 0.14, 1, 81, 1, 1),
(@LOOT_ID + 6, 40406, 0.15, 1, 82, 1, 1),
(@LOOT_ID + 6, 40412, 0.15, 1, 83, 1, 1),
(@LOOT_ID + 6, 40410, 0.15, 1, 84, 1, 1),
(@LOOT_ID + 6, 40414, 0.15, 1, 85, 1, 1),
(@LOOT_ID + 6, 40407, 0.15, 1, 86, 1, 1),
(@LOOT_ID + 6, 39472, 0.15, 1, 87, 1, 1),
(@LOOT_ID + 6, 39473, 0.15, 1, 88, 1, 1),
(@LOOT_ID + 6, 39470, 0.15, 1, 89, 1, 1),
(@LOOT_ID + 6, 39467, 0.15, 1, 90, 1, 1),
(@LOOT_ID + 6, 39427, 0.15, 1, 91, 1, 1),
(@LOOT_ID + 6, 39468, 0.15, 1, 92, 1, 1),
(@LOOT_ID + 6, 45912, 0.1, 1, 93, 1, 1);

DELETE FROM reference_loot_template WHERE entry = @LOOT_ID;
INSERT INTO reference_loot_template VALUES
(@LOOT_ID, 22589, 1, 0, 1, 1, 1),
(@LOOT_ID, 22630, 1, 0, 1, 1, 1),
(@LOOT_ID, 22631, 1, 0, 1, 1, 1),
(@LOOT_ID, 22632, 1, 0, 1, 1, 1);

UPDATE `creature` SET `position_x` = 2890.915527, `position_y` = -808.266846, `position_z` = 160.332977, `orientation` = 5.091118 WHERE `guid` = 400007;

UPDATE `creature_template` SET `name` = "Caleb Runehold", `subname` = "Kirin Tor" WHERE `entry` = 400007;

