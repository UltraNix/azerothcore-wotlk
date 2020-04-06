-- DB/Misc: DK starting zone - fix issues with some mobs/ai https://github.com/SunwellTracker/issues/issues/3017
DELETE FROM `creature` WHERE `guid` IN (129545,129544);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28577;
INSERT INTO `smart_scripts` VALUES
(28577, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Reset - Set Event Phase'),
(28577, 0, 1, 2, 4, 1, 100, 0, 0, 0, 0, 0, 11, 52384, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Cast Cosmetic - Periodic Cower Effect'),
(28577, 0, 2, 3, 61, 1, 100, 0, 0, 0, 0, 0, 11, 52385, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Cast Cosmetic - Periodic Cower'),
(28577, 0, 3, 4, 61, 1, 100, 0, 0, 0, 0, 0, 11, 51604, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Cast Self Stun'),
(28577, 0, 4, 5, 61, 1, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Say Line 1'),
(28577, 0, 5, 0, 61, 1, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Set Event Phase 2'),
(28577, 0, 6, 0, 4, 2, 50, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Aggro - Say Line 0'),
(28577, 0, 7, 0, 2, 2, 50, 1, 0, 30, 0, 0, 11, 52262, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - Between Health 0-30% - Cast Cornered and Enraged!'),
(28577, 0, 8, 0, 6, 0, 50, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Citizen of Havenshire - On Death - Say Line 2');

UPDATE `smart_scripts` SET `action_param2` = 0 WHERE `entryorguid` = 28611 AND `id` = 0;
