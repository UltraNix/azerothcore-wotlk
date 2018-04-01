UPDATE `gameobject` SET `state` = 0 WHERE `guid` IN (17906, 32250);
UPDATE `gameobject_template` SET `flags` = `flags` | 4 WHERE `entry` IN (170558, 101854);
