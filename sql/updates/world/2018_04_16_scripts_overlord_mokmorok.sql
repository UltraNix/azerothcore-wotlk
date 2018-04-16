UPDATE `quest_template` SET `SpecialFlags` = 2 WHERE `id` = 1173;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 4500;
UPDATE `creature` SET `spawntimesecs` = 120 WHERE `guid` = 31442;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (4500, 450000, 450001);
INSERT INTO `smart_scripts` VALUES
(4500, 0, 0, 0, 0, 0, 100, 0, 1000, 3000, 7000, 10000, 11, 6749, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - In Combat Update - cast \'Wide Swipe\''),
(4500, 0, 1, 2, 19, 0, 100, 1, 1173, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Quest Accept - Store players (No repeat)'),
(4500, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 450000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Quest Accept - Run Actionlist 450000'),
(4500, 0, 3, 0, 2, 0, 100, 1, 0, 25, 0, 0, 80, 450001, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Health 0%-25% - Run Actionlist 450001 (No repeat)'),
(4500, 0, 4, 0, 0, 0, 100, 1, 0, 0, 0, 0, 42, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - In Combat - Set invincibility hp level (No repeat)'),
(4500, 0, 5, 0, 58, 0, 100, 0, 0, 4500, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on WP End - Despawn'),
(4500, 0, 6, 7, 25, 0, 100, 0, 0, 0, 0, 0, 18, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Reset - Set Unit Flags immune to NPC & immune to PC'),
(4500, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Reset - Remove all auras'),
(4500, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 2, 29, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Reset - Set faction (Orgrimmar)'),
(4500, 0, 9, 0, 11, 0, 100, 0, 0, 0, 0, 0, 42, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Spawn - Set Invincibility at 1 HP'),
(450000, 9, 0, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Say text 0'),
(450000, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Set faction (Monster)'),
(450000, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Remove npcflag Quest Giver'),
(450000, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Remove Unit Flags immune to NPC & immune to PC'),
(450000, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Attack stored player'),
(450001, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 18, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Set Unit Flags immune to NPC & immune to PC'),
(450001, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Remove all auras'),
(450001, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, 29, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Set faction (Orgrimmar)'),
(450001, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Evade'),
(450001, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 15, 1173, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Credit Quest \'Challenge Overlord Mok\'Morokk\''),
(450001, 9, 5, 0, 0, 0, 100, 0, 500, 500, 0, 0, 1, 1, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Say text 1'),
(450001, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 1, 4500, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Mok\'Morokk - Actionlist - Start Waypoint');

DELETE FROM `creature_text` WHERE `entry` = 4500;
INSERT INTO `creature_text` VALUES
(4500, 0, 0, 'Puny $r wanna fight Overlord Mok\'Morokk? Me beat you! Me boss here!', 12, 0, 100, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Quest Accept'),
(4500, 1, 0, 'Me scared! Me run now!', 14, 0, 100, 0, 0, 0, 0, 'Overlord Mok\'Morokk - on Health 0%-25%');

DELETE FROM `waypoints` WHERE `entry` = 4500;
INSERT INTO `waypoints` VALUES
(4500, 1, -3138.49, -2864.64, 34.76, 'Overlord Mok\'Morokk'),
(4500, 2, -3128.08, -2847.37, 34.72, 'Overlord Mok\'Morokk'),
(4500, 3, -3108.94, -2839.6, 34.28, 'Overlord Mok\'Morokk');
