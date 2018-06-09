UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` | 67108864 WHERE `entry` = 28912;

UPDATE `creature` SET `spawntimesecs` = 10 WHERE `id` = 28912;
