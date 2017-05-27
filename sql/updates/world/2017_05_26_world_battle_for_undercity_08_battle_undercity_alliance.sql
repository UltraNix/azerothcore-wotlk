-- Battle for the Undercity - Alliance

-- Templates
SET @VARIAN := 32401;
SET @JAINA := 32402;
SET @BROLL := 32376;
SET @VAL := 32378;

SET @FLYING := 32388;
SET @SIEGE := 32389;

SET @STORMWIND_ELITE := 32387;

SET @WAVE_TRIGGER := 31684;

SET @WATER_ELEMENTAL := 10955;

SET @GUARDIAN := 32390;
SET @DREADLORD := 32391;
SET @FELBEAST := 32392;
SET @MARAUDER := 32393;
SET @BETRAYER := 32394;
SET @CHEMIST := 32395;
SET @COLLABORATOR := 32396;
SET @DOCTOR := 32397;
SET @WORM := 32483;
SET @KHANOK_CORPSE := 32511;

SET @PUTRESS_TRIGGER := 31653;
SET @PUTRESS := 31530;
SET @FAILED_EXPERIMENT := 32519;

SET @THRALL := 32518;
SET @SYLVANAS := 32365;
SET @WARSONG_BATTLEGUARD := 32510;

SET @SET_CHEMISTRY := 193407;
SET @WAGON := 193409;
SET @BLIGHT_BARREL_1 := 193410;
SET @SMALL_FLAMES := 193411;
SET @BLIGHT_BARREL_2 := 193412;
SET @BIG_FLAMES := 193413;
SET @HUGE_BARREL := 193420;

SET @PORTAL_TO_STORMWIND := 193956;

UPDATE `creature_template` SET `gossip_menu_id`=10194, `minlevel`=73, `maxlevel`=73, `unit_flags`=0 WHERE `entry`=@VARIAN;
UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `faction`=2142, `unit_flags`=0 WHERE `entry`=@JAINA;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `unit_flags`=512 WHERE `entry` IN (@BROLL,@VAL);

UPDATE `creature_template` SET `minlevel`=74, `maxlevel`=75, `faction`=1802, `unit_flags`=0, `InhabitType`=4 WHERE `entry`=@FLYING;
UPDATE `creature_template` SET `modelid1`=0, `minlevel`=74, `maxlevel`=75, `faction`=1802, `unit_flags`=0 WHERE `entry`=@SIEGE;

UPDATE `creature_template` SET `minlevel`=75, `maxlevel`=76, `faction`=1802, `unit_flags`=0 WHERE `entry`=@STORMWIND_ELITE;

UPDATE `creature_template` SET `faction`=16, `unit_flags`=33554690, `flags_extra`=130, `InhabitType`=4 WHERE `entry`=@WAVE_TRIGGER;

UPDATE `creature_template` SET `minlevel`=74, `maxlevel`=75, `unit_flags`=0 WHERE `entry` IN (@GUARDIAN,@MARAUDER,@BETRAYER,@CHEMIST,@COLLABORATOR,@DOCTOR);
UPDATE `creature_template` SET `minlevel`=75, `maxlevel`=75, `unit_flags`=0 WHERE `entry`=@DREADLORD;
UPDATE `creature_template` SET `minlevel`=74, `maxlevel`=74, `unit_flags`=0 WHERE `entry`=@FELBEAST;
UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `unit_flags`=4 WHERE `entry`=@WORM;
UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `faction`=1602,`unit_flags`=`unit_flags`|33554432, `unit_flags2`=2048, `dynamicflags`=32 WHERE `entry`=@KHANOK_CORPSE;

UPDATE `creature_template` SET `faction`=16, `unit_flags`=33554690, `InhabitType`=4, `flags_extra`=130 WHERE `entry`=@PUTRESS_TRIGGER;
UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `faction`=68, `unit_flags`=768 WHERE `entry`=@PUTRESS;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=@FAILED_EXPERIMENT;

UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `unit_flags`=33538 WHERE `entry` IN (@THRALL,@SYLVANAS,@WARSONG_BATTLEGUARD);

-- Spawns
SET @CGUID := 302301;
SET @OGUID := 218981;

DELETE FROM `creature` WHERE `id` IN (@VARIAN,@JAINA,@BROLL,@VAL,@FLYING,@SIEGE,@STORMWIND_ELITE,@WAVE_TRIGGER,@GUARDIAN,@DREADLORD,@FELBEAST,@MARAUDER,@BETRAYER,@CHEMIST,@COLLABORATOR,@DOCTOR,@KHANOK_CORPSE,@WARSONG_BATTLEGUARD);
INSERT INTO `creature` VALUES
(@CGUID,@VARIAN,0,1,128,0,1,1773.374,767.405,55.686,3.561,120,0,0,0,0,0,0,0,0),
(@CGUID+1,@JAINA,0,1,128,0,1,1774.641,766.723,55.375,3.49,120,0,0,0,0,0,0,0,0),
(@CGUID+2,@BROLL,0,1,128,0,0,1773.9374,769.44,55.52,3.573,120,0,0,0,0,0,0,0,0),
(@CGUID+3,@VAL,0,1,128,0,0,1773.405,771.539,55.549,3.56,120,0,0,0,0,0,0,0,0),

(@CGUID+4,@FLYING,0,1,128,0,0,1733.26,758.882,72.0817,4.12525,300,0,0,0,0,0,0,0,0),
(@CGUID+5,@FLYING,0,1,128,0,0,1732.56,712.535,64.7229,2.06044,300,0,0,0,0,0,0,0,0),
(@CGUID+6,@FLYING,0,1,128,0,0,1713.83,723.058,75.5521,1.2986,300,0,0,0,0,0,0,0,0),
(@CGUID+7,@SIEGE,0,1,128,0,0,1728.38,696.288,50.9044,4.00901,300,0,0,0,0,0,0,0,0),
(@CGUID+8,@SIEGE,0,1,128,0,0,1738.4,736.177,48.9801,3.79774,300,0,0,0,0,0,0,0,0),

(@CGUID+9,@STORMWIND_ELITE,0,1,128,0,1,1737.14,722.614,48.4675,3.02254,300,0,0,0,0,0,0,0,0),
(@CGUID+10,@STORMWIND_ELITE,0,1,128,0,1,1718.45,711.327,56.7108,2.76965,300,0,0,0,0,0,0,0,0),
(@CGUID+11,@STORMWIND_ELITE,0,1,128,0,1,1728.69,754.809,54.1777,3.86842,300,0,0,0,0,0,0,0,0),
(@CGUID+12,@STORMWIND_ELITE,0,1,128,0,1,1735.95,719.563,48.6681,3.11286,300,0,0,0,0,0,0,0,0),
(@CGUID+13,@STORMWIND_ELITE,0,1,128,0,1,1715.5,709.699,58.3095,2.64006,300,0,0,0,0,0,0,0,0),
(@CGUID+14,@STORMWIND_ELITE,0,1,128,0,1,1731.61,753.575,53.1105,3.80245,300,0,0,0,0,0,0,0,0),

(@CGUID+15,@WAVE_TRIGGER,0,1,128,0,0,1680.433350,730.041443,78.272003,2.87254,600,0,0,0,0,0,0,0,0),

