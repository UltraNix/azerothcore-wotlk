UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24249;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 24249;
INSERT INTO `smart_scripts` VALUES
(24249, 0, 0, 0, 0, 0, 80, 0, 9000, 9000, 6000, 7000, 11, 43512, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Soulreaver - Combat - Cast Spell Mind Flay'),
(24249, 0, 1, 0, 0, 0, 100, 0, 8000, 8000, 30000, 30000, 11, 11639, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Soulreaver - Combat - Cast Spell Shadow Word: Pain'),
(24249, 0, 2, 0, 4, 0, 80, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Soulreaver - Aggro - talk');

DELETE FROM `creature_text` WHERE `entry` = 24249;
INSERT INTO `creature_text` VALUES
(24249, 0, 0, 'Beg for your life...', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 0, 1, 'Suffer, insect!', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 0, 2, 'Your end draws closer!', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 0, 3, 'My life for Ymiron!', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 0, 4, 'For Ymiron!', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 0, 5, 'YAAARRRGH!', 12, 0, 100, 0,  0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 1, 0, 'I sacrifice this human in the name of our dark master!', 12, 0, 100, 53, 0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 1, 1, 'Take me, val\'kyr! I am ready to be judged!', 12, 0, 100, 53, 0, 0, 0, 'Dragonflayer Soulreaver'),
(24249, 1, 2, 'I am ready to die!', 12, 0, 100, 53, 0, 0, 0, 'Dragonflayer Soulreaver');
