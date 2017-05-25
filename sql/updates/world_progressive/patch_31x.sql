--
-- === Content 3.1.x (Ulduar, Basic AT) ===
--

SET @EmblemLowPREV  := 40752; # Emblem of Heroism
SET @EmblemLowCURR  := 40753; # Emblem of Valor

-- Update loot tables

UPDATE `creature_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;
UPDATE `gameobject_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;
UPDATE `item_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;
UPDATE `reference_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;
UPDATE `spell_loot_template` SET `item`=@EmblemLowCURR WHERE `item`=@EmblemLowPREV;

# Update quest emblems
UPDATE `quest_template` SET `RewardItemId1`=@EmblemLowCURR WHERE `RewardItemId1`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemId2`=@EmblemLowCURR WHERE `RewardItemId2`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemId3`=@EmblemLowCURR WHERE `RewardItemId3`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardItemId4`=@EmblemLowCURR WHERE `RewardItemId4`=@EmblemLowPREV;

UPDATE `quest_template` SET `RewardChoiceItemId1`=@EmblemLowCURR WHERE `RewardChoiceItemId1`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId2`=@EmblemLowCURR WHERE `RewardChoiceItemId2`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId3`=@EmblemLowCURR WHERE `RewardChoiceItemId3`=@EmblemLowPREV;
UPDATE `quest_template` SET `RewardChoiceItemId4`=@EmblemLowCURR WHERE `RewardChoiceItemId4`=@EmblemLowPREV;

# Remove disables for raids and instances for current content
DELETE FROM `disables` WHERE `sourceType` = 2 AND `entry` IN (603);
DELETE FROM `spell_area` WHERE `spell` = 61831; -- 3.1 phase

-- Conquest Vendors
DELETE FROM `creature` WHERE `creature`.`guid` = 85224;
DELETE FROM `creature` WHERE `creature`.`guid` = 86929;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
('85224', '33964', '571', '1', '1', '0', '0', '5762.13', '731.637', '653.748', '2.47837', '180', '0', '0', '10080', '8814', '0', '0', '0', '0'),
('86929', '33963', '571', '1', '1', '0', '0', '5931.55', '507.388', '650.263', '1.67552', '180', '0', '0', '10080', '8814', '0', '0', '0', '0');

-- Enable Emalon at VOA
DELETE FROM `creature` WHERE `creature`.`guid` = 202593; /* Emalon the Storm Watcher <VOA> */
INSERT INTO `creature` ( `guid` , `id` , `map` , `spawnMask` , `phaseMask` , `modelid` , `equipment_id` , `position_x` , `position_y` , `position_z` , `orientation` , `spawntimesecs` , `spawndist` , `currentwaypoint` , `curhealth` , `curmana` , `MovementType` , `npcflag` , `unit_flags` , `dynamicflags` )
VALUES (202593, 33993, 624, 3, 1, 0, 0, - 218.726, - 288.57, 91.5494, 1.58825, 604800, 0, 0, 1, 0, 0, 0, 0, 0);
-- # =============================================================================================
DELETE FROM `reference_loot_template` WHERE `reference_loot_template`.`entry` = 34215 AND `reference_loot_template`.`item` = 40811;

-- Conquests
-- Ulduar Hard Mode Reference
UPDATE `reference_loot_template` SET `item` = '45624' WHERE `reference_loot_template`.`entry` = 34350 AND `reference_loot_template`.`item` = 45087;

-- Flame Leviathan
DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 34003 AND `creature_loot_template`.`item` = 5;
DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 34003 AND `creature_loot_template`.`item` = 7;
UPDATE `creature_loot_template` SET `item` = '45624', `mincountOrRef` = '1' WHERE `creature_loot_template`.`entry` = 34003 AND `creature_loot_template`.`item` = 1;

-- Ignis
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` =33190 AND `creature_loot_template`.`item` =40753;

-- Razorscale
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` =33724 AND `creature_loot_template`.`item` =40753;

-- XT002
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 33885 AND `creature_loot_template`.`item` = 40753;

-- Kologarn
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` = 26929 AND `gameobject_loot_template`.`item` = 40753;

