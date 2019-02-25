-- DB/Quest: Tome of Valor - Daphne Stilwell reduce respawn time
-- DB/NPC: Arcane Vortex - correct flags
-- DB/NPC: Wretched Captive - correct behavior
-- DB/Loot: Chosen Zealot - update loottable
-- DB/Loot: Satchel of Spoils, Large Sack of Ulduar Spoils, Sack of Ulduar Spoils - will drop Emblem of Triumph
UPDATE `creature` SET `spawntimesecs` = 10 WHERE `id` = 6182;
UPDATE `creature` SET `spawntimesecs` = 2700 WHERE `id` IN (17378, 24222, 17407, 17408);
UPDATE `creature_template` SET `faction` = 190, `unit_flags` = 33555200 WHERE `entry` = 17408;

DELETE FROM `creature` WHERE `guid` = 58691;
DELETE FROM `creature` WHERE `guid` = 501696;
INSERT INTO `creature` VALUES 
(501696, 16916, 530, 1, 1, 0, 0, 9513.45, -6838.06, 16.5768, 4.28651, 300, 0, 0, 98, 115, 2, 0, 0, 0);
UPDATE `creature_template` SET `AIName` = "AIName" WHERE `entry` = 16916;

DELETE FROM `creature_loot_template` WHERE `entry` = 32175 AND `item` IN (33470, 33443, 33447, 33448, 35952);
INSERT INTO `creature_loot_template` VALUES
(32175, 33470, 50, 1, 0, 1, 4),
(32175, 33443, 25, 1, 0, 1, 1),
(32175, 33447, 10, 1, 0, 1, 1),
(32175, 33448, 10, 1, 0, 1, 1),
(32175, 35952, 4.9, 1, 0, 1, 1);

DELETE FROM `item_loot_template` WHERE `entry` = 43347;
INSERT INTO `item_loot_template` VALUES 
(43347, 47241, 100, 1, 0, 5, 5);

UPDATE `item_loot_template` SET `item` = 47241 WHERE `entry` = 45878 AND `item` = 45624;
UPDATE `item_loot_template` SET `item` = 47241 WHERE `entry` = 45875 AND `item` = 40753;
