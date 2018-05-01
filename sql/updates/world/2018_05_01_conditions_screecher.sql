UPDATE `conditions` SET `ConditionValue2` = 20, `ConditionValue3` = 1 WHERE `SourceTypeOrReferenceId` = 17 AND `SourceEntry` = 12699 AND `ElseGroup` = 0;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 17 AND `SourceEntry` = 12699 AND `ElseGroup` = 1; 
INSERT INTO `conditions` VALUES 
(17, 0, 12699, 0, 1, 29, 0, 5308, 20, 1, 0, 0, 0, '', 'Summon Screecher Spirit should target dead RogueVale Screecher');