(@CGUID+16,@GUARDIAN,0,1,128,0,0,1517.75,375.644,-50.9619,6.07696,300,0,0,0,0,0,0,570721024,32),
(@CGUID+17,@GUARDIAN,0,1,128,0,0,1495.4,421.519,-62.1856,0.530931,300,0,0,0,0,0,0,570721024,32),
(@CGUID+18,@GUARDIAN,0,1,128,0,0,1530.56,410.833,-62.1329,3.482,300,0,0,0,0,0,0,570721024,32),
(@CGUID+19,@DREADLORD,0,1,128,0,0,1562.74,413.5,-62.1779,3.3403,300,0,0,0,0,0,0,570721024,32),
(@CGUID+20,@DREADLORD,0,1,128,0,0,1594.86,379.248,-62.1776,4.85409,300,0,0,0,0,0,0,570721024,32),
(@CGUID+21,@DREADLORD,0,1,128,0,0,1489.57,408.251,-62.1856,2.05617,300,0,0,0,0,0,0,570721024,32),
(@CGUID+22,@DREADLORD,0,1,128,0,0,1487.31,380.922,-60.7166,3.51656,300,0,0,0,0,0,0,570721024,32),
(@CGUID+23,@FELBEAST,0,1,128,0,0,1493.75,408.317,-62.1856,2.23681,300,0,0,0,0,0,0,570721024,32),
(@CGUID+24,@FELBEAST,0,1,128,0,0,1581.82,376.02,-62.1776,5.36145,300,0,0,0,0,0,0,570721024,32),
(@CGUID+25,@FELBEAST,0,1,128,0,0,1586.56,373.763,-62.1776,5.54131,300,0,0,0,0,0,0,570721024,32),
(@CGUID+26,@FELBEAST,0,1,128,0,0,1490.74,412.705,-62.1856,2.32321,300,0,0,0,0,0,0,570721024,32),
(@CGUID+27,@MARAUDER,0,1,128,0,0,1547.06,365.225,-62.1874,0.732321,300,0,0,0,0,0,0,570721024,32),
(@CGUID+28,@BETRAYER,0,1,128,0,0,1617.53,378.244,-62.1775,5.28292,300,0,0,0,0,0,0,570721024,32),
(@CGUID+29,@BETRAYER,0,1,128,0,0,1549.58,372.034,-62.1787,0.292498,300,0,0,0,0,0,0,570721024,32),
(@CGUID+30,@BETRAYER,0,1,128,0,0,1526.26,362.945,-57.1519,5.47063,300,0,0,0,0,0,0,570721024,32),
(@CGUID+31,@BETRAYER,0,1,128,0,0,1618.7,377.671,-62.1775,5.30255,300,0,0,0,0,0,0,570721024,32),
(@CGUID+32,@BETRAYER,0,1,128,0,0,1495.53,410.351,-62.1856,2.39704,300,0,0,0,0,0,0,570721024,32),
(@CGUID+33,@CHEMIST,0,1,128,0,0,1438.48,460.231,-70.4604,4.75873,300,0,0,0,0,0,0,570721024,32),
(@CGUID+34,@COLLABORATOR,0,1,128,0,0,1438.01,461.485,-70.4612,4.19717,300,0,0,0,0,0,0,570721024,32),
(@CGUID+35,@DOCTOR,0,1,128,0,0,1438.95,459.399,-70.4613,3.52565,300,0,0,0,0,0,0,570721024,32),
(@CGUID+36,@DOCTOR,0,1,128,0,0,1439.61,461.681,-70.4612,3.66702,300,0,0,0,0,0,0,570721024,32),
(@CGUID+37,@KHANOK_CORPSE,0,1,128,0,1,1586.91,384.431,-62.5204,6.21732,300,0,0,0,0,0,0,0,0),

(@CGUID+38,@WARSONG_BATTLEGUARD,0,1,128,0,1,1469.28,369.128,-59.4273,2.54077,300,0,0,0,0,0,0,570721024,32),
(@CGUID+39,@WARSONG_BATTLEGUARD,0,1,128,0,1,1580.8,387.141,-63.7857,5.69211,300,0,0,0,0,0,0,570721024,32),
(@CGUID+40,@WARSONG_BATTLEGUARD,0,1,128,0,1,1590.82,387.814,-64.3627,5.20438,300,0,0,0,0,0,0,570721024,32),
(@CGUID+41,@WARSONG_BATTLEGUARD,0,1,128,0,1,1594.44,384.653,-62.5928,3.95167,300,0,0,0,0,0,0,570721024,32),
(@CGUID+42,@WARSONG_BATTLEGUARD,0,1,128,0,1,1574.41,371.329,-62.1776,6.06439,300,0,0,0,0,0,0,570721024,32),
(@CGUID+43,@WARSONG_BATTLEGUARD,0,1,128,0,1,1543.58,368.558,-62.1815,1.10931,300,0,0,0,0,0,0,570721024,32),
(@CGUID+44,@WARSONG_BATTLEGUARD,0,1,128,0,1,1555.65,367.821,-62.1797,0.206889,300,0,0,0,0,0,0,570721024,32),
(@CGUID+45,@WARSONG_BATTLEGUARD,0,1,128,0,1,1489.92,417.396,-62.1856,0.630677,300,0,0,0,0,0,0,570721024,32),
(@CGUID+46,@WARSONG_BATTLEGUARD,0,1,128,0,1,1465.28,357.37,-62.1855,4.32519,300,0,0,0,0,0,0,570721024,32),
(@CGUID+47,@WARSONG_BATTLEGUARD,0,1,128,0,1,1539.25,415.542,-62.154,3.4102,300,0,0,0,0,0,0,570721024,32),
(@CGUID+48,@WARSONG_BATTLEGUARD,0,1,128,0,1,1560.57,420.003,-62.178,3.8194,300,0,0,0,0,0,0,570721024,32),
(@CGUID+49,@WARSONG_BATTLEGUARD,0,1,128,0,1,1568.59,377.639,-62.1776,0.958514,300,0,0,0,0,0,0,570721024,32),
(@CGUID+50,@WARSONG_BATTLEGUARD,0,1,128,0,1,1535.11,405.587,-62.1756,3.57592,300,0,0,0,0,0,0,570721024,32),
(@CGUID+51,@WARSONG_BATTLEGUARD,0,1,128,0,1,1509.64,392.375,-57.1531,2.14179,300,0,0,0,0,0,0,570721024,32),
(@CGUID+52,@WARSONG_BATTLEGUARD,0,1,128,0,1,1507.59,407.797,-62.1857,5.31951,300,0,0,0,0,0,0,570721024,32),
(@CGUID+53,@WARSONG_BATTLEGUARD,0,1,128,0,1,1487.52,386.135,-62.1853,3.95684,300,0,0,0,0,0,0,570721024,32),
(@CGUID+54,@WARSONG_BATTLEGUARD,0,1,128,0,1,1492.99,383.964,-62.2343,4.03616,300,0,0,0,0,0,0,570721024,32),
(@CGUID+55,@WARSONG_BATTLEGUARD,0,1,128,0,1,1479.26,378.576,-59.7135,3.26962,300,0,0,0,0,0,0,570721024,32),
(@CGUID+56,@WARSONG_BATTLEGUARD,0,1,128,0,1,1478.45,370.485,-62.1857,4.11078,300,0,0,0,0,0,0,570721024,32),
(@CGUID+57,@WARSONG_BATTLEGUARD,0,1,128,0,1,1472.66,368.062,-61.5219,3.48246,300,0,0,0,0,0,0,570721024,32);

