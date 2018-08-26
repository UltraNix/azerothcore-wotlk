-- Add some missing gameobjects
SET @OGUID = 300000;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID AND @OGUID+31;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID,21148,0,1,1,-9072.17,837.258,109.424,0.299373,-0,-0,-0.149128,-0.988818,-120,255,1,0),
(@OGUID+1,21148,0,1,1,-9072.82,829.589,109.478,5.99743,-0,-0,-0.14239,0.989811,-120,255,1,0),
(@OGUID+2,21148,0,1,1,-9059.47,838.004,110.215,0.377914,-0,-0,-0.187835,-0.982201,-120,255,1,0),
(@OGUID+3,21148,0,1,1,-9059.77,838.776,110.215,0.381841,-0,-0,-0.189763,-0.98183,-120,255,1,0),
(@OGUID+4,21148,0,1,1,-9085.29,832.499,109.61,3.58633,-0,-0,-0.975378,0.220539,-120,255,1,0),
(@OGUID+5,21148,0,1,1,-9085.65,833.289,109.61,3.53135,-0,-0,-0.981071,0.193647,-120,255,1,0),
(@OGUID+6,21148,0,1,1,-9081.83,823.735,109.61,3.4803,-0,-0,-0.985694,0.168543,-120,255,1,0),
(@OGUID+7,21148,0,1,1,-9081.1,828.544,109.432,1.763,-0,-0,-0.771693,-0.635995,-120,255,1,0),
(@OGUID+8,21148,0,1,1,-9082.12,830.655,109.429,5.3287,-0,-0,-0.459332,0.888265,-120,255,1,0),
(@OGUID+9,21148,0,1,1,-9069.05,828.82,109.428,1.8533,-0,-0,-0.799613,-0.600515,-120,255,1,0),
(@OGUID+10,21148,0,1,1,-9075.97,820.033,109.55,4.11132,-0,-0,-0.884738,0.466088,-120,255,1,0),
(@OGUID+11,21148,0,1,1,-9070.79,828.253,109.431,0.334503,-0,-0,-0.166473,-0.986046,-120,255,1,0),
(@OGUID+12,21148,0,1,1,-9075.04,838.185,109.463,5.08008,-0,-0,-0.565921,0.824459,-120,255,1,0),
(@OGUID+13,21148,0,1,1,-9076.71,818.742,109.55,0.407534,-0,-0,-0.20236,-0.979311,-120,255,1,0),
(@OGUID+14,21148,0,1,1,-9079.45,828.87,109.436,3.40383,-0,-0,-0.991416,0.130743,-120,255,1,0),
(@OGUID+15,21148,0,1,1,-9073.03,838.268,109.432,0.345678,-0,-0,-0.17198,-0.985101,-120,255,1,0),
(@OGUID+16,21148,0,1,1,-9085.74,814.883,116.796,3.49512,-0,-0,-0.984418,0.175845,-120,255,1,0),
(@OGUID+17,21148,0,1,1,-9087.04,830.81,116.825,5.06286,-0,-0,-0.57-1201,0.819555,-120,255,1,0),
(@OGUID+18,21148,0,1,1,-9094.68,836.463,116.795,1.10446,-0,-0,-0.524585,-0.851358,-120,255,1,0),
(@OGUID+19,21148,0,1,1,-9084.5,824.882,116.825,5.65584,-0,-0,-0.308554,0.951207,-120,255,1,0),
(@OGUID+20,21147,0,1,1,-9081.3,822.651,109.61,3.55732,-0,-0,-0.978474,0.206371,-120,255,1,0),
(@OGUID+21,21147,0,1,1,-9072.24,828.632,109.453,0.376773,-0,-0,-0.187274,-0.982308,-120,255,1,0),
(@OGUID+22,21147,0,1,1,-9083.98,828.135,109.61,3.50271,-0,-0,-0.983743,0.17958,-120,255,1,0),
(@OGUID+23,21146,0,1,1,-9075.14,836.495,109.436,1.95635,-0,-0,-0.82948,-0.558537,-120,255,1,0),
(@OGUID+24,21146,0,1,1,-9069.89,830.264,109.432,0.954968,-0,-0,-0.459546,-0.888154,-120,255,1,0),
(@OGUID+25,21146,0,1,1,-9079.88,818.003,109.61,5.10492,-0,-0,-0.555639,0.831424,-120,255,1,0),
(@OGUID+26,21146,0,1,1,-9080.54,819.582,109.61,5.10492,-0,-0,-0.555639,0.831424,-120,255,1,0),
(@OGUID+27,21146,0,1,1,-9058.49,837.482,110.219,1.94478,-0,-0,-0.826236,-0.563325,-120,255,1,0),
(@OGUID+28,21146,0,1,1,-9081.2,821.143,109.61,5.1167,-0,-0,-0.550732,0.834682,-120,255,1,0),
(@OGUID+29,21145,0,1,1,-9083.11,825.766,109.61,3.52235,-0,-0,-0.981933,0.189231,-120,255,1,0),
(@OGUID+30,21145,0,1,1,-9084.98,830.42,109.61,0.354403,-0,-0,-0.176275,-0.984341,-120,255,1,0),
(@OGUID+31,21145,0,1,1,-9059.28,840.347,110.239,5.05895,-0,-0,-0.574602,0.818433,-120,255,1,0);

