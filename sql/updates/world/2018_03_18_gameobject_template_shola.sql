UPDATE `gameobject_template` SET `AIName` = "", `ScriptName` = "go_raised_mud_scholazar_river" WHERE `entry` = 190779;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 190779;

DELETE FROM `pool_template` WHERE `entry` = 50000;
DELETE FROM `pool_gameobject` WHERE `pool_entry` = 50000;
