-- DB/GO: Fix unreachable mining node in icecrown - https://github.com/SunwellTracker/issues/issues/2934
UPDATE `gameobject` SET `position_x` = 8488.05, `position_y` = 1449.59, `position_z` = 655.43 WHERE `guid` = 163813;
