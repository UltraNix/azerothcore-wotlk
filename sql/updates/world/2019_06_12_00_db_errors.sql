DELETE FROM `waypoint_scripts` WHERE `id` IN (488, 489, 490, 1360541);
DELETE FROM `spell_script_names` WHERE `ScriptName` IN (
'spell_destroy_door_seal',
'spell_item_gnomish_universal_remote',
'spell_item_mind_amplify_dish',
'spell_netherspite_empowerment',
'spell_optic_link',
'spell_pal_seal_of_corruption',
'spell_pal_seal_of_vengeance',
'spell_pri_shadowfiend_shadowcrawl',
'spell_pri_shadowfiend_summon',
'spell_prince_taldaram_conjure_flame_sphere',
'spell_valanar_kinetic_bomb_summon');

UPDATE `gameobject_template` SET `ScriptName` = '' WHERE `ScriptName` = 'go_violet_hold_gate_lever';
UPDATE `creature_template` SET `ScriptName` = '' WHERE `ScriptName` IN (
'npc_curator_astral_flare',
'npc_cyclone',
'npc_fiendish_portal');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 19760;
UPDATE `creature_template` SET `AIName` = "" WHERE `entry` = 19760;
UPDATE `smart_scripts` SET `event_param2` = 5 WHERE `entryorguid` IN (21453, 21663) AND `id` = 1;
UPDATE `smart_scripts` SET `target_type` = 19, `target_param1` = 27662, `target_param2` = 5 WHERE `entryorguid` = 27661 AND `id` = 1;
