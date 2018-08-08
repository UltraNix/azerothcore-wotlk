DELETE FROM `npc_trainer` WHERE `entry` = 33639;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES
(33639, -201019, 0, 0, 0, 0),
(33639, -201018, 0, 0, 0, 0);

UPDATE `creature_template` SET `gossip_menu_id` = 10350, `unit_flags` = 33536, `trainer_type` = 2 WHERE `entry` = 33639;
