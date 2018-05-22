UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` & ~(64 | 2048) WHERE `entry` IN (32918, 33399);
