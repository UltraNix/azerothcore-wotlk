DELETE FROM `smart_scripts` WHERE `entryorguid` = 27331;
INSERT INTO `smart_scripts` VALUES 
(27331, 0, 0, 1, 8, 0, 100, 0, 48345, 0, 0, 0, 33, 27331, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Quest Credit \'Bombard the Ballistae\''),
(27331, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48347, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast FX Master'),
(27331, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 11, 52687, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Knockback'),
(27331, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Despawn Instant');

DELETE FROM `conditions` WHERE `SourceEntry` = 48347 AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` VALUES
(13, 2, 48347, 0, 0, 31, 0, 5, 188673, 0, 0, 0, 0, '', '');
