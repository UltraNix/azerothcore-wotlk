SET @FROST = 49426;
SET @TRIUMPH = 47241;
UPDATE `creature_loot_template` SET `item` = @FROST WHERE `entry` = 38462 AND `item` = @TRIUMPH;
