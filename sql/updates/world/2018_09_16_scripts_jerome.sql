DELETE FROM `creature_text` WHERE `entry` = 19882;
INSERT INTO `creature_text` VALUES
(19882, 0, 0, "Spare some change for a starving artist?", 12, 0, 100, 0, 0, 0, 0, 'Jerome'),
(19882, 0, 1,"Hey, you there. Want some candy?", 12, 0, 100, 0, 0, 0, 0, 'Jerome'),
(19882, 0, 2,"Bip!", 12, 0, 100, 0, 0, 0, 0, 'Jerome'),
(19882, 0, 3,"What up son! Wait, is anyone there?", 12, 0, 100, 0, 0, 0, 0, 'Jerome');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 19882 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(19882, 0, 1, 0, 1, 0, 100, 0, 5000, 10000, 20000, 30000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jerome - OOC - Say 0');
