SET @NewCost18 =  2723;
SET @NewCost28 = 2997;
UPDATE npc_vendor SET ExtendedCost = @NewCost18 WHERE entry = 80003 AND item = 37711 AND ExtendedCost = 2604;
UPDATE npc_vendor SET ExtendedCost = @NewCost28 WHERE entry = 80003 AND item = 37742 AND ExtendedCost = 2607;
