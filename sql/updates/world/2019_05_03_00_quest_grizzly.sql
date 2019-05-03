-- DB/Quest: Keep 'Em on Their Heels/ Kick 'Em While They're Down - resolve issue with friendly npcs showing up as quest objective
DELETE FROM `creature_template` WHERE `entry` = 56891;
INSERT INTO `creature_template` VALUES 
(56891, 0, 0, 0, 0, 0, 16480, 19595, 0, 0, 'Blue Sky Kill Credit Bunny - Grizzly Hills HORDE', '', '', 0, 60, 60, 1, 35, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 0, 1, 0, 2048, 8, 0, 0, 0, 0, 0, 1, 1, 0, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340);

UPDATE `quest_template` SET `RequiredNpcOrGo1` = 56891 WHERE `id` = 12289;
UPDATE `creature_template` SET `KillCredit1` = 56891 WHERE `entry` IN (27456, 27463);
