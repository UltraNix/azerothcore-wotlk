UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 29358;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 29358;
INSERT INTO `smart_scripts` VALUES
(29358, 0, 0, 0, 0, 0, 100, 512, 2000, 5000, 7000, 9000, 11, 61572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Frostworg - IC - Cast Frostbite'),
(29358, 0, 1, 0, 0, 0, 100, 512, 2000, 6000, 6000, 9000, 11, 50075, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Frostworg - IC - Cast Maim Flesh');

DELETE FROM `creature_loot_template` WHERE `entry` = 29358 AND `item` IN (43011, 43013);
INSERT INTO `creature_loot_template` VALUES
(29358, 43013, 12, 1, 0, 1, 1),
(29358, 43011, 61, 1, 0, 1, 1);