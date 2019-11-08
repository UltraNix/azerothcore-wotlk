DELETE FROM `conditions` WHERE `sourceEntry` = 64767;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 64767, 0, 0, 31, 0, 3, 33196, 0, 0, 0, 0, '', 'Spell Stormhammer target sif');

DELETE FROM `spell_script_names` WHERE `spell_id` = 64767;
INSERT INTO `spell_script_names` VALUES
(64767, "spell_thorim_stormhammer_sif");
