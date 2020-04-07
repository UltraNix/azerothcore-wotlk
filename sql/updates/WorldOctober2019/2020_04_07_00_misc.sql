-- DB/Misc: correct height of Sunfury Magister beams near Manaforge Bnaar https://github.com/SunwellTracker/issues/issues/2841
UPDATE `creature` SET `position_z` = `position_z` - 3.5 WHERE `id` = 19421;
-- DB/AI: Sunfury technician - update AI to prevent them from going places https://github.com/SunwellTracker/issues/issues/2842
DELETE FROM `smart_scripts` WHERE `entryorguid` = 20218 AND `id` = 18;
INSERT INTO `smart_scripts` VALUES 
(20218, 0, 18, 0, 54, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sunfury Technician - On Just Summoned - Set Home Position');
-- DB/Creature: Rabid Brown Bear - fix spawn in textures https://github.com/SunwellTracker/issues/issues/2843
UPDATE `creature` SET `position_x` = -22.64, `position_y` = -3549.97, `position_z` = 34.58 WHERE `guid` = 101032;