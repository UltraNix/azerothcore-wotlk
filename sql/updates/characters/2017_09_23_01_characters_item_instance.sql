-- Delete unexisted enchant from existing items 
UPDATE item_instance SET enchantments = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" 
WHERE itemEntry IN(14171, 6568) AND randomPropertyId = 1714;