UPDATE `creature_template` SET `InhabitType` = 3 WHERE `entry` = 22355;
UPDATE `gameobject` SET `spawntimesecs` = -300 WHERE `guid` = 47578;
UPDATE `gameobject` SET `rotation2` = -0.98 WHERE `guid` = 300017;
UPDATE `creature_template` SET `npcflag` = `npcflag` | 3 WHERE `entry` IN (19148, 19171, 19172, 19173);
DELETE FROM `pool_gameobject` WHERE `guid` IN (61422, 61424, 86021, 86032, 86506, 114665, 5111, 5155, 62287);
UPDATE `pool_gameobject` SET `chance` = 95 WHERE `guid` = 75213;
UPDATE `pool_gameobject` SET `chance` = 95 WHERE `guid` = 75228;
UPDATE `pool_gameobject` SET `chance` = 95 WHERE `guid` = 75318;
UPDATE `pool_gameobject` SET `chance` = 95 WHERE `guid` = 75360;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 30108;
INSERT INTO `npc_spellclick_spells` VALUES (30108, 46598, 1, 0);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.5 WHERE `entry` = 17308 AND `item` = 0;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0 WHERE `entry` = 34003 AND `groupid` = 2;

DELETE FROM `reference_loot_template` WHERE `entry` IN (34349, 34380);
