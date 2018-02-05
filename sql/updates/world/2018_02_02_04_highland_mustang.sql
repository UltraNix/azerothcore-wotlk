UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_highland_mustang" WHERE `entry` = 26472;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26472;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (49282, 49285);
INSERT INTO `spell_script_names` VALUES
(49285, "spell_hand_over_reins_49285");

UPDATE `creature_template` SET `spell2` = 29577 WHERE `entry` = 26472;
