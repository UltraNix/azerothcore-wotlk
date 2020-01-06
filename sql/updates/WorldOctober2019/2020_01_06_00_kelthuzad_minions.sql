UPDATE `creature_template`
SET `flags_extra` = `flags_extra` | 1073741824
WHERE `entry` IN (16441, 16427, 16428, 16429, 30057, 30015, 30048, 30018);
