-- Delete wolf summon on reset.
DELETE FROM `smart_scripts` WHERE `entryorguid` = 3265 AND `id` = 2;

SET @GUID := 302427; -- set by tdb team
-- insert 9 razormane wolves into new guids (@GUID to @GUID+8) with invalid xyz coords (we don't know them yet)
DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID+8;
INSERT INTO `creature` (`guid`,`id`,`map`,`position_x`,`position_y`, `position_z`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID  ,3939,1,0,0,0,90,120,1),
(@GUID+1,3939,1,0,0,0,90,120,1),
(@GUID+2,3939,1,0,0,0,90,120,1),
(@GUID+3,3939,1,0,0,0,90,120,1),
(@GUID+4,3939,1,0,0,0,90,120,1),
(@GUID+5,3939,1,0,0,0,90,120,1),
(@GUID+6,3939,1,0,0,0,90,120,1),
(@GUID+7,3939,1,0,0,0,90,120,1),
(@GUID+8,3939,1,0,0,0,90,120,1);
-- bind the wolves to the 9 razormane hunters (id 3265)
DELETE FROM `creature_formations` WHERE `leaderGUID` BETWEEN 20301 AND 20309;
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`) VALUES 
(20301,20301,0,0,2),
(20301,@GUID,4,60,2),
(20302,20302,0,0,2),
(20302,@GUID+1,4,60,2),
(20303,20303,0,0,2),
(20303,@GUID+2,4,60,2),
(20304,20304,0,0,2),
(20304,@GUID+3,4,60,2),
(20305,20305,0,0,2),
(20305,@GUID+4,4,60,2),
(20306,20306,0,0,2),
(20306,@GUID+5,4,60,2),
(20307,20307,0,0,2),
(20307,@GUID+6,4,60,2),
(20308,20308,0,0,2),
(20308,@GUID+7,4,60,2),
(20309,20309,0,0,2),
(20309,@GUID+8,4,60,2);
-- now set the wolf pets to the same xyz as their leader
UPDATE `creature` c1,`creature` c2,`creature_formations` cf SET c1.`position_x`=c2.`position_x`,c1.`position_y`=c2.`position_y`,c1.`position_z`=c2.`position_z` WHERE c1.`guid`=cf.`memberGUID` AND c2.`guid`=cf.`leaderGUID` AND c1. `guid` BETWEEN @GUID AND @GUID+8;
