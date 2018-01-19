-- Plague Scientist
DELETE FROM `smart_scripts` WHERE `entryorguid`=37023 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_plague_scientist" WHERE `entry`=37023;
-- Deathspeaker High Priest
UPDATE `creature_onkill_reputation` SET `RewOnKillRepValue1`=50 WHERE `creature_id`=36829;
-- Web Wrap
DELETE FROM `smart_scripts` WHERE `entryorguid`=38028 AND `source_type`=0;
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|32, `AIName`="", `ScriptName`="npc_icc_web_wrap" WHERE `entry`=38028;
-- ICC Buff 10%->30%
UPDATE `spell_area` SET `spell`=73822 WHERE `spell`=73818;
UPDATE `spell_area` SET `spell`=73828 WHERE `spell`=73824;