UPDATE `smart_scripts` SET `event_param1` = 9528 WHERE `entryorguid` = 27425 AND `id` = 0;
UPDATE `smart_scripts` SET `target_type` = 7 WHERE `entryorguid` = 27425 AND `id` IN (1,2);
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 27414;
DELETE FROM `gossip_menu_option` WHERE `menu_id` = 21251 AND `id` = 1;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(21251, 1, 0, 'Yes, I am ready to travel to Venture Bay!', 1, 1, 0, 0, 0, 0, NULL);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 27414;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(27414, 0, 0, 1, 62, 0, 100, 0, 21251, 1, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Gordun - On Gossip Option 1 Selected - Close Gossip'),
(27414, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 85, 48622, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Gordun - On Gossip Option 1 Selected - Invoker Cast \'Alliance Log Ride 01 Begin\''),
(27414, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 85, 48621, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Gordun - On Gossip Option 1 Selected - Invoker Cast \'Log Ride Alliance 00\'');