DELETE FROM `gameobject` WHERE `id` IN (@SET_CHEMISTRY,@WAGON,@BLIGHT_BARREL_1,@SMALL_FLAMES,@BLIGHT_BARREL_2,@BIG_FLAMES,@HUGE_BARREL,@PORTAL_TO_STORMWIND);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID,@SET_CHEMISTRY,0,1,192,1555.35,329.307,-62.1372,2.14675,0,0,0,1,300,255,1),

(@OGUID+1,@WAGON,0,1,192,1630.55,275.15,-43.1023,0.767944,0,0,0,1,300,255,1),
(@OGUID+2,@WAGON,0,1,192,1682.43,326.504,-62.1652,-0.785397,0,0,0,1,300,255,1),
(@OGUID+3,@WAGON,0,1,192,1475.66,47.9851,-62.2957,-1.64061,0,0,0,1,300,255,1),
(@OGUID+4,@WAGON,0,1,192,1538.1,245.874,-62.1778,-0.191985,0,0,0,1,300,255,1),
(@OGUID+5,@WAGON,0,1,192,1406.87,338.234,-66.001,-2.05949,0,0,0,1,300,255,1),
(@OGUID+6,@WAGON,0,1,192,1576.39,193.66,-43.085,-1.95477,0,0,0,1,300,255,1),

(@OGUID+7,@BLIGHT_BARREL_1,0,1,192,1558.97,349.041,-62.1576,-3.01941,0,0,0,1,300,255,1),
(@OGUID+8,@BLIGHT_BARREL_1,0,1,192,1563.25,345.17,-62.1434,-2.79252,0,0,0,1,300,255,1),

(@OGUID+9,@SMALL_FLAMES,0,1,192,1689.9,777.613,65.3829,-2.11185,0,0,0,1,300,255,1),
(@OGUID+10,@SMALL_FLAMES,0,1,192,1613.94,290.671,-43.1023,-1.22173,0,0,0,1,300,255,1),
(@OGUID+11,@SMALL_FLAMES,0,1,192,1689.34,344.723,-60.4777,0.226892,0,0,0,1,300,255,1),
(@OGUID+12,@SMALL_FLAMES,0,1,192,1599.63,289.821,-41.3606,2.67035,0,0,0,1,300,255,1),
(@OGUID+13,@SMALL_FLAMES,0,1,192,1591.12,292.276,-62.1778,1.85005,0,0,0,1,300,255,1),
(@OGUID+14,@SMALL_FLAMES,0,1,192,1594.62,188.387,-41.3606,-2.9845,0,0,0,1,300,255,1),
(@OGUID+15,@SMALL_FLAMES,0,1,192,1555.54,125.3,-62.1714,-1.01229,0,0,0,1,300,255,1),
(@OGUID+16,@SMALL_FLAMES,0,1,192,1544.85,243.552,-41.3606,1.02974,0,0,0,1,300,255,1),
(@OGUID+17,@SMALL_FLAMES,0,1,192,1478.1,174.8,-61.5027,-2.60053,0,0,0,1,300,255,1),
(@OGUID+18,@SMALL_FLAMES,0,1,192,1644.38,214.804,-43.103,-1.20428,0,0,0,1,300,255,1),
(@OGUID+19,@SMALL_FLAMES,0,1,192,1531.11,305.188,-62.1379,2.37364,0,0,0,1,300,255,1),
(@OGUID+20,@SMALL_FLAMES,0,1,192,1652.15,265.885,-62.1776,-1.50098,0,0,0,1,300,255,1),
(@OGUID+21,@SMALL_FLAMES,0,1,192,1672.65,766.654,78.3797,1.48353,0,0,0,1,300,255,1),
(@OGUID+22,@SMALL_FLAMES,0,1,192,1534.57,309.985,-62.1338,2.58308,0,0,0,1,300,255,1),
(@OGUID+23,@SMALL_FLAMES,0,1,192,1674.42,762.948,78.2124,-1.309,0,0,0,1,300,255,1),
(@OGUID+24,@SMALL_FLAMES,0,1,192,1597.53,188.246,-41.3606,1.79769,0,0,0,1,300,255,1),
(@OGUID+25,@SMALL_FLAMES,0,1,192,1644.87,220.946,-43.1032,-1.18682,0,0,0,1,300,255,1),
(@OGUID+26,@SMALL_FLAMES,0,1,192,1543.12,238.006,-41.3606,0.261798,0,0,0,1,300,255,1),
(@OGUID+27,@SMALL_FLAMES,0,1,192,1719.36,178.111,-60.7699,0.872664,0,0,0,1,300,255,1),
(@OGUID+28,@SMALL_FLAMES,0,1,192,1562.29,206.573,-43.1023,-1.01229,0,0,0,1,300,255,1),
(@OGUID+29,@SMALL_FLAMES,0,1,192,1699.98,711.082,66.8015,1.23918,0,0,0,1,300,255,1),
(@OGUID+30,@SMALL_FLAMES,0,1,192,1682.96,200.872,-62.1716,-1.27409,0,0,0,1,300,255,1),
(@OGUID+31,@SMALL_FLAMES,0,1,192,1557.55,202.067,-43.1022,1.25664,0,0,0,1,300,255,1),
(@OGUID+32,@SMALL_FLAMES,0,1,192,1678.97,195.972,-62.1716,1.41372,0,0,0,1,300,255,1),
(@OGUID+33,@SMALL_FLAMES,0,1,192,1530.12,280.621,-62.1776,-1.44862,0,0,0,1,300,255,1),
(@OGUID+34,@SMALL_FLAMES,0,1,192,1603.85,239.709,-44.6718,0.575957,0,0,0,1,300,255,1),
(@OGUID+35,@SMALL_FLAMES,0,1,192,1642.59,178.146,-62.1783,-0.261798,0,0,0,1,300,255,1),
(@OGUID+36,@SMALL_FLAMES,0,1,192,1533.91,288.105,-62.1779,-2.79252,0,0,0,1,300,255,1),
(@OGUID+37,@SMALL_FLAMES,0,1,192,1597.51,293.949,-62.1777,-1.43117,0,0,0,1,300,255,1),
(@OGUID+38,@SMALL_FLAMES,0,1,192,1590.78,184.6,-62.1778,0.541051,0,0,0,1,300,255,1),
(@OGUID+39,@SMALL_FLAMES,0,1,192,1689.78,783.543,63.5869,2.02458,0,0,0,1,300,255,1),
(@OGUID+40,@SMALL_FLAMES,0,1,192,1562.78,124.93,-62.1645,0,0,0,0,1,300,255,1),
(@OGUID+41,@SMALL_FLAMES,0,1,192,1701.92,706.798,63.8543,0.436332,0,0,0,1,300,255,1),
(@OGUID+42,@SMALL_FLAMES,0,1,192,1705.69,268.705,-62.1681,1.22173,0,0,0,1,300,255,1),
(@OGUID+43,@SMALL_FLAMES,0,1,192,1604.1,291.726,-62.1776,-0.069812,0,0,0,1,300,255,1),
(@OGUID+44,@SMALL_FLAMES,0,1,192,1505.66,347.975,-60.0895,2.87979,0,0,0,1,300,255,1),
(@OGUID+45,@SMALL_FLAMES,0,1,192,1592.21,292.847,-41.3606,2.25147,0,0,0,1,300,255,1),
(@OGUID+46,@SMALL_FLAMES,0,1,192,1694.77,785.005,65.853,2.18166,0,0,0,1,300,255,1),
(@OGUID+47,@SMALL_FLAMES,0,1,192,1616.12,284.173,-43.1024,0.994837,0,0,0,1,300,255,1),
(@OGUID+48,@SMALL_FLAMES,0,1,192,1545.94,231.799,-62.1777,-0.575957,0,0,0,1,300,255,1),
(@OGUID+49,@SMALL_FLAMES,0,1,192,1504.03,346.454,-60.0896,3.14159,0,0,0,1,300,255,1),
(@OGUID+50,@SMALL_FLAMES,0,1,192,1593.58,189.097,-41.3606,2.07694,0,0,0,1,300,255,1),
(@OGUID+51,@SMALL_FLAMES,0,1,192,1825.67,273.237,60.6767,-0.052359,0,0,0,1,300,255,1),
(@OGUID+52,@SMALL_FLAMES,0,1,192,1784.18,204.161,60.0846,2.16421,0,0,0,1,300,255,1),
(@OGUID+53,@SMALL_FLAMES,0,1,192,1830.77,265.903,62.826,0.506145,0,0,0,1,300,255,1),
(@OGUID+54,@SMALL_FLAMES,0,1,192,1841.95,262.513,60.1825,2.54818,0,0,0,1,300,255,1),
(@OGUID+55,@SMALL_FLAMES,0,1,192,1777.58,205.75,60.0713,-1.0472,0,0,0,1,300,255,1),
(@OGUID+56,@SMALL_FLAMES,0,1,192,1789.05,273.004,60.2142,-2.11185,0,0,0,1,300,255,1),
(@OGUID+57,@SMALL_FLAMES,0,1,192,1841.5,254.541,60.0008,1.37881,0,0,0,1,300,255,1),
(@OGUID+58,@SMALL_FLAMES,0,1,192,1778.36,271.688,60.1236,1.8675,0,0,0,1,300,255,1),

