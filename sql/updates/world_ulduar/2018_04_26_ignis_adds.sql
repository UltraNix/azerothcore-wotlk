UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` &~ 3136, `flags_extra` = `flags_extra` | 1048576 WHERE `entry` IN (33121, 33191);
