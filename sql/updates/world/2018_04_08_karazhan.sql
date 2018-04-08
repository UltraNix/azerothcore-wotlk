-- Curator
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_curator_aggro_flare";
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(29856, "spell_curator_aggro_flare");
DELETE FROM `creature_onkill_reputation` WHERE `creature_id`=19782;
-- Shade of Aran
UPDATE `conditions` SET `ConditionValue2`=17176 WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=29967;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_aran_flame_wreath", "spell_aran_flame_wreath_aura", "spell_aran_flame_wreath_effect", "spell_aran_blizzard_activate", "spell_aran_frostbolt");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(29946, "spell_aran_flame_wreath_effect"),
(30004, "spell_aran_flame_wreath"),
(29947, "spell_aran_flame_wreath_aura"),
(29969, "spell_aran_blizzard_activate"),
(29954, "spell_aran_frostbolt");
UPDATE `creature_template` SET `ScriptName`="npc_aran_blizzard" WHERE `entry`=17161;
DELETE FROM `waypoint_data` WHERE `id`=171760;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(171760, 1, -11175.0, -1899.46, 232.009),
(171760, 2, -11169.4, -1896.52, 232.009),
(171760, 3, -11163.1, -1895.94, 232.009),
(171760, 4, -11157.1, -1897.81, 232.009),
(171760, 5, -11152.2, -1901.84, 232.009),
(171760, 6, -11149.3, -1907.42, 232.009),
(171760, 7, -11148.7, -1913.69, 232.009),
(171760, 8, -11150.6, -1919.72, 232.009),
(171760, 9, -11154.6, -1924.56, 232.009),
(171760, 10, -11160.2, -1927.5, 232.009),
(171760, 11, -11166.5, -1928.08, 232.009),
(171760, 12, -11172.5, -1926.21, 232.009),
(171760, 13, -11177.4, -1922.18, 232.009),
(171760, 14, -11180.3, -1916.6, 232.009),
(171760, 15, -11180.9, -1910.33, 232.009),
(171760, 16, -11179, -1904.3, 232.009);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (29969, 29962, 37051, 37052, 37053) AND `ConditionTypeOrReference`=31;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 29969, 0, 0, 31, 0, 3, 17161, 0, 0, 0, 0, "", ""),
(13, 1, 29962 , 0, 0, 31, 0, 3, 17174, 0, 0, 0, 0, "", ""),
(13, 1, 37051 , 0, 0, 31, 0, 3, 17173, 0, 0, 0, 0, "", ""),
(13, 1, 37052 , 0, 0, 31, 0, 3, 17172, 0, 0, 0, 0, "", ""),
(13, 1, 37053 , 0, 0, 31, 0, 3, 17175, 0, 0, 0, 0, "", "");
-- Netherspite
DELETE FROM `creature_template_addon` WHERE `entry` IN (17369, 17367, 17368);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(17369, 30487),
(17367, 30490),
(17368, 30491);
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_netherspite_nether_beam_effect", "spell_netherspite_player_debuff","spell_netherspite_empowerment", "spell_netherspite_roar", "spell_netherspite_nether_beam_selector");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(30463, "spell_netherspite_nether_beam_effect"),
(30464, "spell_netherspite_nether_beam_effect"),
(30465, "spell_netherspite_nether_beam_effect"),
(30421, "spell_netherspite_player_debuff"),
(30422, "spell_netherspite_player_debuff"),
(30423, "spell_netherspite_player_debuff"),
(38549, "spell_netherspite_empowerment"),
(38684, "spell_netherspite_roar"),
(30469, "spell_netherspite_nether_beam_selector");
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=30469 AND `ConditionTypeOrReference` IN (31, 32);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 30469, 0, 0, 31, 0, 3, 15689, 0, 0, 0, 0, "", ""),
(13, 1, 30469, 0, 1, 31, 0, 4, 0, 0, 0, 0, 0, "", "");
DELETE FROM `creature_text` WHERE `entry`=15689;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(15689, 0, 0, "Netherspite cries out in withdrawal, opening gates to the nether", 41, 0, 100, 0, 0, 0, 0, "EMOTE_PORTALS"),
(15689, 1, 0, "Netherspite goes into a nether-fed rage!", 41, 0, 100, 0, 0, 0, 0, "EMOTE_BANISH");
-- Malchezaar
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (30861, 30835)  AND `ConditionTypeOrReference`=31;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 30861, 0, 0, 31, 0, 3, 17645, 0, 0, 0, 0, "", ""),
(13, 1, 30835, 0, 0, 31, 0, 3, 17644, 0, 0, 0, 0, "", "");
DELETE FROM `spell_dbc` WHERE `Id`=30861;
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectItemType1`, `EffectItemType2`, `EffectItemType3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `SchoolMask`, `Comment`) VALUES 
(30861, 0, 0, 536871168, 136, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 101, 0, 0, 0, 0, 0, 13, 0, -1, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 'Infernal Relay Selector');
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ("spell_malchezzar_infernal_relay_selector", "spell_malchezzar_infernal_relay", "spell_malchezzar_amplify_damage", "spell_malchezzar_enfeeble", "spell_malchezzar_shadow_word_pain");
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(30835, "spell_malchezzar_infernal_relay_selector"),
(30861, "spell_malchezzar_infernal_relay"),
(39095, "spell_malchezzar_amplify_damage"),
(30843, "spell_malchezzar_enfeeble"),
(30898, "spell_malchezzar_shadow_word_pain");
UPDATE `spell_dbc` SET `EffectImplicitTargetA1`=0, `EffectImplicitTargetB1`=7, `EffectRadiusIndex1`=30 WHERE `Id`=30861;
UPDATE `creature_template` SET `ScriptName`="npc_flying_axe" WHERE `entry`=17650;
UPDATE `creature_template` SET `ScriptName`="npc_infernal_target" WHERE `entry`=17644;
UPDATE `conditions` SET `ConditionValue2`=17644 WHERE `SourceEntry`=30834 AND `SourceTypeOrReferenceId`=13;
-- Terestian
DELETE FROM `spell_target_position` WHERE `id`=30120;
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES 
(30120, 532, -11234.2, -1698.46, 179.24, 0.67621);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (30065, 30191)  AND `ConditionTypeOrReference`=31;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 30065, 0, 0, 31, 0, 3, 15688, 0, 0, 0, 0, "", ""),
(13, 1, 30191, 0, 0, 31, 0, 3, 17265, 0, 0, 0, 0, "", "");
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_terestian_spawn_imp";
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(30191, "spell_terestian_spawn_imp");
-- Opera
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (7421, 7422, 7441, 7442, 7443);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`) VALUES
(7421, 0, 0, "I'm not an actor.", 1, 1, 7422),
(7422, 0, 0, "Ok, I'll give it a try, then.", 1, 1, 0),
(7441, 0, 0, "Oh, grandmother, what big ears you have.", 1, 1, 7442),
(7442, 0, 0, "Oh, grandmother, what big eyes you have.", 1, 1, 7443),
(7443, 0, 0, "Oh, grandmother, what phat lewts you have.", 1, 1, 0);
DELETE FROM `creature_text` WHERE `entry`=16812;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(16812, 0, 0, 'Splendid. I\'m going to get the audience ready. Break a leg!', 14, 0, 100, 0, 0, 0/*@todo soundid*/, 0, "SAY_BARNES_BEGIN"),
(16812, 1, 0, 'Welcome ladies and gentlemen, to this evening\'s presentation!', 14, 0, 100, 0, 0, 9174, 0, "SAY_BARNES_WELCOME"),
(16812, 2, 0, 'Tonight we plumb the depths of the human soul as we join a lost, lonely girl trying desperately--with the help of her loyal companions--to find her way home!', 14, 0, 100, 0, 0, 9338, 0, "SAY_BARNES_OZ_1"),
(16812, 3, 0, 'But she is pursued... by a wicked, malevolent crone!', 14, 0, 100, 0, 0, 9339, 0, "SAY_BARNES_OZ_2"),
(16812, 4, 0, 'Will she survive? Will she prevail? Only time will tell. And now... on with the show!', 14, 0, 100, 0, 0, 9340, 0, "SAY_BARNES_OZ_3"),
(16812, 5, 0, 'Tonight, things are not what they seem... for tonight your eyes may not be trusted!', 14, 0, 100, 0, 0, 9335, 0, "SAY_BARNES_HOOD_1"),
(16812, 6, 0, 'Take for instance this quiet elderly woman waiting for a visit from her granddaughter... surely there is nothing to fear from this sweet, gray-haired old lady!', 14, 0, 100, 0, 0, 9336, 0, "SAY_BARNES_HOOD_2"),
(16812, 7, 0, 'But don\'t let me pull the wool over your eyes! See for yourself what lies beneath those covers! And now... on with the show!', 14, 0, 100, 0, 0, 9337, 0, "SAY_BARNES_HOOD_3"),
(16812, 8, 0, 'Tonight... we explore a tale of forbidden love!', 14, 0, 100, 0, 0, 9341, 0, "SAY_BARNES_ROMEO_JULIANNE_1"),
(16812, 9, 0, 'But beware, for not all love stories end happily, as you may find out. Sometimes, love pricks like a thorn!', 14, 0, 100, 0, 0, 9342, 0, "SAY_BARNES_ROMEO_JULIANNE_2"),
(16812, 10, 0, 'But don\'t take it from me; see for yourself what tragedy lies ahead when the paths of star crossed lovers meet! And now... on with the show!', 14, 0, 100, 0, 0, 9343, 0, "SAY_BARNES_ROMEO_JULIANNE_3");
DELETE FROM `waypoint_data` WHERE `id`=1358230;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES
(1358230, 0, -10876.036133, -1779.007446, 90.477364, 0),
(1358230, 1, -10895.182617, -1782.360840, 90.477364, 4.578353);
DELETE FROM `waypoint_data` WHERE `id`=1358231;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES
(1358231, 0, -10876.036133, -1779.007446, 90.477364, 0),
(1358231, 1, -10866.7, -1781.03, 90.5517, 1.41372);
DELETE FROM `spell_script_names` WHERE `ScriptName` IN("spell_wolf_pick_red_riding_hood", "spell_wolf_red_riding_hood");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(30769, "spell_wolf_pick_red_riding_hood"),
(30756, "spell_wolf_red_riding_hood");
UPDATE `creature_template` SET `ScriptName`="boss_big_bad_wolf" WHERE `entry`=17521;
DELETE FROM `creature_summon_groups` WHERE `summonerId`=16812;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`, `summonTime`) VALUES 
(16812, 0, 0, 17603, -10892.0, -1758.0, 90.5, 4.738, 1, 7200000), -- Grandmother
(16812, 0, 1, 17535, -10896.0, -1758.0, 90.5, 4.738, 1, 7200000), -- Dorothee
(16812, 0, 1, 17546, -10891.0, -1758.0, 90.5, 4.738, 1, 7200000), -- Roar
(16812, 0, 1, 17547, -10884.0, -1758.0, 90.5, 4.738, 1, 7200000), -- Tinhead
(16812, 0, 1, 17543, -10902.0, -1758.0, 90.5, 4.738, 1, 7200000), -- Strawman
(16812, 0, 1, 18168, -10891.96, -1755.95, 90.5, 4.64, 1, 7200000), -- Crone
(16812, 0, 2, 17534, -10892.0, -1758.0, 90.5, 4.738, 1, 7200000); -- Julianne
UPDATE `creature_text` SET `type`=12 WHERE `entry`=16812 AND `groupid`=0; -- Barnes yell->say
UPDATE `creature_template` SET `ScriptName`="npc_dorothee" WHERE `entry`=17535;
UPDATE `creature_template` SET `ScriptName`="npc_tito" WHERE `entry`=17548;
UPDATE `creature_template` SET `ScriptName`="npc_strawman" WHERE `entry`=17543;
UPDATE `creature_template` SET `ScriptName`="npc_tinhead" WHERE `entry`=17547;
UPDATE `creature_template` SET `ScriptName`="npc_roar" WHERE `entry`=17546;
-- Midnight
SET @ATTUMEN_UNMOUNTED := 15550;
SET @ATTUMEN_MOUNTED   := 16152;
SET @MIDNIGHT          := 16151;
SET @GMIDNIGHT         := 135159;
UPDATE `creature_template` SET `baseattacktime`=2000 WHERE `entry` IN (@ATTUMEN_UNMOUNTED, @ATTUMEN_MOUNTED, @MIDNIGHT);
DELETE FROM `creature_text` WHERE `entry` IN (@MIDNIGHT, @ATTUMEN_UNMOUNTED, @ATTUMEN_MOUNTED);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(@ATTUMEN_UNMOUNTED, 0, 0, 'It was... inevitable.', 14, 0, 100, 0, 0, 9169, 0, 'attumen SAY_KILL1'),
(@ATTUMEN_UNMOUNTED, 0, 1, 'Another trophy to add to my collection!', 14, 0, 100, 0, 0, 9300, 0,'attumen SAY_KILL2'),
(@ATTUMEN_UNMOUNTED, 1, 0, 'Such easy sport.', 14, 0, 100, 0, 0, 9170, 0,'attumen SAY_RANDOM1'),
(@ATTUMEN_UNMOUNTED, 1, 1, 'Amateurs! Do not think you can best me! I kill for a living.', 14, 0, 100, 0, 0, 9304, 0, 'attumen SAY_RANDOM2'),
(@ATTUMEN_UNMOUNTED, 2, 0, 'Weapons are merely a convenience for a warrior of my skill!', 14, 0, 100, 0, 0, 9166, 0, 'attumen SAY_DISARMED'),
(@ATTUMEN_UNMOUNTED, 3, 0, 'Well done, Midnight!', 14, 0, 100, 0, 0, 9173, 0, 'attumen SAY_MIDNIGHT_KILL'),
(@ATTUMEN_UNMOUNTED, 4, 0, 'Cowards! Wretches!', 14, 0, 100, 0, 0, 9167, 0, 'attumen SAY_APPEAR1'),
(@ATTUMEN_UNMOUNTED, 4, 1, 'Who dares attack the steed of the Huntsman?', 14, 0, 100, 0, 0, 9298, 0, 'attumen SAY_APPEAR2'),
(@ATTUMEN_UNMOUNTED, 4, 2, 'Perhaps you would rather test yourselves against a more formidable opponent?!', 14, 0, 100, 0, 0, 9299, 0, 'attumen SAY_APPEAR3'),
(@ATTUMEN_UNMOUNTED, 5, 0, 'Come Midnight, let\'s disperse this petty rabble!', 14, 0, 100, 0, 0, 9168, 0, 'attumen SAY_MOUNT'),
(@ATTUMEN_MOUNTED, 0, 0, 'It was... inevitable.', 14, 0, 100, 0, 0, 9169, 0, 'attumen SAY_KILL1'),
(@ATTUMEN_MOUNTED, 0, 1, 'Another trophy to add to my collection!', 14, 0, 100, 0, 0, 9300, 0,'attumen SAY_KILL2'),
(@ATTUMEN_MOUNTED, 1, 0, 'Such easy sport.', 14, 0, 100, 0, 0, 9170, 0,'attumen SAY_RANDOM1'),
(@ATTUMEN_MOUNTED, 1, 1, 'Amateurs! Do not think you can best me! I kill for a living.', 14, 0, 100, 0, 0, 9304, 0, 'attumen SAY_RANDOM2'),
(@ATTUMEN_MOUNTED, 2, 0, 'Weapons are merely a convenience for a warrior of my skill!', 14, 0, 100, 0, 0, 9166, 0, 'attumen SAY_DISARMED'),
(@ATTUMEN_MOUNTED, 3, 0, 'Always knew... someday I would become... the hunted.', 14, 0, 100, 0, 0, 9165, 0, 'attumen SAY_DEATH'),
(@MIDNIGHT, 0, 0, '%s calls for her master!', 16, 0, 100, 0, 0, 0, 0, 'midnight EMOTE_CALL_ATTUMEN'),
(@MIDNIGHT, 1, 0, '%s rushes to her master\'s aid.', 16, 0, 100, 0, 0, 0, 0, 'midnight EMOTE_MOUNT_UP');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = 29770;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 29770, 0, 0, 31, 0, 3, @ATTUMEN_UNMOUNTED, 0, 0, 0, 0, '', 'Mount spell only hit Attumen the Huntsmen');
UPDATE `creature_template` SET `ScriptName` = 'boss_attumen', `lootid` = @ATTUMEN_MOUNTED WHERE `entry` = @ATTUMEN_MOUNTED;
UPDATE `creature_loot_template` SET `entry` = @ATTUMEN_MOUNTED WHERE `entry` = @ATTUMEN_UNMOUNTED;
-- Moroes
UPDATE `creature_template` SET `ScriptName`="boss_baroness_dorothea_millstipe" WHERE `entry`=19875;
UPDATE `creature_template` SET `ScriptName`="boss_baron_rafe_dreuger" WHERE `entry`=19874;
UPDATE `creature_template` SET `ScriptName`="boss_lady_catriona_von_indi" WHERE `entry`=19872;
UPDATE `creature_template` SET `ScriptName`="boss_lady_keira_berrybuck" WHERE `entry`=17007;
UPDATE `creature_template` SET `ScriptName`="boss_lord_robin_daris" WHERE `entry`=19876;
UPDATE `creature_template` SET `ScriptName`="boss_lord_crispin_ference" WHERE `entry`=19873;
-- Servant Quarters
DELETE FROM `creature_template_addon` WHERE `entry`=16179;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(16179, "22766");
DELETE FROM `creature_text` WHERE `entry` IN (16179, 16180, 16181);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(16179, 0, 0, '%s skitters out from the shadows...', 16, 0, 100, 0, 0, 0, 3, "Hyakiss"),
(16180, 0, 0, '%s flaps down from the ceiling...', 16, 0, 100, 0, 0, 0, 3, "Shadikith"),
(16181, 0, 0, '%s howls through the halls...', 16, 0, 100, 0, 0, 0, 3, "Rokad");
UPDATE `creature_template` SET `ScriptName`="boss_servant_quarters" WHERE `entry` IN (16179, 16180, 16181);
-- Nightbane
DELETE FROM `creature_onkill_reputation` WHERE `creature_id`=17261;
UPDATE `creature_template` SET `ScriptName`="npc_restless_skeleton" WHERE `entry`=17261;
UPDATE `creature_template` SET `flags_extra`=536871681, `InhabitType`=7 WHERE `entry`=17225;
UPDATE `creature_text` SET `TextRange`=3 WHERE `entry`=17225;
UPDATE `creature_model_info` SET `bounding_radius`=0.45, `combat_reach`=10.5 WHERE `modelid`=18062;
UPDATE `creature_template_addon` SET `bytes2`=1 WHERE `entry`=17225;
UPDATE `gameobject_template` SET `ScriptName`= 'go_blackened_urn', `data2`=0 WHERE `entry`=194092;
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_rain_of_bones';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`)VALUES
(37098,'spell_rain_of_bones');
DELETE FROM `script_spline_chain_meta` WHERE `entry`=17225;
INSERT INTO `script_spline_chain_meta` (`entry`,`chainId`,`splineId`,`expectedDuration`,`msUntilNext`) VALUES
(17225, 1, 0, 3689, 0),
(17225, 2, 0, 26021, 0),
(17225, 3, 0, 2697, 0),
(17225, 4, 0, 15920, 0),
(17225, 5, 0, 15920, 0);
DELETE FROM `script_spline_chain_waypoints` WHERE `entry`=17225;
INSERT INTO `script_spline_chain_waypoints` (`entry`,`chainId`,`splineId`,`wpId`,`x`,`y`,`z`) VALUES
(17225, 1, 0, 0, -11003.710, -1760.1940, 140.25340),
(17225, 1, 0, 1, -11018.860, -1797.2690, 172.85250),
(17225, 2, 0, 0, -11018.860, -1797.2690, 172.85250),
(17225, 2, 0, 1, -11105.760, -1875.9000, 158.97800),
(17225, 2, 0, 2, -11175.100, -1857.2240, 101.00590),
(17225, 2, 0, 3, -11296.930, -1764.5310, 101.00590),
(17225, 2, 0, 4, -11258.900, -1722.3720, 101.00590),
(17225, 2, 0, 5, -11176.760, -1809.5990, 101.00590),
(17225, 2, 0, 6, -11191.110, -1889.3960, 107.89480),
(17225, 2, 0, 7, -11152.180, -1863.3180, 101.00590),
(17225, 2, 0, 8, -11130.680, -1891.4230, 107.89630),
(17225, 2, 0, 9, -11110.670, -1878.7710, 107.89690),
(17225, 3, 0, 0, -11110.670, -1878.7710, 107.89690),
(17225, 3, 0, 1, -11142.710, -1891.1930, 92.250380),
(17225, 4, 0, 0, -11162.230, -1900.3290, 94.727470),
(17225, 4, 0, 1, -11162.230, -1900.3290, 91.472650),
(17225, 5, 0, 0, -11160.130, -1870.6830, 97.738760),
(17225, 5, 0, 1, -11117.730, -1941.2610, 127.17200),
(17225, 5, 0, 2, -11123.780, -1968.2430, 125.92200),
(17225, 5, 0, 3, -11148.340, -1972.9800, 116.69970),
(17225, 5, 0, 4, -11161.620, -1945.7250, 103.08860),
(17225, 5, 0, 5, -11168.010, -1922.9050, 97.394150),
(17225, 5, 0, 6, -11162.230, -1900.3290, 94.727470);
-- Trash
DELETE FROM `smart_scripts` WHERE `source_type` = 0 AND `entryorguid` IN (16170, 16171, 16173, 16174, 16175, 16176, 16177, 16178);
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_coldmist_stalker" WHERE `entry`=16170;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_coldmist_widow" WHERE `entry`=16171;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_shadowbat" WHERE `entry`=16173;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_greater_shadowbat" WHERE `entry`=16174;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_vampiric_shadowbat" WHERE `entry`=16175;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_shadowbeast" WHERE `entry`=16176;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_dreadbeast" WHERE `entry`=16177;
UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_phase_hound" WHERE `entry`=16178;
