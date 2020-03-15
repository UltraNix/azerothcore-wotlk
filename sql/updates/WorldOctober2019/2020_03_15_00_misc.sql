-- DB/NPC: Chillmaw - reduce respawn rate https://github.com/SunwellTracker/issues/issues/2933
-- DB/Loot: Big Mouth Clam - redo drop table - https://github.com/SunwellTracker/issues/issues/2938
UPDATE `creature` SET `spawntimesecs` = 120 WHERE `id` = 33687;

DELETE FROM `spell_loot_template` WHERE `entry` = 58165;
INSERT INTO `spell_loot_template` (`Entry`, `Item`, `ChanceOrQuestChance`, `LootMode`, `GroupId`,`MinCountOrRef`,`MaxCount`) VALUES
(58165,  7974,100.0,   1, 0, 1, 1),
(58165,  7971,  4.0, 1, 1, 1, 1),
(58165, 13926,  1.7, 1, 1, 1, 1),
(58165,  5500,  2.3, 1, 1, 1, 1),
(58165,  5498,  1.0, 1, 1, 1, 1);
