DELETE FROM `creature_text` WHERE `entry` = 22483 AND `id` = 3;
INSERT INTO `creature_text` VALUES
(22483,0,3,"AWOOOOGAAAA!",12,0,100,5,0,0,0,"Sand Gnome");
UPDATE `creature_text` SET `emote` = 5 WHERE `entry` = 22483 AND `groupid` = 0;
