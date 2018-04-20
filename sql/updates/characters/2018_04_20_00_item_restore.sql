DROP TABLE IF EXISTS `item_restore`;
CREATE TABLE `item_restore` (
  `restoreId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `item` int(10) unsigned NOT NULL COMMENT 'Item entry',
  `count` int(10) unsigned NOT NULL COMMENT 'Item count',
  `date` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`restoreId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Item Restore System';