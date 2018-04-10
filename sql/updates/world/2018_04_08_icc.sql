DELETE FROM `spell_script_names` WHERE `spell_id`=70914;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70914, "spell_dreamwalker_decay_periodic_timer");

-- Blistering Zombie
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|33554432 WHERE `entry` IN (37934, 38170, 38723, 38733);