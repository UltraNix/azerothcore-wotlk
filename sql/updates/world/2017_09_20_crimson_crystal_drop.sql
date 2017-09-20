-- Fix for Crimson Crystal Shard's drop

DELETE FROM `creature_loot_template` WHERE `entry` = 19188 AND `item` = 29476;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(19188, 29476, 19.36, 1, 0, 1, 1);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=1 AND `SourceGroup`=19188 AND `SourceEntry`=29476 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=14 AND `ConditionTarget`=0 AND `ConditionValue1`=10134 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (1, 19188, 29476, 0, 0, 14, 0, 10134, 0, 0, 0, 0, 0, '', 'Drop Crimson Crystal Shard only if player has not completed Crimson Crystal Clue');
