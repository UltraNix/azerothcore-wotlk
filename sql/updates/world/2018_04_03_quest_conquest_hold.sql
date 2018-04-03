-- Vordrassil
UPDATE `quest_template` SET `PrevQuestId` = 0, `ExclusiveGroup` = -12207 WHERE `id` IN (12207, 12213);
UPDATE `quest_template` SET `PrevQuestId` = 12207, `ExclusiveGroup` = -12231 WHERE `id` IN (12231, 12229);
UPDATE `quest_template` SET `PrevQuestId` = 12231 WHERE `id` IN (12242, 12241);

DELETE FROM `conditions` WHERE `SourceEntry` IN (12207, 12213) AND `SourceTypeOrReferenceId` IN (19, 20);
INSERT INTO `conditions` VALUES
(19, 0, 12207, 0, 0, 8, 0, 12413, 0, 0, 0, 0, 0, '', ''),
(20, 0, 12207, 0, 0, 8, 0, 12413, 0, 0, 0, 0, 0, '', ''),
(19, 0, 12213, 0, 0, 8, 0, 12413, 0, 0, 0, 0, 0, '', ''),
(20, 0, 12213, 0, 0, 8, 0, 12413, 0, 0, 0, 0, 0, '', '');

-- Voldrune
UPDATE `quest_template` SET `PrevQuestId` = 0 WHERE `id` = 12468;
UPDATE `quest_template` SET `PrevQuestId` = 12468 WHERE `id` IN (12256, 12257);
UPDATE `quest_template` SET `PrevQuestId` = 12256 WHERE `id` = 12259;
UPDATE `quest_template` SET `PrevQuestId` = 12259 WHERE `id` = 12451;

-- Silverbrook
UPDATE `quest_template` SET `PrevQuestId` = 12424 WHERE `id` = 12425;
UPDATE `quest_template` SET `PrevQuestId` = 12423 WHERE `id` = 12453;
UPDATE `quest_template` SET `PrevQuestId` = 12412 WHERE `id` = 12208;
