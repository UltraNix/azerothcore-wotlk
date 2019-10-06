SET @ENTRY := 11859;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_warl_doomguard" WHERE `entry`=@ENTRY;
