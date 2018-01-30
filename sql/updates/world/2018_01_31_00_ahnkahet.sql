-- Taldaram
UPDATE `creature_text` SET `TextRange`=1 WHERE `entry`=29308 AND `groupid`=0;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_prince_taldaram_conjure_flame_sphere", "spell_prince_taldaram_flame_sphere_summon");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(55931, "spell_prince_taldaram_conjure_flame_sphere"),
(55895, "spell_prince_taldaram_flame_sphere_summon"),
(59511, "spell_prince_taldaram_flame_sphere_summon"),
(59512, "spell_prince_taldaram_flame_sphere_summon");
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN  (55959, 55926);
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(55959, 55959, 59513),
(55926, 55926, 59508);
-- Nadox
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=7317;
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(7317,11,0,0,"achievement_respect_your_elders");
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_nadox_egg" WHERE `entry` IN (30172, 30173);
DELETE FROM `creature_template_addon` WHERE `entry` IN (30176, 31441, 30178, 30338, 31447);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(30176, 0, 0x0, 0x1, '56151'),
(31441, 0, 0x0, 0x1, '56151'),
(30178, 0, 0x0, 0x1, '56158'),
(30338, 0, 0x0, 0x1, '56158'),
(31447, 0, 0x0, 0x1, '56158');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=56159;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13,1,56159,0,0,31,0,3,30178,0,0,0,0,'','Swarm can only target Ahn''kahar Swarmer'),
(13,1,56159,0,1,31,0,3,30338,0,0,0,0,'','Swarm can only target Ahn''kahar Swarmer');
-- Amanitar
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_amanitar_healthy_mushroom" WHERE `entry`=30391;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_amanitar_poisonous_mushroom" WHERE `entry`=30435;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=56648;
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_amanitar_remove_mushroom_power";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(57283, "spell_amanitar_remove_mushroom_power");
-- Jedoga
UPDATE `creature_template` SET `unit_flags`=33587264, `InhabitType`=4, `HoverHeight`=0 WHERE `entry` IN (29310,31465);
UPDATE `creature` SET `MovementType`=0, `spawndist`=0 WHERE `guid`=131953;
UPDATE `creature_addon` SET `auras`='56075 56327' WHERE `guid`=131953;
UPDATE `creature_template` SET `ScriptName`='npc_twilight_volunteer' WHERE `entry`=30385;
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry` IN(30114,30181);
DELETE FROM `creature` WHERE `id` IN(30114,30181);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (56312);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition` ,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,56312,0,0,31,0,3,29310,0,0,0,'','Spell \'Beam Visual\' targets Jedoga Shadowseeker');
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_random_lightning_visual_effect';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(56328,'spell_random_lightning_visual_effect');
DELETE FROM `creature_text` WHERE `entry`=30385;
INSERT INTO `creature_text` (`entry`,`GroupID`,`ID`,`Text`,`Type`,`Language`,`Probability`,`Emote`,`Duration`,`Sound`,`TextRange`,`comment`) VALUES
(30385,0,0,'I have been chosen!',14,0,100,0,0,0,0,'SAY_CHOSEN'),
(30385,1,0,'I give myself to the master!',14,0,100,0,0,0,0,'SAY_SACRIFICED');
DELETE FROM  `creature_summon_groups` WHERE `summonerId`=29310 AND `groupId`=1;
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(29310,0,1,30114, 362.458, -714.166, -16.0964, 0.977384,6,3000),
(29310,0,1,30114, 368.781, -713.932, -16.0964, 1.46608,6,3000),
(29310,0,1,30114, 364.937, -716.11, -16.0964, 1.25664,6,3000),
(29310,0,1,30114, 362.02, -719.828, -16.0964, 1.20428,6,3000),
(29310,0,1,30114, 368.151, -719.763, -16.0964, 1.53589,6,3000),
(29310,0,1,30114, 392.276, -695.895, -16.0964, 3.40339,6,3000),
(29310,0,1,30114, 387.224, -698.006, -16.0964, 3.36848,6,3000),
(29310,0,1,30114, 389.626, -702.3, -16.0964, 3.07178,6,3000),
(29310,0,1,30114, 383.812, -700.41, -16.0964, 3.15905,6,3000),
(29310,0,1,30114, 385.693, -694.376, -16.0964, 3.59538,6,3000),
(29310,0,1,30114, 379.204, -716.697, -16.0964, 2.1293,6,3000),
(29310,0,1,30114, 375.4, -711.434, -16.0964, 2.09439,6,3000),
(29310,0,1,30114, 382.583, -711.713, -16.0964, 2.53073,6,3000),
(29310,0,1,30114, 379.049, -712.899, -16.0964, 2.28638,6,3000),
(29310,0,1,30114, 378.424, -708.388, -16.0964, 2.58309,6,3000);
DELETE FROM `creature_summon_groups` WHERE `summonerId`=29310 AND `groupId`=2;
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(29310,0,2,30111,427.3021,-717.3993,-17.95177,2.70526,7,0),
(29310,0,2,30111,429.7342,-712.1823,-17.95688,2.86234,7,0),
(29310,0,2,30111,434.4365,-709.4752,-17.96144,2.949606,7,0),
(29310,0,2,30111,434.0043,-702.8975,-17.95797,3.124139,7,0),
(29310,0,2,30111,439.9826,-699.0701,-17.95278,3.193953,7,0),
(29310,0,2,30111,381.8384,-773.3898,-17.95301,1.762783,7,0),
(29310,0,2,30111,387.0695,-770.9496,-17.95761,1.972222,7,0),
(29310,0,2,30111,392.5775,-765.6364,-17.95891,2.251475,7,0),
(29310,0,2,30111,394.3542,-760.8108,-17.95462,2.443461,7,0),
(29310,0,2,30111,388.3078,-766.784,-17.96076,2.094395,7,0);
DELETE FROM `creature_summon_groups` WHERE `summonerId`=29308 AND `groupId`=1;
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(29308,0,1,30181,519.146,-792.274,49.4627,4.15388,8,0),
(29308,0,1,30181,542.994,-762.115,36.0509,1.32645,8,0),
(29308,0,1,30181,599.617,-762.315,35.3111,1.71042,8,0),
(29308,0,1,30181,506.573,-890.563,45.1763,3.35103,8,0),
(29308,0,1,30181,632.232,-774.304,34.0595,0.750492,8,0),
(29308,0,1,30181,489.944,-851.356,52.09,4.95674,8,0),
(29308,0,1,30181,655.409,-814.264,35.2257,0.436332,8,0);
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=7359;
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(7359,11,0,0,'achievement_volunteer_work');

