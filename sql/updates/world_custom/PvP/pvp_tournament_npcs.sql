SET @ENTRY := 90000;
SET @NPC_COUNT := 17;
SET @GUID := 600000;

DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + @NPC_COUNT;

INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,19633,0,0,0,'PvP Gear','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 1,0,0,0,0,0,19633,0,0,0,'PvP Weapons','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 2,0,0,0,0,0,19633,0,0,0,'PvE Plate','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 3,0,0,0,0,0,19633,0,0,0,'PvE Leather','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 4,0,0,0,0,0,19633,0,0,0,'PvE Mail','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 5,0,0,0,0,0,19633,0,0,0,'PvE Cloth','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 6,0,0,0,0,0,19633,0,0,0,'PvE Weapons','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 7,0,0,0,0,0,19633,0,0,0,'PvE Shields&Offhands','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 8,0,0,0,0,0,19633,0,0,0,'PvE Rings&Necks','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 9,0,0,0,0,0,19633,0,0,0,'PvE Trinkets','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 10,0,0,0,0,0,19633,0,0,0,'PvE Cloaks&Relics','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 11,0,0,0,0,0,19633,0,0,0,'Glyphs I','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 12,0,0,0,0,0,19633,0,0,0,'Glyphs II','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 13,0,0,0,0,0,19633,0,0,0,'Glyphs III','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 14,0,0,0,0,0,19633,0,0,0,'Glyphs IV','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 15,0,0,0,0,0,19633,0,0,0,'Armor Enchantements I','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 16,0,0,0,0,0,19633,0,0,0,'Armor Enchantements II','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@ENTRY + 17,0,0,0,0,0,19633,0,0,0,'Weapon Enchantements','',NULL,0,70,70,1,35,128,1,1.14286,0.5,0,252,357,0,304,1,2000,2000,1,33024,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',1,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340);

DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID + @NPC_COUNT;
INSERT INTO `creature` VALUES 
(@GUID + 0,@ENTRY + 0,571,1,1,0,0,5779.96,591.246,609.886,1.77901,300,0,0,6986,0,0,0,0,0),
(@GUID + 1,@ENTRY + 1,571,1,1,0,0,5782.77,592.053,609.886,1.81828,300,0,0,6986,0,0,0,0,0),
(@GUID + 2,@ENTRY + 2,571,1,1,0,0,5785.28,593.595,609.886,2.03505,300,0,0,6986,0,0,0,0,0),
(@GUID + 3,@ENTRY + 3,571,1,1,0,0,5787.65,595.44,609.886,2.20391,300,0,0,6986,0,0,0,0,0),
(@GUID + 4,@ENTRY + 4,571,1,1,0,0,5789.86,597.911,609.886,2.47644,300,0,0,6986,0,0,0,0,0),
(@GUID + 5,@ENTRY + 5,571,1,1,0,0,5791.25,600.845,609.886,2.67201,300,0,0,6986,0,0,0,0,0),
(@GUID + 6,@ENTRY + 6,571,1,1,0,0,5792.06,603.898,609.886,2.80867,300,0,0,6986,0,0,0,0,0),
(@GUID + 7,@ENTRY + 7,571,1,1,0,0,5792.37,606.828,609.886,2.94847,300,0,0,6986,0,0,0,0,0),
(@GUID + 8,@ENTRY + 8,571,1,1,0,0,5792.33,609.993,609.886,3.06785,300,0,0,6986,0,0,0,0,0),
(@GUID + 9,@ENTRY + 9,571,1,1,0,0,5762.27,609.751,609.886,5.45309,300,0,0,6986,0,0,0,0,0),
(@GUID + 10,@ENTRY + 10,571,1,1,0,0,5763.11,612.153,609.886,5.84657,300,0,0,6986,0,0,0,0,0),
(@GUID + 11,@ENTRY + 11,571,1,1,0,0,5764.28,615.094,609.886,5.64394,300,0,0,6986,0,0,0,0,0),
(@GUID + 12,@ENTRY + 12,571,1,1,0,0,5765.88,617.156,609.886,5.40911,300,0,0,6986,0,0,0,0,0),
(@GUID + 13,@ENTRY + 13,571,1,1,0,0,5768.33,618.98,609.886,5.684,300,0,0,6986,0,0,0,0,0),
(@GUID + 14,@ENTRY + 15,571,1,1,0,0,5770.58,620.857,609.886,5.38633,300,0,0,6986,0,0,0,0,0),
(@GUID + 15,@ENTRY + 16,571,1,1,0,0,5772.94,621.811,609.886,5.3879,300,0,0,6986,0,0,0,0,0),
(@GUID + 16,@ENTRY + 17,571,1,1,0,0,5775.73,622.672,609.886,4.62056,300,0,0,6986,0,0,0,0,0);



DELETE FROM `npc_vendor` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + @NPC_COUNT;

