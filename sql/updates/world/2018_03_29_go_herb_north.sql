UPDATE `gameobject` SET `spawntimesecs` = 300 WHERE `id` IN (191019,190171,190170) AND `spawntimesecs` < 2700;
UPDATE `gameobject` SET `spawntimesecs` = 300 WHERE `spawntimesecs` < 900 AND `id` IN (189973, 190169);
UPDATE `gameobject` SET `spawntimesecs` = 300 WHERE `id` IN (189981,191133,189980) AND `spawntimesecs` < 600;

DELETE FROM `pool_template` WHERE `entry` = 11640;
INSERT INTO `pool_template` VALUES
(11640, 1, '');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = 11640;
INSERT INTO `pool_gameobject` VALUES
(164080, 11640, 0, ''),
(163680, 11640, 0, '');

DELETE FROM `gameobject` WHERE `guid` IN (86032, 61424, 61422, 86506, 86021);
INSERT INTO `gameobject` VALUES
(61422, 191019, 571, 1, 1, 5864.65, 4654.4, -134.191, 1.06465, 0, 0, 0, 1, 300, 100, 1, 0),
(61424, 191019, 571, 1, 1, 5838.46, 4507.45, -132.164, -2.23402, 0, 0, 0, 1, 300, 100, 1, 0),
(86021, 191019, 571, 1, 1, 5760.06, 4716.53, -133.105, -1.36136, 0, 0, 0, 1, 300, 255, 1, 0),
(86032, 191019, 571, 1, 1, 5714.81, 4730.84, -136.111, 0.296705, 0, 0, 0, 1, 300, 255, 1, 0),
(86506, 190169, 571, 1, 1, 5787.84, 4815.88, -137.03, 2.54818, 0, 0, 0, 1, 900, 255, 1, 0);
