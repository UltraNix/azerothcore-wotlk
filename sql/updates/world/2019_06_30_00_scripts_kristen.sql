SET @KRISTEN = 18294;
SET @GANKLY = 18297;

DELETE FROM `creature_text` WHERE `entry` IN (@KRISTEN, @GANKLY);
INSERT INTO `creature_text` VALUES
(@KRISTEN, 0, 0, 'Hi, Harold. I have your skins!', 12, 0, 100, 0, 0, 0, 0, 'Kristen DeMeza'),
(@KRISTEN, 1, 0, 'Ack! Somebody help me!', 14, 0, 100, 0, 0, 0, 0, 'Kristen DeMeza'),
(@GANKLY, 0, 0, 'I\'ll be taking those skins, tiny.', 12, 0, 100, 0, 0, 0, 0, 'Gankly Rottenfist');

DELETE FROM `creature` WHERE `id` = @GANKLY;

UPDATE `creature` SET `spawntimesecs` = 900 WHERE `id` = @KRISTEN;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (@KRISTEN, @GANKLY);
UPDATE `creature_template` SET `faction` = 250 WHERE `entry` = @KRISTEN;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@KRISTEN, @GANKLY, @KRISTEN*100);
INSERT INTO `smart_scripts` VALUES
(@KRISTEN, 0, 0, 1, 11, 0, 100, 1, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - On Respawn - Remove flag questgiver'),
(@KRISTEN, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 53, 0, @KRISTEN, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - On Respawn - Start WP'),
(@KRISTEN, 0, 2, 4, 40, 0, 100, 0, 6, 0, 0, 0, 80, @KRISTEN*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - On WP Reached - Start Script'),
(@KRISTEN*100, 9, 0, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - Script - Talk 0'),
(@KRISTEN*100, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 2000, 2000, 12, @GANKLY, 4, 10000, 1, 0, 0, 8, 0, 0, 0, -1440.91, 6346.25, 38.20, 0, 'Kristen - Script - Summon Gankly'),
(@KRISTEN*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, @GANKLY, 25, 0, 0, 0, 0, 0, 'Kristen - Script - Gankly Say 0'),
(@KRISTEN*100, 9, 3, 0, 0, 0, 100, 0, 2000, 2000, 2000, 2000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - Script - Say 1'),
(@KRISTEN, 0, 3, 0, 38, 0, 100, 0, 1, 1, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - On Data Set 1 1 - Set flag questgiver'),
(@KRISTEN, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 120000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kristen - On Data Set 1 1 - Despawn in 2 mins'),
(@GANKLY, 0, 0, 0, 6, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @KRISTEN, 50, 0, 0, 0, 0, 0, 'Gankly - On Death - Set 1 1 on Kristen');

DELETE FROM `waypoints` WHERE `entry` = @KRISTEN;
INSERT INTO `waypoints` VALUES
(@KRISTEN, 1, -1260.25, 6242.72, 50.84, ''),
(@KRISTEN, 2, -1272.17, 6250.24, 49.26, ''),
(@KRISTEN, 3, -1285.34, 6282.34, 47.52, ''),
(@KRISTEN, 4, -1316.89, 6305.80, 45.44, ''),
(@KRISTEN, 5, -1372.96, 6350.22, 41.77, ''),
(@KRISTEN, 6, -1445.41, 6350.39, 37.51, '');