(@OGUID+59,@BLIGHT_BARREL_2,0,1,192,1559.34,350.713,-62.1584,-1.44862,0,0,0,1,300,255,1),
(@OGUID+60,@BLIGHT_BARREL_2,0,1,192,1560.06,347.314,-62.1535,-1.06465,0,0,0,1,300,255,1),

(@OGUID+61,@BIG_FLAMES,0,1,192,1587.34,243.225,-45.1419,2.70526,0,0,0,1,300,255,1),
(@OGUID+62,@BIG_FLAMES,0,1,192,1587.53,236.399,-44.6591,-0.785397,0,0,0,1,300,255,1),
(@OGUID+63,@BIG_FLAMES,0,1,192,1597.9,232.358,-44.2318,-2.30383,0,0,0,1,300,255,1),
(@OGUID+64,@BIG_FLAMES,0,1,192,1592.74,231.815,-45.383,0.104719,0,0,0,1,300,255,1),
(@OGUID+65,@BIG_FLAMES,0,1,192,1594.04,232.018,-44.9632,2.75761,0,0,0,1,300,255,1),
(@OGUID+66,@BIG_FLAMES,0,1,192,1592.61,232.366,-44.3059,-0.506145,0,0,0,1,300,255,1),
(@OGUID+67,@BIG_FLAMES,0,1,192,1697.68,746.448,72.2679,-2.02458,0,0,0,1,300,255,1),
(@OGUID+68,@BIG_FLAMES,0,1,192,1538.09,260.915,-55.0005,2.42601,0,0,0,1,300,255,1),
(@OGUID+69,@BIG_FLAMES,0,1,192,1536.96,260.264,-54.9985,-1.51844,0,0,0,1,300,255,1),
(@OGUID+70,@BIG_FLAMES,0,1,192,1688.43,723.941,73.324,1.8675,0,0,0,1,300,255,1),
(@OGUID+71,@BIG_FLAMES,0,1,192,1591.72,248.572,-44.8338,-0.994837,0,0,0,1,300,255,1),
(@OGUID+72,@BIG_FLAMES,0,1,192,1521.02,217.054,-60.4762,-1.97222,0,0,0,1,300,255,1),
(@OGUID+73,@BIG_FLAMES,0,1,192,1712.47,746.768,65.1409,1.91986,0,0,0,1,300,255,1),
(@OGUID+74,@BIG_FLAMES,0,1,192,1549.16,265,-40.8808,2.51327,0,0,0,1,300,255,1),
(@OGUID+75,@BIG_FLAMES,0,1,192,1644.74,256.843,-41.1102,-1.16937,0,0,0,1,300,255,1),
(@OGUID+76,@BIG_FLAMES,0,1,192,1594.14,248.888,-45.5204,1.81514,0,0,0,1,300,255,1),
(@OGUID+77,@BIG_FLAMES,0,1,192,1708.62,716.61,61.2928,2.30383,0,0,0,1,300,255,1),
(@OGUID+78,@BIG_FLAMES,0,1,192,1594.1,248.659,-45.045,-1.74533,0,0,0,1,300,255,1),
(@OGUID+79,@BIG_FLAMES,0,1,192,1587.4,237.708,-44.9197,0.663223,0,0,0,1,300,255,1),

(@OGUID+80,@HUGE_BARREL,0,1,192,1561.79,279.404,-43.1025,-2.96704,0,0,0,1,300,255,1),
(@OGUID+81,@HUGE_BARREL,0,1,192,1558.28,354.458,-62.1639,2.18166,0,0,0,1,300,255,1),
(@OGUID+82,@HUGE_BARREL,0,1,192,1635.49,329.722,-62.1785,-1.95477,0,0,0,1,300,255,1),
(@OGUID+83,@HUGE_BARREL,0,1,192,1650.84,234.671,-62.1777,-1.18682,0,0,0,1,300,255,1),
(@OGUID+84,@HUGE_BARREL,0,1,192,1387.75,120.87,-62.4307,1.91986,0,0,0,1,300,255,1),
(@OGUID+85,@HUGE_BARREL,0,1,192,1561.46,273.463,-43.1022,1.53589,0,0,0,1,300,255,1),
(@OGUID+86,@HUGE_BARREL,0,1,192,1631.17,206.76,-43.1022,-1.76278,0,0,0,1,300,255,1),
(@OGUID+87,@HUGE_BARREL,0,1,192,1386.27,347.817,-66.0206,-1.20428,0,0,0,1,300,255,1),
(@OGUID+88,@HUGE_BARREL,0,1,192,1602.04,188.686,-62.1778,-1.93731,0,0,0,1,300,255,1),
(@OGUID+89,@HUGE_BARREL,0,1,192,1387.54,125.862,-62.4274,-0.541051,0,0,0,1,300,255,1),
(@OGUID+90,@HUGE_BARREL,0,1,192,1508.61,197.873,-62.1372,0.087266,0,0,0,1,300,255,1),
(@OGUID+91,@HUGE_BARREL,0,1,192,1507.43,201.335,-62.1372,0.383971,0,0,0,1,300,255,1),
(@OGUID+92,@HUGE_BARREL,0,1,192,1488.89,438.438,-83.5422,2.02458,0,0,0,1,300,255,1),
(@OGUID+93,@HUGE_BARREL,0,1,192,1653.87,243.721,-62.1781,-2.51327,0,0,0,1,300,255,1),
(@OGUID+94,@HUGE_BARREL,0,1,192,1486.3,433.56,-83.5422,1.15192,0,0,0,1,300,255,1),
(@OGUID+95,@HUGE_BARREL,0,1,192,1574.22,236.745,-62.0773,-1.78023,0,0,0,1,300,255,1),
(@OGUID+96,@HUGE_BARREL,0,1,192,1655.48,291.696,-62.1782,-1.0821,0,0,0,1,300,255,1),
(@OGUID+97,@HUGE_BARREL,0,1,192,1491.39,434.378,-83.5422,-0.994837,0,0,0,1,300,255,1),
(@OGUID+98,@HUGE_BARREL,0,1,192,1649.16,245.772,-62.1779,1.53589,0,0,0,1,300,255,1),
(@OGUID+99,@HUGE_BARREL,0,1,192,1600.31,184.676,-62.178,0.628317,0,0,0,1,300,255,1),
(@OGUID+100,@HUGE_BARREL,0,1,192,1402.16,152.301,-62.4192,1.09956,0,0,0,1,300,255,1),
(@OGUID+101,@HUGE_BARREL,0,1,192,1388.88,341.997,-66.0226,-0.122173,0,0,0,1,300,255,1),
(@OGUID+102,@HUGE_BARREL,0,1,192,1483.77,438.159,-83.5422,1.88495,0,0,0,1,300,255,1),
(@OGUID+103,@HUGE_BARREL,0,1,192,1615.57,245.317,-62.0773,-0.017452,0,0,0,1,300,255,1),
(@OGUID+104,@HUGE_BARREL,0,1,192,1634.84,200.921,-43.1023,0.558504,0,0,0,1,300,255,1),
(@OGUID+105,@HUGE_BARREL,0,1,192,1639.65,327.075,-62.1765,-2.68781,0,0,0,1,300,255,1),
(@OGUID+106,@HUGE_BARREL,0,1,192,1616.88,240.985,-62.0773,-1.79769,0,0,0,1,300,255,1),
(@OGUID+107,@HUGE_BARREL,0,1,192,1609.83,186.749,-56.8756,2.18166,0,0,0,1,300,255,1),
(@OGUID+108,@HUGE_BARREL,0,1,192,1664.42,173.203,-62.1401,0.226892,0,0,0,1,300,255,1),

