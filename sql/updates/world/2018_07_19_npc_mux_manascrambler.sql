-- Mux Manascrambler
DELETE FROM `gossip_menu_option` WHERE `menu_id`=7083;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `Option_Icon`, `Option_Text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(7083,0,0,"About that ghost revealer.  Did I happen to leave it here?  I seem to be missing it.",1,1,0,0,0,0,""),
(7083,1,0,"I seem to have misplaced the distiller, Mux.  Did I happen to leave it here?",1,1,0,0,0,0,"");
DELETE FROM `conditions` WHERE `SourceGroup` = 7083 AND `ElseGroup` IN (0,1);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 7083, 0, 0, 0, 2, 0, 22115, 1, 0, 1, 0, 0, '', 'Show gossip option if player does not have Extra-Dimensional Ghost Revealer'),
(15, 7083, 0, 0, 0, 8, 0, 8978, 0, 0, 0, 0, 0, '', 'Show gossip menu option if only player has \'Return to Mokvar\' quest Horde rewarded'),
(15, 7083, 0, 0, 1, 2, 0, 22115, 1, 0, 1, 0, 0, '', 'Show gossip option if player does not have Extra-Dimensional Ghost Revealer'),
(15, 7083, 0, 0, 1, 8, 0, 8977, 0, 0, 0, 0, 0, '', 'Show gossip menu option if only player has \'Return to Deliana\' quest Alliance rewarded');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=7083 AND `SourceEntry`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15,7083,1,0,0,9,0,8924,0,0,0,0,0,"","Show gossip option if quest 'Hunting for Ectoplasm' is taken"),
(15,7083,1,0,0,2,0,21946,1,1,1,0,0,"","Show gossip option if player does not have item 'Ectoplasmic Distiller'");
DELETE FROM `smart_scripts` WHERE `entryorguid` = 16014 AND `id` IN (0,1);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(16014, 0, 0, 1, 62, 0, 100, 0, 7083, 0, 0, 0, 11, 27754, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mux Manascrambler - On Gossip Option 0 Selected - Cast Create Extra-Dimensional Ghost Revealer'),
(16014, 0, 1, 0, 61, 0, 100, 512, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mux Manascrambler - On Gossip Option 0 Selected - Close Gossip');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 16014;
UPDATE `smart_scripts` SET `action_type`=85, `action_param2`=2 WHERE `entryorguid`=16014 AND `source_type`=0 AND `id`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=16014 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(16014,0,2,1,62,0,100,0,7083,1,0,0,85,27752,2,0,0,0,0,7,0,0,0,0,0,0,0,"Mux Manascrambler - On Gossip Option 1 Selected - Invoker Cast 'Create Ectoplasmic Distiller'");
