DELETE FROM `disables` WHERE  `sourceType`=1 AND `entry`=13627;
DELETE FROM `disables` WHERE  `sourceType`=1 AND `entry`=13681;
DELETE FROM `spell_area` WHERE `spell` = 61831;
UPDATE `creature` SET `phasemask` = 1 WHERE `guid` = 71980;

DELETE FROM `disables` WHERE `sourceType` = 1 AND `entry` = 14016;
INSERT INTO `disables` VALUES (1, 14016, 0, 0, 0, 'Disables quest The Black Knight\'s Curse');

UPDATE `creature` SET `phasemask` = 2 WHERE `id` IN (34885, 34912, 34914, 34882, 35094, 35574, 35576, 35578, 35580, 35579, 35577, 35575, 35573, 34880, 34881, 34771, 34772);
