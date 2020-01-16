DELETE FROM `smart_scripts` WHERE `entryorguid` = 179533 AND `source_type` = 1 AND `id` = 4;
INSERT INTO `smart_scripts` VALUES 
(179533,1,4,0,61,0,100,0,1,0,0,0,105,16,1,0,0,0,0,1,0,0,0,0,0,0,0,'Warpwood Pod - On Timed Event - Despawn');
UPDATE `smart_scripts` SET `link`=4 WHERE  `entryorguid`=179533 AND `source_type`=1 AND `id`=2;