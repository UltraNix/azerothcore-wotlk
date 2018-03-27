-- Harvest Soul
UPDATE `spell_target_position` SET `target_position_z`=1051.99 WHERE `id`=72546;
-- Lord Marrowgar
UPDATE `creature_template` SET `mindmg`=8800, `maxdmg`=9700, `dmg_multiplier`=10 WHERE `entry`=37959;
-- Boss Immunities
UPDATE `creature_template` SET `mechanic_immune_mask`=550189855 WHERE `entry` IN (37863, 38171, 38727, 38737, 37934, 38170, 38723, 38733);
