DELETE FROM `spell_script_names` WHERE `ScriptName` = "spell_nefarius_shadowblink";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(22681, "spell_nefarius_shadowblink");
DELETE FROM `creature_text` WHERE `entry` = 11583;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(11583, 0, 0, "Well done, my minions. The mortals' courage begins to wane! Now, let's see how they contend with the true Lord of Blackrock Spire!!!", 14, 0, 100, 0, 0, 8288, 0, "nefarian SAY_AGGRO"),
(11583, 1, 0, "Enough! Now you vermin shall feel the force of my birthright, the fury of the earth itself.", 14, 0, 100, 0, 0, 8289, 0, "nefarian SAY_XHEALTH"),
(11583, 2, 0, "BURN! You wretches! BURN!", 14, 0, 100, 0, 0, 8290, 0, "nefarian SAY_SHADOWFLAME"),
(11583, 3, 0, "Impossible! Rise my minions!  Serve your master once more!", 14, 0, 100, 0, 0, 8291, 0, "nefarian SAY_RAISE_SKELETONS"),
(11583, 4, 0, "Worthless $n!  Your friends will join you soon enough!", 14, 0, 100, 0, 0, 8293, 0, "nefarian SAY_SLAY"),
(11583, 5, 0, "This cannot be!  I am the master here!  You mortals are nothing to my kind!  Do you hear me? Nothing!", 14, 0, 100, 0, 0, 8292, 0, "nefarian SAY_DEATH"),
(11583, 6, 0, "Mages too? You should be more careful when you play with magic...", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_MAGE"),
(11583, 7, 0, "Warriors, I know you can hit harder than that! Let's see it!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_WARRIOR"),
(11583, 8, 0, "Druids and your silly shapeshifting. Lets see it in action!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_DRUID"),
(11583, 9, 0, "Priests! If you're going to keep healing like that, we might as well make it a little more interesting!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_PRIEST"),
(11583, 10, 0, "Paladins... I've heard you have many lives. Show me.", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_PALADIN"),
(11583, 11, 0, "Shamans, show me what your totems can do!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_SHAMAN"),
(11583, 12, 0, "Warlocks, you shouldn't be playing with magic you don't understand. See what happens?", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_WARLOCK"),
(11583, 13, 0, "Hunters and your annoying pea-shooters!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_HUNTER"),
(11583, 14, 0, "Rogues? Stop hiding and face me!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_ROGUE"),
(11583, 15, 0, "Death Knights... get over here!", 14, 0, 100, 0, 0, 0, 0, "nefarian SAY_DEATH_KNIGHT");
DELETE FROM `spell_target_position` WHERE `id` BETWEEN 22668 AND 22676;
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES 
(22668, 0, 469, -7581.11, -1216.19, 476.8, 0),
(22669, 0, 469, -7542.47, -1191.92, 476.355, 0),
(22670, 0, 469, -7506.58, -1165.26, 476.796, 0),
(22671, 0, 469, -7561.54, -1244.01, 476.8, 0),
(22674, 0, 469, -7538.63, -1273.64, 476.8, 0),
(22675, 0, 469, -7500.7, -1249.89, 476.798, 0),
(22676, 0, 469, -7469.93, -1227.93, 476.777, 0);
-- Bronze Drakonid SAI
SET @ENTRY := 14263;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,15,5000,8000,11,22642,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bronze Drakonid - Within 0-15 Range - Cast 'Brood Power: Bronze' (Normal Dungeon)");
-- Blue Drakonid SAI
SET @ENTRY := 14261;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,15,5000,8000,11,22559,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blue Drakonid - Within 0-15 Range - Cast 'Brood Power: Blue' (Normal Dungeon)");
-- Green Drakonid SAI
SET @ENTRY := 14262;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,15,5000,8000,11,22561,0,0,0,0,0,2,0,0,0,0,0,0,0,"Green Drakonid - Within 0-15 Range - Cast 'Brood Power: Green' (Normal Dungeon)");
-- Black Drakonid SAI
SET @ENTRY := 14265;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,9,0,100,2,0,15,5000,8000,11,22560,0,0,0,0,0,2,0,0,0,0,0,0,0,"Black Drakonid - Within 0-15 Range - Cast 'Brood Power: Black' (Normal Dungeon)");

