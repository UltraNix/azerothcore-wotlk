SET @CONQUEST = 45624;
SET @FROST = 49426;
SET @TRIUMPH = 47241;

UPDATE `creature_loot_template` SET `item` = @TRIUMPH WHERE `item` = @CONQUEST;
-- Marrowgar
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (37958, 37959, 36612, 37957);
-- Lady D
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (38297,38296, 36855, 38106);
-- Festergut
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (36626, 37504, 37505, 37506);
-- Rotface
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (36627, 38390, 38549, 38550);
-- Putricide
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (36678,38431, 38585, 38586);
-- Prince
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (37970,38401,38784,38785);
-- Blood Queen
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (37955, 38434, 38435, 38436);
-- Svalna
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (37126);
-- Sindragosa
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (36853,38265,38266, 38267);
-- Lich King
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` IN (36597, 39166, 39167, 39168);
-- Chesty ICC Gunship Valithria Saurfang-
UPDATE `gameobject_loot_template` SET `item` = @FROST WHERE `item` = @CONQUEST AND `entry` IN (28052,28082,28064,28096,28046,28074,28058,28088,28045,28072,28045,28072,28057,28090);
-- Pozostałe GO upgrade conqest -> triumph
UPDATE `gameobject_loot_template` SET `item` = @TRIUMPH WHERE `item` = @CONQUEST;
-- Toravon 
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `item` = @TRIUMPH AND `entry` = 38433;

DELETE FROM `creature_loot_template` WHERE `entry` = 32915 AND `item` = @TRIUMPH;
INSERT INTO `creature_loot_template` VALUES
(32915, @TRIUMPH, 100, 1, 0, 1, 1);

UPDATE `reference_loot_template` SET `item` = @TRIUMPH WHERE `item` = @CONQUEST;
UPDATE `item_loot_template` SET `item` = @TRIUMPH WHERE `item` = @CONQUEST;
UPDATE `item_loot_template` SET `item` = @FROST WHERE `entry` = 52006 AND `item` = @TRIUMPH;
