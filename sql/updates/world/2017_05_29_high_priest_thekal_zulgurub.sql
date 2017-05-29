DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_thekal_tiger_form";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(24169, "spell_thekal_tiger_form");
DELETE FROM `creature_text` WHERE `entry` = 14509 AND `groupid` = 2;
DELETE FROM `creature_text` WHERE `entry` IN(11347, 11348) AND `groupid` = 0;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`TextRange`,`comment`) VALUES
(14509, 2, 0, '%s dies.', 16, 0, 100, 0, 0, 16757, 1, 'EMOTE_DEATH_THEKAL_P1'),
(11347, 0, 0, '%s dies.', 16, 0, 100, 0, 0, 16757, 1, 'EMOTE_DEATH_LORKHAN_P1'),
(11348, 0, 0, '%s dies.', 16, 0, 100, 0, 0, 16757, 1, 'EMOTE_DEATH_ZATH_P1');