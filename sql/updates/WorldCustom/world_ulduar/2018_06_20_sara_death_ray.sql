UPDATE `creature_template` SET `InhabitType` = 4, `flags_extra` = 128 WHERE `entry` IN (33881);
UPDATE `conditions` SET `ConditionValue2` = 33881 WHERE `SourceEntry` = 63886 AND `SourceTypeOrReferenceId` = 13;
UPDATE `conditions` SET `ConditionValue2` = 33881 WHERE `SourceEntry` = 63882 AND `SourceTypeOrReferenceId` = 13;
