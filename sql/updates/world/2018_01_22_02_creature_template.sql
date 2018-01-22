UPDATE `creature_template` SET `modelid2` = 26767, `AIName` = "", `ScriptName` = "npc_flame_orb_mistress", `InhabitType` = 4, `flags_extra` = `flags_extra` | 128, `HoverHeight` = 7, `minlevel` = 80, `maxlevel` = 80, `scale` = 2, `unit_flags` = `unit_flags` | 33554432 WHERE `entry` = 30702;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30681;
UPDATE `creature_template` SET `ScriptName` = "npc_blaze_mistress_sarthrion", `AIName` = "" WHERE `entry` = 30681;
DELETE FROM `spell_script_names` WHERE `spell_id` = 57752;
INSERT INTO `spell_script_names` VALUES
(57752, "spell_summon_flame_orb_mistress");
