DELETE FROM `smart_scripts` WHERE `entryorguid`=23960 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_dragonflayer_runecaster" WHERE `entry`=23960;