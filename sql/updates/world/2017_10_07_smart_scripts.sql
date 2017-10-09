/* Silithus */

-- Sand Skitterer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11738;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11738 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11738,0,0,0,0,0,100,0,4000,9000,10000,15000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Sand Skitterer - In Combat - Cast Poison");
-- Rock Stalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11739;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11739 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11739,0,0,0,9,0,100,0,0,30,9000,11000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rock Stalker - Within 0-30 Range - Cast Web"),
(11739,0,1,0,0,0,100,0,4000,9000,10000,15000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rock Stalker - In Combat - Cast Poison");
-- Gretheer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14472;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14472 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14472,0,0,0,9,0,100,0,0,5,18000,22000,11,21787,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gretheer - Within 0-5 Range - Cast Deadly Poison"),
(14472,0,1,0,9,0,100,0,0,30,9000,11000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gretheer - Within 0-30 Range - Cast Web");
-- Stonelash Scorpid
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11735;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11735 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11735,0,0,0,0,0,100,0,3000,8000,13000,18000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonelash Scorpid - In Combat - Cast Venom Sting");
-- Stonelash Pincer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11736;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11736 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11736,0,0,0,0,0,100,0,2000,6000,14000,22000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonelash Pincer - In Combat - Cast Tendon Rip"),
(11736,0,1,0,0,0,100,0,3000,8000,13000,18000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonelash Pincer - In Combat - Cast Venom Sting");
-- Stonelash Flayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11737;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11737 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11737,0,0,0,0,0,100,0,3000,8000,13000,18000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonelash Flayer - In Combat - Cast Venom Sting"),
(11737,0,1,0,0,0,100,0,5000,10000,12000,18000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonelash Flayer - In Combat - Cast Thrash");
-- Krellack
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14476;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14476 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14476,0,0,0,9,0,100,0,0,5,17000,21000,11,17170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Krellack - Within 0-5 Range - Cast Fatal Sting");
-- Dredge Striker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11740;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11740 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11740,0,0,0,9,0,100,1,8,25,0,0,11,22911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dredge Striker - Within 8-25 Range - Cast Charge (No Repeat)");
-- Dredge Crusher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11741;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11741 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11741,0,0,0,0,0,100,0,6000,9000,13000,19000,11,6607,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dredge Crusher - In Combat - Cast Lash");
-- Grubthor
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14477;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14477 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14477,0,0,0,9,0,100,0,0,5,12000,18000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grubthor - Within 0-5 Range - Cast Trample");
-- Dust Stormer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11744;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11744 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11744,0,0,0,0,0,100,0,6000,8000,20000,24000,11,19513,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dust Stormer - In Combat - Cast Lightning Cloud"),
(11744,0,1,0,1,0,100,0,500,1000,600000,600000,11,19514,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dust Stormer - Out of Combat - Cast Lightning Shield"),
(11744,0,2,0,16,0,100,0,19514,1,15000,30000,11,19514,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dust Stormer - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield");
-- Cyclone Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11745;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11745 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11745,0,0,0,0,0,100,0,3000,6000,9000,15000,11,12553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cyclone Warrior - In Combat - Cast Shock"),
(11745,0,1,0,0,0,100,0,7000,12000,18000,23000,11,15535,0,0,0,0,0,4,0,0,0,0,0,0,0,"Cyclone Warrior - In Combat - Cast Enveloping Winds");
-- Huricanian
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14478;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14478 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14478,0,0,0,0,0,100,0,4000,5000,12000,14000,11,15659,0,0,0,0,0,4,0,0,0,0,0,0,0,"Huricanian - In Combat - Cast Chain Lightning");
-- Desert Rumbler
DELETE FROM `smart_scripts` WHERE `entryorguid`=11746 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11746,0,0,0,0,0,100,0,5000,8000,18000,24000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Desert Rumbler - In Combat - Cast Trample");
-- Desert Rager
DELETE FROM `smart_scripts` WHERE `entryorguid`=11747 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11747,0,0,0,0,0,100,0,3000,5000,12000,16000,11,13728,0,0,0,0,0,2,0,0,0,0,0,0,0,"Desert Rager - In Combat - Cast Earth Shock"),
(11747,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Desert Rager - Between 0-30% Health - Cast Enrage (No Repeat)");
-- Tortured Druid
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=12178;
DELETE FROM `smart_scripts` WHERE `entryorguid`=12178 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(12178,0,0,0,2,0,100,1,0,25,0,0,11,23381,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tortured Druid - Between 0-25% Health - Cast Healing Touch (No Repeat)"),
(12178,0,1,0,0,0,100,0,5000,8000,5000,8000,11,23380,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tortured Druid - In Combat - Cast Moonfire"),
(12178,0,2,3,6,0,75,0,0,0,0,0,11,21327,2,0,0,0,0,1,0,0,0,0,0,0,0,"Tortured Druid - On Just Died - Cast Summon Hive\'Ashi Drones"),
(12178,0,3,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tortured Druid - On Just Died - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=12178;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(12178,0,0,"%s\'s death wail has stirred the nearby silithid hive!",16,0,100,0,0,0,0,"Tortured Druid");
-- Tortured Sentinel
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=12179;
DELETE FROM `smart_scripts` WHERE `entryorguid`=12179 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(12179,0,0,1,6,0,75,0,0,0,0,0,11,21327,2,0,0,0,0,1,0,0,0,0,0,0,0,"Tortured Sentinel - On Just Died - Cast Summon Hive\'Ashi Drones"),
(12179,0,1,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tortured Sentinel - On Just Died - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=12179;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(12179,0,0,"%s\'s death wail has stirred the nearby silithid hive!",16,0,100,0,0,0,0,"Tortured Sentinel");
-- Twilight Overlord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15213;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15213 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15213,0,0,0,0,0,100,0,0,0,3400,4800,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Overlord - In Combat - Cast Frostbolt"),
(15213,0,1,0,9,0,100,0,0,8,13000,15000,11,11831,1,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Overlord - Within 0-8 Range - Cast Frost Nova"),
(15213,0,2,0,0,0,100,0,8000,9000,24000,25000,11,12058,1,0,0,0,0,4,0,0,0,0,0,0,0,"Twilight Overlord - In Combat - Cast Chain Lightning"),
(15213,0,3,0,0,0,100,0,5000,6000,15000,21000,11,13339,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Overlord - In Combat - Cast Fire Blast");
-- Twilight Master
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11883;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11883 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11883,0,0,0,0,0,100,0,0,0,3400,4800,11,9672,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Master - In Combat - Cast Frostbolt"),
(11883,0,1,0,9,0,100,0,0,8,13000,15000,11,11831,1,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Master - Within 0-8 Range - Cast Frost Nova"),
(11883,0,2,0,0,0,100,0,8000,9000,24000,25000,11,12058,1,0,0,0,0,4,0,0,0,0,0,0,0,"Twilight Master - In Combat - Cast Chain Lightning"),
(11883,0,3,0,0,0,100,0,5000,6000,15000,21000,11,13339,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Master - In Combat - Cast Fire Blast");
-- Twilight Avenger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11880;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11880 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11880,0,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Avenger - Between 0-30% Health - Cast Enrage (No Repeat)"),
(11880,0,1,0,74,0,100,1,0,20,0,0,11,8602,0,0,0,0,0,9,0,0,0,0,0,0,0,"Twilight Avenger - On Friendly Between 0-20% Health - Cast Vengeance (No Repeat)");
-- Twilight Flamereaver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15201;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15201 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15201,0,0,0,0,0,100,0,2000,5000,18000,22000,11,15732,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Flamereaver - In Combat - Cast Immolate");
-- Vyral the Vile
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15202;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15202 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15202,0,0,0,0,0,100,0,0,40,3400,4700,11,19816,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vyral the Vile - In Combat - Cast Fireball"),
(15202,0,1,0,9,0,100,0,0,20,12000,15000,11,17439,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vyral the Vile - Within 0-20 Range - Cast Shadow Shock");
-- Twilight Marauder Morna
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15541;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15541 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15541,0,0,0,0,0,100,0,5000,8000,9000,13000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Marauder Morna - In Combat - Cast Mortal Strike"),
(15541,0,1,0,0,0,100,0,0,5,5000,9000,11,15572,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Marauder Morna - In Combat - Cast Sunder Armor"),
(15541,0,2,0,0,0,100,0,9000,15000,14000,18000,11,23600,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Marauder Morna - In Combat - Cast Piercing Howl");
-- Twilight Marauder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15542;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15542 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15542,0,0,0,4,0,100,0,0,0,0,0,11,22911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Marauder - On Aggro - Cast Charge"),
(15542,0,1,0,2,0,100,1,0,20,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Marauder - Between 0-20% Health - Cast Enrage (No Repeat)"),
(15542,0,2,0,0,0,100,0,9000,15000,14000,18000,11,23600,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Marauder - In Combat - Cast Piercing Howl");
-- Twilight Geolord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11881;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11881 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11881,0,0,0,0,0,100,0,0,0,2400,3800,11,9483,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Geolord - In Combat - Cast Boulder"),
(11881,0,1,0,9,0,100,0,0,20,12000,15000,11,13728,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Geolord - Within 0-20 Range - Cast Earth Shock");
-- Twilight Stonecaller
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11882;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11882 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11882,0,0,0,0,0,100,0,0,0,3400,4800,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Stonecaller - In Combat - Cast Fireball"),
(11882,0,1,0,1,0,100,1,1000,2000,0,0,11,19704,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Stonecaller - Out of Combat - Cast Summon Earth Elemental"),
(11882,0,2,0,9,0,100,0,0,5,12000,17000,11,11020,1,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Stonecaller - Within 0-5 Range - Cast Petrify"),
(11882,0,3,0,1,0,100,1,3000,5000,0,0,11,13236,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Stonecaller - Out of Combat - Cast Nature Channeling");
-- Twilight Prophet
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15308;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15308 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15308,0,0,0,0,0,100,0,4000,4500,12000,15000,11,15305,0,0,0,0,0,4,0,0,0,0,0,0,0,"Twilight Prophet - In Combat - Cast Chain Lightning"),
(15308,0,1,0,0,0,100,0,8000,9000,25000,28000,11,22884,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Prophet - In Combat - Cast Psychic Scream"),
(15308,0,2,0,9,0,100,0,0,8,16000,19000,11,17366,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Prophet - Within 0-8 Range - Cast Fire Nova"),
(15308,0,3,0,9,0,100,0,0,8,16000,19000,11,15531,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Prophet - Within 0-8 Range - Cast Frost Nova");
-- Twilight Keeper Havunth
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11804;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11804 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11804,0,0,0,9,0,100,0,0,8,10000,15000,11,17366,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Keeper Havunth - Within 0-8 Range - Cast Fire Nova"),
(11804,0,1,0,9,0,100,0,0,20,8000,13000,11,13339,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Keeper Havunth - Within 0-20 Range - Cast Fire Blast");
-- Twilight Keeper Mayna
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15200 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15200,0,0,0,0,0,100,0,7000,8500,12000,14500,11,17165,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Keeper Mayna - In Combat - Cast Mind Flay"),
(15200,0,1,0,0,0,100,0,5000,6000,20000,27000,11,15654,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Keeper Mayna - In Combat - Cast Shadow Word: Pain"),
(15200,0,2,0,0,0,100,0,9000,12000,33000,35000,11,22884,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Keeper Mayna - In Combat - Cast Psychic Scream");
-- Twilight Lord Everun
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14479;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14479 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14479,0,0,0,0,0,100,0,0,40,3400,4700,11,19816,64,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Lord Everun - In Combat - Cast Fireball"),
(14479,0,1,0,9,0,100,0,0,20,12000,15000,11,17439,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Lord Everun - Within 0-20 Range - Cast Shadow Shock");
-- Twilight Keeper Exeter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11803;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11803 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11803,0,0,0,9,0,100,0,0,5,9000,12000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Keeper Exeter - Within 0-5 Range - Cast Mortal Strike"),
(11803,0,1,0,0,0,100,0,5000,9000,18000,22000,11,22427,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Keeper Exeter - In Combat - Cast Concussion Blow");
-- Setis
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14471;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14471 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14471,0,0,0,0,0,100,0,8000,12000,18000,26000,11,16727,0,0,0,0,0,1,0,0,0,0,0,0,0,"Setis - In Combat - Cast War Stomp"),
(14471,0,1,0,0,0,100,0,14000,20000,15000,23000,11,10887,0,0,0,0,0,2,0,0,0,0,0,0,0,"Setis - In Combat - Cast Crowd Pummel"),
(14471,0,2,0,25,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Setis - On Reset - Set Active On");
-- Zora
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14474;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14474 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14474,0,0,0,9,0,100,0,0,30,12000,18000,11,21067,0,0,0,0,0,2,0,0,0,0,0,0,0,"Zora - Within 0-30 Range - Cast Poison Bolt");
-- Lapress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14473;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14473 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14473,0,0,0,9,0,100,0,0,5,20000,27000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lapress - Within 0-5 Range - Cast Rend");
-- Rex Ashil
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=14475;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14475 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14475,0,0,0,9,0,100,0,0,5,18000,22000,11,12097,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rex Ashil - Within 0-5 Range - Cast Pierce Armor");
-- Hive'Ashi Defender
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11722;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11722 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11722,0,0,0,0,0,100,0,3000,4500,12000,15000,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Ashi Defender - In Combat - Cast Cripple"),
(11722,0,1,0,0,0,100,0,6000,9000,22000,27000,11,6713,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Ashi Defender - In Combat - Cast Disarm");
-- Hive'Ashi Sandstalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11723;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11723 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11723,0,0,0,25,0,100,0,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hive\'Ashi Sandstalker - On Reset - Cast Sneak");
-- Hive'Zora Wasp
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11727;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11727 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11727,0,0,0,0,0,100,0,5000,8000,15000,21000,11,19448,32,0,0,0,0,2,0,0,0,0,0,0,0,"Hive'Zora Wasp - In Combat - Cast Poison");
-- Hive'Zora Reaver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11728;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11728 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11728,0,0,0,0,0,100,0,6000,9000,20000,22000,11,16790,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Zora Reaver - In Combat - Cast Knockdown"),
(11728,0,1,0,9,0,100,0,0,5,16000,19000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Zora Reaver - Within 0-5 Range - Cast Cleave");
-- Hive'Zora Hive Sister
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11729;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11729 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11729,0,0,0,0,0,100,0,3000,5000,12000,16000,11,7951,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Zora Hive Sister - In Combat - Cast Toxic Spit");
-- Hive'Regal Hive Lord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11734;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11734 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11734,0,0,0,4,0,100,0,0,0,0,0,11,19471,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Regal Hive Lord - On Aggro - Cast Berserker Charge");
-- Hive'Regal Ambusher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11730;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11730 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11730,0,0,0,25,0,100,0,0,0,0,0,11,22766,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hive\'Regal Ambusher - On Reset - Cast Sneak"),
(11730,0,1,0,9,0,100,0,0,5,15000,24000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Regal Ambusher - Within 0-5 Range - Cast Poison");
-- Hive'Regal Spitfire
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11732;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11732 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11732,0,0,0,0,0,100,0,2000,5000,16000,19000,11,21047,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Regal Spitfire - In Combat - Cast Corrosive Acid Spit"),
(11732,0,1,0,9,0,100,0,0,5,13000,15000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hive\'Regal Spitfire - Within 0-5 Range - Cast Swoop");
-- Alliance Silithyst Sentinel
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=17765;
DELETE FROM `smart_scripts` WHERE `entryorguid`=17765 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17765,0,0,0,0,0,100,0,2000,4500,12000,14000,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alliance Silithyst Sentinel - In Combat - Cast Mortal Strike"),
(17765,0,1,0,9,0,100,1,0,30,0,0,11,18396,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alliance Silithyst Sentinel - Within 0-30 Range - Cast Dismounting Blast (No Repeat)"),
(17765,0,2,0,0,0,100,0,6000,8000,22000,24000,11,18328,0,0,0,0,0,1,0,0,0,0,0,0,0,"Alliance Silithyst Sentinel - In Combat - Cast Incapacitating Shout"),
(17765,0,3,0,13,0,100,0,20000,30000,0,0,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Alliance Silithyst Sentinel - On Victim Casting - Cast Shield Bash");
-- Ironforge Brigade Rifleman
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15441;
UPDATE `creature_template_addon` SET `bytes2`=4098 WHERE `entry`=15441;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15441 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15441,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ironforge Brigade Rifleman - In Combat - Cast Shoot");
-- Horde Silithyst Sentinel
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=17766;
DELETE FROM `smart_scripts` WHERE `entryorguid`=17766 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17766,0,0,0,0,0,100,0,2000,4500,12000,14000,11,19643,0,0,0,0,0,2,0,0,0,0,0,0,0,"Horde Silithyst Sentinel - In Combat - Cast Mortal Strike"),
(17766,0,1,0,9,0,100,1,0,30,0,0,11,18396,0,0,0,0,0,2,0,0,0,0,0,0,0,"Horde Silithyst Sentinel - Within 0-30 Range - Cast Dismounting Blast (No Repeat)"),
(17766,0,2,0,0,0,100,0,6000,8000,22000,24000,11,18328,0,0,0,0,0,1,0,0,0,0,0,0,0,"Horde Silithyst Sentinel - In Combat - Cast Incapacitating Shout"),
(17766,0,3,0,13,0,100,0,20000,30000,0,0,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Horde Silithyst Sentinel - On Victim Casting - Cast Shield Bash");
-- Orgrimmar Legion Axe Thrower
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15617;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15617 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15617,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Orgrimmar Legion Axe Thrower - In Combat - Cast Throw");
-- Mistress Natalia Mar'alith
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15215;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15215 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15215,0,0,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - On Aggro - Say Line 0"),
(15215,0,1,0,0,0,100,0,2000,4000,10000,12000,11,44415,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - In Combat - Cast Blackout"),
(15215,0,2,0,2,0,100,0,0,60,12000,20000,11,27527,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - Between 0-60% Health - Cast Healing Touch"),
(15215,0,3,0,0,0,100,0,5000,7000,16000,24000,11,11639,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - In Combat - Cast Shadow Word: Pain"),
(15215,0,4,0,0,0,100,0,12000,15000,12000,17000,11,13704,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - In Combat - Cast Psychic Scream"),
(15215,0,5,0,0,0,100,0,8000,9000,16000,17000,11,16568,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - In Combat - Cast Mind Flay"),
(15215,0,6,0,6,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mistress Natalia Mar\'alith - On Death - Say Line 1");
DELETE FROM `creature_text` WHERE `entry`=15215;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15215,0,0,"You will make a fitting sacrifice!",12,0,100,0,0,0,0,"Mistress Natalia Mar\'alith"),
(15215,1,0,"C'Thun will retake this world!",14,0,100,0,0,0,0,"Mistress Natalia Mar\'alith");
-- Random movement for some creatures
UPDATE `creature` SET `MovementType`=1, `spawndist`=15 WHERE `guid` IN (51837, 42746, 42923, 43119, 43124);
-- Fix spawn position for one creature
UPDATE `creature` SET `position_x`=-7162.57, `position_y`=1380.36, `position_z`=2.92073, `orientation`=2.05615 WHERE `guid`=42906;

/* Tirisfal Glades */

-- Young Scavenger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1508;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1508 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1508,0,0,1,1,0,100,0,30000,600000,120000,600000,4,1018,0,0,0,0,0,1,0,0,0,0,0,0,0,"Young Scavenger - Out of Combat - Play Sound 1018"),
(1508,0,1,0,61,0,100,0,0,0,0,0,5,393,0,0,0,0,0,1,0,0,0,0,0,0,0,"Young Scavenger - Out of Combat - Play Emote 393");
-- Night Web Matriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1688;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1688 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1688,0,0,0,9,0,100,0,0,5,3000,5000,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Night Web Matriarch - Within 0-5 Range - Cast Poison");
-- Scarlet Warrior
DELETE FROM `smart_scripts` WHERE `entryorguid`=1535 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1535,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Warrior - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=1535;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1535,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Warrior"),
(1535,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Warrior"),
(1535,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Warrior"),
(1535,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Warrior");
-- Tirisfal Farmer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1934;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1934 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1934,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tirisfal Farmer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Tirisfal Farmhand
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1935;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1935 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1935,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tirisfal Farmhand - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Farmer Solliden
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1936;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1936 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1936,0,0,0,9,0,100,0,0,5,7000,10000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Farmer Solliden - Within 0-5 Range - Cast Strike"),
(1936,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Farmer Solliden - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Greater Duskbat
DELETE FROM `smart_scripts` WHERE `entryorguid`=1553 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1553,0,0,0,0,0,100,0,3000,5000,7000,12000,11,3242,0,0,0,0,0,2,0,0,0,0,0,0,0,"Greater Duskbat - In Combat - Cast Ravage");
-- Vampiric Duskbat
DELETE FROM `smart_scripts` WHERE `entryorguid`=1554 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1554,0,0,0,0,0,100,0,3000,5000,7000,12000,11,3242,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vampiric Duskbat - In Combat - Cast Ravage");
-- Ressan the Needler
DELETE FROM `smart_scripts` WHERE `entryorguid`=10357 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10357,0,0,0,9,0,100,0,0,8,12000,17000,11,8281,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ressan the Needler - In Combat - Cast Sonic Burst");
-- Rotting Dead
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1525;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1525 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1525,0,0,0,0,0,100,0,3000,6000,9000,15000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rotting Dead - In Combat - Cast Disease Touch");
-- Ravaged Corpse
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1526;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1526 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1526,0,0,0,0,0,100,0,3000,6000,9000,15000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ravaged Corpse - In Combat - Cast Disease Touch");
-- Lost Soul
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1531;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1531 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1531,0,0,0,9,0,100,0,0,8,12000,18000,11,7713,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lost Soul - Within 0-8 Range - Cast Wailing Dead");
-- Rot Hide Gnoll
DELETE FROM `smart_scripts` WHERE `entryorguid`=1674  AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1674,0,0,0,0,0,100,0,4000,12000,30000,45000,11,3237,2,0,0,0,0,2,0,0,0,0,0,0,0,"Rot Hide Gnoll - In Combat - Cast Curse of Thule"),
(1674,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Rot Hide Gnoll - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1674,0,2,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rot Hide Gnoll - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=1674;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1674,0,0,"Grrrr... fresh meat!",12,0,100,0,0,0,0,"Rot Hide Gnoll"),
(1674,0,1,"More bones to gnaw on...",12,0,100,0,0,0,0,"Rot Hide Gnoll");
-- Rot Hide Mongrel
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1675;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1675 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1675,0,0,0,0,0,100,0,7000,14000,30000,45000,11,3237,2,0,0,0,0,2,0,0,0,0,0,0,0,"Rot Hide Mongrel - In Combat - Cast Curse of Thule"),
(1675,0,1,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rot Hide Mongrel - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=1675;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1675,0,0,"Grrrr... fresh meat!",12,0,100,0,0,0,0,"Rot Hide Mongrel"),
(1675,0,1,"More bones to gnaw on...",12,0,100,0,0,0,0,"Rot Hide Mongrel");
-- Rot Hide Graverobber
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1941;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1941 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1941,0,0,0,0,0,100,0,2000,18000,30000,45000,11,3237,2,0,0,0,0,2,0,0,0,0,0,0,0,"Rot Hide Graverobber - In Combat - Cast Curse of Thule"),
(1941,0,1,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Rot Hide Graverobber - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=1941;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1941,0,0,"Grrrr... fresh meat!",12,0,100,0,0,0,0,"Rot Hide Graverobber"),
(1941,0,1,"More bones to gnaw on...",12,0,100,0,0,0,0,"Rot Hide Graverobber");
-- Maggot Eye
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1753;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1753 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1753,0,0,0,2,0,100,0,0,75,7000,14000,11,3243,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maggot Eye - Between 0-75% Health - Cast Life Harvest"),
(1753,0,1,0,0,0,100,0,4000,9000,30000,45000,11,3237,2,0,0,0,0,2,0,0,0,0,0,0,0,"Maggot Eye - In Combat - Cast Curse of Thule");
-- Wailing Ancestor
DELETE FROM `smart_scripts` WHERE `entryorguid`=1534 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1534,0,0,0,0,0,100,0,6000,10000,12000,20000,11,7713,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wailing Ancestor - In Combat - Cast Wailing Dead");
-- Rotting Ancestor
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1530;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1530 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1530,0,0,0,0,0,100,0,4000,12000,10000,18000,11,3322,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rotting Ancestor - In Combat - Cast Rancid Blood");
-- Darkeye Bonecaster
DELETE FROM `smart_scripts` WHERE `entryorguid`=1522 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1522,0,0,0,0,0,100,0,0,0,3400,4800,11,13322,64,0,0,0,0,2,0,0,0,0,0,0,0,"Darkeye Bonecaster - In Combat CMC - Cast Frostbolt");
-- Cracked Skull Soldier
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1523;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1523 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1523,0,0,0,0,0,100,0,4000,9000,21000,25000,11,589,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cracked Skull Soldier - In Combat - Cast Shadow Word: Pain");
-- Bayne
DELETE FROM `smart_scripts` WHERE `entryorguid`=10356 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10356,0,0,0,0,0,100,0,5000,8000,21000,25000,11,13443,0,0,0,0,0,5,0,0,0,0,0,0,0,"Bayne - In Combat - Cast Rend"),
(10356,0,1,0,9,0,100,0,0,5,20000,24000,11,3604,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bayne - Within 0-5 Range - Cast Tendon Rip");
-- Vile Fin Puddlejumper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1543;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1543 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1543,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Fin Puddlejumper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vile Fin Muckdweller
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1545;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1545 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1545,0,0,0,67,0,100,0,9000,12000,0,0,11,7159,0,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Fin Muckdweller - On Behind Target - Cast Backstab"),
(1545,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Fin Muckdweller - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Vile Fin Minor Oracle
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1544;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1544 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1544,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Vile Fin Minor Oracle - In Combat - Cast Lightning Bolt"),
(1544,0,1,0,0,0,100,0,11000,16000,12000,16000,11,2607,0,0,0,0,0,4,0,0,0,0,0,0,0,"Vile Fin Minor Oracle - In Combat - Cast Shock"),
(1544,0,2,0,1,0,100,0,500,1000,600000,600000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Fin Minor Oracle - Out of Combat - Cast Lightning Shield"),
(1544,0,3,0,16,0,100,0,324,1,15000,30000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Fin Minor Oracle - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield"),
(1544,0,4,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vile Fin Minor Oracle - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Muad
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1910;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1910 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1910,0,0,0,14,0,100,0,80,40,12000,16000,11,332,0,0,0,0,0,7,0,0,0,0,0,0,0,"Muad - Friendly At 80 Health - Cast Healing Wave"),
(1910,0,1,0,9,0,100,0,0,20,5000,8000,11,2607,0,0,0,0,0,2,0,0,0,0,0,0,0,"Muad - Within 0-20 Range - Cast Shock");
-- Scarlet Missionary
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1536;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1536 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1536,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Missionary - On Aggro - Say Line 0"),
(1536,0,1,0,0,0,100,0,0,0,3400,4800,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Missionary - In Combat - Cast Fireball"),
(1536,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Missionary - Between 0-15% Health - Flee For Assist (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=1536;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1536,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Missionary"),
(1536,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Missionary"),
(1536,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Missionary"),
(1536,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Missionary");
-- Scarlet Zealot
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1537;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1537 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1537,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Zealot - On Aggro - Say Line 0"),
(1537,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Zealot - Between 0-15% Health - Flee For Assist (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=1537;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1537,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Zealot"),
(1537,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Zealot"),
(1537,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Zealot"),
(1537,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Zealot");
-- Scarlet Friar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1538;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1538 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1538,0,0,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Friar - On Aggro - Say Line 0"),
(1538,0,1,0,1,0,100,0,1000,1000,3000000,3000000,11,1243,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Friar - Out of Combat - Cast Power Word: Fortitude"),
(1538,0,2,0,14,0,100,0,55,40,8000,12000,11,2052,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Friar - Friendly At 55 Health - Cast Lesser Heal"),
(1538,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Friar - Between 0-15% Health - Flee For Assist (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=1538;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1538,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Friar"),
(1538,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Friar"),
(1538,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Friar"),
(1538,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Friar");
-- Scarlet Vanguard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1540;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1540 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1540,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Vanguard - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1540,0,1,0,13,0,100,0,16000,24000,0,0,11,72,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Vanguard - Target Casting - Cast Shield Bash"),
(1540,0,2,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Vanguard - On Aggro - Say Line 0"),
(1540,0,3,0,0,0,100,1,1000,3000,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Vanguard - In Combat - Cast Defensive Stance (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=1540;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1540,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Vanguard"),
(1540,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Vanguard"),
(1540,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Vanguard"),
(1540,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Vanguard");
-- Scarlet Neophyte
DELETE FROM `smart_scripts` WHERE `entryorguid`=1539 AND `source_type`=0 AND `id`=3;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1539,0,3,0,4,0,15,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Neophyte - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=1539;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1539,0,0,"You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.",12,0,100,0,0,0,0,"Scarlet Neophyte"),
(1539,0,1,"There is no escape for you.  The Crusade shall destroy all who carry the Scourge\'s taint.",12,0,100,0,0,0,0,"Scarlet Neophyte"),
(1539,0,2,"The Light condemns all who harbor evil.  Now you will die!",12,0,100,0,0,0,0,"Scarlet Neophyte"),
(1539,0,3,"The Scarlet Crusade shall smite the wicked and drive evil from these lands!",12,0,100,0,0,0,0,"Scarlet Neophyte");
-- Captain Perrine
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1662;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1662 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1662,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Perrine - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Captain Vachon
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1664;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1664 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1664,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Vachon - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1664,0,1,0,13,0,100,0,16000,24000,0,0,11,72,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captain Vachon - Target Casting - Cast Shield Bash"),
(1664,0,2,0,0,0,100,0,8000,14000,18000,30000,11,3248,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Vachon - In Combat - Cast Improved Blocking"),
(1664,0,3,0,0,0,100,1,1000,3000,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Vachon - In Combat - Cast Defensive Stance (No Repeat)");
-- Captain Melrache
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1665;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1665 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1665,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Melrache - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1665,0,1,0,9,0,100,0,0,5,7000,11000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Melrache - Within 0-5 Range - Cast Strike"),
(1665,0,2,0,0,0,100,1,1000,3000,0,0,11,8258,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Melrache - In Combat - Cast Devotion Aura (No Repeat)");
-- Scarlet Bodyguard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1660;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1660 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1660,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Bodyguard - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1660,0,1,0,0,0,100,0,1000,7000,5000,28000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Bodyguard - In Combat - Cast Shield Block");
-- Bleeding Horror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1529;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1529 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1529,0,0,0,0,0,100,0,4000,12000,10000,18000,11,3322,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bleeding Horror - In Combat - Cast Rancid Blood");
-- Wandering Spirit
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1532;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1532 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1532,0,0,0,0,0,100,0,6000,10000,12000,20000,11,7713,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wandering Spirit - In Combat - Cast Wailing Dead");
-- Fellicent's Shade
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10358;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10358 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10358,0,0,0,0,0,100,0,0,0,3400,4700,11,13901,64,0,0,0,0,2,0,0,0,0,0,0,0,"Fellicent\'s Shade - In Combat - Cast Arcane Bolt"),
(10358,0,1,0,9,0,100,0,0,8,12000,17000,11,11975,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fellicent\'s Shade - Within 0-8 Range - Cast Arcane Explosion"),
(10358,0,2,0,0,0,100,0,5000,9000,22000,26000,11,7068,0,0,0,0,0,2,0,0,0,0,0,0,0,"Fellicent\'s Shade - In Combat - Cast Veil of Shadow");
-- Sri'skulk
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10359;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10359 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10359,0,0,0,9,0,100,0,0,5,17000,20000,11,3583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sri\'skulk - Within 0-5 Range - Cast Deadly Poison");
-- Scarlet Preserver
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4280;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4280 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4280,0,0,0,0,0,100,0,3000,5000,7000,12000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Preserver - In Combat - Cast Holy Strike"),
(4280,0,1,0,14,0,100,0,500,40,12000,18000,11,13952,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Preserver - Friendly At 500 Health - Cast Holy Light"),
(4280,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Preserver - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4281;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4281 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4281,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Scout - In Combat - Cast Shoot"),
(4281,0,1,0,9,0,100,0,5,30,9000,13000,11,6979,2,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Scout - Within 5-30 - Cast Fire Shot"),
(4281,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Scout - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Magician
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4282;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4282 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4282,0,0,0,0,0,100,0,0,0,3400,4700,11,9053,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Magician - In Combat - Cast Fireball"),
(4282,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Magician - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Sentry (4283)
DELETE FROM `creature_text` WHERE `entry`=4283;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(4283, 0, 0, 'You carry the taint of the Scourge. Prepare to enter the Twisting Nether.', 12, 0, 100, 0, 0, 0, 0, 'Scarlet Sentry'),
(4283, 0, 1, 'There is no escape for you. The Crusade shall destroy all who carry the Scourge''s taint.', 12, 0, 100, 0, 0, 0, 0, 'Scarlet Sentry'),
(4283, 0, 2, 'The Light condemns all who harbor evil. Now you will die!', 12, 0, 100, 0, 0, 0, 0, 'Scarlet Sentry'),
(4283, 0, 3, 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', 12, 0, 100, 0, 0, 0, 0, 'Scarlet Sentry');
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4283;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4283 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(4283,0,0,0,25,0,100,0,0,0,0,0,11,3637,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scarlet Sentry - On Reset - Cast Improved Blocking III'),
(4283,0,1,0,4,0,20,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scarlet Sentry - On Aggro - Say Line 0'),
(4283,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scarlet Sentry - Between 0-15% Health - Flee For Assist');
-- Scarlet Disciple
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4285;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4285 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4285,0,0,0,0,0,100,0,0,0,3400,4700,11,9734,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Disciple - In Combat - Cast Holy Smite"),
(4285,0,1,0,14,0,100,0,600,40,11000,15000,11,11642,1,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Disciple - Friendly At 600 Health - Cast Heal"),
(4285,0,2,0,2,0,100,1,0,50,0,0,11,11640,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Disciple - Between 0-50% Health - Cast Renew (No Repeat)"),
(4285,0,3,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Disciple - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Convert
UPDATE `smart_scripts` SET `event_chance`=20 WHERE `entryorguid`=1506 AND `source_type`=0 AND `id`=0;
-- Scarlet Convert
DELETE FROM `smart_scripts` WHERE `entryorguid`=-44957 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-44957,0,0,0,4,0,20,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Convert - On Aggro - Say Line 0"),
(-44957,0,1,0,4,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,1667,0,0,0,0,0,0,"Scarlet Convert - On Aggro - Set Data");
-- Scarlet Initiate
DELETE FROM `smart_scripts` WHERE `entryorguid`=1507 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1507,0,0,0,0,0,100,0,0,0,3400,4800,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Initiate - In Combat - Cast Fireball"),
(1507,0,1,0,23,0,100,0,12544,0,5000,10000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Initiate - On Has No Aura Frost Armor - Cast Frost Armor"),
(1507,0,2,0,4,0,20,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Initiate - On Aggro - Say Line 0");
-- Scarlet Initiate
DELETE FROM `smart_scripts` WHERE `entryorguid`=-44964 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-44964,0,0,0,0,0,100,0,0,0,3400,4800,11,20793,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Initiate - In Combat - Cast Fireball"),
(-44964,0,1,0,23,0,100,0,12544,0,5000,10000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Initiate - On Has No Aura Frost Armor - Cast Frost Armor"),
(-44964,0,2,0,4,0,20,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Initiate - On Aggro - Say Line 0"),
(-44964,0,3,0,4,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,1667,0,0,0,0,0,0,"Scarlet Initiate - On Aggro - Set Data");
-- Meven Korgal
DELETE FROM `smart_scripts` WHERE `entryorguid`=1667 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1667,0,0,0,25,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Meven Korgal - On Reset - Say Line 1"),
(1667,0,1,0,4,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Meven Korgal - On Aggro - Say Line 2"),
(1667,0,2,0,38,0,100,1,1,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Meven Korgal - On Data Set - Say Line 0 (No Repeat)"),
(1667,0,3,0,1,0,100,0,25000,40000,90000,120000,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Meven Korgal - Out of Combat - Say Line 3");
DELETE FROM `creature_text` WHERE `entry`=1667;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1667,0,0,"These lands shall be cleansed!",12,0,100,0,0,0,0,"Meven Korgal"),
(1667,1,0,"These undead atrocities will be destroyed!",14,0,100,0,0,0,0,"Meven Korgal"),
(1667,2,0,"The Scarlet Crusade shall not fail in its mission!",12,0,100,0,0,0,0,"Meven Korgal"),
(1667,3,0,"We must be vigilant to eradicate this plague!",14,0,100,0,0,0,0,"Meven Korgal"),
(1667,3,1,"Keep up the good work.  This scourge will be cleansed!",14,0,100,0,0,0,0,"Meven Korgal"),
(1667,3,2,"The Scarlet Crusade will scour these lands!",14,0,100,0,0,0,0,"Meven Korgal"),
(1667,3,3,"Let none with the foul taint of plague live!",14,0,100,0,0,0,0,"Meven Korgal");
-- Shambling Horror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1528;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1528 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1528,0,0,0,0,0,100,0,3000,6000,9000,15000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shambling Horror - In Combat - Cast Disease Touch");
-- Hungering Dead
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1527;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1527 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1527,0,0,0,0,0,100,0,3000,6000,9000,15000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Hungering Dead - In Combat - Cast Disease Touch");

/* Tanaris */

-- Murderous Blisterpaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8208;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8208 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8208,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murderous Blisterpaw - In Combat - Cast Thrash"),
(8208,0,1,0,0,0,100,0,12000,18000,15000,22000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Murderous Blisterpaw - In Combat - Cast Rend");
-- Scorpid Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5422;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5422 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5422,0,0,0,0,0,100,0,6000,12000,9000,15000,11,7992,32,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpid Hunter - In Combat - Cast Slowing Poison");
-- Kregg Keelhaul
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8203;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8203 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8203,0,0,0,9,0,100,0,0,5,9000,14000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kregg Keelhaul - Within 0-5 Range - Cast Strike"),
(8203,0,1,0,0,0,100,0,9000,16000,16000,21000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kregg Keelhaul - In Combat - Cast Cleave");
-- Hazzali Worker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5452;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5452 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5452,0,0,0,2,0,100,1,0,30,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hazzali Worker - Between 0-30% Health - Flee For Assist (No Repeat)"),
(5452,0,1,0,6,0,100,1,0,0,0,0,11,11023,3,0,0,0,0,1,0,0,0,0,0,0,0,"Hazzali Worker - On Death - Cast Summon Hazzali Parasites");
-- Hazzali Tunneler
UPDATE `smart_scripts` SET `event_chance`=100 WHERE `entryorguid`=5453 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5453 AND `id`=1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5453,0,1,0,6,0,100,1,0,0,0,0,11,11023,3,0,0,0,0,1,0,0,0,0,0,0,0,"Hazzali Tunneler - On Just Died - Cast Summon Hazzali Parasites");
-- Hazzali Sandreaver
UPDATE `smart_scripts` SET `event_chance`=100 WHERE `entryorguid`=5454 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5454 AND `id`=1 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5454,0,1,0,6,0,100,1,0,0,0,0,11,11023,3,0,0,0,0,1,0,0,0,0,0,0,0,"Hazzali Sandreaver - On Just Died - Cast Summon Hazzali Parasites");
-- Searing Roc
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5430;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5430 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5430,0,0,0,0,0,100,0,6000,8000,18000,20000,11,16843,0,0,0,0,0,2,0,0,0,0,0,0,0,"Searing Roc - In Combat - Cast Crimson Fury");
-- Dune Smasher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5469;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5469 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5469,0,0,0,0,0,100,0,9000,19000,24000,36000,11,9791,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dune Smasher - In Combat - Cast Head Crack");
-- Jin'Zallah the Sandbringer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8200 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8200,0,0,0,0,0,100,0,0,0,3400,4800,11,20824,64,0,0,0,0,2,0,0,0,0,0,0,0,"Jin\'Zallah the Sandbringer - In Combat - Cast Lightning Bolt"),
(8200,0,1,0,9,0,100,0,0,8,13600,14500,11,7272,1,0,0,0,0,1,0,0,0,0,0,0,0,"Jin\'Zallah the Sandbringer - Within 0-8 Range - Cast Dust Cloud"),
(8200,0,2,0,2,0,100,1,0,55,0,0,11,10132,1,0,0,0,0,1,0,0,0,0,0,0,0,"Jin\'Zallah the Sandbringer - Between 0-55% Health - Cast Sand Storms (No Repeat)");
-- Sand Storm (7226)
DELETE FROM `creature_template_addon` WHERE `entry`=7226;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`auras`) VALUES
(7226, 0, "10092");
UPDATE `creature_template` SET `flags_extra`=128, `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=7226;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7226 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(7226, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 89, 12, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sand Storm - just summoned - random movement');
-- Warleader Krazzilak
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8199;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8199 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8199,0,0,0,0,0,100,0,8000,10000,18000,34000,11,6713,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warleader Krazzilak - In Combat - Cast Disarm"),
(8199,0,1,0,0,0,100,0,13000,15000,17000,26000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warleader Krazzilak - In Combat - Cast Hamstring"),
(8199,0,2,0,0,0,100,0,14000,18000,12000,26000,11,17230,32,0,0,0,0,5,0,0,0,0,0,0,0,"Warleader Krazzilak - In Combat - Cast Infected Wound"),
(8199,0,3,0,0,0,100,0,12000,20000,12000,25000,11,18103,0,0,0,0,0,5,0,0,0,0,0,0,0,"Warleader Krazzilak - In Combat - Cast Backhand");
-- Haarka the Ravenous
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8205;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8205 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8205,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Haarka the Ravenous - In Combat - Cast Thrash"),
(8205,0,1,0,9,0,100,0,0,5,5000,9000,11,21081,0,0,0,0,0,2,0,0,0,0,0,0,0,"Haarka the Ravenous - Within 0-5 Range - Cast Sunder Armor");
-- Caliph Scorpidsting
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=7847;
DELETE FROM `smart_scripts` WHERE `entryorguid`=7847 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7847,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Caliph Scorpidsting - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Tick
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8198;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8198 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8198,0,0,0,0,0,100,0,8000,16000,12000,18000,11,21073,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tick - In Combat - Cast Arcane Explosion"),
(8198,0,1,0,0,0,100,0,12000,16000,14000,18000,11,20717,0,0,0,0,0,2,0,0,0,0,0,0,0,"Tick - In Combat - Cast Sand Breath");
-- Chronalis
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8197;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8197 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8197,0,0,0,9,0,100,0,0,5,9000,16000,11,18144,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chronalis - Within 0-5 Range - Cast Swoop"),
(8197,0,1,0,0,0,100,0,12000,16000,14000,18000,11,20717,0,0,0,0,0,2,0,0,0,0,0,0,0,"Chronalis - In Combat - Cast Sand Breath");
-- Occulus
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8196;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8196 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8196,0,0,0,9,0,100,0,0,5,9000,14000,11,18144,0,0,0,0,0,2,0,0,0,0,0,0,0,"Occulus - Within 0-5 Range - Cast Swoop"),
(8196,0,1,0,0,0,100,0,12000,16000,14000,18000,11,20717,0,0,0,0,0,2,0,0,0,0,0,0,0,"Occulus - In Combat - Cast Sand Breath"),
(8196,0,2,0,0,0,100,0,9000,14000,11000,15000,11,10833,0,0,0,0,0,5,0,0,0,0,0,0,0,"Occulus - In Combat - Cast Arcane Blast");

/* Western Plaguelands */

-- Lord Maldazzar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1848;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1848 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1848,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Maldazzar - Between 0-15% Health - Flee For Assist (No Repeat)"),
(1848,0,1,0,0,0,100,0,6000,9000,15000,20000,11,17204,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Maldazzar - In Combat - Cast Summon Skeleton"),
(1848,0,2,0,0,0,100,0,12000,16000,15000,19000,11,17173,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Maldazzar - In Combat - Cast Drain Life"),
(1848,0,3,0,0,0,100,0,0,0,3400,4800,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Maldazzar - In Combat - Cast Shadow Bolt");
-- Jabbering Ghoul
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10801;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10801 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10801,0,0,0,4,0,100,0,0,0,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jabbering Ghoul - On Aggro - Cast Enrage"),
(10801,0,1,0,0,0,100,0,4000,7000,9000,13000,11,12097,1,0,0,0,0,2,0,0,0,0,0,0,0,"Jabbering Ghoul - In Combat - Cast Pierce Armor"),
(10801,0,2,0,11,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0,0,0,0,"Jabbering Ghoul - On Respawn - Cast Birth");
-- Farmer Dalson
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10836;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10836 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10836,0,0,0,1,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0,0,0,0,"Farmer Dalson - Out of Combat - Cast Birth (No Repeat)"),
(10836,0,1,0,4,0,100,0,0,0,0,0,11,15716,0,0,0,0,0,1,0,0,0,0,0,0,0,"Farmer Dalson - On Aggro - Cast Enrage"),
(10836,0,2,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Farmer Dalson - In Combat - Cast Thrash"),
(10836,0,3,0,9,0,100,0,0,5,7000,12000,11,16128,33,0,0,0,0,2,0,0,0,0,0,0,0,"Farmer Dalson - In Combat - Cast Infected Bite");
-- Wandering Skeleton
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10816;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10816 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10816,0,0,0,0,0,75,0,1000,3000,3000,6000,11,17014,0,0,0,0,0,1,0,0,0,0,0,0,0,"Wandering Skeleton - In Combat - Cast Bone Shards");
-- Foulmane
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1847;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1847 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1847,0,0,0,11,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0,0,0,0,"Foulmane - On Respawn - Cast Birth"),
(1847,0,1,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foulmane - In Combat - Cast Thrash"),
(1847,0,2,0,9,0,100,0,0,5,19000,23000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foulmane - In Combat - Cast Rend");
-- Skeletal Flayer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1785;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1785 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1785,0,0,0,0,0,100,0,5000,9000,18000,26000,11,12542,0,0,0,0,0,5,0,0,0,0,0,0,0,"Skeletal Flayer - In Combat - Cast Fear");
-- Plague Lurker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1824;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1824 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1824,0,0,0,0,0,100,0,4000,10000,40000,50000,11,3436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Plague Lurker - In Combat - Cast Wandering Plague");
-- Fetid Zombie
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10580;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10580 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10580,0,0,0,11,0,100,1,0,0,0,0,11,8713,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fetid Zombie - On Respawn - Cast Overwhelming Musk (No Repeat)");
-- Haunting Vision
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4472;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4472 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4472,0,0,0,0,0,100,0,0,0,3400,4800,11,13860,64,0,0,0,0,2,0,0,0,0,0,0,0,"Haunting Vision - In Combat - Cast Mind Blast"),
(4472,0,1,0,0,0,100,0,6000,9000,8000,12000,11,11981,1,0,0,0,0,2,0,0,0,0,0,0,0,"Haunting Vision - In Combat - Cast Mana Burn"),
(4472,0,2,0,0,0,100,0,5000,7000,12000,16000,11,11443,1,0,0,0,0,2,0,0,0,0,0,0,0,"Haunting Vision - In Combat - Cast Cripple");
-- Cauldron Lord Bilemaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11075;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11075 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11075,0,0,0,9,0,100,0,0,5,7000,12000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Bilemaw - Within 0-5 Range - Cast Infected Wound"),
(11075,0,1,0,9,0,100,0,0,5,18000,22000,11,13445,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Bilemaw - Within 0-5 Range - Cast Rend"),
(11075,0,2,0,0,0,100,0,8000,12000,15000,20000,11,3391,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Bilemaw - In Combat - Cast Thrash"),
(11075,0,3,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cauldron Lord Bilemaw - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=11075;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11075,0,0,"$R flesh... must feed!",14,0,100,0,0,0,0,"Cauldron Lord Bilemaw");
-- Cauldron Lord Razarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11076;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11076 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11076,0,0,0,0,0,100,0,0,0,3400,4800,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Razarch - In Combat - Cast Shadow Bolt"),
(11076,0,1,0,0,0,100,0,11000,15000,20000,25000,11,17204,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cauldron Lord Razarch - In Combat - Cast Summon Skeleton"),
(11076,0,2,0,2,0,100,0,0,50,14000,18000,11,17173,1,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Razarch - Between 0-50% Health - Cast Drain Life"),
(11076,0,3,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cauldron Lord Razarch - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=11076;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11076,0,0,"The Scourge beckons you, foolish $r.",14,0,100,0,0,0,0,"Cauldron Lord Razarch");
-- Cauldron Lord Malvinious
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11077;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11077 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11077,0,0,0,0,0,100,0,0,0,3400,4800,11,12471,64,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Malvinious - In Combat - Cast Shadow Bolt"),
(11077,0,1,0,0,0,100,0,11000,15000,20000,25000,11,17204,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cauldron Lord Malvinious - In Combat - Cast Summon Skeleton"),
(11077,0,2,0,2,0,100,0,0,50,14000,18000,11,17173,1,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Malvinious - Between 0-50% Health - Cast Drain Life"),
(11077,0,3,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cauldron Lord Malvinious - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=11077;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11077,0,0,"Who dares to approach this cauldron?  Taste my dark blade!",14,0,100,0,0,0,0,"Cauldron Lord Malvinious");
-- Cauldron Lord Soulwrath
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11078;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11078 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11078,0,0,0,0,0,100,0,5000,8000,14000,19000,11,12946,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Soulwrath - In Combat - Cast Putrid Stench"),
(11078,0,1,0,9,0,100,0,0,8,12000,15000,11,10966,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cauldron Lord Soulwrath - Within 0-8 Range - Cast Uppercut"),
(11078,0,2,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Cauldron Lord Soulwrath - On Aggro - Say Line 0");
DELETE FROM `creature_text` WHERE `entry`=11078;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11078,0,0,"$C - I will consume your light!",14,0,100,0,0,0,0,"Cauldron Lord Soulwrath");
-- Decrepit Guardian
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10943;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10943 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10943,0,0,0,1,0,100,1,0,0,0,0,11,26047,0,0,0,0,0,1,0,0,0,0,0,0,0,"Decrepit Guardian - Out of Combat - Cast Birth (No Repeat)"),
(10943,0,1,0,9,0,100,0,0,30,16000,24000,11,16333,0,0,0,0,0,2,0,0,0,0,0,0,0,"Decrepit Guardian - Within 0-30 Range - Cast Debilitating Touch");
-- Scarlet High Clerist
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1839;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1839 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1839,0,0,0,9,0,100,0,0,30,14000,19000,11,17141,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet High Clerist - Within 0-30 Range - Cast Holy Fire"),
(1839,0,1,0,0,0,100,0,18000,25000,60000,90000,11,17139,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet High Clerist - In Combat - Cast Power Word: Shield"),
(1839,0,2,0,2,0,100,0,0,50,15000,21000,11,15586,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet High Clerist - Between 0-50% Health - Cast Heal"),
(1839,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet High Clerist - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Medic
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10605;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10605 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10605,0,0,0,14,0,100,0,1200,40,16000,19000,11,11640,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Medic - Friendly At 1200 Health - Cast Renew"),
(10605,0,1,0,14,0,100,0,2000,40,12000,15000,11,17137,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Medic - Friendly At 2000 Health - Cast Flash Heal"),
(10605,0,2,0,16,0,100,0,17175,8,2000,2000,11,17175,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Medic - On Friendly Unit Missing Buff Resist Arcane - Cast Resist Arcane"),
(10605,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Medic - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Lumberjack
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1884;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1884 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1884,0,0,0,9,0,100,0,0,5,7000,11000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Lumberjack - Within 0-5 Range - Cast Cleave"),
(1884,0,1,0,0,0,100,0,8000,13000,17000,21000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Lumberjack - In Combat - Cast Rend"),
(1884,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Lumberjack - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Priest
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=10608;
DELETE FROM `smart_scripts` WHERE `entryorguid`=10608 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10608,0,0,0,0,0,100,0,0,0,3400,4800,11,15498,64,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Priest - In Combat - Cast Holy Smite"),
(10608,0,1,0,16,0,100,0,13864,30,3000,6000,11,13864,0,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Priest - On Friendly Unit Missing Buff Power Word: Fortitude - Cast Power Word: Fortitude"),
(10608,0,2,0,14,0,100,0,2000,40,12000,15000,11,12039,1,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Priest - Friendly At 2000 Health - Cast Heal"),
(10608,0,3,0,14,0,100,0,1200,40,16000,19000,11,8362,1,0,0,0,0,7,0,0,0,0,0,0,0,"Scarlet Priest - Friendly At 1200 Health - Cast Renew"),
(10608,0,4,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Priest - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Executioner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1841;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1841 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1841,0,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Executioner - Between 0-30% Health - Cast Enrage"),
(1841,0,1,0,9,0,100,0,0,5,9000,14000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Executioner - Within 0-5 Range - Cast Mortal Strike"),
(1841,0,2,0,9,0,100,0,0,5,5000,9000,11,15284,1,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Executioner - Within 0-5 Range - Cast Cleave"),
(1841,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Executioner - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Judge
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1837;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1837 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1837,0,0,0,9,0,100,0,0,5,7000,12000,11,14518,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Judge - Within 0-5 Range - Cast Crusader Strike"),
(1837,0,1,0,0,0,100,0,6000,8000,9000,14000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Judge - In Combat - Cast Holy Strike"),
(1837,0,2,0,0,0,100,0,9000,14000,15000,18000,11,13005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Judge - In Combat - Cast Hammer of Justice"),
(1837,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Judge - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Cavalier
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1836;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1836 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1836,0,0,0,9,0,100,0,0,5,5000,9000,11,15284,1,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Cavalier - Within 0-5 Range - Cast Cleave"),
(1836,0,1,0,9,0,100,0,0,5,9000,14000,11,16856,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Cavalier - Within 0-5 Range - Cast Mortal Strike"),
(1836,0,2,0,0,0,100,0,6000,11000,12000,15000,11,6253,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Cavalier - In Combat - Cast Backhand"),
(1836,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Cavalier - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Scarlet Interrogator
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1838;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1838 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1838,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Interrogator - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Foreman Jerris
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1843;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1843 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1843,0,0,0,9,0,100,0,0,5,9000,14000,11,15618,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Jerris - Within 0-5 Range - Cast Snap Kick"),
(1843,0,1,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Jerris - In Combat - Cast Thrash"),
(1843,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Foreman Jerris - Between 0-15% Health - Flee For Assist (No Repeat)");
-- High Protector Lorik
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1846;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1846 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1846,0,0,0,13,0,100,1,1000,1000,0,0,11,15655,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Protector Lorik - Target Casting - Cast Shield Slam (No Repeat)"),
(1846,0,1,0,9,0,100,0,0,5,7000,12000,11,10833,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Protector Lorik - Within 0-5 Range - Cast Arcane Blast"),
(1846,0,2,0,11,0,100,0,0,0,0,0,11,8990,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Protector Lorik - On Respawn - Cast Retribution Aura"),
(1846,0,3,0,0,0,100,0,16000,21000,18000,21000,11,13874,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Protector Lorik - In Combat - Cast Divine Shield"),
(1846,0,4,0,14,0,100,1,1300,40,0,0,11,15493,1,0,0,0,0,7,0,0,0,0,0,0,0,"High Protector Lorik - On Friendly Between 0-40% Health - Cast Holy Light"),
(1846,0,5,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Protector Lorik - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Highlord Taelan Fordring
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1842;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1842 AND `id`>9 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1842,0,10,0,4,0,100,1,0,0,0,0,11,17232,0,0,0,0,0,1,0,0,0,0,0,0,0,"Highlord Taelan Fordring - On Aggro - Cast Devotion Aura"),
(1842,0,11,0,9,0,100,0,0,5,7000,12000,11,14518,0,0,0,0,0,2,0,0,0,0,0,0,0,"Highlord Taelan Fordring - Within 0-5 Range - Cast Crusader Strike"),
(1842,0,12,0,0,0,100,0,6000,8000,9000,14000,11,17143,0,0,0,0,0,2,0,0,0,0,0,0,0,"Highlord Taelan Fordring - In Combat - Cast Holy Strike"),
(1842,0,13,0,0,0,100,0,11000,15000,11000,13000,11,18819,0,0,0,0,0,2,0,0,0,0,0,0,0,"Highlord Taelan Fordring - In Combat - Cast Holy Cleave"),
(1842,0,14,0,14,0,100,0,1800,40,10000,13000,11,15493,0,0,0,0,0,7,0,0,0,0,0,0,0,"Highlord Taelan Fordring - On Friendly At 1800 Health - Cast Holy Light"),
(1842,0,15,0,2,0,100,1,0,15,0,0,11,17233,1,0,0,0,0,1,0,0,0,0,0,0,0,"Highlord Taelan Fordring - Between 0-15% Health - Cast Lay on Hands");
-- Foreman Marcrid
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1844;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1844 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1844,0,0,0,9,0,100,0,0,5,5000,8000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Marcrid - Within 0-5 Range - Cast Strike"),
(1844,0,1,0,9,0,100,0,0,5,9000,12000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Foreman Marcrid - Within 0-5 Range - Cast Cleave"),
(1844,0,2,0,2,0,100,1,0,20,0,0,39,40,1,0,0,0,0,1,0,0,0,0,0,0,0,"Foreman Marcrid - Between 0-20% Health - Call For Help (No Repeat)");
-- High Protector Tarsen
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1845;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1845 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1845,0,0,0,13,0,100,1,1000,1000,0,0,11,8242,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Protector Tarsen - Target Casting - Cast Shield Slam (No Repeat)"),
(1845,0,1,0,9,0,100,0,0,5,12000,16000,11,10833,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Protector Tarsen - Within 0-5 Range - Cast Arcane Blast"),
(1845,0,2,0,9,0,100,0,0,5,8000,11000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"High Protector Tarsen - Within 0-5 Range - Cast Holy Strike"),
(1845,0,3,0,0,0,100,0,1000,3000,240000,240000,11,8258,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Protector Tarsen - In Combat - Cast Devotion Aura"),
(1845,0,4,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Protector Tarsen - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Cavalier Durgen
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11611;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11611 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11611,0,0,0,11,0,100,0,0,0,0,0,11,13008,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cavalier Durgen - On Respawn - Cast Retribution Aura"),
(11611,0,1,0,0,0,100,0,6000,8000,9000,14000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cavalier Durgen - In Combat - Cast Holy Strike"),
(11611,0,2,0,0,0,100,0,9000,14000,15000,18000,11,13005,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cavalier Durgen - In Combat - Cast Hammer of Justice"),
(11611,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cavalier Durgen - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Huntsman Radley
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11613;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11613 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11613,0,0,0,1,0,100,1,1000,1000,0,0,11,18262,0,0,0,0,0,1,0,0,0,0,0,0,0,"Huntsman Radley - On Respawn - Cast Call Bloodshot"),
(11613,0,1,0,9,0,100,0,5,30,9000,12000,11,14443,0,0,0,0,0,5,0,0,0,0,0,0,0,"Huntsman Radley - Within 5-30 Range - Cast Multi-Shot"),
(11613,0,2,0,9,0,100,0,0,5,5000,8000,11,11976,1,0,0,0,0,2,0,0,0,0,0,0,0,"Huntsman Radley - Within 0-5 Range - Cast Strike"),
(11613,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Huntsman Radley - Between 0-15% Health - Flee For Assist (No Repeat)"),
(11613,0,4,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Huntsman Radley - In Combat CMC - Cast Shoot");
-- Bloodshot
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11614;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11614 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11614,0,0,0,9,0,100,0,0,5,15000,18000,11,13692,1,0,0,0,0,2,0,0,0,0,0,0,0,"Bloodshot - Within 0-5 Range - Cast Dire Growl");
DELETE FROM `creature` WHERE `guid`=52640;
DELETE FROM `creature_addon` WHERE `guid`=52640;

/* Eastern Plaguelands */

-- Living Decay
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8606;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8606 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8606,0,0,0,0,0,100,0,7000,12000,11000,18000,11,11442,32,0,0,0,0,2,0,0,0,0,0,0,0,"Living Decay - In Combat - Cast Withered Touch");

-- Mossflayer Zombie
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11290;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11290 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11290,0,0,0,9,0,100,0,0,5,9000,15000,11,3234,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mossflayer Zombie - Within 0-5 Range - Cast Disease Touch");

-- Scarlet Inquisitor
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15162;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15162 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15162,0,0,0,25,0,100,0,0,0,0,0,11,9276,0,0,0,0,0,1,0,0,0,0,0,0,0,"Scarlet Inquisitor - On Reset - Cast Immolate");

UPDATE `creature` SET `position_x`=1603.97, `position_y`=-5306.89, `position_z`=69.895, `orientation`=4.93402 WHERE `guid`=86149;
UPDATE `creature` SET `position_x`=1598.01, `position_y`=-5315.04, `position_z`=69.8807, `orientation`=3.27291 WHERE `guid`=84825;
UPDATE `creature` SET `position_x`=1594.68, `position_y`=-5313.46, `position_z`=69.8814, `orientation`=3.22185 WHERE `guid`=53036;

-- Remove wrong SAI and spawns for Skeletal Servant
DELETE FROM `creature` WHERE `guid` IN (92273, 92276, 92277, 92280, 52124, 52125, 52126, 52127, 52128, 52129, 52130, 52131, 52132, 52133, 52134, 52135, 52136, 52137, 52138, 52139, 52140);
DELETE FROM `creature_addon` WHERE `guid` IN (92273, 92276, 92277, 92280, 52124, 52125, 52126, 52127, 52128, 52129, 52130, 52131, 52132, 52133, 52134, 52135, 52136, 52137, 52138, 52139, 52140);

UPDATE `creature_template` SET `AIName`='' WHERE `entry`=8477;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8477;

/* Desolace */

-- Scorpashi Snapper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4696;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4696 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4696,0,0,0,0,0,100,0,3000,7000,14000,17000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpashi Snapper - In Combat - Cast Venom Sting");
-- Scorpashi Lasher
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4697;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4697 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4697,0,0,0,0,0,100,0,3000,7000,14000,17000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpashi Lasher - In Combat - Cast Venom Sting");
-- Scorpashi Venomlash
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4699;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4699 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4699,0,0,0,0,0,100,0,3000,7000,14000,17000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpashi Venomlash - In Combat - Cast Venom Sting");
-- Dread Swoop
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4692;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4692 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4692,0,0,0,9,0,100,0,0,5,9000,12000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dread Swoop - Within 0-5 Range - Cast Swoop");
-- Dread Flyer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4693;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4693 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4693,0,0,0,0,0,100,0,4000,10000,18000,34000,11,6713,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dread Flyer - In Combat - Cast Disarm");
-- Dread Ripper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4694;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4694 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4694,0,0,0,9,0,100,0,0,5,15000,18000,11,3147,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dread Ripper - Within 0-5 Range - Cast Rend Flesh");
-- Carrion Horror
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4695;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4695 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4695,0,0,0,0,0,100,0,5000,9000,12000,18000,11,3427,32,0,0,0,0,2,0,0,0,0,0,0,0,"Carrion Horror - In Combat - Cast Infected Wound");
-- Whirlwind Stormwalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11577;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11577 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11577,0,0,0,9,0,100,0,0,20,7000,12000,11,11824,0,0,0,0,0,2,0,0,0,0,0,0,0,"Whirlwind Stormwalker - Within 0-20 Range - Cast Shock");
-- Whirlwind Shredder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11578;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11578 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11578,0,0,0,9,0,100,0,0,5,17000,21000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Whirlwind Shredder - Within 0-5 Range - Cast Rend");
-- Raging Thunder Lizard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4726;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4726 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4726,0,0,0,9,0,100,0,0,30,5000,8000,11,15611,0,0,0,0,0,2,0,0,0,0,0,0,0,"Raging Thunder Lizard - Within 0-30 Range - Cast Lizard Bolt"),
(4726,0,1,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Raging Thunder Lizard - Betwenn 0-30% Health - Cast Enrage (No Repeat)");
-- Elder Thunder Lizard
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4727;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4727 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4727,0,0,0,9,0,100,0,0,30,5000,8000,11,15611,0,0,0,0,0,2,0,0,0,0,0,0,0,"Elder Thunder Lizard - In Combat - Cast Lizard Bolt");
-- Rabid Bonepaw
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4690;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4690 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4690,0,0,0,9,0,100,0,0,5,9000,15000,11,3150,32,0,0,0,0,2,0,0,0,0,0,0,0,"Rabid Bonepaw - Within 0-5 Range - Cast Rabies");
-- Slitherblade Naga
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4711;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4711 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4711,0,0,0,9,0,100,0,0,5,11000,15000,11,7947,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Naga - Within 0-5 Range - Cast Localized Toxin");
-- Slitherblade Sorceress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4712;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4712 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4712,0,0,0,0,0,100,0,0,0,3400,4700,11,32011,64,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Sorceress - In Combat - Cast Water Bolt"),
(4712,0,1,0,1,0,100,0,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Sorceress - Out of Combat - Cast Frost Armor");
-- Slitherblade Warrior
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4713;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4713 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4713,0,0,0,0,0,100,0,5000,9000,16000,21000,11,7947,32,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Warrior - In Combat - Cast Localized Toxin"),
(4713,0,1,0,9,0,100,0,0,5,12000,17000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Warrior - Within 0-5 Range - Cast Hamstring"),
(4713,0,2,0,0,0,100,0,8000,11000,19000,25000,11,11977,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Warrior - In Combat - Cast Rend"),
(4713,0,3,0,11,0,100,0,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Warrior - On Respawn - Cast Battle Stance");
-- Slitherblade Myrmidon
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4714;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4714 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4714,0,0,0,9,0,100,0,0,5,11000,15000,11,7947,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Myrmidon - Within 0-5 Range - Cast Localized Toxin");
-- Slitherblade Razortail
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4715;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4715 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4715,0,0,0,9,0,100,0,0,5,11000,15000,11,7947,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Razortail - Within 0-5 Range - Cast Localized Toxin");
-- Slitherblade Tidehunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4716;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4716 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4716,0,0,0,0,0,100,0,0,0,2300,3900,11,10277,64,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Tidehunter - In Combat CMC - Cast Throw"),
(4716,0,1,0,9,0,100,0,0,5,25000,29000,11,865,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Tidehunter - Within 0-5 Range - Cast Frost Nova"),
(4716,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Tidehunter - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Slitherblade Oracle
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4718;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4718 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4718,0,0,0,0,0,100,0,7000,12000,30000,40000,11,5605,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Oracle - In Combat - Cast Healing Ward"),
(4718,0,1,0,0,0,100,0,4000,7000,13000,16000,11,11436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Oracle - In Combat - Cast Slow");
-- Slitherblade Sea Witch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4719;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4719 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4719,0,0,0,1,0,100,0,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Slitherblade Sea Witch - Out of Combat - Cast Frost Armor"),
(4719,0,1,0,0,0,100,0,5000,9000,16000,24000,11,8427,0,0,0,0,0,2,0,0,0,0,0,0,0,"Slitherblade Sea Witch - In Combat - Cast Blizzard");
-- Kolkar Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4633;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4633 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4633,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Scout - In Combat CMC - Cast Shoot");
-- Kolkar Mauler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4634;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4634 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4634,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Mauler - In Combat - Cast Thrash");
-- Kolkar Windchaser
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4635;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4635 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4635,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Windchaser - In Combat CMC - Cast Lightning Bolt"),
(4635,0,1,0,0,0,100,0,7000,11000,15000,18000,11,6728,0,0,0,0,0,5,0,0,0,0,0,0,0,"Kolkar Windchaser - In Combat - Cast Enveloping Winds");
-- Kolkar Battle Lord
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4636;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4636 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4636,0,0,0,0,0,100,0,1000,3000,240000,240000,11,8258,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kolkar Battle Lord - In Combat - Cast Devotion Aura"),
(4636,0,1,0,9,0,100,0,0,5,8000,12000,11,25710,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Battle Lord - Within 0-5 Range - Cast Heroic Strike"),
(4636,0,2,0,11,0,100,0,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kolkar Battle Lord - On Respawn - Cast Battle Stance"),
(4636,0,3,0,2,0,100,1,0,20,0,0,39,30,0,0,0,0,0,7,0,0,0,0,0,0,0,"Kolkar Battle Lord - Between 0-20% Health - Call For Help (No Repeat)");
-- Kolkar Destroyer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4637;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4637 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4637,0,0,0,9,0,100,0,0,20,9000,14000,11,11824,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Destroyer - In Combat - Cast Shock"),
(4637,0,1,0,12,0,100,1,0,20,30000,35000,11,7160,1,0,0,0,0,2,0,0,0,0,0,0,0,"Kolkar Destroyer - Target Between 0-20% Health - Cast Execute");
-- Maraudine Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4654;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4654 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4654,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Scout - In Combat - Cast Shoot");
-- Maraudine Wrangler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4655;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4655 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4655,0,0,0,0,0,100,0,4000,10000,18000,34000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Wrangler - In Combat - Cast Net"),
(4655,0,1,0,9,0,100,0,0,5,12000,16000,11,8379,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Wrangler - Within 0-5 Range - Cast Disarm");
-- Maraudine Mauler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4656;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4656 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4656,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Mauler - In Combat - Cast Thrash");
-- Maraudine Windchaser
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4657;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4657 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4657,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Windchaser - In Combat CMC - Cast Lightning Bolt"),
(4657,0,1,0,0,0,100,0,7000,11000,15000,18000,11,6728,0,0,0,0,0,5,0,0,0,0,0,0,0,"Maraudine Windchaser - In Combat - Cast Enveloping Winds"),
(4657,0,2,0,14,0,100,0,700,40,17000,21000,11,959,1,0,0,0,0,7,0,0,0,0,0,0,0,"Maraudine Windchaser - Friendly At 700 Health - Cast Healing Wave");
-- Maraudine Stormer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4658;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4658 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4658,0,0,0,0,0,100,0,7000,12000,21000,26000,11,8293,0,0,0,0,0,4,0,0,0,0,0,0,0,"Maraudine Stormer - In Combat - Cast Lightning Cloud"),
(4658,0,1,0,1,0,100,0,1000,1000,600000,600000,11,8788,0,0,0,0,0,1,0,0,0,0,0,0,0,"Maraudine Stormer - Out of Combat - Cast Lightning Shield"),
(4658,0,2,0,16,0,100,0,8788,1,15000,30000,11,8788,0,0,0,0,0,1,0,0,0,0,0,0,0,"Maraudine Stormer - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield"),
(4658,0,3,0,0,0,100,0,0,0,11000,15000,11,9654,0,0,0,0,0,4,0,0,0,0,0,0,0,"Maraudine Stormer - In Combat - Cast Jumping Lightning");
-- Maraudine Marauder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4659;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4659 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4659,0,0,0,9,0,100,0,0,5,8000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Marauder  - Within 0-5 Range - Cast Cleave"),
(4659,0,1,0,4,0,100,1,0,0,0,0,11,7366,0,0,0,0,0,1,0,0,0,0,0,0,0,"Maraudine Marauder - On Aggro - Cast Berserker Stance");
-- Maraudine Priest
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11685;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11685 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11685,0,0,0,9,0,100,0,0,20,7000,10000,11,16568,0,0,0,0,0,2,0,0,0,0,0,0,0,"Maraudine Priest - Within 0-20 Range - Cast Mind Flay"),
(11685,0,1,0,0,0,100,0,7000,12000,21000,25000,11,11639,0,0,0,0,0,5,0,0,0,0,0,0,0,"Maraudine Priest - In Combat - Cast Shadow Word: Pain");
-- Ghostly Marauder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11687;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11687 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11687,0,0,0,9,0,100,0,0,5,6000,9000,11,11976,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Marauder - Within 0-5 Range - Cast Strike");
-- Ghostly Raider
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11686;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11686 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11686,0,0,0,0,0,100,0,0,0,2300,3000,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Raider - In Combat CMC - Cast Shoot"),
(11686,0,1,0,9,0,100,0,5,30,8000,12000,11,17174,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Raider - Within 5-30 Range - Cast Concussive Shot"),
(11686,0,2,0,9,0,100,0,0,20,5000,9000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ghostly Raider - Within 0-20 Range - Cast Net");
-- Rock Worm
UPDATE `creature_template` SET `AIName`="SmartAI", `unit_class`=2 WHERE `entry`=11788;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11788 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11788,0,0,0,0,0,100,0,0,0,3400,4100,11,9591,64,0,0,0,0,2,0,0,0,0,0,0,0,"Rock Worm - In Combat - Cast Acid Spit");
-- Rock Borer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11787;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11787 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11787,0,0,0,9,0,100,0,0,5,7000,12000,11,14120,0,0,0,0,0,2,0,0,0,0,0,0,0,"Rock Borer - Within 0-5 Range - Cast Tunneler Acid");
-- Drysnap Crawler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11562;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11562 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11562,0,0,0,1,0,100,0,500,1000,600000,600000,11,12544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Drysnap Crawler - Out of Combat - Cast Frost Armor"),
(11562,0,1,0,9,0,100,0,0,20,7000,12000,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drysnap Crawler - Within 0-20 Range - Cast Frost Shock");
-- Drysnap Pincer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11563;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11563 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11563,0,0,0,9,0,100,0,0,5,8000,12000,11,13444,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drysnap Pincer - Within 0-5 Range - Cast Sunder Armor"),
(11563,0,1,0,0,0,100,0,5000,9000,18000,22000,11,13443,0,0,0,0,0,2,0,0,0,0,0,0,0,"Drysnap Pincer - In Combat - Cast Rend");
-- Lesser Infernal
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4676;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4676 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4676,0,0,0,0,0,100,0,1000,3000,30000,35000,11,2601,1,0,0,0,0,1,0,0,0,0,0,0,0,"Lesser Infernal - In Combat - Cast Fire Shield III");
-- Nether Maiden
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4679;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4679 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4679,0,0,0,9,0,100,0,0,5,12000,15000,11,7816,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nether Maiden - Within 0-5 Range - Cast Lash of Pain");
-- Doomwarder Captain
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4680;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4680 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4680,0,0,0,0,0,100,0,1000,6000,16000,25000,11,6192,2,0,0,0,0,1,0,0,0,0,0,0,0,"Doomwarder Captain - In Combat - Cast Battle Shout"),
(4680,0,1,0,9,0,100,0,0,5,8000,12000,11,3261,32,0,0,0,0,4,0,0,0,0,0,0,0,"Doomwarder Captain - Within 0-5 Range - Cast Ignite");
-- Nether Sister
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4682;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4682 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4682,0,0,0,9,0,100,0,0,5,12000,15000,11,7816,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nether Sister - Within 0-5 Range - Cast Lash of Pain");
-- Nether Sorceress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4684;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4684 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4684,0,0,0,0,0,100,0,0,0,3400,4700,11,20297,64,0,0,0,0,2,0,0,0,0,0,0,0,"Nether Sorceress - In Combat - Cast Frostbolt"),
(4684,0,1,0,9,0,100,0,0,8,12000,15000,11,11831,1,0,0,0,0,1,0,0,0,0,0,0,0,"Nether Sorceress - Within 0-8 Range - Cast Frost Nova"),
(4684,0,2,0,9,0,100,0,0,5,12000,15000,11,7816,1,0,0,0,0,2,0,0,0,0,0,0,0,"Nether Sorceress - Within 0-5 Range - Cast Lash of Pain");
-- Ley Hunter
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4685;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4685 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4685,0,0,0,9,0,100,0,0,30,9000,15000,11,22189,0,0,0,0,0,2,0,0,0,0,0,0,0,"Ley Hunter - Within 0-30 Range - Cast Mana Burn");
-- Lord Azrethoc
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5760;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5760 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5760,0,0,0,9,0,100,0,0,5,9000,14000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Azrethoc - In Combat - Cast Mortal Strike");
-- Undead Ravager
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11561;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11561 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11561,0,0,0,13,0,100,0,7000,10000,0,0,11,11978,0,0,0,0,0,2,0,0,0,0,0,0,0,"Undead Ravager - Target Casting - Cast Kick");
-- Outcast Necromancer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=11559;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11559 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11559,0,0,0,0,0,100,0,0,0,3400,4700,11,20298,64,0,0,0,0,2,0,0,0,0,0,0,0,"Outcast Necromancer - In Combat - Cast Shadow Bolt"),
(11559,0,1,0,0,0,100,1,12000,18000,0,0,11,18166,0,0,0,0,0,1,0,0,0,0,0,0,0,"Outcast Necromancer - In Combat - Cast Summon Magram Ravager (No Repeat)");
-- Khan Jehn
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5601;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5601 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5601,0,0,0,4,0,100,1,0,0,0,0,11,7164,0,0,0,0,0,1,0,0,0,0,0,0,0,"Khan Jehn - On Aggro - Cast Defensive Stance"),
(5601,0,1,0,13,0,100,0,13000,18000,0,0,11,11972,0,0,0,0,0,7,0,0,0,0,0,0,0,"Khan Jehn - Target Casting - Cast Shield Bash"),
(5601,0,2,0,9,0,100,0,0,5,5000,9000,11,8380,0,0,0,0,0,2,0,0,0,0,0,0,0,"Khan Jehn - Within 0-5 Range - Cast Sunder Armor");
-- Magram Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4638;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4638 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4638,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Magram Scout - In Combat - Cast Shoot");
-- Magram Wrangler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4640;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4640 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4640,0,0,0,9,0,100,0,0,20,18000,24000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,"Magram Wrangler - Within 0-20 Range - Cast Net");
-- Magram Windchaser
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4641;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4641 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4641,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Magram Windchaser - In Combat CMC - Cast Lightning Bolt"),
(4641,0,1,0,14,0,100,0,700,40,17000,21000,11,959,1,0,0,0,0,7,0,0,0,0,0,0,0,"Magram Windchaser - Friendly At 700 Health - Cast Healing Wave");
-- Magram Stormer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4642;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4642 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4642,0,0,0,0,0,100,0,2000,4500,22000,27000,11,6535,0,0,0,0,0,4,0,0,0,0,0,0,0,"Magram Stormer - In Combat - Cast Lightning Cloud"),
(4642,0,1,0,1,0,100,0,500,1000,600000,600000,11,8788,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magram Stormer - Out of Combat - Cast Lightning Shield"),
(4642,0,2,0,16,0,100,0,19514,1,15000,30000,11,8788,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magram Stormer - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield");
-- Magram Marauder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4644;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4644 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4644,0,0,0,9,0,100,0,0,5,8000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Magram Marauder - Within 0-5 Range - Cast Cleave"),
(4644,0,1,0,4,0,100,1,0,0,0,0,11,7366,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magram Marauder - On Aggro - Cast Berserker Stance");
-- Magram Mauler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4645;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4645 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4645,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Magram Mauler - In Combat - Cast Thrash");
-- Gelkis Scout
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4647;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4647 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4647,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gelkis Scout - In Combat CMC - Cast Shoot");
-- Gelkis Stamper
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4648;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4648 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4648,0,0,0,9,0,100,0,0,8,6000,9000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gelkis Stamper - Within 0-8 Range - Cast Trample");
-- Gelkis Windchaser
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4649;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4649 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4649,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gelkis Windchaser - In Combat CMC - Cast Lightning Bolt"),
(4649,0,1,0,14,0,100,0,700,40,17000,21000,11,959,1,0,0,0,0,7,0,0,0,0,0,0,0,"Gelkis Windchaser - Friendly At 700 Health - Cast Healing Wave");
-- Gelkis Earthcaller
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4651;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4651 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4651,0,0,0,0,0,100,0,0,0,3400,4800,11,20815,64,0,0,0,0,2,0,0,0,0,0,0,0,"Gelkis Earthcaller - In Combat CMC - Cast Fireball"),
(4651,0,1,0,1,0,100,1,1000,1000,0,0,11,9653,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gelkis Earthcaller - Out of Combat - Cast Summon Gelkis Rumbler");
-- Gelkis Mauler
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4652;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4652 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4652,0,0,0,0,0,100,0,8000,12000,15000,20000,11,3391,2,0,0,0,0,2,0,0,0,0,0,0,0,"Gelkis Mauler - In Combat - Cast Thrash");
-- Gelkis Marauder
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=4653;
DELETE FROM `smart_scripts` WHERE `entryorguid`=4653 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4653,0,0,0,9,0,100,0,0,5,8000,12000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gelkis Marauder - Within 0-5 Range - Cast Cleave"),
(4653,0,1,0,4,0,100,1,0,0,0,0,11,7366,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gelkis Marauder - On Aggro - Cast Berserker Stance");
-- Remove wrong spawns for Gelkis Rumbler
DELETE FROM `creature` WHERE `guid` IN (27587, 27588, 27589, 27590, 27591, 27592, 27593, 27594, 27595, 27596, 27597, 27598, 27599, 27600);
DELETE FROM `creature_addon` WHERE `guid` IN (27587, 27588, 27589, 27590, 27591, 27592, 27593, 27594, 27595, 27596, 27597, 27598, 27599, 27600);
DELETE FROM `creature_equip_template` WHERE `entry` IN (4663, 4664, 4665, 4666);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(4665,1,2559,0,0,0),
(4666,1,5285,5281,0,0),
(4663,1,5303,0,0,0),
(4664,1,4991,0,0,0);