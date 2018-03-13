-- Argent Champion
UPDATE `creature_template` SET `ScriptName`="npc_icc_argent_champion" WHERE `entry`=37928;
UPDATE `creature_template` SET `ScriptName`="npc_icc_ebon_champion" WHERE `entry`=37996;

-- Deathspeaker Zealot SAI
SET @ENTRY := 36808;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1000,10000,10000,11,69492,0,0,0,0,0,2,0,0,0,0,0,0,0,"Deathspeaker Zealot - In Combat - Cast 'Shadow Cleave'");

-- Deathspeaker Servant SAI
SET @ENTRY := 36805;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,3000,5000,11,69576,64,0,0,0,0,2,0,0,0,0,0,0,0,"Deathspeaker Servant - In Combat - Cast 'Chaos Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,3000,10000,15000,25000,11,69405,64,0,0,0,0,2,0,0,0,0,0,0,0,"Deathspeaker Servant - In Combat - Cast 'Consuming Shadows'");

-- Risen Deathspeaker Servant SAI
SET @ENTRY := 36844;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,3000,5000,11,69576,64,0,0,0,0,2,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - In Combat - Cast 'Chaos Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,3000,10000,15000,25000,11,69405,64,0,0,0,0,2,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - In Combat - Cast 'Consuming Shadows'"),
(@ENTRY,0,2,0,0,0,100,0,3000,10000,15000,25000,11,69404,64,0,0,0,0,2,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - In Combat - Cast 'Curse of Agony'"),
(@ENTRY,0,3,4,37,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - On Initialize - Set Visibility Off"),
(@ENTRY,0,4,5,61,0,100,0,0,0,0,0,18,774,0,0,0,0,0,1,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - On Initialize - Set Flags Not Attackable & Disable Movement & Immune To Players & Immune To NPC's"),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Risen Deathspeaker Servant - On Initialize - Run Script");

-- Valithria adds immunities
UPDATE `creature_template` SET `mechanic_immune_mask`=550189887 WHERE `entry` IN
(
	37863,
	38171,
	38727,
	38737, -- Supresser
	37934,
	38170,
	38723,
	38733-- Blistering Zombie
);

-- Rush spellscript
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_icc_rush";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71801, "spell_icc_rush");

-- Darkfallen Archmage SAI
SET @ENTRY := 37664;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,10000,15000,20000,11,70408,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Amplify Magic'"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,12000,15000,11,70407,64,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Blast Wave'"),
(@ENTRY,0,2,0,0,0,100,0,2000,4000,8000,10000,11,70409,64,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Fireball'"),
(@ENTRY,0,3,0,0,0,100,0,6000,10000,16000,20000,11,70410,64,0,0,0,0,17,14,29,1,0,0,0,0,"Darkfallen Archmage - In Combat - Cast 'Polymorph: Spider'"),
(@ENTRY,0,5,0,4,0,100,0,0,0,0,0,11,70299,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Archmage - On Aggro - Cast 'Siphon Essence'"),
(@ENTRY,0,6,0,6,0,100,0,0,0,0,0,104,0,0,0,0,0,0,20,201741,40,0,0,0,0,0,"Darkfallen Archmage - On Just Died - Set Gameobject Flag ");

-- Dark Nucleus hover
UPDATE `creature_template` SET `HoverHeight`=5 WHERE `entry`=38369;

-- Lady Deathwhisper intro
DELETE FROM `areatrigger_scripts` WHERE `ScriptName`="at_icc_lady_deathwhisper_entrance";
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5709, "at_icc_lady_deathwhisper_entrance");

-- Darkfallen Noble: Summon Vampiric Fiend spell
DELETE FROM `spell_dbc` WHERE `Id`=70647;
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `AttributesEx7`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectItemType1`, `EffectItemType2`, `EffectItemType3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES 
(70647, 0, 0, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 101, 0, 0, 0, 0, 9, 1, 0, -1, 0, 0, 28, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37901, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 'Summon Vampiric Fiend');

-- Darkfallen Noble SAI
SET @ENTRY := 37663;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,5000,5000,11,72960,64,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Noble - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,10000,15000,15000,15000,11,70645,64,0,0,0,0,6,0,0,0,0,0,0,0,"Darkfallen Noble - In Combat - Cast 'Chains of Shadow'"),
(@ENTRY,0,2,0,0,0,100,0,4000,6000,25000,30000,11,70647,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Noble - In Combat - Cast 'Summon Vampiric Fiend'");

-- Vampiric Fiend aura: Disease Cloud
DELETE FROM `creature_template_addon` WHERE `entry`=37901;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(37901, "41290");

-- Spelldifficulty data for Leeching Rot
DELETE FROM `spelldifficulty_dbc` WHERE `id`=70671;
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(70671, 70671, 70710);

-- Vampiric Fiend SAI
SET @ENTRY := 37901;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,5000,5000,6000,11,70671,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vampiric Fiend - In Combat - Cast 'Leeching Rot'");

-- Battle Standard
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_icc_summon_battle_standard";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(69810, "spell_icc_summon_battle_standard"),
(69811, "spell_icc_summon_battle_standard");

-- Remove path
SET @CGUID := 201501;
DELETE FROM `waypoint_data` WHERE `id`=@CGUID*10;
UPDATE `creature_addon` SET `path_id`=0 WHERE `guid`=@CGUID;
UPDATE `creature` SET `MovementType`=0 WHERE `guid`=@CGUID;
SET @CGUID := 201001;
DELETE FROM `waypoint_data` WHERE `id`=@CGUID*10;
UPDATE `creature_addon` SET `path_id`=0 WHERE `guid`=@CGUID;
UPDATE `creature` SET `MovementType`=0 WHERE `guid`=@CGUID;

-- Stinky path
SET @CGUID := 201240;
UPDATE `waypoint_data` SET `delay`=0 WHERE `id`=@CGUID*10 AND `point`=2;
DELETE FROM `waypoint_data` WHERE `id`=@CGUID*10 AND `point` IN (3, 4);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@CGUID*10, 3, 4267.564453, 3071.201172, 360.520386, 1500),
(@CGUID*10, 4, 4266.96, 3027.78, 360.52, 0);

-- Precious path
SET @CGUID := 201247;
UPDATE `waypoint_data` SET `delay`=0 WHERE `id`=@CGUID*10 AND `point`=2;
DELETE FROM `waypoint_data` WHERE `id`=@CGUID*10 AND `point` IN (3, 4);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@CGUID*10, 3, 4445.848145, 3068.747314, 360.519989, 1500),
(@CGUID*10, 4, 4444.54, 3029.85, 360.519, 0);

-- Additional mobs for 1st pack (Crimson Hall)
SET @CGUID = 210010;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 1;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@CGUID + 0, 37595, 631, 15, 1, 0, 1, 4517.617188, 2761.107422, 351.100800, 0.972470, 604800, 0, 0, 431360, 91600, 0, 0, 0, 0),
(@CGUID + 1, 37664, 631, 15, 1, 0, 1, 4518.400879, 2777.651367, 351.100800, 5.131159, 604800, 0, 0, 431360, 91600, 0, 0, 0, 0);
DELETE FROM `creature_formations` WHERE `leaderGUID`=201482;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `groupAI`, `dist`, `angle`) VALUES 
(201482, 201482, 3, 0, 0),
(201482, 201646, 3, 0, 0),
(201482, 201479, 3, 0, 0),
(201482, 201659, 3, 0, 0),
(201482, 210010, 3, 0, 0),
(201482, 210011, 3, 0, 0);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-201479, -201659, -201482, -201646) AND `source_type`=0;
