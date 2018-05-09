-- Ur'dan --> Add Gossip Text
UPDATE `creature_template` SET `gossip_menu_id`=5864 WHERE `entry`=14522;

DELETE FROM `gossip_menu` WHERE `entry`=5864;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(5864,7037);

DELETE FROM `gossip_menu_option` WHERE `menu_id`=5864;
INSERT INTO `gossip_menu_option` VALUES
(5864,0,1,"I wish to purchase from you.",3,128,0,0,0,0,"");
