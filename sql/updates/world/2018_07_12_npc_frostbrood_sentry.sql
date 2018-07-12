UPDATE `creature` SET `spawntimesecs` = 10 WHERE `id` = 32767;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 64 WHERE `entry` = 32767;
