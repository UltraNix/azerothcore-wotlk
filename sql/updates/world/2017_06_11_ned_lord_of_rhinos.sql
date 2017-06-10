UPDATE creature_template SET AIName="", ScriptName="npc_nedar" WHERE entry=25801;
UPDATE creature_template SET AIName="", ScriptName="npc_lunchbox" WHERE entry=25968;
DELETE FROM `smart_scripts` WHERE `entryorguid`=25801 AND `source_type`=0; 