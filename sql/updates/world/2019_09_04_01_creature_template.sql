-- Knockback immunity
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|0x40000000, `mechanic_immune_mask`=`mechanic_immune_mask`|0x00000020 WHERE `entry` IN (40681, 40682);
