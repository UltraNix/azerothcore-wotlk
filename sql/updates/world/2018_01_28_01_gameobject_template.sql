SET @DOOR_ENTRY:= 101831;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @DOOR_ENTRY;

UPDATE `gameobject_template` SET `AIName` = "", `ScriptName` = "go_deadmines_lever_first_boss" WHERE `entry` = @DOOR_ENTRY;
