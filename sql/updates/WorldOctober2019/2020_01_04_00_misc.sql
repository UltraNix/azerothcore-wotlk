-- DB/Quest: Spread the Good Word - fix issue with vehicles not respawning https://github.com/SunwellTracker/issues/issues/2706
-- DB/Quest: Sleeping Giants - correct prequest to "Of Keys and Cages" https://github.com/SunwellTracker/issues/issues/2700
-- DB/Item: Add paladin shoulder pieces to Meminnie vendor https://github.com/SunwellTracker/issues/issues/2695
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 26523;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26523;
INSERT INTO `smart_scripts` VALUES
(26523, 0, 0, 0, 28, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0, 'On passanger removed - Despawn');

UPDATE `quest_template` SET `PrevQuestId` = 11231 WHERE `id` = 11432;

DELETE FROM `npc_vendor` WHERE `entry` = 19857 AND `item` IN (33699, 33726, 33753);
INSERT INTO `npc_vendor` VALUES
(19857, 0, 33699, 0, 0, 2288),
(19857, 0, 33726, 0, 0, 2288),
(19857, 0, 33753, 0, 0, 2288);
