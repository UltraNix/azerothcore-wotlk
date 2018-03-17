DELETE FROM `smart_scripts` WHERE `entryorguid`=24713 AND `source_type`=0 AND `id`>1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(24713, 0, 2, 3, 62, 0, 100, 0, 9335, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '"Crowleg" Dan - On Gossip Option Select - Close Gossip'),
(24713, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, '"Crowleg" Dan - On Gossip Option Select - Start Attack');

DELETE FROM `gossip_menu_option` WHERE `menu_id`=9335;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`,  `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
(9335, 0, 0, 'Ummm... the frog says you''re a traitor, "matey."', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9335;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 9335, 0, 0, 0, 9, 0, 11479, 0, 0, 0, 0, 0, '', 'Crowleg" Dan - Only show Gossip if player is on quest');
