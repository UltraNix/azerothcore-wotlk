DELETE FROM `smart_scripts` WHERE `entryorguid` = 27331;
INSERT INTO `smart_scripts` VALUES 
(27331,0,0,1,8,0,100,0,48345,0,110000,110000,33,27331,0,0,0,0,0,7,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Quest Credit \'Bombard the Ballistae\''),
(27331,0,1,2,61,0,100,0,0,0,0,0,11,48351,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast  Bombard the Ballistae: Ballista Bow'),
(27331,0,2,3,61,0,100,0,0,0,0,0,11,48352,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Frame'),
(27331,0,3,4,61,0,100,0,0,0,0,0,11,48353,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Missile'),
(27331,0,4,5,61,0,100,0,0,0,0,0,11,48354,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Ballista Wheel'),
(27331,0,5,6,61,0,100,0,0,0,0,0,11,48347,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: FX Master'),
(27331,0,6,7,61,0,100,0,0,0,0,0,11,52687,2,0,0,0,0,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Cast Bombard the Ballistae: Knockback'),
(27331,0,7,8,61,0,100,0,0,0,0,0,44,2,0,0,0,0,0,20,188673,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Change Phasemask to 2'),
(27331,0,8,0,61,0,100,0,0,0,0,0,67,1,110000,110000,0,0,100,1,0,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Spellhit \'Siegesmith Bombs\' - Create Timed Event'),
(27331,0,9,0,59,0,100,0,1,0,0,0,44,1,0,0,0,0,0,20,188673,0,0,0,0,0,0,'Bombard the Ballistae Kill Credit Bunny - On Timed Event - Change phasemask to 1');

UPDATE `creature` SET `phaseMask` = 3 WHERE `id` = 27331;