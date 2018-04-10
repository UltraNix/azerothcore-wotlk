UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_mirveda" WHERE `entry` = 15402;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (15656, 15958);
INSERT INTO `smart_scripts` VALUES
(15656, 0, 0, 1, 2, 0, 100, 1, 0, 30, 0, 0, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - Between 0-30% Health - Cast \'Enrage\' (No Repeat)'),
(15656, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - Between 0-30% Health - Say Line 0 (No Repeat)'),
(15656, 0, 2, 3, 54, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - On Just Summoned - Set Phase 2'),
(15656, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 15656, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - On Just Summoned - Start WP'),
(15656, 0, 4, 5, 40, 0, 100, 0, 1, 15656, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - On Reached WP1 - Set Home position'),
(15656, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Angershade - On Reached WP1 - Set react state agressive'),
(15656, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 15402, 0, 500, 0, 0, 0, 0, 'Angershade - On Reached WP1 - Attack Apprentice Mirveda'),
(15656, 0, 7, 0, 6, 2, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 15402, 0, 50, 0, 0, 0, 0, 'AngerShadee - On death - Set data'),
(15958, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gharsul the Remorseless - On Just Summoned - Set Phase 2'),
(15958, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 1, 15958, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 'Gharsul the Remorseless - On Just Summoned - Start WP'),
(15958, 0, 2, 3, 40, 0, 100, 0, 1, 15958, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gharsul the Remorseless - On Reached WP1 - Set Home position'),
(15958, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gharsul the Remorseless - On Reached WP1 - Set react state agressive'),
(15958, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 15402, 0, 50, 0, 0, 0, 0, 'Gharsul the Remorseless - On Reached WP1 - Attack Apprentice Mirveda'),
(15958, 0, 5, 0, 6, 2, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 15402, 0, 50, 0, 0, 0, 0, 'Gharsul the Remorseless - On death - Set data');
