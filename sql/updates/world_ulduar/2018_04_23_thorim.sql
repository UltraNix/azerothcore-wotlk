SET @CGUID:= 136407;

DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID, 32879, 603, 3, 1, 28977, 0, 2124.54, -283.17, 419.767, 1.69297, 604800, 0, 0, 4183500, 425800, 0, 0, 0, 0);

UPDATE `spell_dbc` SET `effect1` = 6, `EffectImplicitTargetA1` = 1, `EffectApplyAuraName1` = 23, `EffectAmplitude1` = 1000, `EffectMiscValue1` = 1, `EffectTriggerSpell1` = 64972, `EffectDieSides1` = 1, `ProcChance` = 100 WHERE `id` = 64973;
