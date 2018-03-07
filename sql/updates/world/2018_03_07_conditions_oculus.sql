SET @GAMEOBJECT_LOOT_TEMPLATE:= 24524;
SET @CACHE_OF_LEY_GUARDIAN:= 52676;

-- ToDo: zrobic jakis conditionTypeOrReference zeby sprawdzal tylko skrypt bo nie ma jak sie podczepic
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 4 AND `SourceGroup` = @GAMEOBJECT_LOOT_TEMPLATE AND `SourceEntry` = @CACHE_OF_LEY_GUARDIAN;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(4, @GAMEOBJECT_LOOT_TEMPLATE, @CACHE_OF_LEY_GUARDIAN, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 'condition_cache_of_lay_guardian', "Cache of ley guardian eregos only while in random dungeon");
