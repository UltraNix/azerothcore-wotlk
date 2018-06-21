UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` IN (188151, 188152, 188153, 188154);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (188151, 188152, 188153, 188154);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(188151, 1, 0, 0, 62, 0, 100, 0, 9273, 0, 0, 0, 80, 18815100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ice Stone - On gossip option select - Run script'),
(188152, 1, 0, 0, 62, 0, 100, 0, 9274, 0, 0, 0, 80, 18815200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ice Stone - On gossip option select - Run script'),
(188153, 1, 0, 0, 62, 0, 100, 0, 9275, 0, 0, 0, 80, 18815300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ice Stone - On gossip option select - Run script'),
(188154, 1, 0, 0, 62, 0, 100, 0, 9276, 0, 0, 0, 80, 18815400, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ice Stone - On gossip option select - Run script');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (18815100,18815200,18815300,18815400);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(18815100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Actionlist - On action 0 - Close gossip'),
(18815100, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 26216, 3, 120000, 0, 0, 0, 8, 0, 0, 0, -153.333, 1142.61, 41.4977, 0.898327, 'Actionlist - On action 1 - Summon Templar'),
(18815200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Actionlist - On action 0 - Close gossip'),
(18815200, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 26216, 3, 120000, 0, 0, 0, 8, 0, 0, 0, -349.365, 1135.74, 40.7126, 2.44833, 'Actionlist - On action 1 - Summon Templar'),
(18815300, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Actionlist - On action 0 - Close gossip'),
(18815300, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 26216, 3, 120000, 0, 0, 0, 8, 0, 0, 0, -133.914, 1199.37, 41.5145, 4.36586, 'Actionlist - On action 1 - Summon Templar'),
(18815400, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Actionlist - On action 0 - Close gossip'),
(18815400, 9, 1, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 26216, 3, 120000, 0, 0, 0, 8, 0, 0, 0, -355.553, 1204.58, 40.3496, 1.81568, 'Actionlist - On action 1 - Summon Templar');
DELETE FROM `gameobject` WHERE `guid` IN  (200875,200880,200882,200884,200881,200879,200883,200876,200874);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES 
(200875, 188151, 530, 1, 1, -155.708, 1136.65, 41.5227, 1.07635, 0, 0, 0.512571, 0.858645, 100, 0, 1, 0),
(200880, 188152, 530, 1, 1, -349.997, 1132.18, 40.645, 0.0623619, 0, 0, 0.0311759, 0.999514, 100, 0, 1, 0),
(200882, 188153, 530, 1, 1, -133.263, 1204.24, 41.6632, 3.20002, 0, 0, 0.999573, -0.0292117, 100, 0, 1, 0),
(200884, 188154, 530, 1, 1, -355.812, 1209.86, 39.809, 1.975, 0, 0, 0.657948, -0.753063, 100, 0, 1, 0),
(200881, 188156, 530, 1, 1, -133.263, 1204.24, 41.6632, 3.20002, 0, 0, 0.999573, -0.0292117, 300, 0, 1, 0),
(200879, 188156, 530, 1, 1, -349.997, 1132.78, 40.645, 0.0623619, 0, 0, 0.0311759, 0.999514, 300, 0, 1, 0),
(200883, 188156, 530, 1, 1, -355.812, 1209.86, 39.809, 1.975, 0, 0, 0.657948, -0.753063, 300, 0, 1, 0),
(200876, 188157, 530, 1, 1, -350.997, 1130.78, 25.645, 2.66284, 0, 0, 0.971486, 0.237097, 300, 0, 1, 0),
(200874, 188156, 530, 1, 1, -155.708, 1136.65, 41.5227, 1.07635, 0, 0, 0.512571, 0.858645, 300, 0, 1, 0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN  (9273,9274,9275,9276);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
(9273, 0, 0, 'Lay your hand on the Ice Stone.', 1, 1, 0, 0, 0, 0, ''),
(9274, 0, 0, 'Lay your hand on the Ice Stone.', 1, 1, 0, 0, 0, 0, ''),
(9275, 0, 0, 'Lay your hand on the Ice Stone.', 1, 1, 0, 0, 0, 0, ''),
(9276, 0, 0, 'Lay your hand on the Ice Stone.', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `conditions` WHERE `SourceGroup` IN (9273,9274,9275,9276);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 9273, 0, 0, 1, 9, 0, 11954, 0, 0, 0, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9274, 0, 0, 1, 9, 0, 11954, 0, 0, 0, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9275, 0, 0, 1, 9, 0, 11954, 0, 0, 0, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9276, 0, 0, 1, 9, 0, 11954, 0, 0, 0, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9273, 0, 0, 1, 29, 0, 26216, 20, 0, 1, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9274, 0, 0, 1, 29, 0, 26216, 20, 0, 1, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9275, 0, 0, 1, 29, 0, 26216, 20, 0, 1, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/'),
(15, 9276, 0, 0, 1, 29, 0, 26216, 20, 0, 1, 0, 0, '', 'Ice Stone - For Gossip player must have Striking back /Hellfire/');
select * FROM `conditions` WHERE `SourceGroup` IN (9273,9274,9275,9276);
select * from conditions where conditiontypeorreference = 31 and negativecondition = 1;
DELETE FROM `game_event_gameobject` WHERE `guid` IN (200875,200880,200882,200884);
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(1, 200875),
(1, 200880),
(1, 200882),
(1, 200884);

DELETE FROM `creature` WHERE `guid` = 245633;
