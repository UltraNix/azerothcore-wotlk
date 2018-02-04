-- Ahn'kahar Watcher normal mode level correction
UPDATE `creature_template` SET `minlevel`=73, `maxlevel`=73 WHERE `entry`=31104;

-- Ahn'kahar Web Winder
DELETE FROM `smart_scripts` WHERE `entryorguid`=30276 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_ahnkahar_web_winder" WHERE `entry`=30276;
DELETE FROM `spelldifficulty_dbc` WHERE `id`=56640;
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(56640, 56640, 59106);