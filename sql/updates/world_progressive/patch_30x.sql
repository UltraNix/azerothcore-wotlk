--
-- === Content 3.0.x (Naxx, OS, EoE) ===
--
 
SET @EmblemHighPREV := 49426; -- Emblem of Frost
SET @EmblemLowPREV  := 47241; -- Emblem of Triumph

SET @EmblemHighCURR := 40753; -- Emblem of Valor
SET @EmblemLowCURR  := 40752; -- Emblem of Heroism

-- Update loot tables
UPDATE `creature_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV;
UPDATE `creature_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

UPDATE `gameobject_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV;
UPDATE `gameobject_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

UPDATE `item_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV;
UPDATE `item_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

UPDATE `reference_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV;
UPDATE `reference_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

UPDATE `spell_loot_template` SET `item`=@EmblemHighCURR WHERE `item`=@EmblemHighPREV;
UPDATE `spell_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

-- Update quest emblems

UPDATE `quest_template` SET `RewardItemID1`=@EmblemHighCURR WHERE `RewardItemID1`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardItemID2`=@EmblemHighCURR WHERE `RewardItemID2`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardItemID3`=@EmblemHighCURR WHERE `RewardItemID3`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardItemID4`=@EmblemHighCURR WHERE `RewardItemID4`=@EmblemHighPREV;

UPDATE `quest_template` SET `RewardItemID1`=@EmblemLowCURR WHERE `RewardItemID1`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemID2`=@EmblemLowCURR WHERE `RewardItemID2`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemID3`=@EmblemLowCURR WHERE `RewardItemID3`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemID4`=@EmblemLowCURR WHERE `RewardItemID4`=@EmblemLowPREV;

UPDATE `quest_template` SET `RewardChoiceItemId1`=@EmblemHighCURR WHERE `RewardChoiceItemId1`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardChoiceItemId2`=@EmblemHighCURR WHERE `RewardChoiceItemId2`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardChoiceItemId3`=@EmblemHighCURR WHERE `RewardChoiceItemId3`=@EmblemHighPREV;
UPDATE `quest_template` SET `RewardChoiceItemId4`=@EmblemHighCURR WHERE `RewardChoiceItemId4`=@EmblemHighPREV;

UPDATE `quest_template` SET `RewardChoiceItemId1`=@EmblemLowCURR WHERE `RewardChoiceItemId1`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId2`=@EmblemLowCURR WHERE `RewardChoiceItemId2`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId3`=@EmblemLowCURR WHERE `RewardChoiceItemId3`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId4`=@EmblemLowCURR WHERE `RewardChoiceItemId4`=@EmblemLowPREV;

-- Remove disables for raids and instances for current content
DELETE FROM `disables` WHERE `sourceType` = 2 AND `entry` IN (533, 574, 575, 576, 578, 595, 599, 600, 601, 602, 604, 607, 608, 609, 615, 616, 617, 618, 619, 624, 628);
-- Add disables for raids and instances for future content
REPLACE INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES 
(2, 616, 15, '', '', 'Disable raid with hc "Eye of Eternity" - patch 3.3.5 content'),
(2, 650, 3, '', '', 'Disable dungeon "Trial of the Champion" - patch 3.2.x content'),
(2, 632, 3, '', '', 'Disable dungeon "The Forge of Souls" - patch 3.3.x content'),
(2, 658, 3, '', '', 'Disable dungeon "Pit of Saron" - patch 3.3.x content'),
(2, 668, 3, '', '', 'Disable dungeon "Halls of Reflection" - patch 3.3.x content'),
(2, 603, 3, '', '', 'Disable raid non-hc "Ulduar" - patch 3.1.x content'),
(2, 249, 3, '', '', 'Disable raid non-hc "Onyxia''s Lair" - patch 3.2.x content'),
(2, 649, 15, '', '', 'Disable raid with hc "Trial of the Crusader" - patch 3.2.x content'),
(2, 631, 15, '', '', 'Disable raid with hc "Icecrown Citadel" - patch 3.3.x content'),
(2, 724, 15, '', '', 'Disable raid with hc "Ruby Sanctum" - patch 3.3.5 content');

