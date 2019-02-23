-- DB/QuesT: Scalps - quest item can be used on Heb'Drakkar Striker too
DELETE FROM `conditions` WHERE `SourceEntry` = 52090 AND `ElseGroup` = 1;
INSERT INTO `conditions` VALUES 
(17, 0, 52090, 0, 1, 31, 1, 3, 28465, 0, 0, 173, 0, '', 'Item 38731 "Ahunae\'s Knife" targets 28600 "Dead Heb\'Drakkar Striker'),
(17, 0, 52090, 0, 1, 36, 1, 0, 0, 0, 1, 173, 0, '', 'Item 38731 "Ahunae\'s Knife" targets 28600 "Dead Heb\'Drakkar Striker');
