UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 188539;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 188539;
INSERT INTO `smart_scripts` VALUES
(188539, 1, 0, 0, 8, 0, 100, 0, 47939, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Coldwind tree - on spell hit - despawn');

DELETE FROM `conditions` WHERE `SourceEntry` = 47939;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 47939, 0, 0, 31, 0, 5, 188539, 0, 0, 0, 0, '', 'Gather lumber - target coldwind tree');
