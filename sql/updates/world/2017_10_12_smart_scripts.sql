/* Durotar */

-- Scorpid Worker
DELETE FROM `smart_scripts` WHERE `entryorguid`=3124 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3124,0,0,0,0,0,100,0,4000,8000,6000,12000,11,6751,32,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpid Worker - In Combat - Cast Weak Poison");
-- Sarkoth
DELETE FROM `smart_scripts` WHERE `entryorguid`=3281 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3281,0,0,0,0,0,100,0,5000,8000,5000,8000,11,11918,32,0,0,0,0,2,0,0,0,0,0,0,0,"Sarkoth - In Combat - Cast Poison");
-- Yarrog Baneshadow
DELETE FROM `smart_scripts` WHERE `entryorguid`=3183 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3183,0,0,0,9,0,100,0,0,30,15000,19000,11,172,0,0,0,0,0,2,0,0,0,0,0,0,0,"Yarrog Baneshadow - Within 0-30 Range - Cast Corruption"),
(3183,0,1,0,0,0,100,0,6000,8000,18000,22000,11,348,0,0,0,0,0,2,0,0,0,0,0,0,0,"Yarrog Baneshadow - In Combat - Cast Immolate");
-- Clattering Scorpid
DELETE FROM `smart_scripts` WHERE `entryorguid`=3125 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3125,0,0,0,0,0,100,0,5000,8000,6000,12000,11,11918,32,0,0,0,0,2,0,0,0,0,0,0,0,"Clattering Scorpid - In Combat - Cast Poison");
-- Venomtail Scorpid
DELETE FROM `smart_scripts` WHERE `entryorguid`=3127 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3127,0,0,0,0,0,100,0,5000,8000,6000,12000,11,5416,32,0,0,0,0,2,0,0,0,0,0,0,0,"Venomtail Scorpid - In Combat - Cast Venom Sting");
-- Kolkar Drudge
DELETE FROM `smart_scripts` WHERE `entryorguid`=3119 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3119,0,0,0,0,0,100,0,6000,11000,15000,22000,11,7272,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kolkar Drudge - In Combat - Cast Dust Cloud");
-- Warlord Kolkanis
DELETE FROM `smart_scripts` WHERE `entryorguid`=5808 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5808,0,0,0,13,0,100,0,15000,25000,0,0,11,12555,0,0,0,0,0,7,0,0,0,0,0,0,0,"Warlord Kolkanis - Target Casting - Cast Pummel"),
(5808,0,1,0,9,0,100,0,0,8,16000,23000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"Warlord Kolkanis - Within 0-8 Range - Cast Thunderclap"),
(5808,0,2,0,0,0,100,0,8000,12000,10000,14000,11,12555,0,0,0,0,0,2,0,0,0,0,0,0,0,"Warlord Kolkanis - In Combat - Cast Pummel");
-- Encrusted Surf Crawler
DELETE FROM `smart_scripts` WHERE `entryorguid`=3108 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3108,0,0,0,0,0,100,0,9000,16000,30000,40000,11,5426,0,0,0,0,0,1,0,0,0,0,0,0,0,"Encrusted Surf Crawler - In Combat - Cast Quick Sidestep");
-- Makrura Snapclaw
DELETE FROM `smart_scripts` WHERE `entryorguid`=3105 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3105,0,0,0,0,0,100,0,6000,9000,15000,21000,11,5424,0,0,0,0,0,2,0,0,0,0,0,0,0,"Makrura Snapclaw - In Combat - Cast Claw Grasp");
-- Makrura Elder
DELETE FROM `smart_scripts` WHERE `entryorguid`=3141 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3141,0,0,0,0,0,100,0,6000,9000,15000,21000,11,5424,0,0,0,0,0,2,0,0,0,0,0,0,0,"Makrura Elder - In Combat - Cast Claw Grasp");
-- Voodoo Troll
DELETE FROM `smart_scripts` WHERE `entryorguid`=3206 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3206,0,0,0,1,0,100,0,500,1000,600000,600000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Voodoo Troll - Out of Combat - Cast Lightning Shield"),
(3206,0,1,0,16,0,100,0,324,1,15000,30000,11,324,0,0,0,0,0,1,0,0,0,0,0,0,0,"Voodoo Troll - On Friendly Unit Missing Buff Lightning Shield - Cast Lightning Shield"),
(3206,0,2,0,2,0,100,0,0,50,16000,21000,11,332,0,0,0,0,0,1,0,0,0,0,0,0,0,"Voodoo Troll - Between 0-50% Health - Cast Healing Wave");
-- Zalazane
DELETE FROM `smart_scripts` WHERE `entryorguid`=3205 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3205,0,0,0,2,0,100,0,0,50,16000,21000,11,332,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zalazane - Between 0-50% Health - Cast Healing Wave"),
(3205,0,1,0,0,0,100,0,6000,11000,12000,21000,11,7289,32,0,0,0,0,2,0,0,0,0,0,0,0,"Zalazane - In Combat - Cast Shrink");
-- Lieutenant Benedict
DELETE FROM `smart_scripts` WHERE `entryorguid`=3192 AND `source_type`=0 AND `id` IN (1,2,3);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3192,0,1,0,13,0,100,0,20000,30000,0,0,11,72,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Benedict - Target Casting - Cast Shield Bash"),
(3192,0,2,0,0,0,100,0,10000,13000,14000,20000,11,11972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Benedict - In Combat - Cast Shield Bash"),
(3192,0,3,0,0,0,100,0,7000,12000,15000,21000,11,3248,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lieutenant Benedict - In Combat - Cast Improved Blocking");
-- Kul Tiras Marine
DELETE FROM `smart_scripts` WHERE `entryorguid`=3129 AND `source_type`=0 AND `id` IN (3,4);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3129,0,3,0,54,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kul Tiras Marine - Just Summoned - Say Line 0"),
(3129,0,4,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,20,0,0,0,0,0,0,"Kul Tiras Marine - Just Summoned - Start Attack");
DELETE FROM `creature_text` WHERE `entry`=3129;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(3129,0,0,"Step away from the Lieutenant's belongings!",12,0,100,0,0,0,0,"Kul Tiras Marine");
-- Razormane Quilboar
DELETE FROM `smart_scripts` WHERE `entryorguid`=3111 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3111,0,1,0,0,0,100,0,0,0,45000,50000,11,5280,0,0,0,0,0,1,0,0,0,0,0,0,0,"Razormane Quilboar - In Combat - Cast Razor Mane");
-- Razormane Dustrunner
DELETE FROM `smart_scripts` WHERE `entryorguid`=3113 AND `source_type`=0 AND `id` IN (0,1);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3113,0,0,0,0,0,100,0,4000,9000,30000,35000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Razormane Dustrunner - In Combat - Cast Faerie Fire"),
(3113,0,1,0,14,0,100,0,100,40,14000,21000,11,774,0,0,0,0,0,7,0,0,0,0,0,0,0,"Razormane Dustrunner - Friendly At 100 Health - Cast Rejuvenation");
-- Razormane Battleguard
DELETE FROM `smart_scripts` WHERE `entryorguid`=3114 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3114,0,0,0,0,0,100,0,3000,8000,11000,19000,11,3248,0,0,0,0,0,1,0,0,0,0,0,0,0,"Razormane Battleguard - In Combat - Cast Improved Blocking");
-- Captain Flat Tusk
DELETE FROM `smart_scripts` WHERE `entryorguid`=5824 AND `source_type`=0 AND `id` IN (0,1);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5824,0,0,0,25,0,100,0,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captain Flat Tusk - On Reset - Cast Battle Stance"),
(5824,0,1,0,0,0,100,0,6000,9000,7000,12000,11,25710,0,0,0,0,0,2,0,0,0,0,0,0,0,"Captain Flat Tusk - In Combat - Cast Heroic Strike");
-- Dreadmaw Crocolisk
DELETE FROM `smart_scripts` WHERE `entryorguid`=3110 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3110,0,0,0,0,0,100,0,5000,9000,12000,16000,11,12166,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadmaw Crocolisk - In Combat - Cast Muscle Tear");
-- Corrupted Dreadmaw Crocolisk
DELETE FROM `smart_scripts` WHERE `entryorguid`=3231 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3231,0,0,0,0,0,100,0,5000,8000,6000,12000,11,7901,32,0,0,0,0,2,0,0,0,0,0,0,0,"Corrupted Dreadmaw Crocolisk - In Combat - Cast Decayed Agility");
-- Burning Blade Neophyte
DELETE FROM `smart_scripts` WHERE `entryorguid`=3196 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3196,0,0,0,0,0,100,0,3000,5000,18000,24000,11,348,0,0,0,0,0,2,0,0,0,0,0,0,0,"Burning Blade Neophyte - In Combat - Cast Immolate");
-- Burning Blade Apprentice
UPDATE `smart_scripts` SET `event_param3`=3400, `event_param4`=4800 WHERE `entryorguid`=3198 AND `source_type`=0 AND `id`=1;
-- Fizzle Darkstorm
UPDATE `smart_scripts` SET `event_param3`=3400, `event_param4`=4800 WHERE `entryorguid`=3203 AND `source_type`=0 AND `id`=1;
-- Thunder Lizard
DELETE FROM `smart_scripts` WHERE `entryorguid`=3130 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3130,0,0,0,0,0,100,0,4000,9000,6000,11000,11,5401,0,0,0,0,0,2,0,0,0,0,0,0,0,"Thunder Lizard - In Combat - Cast Lizard Bolt");
-- Lightning Hide
DELETE FROM `smart_scripts` WHERE `entryorguid`=3131 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3131,0,0,0,0,0,100,0,4000,9000,6000,11000,11,5401,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lightning Hide - In Combat - Cast Lizard Bolt");
-- Dustwind Pillager
DELETE FROM `smart_scripts` WHERE `entryorguid`=3116 AND `source_type`=0 AND `id`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3116,0,0,0,0,0,100,0,5000,11000,18000,24000,11,3147,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dustwind Pillager - In Combat - Cast Rend Flesh");
-- Dustwind Storm Witch
UPDATE `smart_scripts` SET `event_param3`=3400, `event_param4`=4800 WHERE `entryorguid`=3118 AND `source_type`=0 AND `id`=0;
-- Random movement for some creatures
UPDATE `creature` SET `MovementType`=1, `spawndist`=3 WHERE `guid` IN (12188, 12183, 12186, 12951, 12185, 12195, 12190, 12184, 12956, 12202, 12204, 6435, 6436, 7333, 7342, 6420, 7335, 7337, 7883, 7899, 6424, 7897, 8428, 8429, 6426, 7334, 7880, 7900, 7338, 7339, 6421, 6418, 7885, 6423, 6422, 7901, 7336, 7898, 6425, 7340, 7884, 6417, 7882, 6419);
-- Correct spawn position for one creature
UPDATE `creature` SET `position_x`=1421.6, `position_y`=-4770.55, `position_z`=4.49296 WHERE `guid`=7336;

