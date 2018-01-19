SET @LEADER_GUID:= 128103;
DELETE FROM `creature_formations` WHERE `leaderGUID` = @LEADER_GUID;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@LEADER_GUID, 128103, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128104, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128105, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128106, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128107, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128108, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128109, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128110, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128111, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128112, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128113, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128114, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128115, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128116, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128117, 0, 0, 3, 0, 0),
(@LEADER_GUID, 128118, 0, 0, 3, 0, 0);
