UPDATE `creature_template` SET `AIname` = "SmartAI", `ScriptName` = "" WHERE `entry` = 27331;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 27331;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(27331, 0, 0, 1, 8, 0, 100, 0, 48345, 0, 110000, 110000, 33, 27331, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Quest Credit \'Bombard the Ballistae\''),
(27331, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48351, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast  Bombard the Ballistae: Ballista Bow'),
(27331, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48352, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Frame'),
(27331, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48353, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Missile'),
(27331, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48354, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Wheel'),
(27331, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 11, 48347, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: FX Master'),
(27331, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 11, 52687, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Knockback'),
(27331, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 99, 3, 0, 0, 0, 0, 0, 20, 188673, 0, 0, 0, 0, 0, 0, 'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Despawn GO');

UPDATE `gameobject` SET `spawntimesecs` = 110 WHERE `id` = 188673;
