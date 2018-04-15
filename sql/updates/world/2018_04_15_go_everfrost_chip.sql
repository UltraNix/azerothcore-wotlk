UPDATE `gameobject_loot_template` SET `groupid` = 1 WHERE `entry` = 26782 AND `item` = 44724;
UPDATE `gameobject_loot_template` SET `groupid` = 2 WHERE `entry` = 26782 AND `item` = 44725;

DELETE FROM `conditions` WHERE `SourceEntry` = 44725 AND `SourceTypeOrReferenceId` = 4;
INSERT INTO `conditions` VALUES
(4, 26782, 44725, 0, 0, 8, 0, 13420, 0, 0, 1, 0, 0, '', 'Show Everfrost chip if player has not rewarded quest Everfrost');
