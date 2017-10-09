SET @CGUID = 87530; -- creature GUIDs (14 creatures)
UPDATE `creature` SET `position_x`=515.5848,`position_y`=544.2007,`position_z`=673.6272,`orientation`=5.740286 WHERE `map`=601 AND `id`=28921;
-- Remove existing world trigger spawns
DELETE FROM `creature` WHERE `guid` BETWEEN 127376 AND 127378;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN 127376 AND 127378;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+5;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+5;
-- And re-spawn them
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`movementtype`) VALUES
(@CGUID+00,23472,601,3,1,530.495 ,597.0955,777.2634,5.986479 ,0,0,0),
(@CGUID+01,23472,601,3,1,530.6029,596.997 ,777.2633,5.427974 ,0,0,0),
(@CGUID+02,23472,601,3,1,530.7466,596.745 ,777.2631,2.303835 ,0,0,0),
(@CGUID+03,23472,601,3,1,583.0908,617.371 ,771.5508,0.6457718,0,0,0),
(@CGUID+04,23472,601,3,1,480.0325,615.5892,773.3531,4.101524 ,0,0,0),
(@CGUID+05,23472,601,3,1,581.4475,608.8407,739.4051,1.727876 ,0,0,0);
INSERT INTO `creature_addon` (`guid`,`auras`) VALUES
(@CGUID+03,"53035 53036 53037"),
(@CGUID+04,"53035 53036 53037"),
(@CGUID+05,"53035 53036 53037");
-- Crusher groups are now spawn groups on Hadronox
DELETE FROM `creature` WHERE `guid` IN (127379,127380,127402);
DELETE FROM `creature_addon` WHERE `guid` IN (127379,127380,127402);
DELETE FROM `linked_respawn` WHERE `guid` IN (127379,127380,127402);
DELETE FROM `creature_summon_groups` WHERE `summonerId`=28921 AND `summonerType`=0;
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(28921,0,1,28922,529.6913,547.1257,731.9155,4.79965 ,6,45000),
(28921,0,1,29117,539.2076,549.7539,732.8668,4.55531 ,6,30000),
(28921,0,1,29118,520.3911,548.7895,732.0118,5.0091  ,6,30000),
(28921,0,2,28922,493.4772,603.3438,760.5628,5.440244,6,45000),
(28921,0,2,29117,490.4421,604.335 ,763.1821,5.625595,6,30000),
(28921,0,2,29119,488.8254,609.2819,767.5876,5.590288,6,30000),
(28921,0,3,28922,566.9789,602.5711,759.6418,3.885966,6,45000),
(28921,0,3,29118,569.348 ,604.9987,763.2137,4.179827,6,30000),
(28921,0,3,29119,572.4737,607.4109,767.1777,3.944169,6,30000);
-- Periodic spawn triggers: Spell scripts
DELETE FROM `spell_script_names` WHERE `scriptname` IN ("spell_hadronox_periodic_summon_champion","spell_hadronox_periodic_summon_crypt_fiend","spell_hadronox_periodic_summon_necromancer");
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES
(53035,"spell_hadronox_periodic_summon_champion"),
(53037,"spell_hadronox_periodic_summon_crypt_fiend"),
(53036,"spell_hadronox_periodic_summon_necromancer");
-- Assign custom AI to the Anub'ar foes
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (29062,29063,29064,29096,29097,29098);
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_champion" WHERE `entry` IN (29062,29096);
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_crypt_fiend" WHERE `entry` IN (29063,29097);
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_necromancer" WHERE `entry` IN (29064,29098);
-- And crusher pack creatures
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (28922,29117,29118,29119);
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_crusher" WHERE `entry` = 28922;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_crusher_champion" WHERE `entry` = 29117;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_crusher_crypt_fiend" WHERE `entry` = 29118;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_crusher_necromancer" WHERE `entry` = 29119;
-- Hadronox: Leeching Poison
DELETE FROM `spell_script_names` WHERE `scriptname` = "spell_hadronox_leeching_poison";
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES 
(53030,"spell_hadronox_leeching_poison"),
(59417,"spell_hadronox_leeching_poison");
-- Hadronox: Web Side Doors / Web Front Doors
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (53177,53185);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionTarget`,`ElseGroup`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`Comment`) VALUES
(13,1,53177,31,0,0,3,23472,@CGUID+3,"Web Front Door - Target Large AOI World Trigger Top Door 1"),
(13,1,53177,31,0,1,3,23472,@CGUID+4,"Web Front Door - Target Large AOI World Trigger Top Door 2"),
(13,1,53185,31,0,0,3,23472,@CGUID+5,"Web Side Door - Target Large AOI World Trigger Side Door");
DELETE FROM `spell_script_names` WHERE `scriptname`="spell_hadronox_web_doors";
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES
(53177,"spell_hadronox_web_doors"),
(53185,"spell_hadronox_web_doors");
-- Spell difficulty data
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (53406,57731,53318);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES
(53406,53406,59420), -- Hadronox - Web Grab
(53318,53318,59346); -- Crusher - Smash
-- Creature texts
DELETE FROM `creature_text` WHERE `entry` IN (28921,28922);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`probability`,`sound`,`TextRange`,`comment`) VALUES
(28921,1,0,"%s moves up the tunnel!",41,100,0,3,"Hadronox HADRONOX_EMOTE_MOVE"),
(28922,1,0,"The gate has been breached! Quickly, divert forces to deal with these invaders!",14,100,13941,3,"Anub'ar Crusher CRUSHER_SAY_AGGRO"),
(28922,2,0,"%s goes into a frenzy!",41,100,0,3,"Anub'ar Crusher CRUSHER_EMOTE_FRENZY");
-- Achievement: Hadronox Denied
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=4244;
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`ScriptName`) VALUES
(4244,11,"achievement_hadronox_denied");
