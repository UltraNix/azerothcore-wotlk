UPDATE `quest_template` SET `nextQuestIdChain` = 13034 WHERE `id` = 13426;
UPDATE `quest_template` SET `prevQuestId` = 13426 WHERE `id` = 13034; -- witness and the hero after xarantaur the witness

-- memories of stormhoof & distrotion in time after witness and the hero
UPDATE `quest_template` SET `prevQuestId` = 13034, `ExclusiveGroup` = 0, `NextQuestId` = 0 WHERE `id` = 13037;
UPDATE `quest_template` SET `prevQuestId` = 13034, `ExclusiveGroup` = 0, `NextQuestId` = 0 WHERE `id` = 13038;

-- where time went wrong & the hero's arm after the two quests above
UPDATE `quest_template` SET `prevQuestId` = 13037, `ExclusiveGroup` = -13048, `NextQuestId` = 13058 WHERE `id` = 13048;
UPDATE `quest_template` SET `prevQuestId` = 13038, `ExclusiveGroup` = -13048, `NextQuestId` = 13058 WHERE `id` = 13049;

-- changing the wind's course after two quests above
UPDATE `quest_template` SET `prevQuestId` = 0, `ExclusiveGroup` = 0 WHERE `id` = 13058;

DELETE FROM `creature` WHERE `guid` = 1955014;

UPDATE `creature_template` SET `ScriptName` = "npc_stormpeaks_stormhoof" WHERE `entry` = 30388;
UPDATE `creature_template` SET `ScriptName` = "npc_northwind_stormpeaks", `AIName` = "" WHERE `entry` = 30474;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30474;
