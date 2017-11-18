UPDATE `creature_template` SET `unit_flags` = `unit_flags` & ~131072 WHERE `ScriptName` LIKE "%npc_training_dummy%";
