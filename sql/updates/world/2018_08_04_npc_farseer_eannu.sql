DELETE FROM `gossip_menu_option` WHERE `menu_id` = 10631;
INSERT INTO `gossip_menu_option` VALUES
(10631, 0, 0, 'I\'ve lost my Totem of the Earthen Ring.', 1, 1, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 35073;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 35073;
INSERT INTO `smart_scripts` VALUES
(35073, 0, 0, 0, 62, 0, 100, 0, 10631, 0, 0, 0, 85, 66747, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Farseer eannu - On Gossip Select - Invoker Cast Relic of the Earthen Ring');
DELETE FROM `conditions` WHERE `SourceGroup` = 10631;
INSERT INTO `conditions` VALUES
(15, 10631, 0, 0, 0, 9, 0, 14111, 0, 0, 0, 0, 0, '', 'Gossip Option requires quest');
