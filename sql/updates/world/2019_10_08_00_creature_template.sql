DELETE FROM `smart_scripts` WHERE `entryorguid` = 24567 AND `source_type` = 0;
UPDATE `creature_template` SET AIName = '', ScriptName = 'npc_den_vermin' WHERE entry = 24567;
