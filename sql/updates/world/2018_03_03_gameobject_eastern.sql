SET @POOL = 1765;
DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(64098, @POOL, 0, 'Spawn Point EK - Truesilver'),
(45561, @POOL, 0, 'Spawn Point EK - Small Thorium');

DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Spawn Point EK - Truesilver');

SET @POOL = 1765;
DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(146,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(155,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(156,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(165,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(174,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(218,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(232,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(253,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(255,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(260,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(268,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(283,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(295,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(297,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(307,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(328,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(337,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(368,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5769,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5770,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5778,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5783,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5788,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5799,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5816,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5819,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5838,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5849,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5859,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5861,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5863,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5893,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5944,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5952,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(5956,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(6000,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9229,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9269,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9271,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9303,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9338,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9362,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9376,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9391,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9393,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9403,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9404,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9571,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9620,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9638,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(9641,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45497,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45498,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45499,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45502,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45505,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45551,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45553,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45560,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(45561,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63212,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63214,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63216,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63217,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63518,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(63519,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(64098,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(65375,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(120251,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(120252,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(120256,@POOL, 0, 'Western Plaguelands - Gold-Truesilver'),
(120584,@POOL, 0, 'Western Plaguelands - Gold-Truesilver');

DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 25, 'Western Plaguelands - Gold-Truesilver');


SET @POOL = 1766;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 15, 'Copper Vein - Trisfa');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(4650,@POOL, 0, 'Copper Vein - Trisfa'),
(4687,@POOL, 0, 'Copper Vein - Trisfa'),
(4705,@POOL, 0, 'Copper Vein - Trisfa'),
(4758,@POOL, 0, 'Copper Vein - Trisfa'),
(4973,@POOL, 0, 'Copper Vein - Trisfa'),
(5068,@POOL, 0, 'Copper Vein - Trisfa'),
(5093,@POOL, 0, 'Copper Vein - Trisfa'),
(5098,@POOL, 0, 'Copper Vein - Trisfa'),
(5102,@POOL, 0, 'Copper Vein - Trisfa'),
(5104,@POOL, 0, 'Copper Vein - Trisfa'),
(5155,@POOL, 0, 'Copper Vein - Trisfa'),
(5210,@POOL, 0, 'Copper Vein - Trisfa'),
(5332,@POOL, 0, 'Copper Vein - Trisfa'),
(5357,@POOL, 0, 'Copper Vein - Trisfa'),
(5367,@POOL, 0, 'Copper Vein - Trisfa'),
(5457,@POOL, 0, 'Copper Vein - Trisfa'),
(5478,@POOL, 0, 'Copper Vein - Trisfa'),
(5480,@POOL, 0, 'Copper Vein - Trisfa'),
(35514,@POOL, 0, 'Copper Vein - Trisfa'),
(35513,@POOL, 0, 'Copper Vein - Trisfa'),
(35511,@POOL, 0, 'Copper Vein - Trisfa'),
(35491,@POOL, 0, 'Copper Vein - Trisfa'),
(35490,@POOL, 0, 'Copper Vein - Trisfa'),
(35479,@POOL, 0, 'Copper Vein - Trisfa'),
(35443,@POOL, 0, 'Copper Vein - Trisfa'),
(35527,@POOL, 0, 'Copper Vein - Trisfa'),
(35534,@POOL, 0, 'Copper Vein - Trisfa'),
(35535,@POOL, 0, 'Copper Vein - Trisfa'),
(35536,@POOL, 0, 'Copper Vein - Trisfa'),
(35537,@POOL, 0, 'Copper Vein - Trisfa'),
(45033,@POOL, 0, 'Copper Vein - Trisfa'),
(120342,@POOL, 0, 'Copper Vein - Trisfa'),
(120345,@POOL, 0, 'Copper Vein - Trisfa');

SET @POOL = 1767;

DELETE FROM `pool_gameobject` WHERE `guid` IN 
(42063,
42062,
4757,
4846,
4979,
5023,
5028,
5059,
5065,
5111,
5217,
5395,
5397,
5402,
5460,
35571,
75227,
35444,
75212,
75317,
75359,
120343);
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 10, 'Copper Vein - Silverpine');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(42063,@POOL, 0, 'Copper Vein - Silverpine'),
(42062,@POOL, 0, 'Copper Vein - Silverpine'),
(4757,@POOL, 0, 'Copper Vein - Silverpine'),
(4846,@POOL, 0, 'Copper Vein - Silverpine'),
(4979,@POOL, 0, 'Copper Vein - Silverpine'),
(5023,@POOL, 0, 'Copper Vein - Silverpine'),
(5028,@POOL, 0, 'Copper Vein - Silverpine'),
(5059,@POOL, 0, 'Copper Vein - Silverpine'),
(5065,@POOL, 0, 'Copper Vein - Silverpine'),
(5111,@POOL, 0, 'Copper Vein - Silverpine'),
(5217,@POOL, 0, 'Copper Vein - Silverpine'),
(5395,@POOL, 0, 'Copper Vein - Silverpine'),
(5397,@POOL, 0, 'Copper Vein - Silverpine'),
(5402,@POOL, 0, 'Copper Vein - Silverpine'),
(5460,@POOL, 0, 'Copper Vein - Silverpine'),
(35571,@POOL, 0, 'Copper Vein - Silverpine'),
(75227,@POOL, 0, 'Copper Vein - Silverpine'),
(35444,@POOL, 0, 'Copper Vein - Silverpine'),
(75212,@POOL, 0, 'Copper Vein - Silverpine'),
(75317,@POOL, 0, 'Copper Vein - Silverpine'),
(75359,@POOL, 0, 'Copper Vein - Silverpine'),
(120343,@POOL, 0, 'Copper Vein - Silverpine'),
(5373,@POOL, 0, 'Copper Vein - Silverpine'),
(4653,@POOL, 0, 'Copper Vein - Silverpine'),
(5481,@POOL, 0, 'Copper Vein - Silverpine'),
(5334,@POOL, 0, 'Copper Vein - Silverpine');


SET @POOL = 1768;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 3, 'Tin - Gold - Wetlands');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(65227,@POOL, 0, 'Tin - Gold - Wetlands'),
(5538,@POOL, 0, 'Tin - Gold - Wetlands'),
(5581,@POOL, 0, 'Tin - Gold - Wetlands'),
(5516,@POOL, 0, 'Tin - Gold - Wetlands'),
(6314,@POOL, 0, 'Tin - Gold - Wetlands'),
(114665,@POOL, 0, 'Tin - Gold - Wetlands'),
(65203,@POOL, 0, 'Tin - Gold - Wetlands'),
(34143,@POOL, 0, 'Tin - Gold - Wetlands'),
(6393,@POOL, 0, 'Tin - Gold - Wetlands'),
(6741,@POOL, 0, 'Tin - Gold - Wetlands'),
(6225,@POOL, 0, 'Tin - Gold - Wetlands'),
(14663,@POOL, 0, 'Tin - Gold - Wetlands');

SET @POOL = 1769;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 3, 'Thorium - Truesilver -Searing');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(13213,@POOL, 0, 'Thorium - Truesilver -Searing'),
(13212,@POOL, 0, 'Thorium - Truesilver -Searing'),
(10214,@POOL, 0, 'Thorium - Truesilver -Searing'),
(373,@POOL, 0, 'Thorium - Truesilver -Searing'),
(13225,@POOL, 0, 'Thorium - Truesilver -Searing'),
(64838,@POOL, 0, 'Thorium - Truesilver -Searing'),
(10165,@POOL, 0, 'Thorium - Truesilver -Searing');

SET @POOL = 1770;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Thorium - Truesilver -Searing');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(35299,@POOL, 0, 'Thorium - Truesilver -Searing'),
(10004,@POOL, 0, 'Thorium - Truesilver -Searing');

SET @POOL = 1771;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5242,@POOL, 0, 'Copper Redridge'),
(29661,@POOL, 0, 'Copper Redridge');

SET @POOL = 1772;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5668,@POOL, 0, 'Copper Redridge'),
(5026,@POOL, 0, 'Copper Redridge');

SET @POOL = 1773;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5565,@POOL, 0, 'Copper Redridge'),
(5215,@POOL, 0, 'Copper Redridge');

SET @POOL = 1774;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(31113,@POOL, 0, 'Copper Redridge'),
(5027,@POOL, 0, 'Copper Redridge'),
(4977,@POOL, 0, 'Copper Redridge');

SET @POOL = 1775;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5637,@POOL, 0, 'Copper Redridge'),
(5109,@POOL, 0, 'Copper Redridge');

SET @POOL = 1776;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5251,@POOL, 0, 'Copper Redridge'),
(32346,@POOL, 0, 'Copper Redridge');

SET @POOL = 1777;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Copper Redridge');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(5663,@POOL, 0, 'Copper Redridge'),
(4863,@POOL, 0, 'Copper Redridge');

SET @POOL = 1778;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Mithril - Swamp');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(9306,@POOL, 0, 'Mithril - Swamp'),
(7137,@POOL, 0, 'Mithril - Swamp'),
(120655,@POOL, 0, 'Mithril - Swamp'),
(6476,@POOL, 0, 'Mithril - Swamp');

SET @POOL = 1779;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 3, 'Mithril - Swamp');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(30827,@POOL, 0, 'Mithril - Swamp'),
(6046,@POOL, 0, 'Mithril - Swamp'),
(6492,@POOL, 0, 'Mithril - Swamp'),
(5995,@POOL, 0, 'Mithril - Swamp'),
(6664,@POOL, 0, 'Mithril - Swamp'),
(6288,@POOL, 0, 'Mithril - Swamp'),
(6740,@POOL, 0, 'Mithril - Swamp'),
(62287,@POOL, 0, 'Mithril - Swamp'),
(6182,@POOL, 0, 'Mithril - Swamp');

SET @POOL = 1780;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 3, 'Mithril - Swamp');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(6139,@POOL, 0, 'Mithril - Swamp'),
(6653,@POOL, 0, 'Mithril - Swamp'),
(32291,@POOL, 0, 'Mithril - Swamp'),
(30348,@POOL, 0, 'Mithril - Swamp'),
(6629,@POOL, 0, 'Mithril - Swamp'),
(6652,@POOL, 0, 'Mithril - Swamp'),
(32756,@POOL, 0, 'Mithril - Swamp'),
(6056,@POOL, 0, 'Mithril - Swamp');

SET @POOL = 1781;
DELETE FROM `pool_template` WHERE `entry` = @POOL;
INSERT INTO `pool_template` VALUES
(@POOL, 3, 'Mithril - Swamp');

DELETE FROM `pool_gameobject` WHERE `pool_entry` = @POOL;
INSERT INTO `pool_gameobject` VALUES
(31019,@POOL, 0, 'Mithril - Swamp'),
(6657,@POOL, 0, 'Mithril - Swamp'),
(6529,@POOL, 0, 'Mithril - Swamp'),
(6185,@POOL, 0, 'Mithril - Swamp'),
(6758,@POOL, 0, 'Mithril - Swamp'),
(6172,@POOL, 0, 'Mithril - Swamp'),
(6153,@POOL, 0, 'Mithril - Swamp');

