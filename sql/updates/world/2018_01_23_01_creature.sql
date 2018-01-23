UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_overlord_agmar_dragonblight" WHERE `entry` = 26379;
DELETE FROM `waypoints` where `entry` = 26379;
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_roanauk_icemist" WHERE `entry` = 26810;
UPDATE `gossip_menu_option` SET `id` = 1 WHERE `menu_id` = 9462;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (26379, 26810);
