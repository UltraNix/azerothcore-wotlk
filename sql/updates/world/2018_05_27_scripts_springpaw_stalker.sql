UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 15651 ;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 15651;
INSERT INTO `smart_scripts` VALUES
(15651, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 24450, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Springpaw Stalker - On Reset - Cast Prowl');