-- Hodir
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` = 26946 AND `gameobject_loot_template`.`item` = 40753;

-- Thorim
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` = 26955 AND `gameobject_loot_template`.`item` = 40753;

-- Freya
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` =26962 AND `gameobject_loot_template`.`item` =40753;
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` =26960 AND `gameobject_loot_template`.`item` =40753;
UPDATE `gameobject_loot_template` SET `item` = '45624', `mincountOrRef` = '4', `maxcount` = '4' WHERE `gameobject_loot_template`.`entry` = 27079 AND `gameobject_loot_template`.`item` =40753;
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` =27081 AND `gameobject_loot_template`.`item` =40753;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 27081 AND `gameobject_loot_template`.`item` = 6;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 27081 AND `gameobject_loot_template`.`item` = 3;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 26960 AND `gameobject_loot_template`.`item` = 6;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 26960 AND `gameobject_loot_template`.`item` = 5;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 26959 AND `gameobject_loot_template`.`item` = 3;
DELETE FROM `gameobject_loot_template` WHERE `gameobject_loot_template`.`entry` = 27080 AND `gameobject_loot_template`.`item` = 4;

DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 32913;
DELETE FROM `creature_loot_template` WHERE `creature_loot_template`.`entry` = 33391;

INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
('32913', '40753', '100', '1', '0', '1', '1'),
('33391', '45624', '100', '1', '0', '1', '1');

UPDATE `creature_template` SET `lootid` = '32913' WHERE `creature_template`.`entry` =32913;
UPDATE `creature_template` SET `lootid` = '32913' WHERE `creature_template`.`entry` =32914;
UPDATE `creature_template` SET `lootid` = '32913' WHERE `creature_template`.`entry` =32915;

UPDATE `creature_template` SET `lootid` = '33391' WHERE `creature_template`.`entry` =33391;
UPDATE `creature_template` SET `lootid` = '33391' WHERE `creature_template`.`entry` =33392;
UPDATE `creature_template` SET `lootid` = '33391' WHERE `creature_template`.`entry` =33393;


-- Mimiron
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` = 26967 AND `gameobject_loot_template`.`item` =40753;
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` = 26963 AND `gameobject_loot_template`.`item` =40753;

-- Vezax
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` =33449 AND `creature_loot_template`.`item` =40753;

-- Yogg
UPDATE `creature_loot_template` SET `item` = '45624', `mincountOrRef` = '1' WHERE `creature_loot_template`.`entry` = 33955 AND `creature_loot_template`.`item` = 5;

-- 
UPDATE `gameobject_loot_template` SET `item` = '45624' WHERE `gameobject_loot_template`.`entry` =26974 AND `gameobject_loot_template`.`item` =40753;
-- 
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 33994 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 33693 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 33694 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 33692 AND `creature_loot_template`.`item` = 40753;
UPDATE `creature_loot_template` SET `item` = '45624' WHERE `creature_loot_template`.`entry` = 34175 AND `creature_loot_template`.`item` = 40753;

--
-- Heroism emblems creatures
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 29932;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30397;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30398;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30510;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30529;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30530;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30532;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30540;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30748;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30774;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30788;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30807;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 30810;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31211;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31212;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31215;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31349;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31350;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31360;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31362;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31367;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31368;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31370;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31381;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31384;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31386;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31456;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31463;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31464;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31465;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31469;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31506;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31507;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31508;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31509;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31510;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31511;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31512;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31533;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31536;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31537;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31538;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31558;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31559;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31560;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31610;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31611;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31612;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31656;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31673;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31679;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 32313;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 35490;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36476;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36494;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36497;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36498;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36502;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36658;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 36938;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 37126;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 37613;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 37627;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 37677;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 38112;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 38113;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 38599;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 38603;
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15928;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15931;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15932;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15936;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15952;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15953;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15954;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15956;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15989;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 15990; 
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 16011;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 16028;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 16060;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 16061;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 28860;  
UPDATE `creature_loot_template` SET `item` = '40752' WHERE `creature_loot_template`.`item` = 40753 AND `creature_loot_template`.`entry` = 31125;     

