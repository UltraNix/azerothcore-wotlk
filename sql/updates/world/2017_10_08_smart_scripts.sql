/* Winterspring */

-- Winterfall Ursa
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7438;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7438 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7438,0,0,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Ursa - Out of Combat - Cast Winterfall Firewater");
-- Winterfall Shaman
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7439;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7439 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7439,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterfall Shaman - In Combat - Cast Lightning Bolt"),
(7439,0,1,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Shaman - Out of Combat - Cast Winterfall Firewater"),
(7439,0,2,0,1,0,100,0,500,1000,600000,600000,11,13585,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Shaman - Out of Combat - Cast Lightning Shield"),
(7439,0,3,0,16,0,100,0,13585,1,15000,30000,11,13585,1,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Shaman - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield"),
(7439,0,4,0,2,0,100,0,0,40,14000,21000,11,11431,1,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Shaman - Between 0-40% Health - Cast Healing Touch"),
(7439,0,5,0,14,0,100,0,800,40,15000,18000,11,11431,1,0,0,0,0,7,0,0,0,0,0,0,0,"Winterfall Shaman - Friendly At 800 Health - Cast Healing Touch");
-- Winterfall Den Watcher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7440;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7440 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7440,0,0,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Den Watcher - Out of Combat - Cast Winterfall Firewater");
-- Winterfall Totemic
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7441;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7441 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7441,0,0,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Totemic - Out of Combat - Cast Winterfall Firewater"),
(7441,0,1,0,0,0,100,0,6000,9000,45000,50000,11,15786,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Totemic - In Combat - Cast Earthbind Totem"),
(7441,0,2,0,0,0,100,0,6000,9000,22000,25000,11,15787,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Totemic - In Combat - Cast Moonflare Totem");
-- Winterfall Pathfinder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7442;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7442 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7442,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Winterfall Pathfinder - In Combat - Cast Shoot"),
(7442,0,1,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Pathfinder - Out of Combat - Cast Winterfall Firewater"),
(7442,0,2,0,0,0,100,0,6000,8000,22000,25000,11,16498,0,0,0,0,0,2,0,0,0,0,0,0,0,"Winterfall Pathfinder - In Combat - Cast Faerie Fire");
-- High Chief Winterfall
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10738;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10738 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10738,0,0,0,9,0,100,0,0,5,12000,17000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Chief Winterfall - Within 0-5 Range - Cast Maul"),
(10738,0,1,0,9,0,100,0,0,20,15000,25000,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Chief Winterfall - Within 0-20 Range - Cast Frost Shock"),
(10738,0,2,0,0,0,100,0,5000,7000,24000,25000,11,8364,0,0,0,0,0,4,0,0,0,0,0,0,0,"High Chief Winterfall - In Combat - Cast Blizzard"),
(10738,0,3,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Chief Winterfall - Out of Combat - Cast Winterfall Firewater");
-- Grizzle Snowpaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10199;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10199 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10199,0,0,0,9,0,100,0,0,5,12000,17000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grizzle Snowpaw - Within 0-5 Range - Cast Maul"),
(10199,0,1,0,9,0,100,0,0,20,15000,25000,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grizzle Snowpaw - Within 0-20 Range - Cast Frost Shock"),
(10199,0,2,0,0,0,100,0,5000,7000,24000,25000,11,8364,0,0,0,0,0,4,0,0,0,0,0,0,0,"Grizzle Snowpaw - In Combat - Cast Blizzard"),
(10199,0,3,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grizzle Snowpaw - Out of Combat - Cast Winterfall Firewater");
-- Shardtooth Mauler
DELETE FROM `smart_scripts` WHERE `entryorguid`=7443 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7443,0,0,0,0,0,100,0,4000,6000,8000,10000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shardtooth Mauler - In Combat - Cast Maul");
-- Shardtooth Bear
DELETE FROM `smart_scripts` WHERE `entryorguid`=7444 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7444,0,0,0,0,0,100,0,5000,8000,9000,12000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shardtooth Bear - In Combat - Cast Tendon Rip");
-- Elder Shardtooth
DELETE FROM `smart_scripts` WHERE `entryorguid`=7445 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7445,0,0,0,9,0,100,0,0,5,12000,19000,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Shardtooth - Within 0-5 Range - Cast Demoralizing Roar");
-- Rabid Shardtooth
DELETE FROM `smart_scripts` WHERE `entryorguid`=7446 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7446,0,0,0,9,0,100,0,0,5,5000,8000,11,3150,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rabid Shardtooth - Within 0-5 Range - Cast Rabies"),
(7446,0,1,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rabid Shardtooth - In Combat - Cast Thrash");
-- Ursius
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10806;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10806 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10806,0,0,0,9,0,100,0,0,5,12000,17000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ursius - Within 0-5 Range - Cast Maul"),
(10806,0,1,0,0,0,100,0,6000,8000,33000,35000,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ursius - In Combat - Cast Demoralizing Roar");
-- Rogue Ice Thistle
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7457;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7457 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7457,0,0,0,9,0,100,0,0,5,3000,6000,11,3604,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rogue Ice Thistle - Within 0-5 Range - Cast Tendon Rip");
-- Ice Thistle Yeti
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7458;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7458 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7458,0,0,0,0,0,100,0,6000,12000,18000,21000,11,15878,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Thistle Yeti - In Combat - Cast Ice Blast"),
(7458,0,1,0,0,0,100,0,4000,6000,19000,26000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Thistle Yeti - In Combat - Cast Tendon Rip");
-- Ice Thistle Matriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7459;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7459 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7459,0,0,0,0,0,100,0,6000,12000,18000,21000,11,15878,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Thistle Matriarch - In Combat - Cast Ice Blast"),
(7459,0,1,0,4,0,100,1,0,0,0,0,11,6268,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ice Thistle Matriarch - On Aggro - Cast Rushing Charge");
-- Ice Thistle Patriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7460;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7460 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7460,0,0,0,0,0,100,0,8000,12000,18000,21000,11,15878,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Thistle Patriarch - In Combat - Cast Ice Blast"),
(7460,0,1,0,0,0,100,0,6000,8000,16000,24000,11,3131,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ice Thistle Patriarch - In Combat - Cast Frost Breath");
-- Mezzir the Howler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10197;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10197 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10197,0,0,0,9,0,100,0,0,5,31000,35000,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mezzir the Howler - Within 0-5 Range - Cast Demoralizing Roar"),
(10197,0,1,0,0,0,100,0,7000,10000,14000,18000,11,3131,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mezzir the Howler - In Combat - Cast Frost Breath"),
(10197,0,2,0,2,0,100,0,0,40,18000,24000,11,14100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mezzir the Howler - Between 0-40% Health - Cast Terrifying Roar");
-- Fledgling Chillwind
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7447;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7447 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7447,0,0,0,0,0,100,0,4000,6000,8000,12000,11,16552,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fledgling Chillwind - In Combat - Cast Venom Spit");
-- Chillwind Chimaera
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7448;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7448 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7448,0,0,0,0,0,100,0,6000,8000,14000,18000,11,15797,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chillwind Chimaera - In Combat - Cast Lightning Breath"),
(7448,0,1,0,0,0,100,0,3000,5000,16000,20000,11,15850,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chillwind Chimaera - In Combat - Cast Chilled");
-- Chillwind Ravager
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7449;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7449 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7449,0,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chillwind Ravager - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Winterspring Owl
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7455;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7455 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7455,0,0,0,0,0,100,0,7000,9000,12000,16000,11,16576,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterspring Owl - In Combat - Cast Piercing Screech");
-- Winterspring Screecher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7456;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7456 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7456,0,0,0,9,0,100,0,0,10,13000,16000,11,3589,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterspring Screecher - Within 0-10 Range - Cast Deafening Screech");
-- Suffering Highborne
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7523;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7523 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7523,0,0,0,9,0,100,0,0,30,13000,20000,11,14868,32,0,0,0,0,2,0,0,0,0,0,0,0,"Suffering Highborne - Within 0-30 Range - Cast Curse of Agony");
-- Anguished Highborne
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7524;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7524 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7524,0,0,0,0,0,100,0,0,0,3400,4800,11,13860,64,0,0,0,0,2,0,0,0,0,0,0,0,"Anguished Highborne - In Combat - Cast Mind Blast");
-- Watery Invader
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14458;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14458 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14458,0,0,0,0,0,100,0,5000,7000,14000,18000,11,15089,0,0,0,0,0,2,0,0,0,0,0,0,0,"Watery Invader - In Combat - Cast Frost Shock"),
(14458,0,1,0,9,0,100,0,0,5,16000,24000,11,15850,2,0,0,0,0,2,0,0,0,0,0,0,0,"Watery Invader - Within 0-5 Range - Cast Chilled");
-- Frostsaber
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7431;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7431 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7431,0,0,0,0,0,100,0,6000,9000,15000,18000,11,24331,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostsaber - In Combat - Cast Rake");
-- Frostsaber Stalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7432;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7432 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7432,0,0,0,25,0,100,1,0,0,0,0,11,30831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frostsaber Stalker - On Reset - Cast Stealth");
-- Frostsaber Huntress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7433;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7433 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7433,0,0,0,2,0,100,1,0,30,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frostsaber Huntress - Between 0-30% Health - Cast Enrage (No Repeat)"),
(7433,0,1,0,0,0,100,0,6000,9000,16000,21000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostsaber Huntress - In Combat - Cast Rend");
-- Frostsaber Pride Watcher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7434;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7434 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7434,0,0,0,2,0,100,1,0,30,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frostsaber Pride Watcher - Between 0-30% Health - Cast Enrage (No Repeat)"),
(7434,0,1,0,0,0,100,0,6000,10000,18000,24000,11,36590,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostsaber Pride Watcher - In Combat - Cast Rip");
-- Rak'shiri
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10200 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10200,0,0,0,2,0,100,0,0,60,15000,21000,11,7399,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rak\'shiri - Between 0-60% Health - Cast Terrify"),
(10200,0,1,0,2,0,100,1,0,30,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rak\'shiri - Between 0-30% Health - Cast Enrage");
-- Sian-Rotam
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10741;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10741 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10741,0,0,0,0,0,100,0,8000,11000,12000,18000,11,14100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sian-Rotam - In Combat - Cast Terrifying Roar"),
(10741,0,1,0,9,0,100,0,0,5,15000,20000,11,3604,32,0,0,0,0,2,0,0,0,0,0,0,0,"Sian-Rotam - Within 0-5 Range - Cast Tendon Rip"),
(10741,0,2,0,0,0,100,0,5000,9000,13000,16000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sian-Rotam - In Combat - Cast Rend"),
(10741,0,3,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"Sian-Rotam - Just Summoned - Start Attacking");
-- Shy-Rotam
DELETE FROM `smart_scripts` WHERE `entryorguid`=10737 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10737,0,0,0,0,0,100,0,8000,11000,12000,18000,11,14100,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shy-Rotam - In Combat - Cast Terrifying Roar"),
(10737,0,1,0,0,0,100,0,5000,9000,13000,16000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shy-Rotam - In Combat - Cast Rend"),
(10737,0,2,0,9,0,100,0,0,5,15000,20000,11,3604,32,0,0,0,0,2,0,0,0,0,0,0,0,"Shy-Rotam - Within 0-5 Range - Cast Tendon Rip"),
(10737,0,3,0,2,0,100,1,0,50,0,0,12,10741,1,180000,0,0,0,8,0,0,0,8074.84,-3840,690.061,4.6,"Shy-Rotam - Between 0-50% Health - Summon Creature \'Sian-Rotam\'");
-- Ragged Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7450;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7450 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7450,0,0,0,9,0,100,0,0,5,4000,8000,11,15848,32,0,0,0,0,2,0,0,0,0,0,0,0,"Ragged Owlbeast - Within 0-5 Range - Cast Festering Rash");
-- Raging Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7451;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7451 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7451,0,0,0,9,0,100,0,0,5,13000,18000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Raging Owlbeast - Within 0-5 Range - Cast Rend");
-- Crazed Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7452;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7452 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7452,0,0,0,2,0,100,1,0,50,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crazed Owlbeast - Between 0-50% Health - Cast Enrage (No Repeat)");
-- Moontouched Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7453;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7453 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7453,0,0,0,2,0,100,0,0,50,18000,21000,11,12160,0,0,0,0,0,1,0,0,0,0,0,0,0,"Moontouched Owlbeast - Between 0-50% Health - Cast Rejuvenation"),
(7453,0,1,0,0,0,100,0,4000,6000,14000,16000,11,15798,0,0,0,0,0,2,0,0,0,0,0,0,0,"Moontouched Owlbeast - In Combat - Cast Moonfire");
-- Berserk Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7454;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7454 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7454,0,0,0,2,0,100,1,0,30,0,0,11,5915,0,0,0,0,0,1,0,0,0,0,0,0,0,"Berserk Owlbeast - Between 0-30% Health - Cast Crazed (No Repeat)");
-- Cobalt Broodling
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10660;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10660 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10660,0,0,0,0,0,100,0,0,0,3400,4800,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Broodling - In Combat - Cast Frostbolt"),
(10660,0,1,0,9,0,100,0,0,10,10000,15000,11,17008,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Broodling - Within 0-10 Range - Cast Drain Mana"),
(10660,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cobalt Broodling - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Spell Eater
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10661;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10661 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10661,0,0,0,0,0,100,0,6000,8000,14000,20000,11,16340,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spell Eater - In Combat - Cast Frost Breath");
-- Cobalt Whelp
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10659;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10659 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10659,0,0,0,0,0,100,0,4000,6000,12000,16000,11,15089,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Whelp - In Combat - Cast Frost Shock"),
(10659,0,1,0,0,0,100,0,7000,10000,18000,22000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Whelp - In Combat - Cast Rend");
-- Cobalt Wyrmkin
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7435;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7435 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7435,0,0,0,0,0,100,0,6000,9000,7000,10000,11,15580,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Wyrmkin - In Combat - Cast Strike"),
(7435,0,1,0,0,0,100,0,4000,6000,14000,18000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Wyrmkin - In Combat - Cast Hamstring");
-- Cobalt Scalebane
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7436;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7436 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7436,0,0,0,9,0,100,0,0,5,17000,21000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Scalebane - Within 0-5 Range - Cast Rend"),
(7436,0,1,0,9,0,100,0,0,5,9000,13000,11,6713,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Scalebane - Within 0-5 Range - Cast Disarm"),
(7436,0,2,0,13,0,100,1,0,0,0,0,11,15655,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Scalebane - Target Casting - Cast Shield Slam (No Repeat)");
-- Cobalt Mageweaver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7437;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7437 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7437,0,0,0,0,0,100,0,0,0,3400,6200,11,15043,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cobalt Mageweaver - In Combat - Cast Frostbolt"),
(7437,0,1,0,1,0,100,0,1000,1000,1800000,1800000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cobalt Mageweaver - Out of Combat - Cast Frost Armor");
-- Spellmaw
DELETE FROM `smart_scripts` WHERE `entryorguid`=10662 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10662,0,0,0,25,0,100,0,0,0,0,0,11,34304,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spellmaw - On Reset - Cast Damage Immunity: Arcane"),
(10662,0,1,0,0,0,100,0,6000,8000,20000,24000,11,16099,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spellmaw - In Combat - Cast Frost Breath"),
(10662,0,2,0,0,0,100,0,8000,10000,18000,21000,11,17012,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spellmaw - In Combat - Cast Devour Magic");
-- General Colbatann
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10196;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10196 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10196,0,0,0,4,0,100,1,0,0,0,0,11,9128,0,0,0,0,0,1,0,0,0,0,0,0,0,"General Colbatann - On Aggro - Cast Battle Shout"),
(10196,0,1,0,0,0,100,0,7000,10000,35000,44000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,"General Colbatann - In Combat - Cast Demoralizing Shout"),
(10196,0,2,0,9,0,100,0,0,5,15000,19000,11,11971,0,0,0,0,0,2,0,0,0,0,0,0,0,"General Colbatann - Within 0-5 Range - Cast Sunder Armor");
-- Manaclaw
DELETE FROM `smart_scripts` WHERE `entryorguid`=10663 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10663,0,0,0,25,0,100,0,0,0,0,0,11,34304,0,0,0,0,0,1,0,0,0,0,0,0,0,"Manaclaw - On Reset - Cast Damage Immunity: Arcane"),
(10663,0,1,0,0,0,100,0,6000,8000,16000,20000,11,16099,0,0,0,0,0,2,0,0,0,0,0,0,0,"Manaclaw - In Combat - Cast Frost Breath");
-- Scryer
DELETE FROM `smart_scripts` WHERE `entryorguid`=10664 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10664,0,0,0,25,0,100,0,0,0,0,0,11,34304,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scryer - On Reset - Cast Damage Immunity: Arcane"),
(10664,0,1,0,0,0,100,0,6000,8000,20000,24000,11,16099,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer - In Combat - Cast Frost Breath"),
(10664,0,2,0,0,0,100,0,3000,6000,15000,20000,11,12738,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scryer - In Combat - Cast Amplify Damage");
-- Azurous
DELETE FROM `smart_scripts` WHERE `entryorguid`=10202 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10202,0,0,0,25,0,100,0,0,0,0,0,11,34304,0,0,0,0,0,1,0,0,0,0,0,0,0,"Manaclaw - On Reset - Cast Damage Immunity: Arcane"),
(10202,0,1,0,0,0,100,0,6000,8000,15000,18000,11,16099,0,0,0,0,0,2,0,0,0,0,0,0,0,"Manaclaw - In Combat - Cast Frost Breath");
-- Brumeran
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10807;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10807 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10807,0,0,0,0,0,100,0,8000,10000,12000,15000,11,15797,0,0,0,0,0,2,0,0,0,0,0,0,0,"Brumeran - In Combat - Cast Lightning Breath"),
(10807,0,1,0,0,0,100,0,3000,6000,12000,15000,11,16552,0,0,0,0,0,2,0,0,0,0,0,0,0,"Brumeran - In Combat - Cast Venom Spit"),
(10807,0,2,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Brumeran - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Frostmaul Giant
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7428;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7428 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7428,0,0,0,0,0,100,0,12000,16000,28000,34000,11,18670,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostmaul Giant - In Combat - Cast Knock Away"),
(7428,0,1,0,0,0,100,0,4000,6000,14000,18000,11,18368,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostmaul Giant - In Combat - Cast Strike");
-- Frostmaul Preserver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7429;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7429 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7429,0,0,0,2,0,100,0,0,40,19000,26000,11,9616,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frostmaul Preserver - Between 0-40% Health - Cast Wild Regeneration");
-- Kashoch the Reaver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10198;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10198 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10198,0,0,0,9,0,100,0,0,5,14000,16000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kashoch the Reaver - Within 0-5 Range - Cast Cleave");
-- Hederine Initiate
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7461;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7461 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7461,0,0,0,0,0,100,0,0,0,3400,4800,11,12739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Hederine Initiate - In Combat - Cast Shadow Bolt");
-- Hederine Slayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7463;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7463 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7463,0,0,0,0,0,100,0,9000,12000,15000,18000,11,17547,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hederine Slayer - In Combat - Cast Mortal Strike");
-- Lady Hederine
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10201;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10201 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10201,0,0,0,0,0,100,0,5000,7000,18000,24000,11,17146,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lady Hederine - In Combat - Cast Shadow Word: Pain");
-- Random movement for some creatures
UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `guid`=51891;
UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `guid`=42304;

/* Felwood */

-- Felpaw Wolf
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8959;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8959 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8959,0,0,0,9,0,100,0,0,5,8000,14000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Felpaw Wolf - Within 0-5 Range - Cast Infected Wound");
-- Felpaw Scavenger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8960;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8960 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8960,0,0,0,9,0,100,0,0,5,8000,14000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Felpaw Scavenger - Within 0-5 Range - Cast Infected Wound"),
(8960,0,1,0,9,0,100,0,0,5,20000,25000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felpaw Scavenger - Within 0-5 Range - Cast Tendon Rip");
-- Felpaw Ravager
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8961;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8961 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8961,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Felpaw Ravager - In Combat - Cast Thrash"),
(8961,0,1,0,9,0,100,0,0,5,8000,14000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Felpaw Ravager - Within 0-5 Range - Cast Infected Wound");
-- Death Howl
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14339;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14339 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14339,0,0,0,9,0,100,0,0,5,12000,15000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Death Howl - Within 0-5 Range - Cast Tendon Rip"),
(14339,0,1,0,0,0,100,0,7000,11000,25000,29000,11,8715,0,0,0,0,0,1,0,0,0,0,0,0,0,"Death Howl - In Combat - Cast Terrifying Howl"),
(14339,0,2,0,0,0,100,0,4000,6000,8000,14000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Death Howl - In Combat - Cast Infected Wound");
-- Ironbeak Owl
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7097;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7097 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7097,0,0,0,9,0,100,0,0,5,8000,11000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ironbeak Owl - Within 0-5 Range - Cast Swoop");
-- Ironbeak Screecher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7098;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7098 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7098,0,0,0,9,0,100,0,0,10,13000,16000,11,3589,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ironbeak Screecher - Within 0-10 Range - Cast Deafening Screech");
-- Ironbeak Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7099;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7099 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7099,0,0,0,9,0,100,0,0,5,21000,24000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ironbeak Hunter - Within 0-5 Range - Cast Rend");
-- Angerclaw Grizzly
DELETE FROM `smart_scripts` WHERE `entryorguid`=8957 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8957,0,2,0,0,0,100,0,6000,8000,12000,16000,11,8716,0,0,0,0,0,2,0,0,0,0,0,0,0,"Angerclaw Grizzly - In Combat - Cast Low Swipe");
-- Angerclaw Mauler
DELETE FROM `smart_scripts` WHERE `entryorguid`=8958 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8958,0,2,0,9,0,100,0,0,5,5000,8000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Angerclaw Mauler - Within 0-5 Range - Cast Maul");
-- Deadwood Warrior
DELETE FROM `smart_scripts` WHERE `entryorguid`=7153 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7153,0,0,0,0,0,100,0,4000,11000,12000,15000,11,13583,32,0,0,0,0,2,0,0,0,0,0,0,0,"Deadwood Warrior - In Combat - Cast Curse of the Deadwood");
-- Deadwood Gardener
DELETE FROM `smart_scripts` WHERE `entryorguid`=7154 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7154,0,0,0,0,0,100,0,4000,11000,12000,15000,11,13583,32,0,0,0,0,2,0,0,0,0,0,0,0,"Deadwood Gardener - In Combat - Cast Curse of the Deadwood");
-- Overlord Ror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9464;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9464 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9464,0,0,0,9,0,100,0,0,5,5000,8000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Overlord Ror - Within 0-5 Range - Cast Maul"),
(9464,0,1,0,0,0,100,0,8000,12000,17000,21000,11,14100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overlord Ror - In Combat - Cast Terrifying Roar"),
(9464,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Overlord Ror - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Ragepaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14342;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14342 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14342,0,0,0,9,0,100,0,0,5,6000,9000,11,13584,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ragepaw - Within 0-5 Range - Cast Strike"),
(14342,0,1,0,0,0,100,0,4000,11000,12000,15000,11,13583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ragepaw - In Combat - Cast Curse of the Deadwood");
-- Mongress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14344;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14344 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14344,0,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mongress - Between 0-30% Health - Cast Enrage (No Repeat)"),
(14344,0,1,0,9,0,100,0,0,5,12000,14500,11,31279,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mongress - Within 0-5 Range - Cast Swipe");
-- Jadefire Satyr
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7105;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7105 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7105,0,0,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Satyr - In Combat - Cast Jadefire");
-- Jadefire Rogue
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7106;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7106 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7106,0,0,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Rogue - In Combat - Cast Jadefire"),
(7106,0,1,0,67,0,100,0,6000,11000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Rogue - On Behind Target - Cast Backstab"),
(7106,0,2,0,0,0,100,0,4000,7000,9000,12000,11,13579,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Rogue - In Combat - Cast Gouge");
-- Jadefire Trickster
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7107;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7107 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7107,0,0,0,0,0,100,0,5000,9000,21000,25000,11,13338,0,0,0,0,0,4,0,0,0,0,0,0,0,"Jadefire Trickster - In Combat - Cast Curse of Tongues"),
(7107,0,1,0,9,0,100,0,0,30,120000,125000,11,11980,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Trickster - Within 0-30 Range - Cast Curse of Weakness"),
(7107,0,2,0,0,0,100,0,9000,14000,15000,18000,11,12888,0,0,0,0,0,5,0,0,0,0,0,0,0,"Jadefire Trickster - In Combat - Cast Cause Insanity"),
(7107,0,3,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Trickster - In Combat - Cast Jadefire");
-- Jadefire Betrayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7108;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7108 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7108,0,0,0,9,0,100,0,0,5,7000,11000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Betrayer - Within 0-5 Range - Cast Cleave"),
(7108,0,1,0,0,0,100,0,5000,8000,18000,22000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Betrayer - In Combat - Cast Rend"),
(7108,0,2,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Betrayer - In Combat - Cast Jadefire");
-- Jadefire Felsworn
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7109;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7109 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7109,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Felsworn - In Combat - Cast Shadow Bolt"),
(7109,0,1,0,0,0,100,0,6000,9000,16000,19000,11,13578,2,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Felsworn - In Combat - Cast Jadefire"),
(7109,0,2,0,0,0,100,0,7000,11000,21000,24000,11,11443,2,0,0,0,0,4,0,0,0,0,0,0,0,"Jadefire Felsworn - In Combat - Cast Cripple");
-- Jadefire Shadowstalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7110;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7110 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7110,0,0,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Shadowstalker - In Combat - Cast Jadefire"),
(7110,0,1,0,25,0,100,1,0,0,0,0,11,5916,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Shadowstalker - On Reset - Cast Shadowstalker Stealth");
-- Jadefire Hellcaller
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7111;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7111 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7111,0,0,0,0,0,100,0,0,0,3400,4800,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jadefire Hellcaller - In Combat CMC - Cast Fireball"),
(7111,0,1,0,0,0,100,0,9000,13000,18000,22000,11,11990,1,0,0,0,0,4,0,0,0,0,0,0,0,"Jadefire Hellcaller - In Combat - Cast Rain of Fire"),
(7111,0,2,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jadefire Hellcaller - In Combat - Cast Jadefire");
-- Xavathras
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9454;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9454 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9454,0,0,0,9,0,100,0,0,5,21000,26000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Xavathras - Within 0-5 Range - Cast Rend"),
(9454,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Xavathras - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Alshirr Banebreath
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14340;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14340 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14340,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Alshirr Banebreath - In Combat - Cast Shadow Bolt"),
(14340,0,1,0,0,0,100,0,6000,9000,16000,19000,11,13578,2,0,0,0,0,1,0,0,0,0,0,0,0,"Alshirr Banebreath - In Combat - Cast Jadefire"),
(14340,0,2,0,0,0,100,0,9000,13000,19000,22000,11,11962,2,0,0,0,0,4,0,0,0,0,0,0,0,"Alshirr Banebreath - In Combat - Cast Immolate");
-- Tainted Ooze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7092;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7092 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7092,0,0,0,9,0,100,0,0,5,180000,180000,11,3335,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tainted Ooze - Within 0-5 Range - Cast Dark Sludge");
-- Vile Ooze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7093;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7093 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7093,0,0,0,0,0,100,0,0,0,3400,4700,11,21067,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Ooze - In Combat - Cast Poison Bolt"),
(7093,0,1,0,9,0,100,0,0,5,11000,14000,11,22595,2,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Ooze - Within 0-5 Range - Cast Poison Shock");
-- The Ongar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14345;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14345 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14345,0,0,0,9,0,100,0,0,5,180000,180000,11,3335,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Ongar - Within 0-5 Range - Cast Dark Sludge");
-- Jaedenar Cultist
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7112;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7112 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7112,0,0,0,0,0,100,0,0,0,3400,4700,11,20825,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Cultist - In Combat - Cast Shadow Bolt"),
(7112,0,1,0,0,0,100,0,9000,14000,22000,25000,11,11639,2,0,0,0,0,4,0,0,0,0,0,0,0,"Jaedenar Cultist - In Combat - Cast Shadow Word: Pain"),
(7112,0,2,0,0,0,100,0,6000,9000,16000,19000,11,11980,2,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Cultist - In Combat - Cast Curse of Weakness"),
(7112,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jaedenar Cultist - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Jaedenar Adept
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7115;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7115 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7115,0,0,0,0,0,100,0,0,0,3400,4700,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Adept - In Combat - Cast Fireball"),
(7115,0,1,0,0,0,100,0,11000,15000,12000,16000,11,20832,2,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Adept - In Combat - Cast Fire Blast"),
(7115,0,2,0,9,0,100,0,0,5,16000,21000,11,14514,2,0,0,0,0,1,0,0,0,0,0,0,0,"Jaedenar Adept - Within 0-5 Range - Cast Blink"),
(7115,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jaedenar Adept - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Jaedenar Guardian
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7113;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7113 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7113,0,0,0,9,0,100,0,0,5,9000,13000,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Guardian - Within 0-5 Range - Cast Shield Bash"),
(7113,0,1,0,0,0,100,0,5000,9000,13000,17000,11,3248,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jaedenar Guardian - In Combat - Cast Improved Blocking");
-- Jaedenar Hound
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7125;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7125 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7125,0,0,0,9,0,100,0,0,30,9000,15000,11,13321,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Hound - Within 0-30 Range - Cast Mana Burn");
-- Jaedenar Enforcer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7114;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7114 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7114,0,0,0,9,0,100,0,0,5,17000,21000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Enforcer - Within 0-5 Range - Cast Rend");
-- Jaedenar Darkweaver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7118;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7118 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7118,0,0,0,0,0,100,0,0,0,3400,4700,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Darkweaver - In Combat - Cast Shadow Bolt"),
(7118,0,1,0,0,0,100,0,9000,13000,21000,26000,11,11962,2,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Darkweaver - In Combat - Cast Immolate"),
(7118,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jaedenar Darkweaver - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Jaedenar Legionnaire
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9862;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9862 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9862,0,0,0,9,0,100,0,0,8,12000,17000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jaedenar Legionnaire - Within 0-8 Range - Cast Uppercut");
-- Prince Xavalis
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9877;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9877 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9877,0,0,0,0,0,100,0,9000,13000,19000,22000,11,11962,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prince Xavalis - In Combat - Cast Immolate"),
(9877,0,1,0,0,0,100,0,6000,9000,16000,19000,11,13578,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prince Xavalis - In Combat - Cast Jadefire");
-- Rakaiah
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9518;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9518 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9518,0,0,0,9,0,100,0,0,5,5000,9000,11,15968,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rakaiah - Within 0-5 Range - Cast Lash of Pain"),
(9518,0,1,0,0,0,100,0,5000,8000,14000,19000,11,17227,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rakaiah - In Combat - Cast Curse of Weakness");
-- Shadow Lord Feldan
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9517;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9517 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9517,0,0,0,0,0,100,0,0,0,3400,4700,11,20825,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Lord Feldan - In Combat - Cast Shadow Bolt"),
(9517,0,1,0,0,0,100,0,9000,14000,11000,15000,11,9081,2,0,0,0,0,1,0,0,0,0,0,0,0,"Shadow Lord Feldan - In Combat - Cast Shadow Bolt Volley"),
(9517,0,2,0,0,0,100,0,12000,16000,10000,13000,11,16583,2,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Lord Feldan - In Combat - Cast Shadow Shock");
-- Salia
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9860;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9860 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9860,0,0,0,9,0,100,0,0,20,18000,24000,11,12888,0,0,0,0,0,4,1,0,0,0,0,0,0,"Salia - Within 0-20 Range - Cast Cause Insanity");
-- Moora
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9861;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9861 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9861,0,0,0,0,0,100,0,6000,12000,21000,26000,11,11639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Moora - In Combat - Cast Shadow Word: Pain");
-- Ur'dan
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14522;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14522 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14522,0,0,0,1,0,100,1,1000,1000,0,0,11,11939,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ur\'dan - Out of Combat - Cast Summon Imp (No Repeat)"),
(14522,0,1,0,0,0,100,0,0,0,2400,3800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ur\'dan - In Combat CMC - Cast Shadow Bolt"),
(14522,0,2,0,2,0,100,1,0,30,0,0,11,8699,1,0,0,0,0,1,0,0,0,0,0,0,0,"Ur\'dan - Between 0-30% Health - Cast Unholy Frenzy (No Repeat)"),
(14522,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ur\'dan - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Lord Banehollow
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9516;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9516 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9516,0,0,0,9,0,100,0,0,5,12000,21000,11,16247,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Banehollow - Within 0-5 Range - Cast Curse of Thorns"),
(9516,0,1,0,9,0,100,0,0,15,8000,13000,11,17399,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Banehollow - Within 0-15 Range - Cast Shadow Shock");
-- Entropic Horror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9879;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9879 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9879,0,0,0,0,0,100,0,5000,8000,22000,28000,11,2602,2,0,0,0,0,1,0,0,0,0,0,0,0,"Entropic Horror - In Combat - Cast Fire Shield IV");
-- Entropic Beast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9878;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9878 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9878,0,0,0,9,0,100,0,0,30,25000,28000,11,15661,0,0,0,0,0,2,0,0,0,0,0,0,0,"Entropic Beast - Within 0-30 Range - Cast Immolate");
-- Immolatus
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7137;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7137 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7137,0,0,0,9,0,100,0,0,8,10000,14000,11,10101,0,0,0,0,0,2,0,0,0,0,0,0,0,"Immolatus - Within 0-8 Range - Cast Knock Away");
-- Irontree Stomper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7139;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7139 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7139,0,0,0,9,0,100,0,0,5,9000,16000,11,45,0,0,0,0,0,1,0,0,0,0,0,0,0,"Irontree Stomper - Within 0-5 Range - Cast War Stomp");
-- Toxic Horror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7132;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7132 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7132,0,0,0,9,0,100,0,0,5,8000,16000,11,7947,0,0,0,0,0,2,0,0,0,0,0,0,0,"Toxic Horror - Within 0-5 Range - Cast Localized Toxin"),
(7132,0,1,0,0,0,100,0,6000,9000,12000,18000,11,13582,0,0,0,0,0,2,0,0,0,0,0,0,0,"Toxic Horror - In Combat - Cast Deadly Poison");
-- Withered Protector
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7149;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7149 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7149,0,0,0,9,0,100,0,0,5,9000,13000,11,5337,0,0,0,0,0,2,0,0,0,0,0,0,0,"Withered Protector - Within 0-5 Range - Cast Wither Strike"),
(7149,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Withered Protector - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Warpwood Moss Flayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7100;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7100 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7100,0,0,0,9,0,100,0,0,30,21000,25000,11,11922,0,0,0,0,0,4,0,0,0,0,0,0,0,"Warpwood Moss Flayer - Within 0-30 Range - Cast Entangling Roots");
-- Warpwood Shredder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7101;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7101 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7101,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warpwood Shredder - In Combat - Cast Thrash"),
(7101,0,1,0,9,0,100,0,0,5,8000,12000,11,13444,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warpwood Shredder - Within 0-5 Range - Cast Sunder Armor");
-- Dessecus
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7104;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7104 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7104,0,0,0,9,0,100,0,0,30,6000,10000,11,12058,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dessecus - Within 0-30 Range - Cast Chain Lightning"),
(7104,0,1,0,0,0,100,0,6000,11000,16000,21000,11,8293,0,0,0,0,0,4,0,0,0,0,0,0,0,"Dessecus - In Combat - Cast Lightning Cloud");
-- Deadwood Den Watcher
DELETE FROM `smart_scripts` WHERE `entryorguid`=7156 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7156,0,0,0,0,0,100,0,4000,11000,12000,15000,11,13583,32,0,0,0,0,2,0,0,0,0,0,0,0,"Deadwood Warrior - In Combat - Cast Curse of the Deadwood");
-- Deadwood Avenger
DELETE FROM `smart_scripts` WHERE `entryorguid`=7157 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7157,0,0,0,0,0,100,0,4000,11000,12000,15000,11,13583,32,0,0,0,0,2,0,0,0,0,0,0,0,"Deadwood Warrior - In Combat - Cast Curse of the Deadwood");
-- Deadwood Shaman
DELETE FROM `smart_scripts` WHERE `entryorguid`=7158 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7158,0,0,0,0,0,100,0,0,0,3400,4700,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Deadwood Shaman - In Combat - Cast Lightning Bolt"),
(7158,0,1,0,0,0,100,0,4000,11000,12000,15000,11,13583,2,0,0,0,0,4,0,0,0,0,0,0,0,"Deadwood Shaman - In Combat - Cast Curse of the Deadwood"),
(7158,0,2,0,0,0,100,0,5500,9500,6500,9500,11,12058,2,0,0,0,0,4,0,0,0,0,0,0,0,"Deadwood Shaman - In Combat - Cast Chain Lightning"),
(7158,0,3,0,1,0,100,0,500,1000,600000,600000,11,13585,0,0,0,0,0,1,0,0,0,0,0,0,0,"Deadwood Shaman - Out of Combat - Cast Lightning Shield"),
(7158,0,4,0,16,0,100,0,13585,1,15000,30000,11,13585,0,0,0,0,0,1,0,0,0,0,0,0,0,"Deadwood Shaman - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield");
-- Chieftain Bloodmaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9462;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9462 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9462,0,0,0,2,0,100,1,0,30,0,0,11,5915,0,0,0,0,0,1,0,0,0,0,0,0,0,"Chieftain Bloodmaw - Between 0-30% Health - Cast Crazed (No Repeat)"),
(9462,0,1,0,0,0,100,0,4000,11000,12000,15000,11,13583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chieftain Bloodmaw - In Combat - Cast Curse of the Deadwood"),
(9462,0,2,0,9,0,100,0,0,30,15000,18000,11,15117,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chieftain Bloodmaw - Within 0-30 Range - Cast Chain Lightning");
-- Winterfall Runner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10916;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10916 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10916,0,0,0,1,0,100,0,1000,1000,1200000,1200000,11,17205,0,0,0,0,0,1,0,0,0,0,0,0,0,"Winterfall Runner - Out of Combat - Cast Winterfall Firewater");
-- Random movement for some creatures
UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=51897;
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `guid` IN (40656, 51895);

/* Stranglethorn Vale */

-- Elder Saltwater Crocolisk
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2635;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2635 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2635,0,0,0,0,0,100,0,3000,8000,13000,24000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,'Elder Saltwater Crocolisk - In Combat - Cast \'Tendon Rip\' (No Repeat)');
-- Bloodscalp Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=595;
DELETE FROM `smart_scripts` WHERE `entryorguid`=595 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(595,0,0,0,0,0,100,0,0,0,2100,4800,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,'Bloodscalp Hunter - In Combat CMC - Cast \'Throw\''),
(595,0,1,0,0,0,100,0,9500,24100,18500,39800,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,'Bloodscalp Hunter - In Combat - Cast \'Net\''),
(595,0,2,0,2,0,100,1,0,30,0,0,11,8599,1,0,0,0,0,1,0,0,0,0,0,0,0,'Bloodscalp Hunter - Between 0-30% Health - Cast \'Enrage\' (No Repeat)');
-- Saltscale Oracle
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=873;
DELETE FROM `smart_scripts` WHERE `entryorguid`=873 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(873,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,'Saltscale Oracle - In Combat CMC - Cast \'Lightning Bolt\''),
(873,0,1,0,14,0,100,0,700,40,25000,35000,11,11986,1,0,0,0,0,7,0,0,0,0,0,0,0,'Saltscale Oracle - Friendly At 700 Health - Cast \'Healing Wave\''),
(873,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Saltscale Oracle - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Saltscale Tide Lord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=875;
DELETE FROM `smart_scripts` WHERE `entryorguid`=875 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(875,0,0,0,0,0,100,0,1000,1000,1800000,1800000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,'Saltscale Tide Lord - Out of Combat - Cast \'Frost Armor\''),
(875,0,1,0,0,0,100,0,0,0,2400,3800,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,'Saltscale Tide Lord - In Combat CMC - Cast \'Frostbolt\''),
(875,0,2,0,0,0,100,0,6000,9000,15000,18500,11,11831,1,0,0,0,0,1,0,0,0,0,0,0,0,'Saltscale Tide Lord - In Combat - Cast \'Frost Nova\''),
(875,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Saltscale Tide Lord - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Saltscale Forager
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=877;
DELETE FROM `smart_scripts` WHERE `entryorguid`=877 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(877,0,0,0,9,0,100,0,0,5,20000,30000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,'Saltscale Forager - Within 0-5 Range - Cast \'Rend\''),
(877,0,1,0,0,0,100,0,2000,3000,4000,9000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,'Saltscale Forager - In Combat - Cast \'Poison\''),
(877,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'Saltscale Forager - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Saltscale Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=879;
DELETE FROM `smart_scripts` WHERE `entryorguid`=879 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(879,0,0,0,0,0,100,0,0,0,2600,4800,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,'Saltscale Hunter - In Combat CMC - Cast \'Throw\''),
(879,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Saltscale Hunter - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Saltscale Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=871;
DELETE FROM `smart_scripts` WHERE `entryorguid`=871 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(871,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'Saltscale Warrior - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Kurzen Subchief
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=978;
DELETE FROM `smart_scripts` WHERE `entryorguid`=978 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(978,0,0,0,0,0,100,0,6000,11000,20000,30000,11,8053,0,0,0,0,0,2,0,0,0,0,0,0,0,'Kurzen Subchief - In Combat - Cast \'Flame Shock\'');
-- Kurzen Shadow Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=979;
DELETE FROM `smart_scripts` WHERE `entryorguid`=979 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(979,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Kurzen Shadow Hunter - In Combat CMC - Cast \'Shoot\''),
(979,0,1,0,0,0,100,0,9000,14000,9000,14000,11,8806,32,0,0,0,0,5,0,0,0,0,0,0,0,'Kurzen Shadow Hunter - In Combat - Cast \'Poisoned Shot\''),
(979,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kurzen Shadow Hunter - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Colonel Kurzen
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=813;
DELETE FROM `smart_scripts` WHERE `entryorguid`=813 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(813,0,0,0,0,0,100,0,8000,12000,18000,25000,11,8817,0,0,0,0,0,1,0,0,0,0,0,0,0,'Colonel Kurzen - In Combat - Cast \'Smoke Bomb\''),
(813,0,1,0,24,0,100,0,8817,0,100,100,11,8818,32,0,0,0,0,2,0,0,0,0,0,0,0,'Colonel Kurzen - On Target Has \'Smoke Bomb\' Aura - Cast \'Garrote\'');
-- Mosh'Ogg Shaman
DELETE FROM `creature_text` WHERE `entry`=679;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(679,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,0,"Mosh\'Ogg Shaman"),
(679,0,1,"Me smash! You die!",12,0,100,0,0,0,0,"Mosh\'Ogg Shaman"),
(679,0,2,"I\'ll crush you!",12,0,100,0,0,0,0,"Mosh\'Ogg Shaman");
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=679;
DELETE FROM `smart_scripts` WHERE `entryorguid`=679 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(679,0,0,0,0,0,100,0,6500,10000,9500,12500,11,12058,0,0,0,0,0,2,0,0,0,0,0,0,0,'Mosh\'Ogg Shaman - In Combat - Cast \'Chain Lightning\''),
(679,0,1,0,2,0,100,0,0,30,34000,38000,11,6742,1,0,0,0,0,1,0,0,0,0,0,0,0,'Mosh\'Ogg Shaman - Between 0-30% Health - Cast \'Bloodlust\''),
(679,0,2,0,0,0,100,0,9500,18000,33000,45000,11,11899,0,0,0,0,0,1,0,0,0,0,0,0,0,'Mosh\'Ogg Shaman - In Combat - Cast \'Healing Ward\''),
(679,0,3,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosh\'Ogg Shaman - On Aggro - Say Line 0");
-- Verifonix
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14492;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14492 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14492,0,0,0,9,0,100,0,0,5,23800,28200,11,12097,0,0,0,0,0,2,0,0,0,0,0,0,0,'Verifonix - Within 0-5 Range - Cast \'Pierce Armor\'');
-- Mosh'Ogg Mauler --> Add Texts on Aggro
DELETE FROM `creature_text` WHERE `entry`=678;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(678,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,0,"Mosh\'Ogg Mauler"),
(678,0,1,"Me smash! You die!",12,0,100,0,0,0,0,"Mosh\'Ogg Mauler"),
(678,0,2,"I\'ll crush you!",12,0,100,0,0,0,0,"Mosh\'Ogg Mauler");
DELETE FROM `smart_scripts` WHERE `entryorguid`=678 AND `id`=1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(678,0,1,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosh\'Ogg Mauler - On Aggro - Say Line 0");
-- Mosh'Ogg Lord --> Add Texts on Aggro
DELETE FROM `creature_text` WHERE `entry`=680;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(680,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,0,"Mosh\'Ogg Lord"),
(680,0,1,"Me smash! You die!",12,0,100,0,0,0,0,"Mosh\'Ogg Lord"),
(680,0,2,"I\'ll crush you!",12,0,100,0,0,0,0,"Mosh\'Ogg Lord");
DELETE FROM `smart_scripts` WHERE `entryorguid`=680 AND `id`=1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(680,0,1,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosh\'Ogg Lord - On Aggro - Say Line 0");
-- Mosh'Ogg Warmonger --> Add Texts on Aggro
DELETE FROM `creature_text` WHERE `entry`=709;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(709,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,0,"Mosh\'Ogg Warmonger"),
(709,0,1,"Me smash! You die!",12,0,100,0,0,0,0,"Mosh\'Ogg Warmonger"),
(709,0,2,"I\'ll crush you!",12,0,100,0,0,0,0,"Mosh\'Ogg Warmonger");
DELETE FROM `smart_scripts` WHERE `entryorguid`=709 AND `id`=1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(709,0,1,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosh\'Ogg Warmonger - On Aggro - Say Line 0");
-- Mosh'Ogg Spellcrafter --> Add Texts on Aggro
DELETE FROM `creature_text` WHERE `entry`=710;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(710,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,0,"Mosh\'Ogg Spellcrafter"),
(710,0,1,"Me smash! You die!",12,0,100,0,0,0,0,"Mosh\'Ogg Spellcrafter"),
(710,0,2,"I\'ll crush you!",12,0,100,0,0,0,0,"Mosh\'Ogg Spellcrafter");
DELETE FROM `smart_scripts` WHERE `entryorguid`=710 AND `id`=3 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(710,0,3,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosh\'Ogg Spellcrafter - On Aggro - Say Line 0");

/* Hinterlands */

-- Trained Razorbeak
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2657;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2657 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2657,0,0,0,9,0,100,0,0,5,15000,19000,11,3147,0,0,0,0,0,2,0,0,0,0,0,0,0,"Trained Razorbeak - In Combat - Cast Rend Flesh");
-- Mangy Silvermane
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2923;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2923 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2923,0,0,0,0,0,100,0,4000,4500,22000,25000,11,8139,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mangy Silvermane - In Combat - Cast Fevered Fatigue");
-- Silvermane Howler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2925;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2925 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2925,0,0,0,0,0,100,0,2000,4500,12000,13000,11,32919,0,0,0,0,0,2,0,0,0,0,0,0,0,"Silvermane Howler - In Combat - Cast Snarl"),
(2925,0,1,0,0,0,100,0,6000,9000,18000,22000,11,3149,0,0,0,0,0,1,0,0,0,0,0,0,0,"Silvermane Howler - In Combat - Cast Furious Howl");
-- Silvermane Stalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2926;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2926 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2926,0,0,0,0,0,100,0,4000,5000,17000,19000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Silvermane Stalker - In Combat - Cast Infected Bite"),
(2926,0,1,0,25,0,100,1,0,0,0,0,11,6408,0,0,0,0,0,1,0,0,0,0,0,0,0,"Silvermane Stalker - On Reset - Cast Faded (No Repeat)");
-- Old Cliff Jumper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8211;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8211 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8211,0,0,0,9,0,100,0,0,8,15000,18000,11,3264,0,0,0,0,0,1,0,0,0,0,0,0,0,"Old Cliff Jumper - Within 0-8 Range - Cast Blood Howl"),
(8211,0,1,0,9,0,100,0,0,5,20000,25000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Old Cliff Jumper - Within 0-5 Range - Cast Tendon Rip");
-- Vicious Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2927;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2927 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2927,0,0,0,9,0,100,0,0,5,18000,24000,11,7938,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vicious Owlbeast - Within 0-5 Range - Cast Fatal Bite");
-- Primitive Owlbeast
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2928;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2928 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2928,0,0,0,9,0,100,0,0,5,13000,16000,11,3252,0,0,0,0,0,2,0,0,0,0,0,0,0,"Primitive Owlbeast - Within 0-5 Range - Cast Shred");
-- Razortalon
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8210;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8210 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8210,0,0,0,9,0,100,0,0,5,9000,12000,11,13584,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razortalon - Within 0-5 Range - Cast Strike"),
(8210,0,1,0,9,0,100,0,0,5,20000,25000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razortalon - Within 0-5 Range - Cast Tendon Rip"),
(8210,0,2,0,0,0,100,0,6000,11000,18000,21000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razortalon - In Combat - Cast Rend");
-- Jade Ooze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2656;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2656 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2656,0,0,0,0,0,100,0,4000,6000,16000,18000,11,6907,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jade Ooze - In Combat - Cast Diseased Slime");
-- Green Sludge
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2655;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2655 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2655,0,0,0,0,0,100,0,4000,6000,12000,16000,11,9459,0,0,0,0,0,2,0,0,0,0,0,0,0,"Green Sludge - In Combat - Cast Corrosive Ooze");
-- The Reak
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8212;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8212 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8212,0,0,0,0,0,100,0,6000,8000,18000,24000,11,7279,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Reak - In Combat - Cast Black Sludge"),
(8212,0,1,0,0,0,100,0,4000,6000,28000,32000,11,21062,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Reak - In Combat - Cast Putrid Breath");
-- Witherbark Scalper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2649;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2649 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2649,0,0,0,0,0,100,0,0,0,2100,4800,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Scalper - In Combat CMC - Cast Throw"),
(2649,0,1,0,12,0,100,1,0,20,0,0,11,7160,1,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Scalper - Target Between 0-20% Health - Cast Execute (No Repeat)"),
(2649,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Scalper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Zealot
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2650;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2650 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2650,0,0,0,2,0,100,1,0,30,0,0,11,8599,1,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Zealot - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Witherbark Hideskinner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2651;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2651 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2651,0,0,0,9,0,100,0,0,5,5000,9000,11,8721,0,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Hideskinner - In Combat - Cast Backstab"),
(2651,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Hideskinner - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Venomblood
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2652;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2652 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2652,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Venomblood - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Sadist
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2653;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2653 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2653,0,0,0,1,0,100,1,1000,1000,0,0,11,7165,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Sadist - Out of Combat - Cast Battle Stance (No Repeat)"),
(2653,0,1,0,9,0,100,0,0,5,6000,9000,11,25710,0,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Sadist - Within 0-5 Range - Cast Heroic Strike (No Repeat)"),
(2653,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Sadist - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Caller
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2654;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2654 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2654,0,0,0,0,0,100,0,0,0,3400,4800,11,20825,64,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Caller - Combat CMC - Cast Shadow Bolt"),
(2654,0,1,0,4,0,100,0,0,0,0,0,11,11017,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Caller - On Aggro - Summon Witherbark Felhunter"),
(2654,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherbark Caller - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Witherbark Felhunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7767;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7767 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7767,0,0,0,9,0,100,0,0,10,8000,14000,11,2691,0,0,0,0,0,2,0,0,0,0,0,0,0,"Witherbark Felhunter - Within 0-10 Range - Cast Mana Burn");
-- Witherbark Broodguard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2686;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2686 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2686,0,0,0,6,0,100,0,0,0,0,0,11,11018,0,0,0,0,0,7,0,0,0,0,0,0,0,"Witherbark Broodguard - On Death - Summon Witherbark Bloodlings");
-- Witherheart the Stalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8218;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8218 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8218,0,0,0,25,0,100,0,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witherheart the Stalker - On Reset - Cast Sneak"),
(8218,0,1,0,67,0,100,0,5000,9000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Witherheart the Stalker - On Behind Target - Cast Backstab");
-- Zul'arek Hatefowler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8219;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8219 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8219,0,0,0,9,0,100,0,0,30,9000,14000,11,17228,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zul\'arek Hatefowler - Within 0-30 Range - Cast Shadow Bolt Volley");
-- Witch Doctor Mai'jin
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=17235;
DELETE FROM `smart_scripts` WHERE `entryorguid`=17235 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17235,0,0,0,0,0,100,0,15000,25000,30000,45000,11,5605,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witch Doctor Mai\'jin - In Combat - Cast Healing Ward (No Repeat)"),
(17235,0,1,0,0,0,100,0,6000,8000,25000,28000,11,8190,0,0,0,0,0,1,0,0,0,0,0,0,0,"Witch Doctor Mai\'jin - In Combat - Cast Magma Totem (No Repeat)");
-- Tcha'kaz
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=17236;
DELETE FROM `smart_scripts` WHERE `entryorguid`=17236 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17236,0,0,0,6,0,100,0,0,0,0,0,11,11018,0,0,0,0,0,7,0,0,0,0,0,0,0,"Tcha\'kaz - On Death - Summon Witherbark Bloodlings");
-- Highvale Outrunner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2691;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2691 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2691,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Highvale Outrunner - In Combat CMC - Cast Shoot"),
(2691,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highvale Outrunner - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Highvale Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2692;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2692 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2692,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highvale Scout - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Highvale Marksman
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2693;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2693 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2693,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Highvale Marksman - In Combat CMC - Cast Shoot"),
(2693,0,1,0,9,0,100,0,5,30,9000,13000,11,14443,1,0,0,0,0,2,0,0,0,0,0,0,0,"Highvale Marksman - Within 5-30 Range - Cast Multi-Shot"),
(2693,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highvale Marksman - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Highvale Ranger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2694;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2694 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2694,0,0,0,9,0,100,0,0,30,30000,35000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Highvale Ranger - Within 0-30 Range - Cast Faerie Fire");
-- Vilebranch Soothsayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4467;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4467 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4467,0,0,0,0,0,100,0,0,0,3400,4700,11,20824,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Soothsayer - In Combat - Cast Lightning Bolt"),
(4467,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Soothsayer - Between 0-15% Health - Flee For Assist (No Repeat)"),
(4467,0,2,0,14,0,100,0,2500,40,20000,30000,11,10395,1,0,0,0,0,7,0,0,0,0,0,0,0,"Vilebranch Soothsayer - Friendly At 40% Health - Cast Healing Wave");
-- Vilebranch Scalper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4466;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4466 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4466,0,0,0,12,0,100,1,0,20,0,0,11,7160,1,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Scalper - Target Between 0-20% Health - Cast Execute (No Repeat)"),
(4466,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Scalper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Qiaga the Keeperer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7996;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7996 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7996,0,0,0,0,0,100,0,0,0,3400,4800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Qiaga the Keeper - In Combat CMC - Cast Shadow Bolt"),
(7996,0,1,0,0,0,100,0,4200,7700,7100,16200,11,11639,32,0,0,0,0,2,0,0,0,0,0,0,0,"Qiaga the Keeper - In Combat - Cast Shadow Word: Pain"),
(7996,0,2,0,14,0,100,0,1000,40,15000,19000,11,11640,1,0,0,0,0,7,0,0,0,0,0,0,0,"Qiaga the Keeper - Friendly At 40% Health - Cast Renew"),
(7996,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Qiaga the Keeperer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Morta'gya the Keeperer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8636;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8636 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8636,0,0,0,0,0,100,0,0,0,3400,4800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Morta\'gya the Keeper - In Combat CMC - Cast Shadow Bolt"),
(8636,0,1,0,0,0,100,0,4200,7700,7100,16200,11,11639,32,0,0,0,0,2,0,0,0,0,0,0,0,"Morta\'gya the Keeper - In Combat - Cast Shadow Word: Pain"),
(8636,0,2,0,14,0,100,0,1000,40,15000,19000,11,11640,1,0,0,0,0,7,0,0,0,0,0,0,0,"Morta\'gya the Keeper - Friendly At 40% Health - Cast Renew"),
(8636,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Morta\'gya the Keeper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Retherokk the Berserker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8216;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8216 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8216,0,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Retherokk the Berserker - Between 0-30% Health - Cast Enrage (No Repeat)"),
(8216,0,1,0,0,0,100,0,2000,3000,8000,9000,11,3391,0,0,0,0,0,1,0,0,0,0,0,0,0,"Retherokk the Berserker - In Combat - Cast Thrash");
-- Gammerita
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7977;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7977 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7977,0,0,0,9,0,100,0,0,5,45000,45000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gammerita - Within 0-5 Range - Cast Pierce Armor");
-- Jade Sludge
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4468;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4468 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4468,0,0,0,9,0,100,0,0,10,15000,29000,11,6814,0,0,0,0,0,2,0,0,0,0,0,0,0,"Jade Sludge - Within 0-10 Range - Cast Sludge Toxin");
-- Emerald Ooze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4469;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4469 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4469,0,0,0,9,0,100,0,0,5,12000,19000,11,8245,0,0,0,0,0,2,0,0,0,0,0,0,0,"Emerald Ooze - Within 0-5 Range - Cast Corrosive Acid");
-- Vilebranch Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4465;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4465 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4465,0,0,0,9,0,100,0,0,5,5000,9000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Warrior - Within 0-5 Range - Cast Strike"),
(4465,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Warrior - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Witch Doctor
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2640;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2640 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2640,0,0,0,0,0,100,0,0,0,3400,4800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Witch Doctor - In Combat CMC - Cast Shadow Bolt"),
(2640,0,1,0,14,0,100,0,1200,40,13000,17000,11,8005,0,0,0,0,0,7,0,0,0,0,0,0,0,"Vilebranch Witch Doctor - Friendly at 1200 Health - Cast Healing Wave"),
(2640,0,2,0,0,0,100,1,9000,13000,22000,28000,11,18503,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Witch Doctor - In Combat CMC - Cast Hex"),
(2640,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Witch Doctor - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Headhunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2641;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2641 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2641,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Headhunter - In Combat CMC - Cast Throw"),
(2641,0,1,0,9,0,100,0,0,5,15000,18000,11,7357,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Headhunter - Within 0-5 Range - Cast Poisonous Stab"),
(2641,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Headhunter - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Shadowcaster
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2642;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2642 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2642,0,0,0,0,0,100,0,0,0,3400,4800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Shadowcaster - In Combat CMC - Cast Shadow Bolt"),
(2642,0,1,0,1,0,100,1,1000,1000,0,0,11,12746,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Shadowcaster - Out of Combat - Cast Summon Voidwalker"),
(2642,0,2,0,0,0,100,0,2500,10000,35000,40000,11,7289,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Shadowcaster - In Combat - Cast Shrink"),
(2642,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Shadowcaster - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Hideskinnerr
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2644;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2644 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2644,0,0,0,67,0,100,0,5000,9000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Hideskinner - On Behind Target - Cast Backstab"),
(2644,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Hideskinnerr - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Shadow Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2645;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2645 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2645,0,0,0,0,0,100,0,0,0,2300,3900,11,15547,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Shadow Hunter - Combat CMC - Cast Shoot"),
(2645,0,1,0,9,0,100,0,0,30,21000,26000,11,14032,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Shadow Hunter - Within 0-30 Range - Cast Shadow Word: Pain"),
(2645,0,2,0,0,0,100,0,4000,9000,15000,21000,11,9657,1,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Shadow Hunter - In Combat - Cast Shadow Shell"),
(2645,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Shadow Hunter - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Mith'rethis the Enchanter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8217;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8217 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8217,0,0,0,0,0,100,0,5000,9000,12000,16000,11,11436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mith\'rethis the Enchanter - In Combat - Cast Slow"),
(8217,0,1,0,9,0,100,0,0,30,24000,29000,11,15654,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mith\'rethis the Enchanter - Within 0-30 Range - Cast Shadow Word: Pain"),
(8217,0,2,0,0,0,100,0,1000,5000,21000,27000,11,3443,1,0,0,0,0,1,0,0,0,0,0,0,0,"Mith\'rethis the Enchanter - In Combat - Cast Enchanted Quickness");
-- Vilebranch Blood Drinker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2646;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2646 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2646,0,0,0,9,0,100,0,0,5,7000,15000,11,11015,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Blood Drinker - Within 0-5 Range - Cast Blood Leech"),
(2646,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Blood Drinker - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Soul Eater
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2647;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2647 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2647,0,0,0,9,0,100,0,0,5,8000,12000,11,11016,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Soul Eater - Within 0-5 Range - Cast Soul Bite"),
(2647,0,1,0,14,0,100,0,600,10,12000,15000,11,7154,1,0,0,0,0,7,0,0,0,0,0,0,0,"Vilebranch Soul Eater - On Friendly at 600 Health - Cast Dark Offering"),
(2647,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Soul Eater - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Aman'zasi Guard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2648;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2648 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2648,0,0,0,0,0,100,0,4000,7000,8000,11000,11,8242,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Aman\'zasi Guard - In Combat - Cast Shield Slam"),
(2648,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Aman\'zasi Guard - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Raiding Wolf
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2681;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2681 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2681,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Raiding Wolf - In Combat - Cast Thrash");
-- Vile Priestess Hexx
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7995;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7995 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7995,0,0,0,9,0,100,0,0,30,9000,12000,11,11639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Priestess Hexx - Within 0-30 Range - Cast Shadow Word: Pain"),
(7995,0,1,0,0,0,100,0,7000,12000,18000,25000,11,11641,1,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Priestess Hexx - In Combat - Cast Hex"),
(7995,0,2,0,14,0,100,0,1200,40,12000,15000,11,11642,0,0,0,0,0,7,0,0,0,0,0,0,0,"Vile Priestess Hexx - Friendly At 1200 Health - Cast Heal"),
(7995,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Priestess Hexx - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Hitah'ya the Keeper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10802;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10802 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10802,0,0,0,9,0,100,0,0,30,21000,25000,11,11639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hitah\'ya the Keeper - Within 0-30 Range - Cast Shadow Word: Pain"),
(10802,0,1,0,0,0,100,0,0,0,3400,4800,11,9613,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hitah\'ya the Keeper - In Combat - Cast Shadow Bolt"),
(10802,0,2,0,14,0,100,0,1400,40,12000,18000,11,11640,0,0,0,0,0,7,0,0,0,0,0,0,0,"Hitah\'ya the Keeper - Friendly At 1400 Health - Cast Renew"),
(10802,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hitah\'ya the Keeper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vilebranch Kidnapper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14748;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14748 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14748,0,0,0,12,0,100,1,0,20,0,0,11,7160,1,0,0,0,0,2,0,0,0,0,0,0,0,"Vilebranch Kidnapper - Target Between 0-20% Health - Cast Execute (No Repeat)"),
(14748,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Kidnapper - Between 0-15% Health - Flee For Assist (No Repeat)"),
(14748,0,2,0,4,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vilebranch Kidnapper - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=14748;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(14748,0,0,"Another fool falls for the trap!",12,0,100,0,0,0,0,"Vilebranch Kidnapper"),
(14748,0,1,"Dinner has arrived!",12,0,100,0,0,0,0,"Vilebranch Kidnapper"),
(14748,0,2,"The High Priestess will feast on your bones!",12,0,100,0,0,0,0,"Vilebranch Kidnapper");

/* Stonetalon Mountains */

-- Cliff Stormer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4008;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4008 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4008,0,0,0,0,0,100,0,3000,5000,6000,8000,11,5401,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cliff Stormer - In Combat - Cast Lizard Bolt");
-- Raging Cliff Stormer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4009;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4009 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4009,0,0,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,2,0,0,0,0,0,0,0,"Raging Cliff Stormer - On Aggro - Cast Rushing Charge"),
(4009,0,1,0,9,0,100,0,0,8,12000,15000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"Raging Cliff Stormer - Within 0-8 Range - Cast Thunderclap");
-- Sorrow Wing
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5928;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5928 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5928,0,0,0,9,0,100,0,0,5,6000,12000,11,3388,32,0,0,0,0,2,0,0,0,0,0,0,0,"Sorrow Wing - In Combat - Cast Deadly Leech Poison"),
(5928,0,1,0,0,0,100,0,11000,18000,12000,15000,11,3405,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sorrow Wing - IC - Cast Soul Rend");
-- Deepmoss Webspinner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4006;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4006 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4006,0,0,0,9,0,100,0,0,30,8000,12000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Deepmoss Webspinner - In Combat - Cast Web");
-- Deepmoss Venomspitter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4007;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4007 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4007,0,0,0,0,0,100,0,0,0,2300,3900,11,7951,64,0,0,0,0,2,0,0,0,0,0,0,0,"Deepmoss Venomspitter - In Combat - Cast Toxic Spit");
-- Young Pridewing
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4011;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4011 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4011,0,0,0,0,0,100,0,5000,8000,12000,18000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Young Pridewing - In Combat - Cast Poison");
-- Pridewing Patriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4015;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4015 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4015,0,0,0,0,0,100,0,5000,8000,12000,18000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Pridewing Patriarch - In Combat - Cast Poison");
-- Pridewing Wyvern
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4012;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4012 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4012,0,0,0,0,0,100,0,5000,8000,12000,18000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Pridewing Wyvern - In Combat - Cast Poison");
-- Pridewing Skyhunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4013;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4013 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4013,0,0,0,0,0,100,0,3000,5000,12000,18000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Pridewing Skyhunter - In Combat - Cast Poison"),
(4013,0,1,0,0,0,100,0,5000,8000,9000,12000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Pridewing Skyhunter - In Combat - Cast Swoop");
-- Deepmoss Hatchling
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4263;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4263 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4263,0,0,0,2,0,50,1,0,30,0,0,11,6536,0,0,0,0,0,1,0,0,0,0,0,0,0,"Deepmoss Hatchling - At 30% HP - Summon Deepmoss Matriarch");
-- Venture Co. Logger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3989;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3989 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3989,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Venture Co. Logger - In Combat CMC - Cast Throw"),
(3989,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Logger - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Operator
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3988;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3988 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3988,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Operator - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Deforester
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3991;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3991 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3991,0,0,0,0,0,100,0,0,0,3400,4800,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Venture Co. Deforester - In Combat - Cast Fireball"),
(3991,0,1,0,0,0,100,0,9000,16000,18000,24000,11,5740,0,0,0,0,0,2,0,0,0,0,0,0,0,"Venture Co. Deforester - In Combat - Cast Rain of Fire"),
(3991,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Deforester - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Engineer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3992;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3992 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3992,0,0,0,0,0,100,0,0,0,2300,3900,11,7978,64,0,0,0,0,2,0,0,0,0,0,0,0,"Venture Co. Engineer - In Combat CMC - Cast Throw Dynamite"),
(3992,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Engineer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Machine Smith
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3993;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3993 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3993,0,0,0,0,0,100,0,5000,9000,70000,85000,11,7979,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Machine Smith - IC - Cast Compact Harvest Reaper"),
(3993,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Machine Smith - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Builder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4070;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4070 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4070,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Venture Co. Builder - In Combat CMC - Cast Shoot"),
(4070,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Builder - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Taskmaster Whipfang
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5932;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5932 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5932,0,0,0,9,0,100,0,0,8,15000,19000,11,16508,0,0,0,0,0,2,0,0,0,0,0,0,0,"Taskmaster Whipfang - Within 0-8 Range - Cast Intimidating Roar"),
(5932,0,1,0,2,0,100,1,0,20,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Taskmaster Whipfang - Between 0-20% Health - Flee For Assist (No Repeat)");
-- Foreman Rigger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5931;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5931 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5931,0,0,0,9,0,100,0,0,20,15500,25300,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Rigger - Within 0-20 Range - Cast Net"),
(5931,0,1,0,9,0,100,0,0,5,45000,45000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Rigger - Within 0-5 Range - Cast Pierce Armor");
-- Windshear Tunnel Rat
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4001;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4001 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4001,0,0,0,0,0,100,0,4000,11000,7000,15000,11,8139,32,0,0,0,0,2,0,0,0,0,0,0,0,"Windshear Tunnel Rat - In Combat - Cast Fevered Fatigue");
-- Windshear Stonecutter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4002;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4002 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4002,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Windshear Stonecutter - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Windshear Geomancer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4003;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4003 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4003,0,0,0,0,0,100,0,0,0,3400,4800,11,20792,64,0,0,0,0,2,0,0,0,0,0,0,0,"Windshear Geomancer - In Combat CMC - Cast Frostbolt"),
(4003,0,1,0,0,0,100,0,4000,11000,7000,15000,11,8139,32,0,0,0,0,2,0,0,0,0,0,0,0,"Windshear Geomancer - In Combat - Cast Fevered Fatigue"),
(4003,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Windshear Geomancer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Windshear Overlord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4004;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4004 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4004,0,0,0,0,0,100,0,1000,3000,30000,45000,11,3631,0,0,0,0,0,1,0,0,0,0,0,0,0,"Windshear Overlord - In Combat - Cast Battle Fury"),
(4004,0,1,0,0,0,100,0,4000,11000,7000,15000,11,8139,32,0,0,0,0,2,0,0,0,0,0,0,0,"Windshear Overlord - In Combat - Cast Fevered Fatigue"),
(4004,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Windshear Overlord - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Grimtotem Brute
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=11912;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11912 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11912,0,0,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Brute - On Aggro - Cast RushIng Charge"),
(11912,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Brute - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Grimtotem Sorcerer
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=11913;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11913 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11913,0,0,0,0,0,100,0,0,0,3400,4800,11,20802,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Sorcerer - In Combat - Cast LightnIng Bolt"),
(11913,0,1,0,2,0,100,0,0,50,18000,21000,11,12160,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Sorcerer - Between 0-50% Health - Cast Rejuvenation"),
(11913,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Sorcerer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Grimtotem Ruffian
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=11910;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11910 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11910,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Ruffian - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Grimtotem Mercenary
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=11911;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11911 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11911,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Mercenary - In Combat - Cast Throw"),
(11911,0,1,0,9,0,100,0,0,5,7000,11000,11,12555,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grimtotem Mercenary - Within 0-5 Range - Cast Pummel"),
(11911,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grimtotem Mercenary - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Rogue Flame Spirit
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4036;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4036 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4036,0,0,0,9,0,100,0,0,30,120000,125000,11,6205,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rogue Flame Spirit - Within 0-30 Range - Cast Curse of Weakness"),
(4036,0,1,0,0,0,100,0,5000,9000,18000,22000,11,1094,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rogue Flame Spirit - In Combat - Cast Immolate");
-- Charred Ancient
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4028;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4028 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4028,0,0,0,9,0,100,0,0,30,14000,20000,11,12747,0,0,0,0,0,2,0,0,0,0,0,0,0,"Charred Ancient - Within 0-30 Range - Cast Entangling Roots");
-- Burning Ravager
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4037;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4037 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4037,0,0,0,0,0,100,0,1000,3000,60000,65000,11,184,0,0,0,0,0,1,0,0,0,0,0,0,0,"BurnIng Ravager - In Combat - Cast Fire Shield II");
-- Young Chimaera
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4032;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4032 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4032,0,0,0,0,0,100,0,3000,4000,6000,8000,11,9532,0,0,0,0,0,2,0,0,0,0,0,0,0,"Young Chimaera - In Combat CMC - Cast Lightning Bolt");
-- Fledgling Chimaera
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4031;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4031 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4031,0,0,0,9,0,100,0,0,30,8000,16000,11,3396,32,0,0,0,0,2,0,0,0,0,0,0,0,"Fledgling Chimaera - Within 0-30 Range - Cast Corrosive Poison");
-- Sap Beast
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4020;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4020 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4020,0,0,0,9,0,100,0,0,5,7000,16000,11,7997,32,0,0,0,0,2,0,0,0,0,0,0,0,"Sap Beast - Within 0-5 Range - Cast Sap Might");
-- Corrosive Sap Beast
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4021;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4021 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4021,0,0,0,9,0,100,0,0,30,5000,11000,11,3396,32,0,0,0,0,2,0,0,0,0,0,0,0,"Corrosive Sap Beast - Within 0-30 Range - Cast Corrosive Poison");
-- Vengeful Ancient
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4030;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4030 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4030,0,0,0,9,0,100,0,0,5,17000,25000,11,6909,32,0,0,0,0,2,0,0,0,0,0,0,0,"Vengeful Ancient - Within 0-5 Range - Cast Curse of Thorns");
-- Burning Destroyer
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4038;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4038 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4038,0,0,0,0,0,100,0,0,0,3400,4800,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Burning Destroyer - In Combat CMC - Cast Fireball"),
(4038,0,1,0,0,0,100,0,7000,11000,13000,16000,11,8000,0,0,0,0,0,2,0,0,0,0,0,0,0,"Burning Destroyer - In Combat CMC - Cast Area Burn");
-- Sister Riven
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=5930;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5930 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5930,0,0,0,4,0,100,1,0,0,0,0,11,184,2,0,0,0,0,1,0,0,0,0,0,0,0,"Sister Riven - On Aggro - Cast Fire Shield"),
(5930,0,1,0,9,0,100,0,0,20,8000,12000,11,3356,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sister Riven - Within 0-20 Range - Cast Flame Lash"),
(5930,0,2,0,0,0,100,0,7000,10000,30000,30000,11,6725,0,0,0,0,0,4,0,0,0,0,0,0,0,"Sister Riven - In Combat - Cast Flame Spike");
-- Fey Dragon
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4016;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4016 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4016,0,0,0,9,0,100,1,0,30,0,0,11,7994,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fey Dragon - Within 0-30 Range - Cast Nullify Mana (No Repeat)");
-- Wily Fey Dragon
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4017;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4017 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4017,0,0,0,9,0,100,0,0,30,8000,11000,11,17630,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wily Fey Dragon - Within 0-30 Range - Cast Mana Burn");
-- Cenarion Botanist
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4051;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4051 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4051,0,0,0,0,0,100,0,0,0,3400,4800,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cenarion Botanist - In Combat CMC - Cast Wrath"),
(4051,0,1,0,2,0,100,0,0,50,16100,17400,11,1430,1,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Botanist - Between 0-50% Health - Cast Rejuvenation"),
(4051,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cenarion Botanist - Between 0-15% Health - Flee for Assist (No Repeat)");
-- Cenarion Caretaker
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4050;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4050 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4050,0,0,0,1,0,100,0,0,0,300000,300000,11,7090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Caretaker - Out of Combat - Cast Bear Form"),
(4050,0,1,0,4,0,100,1,0,0,0,0,11,782,1,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Caretaker - On Aggro - Cast Thorns"),
(4050,0,2,0,9,0,100,0,0,5,7000,10000,11,12161,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cenarion Caretaker - Within 0-5 Range - Cast Maul"),
(4050,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cenarion Protector - Between 0-15% Health - Flee for Assist (No Repeat)"),
(4050,0,4,0,2,0,100,1,0,15,0,0,28,7090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Protector - Between 0-15% Health - Remove Bear Form");
-- Gatekeeper Kordurus
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4409;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4409 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4409,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gatekeeper Kordurus - Between 0-15% Health - Flee for Assist (No Repeat)");
-- Rynthariel the Keymaster
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=8518;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8518 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8518,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Rynthariel the Keymaster - In Combat CMC - Cast Throw"),
(8518,0,1,0,9,0,100,0,0,30,10000,16000,11,7992,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rynthariel the Keymaster - Within 0-30 Range - Cast Slowing Poison"),
(8518,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rynthariel the Keymaster - Between 0-15% Health - Flee for Assist (No Repeat)");
-- Cenarion Druid
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4052;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4052 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4052,0,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Druid - On Aggro - Set Event Phase 1"),
(4052,0,1,0,0,1,100,0,0,0,3400,4700,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cenarion Druid - In Combat (Phase 1) - Cast Wrath"),
(4052,0,2,0,2,0,100,1,0,50,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Druid - Between 0-50% Health - Set Event Phase 2"),
(4052,0,3,0,0,2,100,1,0,0,0,0,11,5759,1,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Druid - In Combat (Phase 2) - Cast Cat Form"),
(4052,0,5,0,0,2,100,1,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Druid - In Combat (Phase 2) - Enable Combat Movement"),
(4052,0,4,0,0,2,100,0,12000,16000,30000,35000,11,5217,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cenarion Druid - In Combat (Phase 2) - Cast Tiger\'s Fury");
-- Mirkfallon Dryad
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4061;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4061 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4061,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Mirkfallon Dryad - In Combat CMC - Cast Throw"),
(4061,0,1,0,9,0,100,0,0,30,10000,16000,11,7992,32,0,0,0,0,2,0,0,0,0,0,0,0,"Mirkfallon Dryad - Within 0-30 Range - Cast Slowing Poison"),
(4061,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mirkfallon Dryad - Between 0-15% Health - Flee for Assist (No Repeat)");
-- Brother Ravenoak
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=5915;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5915 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5915,0,0,0,4,0,100,1,0,0,0,0,11,7090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Brother Ravenoak - On Aggro - Cast Bear Form"),
(5915,0,1,0,9,0,100,0,0,5,12000,15000,11,12161,0,0,0,0,0,2,0,0,0,0,0,0,0,"Brother Ravenoak - Within 0-5 Range - Cast Maul"),
(5915,0,2,0,9,0,100,0,0,5,17000,22000,11,8716,0,0,0,0,0,2,0,0,0,0,0,0,0,"Brother Ravenoak - Within 0-5 Range - Cast Low Swipe"),
(5915,0,3,0,1,0,100,0,30000,30000,480000,480000,11,7090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Brother Ravenoak - Out of Combat - Cast Bear Form"),
(5915,0,4,0,2,0,100,0,0,75,21000,26000,11,2090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Brother Ravenoak - Between 0-75% Health - Cast Rejuvenation");
-- Mirkfallon Keeper
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4056;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4056 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4056,0,0,0,9,0,100,0,0,30,14000,26000,11,8138,32,0,0,0,0,2,0,0,0,0,0,0,0,"Mirkfallon Keeper - Within 0-5 Range - Cast Mirkfallon Fungus");
-- Nal'taszar
UPDATE `creature_template` SET `AIname`="SmartAI" WHERE `entry`=4066;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4066 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4066,0,0,0,9,0,100,0,0,30,11000,18000,11,8211,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nal\'taszar - Within 0-30 Range - Cast Chain Burn"),
(4066,0,1,0,0,0,100,0,8000,13000,12000,15000,11,15305,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nal\'taszar - In Combat - Cast Chain Lightning");
-- Gogger Rock Keeper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11915;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11915 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11915,0,0,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gogger Rock Keeper - On Aggro - Say Line 0"),
(11915,0,1,0,9,0,100,0,0,20,9000,15000,11,13281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gogger Rock Keeper - In Combat - Cast Earth Shock"),
(11915,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gogger Rock Keeper - Between 0-15% Health - Flee For Assist (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=11915;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11915,0,0,"You no take candle!",12,0,100,0,0,0,0,"Gogger Rock Keeper"),
(11915,0,1,"Yiieeeee! Me run!",12,0,100,0,0,0,0,"Gogger Rock Keeper"),
(11915,0,2,"No kill me! No kill me!",12,0,100,0,0,0,0,"Gogger Rock Keeper");
-- Gogger Geomancer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11917;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11917 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11917,0,0,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gogger Geomancer - On Aggro - Say Line 0"),
(11917,0,1,0,0,0,100,0,0,0,3400,4800,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gogger Geomancer - In Combat - Cast Fireball"),
(11917,0,2,0,0,0,100,0,11000,17000,12000,18000,11,11990,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gogger Geomancer - In Combat - Cast Rain of Fire");
DELETE FROM `creature_text` WHERE `entry`=11917;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11917,0,0,"You NO take candle!",12,0,100,0,0,0,0,"Gogger Geomancer"),
(11917,0,1,"Yiieeeee! Me run!",12,0,100,0,0,0,0,"Gogger Geomancer"),
(11917,0,2,"No kill me! No kill me!",12,0,100,0,0,0,0,"Gogger Geomancer");
-- Gogger Stonepounder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11918;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11918 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11918,0,0,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gogger Stonepounder - On Aggro - Say Line 0"),
(11918,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gogger Stonepounder - Between 0-15% Health - Flee For Assist (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=11918;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11918,0,0,"You NO take candle!",12,0,100,0,0,0,0,"Gogger Stonepounder"),
(11918,0,1,"Yiieeeee! Me run!",12,0,100,0,0,0,0,"Gogger Stonepounder"),
(11918,0,2,"No kill me! No kill me!",12,0,100,0,0,0,0,"Gogger Stonepounder");

/* Darkshore */

-- Moonstalker Matriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2071;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2071;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2071,0,0,0,1,0,100,1,3000,5000,0,0,11,8594,0,0,0,0,0,1,0,0,0,0,0,0,0,'Moonstalker Matriarch - Out of Combat - Cast Summon Moonstalker Runt (No Repeat)');
-- Moonstalker Sire
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2237;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2237;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2237,0,0,0,9,0,100,0,0,5,10000,14000,11,6595,0,0,0,0,0,2,0,0,0,0,0,0,0,'Moonstalker Sire - Within 0-5 Range - Cast Exploit Weakness');
-- Grizzled Thistle Bear
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2165;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2165;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2165,0,0,0,0,0,100,0,3000,5000,7000,10000,11,3242,0,0,0,0,0,2,0,0,0,0,0,0,0,'Grizzled Thistle Bear - In Combat - Cast Ravage');
-- Strider Clutchmother
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2172;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2172;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2172,0,0,0,0,0,100,0,7000,11000,12000,14000,11,7272,0,0,0,0,0,1,0,0,0,0,0,0,0,'Strider Clutchmother - In Combat - Cast Dust Cloud'),
(2172,0,1,0,9,0,100,0,0,5,15000,17000,11,6607,0,0,0,0,0,2,0,0,0,0,0,0,0,'Strider Clutchmother - Within 0-5 Range - Cast Lash'),
(2172,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Strider Clutchmother - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Shadowclaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2175;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2175;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2175,0,0,0,9,0,100,0,0,30,12000,15000,11,17227,0,0,0,0,0,2,0,0,0,0,0,0,0,'Shadowclaw - Within 0-30 Range - Cast Curse of Weakness');
-- Moonkin Oracle
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10157;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10157;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10157,0,0,0,0,0,100,0,1000,2000,2000,2000,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,'Moonkin Oracle - In Combat - Cast Wrath'),
(10157,0,1,0,0,0,100,0,7000,11000,12000,15000,11,15798,1,0,0,0,0,2,0,0,0,0,0,0,0,'Moonkin Oracle - In Combat - Cast Moonfire'),
(10157,0,2,0,14,0,100,0,200,40,25000,30000,11,16561,1,0,0,0,0,7,0,0,0,0,0,0,0,'Moonkin Oracle - Friendly At 200 Health - Cast Regrowth');
-- Moonkin
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10158;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10158;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10158,0,0,0,4,0,100,0,0,0,0,0,75,12787,0,0,0,0,0,1,0,0,0,0,0,0,0,'Moonkin Cast Thrash on reset');
-- Raging Moonkin
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10160;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10160;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10160,0,0,0,2,0,100,1,0,30,0,0,11,8599,1,0,0,0,0,1,0,0,0,0,0,0,0,'Raging Moonkin - Between 0-30% Health - Cast Enrage (No Repeat)'),
(10160,0,1,0,9,0,100,0,0,5,10000,15000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,'Raging Moonkin - Within 0-5 Range - Cast Rend');
-- Wild Grell
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2190;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2190;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2190,0,0,0,2,0,100,0,0,30,60000,60000,11,5915,0,0,0,0,0,1,0,0,0,0,0,0,0,'Wild Grell - Between 0-30% Health - Cast Crazed');
-- Deth'ryll Satyr
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2212;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2212;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2212,0,0,0,0,0,100,0,1000,2000,3500,4100,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Dethryll Satyr - In Combat - Cast Shoot');
-- Licillin
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2191;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2191;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2191,0,0,0,0,0,100,0,1000,2000,3000,3500,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,'Licillin - In Combat - Cast Fireball'),
(2191,0,1,0,9,0,100,0,0,30,20000,25000,11,11980,1,0,0,0,0,2,0,0,0,0,0,0,0,'Licillin - Within 0-30 Range - Cast Curse of Weakness');
-- Blackwood Pathfinder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2167;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2167;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2167,0,0,0,9,0,100,0,0,30,30000,35000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackwood Pathfinder - Within 0-30 Range - Cast Faerie Fire'),
(2167,0,1,0,4,0,100,0,0,0,0,0,75,54913,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackwood Pathfinder - Within 0-5 Range - Cast Thrash');
-- Blackwood Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2168;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2168;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2168,0,0,0,9,0,100,0,0,8,8000,13000,11,8078,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackwood Warrior - Within 0-8 Range - Cast Thunderclap'),
(2168,0,1,0,4,0,100,0,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackwood Warrior - Out of Combat - Cast Battle Stance (No Repeat)');
-- Blackwood Totemic
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2169;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2169;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2169,0,0,0,0,0,100,0,3000,6000,18000,23000,11,5605,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackwood Totemic - In Combat - Cast Healing Ward');
-- Blackwood Ursa
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2170;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2170;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2170,0,0,0,14,0,100,0,200,40,18000,21000,11,1058,0,0,0,0,0,7,0,0,0,0,0,0,0,'Blackwood Ursa - Friendly At 200 Health - Cast Rejuvenation');
-- Blackwood Shaman
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2171;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2171;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2171,0,0,0,0,0,100,0,1000,2000,3000,3400,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,'Blackwood Shaman - In Combat CMC - Cast Lightning Bolt'),
(2171,0,1,0,0,0,100,0,9000,14000,11000,15000,11,2606,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackwood Shaman - In Combat - Cast Shock'),
(2171,0,2,0,14,0,100,0,300,40,16000,21000,11,913,0,0,0,0,0,7,0,0,0,0,0,0,0,'Blackwood Shaman - Friendly At 300 Health - Cast Healing Wave');
-- Blackwood Windtalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2324;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2324;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2324,0,0,0,0,0,100,0,7000,11000,16000,21000,11,6982,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackwood Windtalker - In Combat - Cast Gust of Wind');
-- Carnivous the Breaker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2186;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2186;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2186,0,0,0,25,0,100,0,0,0,0,0,75,8876,0,0,0,0,0,1,0,0,0,0,0,0,0,'Carnivous the Breaker - On Respawn - Cast Thrash (No Repeat)'),
(2186,0,1,0,9,0,100,0,0,0,15000,20000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,'Carnivous the Breaker - Within 0-5 Range - Cast Pierce Armor');
-- Cursed Highborne
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2176;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2176;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2176,0,0,0,0,0,100,0,5000,9000,10000,13000,11,5884,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cursed Highborne - In Combat - Cast Banshee Curse');
-- Writhing Highborne
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2177;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2177;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2177,0,0,0,0,0,100,0,5000,9000,10000,13000,11,5884,0,0,0,0,0,5,0,0,0,0,0,0,0,'Writhing Highborne - In Combat - Cast Banshee Curse');
-- Wailing Highborne
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2178;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2178;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2178,0,0,0,0,0,100,0,5000,9000,10000,13000,11,5884,0,0,0,0,0,5,0,0,0,0,0,0,0,'Wailing Highborne - In Combat - Cast Banshee Curse');
-- Lady Moongazer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2184;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2184;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2184,0,0,0,0,0,100,0,1500,2000,3100,3500,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Lady Moongazer - In Combat - Cast Shoot'),
(2184,0,1,0,9,0,100,0,0,20,8000,11000,11,6533,1,0,0,0,0,2,0,0,0,0,0,0,0,'Lady Moongazer - Within 0-20 Range - Cast Net');
-- Stormscale Siren
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2180;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2180;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2180,0,0,0,0,0,100,0,1000,2000,2600,3000,11,9734,64,0,0,0,0,2,0,0,0,0,0,0,0,'Stormscale Siren - In Combat - Cast Holy Smite'),
(2180,0,1,0,2,0,100,0,0,50,18000,25000,11,11642,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stormscale Siren - Between 0-50% Health - Cast Heal'),
(2180, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 25, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Flee at 15% HP");
-- Stormscale Wave Rider
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2179;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2179;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2179,0,0,0,0,0,100,0,8000,13000,12000,16000,11,13586,0,0,0,0,0,2,0,0,0,0,0,0,0,'Stormscale Wave Rider - In Combat - Cast Aqua Jet');
-- Stormscale Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2183;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2183;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2183,0,0,0,0,0,100,0,4000,8000,10000,12000,11,3248,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stormscale Warrior - In Combat - Cast Improved Blocking');
-- Lord Sinslayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7017;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7017;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7017,0,0,0,9,0,100,0,0,5,5000,10000,11,12057,0,0,0,0,0,2,0,0,0,0,0,0,0,'Lord Sinslayer - Within 0-5 Range - Cast Strike'),
(7017,0,1,0,0,0,100,0,9000,12000,9000,12000,11,13586,0,0,0,0,0,2,0,0,0,0,0,0,0,'Lord Sinslayer - In Combat - Cast Aqua Jet');
-- Encrusted Tide Crawler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2233;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2233;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2233,0,0,0,0,0,100,0,2000,3000,7000,12000,11,3427,0,0,0,0,0,2,0,0,0,0,0,0,0,'Encrusted Tide Crawler - In Combat - Cast Infected Wound');
-- Greymist Raider
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2201;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2201;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2201,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Raider - Between 0-15% Health - Flee For Assist');
-- Greymist Coastrunner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2202;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2202;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2202,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Coastrunner - Between 0-15% Health - Flee For Assist');
-- Greymist Seer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2203;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2203;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2203,0,0,0,23,0,100,0,324,0,2000,3000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Seer - On missing aura - Cast Lightning Shield'),
(2203,0,1,0,16,0,100,0,324,1,9000,29000,11,324,48,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Seer - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield'),
(2203,0,2,0,74,0,100,0,0,40,14000,18000,11,547,0,0,0,0,0,9,0,0,0,0,0,0,0,'Greymist Seer - On Friendly Between 0-40% Health - Cast Healing Wave'),
(2203,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Seer - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Greymist Netter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2204;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2204;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2204,0,0,0,9,0,100,0,0,20,8000,14000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,'Greymist Netter - Within 0-20 Range - Cast Net'),
(2204,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Netter - Between 0-15% Health - Flee For Assist');
-- Greymist Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2205;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2205;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2205,0,0,0,4,0,100,0,0,0,0,0,11,5242,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Warrior - In Combat - Cast Battle Shout'),
(2205,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Warrior - Between 0-15% Health - Flee For Assist');
-- Greymist Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2206;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2206;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2206,0,0,0,0,0,100,0,1000,2000,2300,3000,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,'Greymist Hunter - In Combat CMC - Cast Throw'),
(2206,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Hunter - Between 0-15% Health - Flee For Assist');
-- Greymist Tidehunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2208;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2208;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2208,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Greymist Tidehunter - Between 0-15% Health - Flee For Assist');
-- Flagglemurk the Cruel
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7015;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7015;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7015,0,0,0,9,0,100,0,0,5,7000,10000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,'Flagglemurk the Cruel - Within 0-5 Range - Cast Strike'),
(7015,0,1,0,0,0,100,0,8000,12000,9000,12000,11,11428,0,0,0,0,0,2,0,0,0,0,0,0,0,'Flagglemurk the Cruel - In Combat - Cast Knockdown'),
(7015,0,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Flagglemurk the Cruel - Between 0-15% Health - Flee For Assist (No Repeat)');
-- Darkshore Thresher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2185;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2185;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2185,0,0,0,9,0,100,0,0,5,18000,20000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,'Darkshore Thresher - Within 0-5 Range - Cast Pierce Armor');
-- Elder Darkshore Thresher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2187;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2187;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2187,0,0,0,9,0,100,0,0,5,19000,21000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,'Elder Darkshore Thresher - Within 0-5 Range - Cast Pierce Armor');
-- Firecaller Radison
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2192;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2192;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2192,0,0,0,0,0,100,0,1000,2000,3400,4700,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,'Firecaller Radison - In Combat - Cast Fireball'),
(2192,0,1,0,9,0,100,0,0,8,11000,13000,11,11969,2,0,0,0,0,2,0,0,0,0,0,0,0,'Firecaller Radison - Within 0-8 Range - Cast Fire Nova'),
(2192,0,2,0,2,0,100,0,0,30,60000,65000,11,5915,2,0,0,0,0,1,0,0,0,0,0,0,0,'Firecaller Radison - Between 0-30% Health - Cast Crazed');
-- Stone Behemoth
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2157;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2157;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2157,0,0,0,0,0,100,0,5000,11000,13000,16000,11,5810,0,0,0,0,0,1,0,0,0,0,0,0,0,'Stone Behemoth - In Combat - Cast Stone Skin');
-- Lady Vespira
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7016;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7016;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7016,0,0,0,0,0,100,0,1500,3000,3000,3100,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Lady Vespira - In Combat - Cast Shoot'),
(7016,0,1,0,9,0,100,0,0,5,9000,14000,11,11428,1,0,0,0,0,2,0,0,0,0,0,0,0,'Lady Vespira - Within 0-5 Range - Cast Knockdown'),
(7016,0,2,0,0,0,100,0,11000,15000,14000,17000,11,12549,1,0,0,0,0,2,0,0,0,0,0,0,0,'Lady Vespira - In Combat - Cast Forked Lightning');
-- Remove Wrong 'Moonstalker Runt' Spawns
DELETE FROM `creature` WHERE `guid` IN (36898, 36904, 36907, 36924, 36938, 36942, 36943, 36944, 36957, 36956, 36958);
DELETE FROM `creature_addon` WHERE `guid` IN (36898, 36904, 36907, 36924, 36938, 36942, 36943, 36944, 36957, 36956, 36958);
UPDATE `creature` SET `position_x`=6594.56, `position_y`=313.645, `position_z`=28.3839 WHERE `guid`=36643;
UPDATE `creature` SET `position_x`=4424.85, `position_y`=422.488, `position_z`=56.4554 WHERE `guid`=36794;
UPDATE `creature` SET `position_x`=7742.69, `position_y`=-1067.14, `position_z`=38.1206 WHERE `guid`=36959;

/* Teldrassil */

-- Gnarlpine Ursa
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2006;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2006 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2006,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Ursa - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Gnarlpine Gardener
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2007;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2007 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2007,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Gardener - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Gnarlpine Warrior
DELETE FROM `smart_scripts` WHERE `entryorguid`=2008 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2008,0,0,0,0,0,100,0,4000,5000,7000,12000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gnarlpine Warrior - IC - Cast Strike");
-- Gnarlpine Shaman
DELETE FROM `smart_scripts` WHERE `entryorguid`=2009 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2009,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Shaman - Between 0-15% Health - Flee For Assist (No Repeat)"),
(2009,0,1,0,14,0,100,0,70,40,15000,21000,11,332,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gnarlpine Shaman - Friendly At 70 Health - Cast Healing Wave");
-- Gnarlpine Defender
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2010;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2010 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2010,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Defender - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Gnarlpine Augur
DELETE FROM `smart_scripts` WHERE `entryorguid`=2011 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2011,0,0,0,0,0,100,0,6000,11000,9000,16000,11,702,32,0,0,0,0,2,0,0,0,0,0,0,0,"Gnarlpine Augur - In Combat - Cast Curse of Weakness"),
(2011,0,1,0,2,0,100,1,0,30,0,0,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Augur - Between 0-30% Health - Cast Gnarlpine Vengeance (No Repeat)");
-- Gnarlpine Pathfinder
DELETE FROM `smart_scripts` WHERE `entryorguid`=2012 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2012,0,0,0,0,0,100,0,0,0,3400,4700,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gnarlpine Pathfinder - In Combat - Cast Wrath"),
(2012,0,1,0,2,0,100,1,0,30,0,0,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Pathfinder - Between 0-30% Health - Cast Gnarlpine Vengeance (No Repeat)");
-- Gnarlpine Avenger
DELETE FROM `smart_scripts` WHERE `entryorguid`=2013 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2013,0,0,0,2,0,100,1,0,30,0,0,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Avenger - Between 0-30% Health - Cast Gnarlpine Vengeance (No Repeat)");
-- Gnarlpine Totemic
DELETE FROM `smart_scripts` WHERE `entryorguid`=2014 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2014,0,0,0,2,0,100,1,0,30,0,0,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Totemic - Between 0-30% Health - Cast Gnarlpine Vengeance (No Repeat)"),
(2014,0,1,0,2,0,100,0,0,60,25000,30000,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Totemic - Between 0-60% Health - Cast Healing Ward");
-- Gnarlpine Mystic
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7235;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7235 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7235,0,0,0,0,0,100,0,0,0,3400,4700,11,9739,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gnarlpine Mystic - In Combat - Cast Wrath"),
(7235,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnarlpine Mystic - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Uruson
DELETE FROM `smart_scripts` WHERE `entryorguid`=14428 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14428,0,0,0,0,0,100,0,10000,15000,30000,35000,11,15971,0,0,0,0,0,1,0,0,0,0,0,0,0,"Uruson - IC - Cast Demoralizing Roar");
-- Rageclaw
DELETE FROM `smart_scripts` WHERE `entryorguid`=7318 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7318,0,0,0,4,0,100,1,0,0,0,0,11,7090,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rageclaw - On Aggro - Cast Bear Form"),
(7318,0,1,0,0,0,100,0,5000,7000,7000,10000,11,12161,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rageclaw - IC - Cast Maul");
-- Greenpaw
DELETE FROM `smart_scripts` WHERE `entryorguid`=1993 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1993,0,0,0,2,0,100,0,0,50,13000,19000,11,774,0,0,0,0,0,1,0,0,0,0,0,0,0,"Greenpaw - Between 0-50% Health - Cast Rejuvenation"),
(1993,0,1,0,0,0,100,0,3000,5000,7000,11000,11,2606,0,0,0,0,0,2,0,0,0,0,0,0,0,"Greenpaw - In Combat - Cast Shock");
-- Ursal the Mauler
DELETE FROM `smart_scripts` WHERE `entryorguid`=2039 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2039,0,0,0,0,0,100,0,4000,7000,5000,8000,11,15793,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ursal the Mauler - In Combat - Cast Maul");
-- Grimmaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14429;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14429 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14429,0,0,0,0,0,100,0,5000,7000,12000,20000,11,19319,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grimmaw - IC - Cast Vicious Bite");
-- Feral Nightsaber
DELETE FROM `smart_scripts` WHERE `entryorguid`=2034 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2034,0,0,0,0,0,100,0,5000,7000,10000,16000,11,12166,0,0,0,0,0,2,0,0,0,0,0,0,0,"Feral Nightsaber - IC - Cast Muscle Tear");
-- Duskstalker
DELETE FROM `smart_scripts` WHERE `entryorguid`=14430 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14430,0,0,0,0,0,100,0,3000,5000,4000,6000,11,3604,32,0,0,0,0,2,0,0,0,0,0,0,0,"Duskstalker - In Combat - Cast Tendon Rip");
-- Webwood Lurker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1998;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1998 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1998,0,0,0,9,0,100,0,0,30,40000,45000,11,4167,0,0,0,0,0,2,0,0,0,0,0,0,0,"Webwood Lurker - Within 0-30 Range - Cast Web");
-- Webwood Venomfang
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1999;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1999 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1999,0,0,0,0,0,100,0,3000,7000,13000,17000,11,11918,0,0,0,0,0,2,0,0,0,0,0,0,0,"Webwood Venomfang - In Combat - Cast Poison");
-- Webwood Silkspinner
DELETE FROM `smart_scripts` WHERE `entryorguid`=2000 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2000,0,0,0,9,0,100,0,0,30,12000,17000,11,12023,0,0,0,0,0,2,0,0,0,0,0,0,0,"Webwood Silkspinner - Within 0-30 Range - Cast Web");
-- Giant Webwood Spider
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2001;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2001 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2001,0,0,0,0,0,100,0,3000,7000,13000,17000,11,11918,0,0,0,0,0,2,0,0,0,0,0,0,0,"Giant Webwood Spider - In Combat - Cast Poison");
-- Shadow Sprite
DELETE FROM `smart_scripts` WHERE `entryorguid`=2003 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2003,0,0,0,0,0,100,0,0,0,3400,4800,11,9613,64,0,0,0,0,2,0,0,0,0,0,0,0,"Shadow Sprite - In Combat CMC - Cast Shadow Bolt");
-- Rascal Sprite
DELETE FROM `smart_scripts` WHERE `entryorguid`=2002 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2002,0,0,0,0,0,100,0,5000,12000,30000,40000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rascal Sprite - In Combat - Cast Faerie Fire");
-- Dark Sprite
DELETE FROM `smart_scripts` WHERE `entryorguid`=2004 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2004,0,0,0,0,0,100,0,2000,7000,15000,21000,11,5514,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Sprite - In Combat - Cast Darken Vision");
-- Vicious Grell
DELETE FROM `smart_scripts` WHERE `entryorguid`=2005 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2005,0,0,0,0,0,100,0,4000,8000,12000,16000,11,5515,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vicious Grell - In Combat - Cast Savagery");
-- Threggil
DELETE FROM `smart_scripts` WHERE `entryorguid`=14432 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14432,0,0,0,0,0,100,0,5000,7000,5000,8000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Threggil - IC - Cast Strike");
-- Lord Melenas
DELETE FROM `smart_scripts` WHERE `entryorguid`=2038 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2038,0,0,0,4,0,100,0,0,0,0,0,11,5759,2,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Melenas - On Aggro - Cast Cat Form"),
(2038,0,1,0,4,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Melenas - On Aggro - Set Event Phase 1"),
(2038,0,2,0,0,1,100,0,5000,7000,13000,18000,11,1822,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Melenas - IC - Cast Rake (Phase 1)"),
(2038,0,3,4,2,1,100,1,0,30,0,0,28,5759,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Melenas - Between 0-30% Health - Remove Aura Cat Form"),
(2038,0,4,0,61,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Melenas - Between 0-30% Health - Set Phase 2"),
(2038,0,5,0,2,2,100,0,0,30,12000,18000,11,774,2,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Melenas - Between 0-30% Health - Cast Rejuvenation (Phase 2)");
-- Timberling Bark Ripper
DELETE FROM `smart_scripts` WHERE `entryorguid`=2025 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2025,0,0,0,0,0,100,0,5000,7000,22000,25000,11,6016,0,0,0,0,0,2,0,0,0,0,0,0,0,"Timberling Bark Ripper - IC - Cast Pierce Armor");
-- Timberling Trampler
DELETE FROM `smart_scripts` WHERE `entryorguid`=2027 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2027,0,0,0,0,0,100,0,6000,11000,7000,12000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Timberling Trampler - In Combat - Cast Trample");
-- Timberling Mire Beast
DELETE FROM `smart_scripts` WHERE `entryorguid`=2029 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2029,0,0,0,0,0,100,0,5000,7000,12000,17000,11,5567,0,0,0,0,0,2,0,0,0,0,0,0,0,"Timberling Mire Beast - IC - Cast Miring Mud");
-- Elder Timberling
DELETE FROM `smart_scripts` WHERE `entryorguid`=2030 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2030,0,0,0,1,0,100,0,500,1000,600000,600000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Timberling - Out of Combat - Cast Lightning Shield"),
(2030,0,1,0,16,0,100,0,324,1,15000,30000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Timberling - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield"),
(2030,0,2,0,2,0,100,0,0,50,9000,15000,11,332,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Timberling - Between 0-50% Health - Cast Healing Wave");
-- Fury Shelda
DELETE FROM `smart_scripts` WHERE `entryorguid`=14431 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14431,0,0,0,0,0,100,0,5000,7000,13000,17000,11,3589,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fury Shelda - IC - Cast Deafening Screech");
-- Bloodfeather Harpy
DELETE FROM `smart_scripts` WHERE `entryorguid`=2015 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2015,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodfeather Harpy - On Aggro - Say Line 0"),
(2015,0,1,0,0,0,100,0,5000,8000,9000,12000,11,6958,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfeather Harpy - In Combat - Cast Blood Leech");
-- Bloodfeather Sorceress
DELETE FROM `smart_scripts` WHERE `entryorguid`=2018 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2018,0,2,0,0,0,100,0,0,0,3400,4800,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfeather Sorceress - In Combat CMC - Cast Fireball");
-- Bloodfeather Fury
DELETE FROM `smart_scripts` WHERE `entryorguid`=2019 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2019,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Bloodfeather Fury - On Aggro - Say Line 0"),
(2019,0,1,0,2,0,100,0,0,50,14000,18000,11,5515,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodfeather Fury - Between 0-50% Health - Cast Savagery");
DELETE FROM `creature_text` WHERE `entry`=2019;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2019,0,0,"A fine trophy your head will make, $r.",12,0,100,0,0,0,0,"Bloodfeather Fury"),
(2019,0,1,"My talons will shred your puny body, $r.",12,0,100,0,0,0,0,"Bloodfeather Fury"),
(2019,0,2,"You will be easy prey, $c.",12,0,100,0,0,0,0,"Bloodfeather Fury");
-- Bloodfeather Wind Witch
DELETE FROM `smart_scripts` WHERE `entryorguid`=2020 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2020,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Bloodfeather Wind Witch - On Aggro - Say Line 0"),
(2020,0,1,0,0,0,100,0,5000,7000,11000,16000,11,6982,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodfeather Wind Witch - IC - Cast Gust of Wind");
DELETE FROM `creature_text` WHERE `entry`=2020;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2020,0,0,"A fine trophy your head will make, $r.",12,0,100,0,0,0,0,"Bloodfeather Wind Witch"),
(2020,0,1,"My talons will shred your puny body, $r.",12,0,100,0,0,0,0,"Bloodfeather Wind Witch"),
(2020,0,2,"You will be easy prey, $c.",12,0,100,0,0,0,0,"Bloodfeather Wind Witch");
-- Bloodfeather Matriarch
DELETE FROM `smart_scripts` WHERE `entryorguid`=2021 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2021,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Bloodfeather Matriarch - On Aggro - Say Line 0"),
(2021,0,1,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodfeather Matriarch - In Combat CMC - Cast Lightning Bolt"),
(2021,0,2,0,2,0,100,0,0,50,18000,24000,11,332,1,0,0,0,0,1,0,0,0,0,0,0,0,"Bloodfeather Matriarch - Between 0-50% Health - Cast Healing Wave");
DELETE FROM `creature_text` WHERE `entry`=2021;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(2021,0,0,"A fine trophy your head will make, $r.",12,0,100,0,0,0,0,"Bloodfeather Matriarch"),
(2021,0,1,"My talons will shred your puny body, $r.",12,0,100,0,0,0,0,"Bloodfeather Matriarch"),
(2021,0,2,"You will be easy prey, $c.",12,0,100,0,0,0,0,"Bloodfeather Matriarch");
-- Add Random Movement for some creatures
UPDATE `creature` SET `MovementType`=1, `spawndist`=8 WHERE `guid` IN (46351, 47536);
