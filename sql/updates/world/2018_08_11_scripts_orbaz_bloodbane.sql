UPDATE `smart_scripts` SET `event_param2` = 120000, `event_param3` = 120000, `event_param4` = 180000 WHERE `entryorguid` = 31316 AND `id` = 0;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x01000000 WHERE `entry` = 31283;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 31318;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 31318;
INSERT INTO `smart_scripts` VALUES
(31318, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 0, 30, 0, 0, 0, 0, 'Death Knight Adept - Summoned - Attack Nearby Entry');
