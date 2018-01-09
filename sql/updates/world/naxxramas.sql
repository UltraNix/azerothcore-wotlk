DELETE FROM `smart_scripts` WHERE `entryorguid`=16168 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_stoneskin_gargoyle" WHERE `entry`=16168;
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_gargoyle_stoneskin";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(28995, "spell_gargoyle_stoneskin"),
(54722, "spell_gargoyle_stoneskin");