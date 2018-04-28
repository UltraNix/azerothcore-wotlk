UPDATE `pool_template` SET `max_limit` = 25 WHERE `entry` = 2013;
SET @POOL = 4740;
DELETE FROM `pool_template` WHERE `entry` IN (@POOL, @POOL+1, @POOL+2, @POOL+3);
INSERT INTO `pool_template` VALUES
(@POOL, 1, 'Spawn Point 41 - Ghostlands'),
(@POOL+1, 1, 'Spawn Point 42 - Ghostlands'),
(@POOL+2, 1, 'Spawn Point 43 - Ghostlands'),
(@POOL+3, 1, 'Spawn Point 43 - Ghostlands');

DELETE FROM `pool_gameobject` WHERE `guid` IN (75026,75025,75024,75107,75106,75105,75092,75091,75090,75053,75052,75051);
INSERT INTO `pool_gameobject` VALUES
(75026, @POOL, 0, 'Ghostlands - Spawn Point 41'),
(75025, @POOL, 0, 'Ghostlands - Spawn Point 41'), 
(75024, @POOL, 0, 'Ghostlands - Spawn Point 41'),
(75107, @POOL+1, 0, 'Ghostlands - Spawn Point 42'),
(75106, @POOL+1, 0, 'Ghostlands - Spawn Point 42'), 
(75105, @POOL+1, 0, 'Ghostlands - Spawn Point 42'),
(75092, @POOL+2, 0, 'Ghostlands - Spawn Point 43'),
(75091, @POOL+2, 0, 'Ghostlands - Spawn Point 43'), 
(75090, @POOL+2, 0, 'Ghostlands - Spawn Point 43'),
(75053, @POOL+3, 0, 'Ghostlands - Spawn Point 44'),
(75052, @POOL+3, 0, 'Ghostlands - Spawn Point 44'), 
(75051, @POOL+3, 0, 'Ghostlands - Spawn Point 44');

DELETE FROM `pool_pool` WHERE `pool_id` IN (@POOL, @POOL+1,@POOL+2,@POOL+3);
INSERT INTO `pool_pool` VALUES
(@POOL, 2013, 0, 'Spawn Point 41 - Ghostlands'),
(@POOL+1, 2013, 0, 'Spawn Point 42 - Ghostlands'),
(@POOL+2, 2013, 0, 'Spawn Point 43 - Ghostlands'),
(@POOL+3, 2013, 0, 'Spawn Point 44 - Ghostlands');
