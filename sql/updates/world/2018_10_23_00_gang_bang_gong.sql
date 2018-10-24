DELETE FROM `game_event` WHERE `eventEntry`=135;
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(135, '0000-00-00 00:00:00', '2020-10-22 14:29:29', 5184000, 600, 0, 'The Scarab Lord', 0);

DELETE FROM `gameobject_queststarter` WHERE `id`=180718 AND `quest`=8743;
INSERT INTO `gameobject_queststarter` (`id`, `quest`) VALUES
(180718, 8743);

DELETE FROM `gameobject_questender` WHERE `id`=180718 AND `quest`=8743;
INSERT INTO `gameobject_questender` (`id`, `quest`) VALUES
(180718, 8743);

UPDATE `gameobject_template` SET `type`='2', `data1`='8743',  `data5`='0', `ScriptName`='go_the_scarab_gong' WHERE  `entry`=180718;
UPDATE `quest_template` SET `RewardItemId1`='0', `RewardItemCount1`='0', `RewardTitleId`='46' WHERE  `Id`=8743;
UPDATE `quest_template` SET `PrevQuestId`='8742' WHERE  `Id`=8745;

SET @TRINITY_STRING_ID:= 11037;
DELETE FROM `trinity_string` where `entry` IN (@TRINITY_STRING_ID, @TRINITY_STRING_ID + 1, @TRINITY_STRING_ID + 2);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES 
(@TRINITY_STRING_ID, "The Gates of Ahn'Qiraj have been opened by %s! Brave champions who want to finish the quest chain have 10 hours to complete it!|r"),
(@TRINITY_STRING_ID + 1, "Gates of Ahn'Qiraj Opening Event will end in %i hours and %i minutes|r"),
(@TRINITY_STRING_ID + 2, "Gates of Ahn'Qiraj Opening Event has ended! Congratulations for all those who completed it in time!|r");

UPDATE `creature_template` SET `ScriptName` = "npc_jonathan_the_revelator" WHERE `entry` = 15693;