--
-- Heroism emblems objects
UPDATE `gameobject_loot_template` SET `item` = '40752' WHERE  `gameobject_loot_template`.`item` = '40753' AND `gameobject_loot_template`.`entry` = 25192;
UPDATE `gameobject_loot_template` SET `item` = '40752' WHERE  `gameobject_loot_template`.`item` = '40753' AND `gameobject_loot_template`.`entry` = 24589;
UPDATE `gameobject_loot_template` SET `item` = '40752' WHERE  `gameobject_loot_template`.`item` = '40753' AND `gameobject_loot_template`.`entry` = 24524;
UPDATE `gameobject_loot_template` SET `item` = '40752' WHERE  `gameobject_loot_template`.`item` = '40753' AND `gameobject_loot_template`.`entry` = 26094;

-- 
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 40719;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 40720;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 40717;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 40718;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 45688;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 45689;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 45690;
DELETE FROM `npc_vendor` WHERE `npc_vendor`.`item` = 45691;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(31579, 0, 40717, 0, 0, 2534),
(31579, 0, 40718, 0, 0, 2534),
(31579, 0, 40719, 0, 0, 2534),
(31579, 0, 40720, 0, 0, 2534),
(31581, 0, 40717, 0, 0, 2534),
(31581, 0, 40718, 0, 0, 2534),
(31581, 0, 40719, 0, 0, 2534),
(31581, 0, 40720, 0, 0, 2534),
(32172, 0, 40717, 0, 0, 2534),
(32172, 0, 40718, 0, 0, 2534),
(32172, 0, 40719, 0, 0, 2534),
(32172, 0, 40720, 0, 0, 2534),
(32172, 0, 45688, 0, 0, 2592),
(32172, 0, 45689, 0, 0, 2593),
(32172, 0, 45690, 0, 0, 2594),
(32172, 0, 45691, 0, 0, 2595);

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32294;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(32294, 0, 41727, 0, 0, 2481),
(32294, 0, 41728, 0, 0, 2481),
(32294, 0, 41730, 0, 0, 2481),
(32294, 0, 41732, 0, 0, 2481),
(32294, 0, 41733, 0, 0, 2481),
(32294, 0, 41734, 0, 0, 2481),
(32294, 0, 41735, 0, 0, 2481),
(32294, 0, 41736, 0, 0, 2481),
(32294, 0, 41737, 0, 0, 2481),
(32294, 0, 41738, 0, 0, 2481),
(32294, 0, 41739, 0, 0, 2481),
(32294, 0, 41740, 0, 0, 2481),
(32294, 0, 41742, 0, 0, 2482),
(32294, 0, 41743, 0, 0, 2482),
(32294, 0, 41744, 0, 0, 2482),
(32294, 0, 43956, 0, 0, 2552),
(32294, 0, 44066, 0, 0, 2545),
(32294, 0, 44067, 0, 0, 2546),
(32294, 0, 44068, 0, 0, 2546),
(32294, 0, 44069, 0, 0, 2549),
(32294, 0, 44075, 0, 0, 2549),
(32294, 0, 44076, 0, 0, 2547),
(32294, 0, 44078, 0, 0, 2547),
(32294, 0, 44081, 0, 0, 2547),
(32294, 0, 44082, 0, 0, 2547),
(32294, 0, 44084, 0, 0, 2547),
(32294, 0, 44087, 0, 0, 2547),
(32294, 0, 44088, 0, 0, 2547),
(32294, 0, 44089, 0, 0, 2547),
(32294, 0, 44091, 0, 0, 2542),
(32294, 0, 44092, 0, 0, 2543),
(32294, 0, 44093, 0, 0, 2543),
(32294, 0, 44094, 0, 0, 2544),
(32294, 0, 44095, 0, 0, 2543),
(32294, 0, 44096, 0, 0, 2542),
(32294, 0, 44098, 0, 0, 2544),
(32294, 0, 44099, 0, 0, 2542),
(32294, 0, 44100, 0, 0, 2542),
(32294, 0, 44101, 0, 0, 2542),
(32294, 0, 44102, 0, 0, 2542),
(32294, 0, 44103, 0, 0, 2542),
(32294, 0, 44105, 0, 0, 2542),
(32294, 0, 44107, 0, 0, 2542),
(32294, 0, 44115, 0, 0, 2546),
(32294, 0, 44891, 0, 0, 2577),
(32294, 0, 44892, 0, 0, 2577),
(32294, 0, 44893, 0, 0, 2577),
(32294, 0, 44894, 0, 0, 2577),
(32294, 0, 44895, 0, 0, 2577),
(32294, 0, 44896, 0, 0, 2577),
(32294, 0, 44897, 0, 0, 2577),
(32294, 0, 44898, 0, 0, 2577),
(32294, 0, 44899, 0, 0, 2577),
(32294, 0, 44900, 0, 0, 2577),
(32294, 0, 44901, 0, 0, 2579),
(32294, 0, 44902, 0, 0, 2579),
(32294, 0, 44903, 0, 0, 2579),
(32294, 0, 44904, 0, 0, 2579),
(32294, 0, 44905, 0, 0, 2579),
(32294, 0, 44906, 0, 0, 2579),
(32294, 0, 44907, 0, 0, 2579),
(32294, 0, 44908, 0, 0, 2579),
(32294, 0, 44909, 0, 0, 2579),
(32294, 0, 44910, 0, 0, 2579),
(32294, 0, 44912, 0, 0, 2578),
(32294, 0, 44914, 0, 0, 2578),
(32294, 0, 46057, 0, 0, 2579),
(32294, 0, 46058, 0, 0, 2579),
(32294, 0, 46059, 0, 0, 2579),
(32294, 0, 46060, 0, 0, 2579),
(32294, 0, 46061, 0, 0, 2579),
(32294, 0, 46062, 0, 0, 2579),
(32294, 0, 46063, 0, 0, 2579),
(32294, 0, 46064, 0, 0, 2579),
(32294, 0, 46065, 0, 0, 2579),
(32294, 0, 46066, 0, 0, 2579),
(32294, 0, 46071, 0, 0, 2577),
(32294, 0, 46072, 0, 0, 2577),
(32294, 0, 46073, 0, 0, 2577),
(32294, 0, 46074, 0, 0, 2577),
(32294, 0, 46075, 0, 0, 2577),
(32294, 0, 46076, 0, 0, 2577),
(32294, 0, 46077, 0, 0, 2577),
(32294, 0, 46078, 0, 0, 2577),
(32294, 0, 46079, 0, 0, 2577),
(32294, 0, 46080, 0, 0, 2577),
(32294, 0, 46081, 0, 0, 2578),
(32294, 0, 46082, 0, 0, 2578),
(32294, 0, 46083, 0, 0, 2578),
(32294, 0, 46084, 0, 0, 2578),
(32294, 0, 46085, 0, 0, 2578),
(32294, 0, 46086, 0, 0, 2578),
(32294, 0, 46087, 0, 0, 2578),
(32294, 0, 46088, 0, 0, 2578);

