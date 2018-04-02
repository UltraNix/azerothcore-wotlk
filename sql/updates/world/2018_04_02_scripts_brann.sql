SET @BRANN = 29579;

UPDATE `quest_template` SET `PrevQuestId` = 12917 WHERE `id` = 12920;
UPDATE `smart_scripts` SET `link` = 0 WHERE `entryorguid` = @BRANN AND `id` = 1;
UPDATE `smart_scripts` SET `event_type` = 8, `event_param1` = 55578, `event_param2` = 0 WHERE `entryorguid` = @BRANN AND `id` = 2;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @BRANN*100;
INSERT INTO `smart_scripts` VALUES
(2957900, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Set Orientation Owner Or Summoner'),
(2957900, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Remove NPC Flags'),
(2957900, 9, 2, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 0'),
(2957900, 9, 3, 0, 0, 0, 100, 0, 3100, 3100, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Play Emote 25'),
(2957900, 9, 4, 0, 0, 0, 100, 0, 3200, 3200, 0, 0, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 1'),
(2957900, 9, 5, 0, 0, 0, 100, 0, 5600, 5600, 0, 0, 84, 2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 2'),
(2957900, 9, 6, 0, 0, 0, 100, 0, 6300, 6300, 0, 0, 1, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 3'),
(2957900, 9, 7, 0, 0, 0, 100, 0, 7200, 7200, 0, 0, 84, 4, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 4'),
(2957900, 9, 8, 0, 0, 0, 100, 0, 6400, 6400, 0, 0, 1, 5, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 5'),
(2957900, 9, 9, 0, 0, 0, 100, 0, 7200, 7200, 0, 0, 1, 6, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 6'),
(2957900, 9, 10, 0, 0, 0, 100, 0, 7200, 7200, 0, 0, 1, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 7'),
(2957900, 9, 11, 0, 0, 0, 100, 0, 7200, 7200, 0, 0, 1, 8, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 8'),
(2957900, 9, 12, 0, 0, 0, 100, 0, 7100, 7100, 0, 0, 1, 9, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Say Line 9'),
(2957900, 9, 13, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 33, 29579, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Quest Credit \'Catching up with Brann\''),
(2957900, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 82, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Brann Bronzebeard - On Script - Add NPC Flags');
