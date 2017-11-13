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
UPDATE `creature_template` SET `health_mod` = 585 WHERE `entry` = 400040;
UPDATE `creature_template` SET `health_mod` = 450 WHERE `entry` = 400041;
UPDATE `creature_template` SET `health_mod` = 321.75, `mindmg` = 700, `maxdmg` = 800 WHERE `entry` = 400040;
UPDATE `creature_template` SET `health_mod` = 1100 WHERE `entry` = 400010;
UPDATE `creature_template` SET `health_mod` = 30 WHERE `entry` = 400015;
UPDATE `creature_template` SET `health_mod` = 3 WHERE `entry` = 400016;

SET @LOOT_ID:= 33755;
UPDATE `creature_template` SET `lootid` = @LOOT_ID WHERE `entry` IN (400050, 400051, 400052, 400053, 400054);

UPDATE `creature_template` SET `mingold` = 10000000, `maxgold` = 10000000 WHERE `entry` = 400022;
UPDATE `creature_template` SET `mingold` = 12500000, `maxgold` = 12500000 WHERE `entry` = 400000;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400008;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400041;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400043;
UPDATE `creature_template` SET `mingold` = 15000000, `maxgold` = 15000000 WHERE `entry` = 400010;

UPDATE `creature_template` SET `name` = "Prince Val’sameth", `subname` = "<The San’layn>", `modelid1` = 28194 WHERE `entry` = 400022;
UPDATE `creature_template` SET `subname` = "<The Unforseen>" WHERE `entry` = 400000;
UPDATE `creature_template` SET `subname` = "<The Gatekeeper>" WHERE `entry` = 400008;
UPDATE `creature_template` SET `name` = "Va’Thanui", `subname` = "<Void Lord>" WHERE `entry` = 400041;
