-- Fate, Up Against Your Will

/* Stormwind, Orgrimmar, Undercity, Durotar, and Tirisfal Glades */
DELETE FROM `spell_area` WHERE `spell` IN (60877,60815);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60877, 1519, 13347, 13369, 0, 1101, 2, 1, 74, 11),
(60815, 85, 12499, 13377, 0, 1101, 2, 1, 64, 11),
(60815, 14, 12499, 13377, 0, 1101, 2, 1, 64, 11),
(60815, 1519, 12499, 13377, 0, 1101, 2, 1, 64, 11),
(60815, 1497, 12499, 13377, 0, 1101, 2, 1, 64, 11),
(60815, 1637, 12499, 13377, 0, 1101, 2, 1, 64, 11);

/* Update Phase masks in Stormwind Keep */
UPDATE `creature` SET `phaseMask`=129 WHERE `guid`=10495 LIMIT 1; -- King Varian
UPDATE `creature` SET `phaseMask`=129 WHERE `id` IN (1756,1976,68); -- Guards

/* Spawns */
SET @JAINA_IN_STORMWIND := 32346;
SET @JAINA_IN_ORGRIMMAR := 32364;
SET @THRALL := 32363;
SET @SYLVANAS := 32365;
SET @GUARDS := 32367;
SET @PORTAL_STORMWIND := 31640;

SET @CGUID := 302162;

