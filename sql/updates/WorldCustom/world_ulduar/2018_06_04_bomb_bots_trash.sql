UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_boomer_xp500_ulduar" WHERE `entry` = 34192;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 34192;
