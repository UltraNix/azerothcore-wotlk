UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 5193;
DELETE FROM `gossip_menu_option` WHERE `menu_id` = 10392;
INSERT INTO `gossip_menu_option` VALUES
(10392, 0, 1, 'Let me browse your goods.', 3, 128, 0, 0, 0, 0, ''),
(10392, 1, 0, 'I\'ve lost my Blood Knight Tabard.', 1, 1, 0, 0, 0, 0, ''),
(10392, 2, 0, 'I\'ve lost my Tabard of the Hand.', 1, 1, 0, 0, 0, 0, ''),
(10392, 3, 0, 'I\'ve lost my Tabard of the Protector.', 1, 1, 0, 0, 0, 0, ''),
(10392, 4, 0, 'I\'ve lost my Green Trophy Tabard of the Illidari.', 1, 1, 0, 0, 0, 0, ''),
(10392, 5, 0, 'I\'ve lost my Purple Trophy Tabard of the Illidari.', 1, 1, 0, 0, 0, 0, ''),
(10392, 6, 0, 'I\'ve lost my Tabard of Summer Skies.', 1, 1, 0, 0, 0, 0, ''),
(10392, 7, 0, 'I\'ve lost my Tabard of Summer Flames.', 1, 1, 0, 0, 0, 0, ''),
(10392, 8, 0, 'I\'ve lost my Loremaster\'s Colors.', 1, 1, 0, 0, 0, 0, ''),
(10392, 9, 0, 'I\'ve lost my Tabard of the Explorer.', 1, 1, 0, 0, 0, 0, ''),
(10392, 10, 0, 'I\'ve lost my Tabard of the Achiever.', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 5193;
INSERT INTO `smart_scripts` VALUES
(5193, 0, 0, 10, 62, 0, 100, 0, 10392, 1, 0, 0, 11, 54974, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 1 Selected - Cast \'Create Blood Knight Tabard\''),
(5193, 0, 1, 10, 62, 0, 100, 0, 10392, 2, 0, 0, 11, 54976, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 2 Selected - Cast \'Create Tabard of the Hand\''),
(5193, 0, 2, 10, 62, 0, 100, 0, 10392, 3, 0, 0, 11, 55008, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin- On Gossip Option 3 Selected - Cast \'Create Tabard of the Protector\''),
(5193, 0, 3, 10, 62, 0, 100, 0, 10392, 4, 0, 0, 11, 54977, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 4 Selected - Cast \'Create Green Trophy Tabard of the Illidari\''),
(5193, 0, 4, 10, 62, 0, 100, 0, 10392, 5, 0, 0, 11, 54982, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 5 Selected - Cast \'Create Purple Trophy Tabard of the Illidari\''),
(5193, 0, 5, 10, 62, 0, 100, 0, 10392, 6, 0, 0, 11, 62768, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 6 Selected - Cast \'Create Tabard of Summer Skies\''),
(5193, 0, 6, 10, 62, 0, 100, 0, 10392, 7, 0, 0, 11, 62769, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 7 Selected - Cast \'Create Tabard of Summer Flames\''),
(5193, 0, 7, 10, 62, 0, 100, 0, 10392, 8, 0, 0, 11, 58194, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 8 Selected - Cast \'Create Loremaster\'s Colors\''),
(5193, 0, 8, 10, 62, 0, 100, 0, 10392, 9, 0, 0, 11, 58224, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 9 Selected - Cast \'Create Tabard of the Explorer\''),
(5193, 0, 9, 10, 62, 0, 100, 0, 10392, 10, 0, 0, 11, 55006, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin- On Gossip Option 10 Selected - Cast \'Create Tabard of the Achiever\''),
(5193, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rebecca Laughlin - On Gossip Option 10 Selected - Close Gossip');

UPDATE `creature_template` SET `npcflag` = `npcflag` | 1 WHERE `entry` IN (5191,16610);

DELETE FROM `conditions` WHERE `SourceGroup` = 10392 AND `SourceTypeOrReferenceId` = 15;
INSERT INTO `conditions` VALUES
(15, 10392, 1, 0, 0, 2, 0, 25549, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Blood Knight Tabard'),
(15, 10392, 1, 0, 0, 8, 0, 9737, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest True Masters of Light'),
(15, 10392, 2, 0, 0, 2, 0, 24344, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of the Hand'),
(15, 10392, 2, 0, 0, 8, 0, 9762, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest The Unwritten Prophecy'),
(15, 10392, 3, 0, 0, 2, 0, 28788, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of the protector'),
(15, 10392, 3, 0, 0, 8, 0, 10259, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest Into the Breach'),
(15, 10392, 4, 0, 0, 2, 0, 31404, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Green Trophy Tabard of Illidari'),
(15, 10392, 4, 0, 0, 2, 0, 31405, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Purple Trophy Tabard of Illidari'),
(15, 10392, 4, 0, 0, 8, 0, 10781, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest Battle of the Crimson Watch'),
(15, 10392, 5, 0, 0, 2, 0, 31404, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Green Trophy Tabard of Illidari'),
(15, 10392, 5, 0, 0, 2, 0, 31405, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Purple Trophy Tabard of Illidari'),
(15, 10392, 5, 0, 0, 8, 0, 10781, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest Battle of the Crimson Watch'),
(15, 10392, 6, 0, 0, 2, 0, 35279, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of Summer Skies'),
(15, 10392, 6, 0, 0, 2, 0, 35280, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of Summer Flames'),
(15, 10392, 6, 0, 0, 8, 0, 11972, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest Shards of Ahune'),
(15, 10392, 7, 0, 0, 2, 0, 35279, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of Summer Skies'),
(15, 10392, 7, 0, 0, 2, 0, 35280, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of Summer Flames'),
(15, 10392, 7, 0, 0, 8, 0, 11972, 0, 0, 0, 0, 0, '', 'Only show gossip if player already finished quest Shards of Ahune'),
(15, 10392, 8, 0, 0, 2, 0, 43300, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Loremaster\'s Colors'),
(15, 10392, 8, 0, 0, 17, 0, 1681, 0, 0, 0, 0, 0, '', 'Only show gossip if player have achievement Loremaster (A)'),
(15, 10392, 8, 0, 1, 2, 0, 43300, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Loremaster\'s Colors'),
(15, 10392, 8, 0, 1, 17, 0, 1682, 0, 0, 0, 0, 0, '', 'Only show gossip if player have achievement Loremaster (H)'),
(15, 10392, 9, 0, 0, 2, 0, 43348, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of the Explorer'),
(15, 10392, 9, 0, 0, 17, 0, 45, 0, 0, 0, 0, 0, '', 'Only show gossip if player have achievement Explore Northrend'),
(15, 10392, 10, 0, 0, 2, 0, 40643, 1, 1, 1, 0, 0, '', 'Only show gossip if player doesn\'t have Tabard of the Explorer'),
(15, 10392, 10, 0, 0, 17, 0, 1021, 0, 0, 0, 0, 0, '', 'Only show gossip if player have achievement Twenty-Five Tabards');
