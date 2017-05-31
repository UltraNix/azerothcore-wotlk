-- Flamewaker Healer SAI
SET @ENTRY := 11663;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,14000,8000,12000,11,20603,0,0,0,0,0,2,0,0,0,0,0,0,0,"Flamewaker Healer - In Combat - Cast 'Shadow Shock'"),
(@ENTRY,0,1,0,0,0,100,0,3400,4800,3400,4800,11,22677,0,0,0,0,0,17,8,40,0,0,0,0,0,"Flamewaker Healer - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,2,0,4,0,100,0,0,0,0,0,39,30,0,0,0,0,0,1,0,0,0,0,0,0,0,"Flamewaker Healer - On Aggro - Call For Help");
-- Flamewaker Elite SAI
SET @ENTRY := 11664;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,12000,3400,4800,11,36711,0,0,0,0,0,17,8,40,0,0,0,0,0,"Flamewaker Elite - In Combat - Cast 'Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,11000,14000,11000,14000,11,20229,0,0,0,0,0,17,0,8,0,0,0,0,0,"Flamewaker Elite - In Combat - Cast 'Blast Wave'"),
(@ENTRY,0,2,0,0,0,80,0,9000,11000,9000,12000,11,20623,0,0,0,0,0,2,0,0,0,0,0,0,0,"Flamewaker Elite - In Combat - Cast 'Fire Blast'"),
(@ENTRY,0,3,0,4,0,100,0,0,0,0,0,39,30,0,0,0,0,0,0,0,0,0,0,0,0,0,"Flamewaker Elite - On Aggro - Call For Help");
-- Majordomo texts
DELETE FROM `creature_text` WHERE `entry`=12018;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(12018, 0, 0, "Reckless mortals! None may challenge the Sons of the Living flame!", 14, 0, 100, 0, 0, 8035, 0, "majordomo SAY_AGGRO"),
(12018, 1, 0, "The runes of warding have been destroyed! Hunt down the infidels, my brethren!", 14, 0, 100, 0, 0, 8039, 0, "majordomo SAY_SPAWN"),
(12018, 2, 0, "Ashes to ashes!", 14, 0, 100, 0, 0, 8037, 0, "majordomo SAY_SLAY_1"),
(12018, 3, 0, "Burn mortals! Burn for this transgression!", 14, 0, 100, 0, 0, 8036, 0, "majordomo SAY_SLAY_2"),
(12018, 4, 0, "You think you\'ve won already? Perhaps you\'ll need another lesson in pain!", 14, 0, 100, 0, 0, 8036, 0, "majordomo SAY_LAST_ADD"),
(12018, 5, 0, "Impossible! Stay your attack, mortals... I submit! I submit!", 14, 0, 100, 0, 0, 8038, 0, "majordomo SAY_DEFEAT_1"),
(12018, 6, 0, "Brashly, you have come to wrest the secrets of the Living Flame! You will soon regret the recklessness of your quest.", 14, 0, 100, 0, 0, 0, 0, "majordomo SAY_DEFEAT_2"),
(12018, 7, 0, "I go now to summon the lord whose house this is. Should you seek an audience with him, your paltry lives will surely be forfeit! Nevertheless, seek out his lair, if you dare!", 14, 0, 100, 0, 0, 0, 0, "majordomo SAY_DEFEAT_3"),
(12018, 8, 0, "Very well, $n.", 12, 0, 100, 0, 0, 0, 0, "majordomo SAY_SUMMON_MAJ"),
(12018, 9, 0, "Impudent whelps! You\'ve rushed headlong to your own deaths! See now, the master stirs!", 14, 0, 100, 0, 0, 0, 0, "majordomo SAY_SUMMON_MAJ_1"),
(12018, 10, 0, "Behold Ragnaros - the Firelord! He who was ancient when this world was young! Bow before him, mortals! Bow before your ending!", 14, 0, 100, 0, 0, 8040, 0, "majordomo SAY_SUMMON_MAJ_2"),
(12018, 11, 0, "These mortal infidels, my lord! They have invaded your sanctum and seek to steal your secrets!", 14, 0, 100, 0, 0, 8041, 0, "majordomo SAY_SUMMON_MAJ_3");
-- Missing gob
DELETE FROM `gameobject` WHERE `guid`=27146;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(27146, 178107, 409, 1, 1, 838.951, -830.383, -230.206, 0.837757, 0, 0, 0, 1, 604800, 100, 1, 0);
-- Ragnaros texts
DELETE FROM `creature_text` WHERE `entry`=11502;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(11502, 0, 0, "TOO SOON! YOU HAVE AWAKENED ME TOO SOON, EXECUTUS! WHAT IS THE MEANING OF THIS INTRUSION???", 14, 0, 100, 0, 0, 8043, 0, "ragnaros SAY_SUMMON_RAG_1"),
(11502, 1, 0, "FOOL! YOU ALLOWED THESE INSECTS TO RUN RAMPANT THROUGH THE HALLOWED CORE? AND NOW YOU LEAD THEM TO MY VERY LAIR? YOU HAVE FAILED ME, EXECUTUS! JUSTICE SHALL BE MET, INDEED!", 14, 0, 100, 0, 0, 8044, 0, "ragnaros SAY_SUMMON_RAG_2"),
(11502, 2, 0, "NOW FOR YOU, INSECTS! BOLDLY, YOU SOUGHT THE POWER OF RAGNAROS. NOW YOU SHALL SEE IT FIRSTHAND!", 14, 0, 100, 15, 0, 8045, 0, "ragnaros SAY_SUMMON_RAG_3"),
(11502, 3, 0, "COME FORTH, MY SERVANTS! DEFEND YOUR MASTER!", 14, 0, 100, 0, 0, 8049, 0, "ragnaros SAY_REINFORCEMENTS_1"),
(11502, 4, 0, "YOU CANNOT DEFEAT THE LIVING FLAME! COME YOU MINIONS OF FIRE! COME FORTH YOU CREATURES OF HATE! YOUR MASTER CALLS!", 14, 0, 100, 0, 0, 8050, 0, "ragnaros SAY_REINFORCEMENTS_2"),
(11502, 5, 0, "BY FIRE BE PURGED!", 14, 0, 100, 0, 0, 8046, 0, "ragnaros SAY_HAMMER"),
(11502, 6, 0, "TASTE THE FLAMES OF SULFURON!", 14, 0, 100, 0, 0, 8047, 0, "ragnaros SAY_WRATH"),
(11502, 7, 0, "DIE INSECT!", 14, 0, 100, 0, 0, 8051, 0, "ragnaros SAY_KILL"),
(11502, 8, 0, "MY PATIENCE IS DWINDILING! COME NATS TO YOUR DEATH!", 14, 0, 100, 0, 0, 8048, 0, "ragnaros SAY_MAGMA_BURST");
-- Spells
DELETE FROM `spell_target_position` WHERE `ID` IN (19527, 20534, 20618);
INSERT INTO `spell_target_position` (`ID`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(19527, 0, 409, 847.103, -816.153, -229.775, 4.344),
(20534, 0, 409, 736.516, -1176.35, -119.006, 0),
(20618, 0, 409, 736.516, -1176.35, -119.006, 0);
DELETE FROM `spell_script_names` WHERE `ScriptName` = "spell_executus_shield";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(20619, "spell_executus_shield"),
(21075, "spell_executus_shield");
-- Gossip
UPDATE `creature_template` SET `gossip_menu_id`=2000 WHERE `entry`=12018;
DELETE FROM `gossip_menu` WHERE `entry` IN (2000, 2001, 2002);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(2000, 4995),
(2001, 5011),
(2002, 5012);
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (2000, 2001, 2002);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`) VALUES
(2000, 0, 0, "Tell me more.", 1, 1, 2001),
(2001, 0, 0, "What else do you have to say?", 1, 1, 2002),
(2002, 0, 0, "You challenged us and we have come. Where is the master you speak of?", 1, 1, 0);
