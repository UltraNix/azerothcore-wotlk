-- Hodir 25 normal chest should drop additional token
UPDATE `gameobject_loot_template` SET `maxcount` = 2 WHERE `entry` = 26946 AND `item` = 2 AND `mincountOrRef` = -12029;
