DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29895,2989500);
INSERT INTO `smart_scripts` VALUES
(29895, 0, 0, 0, 11, 0, 100, 1, 0, 0, 0, 0, 80, 2989500, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thrym - On Respawn - Start Script'),
(2989500, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thrym - Script - Say line 0'),
(2989500, 9, 1, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thrym - Script - Say line 1'),
(2989500, 9, 2, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 97, 40, 30, 0, 0, 0, 0, 1, 0, 0, 0, 5595.84, -2187.93, 237.49, 0, 'Thrym - Script - Jump To Pos'),
(2989500, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 4000, 4000, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thrym - Script - Set Home Position'),
(2989500, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 29884, 0, 100, 0, 0, 0, 0, 'Thrym - Script - Attack Gymer'),
(29895, 0, 1, 0, 0, 0, 100, 0, 8000, 16000, 15000, 21000, 11, 28167, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Thrym - In Combat - Cast \'Chain Lightning\' (Phase 1) (No Repeat)'),
(29895, 0, 2, 0, 6, 0, 100, 0, 0, 0, 0, 0, 11, 55662, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Thrym - On Just Died - Cast \'Thrym Kill Credit\' (No Repeat)');

UPDATE `creature` SET `spawntimesecs` = 300 WHERE `guid` = 142488;
