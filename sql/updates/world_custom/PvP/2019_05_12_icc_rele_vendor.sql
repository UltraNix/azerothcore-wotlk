SET @CGUID = 500001;
SET @NPC = 220001;

DELETE FROM `creature_template` WHERE `entry` = @NPC;
INSERT INTO `creature_template` VALUES (@NPC,0,0,0,0,0,29077,0,0,0,'Zrynazz Gayserstick','','',0,70,70,1,35,128,1,1.14286,1,0,252,357,0,304,1,2000,2000,1,0,2048,0,0,0,0,0,0,215,320,44,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340);

DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` VALUES
(@CGUID, @NPC, 571, 1, 1, 0, 0, 5754.33, 580.06, 613.76, 0.78, 300, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `npc_vendor` WHERE `entry` = @NPC;

-- Move items from s7 vendor
INSERT INTO npc_vendor 
(SELECT @NPC, `slot`, `item`, `maxcount`, `incrtime`, `extendedcost` FROM `npc_vendor` WHERE `entry` = 34092);

-- Delete tabard
DELETE FROM `npc_vendor` WHERE `entry` = @NPC AND `item` = 49086;

-- Set cost of ranged and 2h weapons to 24k honor and 700ap
UPDATE `npc_vendor` n SET `ExtendedCost` = 2438 WHERE `entry` = @NPC AND 
EXISTS (SELECT * FROM item_template i WHERE i.entry = n.item AND i.inventorytype IN (15, 17));

-- Set cost of mainhand, 1h weapons and offhands to 12k honor and 350 arena points
UPDATE `npc_vendor` n SET `ExtendedCost` = 2440 WHERE `entry` = @NPC AND 
EXISTS (SELECT * FROM item_template i WHERE i.entry = n.item AND i.inventorytype IN (21, 13, 22));
