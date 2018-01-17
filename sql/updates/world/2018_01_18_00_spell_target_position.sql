UPDATE `spell_target_position` SET `target_map` = 533, `target_position_x` = 2689.259277, `target_position_y` = -3396.083496, `target_position_z` = 267.683502 WHERE `id` = 28026;
/* equip templates for razuvious cube bug and utgarde keep cube bug */
UPDATE `creature_equip_template` SET `itemEntry3` = 29010 WHERE `entry` = 16061;
UPDATE `creature_equip_template` SET `itemEntry2` = 0, `itemEntry3` = 40183 WHERE `entry` = 23956;
