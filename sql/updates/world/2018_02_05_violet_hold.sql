DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=58694;

DELETE FROM `spell_script_names` WHERE `ScriptName` IN (
'spell_cyanigosa_arcane_vacuum',
'spell_ichoron_splatter',
'spell_ichoron_protective_bubble',
'spell_ichoron_drained',
'spell_ichoron_merge',
'spell_moragg_ray',
'spell_moragg_ray_of_pain',
'spell_moragg_ray_of_suffering',
'spell_xevozz_summon_ethereal_sphere',
'spell_violet_hold_destroy_door_seal',
'spell_violet_hold_portal_periodic',
'spell_violet_hold_teleport_player',
'spell_crystal_activation',
'spell_xevozz_summon_players'
);
INSERT INTO `spell_script_names`(`spell_id`,`ScriptName`) values
(58694,'spell_cyanigosa_arcane_vacuum'),
(54259,'spell_ichoron_splatter'),
(54306,'spell_ichoron_protective_bubble'),
(59820,'spell_ichoron_drained'),
(54269,'spell_ichoron_merge'),
(54438,'spell_moragg_ray'),
(54442,'spell_moragg_ray'),
(59523,'spell_moragg_ray'),
(59524,'spell_moragg_ray'),
(58040,'spell_violet_hold_destroy_door_seal'),
(58008,'spell_violet_hold_portal_periodic'),
(62138,'spell_violet_hold_teleport_player'),
(54164, 'spell_xevozz_summon_players');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 and `SourceEntry` IN (57912, 57930, 58152, 54258, 54264, 54265, 54266, 54267, 54269);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,57912,0,0,31,0,3,29425,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,57930,0,0,31,0,3,30857,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,0,31,0,3,30661,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,1,31,0,3,30662,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,2,31,0,3,30663,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,3,31,0,3,30664,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,4,31,0,3,30665,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,5,31,0,3,30666,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,6,31,0,3,30667,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,7,31,0,3,30668,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,8,31,0,3,30918,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,9,31,0,3,30961,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,10,31,0,3,30962,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,11,31,0,3,30963,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,12,31,0,3,31007,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,13,31,0,3,31008,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,14,31,0,3,31009,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,15,31,0,3,31010,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,16,31,0,3,31118,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,58152,0,17,31,0,3,32191,0,0,0,0,'','Defense System - Arcane Lightning'),
(13,1,54258,0,0,31,0,3,29326,102906,0,0,0,'','Ichoron - Water Globule'),
(13,1,54264,0,0,31,0,3,29326,102905,0,0,0,'','Ichoron - Water Globule'),
(13,1,54265,0,0,31,0,3,29326,102904,0,0,0,'','Ichoron - Water Globule'),
(13,1,54266,0,0,31,0,3,29326,102901,0,0,0,'','Ichoron - Water Globule'),
(13,1,54267,0,0,31,0,3,29326,102902,0,0,0,'','Ichoron - Water Globule'),
(13,1,54269,0,0,31,0,3,29313,0,0,0,0,'','Ichoron - Merge');

UPDATE `creature_template` SET `gossip_menu_id`=9997 WHERE `entry`=30658;

UPDATE `gossip_menu_option` SET `action_menu_id`=9998 WHERE `menu_id`=9997;

UPDATE `creature_template` SET `ScriptName`='npc_violet_hold_teleportation_portal' WHERE `entry`=30679;
UPDATE `creature_template` SET `ScriptName`='npc_violet_hold_teleportation_portal_elite' WHERE `entry`=32174;
UPDATE `creature_template` SET `ScriptName`='npc_violet_hold_teleportation_portal_intro' WHERE `entry`=31011;

UPDATE `creature_template` SET `ScriptName`='npc_violet_hold_defense_system' WHERE `entry`=30837;

UPDATE `creature_template` SET `unit_flags`=832 WHERE `entry` IN (31134, 31506); -- Cyanigosa

UPDATE `creature_template` SET `speed_walk`=2.22222/2.5, `speed_run`=8.0/7.0, `unit_flags`=768 WHERE `entry` IN (31079, 31492); -- Azure Saboteur

UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=12.0/7.0, `unit_flags`=832 WHERE `entry` IN (29266, 31511, 32231, 32552); -- Xevozz
UPDATE `creature_template` SET `speed_walk`=3.0/2.5, `speed_run`=3.0/7.0 WHERE `entry` IN (29271, 31514, 32582, 32583); -- Ethereal Sphere
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=12.0/7.0, `unit_flags`=832 WHERE `entry` IN (29312, 31509, 32237, 32553); -- Lavanthor
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=12.0/7.0, `unit_flags`=832 WHERE `entry` IN (29313, 31508, 32234, 32554); -- Ichoron
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=4.0/7.0, `unit_flags`=33587200 WHERE `entry` IN (29321, 31515); -- Ichor Globule
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=12.0/7.0, `unit_flags`=832 WHERE `entry` IN (29314, 31512, 32230, 32555); -- Zuramat
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=10.0/7.0, `unit_flags`=33600 WHERE `entry` IN (29315, 31507, 32226, 32550); -- Erekem
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=10.0/7.0, `unit_flags`=33600 WHERE `entry` IN (29395, 31513, 32228, 32549); -- Erekem Guard
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=12.0/7.0, `unit_flags`=33600 WHERE `entry` IN (29316, 31510, 32235, 32551); -- Moragg

UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_xevozz' WHERE `entry`=32231; -- Xevozz
UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_lavanthor' WHERE `entry`=32237; -- Lavanthor
UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_ichoron' WHERE `entry`=32234; -- Ichoron
UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_zuramat' WHERE `entry`=32230; -- Zuramat
UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_erekem' WHERE `entry`=32226; -- Erekem
UPDATE `creature_template` SET `minlevel`=76, `maxlevel`=76, `ScriptName`='npc_erekem_guard' WHERE `entry`=32228; -- Erekem Guard
UPDATE `creature_template` SET `minlevel`=77, `maxlevel`=77, `ScriptName`='boss_moragg' WHERE `entry`=32235; -- Moragg

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29364, 29365); -- Void Sentry
UPDATE `creature_template` SET `flags_extra`=0, `AIName`='', `ScriptName`='npc_void_sentry' WHERE `entry`=29364; -- Void Sentry
UPDATE `creature_template` SET `AIName`='' WHERE `entry`=29365; -- Void Sentry
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry` IN (29364, 31518);
UPDATE `creature_template` SET `unit_flags`=33554432, `unit_flags2`=2080 WHERE `entry` IN (29365, 31519); -- Void Sentry

UPDATE `creature_template` SET `flags_extra`=`flags_extra`|0x1 WHERE `entry` IN (32552, 32553, 32554, 32555, 32550, 32551);
UPDATE `creature_template` SET `mechanic_immune_mask`=536941137 WHERE `entry` IN (32231, 32552, 32237, 32553, 32234, 32554, 32230, 32555, 32226, 32550, 32228, 32549, 32235, 32551);

UPDATE `creature_template` SET `InhabitType`=4, `flags_extra`=128 WHERE `entry`=30837;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (29326, 30896);
UPDATE `creature` SET `modelid`=0, `spawndist`=0, `MovementType`=0 WHERE `id` IN (29326, 30896);

UPDATE `creature_template` SET `AIName`='' WHERE `entry` IN (32226,32228,32230,32231,32234,32235,32237);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (32226,32228,32230,32231,32234,32235,32237);

DELETE FROM `creature_template_addon` WHERE `entry` IN (30837, 30896, 31079, 29364, 29365, 31518, 31519);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(30837, 0, 0x3000000, 0x1, '57886 57887'),
(30896, 0, 0x3000000, 0x1, ''),
(31079, 0, 0x0, 0x1, '31635'),
(29364, 0, 0x0, 0x1, '54351 54341'),
(29365, 0, 0x0, 0x1, '54351 54342'),
(31518, 0, 0x0, 0x1, '54351 54341'),
(31519, 0, 0x0, 0x1, '54351 59747');

DELETE FROM `creature_text` WHERE `entry` IN (30658, 32204, 29271);
DELETE FROM `creature_text` WHERE `entry`=29313 AND `groupid`=7;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(30658, 0, 0, 'Prison guards, we are leaving! These adventurers are taking over! Go go go!', 14, 0, 100, 5, 0, 0, 3, 'Lieutenant Sinclari - Intro 1'),
(30658, 1, 0, 'I''m locking the door. Good luck, and thank you for doing this.', 12, 0, 100, 396, 0, 0, 3, 'Lieutenant Sinclari - Intro 2'),
(30658, 2, 0, 'You did it! You held the Blue Dragonflight back and defeated their commander. Amazing work!', 12, 0, 100, 396, 0, 0, 3, 'Lieutenant Sinclari - Outro'),

(32204, 0, 0, 'An elite Blue Dragonflight squad appears from the portal!', 41, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Blue Dragonflight squad'),
(32204, 1, 0, 'A Portal Guardian defends the new portal!', 41, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Portal Guardian'),
(32204, 2, 0, 'A Portal Keeper emerges from the portal!', 41, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Portal Keeper'),
(32204, 3, 0, 'Adventurers, the door is beginning to weaken!', 14, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Door weaken'),
(32204, 4, 0, 'Only half of the door seal''s strength remains! You must fight on!', 14, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Half Door Seal reains'),
(32204, 5, 0, 'The door seal is about to collapse! All is lost if the Blue Dragonflight breaks through the door!', 14, 0, 100, 0, 0, 0, 3, 'Lieutenant Sinclari - Door Seal broken'),

(29313, 7, 0, '%s''s Protective Bubble shatters!', 41, 0, 100, 0, 0, 0, 0, 'Ichoron - Emote Shatter'),

(29271, 0, 0, '%s begins to summon!', 41, 0, 100, 0, 0, 0, 3, 'Ethereal Sphere');

UPDATE `creature_text` SET `sound`=14499 WHERE `entry`=29266 AND `groupid`=0;
UPDATE `creature_text` SET `emote`=396 WHERE `entry`=29266 AND `groupid`=3;
UPDATE `creature_text` SET `emote`=15 WHERE `entry`=29315 AND `groupid`=3;
UPDATE `creature_text` SET `emote`=396 WHERE `entry`=31134 AND `groupid`=3;

DELETE FROM `spell_target_position` WHERE `id` IN (54102, 54137, 54138, 61337, 61338, 61339, 62139);
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`) VALUES
(54102, 0, 608, 1854.36, 802.65, 44.3),
(54137, 0, 608, 1899.18, 824.7,  38.72333),
(54138, 0, 608, 1891.42, 788.04, 38.64),
(61337, 0, 608, 1854.36, 802.65, 44.3),
(61338, 0, 608, 1899.18, 824.7,  38.72333),
(61339, 0, 608, 1891.42, 788.04, 38.64),
(62139, 0, 608, 1857.24, 803.877, 44.0085);