(@OGUID+109,@PORTAL_TO_STORMWIND,0,1,128,1777.23,762.609,54.1443,3.08918,0,0,0,1,300,255,1);

-- Creature addons
DELETE FROM `creature_template_addon` WHERE `entry` IN (@THRALL,@WARSONG_BATTLEGUARD);
INSERT INTO `creature_template_addon` VALUES
(@THRALL,0,0,0,257,375,''),
(@WARSONG_BATTLEGUARD,0,0,0,257,375,'');

DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+16 AND @CGUID+57;
INSERT INTO `creature_addon` VALUES
(@CGUID+16,0,0,0,257,0,'29266'),
(@CGUID+17,0,0,0,257,0,'29266'),
(@CGUID+18,0,0,0,257,0,'29266'),
(@CGUID+19,0,0,0,257,0,'29266'),
(@CGUID+20,0,0,0,257,0,'29266'),
(@CGUID+21,0,0,0,257,0,'29266'),
(@CGUID+22,0,0,0,257,0,'29266'),
(@CGUID+23,0,0,0,257,0,'29266'),
(@CGUID+24,0,0,0,257,0,'29266'),
(@CGUID+25,0,0,0,257,0,'29266'),
(@CGUID+26,0,0,0,257,0,'29266'),
(@CGUID+27,0,0,0,257,0,'29266'),
(@CGUID+28,0,0,0,257,0,'29266'),
(@CGUID+29,0,0,0,257,0,'29266'),
(@CGUID+30,0,0,0,1,0,'29266'),
(@CGUID+31,0,0,0,1,0,'29266'),
(@CGUID+32,0,0,0,1,0,'29266'),
(@CGUID+33,0,0,0,1,0,'29266'),
(@CGUID+34,0,0,0,1,0,'29266'),
(@CGUID+35,0,0,0,1,0,'29266'),
(@CGUID+36,0,0,0,1,0,'29266'),
(@CGUID+37,0,0,0,1,0,'29266'),
(@CGUID+38,0,0,0,1,0,'29266'),
(@CGUID+39,0,0,0,1,0,'29266'),
(@CGUID+40,0,0,0,1,0,'29266'),
(@CGUID+41,0,0,0,1,0,'29266'),
(@CGUID+42,0,0,0,1,0,'29266'),
(@CGUID+43,0,0,0,1,0,'29266'),
(@CGUID+44,0,0,0,1,0,'29266'),
(@CGUID+45,0,0,0,1,0,'29266'),
(@CGUID+46,0,0,0,1,0,'29266'),
(@CGUID+47,0,0,0,1,0,'29266'),
(@CGUID+48,0,0,0,1,0,'29266'),
(@CGUID+49,0,0,0,1,0,'29266'),
(@CGUID+50,0,0,0,1,0,'29266'),
(@CGUID+51,0,0,0,1,0,'29266'),
(@CGUID+52,0,0,0,1,0,'29266'),
(@CGUID+53,0,0,0,1,0,'29266'),
(@CGUID+54,0,0,0,1,0,'29266'),
(@CGUID+55,0,0,0,1,0,'29266'),
(@CGUID+56,0,0,0,1,0,'29266'),
(@CGUID+57,0,0,0,1,0,'29266');

-- Equipments
DELETE FROM `creature_equip_template` WHERE `entry` IN (@VARIAN,@JAINA,@STORMWIND_ELITE,@KHANOK_CORPSE,@WARSONG_BATTLEGUARD,@THRALL,@SYLVANAS);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(@VARIAN,1,44705,44705,0),
(@JAINA,1,2177,12869,0),
(@STORMWIND_ELITE,1,1895,1984,0),
(@KHANOK_CORPSE,1,13623,0,0),
(@WARSONG_BATTLEGUARD,1,34638,0,0),
(@THRALL,1,12183,0,0),
(@SYLVANAS,1,2179,0,42775);

-- Formations
DELETE FROM `creature_formations` WHERE `leaderGUID` IN (@CGUID,@CGUID+8);
INSERT INTO `creature_formations` VALUES
(@CGUID,@CGUID,0,0,2,0,0),
(@CGUID,@CGUID+1,5,45,2,0,0),
(@CGUID+8,@CGUID+4,0,0,2,0,0),
(@CGUID+8,@CGUID+5,0,0,2,0,0),
(@CGUID+8,@CGUID+6,0,0,2,0,0),
(@CGUID+8,@CGUID+7,0,0,2,0,0),
(@CGUID+8,@CGUID+8,0,0,2,0,0),
(@CGUID+8,@CGUID+9,0,0,2,0,0),
(@CGUID+8,@CGUID+10,0,0,2,0,0),
(@CGUID+8,@CGUID+11,0,0,2,0,0),
(@CGUID+8,@CGUID+12,0,0,2,0,0),
(@CGUID+8,@CGUID+13,0,0,2,0,0),
(@CGUID+8,@CGUID+14,0,0,2,0,0);

