DELETE FROM `smart_scripts` WHERE `entryorguid` IN (27531,27685) AND `id` IN (1,2);
INSERT INTO `smart_scripts` VALUES
(27531, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frigid Abomination Attacker - On Reset - Set React State Aggresive'),
(27531, 0, 2, 0, 1, 0, 100, 0, 2000, 4000, 10000, 15000, 8, 2, 0, 0, 0, 0, 0, 25, 20, 0, 0, 0, 0, 0, 0, 'Frigid Abomination Attacker - OOC - Attack Closest Enemy'),
(27685, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frigid Ghoul Attacker - On Reset - Set React State Aggresive'),
(27685, 0, 2, 0, 1, 0, 100, 0, 2000, 4000, 10000, 15000, 8, 2, 0, 0, 0, 0, 0, 25, 20, 0, 0, 0, 0, 0, 0, 'Frigid Ghoul Attacker -  OOC - Attack Closest Enemy');
