DELETE FROM `creature_template` WHERE `entry` = 21080;
INSERT INTO `creature_template` VALUES (21080,0,0,0,0,0,19595,0,0,0,'Dormant Infernal',NULL,NULL,0,69,69,1,14,0,1,1.14286,1,0,245,346,0,298,1,2000,2000,1,0,2048,0,0,0,0,0,0,206,302,43,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340);

UPDATE `smart_scripts` SET `link` = 2 WHERE `entryorguid` = 21080 AND `source_type` = 0 AND `id` = 1;
UPDATE `smart_scripts` SET `link` = 0 WHERE `entryorguid` = 21080 AND `source_type` = 0 AND `id` = 2;