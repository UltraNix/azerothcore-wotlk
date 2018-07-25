DELETE FROM `gossip_menu_option` WHERE `menu_id` = 1470;
INSERT INTO `gossip_menu_option` VALUES
(1470, 0, 0, "Retrieve Yeh\'kinya Scroll.", 1, 1, 0, 0, 0, 0, '');
DELETE FROM `conditions` WHERE `SourceGroup` = 1470;
INSERT INTO `conditions` VALUES
(15, 1470, 0, 0, 0, 8, 0, 3528, 0, 0, 0, 0, 0, '', 'Show gossip if quest rewarded');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 8579;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 8579;
INSERT INTO `smart_scripts` VALUES
(8579, 0, 0, 0, 62, 0, 100, 0, 1470, 0, 0, 0, 85, 12998, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Yeh\'kinya - on gossip select - cast create Yehkinya Scroll');