-- Proof of demise
DELETE FROM `creature_queststarter` WHERE `quest` > 20000 AND `id` = 20735;
REPLACE INTO `creature_queststarter` (`quest`, `id`) VALUES
(13245, 20735),
(13246, 20735),
(13247, 20735),
(13248, 20735),
(13249, 20735),
(13250, 20735),
(13251, 20735),
(13252, 20735),
(13253, 20735),
(13254, 20735),
(13255, 20735),
(13256, 20735);

REPLACE INTO `creature_questender` (`quest`, `id`) VALUES
(13245, 20735),
(13246, 20735),
(13247, 20735),
(13248, 20735),
(13249, 20735),
(13250, 20735),
(13251, 20735),
(13252, 20735),
(13253, 20735),
(13254, 20735),
(13255, 20735),
(13256, 20735);

REPLACE INTO `pool_template` (`entry`, `max_limit`, `description`) VALUES (60004, 1, 'Proof of demise: ... - Dalaran dungeon daily quests');
REPLACE INTO `pool_quest` VALUES 
(13245, 60004, 'Proof of Demise: Ingvar the Plunderer'),
(13246, 60004, 'Proof of Demise: Keristrasza'),
(13247, 60004, 'Proof of Demise: Ley-Guardian Eregos'),
(13248, 60004, 'Proof of Demise: King Ymiron'),
(13249, 60004, 'Proof of Demise: The Prophet Tharon''ja'),
(13250, 60004, 'Proof of Demise: Gal''darah'),
(13251, 60004, 'Proof of Demise: Mal''Ganis'),
(13252, 60004, 'Proof of Demise: Sjonnir The Ironshaper'),
(13253, 60004, 'Proof of Demise: Loken'),
(13254, 60004, 'Proof of Demise: Anub''arak'),
(13255, 60004, 'Proof of Demise: Herald Volazj'),
(13256, 60004, 'Proof of Demise: Cyanigosa');

-- Timear forces
REPLACE INTO `creature_queststarter` (`quest`, `id`) VALUES
(13240, 31439),
(13241, 31439),
(13243, 31439),
(13244, 31439);

REPLACE INTO `creature_questender` (`quest`, `id`) VALUES
(13240, 31439),
(13241, 31439),
(13243, 31439),
(13244, 31439);

REPLACE INTO `pool_template` (`entry`, `max_limit`, `description`) VALUES (60005, 1, 'Timear forces: ... - Dalaran dungeon daily quests');
REPLACE INTO `pool_quest` VALUES 
(13240, 60005, 'Timear Foresees Centrifuge Constructs in your Future!'),
(13241, 60005, 'Timear Foresees Ymirjar Berserkers in your Future!'),
(13243, 60005, 'Timear Foresees Infinite Agents in your Future!'),
(13244, 60005, 'Timear Foresees Titanium Vanguards in your Future!');

UPDATE `creature_template` SET `ScriptName`='npc_archmage_timear' WHERE `entry`=31439;

-- AT phasing for objects

DELETE FROM `spell_area` WHERE `spell` = 61831; -- 3.1 phase
REPLACE INTO `spell_area` (`spell`, `area`, `autocast`) VALUES 
(61831, 4670, 1),
(61831, 4671, 1),
(61831, 4673, 1),
(61831, 4669, 1),
(61831, 4672, 1),
(61831, 4658, 1),
(61831, 4666, 1),
(61831, 4667, 1),
(61831, 4674, 1),
(61831, 4676, 1),
(61831, 4677, 1);

-- Call to Arms quests

