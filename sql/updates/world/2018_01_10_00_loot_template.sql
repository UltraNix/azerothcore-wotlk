SET @CONQUEST:= 45624;
SET @TRIUMPH:= 47241;

/* emblemy */
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 38599 AND `item` = 45624; -- farlic
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 38603 AND `item` = 45624; -- marwyn
-- skrzynka HOR
DELETE FROM `gameobject_loot_template` WHERE `entry` = 27985 AND `item` = @CONQUEST;
INSERT INTO `gameobject_loot_template` VALUES
(27985, @CONQUEST, 100, 1, 0, 2, 2);

DELETE FROM `gameobject_loot_template` WHERE `entry` = 27993 AND `item` = @TRIUMPH;
INSERT INTO `gameobject_loot_template` VALUES
(27993, @TRIUMPH, 100, 1, 0, 2, 2);

UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37613 AND `item` = 45624; -- garfrost
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37627 AND `item` = 45624; -- ick
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 36938 AND `item` = 45624; -- tyrannus

UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 36498 AND `item` = 45624; -- bronhjam
UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `entry` = 37677 AND `item` = 45624; -- devourer

/* quest rewardy */
UPDATE `quest_template` SET `RewardItemId1` = 49426 WHERE `Id` IN (24511, 24499, 24710, 24712, 24500, 24802);
