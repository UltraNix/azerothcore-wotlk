DELETE FROM `gossip_menu_option` WHERE `menu_id` = 2208 AND id = 1;
INSERT INTO `gossip_menu_option` VALUES
(2208, 1, 0, 'What plants are in Felwood that might be corrupted?', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 21400 AND `id` = 0;
INSERT INTO `gossip_menu_option` VALUES 
(21400, 1, 0, 'What plants are in Felwood that might be corrupted?', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `conditions` WHERE `SourceEntry` = 54267 AND `ConditionValue3` = 102902;
DELETE FROM `conditions` WHERE `SourceEntry` = 54266 AND `ConditionValue3` = 102901;
DELETE FROM `conditions` WHERE `SourceEntry` = 54265 AND `ConditionValue3` = 102904;
DELETE FROM `conditions` WHERE `SourceEntry` = 54264 AND `ConditionValue3` = 102905;
DELETE FROM `conditions` WHERE `SourceEntry` = 54258 AND `ConditionValue3` = 102906;


