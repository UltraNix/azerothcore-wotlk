DELETE FROM `game_event` WHERE `eventEntry`=135;
DELETE FROM `game_event` WHERE `eventEntry`=136;
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(135, '2010-01-02 00:10:00', '2020-12-31 06:00:00', 525600, 600, 0, 'The Scarab Lord', 0),
(136, '2010-01-02 00:10:00', '2020-12-31 06:00:00', 525600, 10080, 0, 'The Scarab Lord Lock', 0);

DELETE FROM `gameobject_queststarter` WHERE `id`=180718 AND `quest`=8743;
INSERT INTO `gameobject_queststarter` (`id`, `quest`) VALUES (180718, 8743);

DELETE FROM `gameobject_questender` WHERE `id`=180718 AND `quest`=8743;
INSERT INTO `gameobject_questender` (`id`, `quest`) VALUES (180718, 8743);

UPDATE `gameobject_template` SET `type`='2', `data1`='8743',  `data5`='0', `ScriptName`='go_the_scarab_gong' WHERE  `entry`=180718;
UPDATE `quest_template` SET `RewardItemId1`='0', `RewardItemCount1`='0', `RewardTitleId`='46' WHERE  `Id`=8743;
UPDATE `quest_template` SET `PrevQuestId`='8743' WHERE  `Id`=8745;

DELETE FROM `trinity_string` where `entry` IN ('11030', '11031');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES 
('11031', ' Player %s opened gates of Ahn\'Qiraj! The daredevil who wants to finish the event left 10 hours!|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES 
('11030', 'Gracz %s otworzyl bramy Ahn\'Qiraj! Smialkom, ktorzy chca ukonczyc event pozostalo 10 godzin!|r');
