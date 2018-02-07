DELETE l
FROM reference_loot_template l
JOIN item_template i ON l.item = i.entry
WHERE l.entry = 34209 
AND i.class = 4
AND i.InventoryType = 7