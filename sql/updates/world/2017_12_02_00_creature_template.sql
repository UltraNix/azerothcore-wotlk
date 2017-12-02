UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_sarathstra_dragonblight" WHERE `entry` = 26858;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26858;
DELETE FROM `creature` WHERE `guid` = 112401;