-- Update AI
UPDATE `creature_template` SET `AiName`='SmartAI' WHERE `entry` IN (@JAINA,@WATER_ELEMENTAL,@FLYING,@SIEGE,@STORMWIND_ELITE,@GUARDIAN,@DREADLORD,@FELBEAST,@MARAUDER,@BETRAYER,@CHEMIST,@WORM,@THRALL,@SYLVANAS,@WARSONG_BATTLEGUARD);
UPDATE `creature_template` SET `ScriptName`='npc_varian_battle_undercity' WHERE `entry`=@VARIAN;
UPDATE `creature_template` SET `ScriptName`='npc_wave_trigger_battle_undercity' WHERE `entry`=@WAVE_TRIGGER;
UPDATE `creature_template` SET `ScriptName`='npc_putress_battle_undercity' WHERE `entry`=@PUTRESS;

-- Gossip
DELETE FROM `gossip_menu_option` WHERE `menu_id`=10194;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10194, 0, 0, 'Reporting for duty, your majesty! Let the assault begin!', 1, 1);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=10194;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10194, 0, 0, 0, 9, 0, 13377, 0, 0, 0, 0, '', 'Show gossip if player has quest The Battle for Undercity');

-- Spell target position
DELETE FROM `spell_target_position` WHERE `id`=61239;
INSERT INTO `spell_target_position` VALUES
(61239,0,0,-8448.6035,341.9446,120.8860,5.4145);

-- Conditions
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (59449,59456,61224);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 59449, 0, 0, 31, 0, 3, @PUTRESS, 0, 0, 0, '', 'Blight Empowerment targets Putress'),
(13, 1, 59456, 0, 0, 31, 0, 3, @PUTRESS_TRIGGER, 0, 0, 0, '', 'Blight Empowerment targets Putress'),
(13, 1, 61224, 0, 0, 31, 0, 3, @VARIAN, 0, 0, 0, '', 'Deep Freeze targets Varian'),
(13, 1, 61224, 0, 1, 31, 0, 3, @THRALL, 0, 0, 0, '', 'Deep Freeze targets Thrall'),
(13, 1, 61224, 0, 2, 31, 0, 3, @SYLVANAS, 0, 0, 0, '', 'Deep Freeze targets Sylvanas'),
(13, 1, 61224, 0, 3, 31, 0, 3, @WARSONG_BATTLEGUARD, 0, 0, 0, '', 'Deep Freeze targets Warsong Battlegurad'),
(13, 1, 61224, 0, 4, 31, 0, 4, 0, 0, 0, 0, '', 'Deep Freeze targets players'),
(13, 2, 61224, 0, 0, 31, 0, 4, 0, 0, 0, 0, '', 'Deep Freeze targets players');

-- Waypointy
DELETE FROM `script_waypoint` WHERE `entry`=@VARIAN;
INSERT INTO `script_waypoint` VALUES
(@VARIAN,1,1773.374,767.405,55.686,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,2,1740.206,746.545,50.662,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,3,1708.954,735.985,64.81,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,4,1682.888,725.082,76.542,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,5,1680.996,725.512,76.895,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,6,1663.554,730.474,79.553,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,7,1652.936,732.063,80.377,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,8,1624.833,731.953,80.377,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,9,1610.656,723.584,67.64,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,10,1601.735,715.762,63.933,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,11,1597.082,704.761,59.759,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,12,1591.546,676.636,49.834,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,13,1602.099,656.522,40.852,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,14,1620.421,647.783,35.887,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,15,1641.179,646.132,26.157,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,16,1667.26,643.398,17.066,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,17,1682.491,633.145,10.326,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,18,1691.383,613.445,2.957,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,19,1685.723,596.909,-6.136,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,20,1681.454,583.924,-11.807,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,21,1678.7,571.664,-17.189,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,22,1674.67,573.613,-16.88,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,23,1668.45,571.36,-16.32,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,24,1664.69,562.5,-16.96,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,25,1665.94,548.814,-15.5,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,26,1665.09,540.793,-11.66,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,27,1665.197,532.244,-11.37,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,28,1664.863,524.35,-13.1,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,29,1664.688,487.213,-11.853,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,30,1663.974,481.992,-11.89,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,31,1658.724,478.842,-11.911,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,32,1632.564,479.032,-22.869,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,33,1629.777,477.544,-22.868,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,34,1629.481,473.969,-22.868,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,35,1629.352,445.047,-34.263,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,36,1628.989,441.104,-34.263,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,37,1628.146,439.061,-34.263,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,38,1626.121,437.459,-34.263,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,39,1600.108,437.628,-46.176,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,40,1597.615,436.736,-46.335,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,41,1596.573,434.44,-46.335,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,42,1596.719,425.867,-46.355,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,43,1596.696,422.822,-46.381,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,44,1591.901,421.675,-46.395,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,45,1589.9,420.099,-45.411,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,46,1574.767,420.731,-54.449,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,47,1571.68,423.198,-57.55,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,48,1564.43,420.833,-62.178,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,49,1553.361,415.537,-61.62,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,50,1547.894,413.559,-61.62,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,51,1531.256,406.92,-62.154,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,52,1518.0,405.649,-62.243,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,53,1500.856,410.32,-62.187,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,54,1494.833,419.489,-62.187,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,55,1496.85,422.568,-62.236,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,56,1504.859,427.41,-64.008,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,57,1507.547,435.612,-65.229,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,58,1505.386,439.96,-64.53,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,59,1503.018,443.704,-63.674,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,60,1491.935,449.94,-61.204,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,61,1481.115,448.795,-61.927,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,62,1470.018,441.205,-64.915,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,63,1459.685,439.183,-65.72,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,64,1452.454,445.473,-65.725,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,65,1445.789,452.056,-70.065,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,66,1438.592,457.522,-70.461,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,67,1431.477,453.717,-69.988,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,68,1417.966,440.227,-77.238,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,69,1422.84,436.52,-77.24,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,70,1431.075,417.264,-85.245,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,71,1423.47,415.173,-84.965,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,72,1412.834,405.204,-84.965,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,73,1407.739,403,-84.965,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,74,1398.872,412.462,-77.368,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,75,1395.071,416.222,-77.24,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,76,1388.488,414.182,-77.238,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,77,1379.766,406.804,-74.715,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,78,1370.855,397.114,-72.218,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,79,1365.359,386.238,-69.962,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,80,1362.731,378.189,-70.518,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,81,1363.709,372.871,-70.493,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,82,1370.064,369.358,-70.374,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,83,1379.739,366.434,-65.725,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,84,1421.059,353.903,-66,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,85,1427.013,350.9,-62.184,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,86,1446.439,345.802,-62.245,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,87,1467.115,359.943,-62.186,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,88,1468.09,367.518,-59.422,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,89,1464.727,373.517,-59.451,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,90,1434.457,406.115,-57.818,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,91,1415.149,425.592,-55.053,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,92,1406.088,431.704,-54.931,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,93,1383.303,438.238,-52.919,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,94,1372.31,438.724,-52.779,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,95,1347.006,432.274,-56.136,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,96,1338.757,427.926,-56.124,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,97,1319.922,410.112,-61.58,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,98,1314.552,402.044,-61.679,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,99,1312.79,398.461,-62.362,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,100,1307.019,376.076,-67.29,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,101,1304.085,365.252,-67.292,0,'Varian Wrynn - Battle for the Undercity'),
(@VARIAN,102,1302.529,359.509,-67.295,0,'Varian Wrynn - Battle for the Undercity');

