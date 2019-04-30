SET @GUID := 85192;
DELETE FROM `creature` WHERE `guid` = @GUID;
INSERT INTO `creature` VALUES (@GUID,36209,571,1,1,0,0,4027.14,-3771.86,114.672,3.15258,300,0,0,42,0,0,0,0,0);

DELETE FROM `game_event_creature` WHERE guid = @GUID;
INSERT INTO `game_event_creature` VALUES (10, @GUID);