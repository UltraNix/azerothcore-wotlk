DELETE FROM `smart_scripts` WHERE `entryorguid` = 2811301 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2811302;
INSERT INTO `smart_scripts` VALUES
(2811302, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mosswalker Victim - On Script - Say Line 1'),
(2811302, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 85, 52157, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mosswalker Victim - On Script - Invoker Cast \'Mosswalker Quest Credit\''),
(2811302, 9, 2, 0, 0, 0, 100, 0, 100, 100, 0, 0, 28, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mosswalker Victim - On Script - Remove Aura \'Permanent Feign Death (Drowned Anim)\''),
(2811302, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mosswalker Victim - On Script - Despawn'),
(2811301, 9, 2, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mosswalker Victim - On Script - Despawn');
