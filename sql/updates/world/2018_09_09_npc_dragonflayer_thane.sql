UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 23660;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 23660;
INSERT INTO `smart_scripts` VALUES
(23660, 0, 0, 0, 0, 0, 100, 0, 5000, 10000, 15000, 20000, 11, 9080, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Thane - Aggro - Cast Harmstring'),
(23660, 0, 1, 0, 0, 0, 100, 0, 5000, 8000, 10000, 15000, 11, 11971, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Thane - Combat  - Cast Sunder Armor');
