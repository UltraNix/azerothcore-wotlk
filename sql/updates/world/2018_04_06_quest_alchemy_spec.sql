UPDATE `quest_template` SET `PrevQuestId` = 0 WHERE `id` IN (10897, 10902, 10899);
DELETE FROM `conditions` WHERE `SourceEntry` IN (10897, 10902, 10899) AND `SourceTypeOrReferenceId` IN (19,20);
INSERT INTO `conditions` VALUES
(19, 0, 10897, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10897, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10897, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10897, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10897, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10897, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10902, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10902, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10902, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10902, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10902, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10902, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10899, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10899, 0, 1, 8, 0, 10905, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10899, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10899, 0, 2, 8, 0, 10906, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(19, 0, 10899, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest'),
(20, 0, 10899, 0, 3, 8, 0, 10907, 0, 0, 0, 0, 0, '', 'Alchemy Special after any prequest');
