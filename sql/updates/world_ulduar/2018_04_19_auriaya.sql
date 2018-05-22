UPDATE `creature_template` SET `ScriptName` = "npc_swarming_guardian_auriaya", `AIName` = "" WHERE `entry` = 34034;
DELETE FROM `conditions` WHERE `sourceEntry` = 64397;
INSERT INTO `conditions` VALUES
(13, 1, 64397, 0, 0, 31, 0, 3, 33515, 0, 0, 0, 0, '', 'summon swarming guardian target auriaya');
