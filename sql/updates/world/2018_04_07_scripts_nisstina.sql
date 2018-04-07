DELETE FROM `creature_text` WHERE `entry` = 29778;
INSERT INTO `creature_text` VALUES
(29778, 0, 0, 'I don\'t be worryin\' \'bout no Lich Kings. Seen a lotta big-shots come and go, dey always messin\' somethin\' up.It ain\'t long aftah that when a posse rolls on through and sends dem quick on dey way to da history books. Dis one ain\'t no different.', 12, 0, 100, 0, 0, 0, 0, 'Scout Nisstina'),
(29778, 0, 1, 'When it comes to treasure, never be lookin\' sideways at lootin\' someone else\'s junk. Stolen goods be much sweeter, ya? But free is free, no matta how it got that way!', 12, 0, 100, 0, 0, 0, 0, 'Scout Nisstina'),
(29778, 0, 2, 'I always be up for a nice three-fingered discount. Stealin\' be all in the wrist...and when that fails ya, then ya stick something sharp in between the ribs, and that\'s all in the wrist too. Skilled hands be worth more than a steady job, ya heard?', 12, 0, 100, 0, 0, 0, 0, 'Scout Nisstina');

UPDATE `creature_template` SET `AIName` = "SmartAI", `npcflag` = 1 WHERE `entry` = 29778;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29778, 2977800);
INSERT INTO `smart_scripts` VALUES
(29778, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 80, 2977800, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scout Nisstina - On Gossip Hello - Run Script'),
(2977800, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scout Nisstina - Script - Remove npc flag'),
(2977800, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scout Nisstina - Script - Say random line'),
(2977800, 9, 2, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scout Nisstina - Script - Add npc flag');
