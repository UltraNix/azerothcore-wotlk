UPDATE `conditions` SET `ConditionTypeOrReference` = 28 WHERE `SourceGroup` = 28519 AND `SourceEntry` = 38673 AND `ElseGroup` = 0; 
DELETE FROM `conditions` WHERE `SourceGroup` = 28519 AND `SourceEntry` = 38673 AND `ElseGroup` = 1;
INSERT INTO `conditions` VALUES
(1, 28519, 38673, 0, 1, 8, 0, 12238, 0, 0, 0, 0, 0, '','');