DELETE FROM `item_loot_template` WHERE `entry` = 41426 AND `item` IN (37742, 37711);
INSERT INTO `item_loot_template` VALUES
(41426, 37742, 100, 1, 0, 1, 1),
(41426, 37711, 100, 1, 0, 2, 2);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 5 AND `sourcegroup` = 41426 AND `sourceentry` IN (37742, 37711);
INSERT INTO `conditions` VALUES 
(5,41426,37742,0,0,6,0,469,0,0,0,0,0,'','Magically Wrapped Gift - Weapon Transmog Token can drop only for Alliance'),
(5,41426,37711,0,0,6,0,469,0,0,0,0,0,'','Magically Wrapped Gift - Armor Transmog Token can drop only for Alliance');