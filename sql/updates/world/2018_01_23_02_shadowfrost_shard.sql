UPDATE gameobject_loot_template SET ChanceOrQuestChance = -37.5 WHERE item = 50274 AND entry IN (28072, 28072, 28074, 28082);
UPDATE gameobject_loot_template SET ChanceOrQuestChance = -75 WHERE item = 50274 AND entry IN (28088, 28096);

UPDATE creature_loot_template SET ChanceOrQuestChance = -75 WHERE item = 50274 AND ChanceOrQuestChance = -68;
UPDATE creature_loot_template SET ChanceOrQuestChance = -37.5 WHERE item = 50274 AND ChanceOrQuestChance = -38;