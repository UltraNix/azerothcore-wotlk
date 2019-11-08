SET @COST = 2588;
SET @NPC1 = 34081;
SET @NPC2 = 34043;

DELETE FROM `npc_vendor` WHERE `entry` = 34040 AND `item` IN
(36918,36921,36924,36927,36930,36933);
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES 
(34040, 0, 36918, 0, 0, @COST),
(34040, 0, 36921, 0, 0, @COST),
(34040, 0, 36924, 0, 0, @COST),
(34040, 0, 36927, 0, 0, @COST),
(34040, 0, 36930, 0, 0, @COST),
(34040, 0, 36933, 0, 0, @COST);
