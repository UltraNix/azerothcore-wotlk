UPDATE `creature_template` SET `dmg_multiplier` = '26' WHERE `creature_template`.`entry` = 34016; -- Tempest Warder damage correction
UPDATE `creature_template` SET `dmg_multiplier` = '95' WHERE `creature_template`.`entry` = 33994; -- Emalon damage correction

UPDATE `creature_template` SET `spell4` = '67372', `spell5` = '67393', `spell6` = '64660' WHERE `creature_template`.`entry` = 33062;
UPDATE `creature_template` SET `spell4` = '67372', `spell5` = '67393', `spell6` = '64660' WHERE `creature_template`.`entry` = 34045;

UPDATE `script_waypoint` SET `location_x` = '379.218',
`location_y` = '10.4420' WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` =1;

UPDATE `script_waypoint` SET `location_x` = '378.748',
`location_y` = '-35.8312' WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` =2;

UPDATE `script_waypoint` SET `location_x` = '278.980',
`location_y` = '-128.7513',
`location_z` = '409.804' WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` =3;

UPDATE `script_waypoint` SET `location_x` = '168.871',
`location_y` = '-35.5354',
`location_z` = '409.804' WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` =4;

UPDATE `script_waypoint` SET `location_x` = '279.052',
`location_y` = '62.4145',
`location_z` = '409.804' WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` =5;

DELETE FROM `script_waypoint` WHERE `script_waypoint`.`entry` = 33369 AND `script_waypoint`.`pointid` = 6;


DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 33387;
DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 34275;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_ward_of_life' WHERE `creature_template`.`entry` = 33387;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_ward_of_life' WHERE `creature_template`.`entry` = 34275;

UPDATE `creature_template` SET `flags_extra` = '130' WHERE `creature_template`.`entry` = 33282;

UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 32904;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 33157;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 32877;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 33155;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 32878;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 33156;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 32876;
UPDATE `creature_template` SET `mechanic_immune_mask` = '0' WHERE `creature_template`.`entry` = 33158;

UPDATE `creature` SET `spawndist` = '0', `MovementType` = '0', `orientation` = '3.09' WHERE `creature`.`guid` = 136610;
UPDATE `creature` SET `orientation` = '2.68494' WHERE `creature`.`guid` = 136602;

SET @GUID := (SELECT MAX(guid) from creature) +100; 
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@GUID+1, 34190, 603, 3, 1, 0, 1, 1683.53, -10.1463, 427.57, 3.75, 604800, 0, 0, 0, 0, 0, 0, 0, 0),
(@GUID+2, 34190, 603, 3, 1, 0, 1, 1550.02, -10.8806, 420.96, 5.35, 604800, 0, 0, 0, 0, 0, 0, 0, 0),
(@GUID+3, 34198, 603, 3, 1, 0, 1, 1675.93, -10.4150, 427.31, 3.75, 604800, 0, 0, 0, 0, 0, 0, 0, 0),
(@GUID+4, 34198, 603, 3, 1, 0, 1, 1553.17, -15.3195, 420.96, 3.93, 604800, 0, 0, 0, 0, 0, 0, 0, 0),
(@GUID+5, 34199, 603, 3, 1, 0, 1, 1679.86, -17.8350, 427.31, 3.43, 604800, 0, 0, 0, 0, 0, 0, 0, 0),
(@GUID+6, 34199, 603, 3, 1, 0, 1, 1544.61, -19.9128, 420.96, 3.09, 604800, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `mechanic_immune_mask` = '617298779' WHERE `creature_template`.`entry` = 32916;
UPDATE `creature_template` SET `Health_mod` = '28' WHERE `creature_template`.`entry` = 34005;

DELETE FROM spell_script_names WHERE spell_id IN(67387);
INSERT INTO spell_script_names VALUES (67387, 'spell_vehicle_chopper_grab_pyrite');