-- Trash
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (30279, 30278, 30277, 31104, 30287, 30285, 30284, 30286, 30179, 30319, 30414);
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_deep_crawler" WHERE `entry`=30279;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_ahnkahar_spell_flinger" WHERE `entry`=30278;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_ahnkahar_slasher" WHERE `entry` IN (30277, 31104);
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_plundering_geist" WHERE `entry`=30287;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_eye_of_taldaram" WHERE `entry`=30285;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_bonegrinder" WHERE `entry`=30284;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_frostbringer" WHERE `entry`=30286;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_twilight_apostle" WHERE `entry`=30179;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_twilight_darkcaster" WHERE `entry`=30319;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_forgotten_one" WHERE `entry`=30414;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_shadow_blast", "spell_shadow_sickle","spell_triple_slash");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(56698, "spell_shadow_blast"),
(59102, "spell_shadow_blast"),
(56702, "spell_shadow_sickle"),
(59103, "spell_shadow_sickle"),
(56643, "spell_triple_slash");
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (56580, 56581, 56698, 56702, 56701, 56646, 56715, 17439, 56730, 56733, 56736, 57825, 15063, 12550, 12739, 56898, 60845, 60833, 11986);
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(56580, 56580, 59108),
(56581, 56581, 59109),
(56698, 56698, 59102),
(56702, 56702, 59103),
(56701, 56701, 59104),
(56646, 56646, 32714),
(56715, 56715, 59114),
(17439, 17439, 17289),
(56730, 56730, 59111),
(56733, 56733, 61463),
(56736, 56736, 59107),
(57825, 57825, 61461),
(15063, 15063, 61462),
(12550, 12550, 61570),
(12739, 12739, 61562),
(56898, 56898, 61563),
(60845, 60845, 60851),
(60833, 60833, 60848),
(11986, 11986, 61569);