-- 3.3.5 only
DELETE FROM `spelldifficulty_dbc` WHERE `spellid0` IN (54102, 54137, 54138, 54207, 54438, 54442);
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`) VALUES
(54207, 54207, 59476),
(54438, 54438, 59523),
(54442, 54442, 59524);

UPDATE `creature_template` SET `ScriptName`="npc_sinclari_vh" WHERE `entry`=30658;
UPDATE `gameobject_template` SET `flags`=48, `ScriptName`='go_activation_crystal' WHERE `entry`=193611;

UPDATE `creature_template` SET `ScriptName`="npc_ethereal_sphere", `InhabitType`=3 WHERE `entry` IN (29271, 32582);

-- Bosses
SET @ENTRY := 29266;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 29312;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 29313;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 29314;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 29315;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 29316;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

SET @ENTRY := 31134;
SET @ENTRY_HEROIC := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (@ENTRY_HEROIC);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(@ENTRY_HEROIC, 1037, 1052, 7, 0, 325, 7, 0, 325, 1);

-- Texts
SET @ENTRY := 30695;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The destruction of Dalaran is inevitable!", 14, "Portal Guardian SAY_SPAWN"),
(@ENTRY, 0, 1, "The portal has stabilized! Attack!", 14, "Portal Guardian SAY_SPAWN"),
(@ENTRY, 0, 2, "The way into Dalaran has been opened!", 14, "Portal Guardian SAY_SPAWN"),
(@ENTRY, 1, 0, "Your pathetic defense ends here!", 14, "Portal Guardian SAY_AGGRO"),
(@ENTRY, 1, 1, "You shall not disrupt this portal!", 14, "Portal Guardian SAY_AGGRO"),
(@ENTRY, 2, 0, "More portals will take this one's place!", 14, "Portal Guardian SAY_DEATH"),
(@ENTRY, 2, 1, "My death will not stop this invasion!", 14, "Portal Guardian SAY_DEATH"),
(@ENTRY, 2, 2, "Why do you defend the Kirin Tor...", 14, "Portal Guardian SAY_DEATH");

SET @ENTRY := 30660;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The destruction of Dalaran is inevitable!", 14, "Portal Keeper SAY_SPAWN"),
(@ENTRY, 0, 1, "The portal has stabilized! Attack!", 14, "Portal Keeper SAY_SPAWN"),
(@ENTRY, 0, 2, "The way into Dalaran has been opened!", 14, "Portal Keeper SAY_SPAWN"),
(@ENTRY, 1, 0, "Your pathetic defense ends here!", 14, "Portal Keeper SAY_AGGRO"),
(@ENTRY, 1, 1, "You shall not disrupt this portal!", 14, "Portal Keeper SAY_AGGRO"),
(@ENTRY, 2, 0, "More portals will take this one's place!", 14, "Portal Keeper SAY_DEATH"),
(@ENTRY, 2, 1, "My death will not stop this invasion!", 14, "Portal Keeper SAY_DEATH"),
(@ENTRY, 2, 2, "Why do you defend the Kirin Tor...", 14, "Portal Keeper SAY_DEATH");

SET @ENTRY := 30661;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Invader SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Invader SAY_DEATH");

SET @ENTRY := 30662;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Spellbreaker SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Spellbreaker SAY_DEATH");

SET @ENTRY := 30663;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Binder SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Binder SAY_DEATH");

SET @ENTRY := 30665;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Veteran Mage Hunter SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Veteran Mage Hunter SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Veteran Mage Hunter SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Veteran Mage Hunter SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Veteran Mage Hunter SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Veteran Mage Hunter SAY_DEATH");

SET @ENTRY := 30666;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Captain SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Captain SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Captain SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Captain SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Captain SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Captain SAY_DEATH");

SET @ENTRY := 30667;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Sorceror SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Sorceror SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Sorceror SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Sorceror SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Sorceror SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Sorceror SAY_DEATH");

SET @ENTRY := 30668;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Raider SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Raider SAY_DEATH");

SET @ENTRY := 30918;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Binder SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Binder SAY_DEATH");

SET @ENTRY := 30961;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Invader SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Invader SAY_DEATH");

SET @ENTRY := 30962;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Spellbreaker SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Spellbreaker SAY_DEATH");

SET @ENTRY := 31007;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Binder SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Binder SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Binder SAY_DEATH");

SET @ENTRY := 31008;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Invader SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Invader SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Invader SAY_DEATH");

SET @ENTRY := 31009;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Spellbreaker SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Spellbreaker SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Spellbreaker SAY_DEATH");

SET @ENTRY := 31010;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Mage Slayer SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Mage Slayer SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Mage Slayer SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Mage Slayer SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Mage Slayer SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Mage Slayer SAY_DEATH");

SET @ENTRY := 31118;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Raider SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Raider SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Raider SAY_DEATH");

SET @ENTRY := 32191;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES
(@ENTRY, 0, 0, "The Kirin Tor must be stopped!", 12, "Azure Stalker SAY_AGGRO"),
(@ENTRY, 0, 1, "Destroy all who stand against us!", 12, "Azure Stalker SAY_AGGRO"),
(@ENTRY, 0, 2, "Dalaran must fall!", 12, "Azure Stalker SAY_AGGRO"),
(@ENTRY, 0, 3, "For the Spellweaver!", 12, "Azure Stalker SAY_AGGRO"),
(@ENTRY, 1, 0, "The Nexus War will not be stopped!", 12, "Azure Stalker SAY_DEATH"),
(@ENTRY, 1, 1, "You cannot stop us all!", 12, "Azure Stalker SAY_DEATH");

-- Portal Guardian SAI
SET @ENTRY := 30660;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,7000,6000,9000,11,58504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Guardian - In Combat - Cast 'Agonizing Strike'"),
(@ENTRY,0,1,0,0,0,100,0,7000,12000,9000,11000,11,58508,0,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Guardian - In Combat - Cast 'Side Swipe'"),
(@ENTRY,0,2,0,37,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Guardian - On Initialize - Say Line 0"),
(@ENTRY,0,3,0,4,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Guardian - On Aggro - Say Line 1"),
(@ENTRY,0,4,0,6,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Guardian - On Just Died - Say Line 2");

-- Portal Keeper SAI
SET @ENTRY := 30695;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,6000,6000,8000,11,58531,64,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Keeper - In Combat - Cast 'Arcane Missiles' (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,4,6000,8000,6000,8000,11,61593,64,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Keeper - In Combat - Cast 'Arcane Missiles' (Heroic Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,13000,19000,13000,19000,11,58532,0,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Keeper - In Combat - Cast 'Frostbolt Volley' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,13000,19000,13000,19000,11,61594,0,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Keeper - In Combat - Cast 'Frostbolt Volley' (Heroic Dungeon)"),
(@ENTRY,0,4,0,0,0,100,4,6000,9000,9000,14000,11,58534,0,0,0,0,0,2,0,0,0,0,0,0,0,"Portal Keeper - In Combat - Cast 'Deep Freeze' (Heroic Dungeon)"),
(@ENTRY,0,5,0,37,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Keeper - On Initialize - Say Line 0"),
(@ENTRY,0,6,0,4,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Keeper - On Aggro - Say Line 1"),
(@ENTRY,0,7,0,6,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Portal Keeper - On Just Died - Say Line 2");

DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_water_globule_summon";
INSERT INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES
(54258, "spell_water_globule_summon"),
(54264, "spell_water_globule_summon"),
(54265, "spell_water_globule_summon"),
(54266, "spell_water_globule_summon"),
(54267, "spell_water_globule_summon");

DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (30668, 30695, 29395, 29315, 29316, 30663, 29312, 29313, 29266, 29314);
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` IN (30668, 30695, 29395, 30663));
