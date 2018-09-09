UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 24250;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (24250, 2425000);
INSERT INTO `smart_scripts` VALUES
(24250, 0, 0, 0, 0, 0, 100, 0, 5000, 7000, 25000, 35000, 11, 11977, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Combat - Cast Spell Rend'),
(24250, 0, 1, 0, 0, 0, 100, 0, 20000, 25000, 30000, 40000, 11, 35948, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Combat - Cast Spell Bloodthirst'),
(24250, 0, 2, 0, 4, 0, 80, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Aggro - talk'),
(24250, 0, 3, 0, 75, 0, 20, 0, 0, 24249, 10, 5000, 80, 2425000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Creature Distance - Run script'),
(24250, 0, 4, 0, 75, 0, 30, 0, 0, 24226, 5, 60000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Creature Distance - Say text'),
(2425000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 24249, 10, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Script - turn to 24249'),
(2425000, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 5, 113, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Script - emote salute'),
(2425000, 9, 2, 0, 0, 0, 20, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Script - talk'),
(2425000, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dragonflayer Fleshripper - Script - turn back');

DELETE FROM `creature_text` WHERE `entry` = 24250;
INSERT INTO `creature_text` VALUES
(24250, 0, 0, 'Beg for your life...', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 0, 1, 'Suffer, insect!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 0, 2, 'Your end draws closer!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 0, 3, 'My life for Ymiron!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 0, 4, 'For Ymiron!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 0, 5, 'YAAARRRGH!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 1, 0, 'The interlopers will be stopped, my lord.', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 1, 1, 'One among us will ascend on this day.', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 1, 2, 'My life for the Dread King!', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 2, 0, 'I should be in Utgarde Keep, battling at Ingvar\'s side! Instead I am charged to guard little maggots like you.', 12, 0, 100, 0, 0, 0, 0, 'Dragonflayer Fleshripper'),
(24250, 2, 1, 'Why we don\'t just kill you is beyond my understanding.', 12, 0, 100, 0, 0, 0, 0,  'Dragonflayer Fleshripper'),
(24250, 2, 2, 'Ingvar has plans for you, little one.', 12, 0, 100, 0, 0, 0, 0,  'Dragonflayer Fleshripper'),
(24250, 2, 3, 'Your time in the Ring of Judgment comes soon, maggot.', 12, 0, 100, 0, 0, 0, 0,  'Dragonflayer Fleshripper');
