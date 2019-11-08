-- Dadanie custom game eventu
DELETE FROM `game_event` WHERE `eventEntry` = 134;
INSERT INTO `game_event` VALUES
(134, "2018-06-12 10:05:00", "2020-12-31 06:00:00", 525600, 2592000, 0, 0, 'AT daily quest Counter', 1);
-- Zrobienie że oba quest dają po 1 do condition 44 
DELETE FROM `game_event_quest_condition` WHERE `eventEntry` = 134;
INSERT INTO `game_event_quest_condition` VALUES
(134, 13681, 44, 1),
(134, 13627, 44, 1);
-- definicja condition 44 czyli dla eventu 134 condition 44 teksty do wyswietlania
-- progresu 333 i 334
DELETE FROM `game_event_condition` WHERE `eventEntry` = 134;
INSERT INTO `game_event_condition` VALUES
(134, 44, 1000, 333, 334, 'AT Quests Progress');
-- update textu zeby zawieral 333 i 334
UPDATE `npc_text` SET `text0_0` = "No one builds it faster, cheaper, and better than the Blastbolt brothers! Completed daily quests: $333w " WHERE `ID` = 14426;
UPDATE `creature_template` SET `ScriptName` = "npc_blastbolt_brother" WHERE `entry` = 33434;
