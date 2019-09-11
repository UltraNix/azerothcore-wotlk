UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_guardian_pet" WHERE `entry` IN (28017, 38391, 38392);
UPDATE `spell_proc_event` SET `Cooldown`=4000 WHERE `entry` IN (49027, 49542, 49543);
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE "spell_bloodworms";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49027, "spell_bloodworms"),
(49542, "spell_bloodworms"),
(49543, "spell_bloodworms");