DELETE FROM `disables` WHERE `entry` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
DELETE FROM `game_event_seasonal_questrelation` WHERE `questId` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
DELETE FROM `game_event_creature_quest` WHERE `quest` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
DELETE FROM `creature_queststarter` WHERE `quest` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
DELETE FROM `creature_questender` WHERE `quest` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 12 AND `SourceEntry` IN (11335,11336,11337,11338,11339,11340,11341,11342,13405,13407,14163,14164);
-- Alliance
-- Call to Arms: WSG - Event 19
INSERT INTO `creature_queststarter` VALUES (15351, 11338);
INSERT INTO `creature_questender`   VALUES (15351, 11338);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11338, 19);
INSERT INTO `conditions` VALUES (19, 0, 11338, 0, 0, 12, 0, 19, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: WSG');
-- Call to Arms: AB - Event 20
INSERT INTO `creature_queststarter` VALUES (15351, 11335);
INSERT INTO `creature_questender`   VALUES (15351, 11335);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11335, 20);
INSERT INTO `conditions` VALUES (19, 0, 11335, 0, 0, 12, 0, 20, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: AB');
-- Call to Arms: AV - Event 18
INSERT INTO `creature_queststarter` VALUES (15351, 11336);
INSERT INTO `creature_questender`   VALUES (15351, 11336);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11336, 18);
INSERT INTO `conditions` VALUES (19, 0, 11336, 0, 0, 12, 0, 18, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: AV');
-- Call to Arms: EotS - Event 21
INSERT INTO `creature_queststarter` VALUES (15351, 11337);
INSERT INTO `creature_questender`   VALUES (15351, 11337);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11337, 21);
INSERT INTO `conditions` VALUES (19, 0, 11337, 0, 0, 12, 0, 21, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: EotS');
-- Call to Arms: SotA - Event 53
INSERT INTO `creature_queststarter` VALUES (15351, 13405);
INSERT INTO `creature_questender`   VALUES (15351, 13405);
INSERT INTO `game_event_seasonal_questrelation` VALUES (13405, 53);
INSERT INTO `conditions` VALUES (19, 0, 13405, 0, 0, 12, 0, 53, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: SotA');
-- Call to Arms: IoC - Event 54
INSERT INTO `creature_queststarter` VALUES (15351, 14163);
INSERT INTO `creature_questender`   VALUES (15351, 14163);
INSERT INTO `game_event_seasonal_questrelation` VALUES (14163, 54);
INSERT INTO `conditions` VALUES (19, 0, 14163, 0, 0, 12, 0, 54, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: IoC');
-- Horde
-- Call to Arms: WSG - Event 19
INSERT INTO `creature_queststarter` VALUES (15350, 11342);
INSERT INTO `creature_questender`   VALUES (15350, 11342);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11342, 19);
INSERT INTO `conditions` VALUES (19, 0, 11342, 0, 0, 12, 0, 19, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: WSG');
-- Call to Arms: AB - Event 20
INSERT INTO `creature_queststarter` VALUES (15350, 11339);
INSERT INTO `creature_questender`   VALUES (15350, 11339);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11339, 20);
INSERT INTO `conditions` VALUES (19, 0, 11339, 0, 0, 12, 0, 20, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: AB');
-- Call to Arms: AV - Event 18
INSERT INTO `creature_queststarter` VALUES (15350, 11340);
INSERT INTO `creature_questender`   VALUES (15350, 11340);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11340, 18);
INSERT INTO `conditions` VALUES (19, 0, 11340, 0, 0, 12, 0, 18, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: AV');
-- Call to Arms: EotS - Event 21
INSERT INTO `creature_queststarter` VALUES (15350, 11341);
INSERT INTO `creature_questender`   VALUES (15350, 11341);
INSERT INTO `game_event_seasonal_questrelation` VALUES (11341, 21);
INSERT INTO `conditions` VALUES (19, 0, 11341, 0, 0, 12, 0, 21, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: EotS');
-- Call to Arms: SotA - Event 53
INSERT INTO `creature_queststarter` VALUES (15350, 13407);
INSERT INTO `creature_questender`   VALUES (15350, 13407);
INSERT INTO `game_event_seasonal_questrelation` VALUES (13407, 53);
INSERT INTO `conditions` VALUES (19, 0, 13407, 0, 0, 12, 0, 53, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: SotA');
-- Call to Arms: IoC - Event 54
INSERT INTO `creature_queststarter` VALUES (15350, 14164);
INSERT INTO `creature_questender`   VALUES (15350, 14164);
INSERT INTO `game_event_seasonal_questrelation` VALUES (14164, 54);
INSERT INTO `conditions` VALUES (19, 0, 14164, 0, 0, 12, 0, 54, 0, 0, 0, 0, 0, '', 'Quest avialable only during Call to Arms: IoC');

-- =============================================================================================

/* WG VENDORS ITEMS */

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 39173;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 39172;

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48974;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48975;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48976;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48999;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 49000;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48977;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48978;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48988;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48983;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48991;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48997;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48979;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48998;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48987;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48994;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48980;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48981;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48982;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48990;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48992;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 48993;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46086;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46087;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46088;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46076;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46077;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46078;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46058;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46059;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46057;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46079;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46080;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46071;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46072;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46064;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46063;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46062;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46061;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46065;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46066;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46083;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46085;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46081;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46084;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46082;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46073;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46074;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46075;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 46060;

/* JC GEMS */

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36919; /* Cardinal Ruby */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36925; /* Majestic Zircon  */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36922; /* King's Amber */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36928; /* Dreadstone */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36934; /* Eye of Zul */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 36931; /* Ametrine */

/* TAILORING ORB */

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 45087; /* Runed Orb */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 47556; /* Crusader Orb	 */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 54798; /* Flying Carpet */

DELETE FROM `creature` WHERE `creature`.`id` = 35495;
DELETE FROM `creature` WHERE `creature`.`id` = 37941;
DELETE FROM `creature` WHERE `creature`.`id` = 33963;
DELETE FROM `creature` WHERE `creature`.`id` = 33964;
DELETE FROM `creature` WHERE `creature`.`id` = 37942;
DELETE FROM `creature` WHERE `creature`.`id` = 35494;

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 40717 AND `npc_vendor`.`ExtendedCost` = 2534;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 40718 AND `npc_vendor`.`ExtendedCost` = 2534;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 40719 AND `npc_vendor`.`ExtendedCost` = 2534;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 40720 AND `npc_vendor`.`ExtendedCost` = 2534;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45688 AND `npc_vendor`.`ExtendedCost` = 2592;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45689 AND `npc_vendor`.`ExtendedCost` = 2593;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45690 AND `npc_vendor`.`ExtendedCost` = 2594;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45691 AND `npc_vendor`.`ExtendedCost` = 2595;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45819 AND `npc_vendor`.`ExtendedCost` = 2606;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45820 AND `npc_vendor`.`ExtendedCost` = 2606;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45821 AND `npc_vendor`.`ExtendedCost` = 2606;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45822 AND `npc_vendor`.`ExtendedCost` = 2606;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 45823 AND `npc_vendor`.`ExtendedCost` = 2606;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 47729 AND `npc_vendor`.`ExtendedCost` = 2685;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 47730 AND `npc_vendor`.`ExtendedCost` = 2685;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 47731 AND `npc_vendor`.`ExtendedCost` = 2685;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 47732 AND `npc_vendor`.`ExtendedCost` = 2685;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 47733 AND `npc_vendor`.`ExtendedCost` = 2685;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 48954 AND `npc_vendor`.`ExtendedCost` = 2702;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 48955 AND `npc_vendor`.`ExtendedCost` = 2703;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 48956 AND `npc_vendor`.`ExtendedCost` = 2704;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 48957 AND `npc_vendor`.`ExtendedCost` = 2705;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 51557 AND `npc_vendor`.`ExtendedCost` = 2735;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 51558 AND `npc_vendor`.`ExtendedCost` = 2737;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 51559 AND `npc_vendor`.`ExtendedCost` = 2736;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32172 AND `npc_vendor`.`item` = 51560 AND `npc_vendor`.`ExtendedCost` = 2738;

/* DELETE RECIPES AT JC TRAINER TIMOTHY JONES */
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46897 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46898 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46899 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46900 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46901 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46902 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46903 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46904 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46905 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46906 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46907 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46908 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46909 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46910 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46911 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46912 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46913 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46914 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46915 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46916 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46917 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46918 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46919 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46920 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46921 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46922 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46923 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46924 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46925 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46926 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46927 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46928 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46929 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46930 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46931 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46932 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46933 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46934 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46935 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46936 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46937 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46938 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46939 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46940 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46941 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46942 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46943 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46944 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46945 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46946 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46947 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46948 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46949 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46950 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46951 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46952 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46953 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 46956 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47007 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47008 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47010 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47011 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47012 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47015 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47016 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47017 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47018 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47019 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47020 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47021 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47022 AND `npc_vendor`.`ExtendedCost` = 2436;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 28701 AND `npc_vendor`.`item` = 47023 AND `npc_vendor`.`ExtendedCost` = 2436;

/* PROSPECTING JC GEMS */
DELETE FROM `prospecting_loot_template` WHERE `prospecting_loot_template`.`entry` = 36910;
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 13005;

/* ICY PRISM EPIC GEMS */
DELETE FROM `item_loot_template` WHERE `item_loot_template`.`entry` = 44943 AND `item_loot_template`.`item` = 1;
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 10008;

/* FISHING GEMS */
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 10019;
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 10013;


DELETE FROM `item_loot_template` WHERE `item_loot_template`.`mincountOrRef` = -10013;
DELETE FROM `item_loot_template` WHERE `item_loot_template`.`mincountOrRef` = -10019;

DELETE FROM `creature` WHERE `creature`.`id` = 33993; /* Koralon the Flame Watcher <VOA> */
DELETE FROM `creature` WHERE `creature`.`id` = 35013; /* Emalon the Storm Watcher <VOA> */
DELETE FROM `creature` WHERE `creature`.`id` = 38433; /* Toravon the Ice Watcher <VOA> */

/* NAXXRAMAS EMBLEMS */
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15956 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29249 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15953 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29268 AND `creature_loot_template`.`item` = 40752;  
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15952 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29278 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15954 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29615 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15936 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29701 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 16011 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29718 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 16061 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29940 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 16060 AND `creature_loot_template`.`item` = 40752; 
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29955 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 16028 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29324 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15931 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29373 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15932 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29417 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15928 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29448 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15989 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29991 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 15990 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 30061 AND `creature_loot_template`.`item` = 40752;

UPDATE `gameobject_loot_template` SET `item` = '40753' WHERE `gameobject_loot_template`.`entry` = 25192 AND `gameobject_loot_template`.`item` = 40752;
UPDATE `gameobject_loot_template` SET `item` = '40753' WHERE `gameobject_loot_template`.`entry` = 25193 AND `gameobject_loot_template`.`item` = 40752;

/* OS EMBLEMS */
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 31311 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 31535 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 31520 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 31534 AND `creature_loot_template`.`item` = 40752;

UPDATE `item_loot_template` SET `item` = '40753' WHERE `item_loot_template`.`entry` = 43346 AND `item_loot_template`.`item` = 40752;
UPDATE `reference_loot_template` SET `item` = '40753' WHERE `reference_loot_template`.`entry` = 34349 AND `reference_loot_template`.`item` = 40752;

/* VOA EMBLEMS */
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` =31722 AND `creature_loot_template`.`item` =40752;

/* NAXXRAMAS EMBLEMS NEW VALUES */
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15956 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15953 AND `creature_loot_template`.`item` = 40753;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15952 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15954 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15936 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 16011 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 16061 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 16060 AND `creature_loot_template`.`item` = 40753; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 16028 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15931 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15932 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15928 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15989 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`entry` = 15990 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29249 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29268 AND `creature_loot_template`.`item` = 40752;  
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29278 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29615 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29701 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29718 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29940 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29955 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29324 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29373 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29417 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29448 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 29991 AND `creature_loot_template`.`item` = 40752;
UPDATE `creature_loot_template` SET `item` = '40753' WHERE `creature_loot_template`.`entry` = 30061 AND `creature_loot_template`.`item` = 40752;

UPDATE `gameobject_loot_template` SET `item` = '40752' WHERE `gameobject_loot_template`.`entry` = 25192 AND `gameobject_loot_template`.`item` = 40753;