-- Texts
DELETE FROM `creature_text` WHERE `entry` IN (1141,3628,1311);
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(1141,0,0,"All hail $n, a $c of worth!",12,7,100,22,0,0,0,"Angus Stern"),
(1141,1,0,"Behold!  The Blue Recluse holds a feast in $g his:her; honor!",12,7,100,25,0,0,0,"Angus Stern"),
(3628,0,0,"Here here!",12,7,100,5,0,0,0,"Steven Lohan"),
(1311,0,0,"Hooray, $n!",12,7,100,4,0,0,0,"Joachim Brenlow"),
(1311,0,1,"Long live $n!",12,7,100,4,0,0,0,"Joachim Brenlow");

-- Angus Stern
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1141;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1141 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=114100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1141,0,0,0,20,0,100,0,1271,0,0,0,80,114100,0,0,0,0,0,1,0,0,0,0,0,0,0,"Angus Stern - On Quest 'Feast at the Blue Recluse' Finished - Run Script"),
(1141,0,1,0,20,0,100,0,1271,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Angus Stern - On Quest 'Feast at the Blue Recluse' Finished - Store Target"),
(114100,9,0,0,0,0,100,0,0,0,0,0,83,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Angus Stern - On Script - Remove Npc Flag Questgiver"),
(114100,9,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Angus Stern - On Script - Say Line 0"),
(114100,9,2,0,0,0,100,0,0,0,0,0,70,120,0,0,0,0,0,15,0,100,0,0,0,0,0,"Angus Stern - On Script - Respawn All Gameobjects"),
(114100,9,3,0,0,0,100,0,5000,5000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,1.02834,"Angus Stern - On Script - Set Orientation"),
(114100,9,4,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Angus Stern - On Script - Say Line 1"),
(114100,9,5,0,0,0,100,0,6000,6000,0,0,100,1,0,0,0,0,0,19,3628,0,0,0,0,0,0,"Angus Stern - On Script - Send Target to Steven Lohan"),
(114100,9,6,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,3628,0,0,0,0,0,0,"Angus Stern - On Script - Set Data to Steven Lohan"),
(114100,9,7,0,0,0,100,0,4000,4000,0,0,82,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Angus Stern - On Script - Add Npc Flag Questgiver"),
(114100,9,8,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0.558505,"Angus Stern - On Script - Set Orientation");

-- Steven Lohan
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=3628;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3628 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=362800 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(3628,0,0,0,38,0,100,0,1,1,0,0,80,362800,0,0,0,0,0,1,0,0,0,0,0,0,0,"Steven Lohan - On Data Set - Run Script"),
(362800,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,12,1,0,0,0,0,0,0,"Steven Lohan - On Script - Say Line 0"),
(362800,9,1,0,0,0,100,0,2000,2000,0,0,100,1,0,0,0,0,0,19,1311,0,0,0,0,0,0,"Steven Lohan - On Script - Send Target to Steven Lohan"),
(362800,9,2,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,1311,0,0,0,0,0,0,"Steven Lohan - On Script - Set Data to Joachim Brenlow");

-- Joachim Brenlow
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=1311;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1311 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1311,0,0,0,38,0,100,0,1,1,0,0,1,0,0,0,0,0,0,12,1,0,0,0,0,0,0,"Joachim Brenlow - On Data Set - Say Line 0");
