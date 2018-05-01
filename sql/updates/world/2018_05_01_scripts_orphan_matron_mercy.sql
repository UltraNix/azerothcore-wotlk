UPDATE `creature_template` SET `gossip_menu_id` = 8561 WHERE `entry` = 22819;
DELETE FROM `gossip_menu_option` WHERE `menu_id` = 8561;
INSERT INTO `gossip_menu_option` VALUES
(8561, 1, 0, 'I need a new Blood Elf Orphan Whistle.', 1, 1, 0, 0, 0, 0, ''),
(8561, 2, 0, 'I need a new Draenei Orphan Whistle.', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 22819;
INSERT INTO `smart_scripts` VALUES
(22819, 0, 1, 3, 62, 0, 100, 0, 8561, 1, 0, 0, 11, 39512, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Orphan Matron Mercy - On Gossip Option 1 Selected - Cast \'OCW Create Blood Elf Orphan Whistle\''),
(22819, 0, 2, 3, 62, 0, 100, 0, 8561, 2, 0, 0, 11, 39513, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Orphan Matron Mercy - On Gossip Option 2 Selected - Cast \'OCW Create Draenei Orphan Whistle\''),
(22819, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Orphan Matron Mercy - On Gossip Option 2 Selected - Close Gossip');

DELETE FROM `conditions` WHERE `SourceGroup` = 8561 AND `SourceTypeOrReferenceId` = 15;
INSERT INTO `conditions` VALUES
(15, 8561, 1, 0, 0, 12, 0, 10, 0, 0, 0, 0, 0, '', 'Childrens Week must be active'),
(15, 8561, 1, 0, 0, 2, 0, 31880, 1, 0, 1, 0, 0, '', 'Must not have item 31880'),
(15, 8561, 1, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0, '', 'For Team Horde'),
(15, 8561, 2, 0, 0, 12, 0, 10, 0, 0, 0, 0, 0, '', 'Childrens Week must be active'),
(15, 8561, 2, 0, 0, 2, 0, 31881, 1, 0, 1, 0, 0, '', 'Must not have item 31881'),
(15, 8561, 2, 0, 0, 6, 0, 469 , 0, 0, 0, 0, 0, '', 'For Team Alliance');