-- Texty
DELETE FROM `creature_text` WHERE `entry` IN (@VARIAN,@JAINA,@PUTRESS,@THRALL);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@VARIAN,0,0,'Heroes of the Alliance, your King calls! Gather behind me at the entrance to the sewers of the Undercity!',14,0,100,0,0,16103,'Varian Yell 1'),
(@VARIAN,1,0,'Hidden inside this defiled city is the wretch responsible for murdering our brothers and sisters at the Wrathgate! He must be brought to justice!',14,0,100,0,0,16104,'Varian Yell 2'),
(@VARIAN,2,0,'Soon we march upon this cursed place and cleanse it of its evil taint!',14,0,100,0,0,16102,'Varian Yell 3'),
(@VARIAN,3,0,'The hour of our redemption is close at hand! Prepare yourselves!',14,0,100,0,0,16101,'Varian Yell 4'),
(@VARIAN,4,0,'The march upon the Undercity begins now! Be empowered by your King\'s strength! Follow me, heroes! FOR THE GLORY OF THE ALLIANCE!',14,0,100,0,0,16100,'Varian Yell 5'),
(@VARIAN,5,0,'Onward, brothers and sisters! Destiny awaits!',14,0,100,0,0,16079,'Varian Yell 6'),
(@VARIAN,6,0,'Our descent into the depths of depravity begins! Be on guard! Jaina, lend us your strength!',12,0,100,0,0,16080,'Varian Say 1'),
(@VARIAN,7,0,'What is this?! Stand your ground! Do not give them an inch!',12,0,100,0,0,16081,'Varian Say 2'),
(@VARIAN,8,0,'Grand Apotecary Putress unleashed the Engorged Blight Worm!',41,0,100,0,0,0,'Varian Emote 1'),
(@VARIAN,9,0,'Soldiers, fall in! Guard the halls!',14,0,100,0,0,16082,'Varian Yell 7'),
(@VARIAN,10,0,'Your aberrations are no match for the Alliance, Putress! We\'re coming for you!',14,0,100,0,0,16083,'Varian Yell 8'),
(@VARIAN,11,0,'Horde. By the looks of the struggle, they are here in force - somewhere.',12,0,100,0,0,16084,'Varian Say 3'),
(@VARIAN,12,0,'Stay alert and on guard. There\'s no telling what horrors await us.',12,0,100,0,0,16085,'Varian Say 4'),
(@VARIAN,13,0,'ONWARD!',12,0,100,0,0,16086,'Varian Say 5'),
(@VARIAN,14,0,'The main chamber is this way! Let\'s go!',12,0,100,0,0,16087,'Varian Say 6'),
(@VARIAN,15,0,'THERE!',12,0,100,0,0,16088,'Varian Say 7'),
(@VARIAN,16,0,'There\'s nowhere to run, monster!',14,0,100,0,0,16089,'Varian Yell 9'),
(@VARIAN,17,0,'And justice is served!',14,0,100,0,0,16090,'Varian Yell 10'),
(@VARIAN,18,0,'What say you now, Putress?',12,0,100,0,0,16091,'Varian Say 8'),
(@VARIAN,19,0,'Look around you, brothers and sisters. Open your eyes! Look at what they have done to our kingdom!',12,0,100,0,0,16092,'Varian Say 9'),
(@VARIAN,20,0,'How much longer will we allow these savages free reign in our world?',12,0,100,0,0,16093,'Varian Say 10'),
(@VARIAN,21,0,'I have seen the Horde\'s world. I have been inside their cities. Inside their minds...',12,0,100,0,0,16094,'Varian Say 11'),
(@VARIAN,22,0,'I know what evil lies in the hearts of orcs.',12,0,100,0,0,16095,'Varian Say 12'),
(@VARIAN,23,0,'THRALL! HERE?',12,0,100,0,0,16096,'Varian Say 13'),
(@VARIAN,24,0,'ONWARD! We end this now!',12,0,100,0,0,16097,'Varian Say 14'),
(@VARIAN,25,0,'The orcs have a battle cry: LOK\'TAR OGAR! It means "victory or death." Fitting...',12,0,100,0,0,16098,'Varian Say 15'),
(@VARIAN,26,0,'To the throne room!',12,0,100,0,0,16099,'Varian Say 16'),
(@VARIAN,27,0,'I was away for too long. My absence cost us the lives of some of our greatest heroes. Trash like you and this evil witch were allowed to roam free -- unchecked.',12,0,100,0,0,16073,'Varian Say 17'),
(@VARIAN,28,0,'The time has come to make things right. To disband your treacherous kingdom of murderers and thieves. Putress was the first strike. Many more will come.',12,0,100,0,0,16074,'Varian Say 18'),
(@VARIAN,29,0,'I\'ve waited a long time for this, Thrall. For every time I was thrown into one of your damned arenas... for every time I killed a green-skinned aberration like you... I could only think of one thing.',12,0,100,0,0,16075,'Varian Say 19'),
(@VARIAN,30,0,'What our world could be without you and your twisted Horde... It ends now, Warchief.',12,0,100,0,0,16076,'Varian Say 20'),
(@VARIAN,31,0,'ATTACK! FOR STORMWIND! FOR BOLVAR! FOR THE ALLIANCE!',12,0,100,0,0,16077,'Varian Say 21'),

(@JAINA,0,0,'Right away, your majesty!',12,0,100,0,0,16126,'Jaina Say 1'),
(@JAINA,1,0,'What\'s happened here? There are corpses everywhere... the stench... overwhelming..',12,0,100,0,0,16127,'Jaina Say 2'),
(@JAINA,2,0,'Varian, stop! I won\'t help you do this!',12,0,100,0,0,16128,'Jaina Say 3'),
(@JAINA,3,0,'VARIAN, NO! STOP!',14,0,100,0,0,16122,'Jaina Yell 1'),
(@JAINA,4,0,'It did not have to be like this...',12,0,100,0,0,16123,'Jaina Say 4'),

(@PUTRESS,0,0,'Do not let them pass, minions!',14,0,100,0,0,16289,'Putress Yell 1'),
(@PUTRESS,1,0,'KILL THEM! My work must not be interrupted!',14,0,100,0,0,16290,'Putress Yell 2'),
(@PUTRESS,2,0,'Stare into the abyss and watch as it blackens your souls!',14,0,100,0,0,16294,'Putress Yell 3'),
(@PUTRESS,3,0,'You are no match for my creations!',14,0,100,0,0,16295,'Putress Yell 4'),
(@PUTRESS,4,0,'This cannot be happening!',14,0,100,0,0,16296,'Putress Yell 5'),
(@PUTRESS,5,0,'It will not end like this! I\'ve worked too hard! So many years... I... I will consume more energy!',14,0,100,0,0,16291,'Putress Yell 6'),
(@PUTRESS,6,0,'The power washes through me! I see... EVERTHING!',14,0,100,0,0,16292,'Putress Yell 7'),
(@PUTRESS,7,0,'MORE SUFFERING AWAITS!',14,0,100,0,0,16293,'Putress Yell 8'),

(@THRALL,0,0,'WE ARE VICTORIOUS!',14,1,100,0,0,16212,'Thrall Yell 1'),
(@THRALL,1,0,'The Undercity belongs to the Horde once more! LOK\'TAR!',14,1,100,0,0,16214,'Thrall Yell 2');

