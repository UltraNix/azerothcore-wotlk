SET @CGUID = 1979922;

UPDATE `creature_template` SET `AIName`= "SmartAI" WHERE `entry` = 26115;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26115;
INSERT INTO `smart_scripts` VALUES 
(26115, 0, 0, 0, 0, 0, 100, 0, 4000, 6000, 3000, 3000, 11, 50349, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0,'Darkfallen Bloodbearer - in combat - cast icy touch');

DELETE FROM `creature` WHERE `guid` IN (96556,@CGUID);
INSERT INTO `creature` VALUES 
(@CGUID, 26115, 571, 1, 1, 23554, 1, 3928.86, 3578.87, 70.56, 2.71552, 300, 0, 0, 9610, 3309, 2, 0, 0, 0);
 
SET @NPC = @CGUID;
SET @PATH = @NPC * 10;

UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3928.86, 3578.87, 70.56, 2.65,0,0,100,0),
(@PATH,2,3920.99,3583.03, 70.98, 2.65,0,0,100,0),
(@PATH,3,3904.44, 3592.07, 60.92, 2.63,0,0,100,0),
(@PATH,4,3867.03, 3613.95, 47.23, 2.57,0,0,100,0),
(@PATH,5,3857.94, 3620.15, 46.54, 4.06,0,0,100,0),
(@PATH,6,3840.73, 3590.02, 46.96, 4.18,0,0,100,0),
(@PATH,7,3801.80, 3589.35, 49.06, 4.24,0,0,100,0),
(@PATH,8,3838.64, 3669.60, 47.05, 1.07,0,0,100,0),
(@PATH,9,3866.29,3717.07, 48.12, 1.04,0,0,100,0),
(@PATH,10,3882.86, 3701.38, 46.45, 5.94,0,0,100,0),
(@PATH,11,3897.29, 3698.97, 54.66, 6.11,0,0,100,0),
(@PATH,12,3914.31,3696.12, 62.11,5.58,0,0,100,0),
(@PATH,13,3961.72, 3655.27, 62.37, 5.57,0,0,100,0),
(@PATH,14,3953.32, 3639.68, 69.50, 4.23,0,0,100,0),
(@PATH,15,3947.27,3628.47,74.14,4.20,0,0,100,0),
(@PATH,16,3928.86, 3578.87, 70.56, 2.65,0,0,100,0);