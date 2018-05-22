UPDATE `gameobject_template` SET `ScriptName` = "go_mimiron_summoning_pad" WHERE `entry` IN (194742, 194746, 194745, 194741, 194744, 194747, 194740, 194743, 194748);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 33836;

UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_mimiron_bomb_bot" WHERE `entry` = 33836;

DELETE FROM `spell_script_names` WHERE `spell_id` = 64623;
INSERT INTO `spell_script_names` VALUES
(64623, "spell_mimiron_frost_bomb_launch");
