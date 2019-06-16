-- Scorn should not spawn in Scarlet Monastery
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4543 AND `id` = 7;
