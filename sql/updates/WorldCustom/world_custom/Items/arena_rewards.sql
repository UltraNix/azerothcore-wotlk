SET @WIN_ENTRY := 1672;
SET @LOSS_ENTRY := 4868;

SET @RENTRY := @WIN_ENTRY * 10 + 1;
DELETE FROM `reference_loot_template` WHERE `entry` = @RENTRY;
INSERT INTO `reference_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@RENTRY, 34822, 0, 1, 1, 1, 1),
(@RENTRY, 45980, 0, 1, 1, 1, 1),
(@RENTRY, 45981, 0, 1, 1, 1, 1),
(@RENTRY, 34823, 0, 1, 1, 1, 1),
(@RENTRY, 34824, 0, 1, 1, 1, 1),
(@RENTRY, 34825, 0, 1, 1, 1, 1),
(@RENTRY, 43522, 0, 1, 1, 1, 1),
(@RENTRY, 45979, 0, 1, 1, 1, 1),
(@RENTRY, 43521, 0, 1, 1, 1, 1),
(@RENTRY, 27442, 0, 1, 1, 1, 1),
(@RENTRY, 54470, 0, 1, 1, 1, 1),
(@RENTRY, 34476, 0, 1, 1, 1, 1);

SET @RENTRY := @WIN_ENTRY * 10 + 2;
DELETE FROM `reference_loot_template` WHERE `entry` = @RENTRY;
INSERT INTO `reference_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@RENTRY, 38233, 0, 1, 1, 3, 3),
(@RENTRY, 46779, 0, 1, 1, 3, 3),
(@RENTRY, 41427, 0, 1, 1, 5, 5),
(@RENTRY, 9317, 0, 1, 1, 5, 5),
(@RENTRY, 19026, 0, 1, 1, 5, 5);

SET @RENTRY := @WIN_ENTRY * 10 + 3;
DELETE FROM `reference_loot_template` WHERE `entry` = @RENTRY;
INSERT INTO `reference_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@RENTRY, 44115, 0, 1, 1, 1, 1),
(@RENTRY, 38311, 0, 1, 1, 1, 1),
(@RENTRY, 45037, 0, 1, 1, 1, 1),
(@RENTRY, 45063, 0, 1, 1, 1, 1),
(@RENTRY, 46780, 0, 1, 1, 1, 1),
(@RENTRY, 34499, 0, 1, 1, 1, 1),
(@RENTRY, 36922, 0, 1, 1, 1, 1),
(@RENTRY, 36934, 0, 1, 1, 1, 1),
(@RENTRY, 36931, 0, 1, 1, 1, 1),
(@RENTRY, 36928, 0, 1, 1, 1, 1),
(@RENTRY, 36925, 0, 1, 1, 1, 1);

SET @RENTRY := @WIN_ENTRY * 10 + 4;
DELETE FROM `reference_loot_template` WHERE `entry` = @RENTRY;
INSERT INTO `reference_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@RENTRY, 38050, 0, 1, 1, 1, 1),
(@RENTRY, 39656, 0, 1, 1, 1, 1),
(@RENTRY, 49287, 0, 1, 1, 1, 1),
(@RENTRY, 49646, 0, 1, 1, 1, 1),
(@RENTRY, 8628, 0, 1, 1, 1, 1);

