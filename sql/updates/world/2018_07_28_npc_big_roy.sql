DELETE FROM `pool_template` WHERE `entry` = 50003;
INSERT INTO `pool_template` VALUES
(50003, 1, "Big Roy");
DELETE FROM `pool_creature` WHERE `guid` IN (203340, 203496);
INSERT INTO `pool_creature` VALUES
(203340, 50003, 0, "Big Roy"),
(203496, 50003, 0, "Big Roy");
UPDATE `creature` SET `spawntimesecs` = 60 WHERE `guid` IN  (203340, 203496);
