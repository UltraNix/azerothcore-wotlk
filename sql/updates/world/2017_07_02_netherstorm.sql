DELETE FROM `smart_scripts` WHERE `entryorguid`=20483 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_naberius" WHERE `entry`=20483;
