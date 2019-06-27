-- DB/Quest: The Stones That Bind Us 
-- DB/Waypoint: add pathing for Nishera the Garden Keeper. 
-- DB/SAI: add out-of-combat behavior for Jainthess Thelryn
-- DB/SAI: Add in-combat texts for Rageclaw Berserker and Rageclaw Hunter 
-- DB/SAI: Add out-of-combat texts for Falcon Watch Ranger 
-- DB/SAI: Add special emote on flee for assist for Zulian Cub 

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (7668,7669,7670,7671);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (7668,7669,7670,7671) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=766800 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(7668,0,0,0,25,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - On Reset - Set Invincibility at 1 HP"),
(7668,0,1,0,2,0,100,1,0,5,0,0,11,10794,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - Between 0-5% Health - Cast 'Spirit Shock' (No Repeat)"),
(7668,0,2,0,2,0,100,1,0,5,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - Between 0-5% Health - Say Line 0 (No Repeat)"),
(7668,0,3,0,2,0,100,1,0,5,0,0,106,16,0,0,0,0,0,15,141812,10,0,0,0,0,0,"Servant of Razelikh - Between 0-5% Health - Remove Gameobject Flag 'Not Selectable' (Stone of Binding)"),
(7668,0,4,0,8,0,100,1,10805,0,0,0,80,766800,2,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - On spell hit - Run Script"),
(7669,0,0,0,25,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Grol - On Reset - Set Invincibility at 1 HP"),
(7669,0,1,0,2,0,100,1,0,5,0,0,11,10794,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Grol - Between 0-5% Health - Cast 'Spirit Shock' (No Repeat)"),
(7669,0,2,0,2,0,100,1,0,5,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Grol - Between 0-5% Health - Say Line 0 (No Repeat)"),
(7669,0,3,0,2,0,100,1,0,5,0,0,106,16,0,0,0,0,0,15,141857,10,0,0,0,0,0,"Servant of Grol - Between 0-5% Health - Remove Gameobject Flag 'Not Selectable' (Stone of Binding)"),
(7669,0,4,0,8,0,100,1,10834,0,0,0,80,766800,2,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Grol - On spell hit - Run Script"),
(7670,0,0,0,25,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Allistarj - On Reset - Set Invincibility at 1 HP"),
(7670,0,1,0,2,0,100,1,0,5,0,0,11,10794,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Allistarj - Between 0-5% Health - Cast 'Spirit Shock' (No Repeat)"),
(7670,0,2,0,2,0,100,1,0,5,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Allistarj - Between 0-5% Health - Say Line 0 (No Repeat)"),
(7670,0,3,0,2,0,100,1,0,5,0,0,106,16,0,0,0,0,0,15,141858,10,0,0,0,0,0,"Servant of Allistarj - Between 0-5% Health - Remove Gameobject Flag 'Not Selectable' (Stone of Binding)"),
(7670,0,4,0,8,0,100,1,10835,0,0,0,80,766800,2,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Allistarj - On spell hit - Run Script"),
(7671,0,0,0,25,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Sevine - On Reset - Set Invincibility at 1 HP"),
(7671,0,1,0,2,0,100,1,0,5,0,0,11,10794,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Sevine - Between 0-5% Health - Cast 'Spirit Shock' (No Repeat)"),
(7671,0,2,0,2,0,100,1,0,5,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Sevine - Between 0-5% Health - Say Line 0 (No Repeat)"),
(7671,0,3,0,2,0,100,1,0,5,0,0,106,16,0,0,0,0,0,15,141859,10,0,0,0,0,0,"Servant of Sevine - Between 0-5% Health - Remove Gameobject Flag 'Not Selectable' (Stone of Binding)"),
(7671,0,4,0,8,0,100,1,10836,0,0,0,80,766800,2,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Sevine - On spell hit - Run Script"),
(766800,9,0,0,0,0,100,0,3000,3000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - On Spellhit 'Shackle Shatter' - Say Line 2"),
(766800,9,1,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - On Spellhit 'Shackle Shatter' - Say Line 1"),
(766800,9,2,0,0,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Servant of Razelikh - On Spellhit 'Shackle Shatter' - Kill Self");

-- Stone of Binding
UPDATE `gameobject_template` SET `AIName`="SmartGameObjectAI" WHERE `entry` IN (141812,141857,141858,141859);
UPDATE `gameobject_template` SET `flags`=20 WHERE `entry` IN (141812,141857,141858,141859);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (141812,141857,141858,141859) AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(141812,1,0,0,70,0,100,0,2,0,0,0,11,10805,0,0,0,0,0,19,7668,10,0,0,0,0,0,"Stone of Binding - On Gameobject State Changed - Cast 'Shackle Shatter'"),
(141857,1,0,0,70,0,100,0,2,0,0,0,11,10834,0,0,0,0,0,19,7669,10,0,0,0,0,0,"Stone of Binding - On Gameobject State Changed - Cast 'Shackle Shatter'"),
(141858,1,0,0,70,0,100,0,2,0,0,0,11,10835,0,0,0,0,0,19,7670,10,0,0,0,0,0,"Stone of Binding - On Gameobject State Changed - Cast 'Shackle Shatter'"),
(141859,1,0,0,70,0,100,0,2,0,0,0,11,10836,0,0,0,0,0,19,7671,10,0,0,0,0,0,"Stone of Binding - On Gameobject State Changed - Cast 'Shackle Shatter'");

-- Spell "Shackle Shatter"
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (10805,10834,10835,10836);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13,3,10805,0,0,31,0,3,7668,0,0,0,0,"","Spell 'Shackle Shatter' can only hit Servant of Razelikh"),
(13,3,10834,0,1,31,0,3,7669,0,0,0,0,"","Spell 'Shackle Shatter' can only hit Servant of Grol"),
(13,3,10835,0,2,31,0,3,7670,0,0,0,0,"","Spell 'Shackle Shatter' can only hit Servant of Allistarj"),
(13,3,10836,0,2,31,0,3,7671,0,0,0,0,"","Spell 'Shackle Shatter' can only hit Servant of Sevine");

DELETE FROM `creature_text` WHERE `entry` IN (7668,7669,7670,7671);
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(7668,0,0,"%s's physical form is weakened. You notice the Stone of Binding near the creature is glowing! Strike now!",41,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,0,"FREEEEEEEEEEDDOOOOMM!",14,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,1,"Finally, the agony ceases....",12,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,2,"Give my regards to Commander Trebor.",12,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,3,"The Defiler... must warn Thrall...",12,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,4,"It was not his fault. Tell him that...",12,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,1,5,"Finally, released from his cursed grasp. Father, I come...",12,0,100,0,0,0,0,"Servant of Razelikh"),
(7668,2,0,"Stone of Binding shatters, releasing the soul which it held.",16,0,100,0,0,0,0,"Servant of Razelikh"),
(7669,0,0,"%s's physical form is weakened. You notice the Stone of Binding near the creature is glowing! Strike now!",41,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,0,"FREEEEEEEEEEDDOOOOMM!",14,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,1,"Finally, the agony ceases....",12,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,2,"Give my regards to Commander Trebor.",12,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,3,"The Defiler... must warn Thrall...",12,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,4,"It was not his fault. Tell him that...",12,0,100,0,0,0,0,"Servant of Grol"),
(7669,1,5,"Finally, released from his cursed grasp. Father, I come... ",12,0,100,0,0,0,0,"Servant of Grol"),
(7669,2,0,"Stone of Binding shatters, releasing the soul which it held.",16,0,100,0,0,0,0,"Servant of Grol"),
(7670,0,0,"%s's physical form is weakened. You notice the Stone of Binding near the creature is glowing! Strike now!",41,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,0,"FREEEEEEEEEEDDOOOOMM!",14,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,1,"Finally, the agony ceases....",12,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,2,"Give my regards to Commander Trebor.",12,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,3,"The Defiler... must warn Thrall...",12,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,4,"It was not his fault. Tell him that...",12,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,1,5,"Finally, released from his cursed grasp. Father, I come... ",12,0,100,0,0,0,0,"Servant of Allistarj"),
(7670,2,0,"Stone of Binding shatters, releasing the soul which it held.",16,0,100,0,0,0,0,"Servant of Allistarj"),
(7671,0,0,"%s's physical form is weakened. You notice the Stone of Binding near the creature is glowing! Strike now!",41,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,0,"FREEEEEEEEEEDDOOOOMM!",14,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,1,"Finally, the agony ceases....",12,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,2,"Give my regards to Commander Trebor.",12,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,3,"The Defiler... must warn Thrall...",12,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,4,"It was not his fault. Tell him that...",12,0,100,0,0,0,0,"Servant of Sevine"),
(7671,1,5,"Finally, released from his cursed grasp. Father, I come... ",12,0,100,0,0,0,0,"Servant of Sevine"),
(7671,2,0,"Stone of Binding shatters, releasing the soul which it held.",16,0,100,0,0,0,0,"Servant of Sevine");

DELETE FROM `creature_addon` WHERE `guid`=106959;
UPDATE `creature_template_addon` SET `path_id`=272550, `bytes2`=1 WHERE `entry`=27255;
UPDATE `creature` SET `MovementType`=2 WHERE `id`=27255;
DELETE FROM `creature_template_addon` WHERE `entry` = 27255;
INSERT INTO `creature_template_addon` VALUES
(27255, 272550, 0, 0, 1, 0, '');
DELETE FROM `waypoint_data` WHERE `id`=272550;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(272550, 1, 2846.652, -18.03868, 0.5942773),
(272550, 2, 2859.129, -6.210721, 0.8772362),
(272550, 3, 2868.413, -4.458008, 0.8990343),
(272550, 4, 2881.048, 7.002713, 0.6996365),
(272550, 5, 2881.712, 14.12375, 0.3246365),
(272550, 6, 2883.564, 38.37462, 1.166026),
(272550, 7, 2886.205, 52.10439, 0.9160259),
(272550, 8, 2885.475, 55.2174, 0.9160259),
(272550, 9, 2883.057, 60.77968, 0.5410259),
(272550, 10, 2880.73, 64.77002, 0.5410259),
(272550, 11, 2881.537, 74.34549, 1.077996),
(272550, 12, 2882.853, 82.22849, 1.327996),
(272550, 13, 2871.807, 104.8361, 1.382215),
(272550, 14, 2868.9761, 108.4443, 1.2516),
(272550, 15, 2833.0100, 123.0882, 0.5406),
(272550, 16, 2814.2317, 120.1411, 0.4954),
(272550, 17, 2787.9084, 123.6816, 0.8508),
(272550, 18, 2758.4324, 109.4119, 2.1920),
(272550, 19, 2751.1382, 98.4347, 2.3503),
(272550, 20, 2751.3394, 82.3503, 3.3260),
(272550, 21, 2746.8130, 76.1211, 3.5752),
(272550, 22, 2751.3394, 82.3503, 3.3260),
(272550, 23, 2751.1382, 98.4347, 2.3503),
(272550, 24, 2758.4324, 109.4119, 2.1920),
(272550, 25, 2787.9084, 123.6816, 0.8508),
(272550, 26, 2814.2317, 120.1411, 0.4954),
(272550, 27, 2833.0100, 123.0882, 0.5406),
(272550, 28, 2868.9761, 108.4443, 1.2516),
(272550, 29, 2877.5859, 91.7811, 1.0588),
(272550, 30, 2882.8047, 77.9702, 1.1827),
(272550, 31, 2880.1309, 66.4228, 0.5722),
(272550, 32, 2885.8425, 53.4985, 0.8828),
(272550, 33, 2886.1099, 44.9907, 0.8721),
(272550, 34, 2881.2725, 31.9808, 1.2111),
(272550, 35, 2881.7593, 10.6438, 0.4511),
(272550, 36, 2879.105, 5.936632, 0.6996365),
(272550, 37, 2867.718, -4.473795, 0.9263781),
(272550, 38, 2858.986, -6.764106, 0.8442773),
(272550, 39, 2846.623, -17.78228, 0.5942773),
(272550, 40, 2828.276, -20.16325, 0.5493096),
(272550, 41, 2814.309, -15.23454, 0.5493096),
(272550, 42, 2802.623, -14.91173, 0.6743096),
(272550, 43, 2779.8772, -18.0462, 0.6422),
(272550, 44, 2763.3828, -10.1257, 1.3932),
(272550, 45, 2743.0781, -18.0336, 1.5010),
(272550, 46, 2731.222, -15.17006, 2.059937),
(272550, 47, 2717.93, -8.302789, 1.318791),
(272550, 48, 2719.173, -0.079698, 3.292424),
(272550, 49, 2718.575, -7.877007, 1.420842),
(272550, 50, 2730.189, -15.23438, 1.811467),
(272550, 51, 2743.433, -17.34923, 1.474984),
(272550, 52, 2761.801, -12.24403, 1.580453),
(272550, 53, 2772.806, -15.62581, 1.061682),
(272550, 54, 2782.825, -16.96083, 0.4842899),
(272550, 55, 2803.748, -14.84977, 0.6743096),
(272550, 56, 2813.47, -15.30463, 0.5493096),
(272550, 57, 2827.618, -20.49647, 0.5493096);

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=15291;
DELETE FROM `smart_scripts` WHERE `entryorguid`=15291 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1529100, 1529101) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(15291, 0, 0, 0, 1, 0, 100, 0, 5000, 20000, 50000, 120000, 53, 0, 15291, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - Out Of Combat - Start Waypoint"),
(15291, 0, 1, 0, 40, 0, 100, 0, 2, 0, 0, 0, 80, 1529100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - On WP 2 Reached - Run Actionlist"),
(15291, 0, 2, 0, 40, 0, 100, 0, 4, 0, 0, 0, 80, 1529101, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - On WP 4 Reached - Run Actionlist"),
(1529100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 54, 9000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - On Script - Pause Waypoint"),
(1529100, 9, 1, 0, 0, 0, 100, 0, 500, 500, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1.9839, "Jainthess Thelryn - On Script - Change Orientation"),
(1529100, 9, 2, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - On Script - Emote 'Oneshot Point'"),
(1529101, 9, 0, 0, 0, 0, 100, 0, 500, 500, 0, 0, 5, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jainthess Thelryn - On Script - Emote 'Oneshot Kneel'"),
(1529101, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 4.0143, "Jainthess Thelryn - On Script - Change Orientation");

DELETE FROM `waypoints` WHERE `entry`=15291;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(15291, 1, 10419.11, -6319.905, 35.5736, "Jainthess Thelryn"),
(15291, 2, 10424.43, -6320.706, 35.5736, "Jainthess Thelryn"),
(15291, 3, 10419.11, -6319.905, 35.5736, "Jainthess Thelryn"),
(15291, 4, 10416.7998, -6316.6001, 35.5763, "Jainthess Thelryn");

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (29437, 29439);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29437, 29439) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(29437, 0, 0, 0, 0, 0, 100, 0, 200, 900, 120000, 240000, 11, 50420, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rageclaw Berserker - In Combat - Cast 'Enrage'"),
(29437, 0, 1, 0, 0, 0, 30, 0, 10000, 60000, 120000, 240000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rageclaw Berserker - In Combat - Talk 0"),
(29439, 0, 0, 0, 0, 0, 30, 0, 10000, 60000, 120000, 240000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rageclaw Hunter - In Combat - Talk 0");

DELETE FROM `creature_text` WHERE `entry` IN (29437, 29439);
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(29437, 0, 0, "You go now, bad troll!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 1, "Why you hurt Rageclaw? You crazy?", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 2, "Rageclaw and troll friends no more!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 3, "You kill our pups! We kill you back!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 4, "You leave den the hard way!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 5, "You hurted the chief's lion seal! WHY YOU HURT LION SEAL??!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 6, "Why you smell so bad now? You smelled much less bad before!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29437, 0, 7, "Trolls is shameful. Trolls is killers!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Berserker"),
(29439, 0, 0, "You go now, bad troll!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 1, "Why you hurt Rageclaw? You crazy?", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 2, "Rageclaw and troll friends no more!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 3, "You kill our pups! We kill you back!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 4, "You leave den the hard way!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 5, "You hurted the chief's lion seal! WHY YOU HURT LION SEAL??!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 6, "Why you smell so bad now? You smelled much less bad before!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter"),
(29439, 0, 7, "Trolls is shameful. Trolls is killers!", 12, 0, 100, 0, 0, 0,  0, "Rageclaw Hunter");

DELETE FROM `creature_text` WHERE `entry`=17282;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(17282, 0, 0, "We're never going to fire one of these, are we?", 12, 1, 100, 0, 0, 0,  0, "Falcon Watch Ranger"),
(17282, 0, 1, "Do we even have ammunition for these?", 12, 1, 100, 0, 0, 0,  0, "Falcon Watch Ranger"),
(17282, 0, 2, "What, exactly, are we ever going to fire these at?", 12, 1, 100, 0, 0, 0,  0, "Falcon Watch Ranger"),
(17282, 0, 3, "I wonder how far this would launch that white cat...", 12, 1, 100, 0, 0, 0,  0, "Falcon Watch Ranger");

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=17282;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-62073, -62075) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-62073, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 11, 18950, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Honor Hold Defender - On Reset - Cast Invisibility and Stealth Detection'),
(-62073, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18396, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Honor Hold Defender - On Aggro - Cast Dismounting Blast'),
(-62073, 0, 2, 0, 1, 0, 100, 0, 5000, 20000, 120000, 240000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Falcon Watch Ranger - Out Of Combat - Talk"),
(-62075, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 11, 18950, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Honor Hold Defender - On Reset - Cast Invisibility and Stealth Detection'),
(-62075, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 18396, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Honor Hold Defender - On Aggro - Cast Dismounting Blast'),
(-62075, 0, 2, 0, 1, 0, 100, 0, 5000, 20000, 120000, 240000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Falcon Watch Ranger - Out Of Combat - Talk");

DELETE FROM `creature_text` WHERE `entry`=11360;
INSERT INTO `creature_text` (`entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `TextRange`, `comment`) VALUES
(11360, 0, 0, "%s flees toward the safety of another tiger.", 16, 0, 100, 0, 0, 0, 0, "Zulian Cub");

UPDATE `smart_scripts` SET `link`=1, `action_param1`=0 WHERE `entryorguid`=11360 AND `source_type`=0 AND `id`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=11360 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(11360, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Zulian Cub - Between 0-15% Health - Flee For Assist (No Repeat)");