/* Silithus */

-- Azure Templar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15211;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15211 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15211,0,0,0,0,0,100,0,3000,5000,8000,12000,11,12548,0,0,0,0,0,2,0,0,0,0,0,0,0,"Azure Templar - In Combat - Cast Frost Shock"),
(15211,0,1,0,0,0,100,0,7000,9000,11000,15000,11,14907,0,0,0,0,0,1,0,0,0,0,0,0,0,"Azure Templar - In Combat - Cast Frost Nova");
DELETE FROM `creature_text` WHERE `entry`=15211 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15211,0,1,"My lord will be outraged to learn of this ambush.  Let us hope your death will appease him.",12,0,100,0,0,0,0,"Azure Templar"),
(15211,0,2,"It is my duty and honor to die for the Abyssal Council!",12,0,100,0,0,0,0,"Azure Templar"),
(15211,0,3,"Your life is a fitting sacrifice for my master, $c.",12,0,100,0,0,0,0,"Azure Templar");
-- Earthen Templar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15307;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15307 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15307,0,0,0,0,0,100,0,2000,3000,13000,15000,11,22127,2,0,0,0,0,2,0,0,0,0,0,0,0,"Earthen Templar - In Combat - Cast Entangling Roots"),
(15307,0,1,0,0,0,100,0,7000,9000,12000,16000,11,18813,0,0,0,0,0,2,0,0,0,0,0,0,0,"Earthen Templar - In Combat - Cast Knock Away");
DELETE FROM `creature_text` WHERE `entry`=15307 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15307,0,1,"My lord will be outraged to learn of this ambush.  Let us hope your death will appease him.",12,0,100,0,0,0,0,"Earthen Templar"),
(15307,0,2,"It is my duty and honor to die for the Abyssal Council!",12,0,100,0,0,0,0,"Earthen Templar"),
(15307,0,3,"Your life is a fitting sacrifice for my master, $c.",12,0,100,0,0,0,0,"Earthen Templar");
-- Hoary Templar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15212;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15212 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15212,0,0,0,0,0,100,0,3000,5000,7000,11000,11,2610,2,0,0,0,0,2,0,0,0,0,0,0,0,"Hoary Templar - In Combat - Cast Shock"),
(15212,0,1,0,4,0,100,0,0,0,0,0,11,25020,0,0,0,0,0,1,0,0,0,0,0,0,0,"Hoary Templar - On Aggro - Cast Lightning Shield");
DELETE FROM `creature_text` WHERE `entry`=15212 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15212,0,1,"My lord will be outraged to learn of this ambush.  Let us hope your death will appease him.",12,0,100,0,0,0,0,"Hoary Templar"),
(15212,0,2,"It is my duty and honor to die for the Abyssal Council!",12,0,100,0,0,0,0,"Hoary Templar"),
(15212,0,3,"Your life is a fitting sacrifice for my master, $c.",12,0,100,0,0,0,0,"Hoary Templar");
-- Crimson Templar
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15209;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15209 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15209,0,0,0,0,0,100,0,4000,6000,7000,11000,11,11989,0,0,0,0,0,1,0,0,0,0,0,0,0,"Crimson Templar - In Combat - Cast Fireball Volley"),
(15209,0,1,0,0,0,100,0,2000,3000,11000,15000,11,16536,0,0,0,0,0,2,0,0,0,0,0,0,0,"Crimson Templar - In Combat - Cast Flame Buffet");
DELETE FROM `creature_text` WHERE `entry`=15209 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15209,0,1,"My lord will be outraged to learn of this ambush.  Let us hope your death will appease him.",12,0,100,0,0,0,0,"Crimson Templar"),
(15209,0,2,"It is my duty and honor to die for the Abyssal Council!",12,0,100,0,0,0,0,"Crimson Templar"),
(15209,0,3,"Your life is a fitting sacrifice for my master, $c.",12,0,100,0,0,0,0,"Crimson Templar");
-- The Duke of Cynders
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15206;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15206 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15206,0,0,0,0,0,100,0,3000,6000,6000,9000,11,25028,0,0,0,0,0,5,0,0,0,0,0,0,0,"The Duke of Cynders - In Combat - Cast Fire Blast"),
(15206,0,1,0,0,0,100,0,8000,14000,12000,17000,11,18399,0,0,0,0,0,5,0,0,0,0,0,0,0,"The Duke of Cynders - In Combat - Cast Flamestrike"),
(15206,0,2,0,0,0,100,0,6000,10000,8000,12000,11,22424,0,0,0,0,0,1,0,0,0,0,0,0,0,"The Duke of Cynders - In Combat - Cast Blast Wave");
DELETE FROM `creature_text` WHERE `entry`=15206 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15206,0,1,"You will pay the ultimate price for this insolence, little vermin.  Your soul is mine!",12,0,100,0,0,0,0,"The Duke of Cynders"),
(15206,0,2,"This act of defiance will not go unpunished.  You, and your world, will die!",12,0,100,0,0,0,0,"The Duke of Cynders"),
(15206,0,3,"Imposter!  It is a dishonor without equal to be summoned by a whelp such as you!  DIE!",12,0,100,0,0,0,0,"The Duke of Cynders");
-- The Duke of Fathoms
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15207;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15207 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15207,0,0,0,4,0,100,0,0,0,0,0,11,3417,0,0,0,0,0,1,0,0,0,0,0,0,0,"The Duke of Fathoms - On Aggro - Cast Thrash"),
(15207,0,1,0,0,0,100,0,8000,12000,8000,12000,11,16790,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Duke of Fathoms - In Combat - Cast Knockdown"),
(15207,0,2,0,0,0,100,0,3000,6000,10000,15000,11,18670,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Duke of Fathoms - In Combat - Cast Knock Away");
DELETE FROM `creature_text` WHERE `entry`=15207 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15207,0,1,"You will pay the ultimate price for this insolence, little vermin.  Your soul is mine!",12,0,100,0,0,0,0,"The Duke of Fathoms"),
(15207,0,2,"This act of defiance will not go unpunished.  You, and your world, will die!",12,0,100,0,0,0,0,"The Duke of Fathoms"),
(15207,0,3,"Imposter!  It is a dishonor without equal to be summoned by a whelp such as you!  DIE!",12,0,100,0,0,0,0,"The Duke of Fathoms");
-- The Duke of Shards
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15208;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15208 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15208,0,0,0,0,0,100,0,4000,6000,4000,6000,11,13446,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Duke of Shards - In Combat - Cast Strike"),
(15208,0,1,0,0,0,100,0,8000,12000,13000,17000,11,8078,0,0,0,0,0,1,0,0,0,0,0,0,0,"The Duke of Shards - In Combat - Cast Thunderclap"),
(15208,0,2,0,0,0,100,0,6000,10000,10000,15000,11,6524,0,0,0,0,0,1,0,0,0,0,0,0,0,"The Duke of Shards - In Combat - Cast Ground Tremor");
DELETE FROM `creature_text` WHERE `entry`=15208 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15208,0,1,"You will pay the ultimate price for this insolence, little vermin.  Your soul is mine!",12,0,100,0,0,0,0,"The Duke of Shards"),
(15208,0,2,"This act of defiance will not go unpunished.  You, and your world, will die!",12,0,100,0,0,0,0,"The Duke of Shards"),
(15208,0,3,"Imposter!  It is a dishonor without equal to be summoned by a whelp such as you!  DIE!",12,0,100,0,0,0,0,"The Duke of Shards");
-- The Duke of Zephyrs
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15220;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15220 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15220,0,0,0,0,0,100,0,5000,8000,14000,18000,11,25034,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Duke of Zephyrs - In Combat - Cast Forked Lightning"),
(15220,0,1,0,0,0,100,0,10000,12000,18000,22000,11,44417,0,0,0,0,0,5,0,0,0,0,0,0,0,"The Duke of Zephyrs - In Combat - Cast Lightning Cloud"),
(15220,0,2,0,0,0,100,0,5000,15000,10000,15000,11,12882,0,0,0,0,0,1,0,0,0,0,0,0,0,"The Duke of Zephyrs - In Combat - Cast Wing Flap"),
(15220,0,3,0,0,0,100,0,8000,20000,8000,20000,11,15535,0,0,0,0,0,5,0,0,0,0,0,0,0,"The Duke of Zephyrs - In Combat - Cast Enveloping Winds");
DELETE FROM `creature_text` WHERE `entry`=15220 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15220,0,1,"You will pay the ultimate price for this insolence, little vermin.  Your soul is mine!",12,0,100,0,0,0,0,"The Duke of Zephyrs"),
(15220,0,2,"This act of defiance will not go unpunished.  You, and your world, will die!",12,0,100,0,0,0,0,"The Duke of Zephyrs"),
(15220,0,3,"Imposter!  It is a dishonor without equal to be summoned by a whelp such as you!  DIE!",12,0,100,0,0,0,0,"The Duke of Zephyrs");
-- Prince Skaldrenox
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15203;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15203 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15203,0,0,0,0,0,100,0,4000,6000,20000,30000,11,25050,0,0,0,0,0,4,0,0,0,0,0,0,0,"Prince Skaldrenox - In Combat - Cast Mark of Flames"),
(15203,0,1,0,0,0,100,0,8000,10000,15000,24000,11,25049,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prince Skaldrenox - In Combat - Cast Blastwave"),
(15203,0,2,0,0,0,100,0,7000,8000,7000,8000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prince Skaldrenox - In Combat - Cast Cleave");
DELETE FROM `creature_text` WHERE `entry`=15203 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15203,0,1,"You dare!  Outrageous!  I curse you, $c.  I curse you with... death!",14,0,100,0,0,0,0,"Prince Skaldrenox"),
(15203,0,2,"What?  Such a small, frail thing beckons me?  I shall add your bones to my throne, $r!!",14,0,100,0,0,0,0,"Prince Skaldrenox"),
(15203,0,3,"Killing you and your cohorts, $c, will amuse me.  I shall make it quick.",14,0,100,0,0,0,0,"Prince Skaldrenox");
-- High Marshal Whirlaxis
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15204;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15204 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15204,0,0,0,0,0,100,0,0,0,5000,5000,11,25020,32,0,0,0,0,1,0,0,0,0,0,0,0,"High Marshal Whirlaxis - In Combat - Cast Lightning Shield"),
(15204,0,1,0,0,0,100,0,9000,11000,21000,26000,11,23103,0,0,0,0,0,5,0,0,0,0,0,0,0,"High Marshal Whirlaxis - In Combat - Cast Enveloping Winds"),
(15204,0,2,0,0,0,100,0,17000,20000,17000,20000,11,25060,0,0,0,0,0,1,0,0,0,0,0,0,0,"High Marshal Whirlaxis - In Combat - Cast Updraft");
DELETE FROM `creature_text` WHERE `entry`=15204 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15204,0,1,"You dare!  Outrageous!  I curse you, $c.  I curse you with... death!",14,0,100,0,0,0,0,"High Marshal Whirlaxis"),
(15204,0,2,"What?  Such a small, frail thing beckons me?  I shall add your bones to my throne, $r!!",14,0,100,0,0,0,0,"High Marshal Whirlaxis"),
(15204,0,3,"Killing you and your cohorts, $c, will amuse me.  I shall make it quick.",14,0,100,0,0,0,0,"High Marshal Whirlaxis");
-- Baron Kazum
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15205;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15205 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15205,0,0,0,0,0,100,0,3000,6000,13000,16000,11,25056,0,0,0,0,0,1,0,0,0,0,0,0,0,"Baron Kazum - In Combat - Cast Stomp"),
(15205,0,1,0,0,0,100,0,7000,10000,15000,28000,11,19129,0,0,0,0,0,1,0,0,0,0,0,0,0,"Baron Kazum - In Combat - Cast Massive Tremor"),
(15205,0,2,0,0,0,100,0,12000,15000,15000,18000,11,17547,0,0,0,0,0,2,0,0,0,0,0,0,0,"Baron Kazum - In Combat - Cast Mortal Strike");
DELETE FROM `creature_text` WHERE `entry`=15205 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15205,0,1,"You dare!  Outrageous!  I curse you, $c.  I curse you with... death!",14,0,100,0,0,0,0,"Baron Kazum"),
(15205,0,2,"What?  Such a small, frail thing beckons me?  I shall add your bones to my throne, $r!!",14,0,100,0,0,0,0,"Baron Kazum"),
(15205,0,3,"Killing you and your cohorts, $c, will amuse me.  I shall make it quick.",14,0,100,0,0,0,0,"Baron Kazum");
-- Lord Skwol
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15305;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15305 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15305,0,0,0,4,0,100,0,0,0,0,0,11,3417,0,0,0,0,0,1,0,0,0,0,0,0,0,"Lord Skwol - On Aggro - Cast Thrash"),
(15305,0,1,0,0,0,100,0,10000,12000,18000,20000,11,25053,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Skwol - In Combat - Cast Venom Spit"),
(15305,0,2,0,0,0,100,0,2000,3000,5000,8000,11,25051,0,0,0,0,0,2,0,0,0,0,0,0,0,"Lord Skwol - In Combat - Cast Sunder Armor");
DELETE FROM `creature_text` WHERE `entry`=15305 AND `ID`>0;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(15305,0,1,"You dare!  Outrageous!  I curse you, $c.  I curse you with... death!",14,0,100,0,0,0,0,"Lord Skwol"),
(15305,0,2,"What?  Such a small, frail thing beckons me?  I shall add your bones to my throne, $r!!",14,0,100,0,0,0,0,"Lord Skwol"),
(15305,0,3,"Killing you and your cohorts, $c, will amuse me.  I shall make it quick.",14,0,100,0,0,0,0,"Lord Skwol");

/* Mulgore */

-- Bristleback Battleboar
UPDATE `smart_scripts` SET `event_chance`=100 WHERE `entryorguid`=2954 AND `source_type`=0;
-- Bristleback Shaman
UPDATE `smart_scripts` SET `event_param3`=3400, `event_param4`=4800 WHERE `entryorguid`=2953 AND `source_type`=0 AND `id`=0;
-- Elder Plainstrider
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2957;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2957 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2957,0,0,0,0,0,100,0,6000,10000,19000,24000,11,7272,0,0,0,0,0,1,0,0,0,0,0,0,0,"Elder Plainstrider - In Combat - Cast Dust Cloud");
-- Prairie Wolf
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2958;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2958 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2958,0,0,1,1,0,100,0,30000,600000,120000,600000,4,1018,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Wolf - Out of Combat - Play Sound 1018"),
(2958,0,1,0,61,0,100,0,0,0,0,0,5,393,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Wolf - Out of Combat - Play Emote 393"),
(2958,0,2,0,0,0,100,0,6000,10000,35000,45000,11,5781,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prairie Wolf - In Combat - Cast Threatening Growl");
-- Prairie Stalker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2959;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2959 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2959,0,0,1,1,0,100,0,30000,600000,120000,600000,4,1018,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Stalker - Out of Combat - Play Sound 1018"),
(2959,0,1,0,61,0,100,0,0,0,0,0,5,393,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Stalker - Out of Combat - Play Emote 393");
-- Prairie Wolf Alpha
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2960;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2960 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2960,0,0,1,1,0,100,0,30000,600000,120000,600000,4,1018,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Wolf Alpha - Out of Combat - Play Sound 1018"),
(2960,0,1,0,61,0,100,0,0,0,0,0,5,393,0,0,0,0,0,1,0,0,0,0,0,0,0,"Prairie Wolf Alpha - Out of Combat - Play Emote 393"),
(2960,0,2,0,0,0,100,0,6000,10000,35000,45000,11,5781,0,0,0,0,0,2,0,0,0,0,0,0,0,"Prairie Wolf Alpha - In Combat - Cast Threatening Growl");
-- Wiry Swoop
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2969;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2969 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2969,0,0,0,0,0,100,0,5000,8000,15000,21000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Wiry Swoop - In Combat - Cast Swoop");
-- Swoop
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2970;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2970 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2970,0,0,0,0,0,100,0,5000,8000,15000,21000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Swoop - In Combat - Cast Swoop");
-- Taloned Swoop
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2971;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2971 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2971,0,0,0,0,0,100,0,5000,8000,15000,21000,11,5708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Taloned Swoop - In Combat - Cast Swoop");
-- Venture Co. Laborer
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2976;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2976 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2976,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Laborer - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Taskmaster
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2977;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2977 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2977,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Taskmaster - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Worker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2978;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2978 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2978,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Worker - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Venture Co. Supervisor
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2979;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2979 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2979,0,0,0,0,0,100,0,1000,3000,15000,30000,11,6673,2,0,0,0,0,1,0,0,0,0,0,0,0,"Venture Co. Supervisor - In Combat - Cast Battle Shout");
-- Kodo Matriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2974;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2974 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2974,0,0,0,9,0,100,0,0,8,9000,14000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kodo Matriarch - Within 0-8 Range - Cast Trample");
-- Kodo Bull
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2973;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2973 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2973,0,0,0,9,0,100,0,0,8,9000,14000,11,5568,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kodo Bull - Within 0-8 Range - Cast Trample");
-- Kodo Calf
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2972;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2972 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2972,0,0,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kodo Calf - On Aggro - Cast Rushing Charge");
-- Galak Outrunner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2968;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2968 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2968,0,0,0,0,0,100,0,0,0,2300,3900,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Galak Outrunner - In Combat - Cast Shoot"),
(2968,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Galak Outrunner - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Bristleback Interloper
DELETE FROM `smart_scripts` WHERE `entryorguid`=3232 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3232,0,0,0,0,0,100,0,5000,8000,14000,20000,11,12166,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bristleback Interloper - In Combat - Cast Muscle Tear"),
(3232,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bristleback Interloper - Between 0-15% Health - Flee For Assist (No Repeat)");
-- The Rake
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5807;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5807 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5807,0,0,0,0,0,100,0,5000,8000,8000,12000,11,12166,0,0,0,0,0,2,0,0,0,0,0,0,0,"The Rake - In Combat - Cast Muscle Tear");
-- Enforcer Emilgund
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5787;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5787 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5787,0,0,1,2,0,100,1,0,30,0,0,11,3019,0,0,0,0,0,1,0,0,0,0,0,0,0,"Enforcer Emilgund - Between 0-30% Health - Cast Frenzy (No Repeat)"),
(5787,0,1,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Enforcer Emilgund - Between 0-30% Health - Say Line 0 (No Repeat)");
DELETE FROM `creature_text` WHERE `entry`=5787;
INSERT INTO `creature_text` (`entry`, `groupid`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(5787,0,0,"%s goes into a frenzy!",16,0,100,0,0,0,0,"Enforcer Emilgund");
-- Bael'dun Digger
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2989;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2989 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2989,0,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bael'dun Digger - Between 0-15% Health - Flee For Assist (No Repeat)");
-- Bael'dun Appraiser
UPDATE `smart_scripts` SET `event_param4`=17000 WHERE `entryorguid`=2990 AND `source_type`=0 AND `id`=0;
-- Windfury Wind Witch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2963;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2963 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2963,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Windfury Wind Witch - In Combat - Cast Lightning Bolt"),
(2963,0,1,0,9,0,100,0,0,5,11000,16000,11,6982,0,0,0,0,0,2,0,0,0,0,0,0,0,"Windfury Wind Witch - Within 0-5 Range - Cast Gust of Wind");
-- Windfury Sorceress
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2964;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2964 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2964,0,0,0,0,0,100,0,0,0,3400,4800,11,13322,64,0,0,0,0,2,0,0,0,0,0,0,0,"Windfury Sorceress - In Combat - Cast Frostbolt");
-- Windfury Matriarch
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2965;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2965 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2965,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Windfury Matriarch - In Combat - Cast Lightning Bolt"),
(2965,0,1,0,2,0,100,0,0,50,18000,24000,11,332,0,0,0,0,0,1,0,0,0,0,0,0,0,"Windfury Matriarch - Between 0-50% Health - Cast Healing Wave");
-- Sister Hatelash
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5785;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5785 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5785,0,0,0,0,0,100,0,0,0,3400,4800,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Sister Hatelash - In Combat - Cast Lightning Bolt"),
(5785,0,1,0,0,0,100,0,4000,9000,30000,45000,11,6960,2,0,0,0,0,1,0,0,0,0,0,0,0,"Sister Hatelash - In Combat - Cast Lightning Barrier");
-- Snagglespear
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5786;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5786 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5786,0,0,0,9,0,100,0,0,20,11000,18000,11,12024,0,0,0,0,0,2,0,0,0,0,0,0,0,"Snagglespear - Within 0-20 Range - Cast Net");
-- Arra'chea
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3058;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3058 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3058,0,0,0,0,0,100,0,7000,9000,11000,15000,11,6730,0,0,0,0,0,2,0,0,0,0,0,0,0,"Arra'chea - In Combat - Cast Head Butt");
-- Mazzranache
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3068;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3068 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3068,0,0,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mazzranache - On Aggro - Cast Rushing Charge"),
(3068,0,1,0,0,0,100,0,6000,8000,16000,20000,11,3583,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mazzranache - In Combat - Cast Deadly Poison");
-- Palemane Tanner
UPDATE `smart_scripts` SET `event_param3`=2400, `event_param4`=3800 WHERE `entryorguid`=2949 AND `source_type`=0 AND `id`=1;
-- Palemane Poacher
UPDATE `smart_scripts` SET `event_param3`=2300, `event_param4`=3900 WHERE `entryorguid`=2951 AND `source_type`=0 AND `id`=1;