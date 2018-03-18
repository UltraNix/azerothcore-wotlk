-- Utgarde Pinnacle
UPDATE `creature_template` SET `lootid` = 30766 WHERE `entry` IN (30766,30764,30765,30806,30821,30818,30762,30820,30816);

DELETE FROM `creature_loot_template` WHERE `item` IN (37590,37587) AND `entry` IN
(SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` IN (30766,30764,30765,30806,30821,30818,30762,30820,30816));

DELETE FROM `creature_loot_template` WHERE `entry` = 30766;
INSERT INTO `creature_loot_template` VALUES
(30766, 26001, 6, 1, 1, -26001, 1),
(30766, 26040, 31.9, 1, 0, -26040, 1),
(30766, 33424, 1.1, 1, 0, 1, 1),
(30766, 33445, 4.3, 1, 0, 1, 1),
(30766, 33454, 6.7, 1, 0, 1, 1),
(30766, 37587, 1.5, 1, 0, 1, 1),
(30766, 37590, 1.7, 1, 0, 1, 1),
(30766, 39152, 1.3, 1, 0, 1, 1),
(30766, 43624, 0.02, 1, 0, 1, 1),
(30766, 43852, 15.7, 1, 0, 1, 1),
(30766, 45912, 0.1, 1, 0, 1, 1);