DELETE FROM `npc_vendor` WHERE `npc_vendor`.`entry` = 32296;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(32296, 0, 41727, 0, 0, 2481),
(32296, 0, 41728, 0, 0, 2481),
(32296, 0, 41730, 0, 0, 2481),
(32296, 0, 41732, 0, 0, 2481),
(32296, 0, 41733, 0, 0, 2481),
(32296, 0, 41734, 0, 0, 2481),
(32296, 0, 41735, 0, 0, 2481),
(32296, 0, 41736, 0, 0, 2481),
(32296, 0, 41737, 0, 0, 2481),
(32296, 0, 41738, 0, 0, 2481),
(32296, 0, 41739, 0, 0, 2481),
(32296, 0, 41740, 0, 0, 2481),
(32296, 0, 41742, 0, 0, 2482),
(32296, 0, 41743, 0, 0, 2482),
(32296, 0, 41744, 0, 0, 2482),
(32296, 0, 44066, 0, 0, 2545),
(32296, 0, 44067, 0, 0, 2546),
(32296, 0, 44068, 0, 0, 2546),
(32296, 0, 44069, 0, 0, 2549),
(32296, 0, 44075, 0, 0, 2549),
(32296, 0, 44076, 0, 0, 2547),
(32296, 0, 44077, 0, 0, 2552),
(32296, 0, 44078, 0, 0, 2547),
(32296, 0, 44081, 0, 0, 2547),
(32296, 0, 44082, 0, 0, 2547),
(32296, 0, 44084, 0, 0, 2547),
(32296, 0, 44087, 0, 0, 2547),
(32296, 0, 44088, 0, 0, 2547),
(32296, 0, 44089, 0, 0, 2547),
(32296, 0, 44091, 0, 0, 2542),
(32296, 0, 44092, 0, 0, 2543),
(32296, 0, 44093, 0, 0, 2543),
(32296, 0, 44094, 0, 0, 2544),
(32296, 0, 44095, 0, 0, 2543),
(32296, 0, 44096, 0, 0, 2542),
(32296, 0, 44097, 0, 0, 2544),
(32296, 0, 44099, 0, 0, 2542),
(32296, 0, 44100, 0, 0, 2542),
(32296, 0, 44101, 0, 0, 2542),
(32296, 0, 44102, 0, 0, 2542),
(32296, 0, 44103, 0, 0, 2542),
(32296, 0, 44105, 0, 0, 2542),
(32296, 0, 44107, 0, 0, 2542),
(32296, 0, 44115, 0, 0, 2546),
(32296, 0, 44891, 0, 0, 2577),
(32296, 0, 44892, 0, 0, 2577),
(32296, 0, 44893, 0, 0, 2577),
(32296, 0, 44894, 0, 0, 2577),
(32296, 0, 44895, 0, 0, 2577),
(32296, 0, 44896, 0, 0, 2577),
(32296, 0, 44897, 0, 0, 2577),
(32296, 0, 44898, 0, 0, 2577),
(32296, 0, 44899, 0, 0, 2577),
(32296, 0, 44900, 0, 0, 2577),
(32296, 0, 44901, 0, 0, 2579),
(32296, 0, 44902, 0, 0, 2579),
(32296, 0, 44903, 0, 0, 2579),
(32296, 0, 44904, 0, 0, 2579),
(32296, 0, 44905, 0, 0, 2579),
(32296, 0, 44906, 0, 0, 2579),
(32296, 0, 44907, 0, 0, 2579),
(32296, 0, 44908, 0, 0, 2579),
(32296, 0, 44909, 0, 0, 2579),
(32296, 0, 44910, 0, 0, 2579),
(32296, 0, 44912, 0, 0, 2578),
(32296, 0, 44914, 0, 0, 2578),
(32296, 0, 46057, 0, 0, 2579),
(32296, 0, 46058, 0, 0, 2579),
(32296, 0, 46059, 0, 0, 2579),
(32296, 0, 46060, 0, 0, 2579),
(32296, 0, 46061, 0, 0, 2579),
(32296, 0, 46062, 0, 0, 2579),
(32296, 0, 46063, 0, 0, 2579),
(32296, 0, 46064, 0, 0, 2579),
(32296, 0, 46065, 0, 0, 2579),
(32296, 0, 46066, 0, 0, 2579),
(32296, 0, 46071, 0, 0, 2577),
(32296, 0, 46072, 0, 0, 2577),
(32296, 0, 46073, 0, 0, 2577),
(32296, 0, 46074, 0, 0, 2577),
(32296, 0, 46075, 0, 0, 2577),
(32296, 0, 46076, 0, 0, 2577),
(32296, 0, 46077, 0, 0, 2577),
(32296, 0, 46078, 0, 0, 2577),
(32296, 0, 46079, 0, 0, 2577),
(32296, 0, 46080, 0, 0, 2577),
(32296, 0, 46081, 0, 0, 2578),
(32296, 0, 46082, 0, 0, 2578),
(32296, 0, 46083, 0, 0, 2578),
(32296, 0, 46084, 0, 0, 2578),
(32296, 0, 46085, 0, 0, 2578),
(32296, 0, 46086, 0, 0, 2578),
(32296, 0, 46087, 0, 0, 2578),
(32296, 0, 46088, 0, 0, 2578);

UPDATE `npc_vendor` SET `item` = '42122' WHERE `npc_vendor`.`entry` = 34036 AND `npc_vendor`.`item` = 42123 AND `npc_vendor`.`ExtendedCost` = 2605;