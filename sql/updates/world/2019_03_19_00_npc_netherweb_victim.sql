UPDATE `creature_template` SET `InhabitType` = 8, `MovementType` = 0, `unit_flags` = 262144 | 131072, `flags_extra` = 2 WHERE `entry` = 22355;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 22355 AND `id` IN (8,9);
INSERT INTO `smart_scripts` VALUES
(22355, 0, 8, 9, 11, 0, 100, 1, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Netherweb Victim - On Respawn - Disable Combat Movement (No Repeat)'),
(22355, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 18, 2097152, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Netherweb Victim - On Respawn - Set Flag Disarmed (No Repeat)');
