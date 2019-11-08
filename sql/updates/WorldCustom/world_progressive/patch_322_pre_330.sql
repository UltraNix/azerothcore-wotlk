--
-- === Content PRE 3.3.0 (PRE ICC FERONIS VERSION) ===
--

-- Remove disables for FOS, POS, HOR instances 
DELETE FROM `disables` WHERE `sourceType` = 2 AND `entry` IN (632, 658, 668);

SET @CONQUEST:= 45624;
SET @TRIUMPH:= 47241;

-- Update loot tables
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 38599 AND `item` = 45624; -- Farlic
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 38603 AND `item` = 45624; -- Marwyn

-- Hor chest
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27985 AND `item` = @CONQUEST;
INSERT INTO `gameobject_loot_template` VALUES
(27985, @CONQUEST, 100, 1, 0, 2, 2);

DELETE FROM `gameobject_loot_template` WHERE `entry` = 27993 AND `item` = @TRIUMPH;
INSERT INTO `gameobject_loot_template` VALUES
(27993, @TRIUMPH, 100, 1, 0, 2, 2);

UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37613 AND `item` = 45624; -- Garfrost
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37627 AND `item` = 45624; -- Ick
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 36938 AND `item` = 45624; -- Tyrannus

UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 36498 AND `item` = 45624; -- Bronhjam
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37677 AND `item` = 45624; -- Devourer

-- Update quest rewards
UPDATE `quest_template` SET `RewardItemId1` = 49426 WHERE `Id` IN (24511, 24499, 24710, 24712, 24500, 24802);

-- =============================================================================================