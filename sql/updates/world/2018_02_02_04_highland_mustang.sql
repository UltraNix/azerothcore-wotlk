UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_highland_mustang" WHERE `entry` = 26472;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26472;
