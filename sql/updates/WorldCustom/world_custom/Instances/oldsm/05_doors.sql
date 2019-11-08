SET @ENTRY := 500000;
SET @GUID := 300000;

DELETE FROM `gameobject_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY+15;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@ENTRY, 0, 444, 'Entrance Doors', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- first room doors
-- first boss
(@ENTRY+1, 0, 444, 'Garden Entrance Doors', '', '', '', 0, 4, 1.2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- first boss entrance
(@ENTRY+2, 0, 444, 'Garden Exit Doors', '', '', '', 0, 4, 1.2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- first boss exit
(@ENTRY+3, 0, 444, 'Garden Secret Doors', '', '', '', 0, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- first boss room doors
-- second boss
(@ENTRY+4, 0, 444, 'Hall of Champions Entrance', '', '', '', 0, 20, 1.2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- second boss entrance 1
(@ENTRY+5, 0, 444, 'Hall of Champions Entrance', '', '', '', 0, 20, 1.2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- second boss entrance 2
(@ENTRY+6, 0, 444, 'Hall of Champions Exit', '', '', '', 0, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- second boss exit
-- third boss
(@ENTRY+7, 0, 444, 'Back Hall Doors', '', '', '', 0, 20, 1.14, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- third boss passage
(@ENTRY+8, 0, 444, 'Back Room Doors', '', '', '', 0, 20, 1.14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- third boss entrance/exit
-- passage
(@ENTRY+9, 0, 4653, 'Main Hall Doors', '', '', '', 0, 20, 0.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- passage doors
-- last room
(@ENTRY+10, 0, 4653, 'End Doors 1', '', '', '', 0, 20, 1.25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- passage doors
(@ENTRY+11, 0, 4653, 'End Doors 2', '', '', '', 0, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- passage doors
(@ENTRY+12, 0, 441, 'Secret Doors', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- secret room
(@ENTRY+13, 0, 413, 'Courtyard Doors', '', '', '', 0, 20, 1.05, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- prisons
(@ENTRY+14, 0, 400, 'Cathedral Doors', '', '', '', 0, 20, 0.88, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0), -- catheral entrance/exit
-- entrance
(@ENTRY+15, 0, 400, 'Old Scarlet Monastery Entrance', '', '', '', 0, 20, 0.88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0); -- instance entrance

DELETE FROM `gameobject` WHERE `id` BETWEEN @ENTRY AND @ENTRY+15;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GUID, @ENTRY, 44, 1, 1, 140.7664, -12.7418, 18.6774, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- first room doors
(@GUID+1, @ENTRY, 44, 1, 1, 140.7664, 10.9548, 18.6774, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- first room doors
-- first boss
(@GUID+2, @ENTRY+1, 44, 1, 1, 161.1367, -57.1645, 18.6774, 0.0000, 0, 0, 1, 0, 0, 100, 0), -- first boss entrance
(@GUID+3, @ENTRY+2, 44, 1, 1, 215.7608, -83.4439, 18.6774, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- first boss exit
(@GUID+4, @ENTRY+3, 44, 1, 1, 184.4769, -106.6946, 18.6774, 1.5708, 0, 0, 1, 0, 0, 100, 1), -- first boss room doors
-- second boss
(@GUID+5, @ENTRY+4, 44, 1, 1, 232.5233,  -100.0000, 18.6782, 3.1416, 0, 0, 1, 0, 0, 100, 0), -- second boss entrance 1
(@GUID+6, @ENTRY+5, 44, 1, 1, 244.7465,  -100.0000, 18.6779, 0.0000, 0, 0, 1, 0, 0, 100, 0), -- second boss entrance 2
(@GUID+7, @ENTRY+6, 44, 1, 1, 286.8494,  -100.0500, 31.4949, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- second boss exit
-- third boss
(@GUID+8, @ENTRY+7, 44, 1, 1, 237.3485,  -29.9402, 31.4936, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- third boss passage
(@GUID+9, @ENTRY+8, 44, 1, 1, 220.5461,  25.8464, 31.4936, 3.1416, 0, 0, 1, 0, 0, 100, 0), -- third boss entrance/exit
-- passage
(@GUID+10, @ENTRY+9, 44, 1, 1, 308.5686,  -53.5707, 31.4911, 3.1416, 0, 0, 1, 0, 0, 100, 1), -- passage
-- last room
(@GUID+11, @ENTRY+10, 44, 1, 1, 374.2939,  -120.6913, 32.4946, 1.5708, 0, 0, 1, 0, 0, 100, 1), -- end room doors 1
(@GUID+12, @ENTRY+11, 44, 1, 1, 374.2939,  -133.9144, 30.6106, 1.5708, 0, 0, 1, 0, 0, 100, 1), -- end room doors 2
(@GUID+13, @ENTRY+12, 44, 1, 1, 322.5289,  -115.6555, 32.0727, 0.0000, 0, 0, 1, 0, 0, 100, 1), -- secret room
(@GUID+14, @ENTRY+13, 44, 1, 1, 430.6579,  -102.6583, 30.8281, 4.7124, 0, 0, 1, 0, 0, 100, 1), -- prison 1
(@GUID+15, @ENTRY+13, 44, 1, 1, 412.4076,  -102.6583, 30.8281, 4.7124, 0, 0, 1, 0, 0, 100, 1), -- prison 2
(@GUID+16, @ENTRY+13, 44, 1, 1, 315.2256,  -102.6583, 30.8281, 4.7124, 0, 0, 1, 0, 0, 100, 1), -- prison 3
(@GUID+17, @ENTRY+14, 44, 1, 1, 374.4284,  -18.3253, 31.4945, 4.7124, 0, 0, 1, 0, 0, 100, 0), -- cathedral entrance/exit
-- entrance
(@GUID+18, @ENTRY+15, 44, 1, 1, 72.4432,  -0.7665, 18.6774, 0.0000, 0, 0, 1, 0, 0, 100, 1); -- instance entrance