SET @RENTRY := @WIN_ENTRY * 10 + 5;
DELETE FROM `reference_loot_template` WHERE `entry` = @RENTRY;
INSERT INTO `reference_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@RENTRY, 54068, 0, 1, 1, 1, 1),
(@RENTRY, 54069, 0, 1, 1, 1, 1),
(@RENTRY, 35226, 0, 1, 1, 1, 1);

DELETE FROM `item_template` WHERE `item_template`.`entry` = @WIN_ENTRY;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(@WIN_ENTRY, 15, 0, -1, 'Bloody Sack of Goods', 56915, 4, 4, 0, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, '', 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, '', 0, 0, 100, 3000, 0, 12340);

DELETE FROM `item_loot_template` WHERE `entry` = @WIN_ENTRY;
INSERT INTO `item_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@WIN_ENTRY, 1, 100, 1, 0, -(@WIN_ENTRY * 10 + 1), 1),
(@WIN_ENTRY, 2, 20, 1, 0, -(@WIN_ENTRY * 10 + 2), 1),
(@WIN_ENTRY, 3, 5, 1, 0, -(@WIN_ENTRY * 10 + 3), 1),
(@WIN_ENTRY, 4, 2, 1, 0, -(@WIN_ENTRY * 10 + 4), 1),
(@WIN_ENTRY, 5, 0.5, 1, 0, -(@WIN_ENTRY * 10 + 5), 1),
(@WIN_ENTRY, 8628, 0.10, 1, 0, 1, 1),
(@WIN_ENTRY, 13317, 0.05, 1, 0, 1, 1),
(@WIN_ENTRY, 12302, 0.05, 1, 0, 1, 1),
(@WIN_ENTRY, 43651, 0.05, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 5 AND `sourcegroup` = @WIN_ENTRY;
INSERT INTO `conditions` VALUES 
(5,@WIN_ENTRY,12302,0,0,6,0,469,0,0,0,0,0,'','Bloody Sack of Goods - Reins of the Ancient Frostsaber can drop only for Alliance'),
(5,@WIN_ENTRY,13317,0,0,6,0,67,0,0,0,0,0,'','Bloody Sack of Goods - Whistle of the Ivory Raptor can drop only for Horde');


DELETE FROM `item_template` WHERE `item_template`.`entry` = @LOSS_ENTRY;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `VerifiedBuild`) VALUES
(@LOSS_ENTRY, 15, 0, -1, 'Bloody Satchel of Goods', 56915, 4, 4, 0, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 1, '', 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, '', 0, 0, 100, 3000, 0, 12340);

DELETE FROM `item_loot_template` WHERE `entry` = @LOSS_ENTRY;
INSERT INTO `item_loot_template`(`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOSS_ENTRY, 1, 10, 1, 0, -(@WIN_ENTRY * 10 + 1), 1),
(@LOSS_ENTRY, 2, 20, 1, 0, -(@WIN_ENTRY * 10 + 2), 1),
(@LOSS_ENTRY, 3, 0.5, 1, 0, -(@WIN_ENTRY * 10 + 3), 1),
(@LOSS_ENTRY, 4, 0.1, 1, 0, -(@WIN_ENTRY * 10 + 4), 1),
(@LOSS_ENTRY, 5, 0.05, 1, 0, -(@WIN_ENTRY * 10 + 5), 1),
(@LOSS_ENTRY, 13317, 0.01, 1, 0, 1, 1),
(@LOSS_ENTRY, 12302, 0.01, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 5 AND `sourcegroup` = @LOSS_ENTRY;
INSERT INTO `conditions` VALUES 
(5,@LOSS_ENTRY,12302,0,0,6,0,469,0,0,0,0,0,'','Bloody Satchel of Goods - Reins of the Ancient Frostsaber can drop only for Alliance'),
(5,@LOSS_ENTRY,13317,0,0,6,0,67,0,0,0,0,0,'','Bloody Satchel of Goods - Whistle of the Ivory Raptor can drop only for Horde');

DELETE FROM `trinity_string` WHERE `entry` IN (10510, 10511);
INSERT INTO `trinity_string`(`entry`, `content_default`) VALUES
(10510, "You have won the arena match. |cffa335ee|Hitem:1672:0:0:0:0:0:0:0:80|h[Bloody Sack of Goods]|h|r has been added to your inventory."),
(10511, "You have lost the arena match. |cffa335ee|Hitem:4868:0:0:0:0:0:0:0:80|h[Bloody Satchel of Goods]|h|r has been added to your inventory.");