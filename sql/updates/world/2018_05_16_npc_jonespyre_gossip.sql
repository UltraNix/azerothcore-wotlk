-- Quintis Jonespyre --> Add Gossip Text
UPDATE `creature_template` SET `gossip_menu_id`=1922 WHERE `entry`=7879;

DELETE FROM `gossip_menu_option` WHERE `menu_id`=1922;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(1922,0,1,"I'd like to purchase more Tharlendris seeds.",3,128,0,0,0,0,"");
