UPDATE `creature` SET `spawntimesecs` = 30 WHERE `guid` IN (42887, 42888);
UPDATE `smart_scripts` SET `link` = 2 WHERE `id` = 1 AND `entryorguid` = 28013;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28013 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(28013, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On SpellHit - Despawn');
