SET @OVERLOAD_SPELL:= 61876;

UPDATE `creature_template` SET `ScriptName` = "npc_overload_ball_assembly", `flags_extra` = 128 WHERE `entry` IN (32866, 33690);
DELETE FROM `spell_script_names` WHERE `spell_id` = @OVERLOAD_SPELL;
INSERT INTO `spell_script_names` VALUES
(@OVERLOAD_SPELL, "spell_summon_overload_ball");
