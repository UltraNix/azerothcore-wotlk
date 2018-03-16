-- [Quest] No Mere Dream
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` IN (22834) AND `SourceId`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(22,2,22834,0,0,1,0,39601,1,0,1,0,'','Event SAI triggred only if the player don''t have the aura 39601');
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=22916;
