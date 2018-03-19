DELETE FROM `conditions` WHERE `SourceEntry` = 13718;
INSERT INTO `conditions` VALUES
(19, 0, 13718, 0, 0, 8, 0, 13684, 0, 0, 0, 0, 0, '', 'The valiants charge after a valiant of stormwind'),
(19, 0, 13718, 0, 1, 8, 0, 13593, 0, 0, 0, 0, 0, '', 'The valiants charge after valiant of stormwind'),
(20, 0, 13718, 0, 0, 8, 0, 13684, 0, 0, 0, 0, 0, '', 'The valiants charge after a valiant of stormwind'),
(20, 0, 13718, 0, 1, 8, 0, 13593, 0, 0, 0, 0, 0, '', 'The valiants charge after valiant of stormwind');

UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 13718, `ExclusiveGroup` = 13593 WHERE `id` = 13593;
UPDATE `quest_template` SET `PrevQuestId` = 13679, `NextQuestId` = 13718, `ExclusiveGroup` = 13593 WHERE `id` = 13684;
UPDATE `quest_template` SET `PrevQuestId` = 13593, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `id` = 13718;