-- Wrathful items, not weapons
INSERT INTO npc_vendor SELECT @ENTRY, 0, `entry`, 0, 0, 0 FROM `item_template` WHERE `name` LIKE 'Wrathful%' AND `class` != 2;

-- Wrathful items, only weapons
INSERT INTO npc_vendor SELECT @ENTRY + 1, 0, `entry`, 0, 0, 0 FROM `item_template` WHERE `name` LIKE 'Wrathful%' AND `class` = 2;

-- ICC Plate items
INSERT INTO npc_vendor 
SELECT @ENTRY + 2, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.class = 4 AND i.subclass = 4;
-- T10 Plate items
INSERT INTO npc_vendor 
SELECT @ENTRY + 2, 0, i.entry, 0, 0, 0
FROM item_template i 
WHERE i.NAME LIKE 'Sanctified%' AND i.ItemLevel = 277 AND i.class = 4 AND i.subclass = 4;

-- ICC Leather items
INSERT INTO npc_vendor 
SELECT @ENTRY + 3, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.class = 4 AND i.subclass = 2;
-- T10 Leather items
INSERT INTO npc_vendor 
SELECT @ENTRY + 3, 0, i.entry, 0, 0, 0
FROM item_template i 
WHERE i.NAME LIKE 'Sanctified%' AND i.ItemLevel = 277 AND i.class = 4 AND i.subclass = 2;

-- ICC Mail items
INSERT INTO npc_vendor 
SELECT @ENTRY + 4, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.class = 4 AND i.subclass = 3;
-- T10 Mail items
INSERT INTO npc_vendor 
SELECT @ENTRY + 4, 0, i.entry, 0, 0, 0
FROM item_template i 
WHERE i.NAME LIKE 'Sanctified%' AND i.ItemLevel = 277 AND i.class = 4 AND i.subclass = 3;

-- ICC Cloth items
INSERT INTO npc_vendor 
SELECT @ENTRY + 5, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
 AND i.class = 4 AND i.subclass = 1;
-- T10 Cloth items
INSERT INTO npc_vendor 
SELECT @ENTRY + 5, 0, i.entry, 0, 0, 0
FROM item_template i 
WHERE i.NAME LIKE 'Sanctified%' AND i.ItemLevel = 277 AND i.class = 4 AND i.subclass = 1;

-- ICC Weapons
INSERT INTO npc_vendor 
SELECT @ENTRY + 6, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.class = 2;

-- ICC Shields&Offhands
INSERT INTO npc_vendor 
SELECT @ENTRY + 7, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.InventoryType IN (14,23);

-- ICC Rings&Necks
INSERT INTO npc_vendor 
SELECT @ENTRY + 8, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.InventoryType IN (2,11);

-- ICC Trinkets
INSERT INTO npc_vendor 
SELECT @ENTRY + 9, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.InventoryType = 12;

-- ICC Cloaks
INSERT INTO npc_vendor 
SELECT @ENTRY + 10, 0, c.item, 0, 0, 0
FROM reference_loot_template c 
JOIN item_template i ON i.entry = c.item
WHERE c.entry IN (34266, 34267, 34267, 34272, 34279, 34273, 34279, 34263, 34275, 34263, 34275, 34265, 34277, 34287, 34274, 34279, 34256, 34254, 34261, 34255, 34257, 34258, 34259, 34262)  
AND i.InventoryType = 16;

-- Relics
INSERT INTO npc_vendor
SELECT @ENTRY + 10, 0, entry, 0, 0, 0 FROM item_template i WHERE i.InventoryType = 28 AND i.ItemLevel = 264;

-- All items for free!!!11
UPDATE item_template i SET BuyPrice = 0;

-- Glyphs
INSERT INTO npc_vendor
SELECT @ENTRY + 11, 0, entry, 0, 0, 0 FROM item_template i WHERE i.class = 16 LIMIT 150;
INSERT INTO npc_vendor
SELECT @ENTRY + 12, 0, entry, 0, 0, 0 FROM item_template i WHERE i.class = 16 LIMIT 150,150;
INSERT INTO npc_vendor
SELECT @ENTRY + 13, 0, entry, 0, 0, 0 FROM item_template i WHERE i.class = 16 AND i.name NOT like '%deprecated%' LIMIT 300,150;


-- Enchantements
INSERT INTO npc_vendor
SELECT @ENTRY + 15, 0, entry, 0, 0, 0 FROM item_template i WHERE `name` LIKE 'Scroll of Enchant%' AND `name` NOT LIKE '%weapon%' LIMIT 100;
INSERT INTO npc_vendor
SELECT @ENTRY + 16, 0, entry, 0, 0, 0 FROM item_template i WHERE `name` LIKE 'Scroll of Enchant%' AND `name` NOT LIKE '%weapon%' LIMIT 100,100;
INSERT INTO npc_vendor
SELECT @ENTRY + 17, 0, entry, 0, 0, 0 FROM item_template i WHERE `name` LIKE 'Scroll of Enchant Weapon%';
