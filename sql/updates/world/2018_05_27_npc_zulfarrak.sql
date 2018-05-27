SET @PATH = 100800;
SET @PATH2 = 100810;
SET @CGUID = 138255;
SET @CGUID2 = 81459;

SET @POOL = 1784;
DELETE FROM `pool_template` WHERE `entry` IN (@POOL,@POOL+1,@POOL+2, 5662);
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Zulfarrak rare boss spawn'),
(@POOL+1, 1, 'Zulfarrak rare boss spawn'),
(@POOL+2, 1, 'Zulfarrak rare boss spawn'),
(5662, 1, 'Zulfarrak rare boss spawn');

DELETE FROM `pool_creature` WHERE `guid` IN (@CGUID, @CGUID+1, @CGUID+2, @CGUID2);
DELETE FROM `pool_creature` WHERE `pool_entry` IN (@POOL, @POOL+1, @POOL+2);
INSERT INTO `pool_creature` VALUES
(@CGUID, @POOL, 10, 'Zulfarrak rare boss'),
(38014, @POOL, 90, 'Zulfarrak rare boss'),
(@CGUID+1, @POOL+1, 10, 'Zulfarrak rare boss'),
(38018, @POOL+1, 90, 'Zulfarrak rare boss'),
(@CGUID+2, @POOL+2, 10, 'Zulfarrak rare boss'),
(42615, @POOL+2, 90, 'Zulfarrak rare boss');
