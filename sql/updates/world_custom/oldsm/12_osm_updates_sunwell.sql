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

SET @LOOT_ID:= 33755;
UPDATE `creature_template` SET `lootid` = @LOOT_ID WHERE `entry` IN (400050, 400051, 400052, 400053, 400054);

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

UPDATE `creature_text` SET `text` = "Uhh.. strangers.. I''m Prince Val’sameth, are you here to fight me?" WHERE `entry` = 400022;
DELETE FROM `creature_equip_template` WHERE `entry` = 400043;

UPDATE `creature_template` SET `health_mod` = 40 WHERE `entry` = 400009;
UPDATE `creature_template` SET `mindmg` = 1200, `maxdmg` = 1300, `dmg_multiplier` = 100, `health_mod` = 1000 WHERE `entry` = 400008;
