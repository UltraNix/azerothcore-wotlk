-- Festergut Gastric Bloat
DELETE FROM `spell_proc_event` WHERE `entry`=72214;
INSERT INTO `spell_proc_event` (`entry`, `Cooldown`) VALUES
(72214, 14000);
-- Rotface
DELETE FROM `creature_text` WHERE `entry`=36627 AND `groupid`=4;
DELETE FROM `creature_text` WHERE `entry`=36899;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`TextRange`,`comment`) VALUES
(36899,0,0,'%s grows more unstable!',16,0,0,0,0,0,0,'Big Ooze - EMOTE_UNSTABLE_2'),
(36899,1,0,'%s is growing volatile!',16,0,0,0,0,0,0,'Big Ooze - EMOTE_UNSTABLE_3'),
(36899,2,0,'%s can barely maintain its form!',16,0,0,0,0,0,0,'Big Ooze - EMOTE_UNSTABLE_4'),
(36899,3,0,'|TInterface\\Icons\\spell_shadow_unstableaffliction_2.blp:16|t%s begins to cast |cFFFF0000Unstable Ooze Explosion!|r',41,0,0,0,0,0,0,'Big Ooze - EMOTE_UNSTABLE_EXPLOSION');
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_rotface_vile_gas_trigger');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(72285, 'spell_rotface_vile_gas_trigger'),
(72288, 'spell_rotface_vile_gas_trigger');
