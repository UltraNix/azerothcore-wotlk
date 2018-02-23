UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = "", `flags_extra` = 2097216 WHERE `entry` IN (27531, 27685);
UPDATE `creature_template` SET `ScriptName` = "", `flags_extra` = 2097216 WHERE `entry` = 27686;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (27531, 27685);
INSERT INTO `smart_scripts` VALUES
(27531, 0, 0, 0, 0, 0, 100, 0, 3000, 6000, 7000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Frigid Abomination Attacker - In Combat - Cast \'Cleave\' (Phase 1) (No Repeat)'),
(27685, 0, 0, 0, 0, 0, 100, 0, 2000, 6000, 14000, 17000, 11, 50361, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Frigid Ghoul Attacker - In Combat - Cast \'Rot Armor\' (Phase 1) (No Repeat)');
