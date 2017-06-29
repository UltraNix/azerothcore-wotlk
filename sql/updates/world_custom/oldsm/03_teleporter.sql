SET @TELEPORT := 400007;
SET @CGUID := 400007;

DELETE FROM `creature_template` WHERE `entry` = @TELEPORT;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(@TELEPORT, 0, 0, 0, 0, 0, 2512, 2513, 0, 0, 'Old Scarlet Monastery Teleporter', NULL, NULL, 65006, 80, 80, 0, 35, 1, 1, 1.14286, 1, 1, 30, 42, 0, 44, 1, 2000, 0, 8, 33536, 2048, 0, 0, 0, 0, 0, 0, 26, 38, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1.05, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, '');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 65006;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(65006, 0, 0, 'I want to enter Old Scarlet Monastery.', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` = @TELEPORT;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@TELEPORT, 0, 0, 0, 62, 0, 100, 0, 65006, 0, 0, 0, 62, 44, 0, 0, 0, 0, 0, 7, 0, 0, 0, 77, -1, 18.68, 0.05, 'Scarlet Teleporter - On Gossip Option 0 Selected - Teleport');

DELETE FROM `creature` WHERE `id` = @TELEPORT;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID, @TELEPORT, 0, 1, 1, 0, 1, 2926.5149, -737.7026, 153.9836, 1.130361, 604800, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `game_event_creature` WHERE `eventEntry` = 88;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(88, @CGUID);
