SET @GARREN = 25291;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 9761;
INSERT INTO `gossip_menu_option` VALUES
(9761, 0, 0, "I require water breathing, Garren", 1, 2, 0, 0, 0, 0, '');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 9761;
INSERT INTO `conditions` VALUES
(15, 9761, 0, 0, 0, 9, 0, 11582, 0, 0, 0, 0, 0, '', 'Librarian Garren - show gossip option - on quest Monitoring the Rift: Sundered Chasm taken');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @GARREN;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @GARREN;
INSERT INTO `smart_scripts` VALUES
(@GARREN, 0, 0, 0, 19, 0, 100, 1, 11582, 0, 0, 0, 85, 16881, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Librarion Garren - On Quest:Monitoring the Rift: Sundered Chasm Accepted - Cast Water Breathing'),
(@GARREN, 0, 1, 2, 62, 0, 100, 1, 9761, 0, 0, 0, 85, 16881, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Librarion Garren - On Gossip Option Selected - Cast Water Breathing'),
(@GARREN, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Librarion Garren - On Gossip Option Selected - Close Gossip');