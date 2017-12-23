--
SET @GO_FATHER_FLAME:= 175245;
SET @NPC_ROOKERY_GUARDIAN:= 10258;
SET @NPC_ROOKERY_HATCHER:= 10683;

UPDATE `gameobject_template` SET `ScriptName` = "go_father_flame_event_ubrs" WHERE `entry` = @GO_FATHER_FLAME;
UPDATE `creature_template` SET `ScriptName` = "npc_rookery_guardian" WHERE `entry` = @NPC_ROOKERY_GUARDIAN;
UPDATE `creature_template` SET `AIName` ="", `ScriptName` = "npc_rookery_hatcher" WHERE `entry` = @NPC_ROOKERY_HATCHER;
