DELETE FROM `smart_scripts` WHERE `entryorguid` = 80001;
INSERT INTO `smart_scripts` VALUES
(80001, 0, 0, 0, 1, 0, 100, 1, 10000, 10000, 10000, 10000, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - OOC - Set Active'),
(80001, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 80, 8000100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - OOC - Start Script'),
(80001, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Warsong Event Trigger - On Data Set - Despawn');