DELETE FROM `creature` WHERE `id` IN (@JAINA_IN_STORMWIND,@JAINA_IN_ORGRIMMAR,@THRALL,@SYLVANAS,@GUARDS,@PORTAL_STORMWIND);
INSERT INTO `creature` (`guid`,`id`, `map`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES 
(@CGUID, @JAINA_IN_STORMWIND, 0, 128, -8443.36, 332.2, 122.579, 1.570795),
(@CGUID+1, @JAINA_IN_ORGRIMMAR, 1, 128, 1921.699951, -4147.27, 40.625, 1.571),
(@CGUID+2, @PORTAL_STORMWIND, 1, 192, 1921.699951, -4147.27, 40.625, 1.571),
(@CGUID+3, @THRALL, 1, 128, 1920.57, -4136.53, 43.221, -1.570795),
(@CGUID+4, @SYLVANAS, 1, 128, 1920, -4129.52, 43.221, -1.570795),
(@CGUID+5, @GUARDS, 1, 128, 1930.631, -4139.943, 40.625, 3.9269875),
(@CGUID+6, @GUARDS, 1, 128, 1911.631, -4157.943, 40.625, 0.7853975),
(@CGUID+7, @GUARDS, 1, 128, 1930.631, -4157.943, 40.625, -2.3561925),
(@CGUID+8, @GUARDS, 1, 128, 1911.631, -4139.943, 40.625, 2.3561925);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (@JAINA_IN_STORMWIND,@JAINA_IN_ORGRIMMAR,@SYLVANAS,@GUARDS,@PORTAL_STORMWIND);
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_thrall_pre_battle_undercity' WHERE `entry`=@THRALL;

UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80 WHERE `entry`=@GUARDS;
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|33554432 WHERE `entry`=@PORTAL_STORMWIND;

-- Jaina's Teleport
UPDATE `creature_template` SET `gossip_menu_id`=10189 WHERE `entry`=@JAINA_IN_STORMWIND LIMIT 1;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=@JAINA_IN_STORMWIND LIMIT 1;

DELETE FROM `gossip_menu_option` WHERE `menu_id`=10189;
INSERT INTO `gossip_menu_option` (`menu_id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES 
(10189, 0, "Lady Proudmoore, I am ready to go to Orgrimmar.  Please open a portal.", 1, 1);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=10189;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`,`ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 10189, 0, 0, 0, 28, 0, 13369, 0, 0, 0, 0, '', 'Show gossip if player has q: Fate, Up Against Your Will');

DELETE FROM `creature_template_addon` WHERE `entry`=@JAINA_IN_STORMWIND;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES 
(@JAINA_IN_STORMWIND, '60878');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@JAINA_IN_STORMWIND,@JAINA_IN_STORMWIND*100);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@JAINA_IN_STORMWIND, 0, 0, 0, 62, 0, 100, 0, 10189, 0, 0, 0, 80, @JAINA_IN_STORMWIND*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - On gossip option select run script'),

(@JAINA_IN_STORMWIND*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - Turn off Gossip & Questgiver flags'),
(@JAINA_IN_STORMWIND*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - Say text 0'),
(@JAINA_IN_STORMWIND*100, 9, 2, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 11, 60904, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - Cast spell 60904'),
(@JAINA_IN_STORMWIND*100, 9, 3, 0, 0, 0, 100, 0, 6500, 6500, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - Say text 1'),
(@JAINA_IN_STORMWIND*100, 9, 4, 0, 0, 0, 100, 0, 4500, 4500, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - Turn on Gossip & Questgiver flags');

DELETE FROM `spell_script_names` WHERE `spell_id`=60904;
INSERT INTO `spell_script_names` VALUES
(60904,'spell_portal_to_orgrimmar');

-- Teleports
DELETE FROM `spell_scripts` WHERE `id`=60900;
INSERT INTO `spell_scripts` VALUES
(60900,0,0,15,60901,0,0,0,0,0,0);

DELETE FROM `spell_target_position` WHERE `id`=60901;
INSERT INTO `spell_target_position` VALUES
(60901,0,1,1921.130615,-4148.943359,40.637367,1.570795);

/* Text */
DELETE FROM `creature_text` WHERE `entry`=32346;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(32346, 0, 0, 'Do not do anything that would incite the Horde, $N. The Warchief has agreed to see us on good faith.', 12, 0, 100, 1, 0, 16124, 'Jaina Proudmoore'),
(32346, 1, 0, 'Let\'s go.', 12, 0, 100, 1, 0, 16125, 'Jaina Proudmoore');

-- Areatrigger in Orgrimmar
DELETE FROM `areatrigger_scripts` WHERE `entry`=5311;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES 
(5311, 'AreaTrigger_at_orgrimmar');

-- /* EVENT */ --
-- Sai for Jaina
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@JAINA_IN_ORGRIMMAR,@JAINA_IN_ORGRIMMAR*100);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@JAINA_IN_ORGRIMMAR, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on reset - set walk'),
(@JAINA_IN_ORGRIMMAR, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on respawn - set visibility off'),
(@JAINA_IN_ORGRIMMAR, 0, 2, 3, 38, 0, 100, 0, 0, 1, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on data 1 set - set visibility on'),
(@JAINA_IN_ORGRIMMAR, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 52096, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on data 1 set - Cast spell Air Revenant Entrance'),
(@JAINA_IN_ORGRIMMAR, 0, 4, 0, 38, 0, 100, 0, 0, 2, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1921, -4139.4, 40.6, 0, 'Jaina - on data 2 set - go to pos 1'),
(@JAINA_IN_ORGRIMMAR, 0, 5, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, @JAINA_IN_ORGRIMMAR*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on pos 1 - run script'),
(@JAINA_IN_ORGRIMMAR, 0, 6, 0, 38, 0, 100, 0, 0, 3, 0, 0, 69, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1921.699951, -4147.27, 40.625, 0, 'Jaina - on data 3 set - go to pos 2'),
(@JAINA_IN_ORGRIMMAR, 0, 7, 8, 34, 0, 100, 0, 0, 2, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @PORTAL_STORMWIND, 10, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on portal'),
(@JAINA_IN_ORGRIMMAR, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @THRALL, 40, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on Thrall'),
(@JAINA_IN_ORGRIMMAR, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 45, 0, 2, 0, 0, 0, 0, 19, @SYLVANAS, 40, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set data 2 on Sylvanas'),
(@JAINA_IN_ORGRIMMAR, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on pos 2 - set visibility off'),

(@JAINA_IN_ORGRIMMAR*100, 9, 0, 0, 1, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Jaina - on run script - say 1'),
(@JAINA_IN_ORGRIMMAR*100, 9, 1, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Jaina - on run script - say 3'),
(@JAINA_IN_ORGRIMMAR*100, 9, 2, 0, 1, 0, 100, 0, 5000, 5000, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, @SYLVANAS, 30, 0, 0, 0, 0, 0, 'Jaina - on run script - set data 1 on Sylvanas');

-- Sai from Sylvanas
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SYLVANAS,@SYLVANAS*100);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@SYLVANAS, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on reset - set walk'),
(@SYLVANAS, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 90, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on reset - set kneel'),
(@SYLVANAS, 0, 2, 3, 38, 0, 100, 0, 0, 1, 0, 0, 91, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on data 1 set - stand up'),
(@SYLVANAS, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.57019, -4136.34131, 40.559574, 0, 'Sylvanas - on data 1 set - go to pos 1'),
(@SYLVANAS, 0, 4, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, @SYLVANAS*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on pos 1 - run script'),
(@SYLVANAS, 0, 5, 0, 38, 0, 100, 0, 0, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on data 2 set - evade'),

(@SYLVANAS*100, 9, 0, 0, 1, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on run script - say 1'),
(@SYLVANAS*100, 9, 1, 0, 1, 0, 100, 0, 12000, 12000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas - on run script - say 2'),
(@SYLVANAS*100, 9, 2, 0, 1, 0, 100, 0, 16000, 16000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 4'),
(@SYLVANAS*100, 9, 3, 0, 1, 0, 100, 0, 6000, 6000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 5'),
(@SYLVANAS*100, 9, 4, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 6'),
(@SYLVANAS*100, 9, 5, 0, 1, 0, 100, 0, 10000, 10000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 19, @THRALL, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Thrall say 7'),
(@SYLVANAS*100, 9, 6, 0, 1, 0, 100, 0, 6000, 6000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, @JAINA_IN_ORGRIMMAR, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 2'),
(@SYLVANAS*100, 9, 7, 0, 1, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @JAINA_IN_ORGRIMMAR, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 3'),
(@SYLVANAS*100, 9, 8, 0, 1, 0, 100, 0, 14000, 14000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, @JAINA_IN_ORGRIMMAR, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 4'),
(@SYLVANAS*100, 9, 9, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @JAINA_IN_ORGRIMMAR, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - Jaina say 5'),
(@SYLVANAS*100, 9, 10, 0, 1, 0, 100, 0, 8000, 8000, 0, 0, 45, 0, 3, 0, 0, 0, 0, 19, @JAINA_IN_ORGRIMMAR, 10, 0, 0, 0, 0, 0, 'Sylvanas - on run script - set data 3 on Jaina');

-- Sai for portal
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@PORTAL_STORMWIND);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@PORTAL_STORMWIND, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Portal - on reset - set visibility off'),
(@PORTAL_STORMWIND, 0, 1, 0, 38, 0, 100, 0, 0, 1, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Portal - on data 1 set - set visibility on'),
(@PORTAL_STORMWIND, 0, 2, 0, 38, 0, 100, 0, 0, 2, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Portal - on data 2 set - set visibility on');

-- Sai for guards
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-(@CGUID+5),-(@CGUID+6),-(@CGUID+7),-(@CGUID+8));
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(-(@CGUID+5), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1923.506, -4146.693, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+5), 0, 1, 0, 34, 0, 100, 0, 0, 1, 0, 0, 45, 0, 1, 0, 0, 0, 0, 19, @THRALL, 30, 0, 0, 0, 0, 0, 'Kor\'kron Elite - On pos 1 - set data 1 on Thrall'),
(-(@CGUID+6), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.756, -4151.193, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+7), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1923.506, -4151.193, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP'),
(-(@CGUID+8), 0, 0, 0, 38, 0, 100, 0, 0, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1918.756, -4146.693, 40.625, 0, 'Kor\'kron Elite - On data set, Start WP');

-- Texts
DELETE FROM `creature_text` WHERE `entry` IN (@THRALL,@SYLVANAS,@JAINA_IN_ORGRIMMAR);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@THRALL, 0, 0, 'Kor\'kron, stand down!', 14, 0, 100, 5, 0, 16222, 'Thrall - WG_Thrall_HORIntro01'),
(@THRALL, 1, 0, 'Jaina...', 12, 0, 100, 0, 0, 16223, 'Thrall - WG_Thrall_HORIntro02'),
(@THRALL, 2, 0, 'Jaina, what happened at the Wrathgate. It was a betrayal from within...', 12, 0, 100, 378, 0, 16224, 'Thrall - WG_Thrall_HORIntro03'),
(@THRALL, 3, 0, 'The Horde has lost the Undercity.', 12, 0, 100, 1, 0, 16225, 'Thrall - WG_Thrall_HORIntro04'),
(@THRALL, 4, 0, 'We now prepare to lay siege to the city and bring in the perpetrators of the unforgivable crime to justice.', 12, 0, 100, 378, 0, 16226, 'Thrall - WG_Thrall_HORIntro05'),
(@THRALL, 5, 0, 'Know this, Jaina: War with the Alliance is not in our best interests. If we are forced into a conflict, the Lich King will destroy our divided forces in Northrend.', 12, 0, 100, 378, 0, 16227, 'Thrall - WG_Thrall_HORIntro06'),
(@THRALL, 6, 0, 'We will make this right, Jaina. Tell your king all that you have learned here.', 12, 0, 100, 378, 0, 16228, 'Thrall - WG_Thrall_HORIntro07'),
(@THRALL, 7, 0, 'Kor\'kron, prepare transport to the Undercity.', 12, 0, 100, 0, 0, 16229, 'Thrall - WG_Thrall_HORIntro08'),
(@SYLVANAS, 0, 0, 'Lady Proudmoore, the Warchief speaks the truth. This subterfuge was set in motion by Varimathras and Grand Apothecary Putress. It was not the Horde\'s doing.', 12, 0, 100, 5, 0, 16315, 'Sylvanas - WG_Sylvanas_HORIntro01'),
(@SYLVANAS, 1, 0, 'As the combined Horde and Alliance forces begain their assault upon the Wrathgate, an uprising broke out in the Undercity. Varimathras and hordes of his demonic bretheren attacked. Hundreds of my people were slain in the coup. I barely managed to escape with my life.', 12, 0, 100, 5, 0, 16316, 'Sylvanas - WG_Sylvanas_HORIntro02'),
(@JAINA_IN_ORGRIMMAR, 0, 0, 'Thrall, what has happened? The King is preparing for war...', 12, 0, 100, 1, 0, 16129, 'Jaina - WG_Jaina_HORIntro01'),
(@JAINA_IN_ORGRIMMAR, 1, 0, 'I will deliver this information to King Wrynn, Thrall, but...', 12, 0, 100, 378, 0, 16130, 'Jaina - WG_Jaina_HORIntro02'),
(@JAINA_IN_ORGRIMMAR, 2, 0, 'Bolvar was like a brother to him. In the King\'s absence, Bolvar kept the Alliance united. He found strength for our people in our darkest hours. He watched over Anduin, raising him as his own.', 12, 0, 100, 378, 0, 16131, 'Jaina - WG_Jaina_HORIntro03'),
(@JAINA_IN_ORGRIMMAR, 3, 0, ' I fear that the rage will consume him, Thrall. I remain hopeful that reason will prevail, but we must prepare for the worst... for war.', 12, 0, 100, 378, 0, 16132, 'Jaina - WG_Jaina_HORIntro04'),
(@JAINA_IN_ORGRIMMAR, 4, 0, 'Farewell, Warchief. I pray that the next time we meet it will be as allies.', 12, 0, 100, 2, 0, 16133, 'Jaina - WG_Jaina_HORIntro05');
