-- DB/Item: Recipe: Captain Rumsey's Lager - will have a chance to drop from daily cooking quest rewards
DELETE FROM `item_loot_template` WHERE `item` = 34834 AND `entry` IN (46007, 34863, 35348);
INSERT INTO `item_loot_template` VALUES 
(46007, 34834, 0.4, 1, 0, 1, 1),
(34863, 34834, 0.4, 1, 0, 1, 1),
(35348, 34834, 0.4, 1, 0, 1, 1);
