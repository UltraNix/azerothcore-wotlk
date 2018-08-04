DELETE FROM `gossip_menu_option` WHERE `menu_id` = 10630;
INSERT INTO `gossip_menu_option` VALUES
(10630, 0, 0, 'I\'ve lost my Totem of the Earthen Ring.', 1, 1, 0, 0, 0, 0, '');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 35068;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 35068;
INSERT INTO `smart_scripts` VALUES
(35068, 0, 0, 0, 62, 0, 100, 0, 10630, 0, 0, 0, 85, 66747, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Gotura Fourwinds - On Gossip Select - Invoker Cast Relic of the Earthen Ring');
DELETE FROM `conditions` WHERE `SourceGroup` = 10630;
INSERT INTO `conditions` VALUES
(15, 10630, 0, 0, 0, 9, 0, 14100, 0, 0, 0, 0, 0, '', 'Gossip Option requires quest');
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` = 35068;
