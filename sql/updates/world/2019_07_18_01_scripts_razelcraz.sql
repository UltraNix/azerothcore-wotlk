UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 16915;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 16915;
INSERT INTO `smart_scripts` VALUES 
(16915, 0, 0, 0, 1, 0, 100, 0, 30000, 60000, 30000, 60000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Foreman Razelcraz - OOC - Say Line 0'),
(16915, 0, 1, 0, 1, 0, 100, 0, 45000, 90000, 45000, 90000, 11, 34396, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Foreman Razelcraz - OOC - Cast Zap'),
(16915, 0, 2, 0, 1, 0, 100, 0, 20000, 40000, 20000, 40000, 5, 60, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Foreman Razelcraz - OOC - Play emote oneshotkick');

DELETE FROM `creature_text` WHERE `entry` = 16915;
INSERT INTO `creature_text` VALUES 
(16915, 0, 0, 'I\'ll get you working yet, you bucket of junk.', 12, 0, 100, 1, 0, 0, 0, 'Foreman Razelcraz'),
(16915, 0, 1, 'What?!  You don\'t think I can do it?  I\'ll show you...once I get my parts, that is.', 12, 0, 100, 1, 0, 0, 0, 'Foreman Razelcraz'),
(16915, 0, 2, 'It moved!  I swear, I saw it move!', 12, 0, 100, 0, 0, 0, 0, 'Foreman Razelcraz'),
(16915, 0, 3, 'Ouch!  That\'s not right.', 12, 0, 100, 0, 0, 0, 0, 'Foreman Razelcraz'),
(16915, 0, 4, 'Oh yeah, it\'s real funny isn\'t it?', 12, 0, 100, 1, 0, 0, 0, 'Foreman Razelcraz');

