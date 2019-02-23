-- DB/Item: Master First Aid - Doctor in the House should no longer be sold
DELETE FROM `npc_vendor` WHERE `item` = 22012;
