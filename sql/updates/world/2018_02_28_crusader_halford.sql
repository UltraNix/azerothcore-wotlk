DELETE FROM `gossip_menu_option` WHERE `menu_id` = 11101;
INSERT INTO `gossip_menu_option` VALUES
(11101, 0, 1, 'I want to browse your goods', 3, 128, 0, 0, 0, 0, '');

DELETE FROM `conditions` WHERE `SourceGroup` = 11101 AND `SourceEntry` = 15451;
DELETE FROM `conditions` WHERE `SourceGroup` = 11101 AND `SourceTypeOrReferenceId` = 15;
INSERT INTO `conditions` VALUES
(14, 11101, 15451, 0, 0, 15, 0, 1533, 0, 0, 0, 0, 0, '', 'Show gossip text if player is not a Paladin'),
(15, 11101, 0, 0, 0, 15, 0, 2, 0, 0, 0, 0, 0, '', 'Require Paladin To Show Gossip');
