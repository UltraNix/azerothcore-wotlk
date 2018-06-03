-- D.E.H.T.A. Enforcer
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=25819;
UPDATE `creature` SET `MovementType`=0, `spawndist`=0 WHERE `id`=25819;

SET @NPC:=132984;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,1329840,0,0,0,0, '');
DELETE FROM `waypoint_data` WHERE `id`=1329840;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(1329840,1,3197.389, 5262.509, 59.1744, 5.665670,0,0,0,100,0),
(1329840,2,3205.473, 5261.450, 59.1744, 0.418089,0,0,0,100,0),
(1329840,3,3213.649, 5266.860, 59.1744, 0.630147,0,0,0,100,0),
(1329840,4,3220.222, 5276.440, 59.1744, 1.021275,0,0,0,100,0),
(1329840,5,3219.638, 5285.621, 59.1744, 1.939406,0,0,0,100,0),
(1329840,6,3211.313, 5295.542, 59.1744, 2.873245,0,0,0,100,0),
(1329840,7,3199.114, 5292.031, 59.1744, 3.573035,0,0,0,100,0),
(1329840,8,3193.253, 5282.330, 59.1744, 4.762128,0,0,0,100,0),
(1329840,9,3195.002, 5273.082, 59.1744, 4.700867,0,0,0,100,0);