-- Scripty i SAI
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@JAINA);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@JAINA, 0, 0, 0, 0, 0, 100, 0, 16000, 35000, 15000, 35000, 11, 20680, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Jaina - IC - cast Blizzard'),
(@JAINA, 0, 1, 0, 0, 0, 100, 0, 2500, 4500, 5500, 9500, 11, 20679, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Jaina - IC - cast Fire Blast'),
(@JAINA, 0, 2, 0, 0, 0, 100, 0, 0, 2500, 3000, 5000, 11, 20692, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Jaina - IC - cast Fireball'),
(@JAINA, 0, 3, 0, 0, 0, 100, 0, 15000, 45000, 15000, 45000, 11, 61128, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - IC - cast Summon Water Elementals'),
(@JAINA, 0, 4, 5, 34, 0, 100, 0, 8, 103, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 5.902637, 'Jaina - on pos 103 - set orient'),
(@JAINA, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 90, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on pos 103 - set creep flag'),
(@JAINA, 0, 6, 0, 34, 0, 100, 0, 8, 104, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 5.454961, 'Jaina - on pos 104 - set orient'),
(@JAINA, 0, 7, 0, 34, 0, 100, 0, 8, 105, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1.259334, 'Jaina - on pos 105 - set orient');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@WATER_ELEMENTAL);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@WATER_ELEMENTAL, 0, 0, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 11, 46983, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Water Elemental - IC - cast Water Bolt');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@FLYING);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@FLYING, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 8000, 10000, 11, 59391, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Alliance Flying Machine - IC - cast Suppressive Fire'),
(@FLYING, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Flying Machine - on aggro - stop combat movement'),
(@FLYING, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Flying Machine - on reset - allow combat movement');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SIEGE);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@SIEGE, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 5000, 8000, 11, 59392, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Alliance Siege Vehicle - IC - cast Siege Shell'),
(@SIEGE, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Flying Vehicle - on aggro - stop melee'),
(@SIEGE, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Flying Vehicle - on reset - allow melee');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@STORMWIND_ELITE);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@STORMWIND_ELITE, 0, 0, 0, 9, 0, 100, 0, 0, 5, 12000, 15000, 11, 9080, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stormwind Elite - on 5 y - cast Harmstring'),
(@STORMWIND_ELITE, 0, 1, 0, 13, 0, 100, 0, 8000, 12000, 0, 0, 11, 11972, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stormwind Elite - on target casting - cast Shield Bash'),
(@STORMWIND_ELITE, 0, 2, 0, 0, 0, 100, 0, 7000, 10000, 7000, 10000, 11, 14516, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stormwind Elite - IC - cast Strike'),
(@STORMWIND_ELITE, 0, 3, 4, 34, 0, 100, 0, 8, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, @WORM, 100, 0, 0, 0, 0, 0, 'Stormwind Elite - on pos 0 - set facing to Worm'),
(@STORMWIND_ELITE, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 90, 2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormwind Elite - on pos 0 - set creep');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@GUARDIAN);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@GUARDIAN, 0, 0, 0, 9, 0, 100, 0, 8, 40, 15000, 20000, 11, 59395, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Treacherous Guardian - on 8-40y - cast Abomination Hook');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@DREADLORD);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@DREADLORD, 0, 0, 0, 0, 0, 100, 0, 18000, 23000, 17000, 24000, 11, 22884, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Perfidious Dreadlord - IC - cast Psychic Scream'),
(@DREADLORD, 0, 1, 0, 0, 0, 100, 0, 1000, 3000, 5000, 7000, 11, 15587, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Perfidious Dreadlord - IC - cast Mind Blast'),
(@DREADLORD, 0, 2, 0, 0, 0, 100, 0, 9000, 14000, 12000, 16000, 11, 37624, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Perfidious Dreadlord - IC - cast Carrion Swarm');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@FELBEAST);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@FELBEAST, 0, 0, 0, 0, 0, 100, 0, 9000, 15000, 8000, 14000, 11, 38356, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Plagued Felbeast - IC - cast Psychic Scream'),
(@FELBEAST, 0, 1, 0, 9, 0, 100, 0, 0, 5, 12000, 16000, 11, 16128, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Plagued Felbeast - on 5y - cast Infected Bite');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@MARAUDER);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@MARAUDER, 0, 0, 0, 9, 0, 100, 0, 0, 5, 7000, 12000, 11, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Marauder - on 5y - cast Cleave'),
(@MARAUDER, 0, 1, 0, 0, 0, 100, 0, 9000, 15000, 16000, 21000, 11, 18072, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Marauder - IC - cast Uppercut'),
(@MARAUDER, 0, 2, 0, 0, 0, 100, 0, 12000, 18000, 18000, 24000, 11, 23113, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Felguard Marauder - IC - cast Blast Wave');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@BETRAYER);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@BETRAYER, 0, 0, 0, 9, 0, 100, 0, 0, 5, 6000, 9000, 11, 32202, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ravishing Betrayer - on 5y - cast Lash of Pain'),
(@BETRAYER, 0, 1, 0, 0, 0, 100, 0, 9000, 14000, 8000, 12000, 11, 24616, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ravishing Betrayer - IC - cast Shadow Shock');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@CHEMIST);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@CHEMIST, 0, 0, 0, 0, 0, 100, 0, 11000, 16000, 18000, 24000, 11, 59122, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Apothecary Chemist - IC - cast Vial of Blight');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@WORM);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@WORM, 0, 0, 0, 0, 0, 100, 0, 8000, 10000, 20000, 30000, 11, 61125, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Engorged Blight Worm - IC - cast Blight Breath'),
(@WORM, 0, 1, 0, 0, 0, 100, 0, 25000, 30000, 30000, 30000, 11, 61123, 0, 0, 0, 0, 0, 21, 40, 0, 0, 0, 0, 0, 0, 'Engorged Blight Worm - IC - cast Ingest'),
(@WORM, 0, 2, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, @VARIAN, 20, 0, 0, 0, 0, 0, 'Engorged Blight Worm - on death - set data 1 to Varian');

UPDATE `creature_model_info` SET `combat_reach`=10 WHERE `modelid`=27992;

DELETE FROM `spell_scripts` WHERE `id`=61123;
INSERT INTO `spell_scripts` VALUES
(61123,0,0,15,61124,3,0,0,0,0,0);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@THRALL);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
-- (@THRALL, 0, 0, 0, 0, 0, 100, 0, 8000, 10000, 15000, 20000, 11, 59517, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrall - IC - cast Chain Lightning'),
(@THRALL, 0, 1, 0, 0, 0, 100, 0, 3000, 4000, 10000, 10000, 11, 59519, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrall - IC - cast Lava Burst');
-- (@THRALL, 0, 2, 0, 0, 0, 100, 0, 10000, 12000, 20000, 30000, 11, 59507, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thrall - IC - cast Thunder');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SYLVANAS) AND `id` IN (40,41,42);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@SYLVANAS, 0, 40, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 20463, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on aggro - cast Shoot'),
(@SYLVANAS, 0, 41, 0, 9, 0, 100, 0, 0, 30, 7500, 9000, 11, 59515, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on 0-30y - cast Multi-Shot'),
(@SYLVANAS, 0, 42, 0, 0, 0, 100, 0, 10000, 12000, 20000, 30000, 11, 59514, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - IC - cast Shriek of the Highborne');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@WARSONG_BATTLEGUARD);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@WARSONG_BATTLEGUARD, 0, 0, 0, 9, 0, 100, 0, 8, 25, 12000, 19000, 11, 57793, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Warsong Battleguard - on 5-25y - cast Heroic Leap');
