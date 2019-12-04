UPDATE `creature_template` SET `dmg_multiplier` = '85', `Health_mod` = '1799' WHERE `creature_template`.`entry` = 29324;
UPDATE `creature_template` SET `dmg_multiplier` = '110', `Health_mod` = '1370' WHERE `creature_template`.`entry` = 29373;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '45' WHERE `creature_template`.`entry` = 29388;
UPDATE `creature_template` SET `dmg_multiplier` = '70', `Health_mod` = '1210' WHERE `creature_template`.`entry` = 29417;
UPDATE `creature_template` SET `dmg_multiplier` = '110', `Health_mod` = '3631' WHERE `creature_template`.`entry` = 29448;
UPDATE `creature_template` SET `Health_mod` = '275' WHERE `creature_template`.`entry` = 29446;
UPDATE `creature_template` SET `Health_mod` = '275' WHERE `creature_template`.`entry` = 29447;
UPDATE `creature_template` SET `Health_mod` = '1066' WHERE `creature_template`.`entry` =29249;
UPDATE `creature_template` SET `Health_mod` = '80', `dmg_multiplier` = '26' WHERE `creature_template`.`entry` =29256;
UPDATE `creature_template` SET `Health_mod` = '1235' WHERE `creature_template`.`entry` =29268;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '40' WHERE `creature_template`.`entry` =29274;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '80' WHERE `creature_template`.`entry` =29273;
UPDATE `creature_template` SET `Health_mod` = '1250' WHERE `creature_template`.`entry` = 29278;
UPDATE `creature_template` SET `Health_mod` = '3.2' WHERE `creature_template`.`entry` =30183;
UPDATE `creature_template` SET `Health_mod` = '1185' WHERE `creature_template`.`entry` =29615;
UPDATE `creature_template` SET `Health_mod` = '1100' WHERE `creature_template`.`entry` =29701;
UPDATE `creature_template` SET `Health_mod` = '320' WHERE `creature_template`.`entry` =29955;


UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '12' WHERE `creature_template`.`entry` =29990;
UPDATE `creature_template` SET `dmg_multiplier` = '8', `Health_mod` = '4' WHERE `creature_template`.`entry` = 29987;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '13' WHERE `creature_template`.`entry` =29985;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '20' WHERE `creature_template`.`entry` =29986;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '20' WHERE `creature_template`.`entry` =29988;
UPDATE `creature_template` SET `Health_mod` = '6' WHERE `creature_template`.`entry` =29989;
UPDATE `creature_template` SET `Health_mod` = '4' WHERE `creature_template`.`entry` =30264;

UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '24' WHERE `creature_template`.`entry` =29632;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '24' WHERE `creature_template`.`entry` =29633;
UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '24' WHERE `creature_template`.`entry` =29634;
UPDATE `creature_template` SET `dmg_multiplier` = '43', `Health_mod` = '2475' WHERE `creature_template`.`entry` =29718;

UPDATE `creature_template` SET `dmg_multiplier` = '26', `Health_mod` = '45' WHERE `creature_template`.`entry` =29941;
UPDATE `creature_template` SET `dmg_multiplier` = '210',`Health_mod` = '1080' WHERE `creature_template`.`entry` =29940;

/* FOUR HORSEMEN */
SET @ZELIK:= 30602;
SET @BARON:= 30600;
SET @THANE:= 30603;
SET @LADY:= 30601;

SET @BASE_HEALTH_MOD:= 340;

UPDATE `creature_template` SET `Health_mod` = @BASE_HEALTH_MOD + (@BASE_HEALTH_MOD * 0.1) WHERE `entry` IN (@ZELIK, @BARON, @THANE, @LADY);

/* KEL THUZAD */
SET @SOUL_WEAVER_25_BASE_HP_MODIFIER:= 12;
SET @SOUL_WEAVER_25_ENTRY:= 30018;

UPDATE `creature_template` SET `Health_mod` = (@SOUL_WEAVER_25_BASE_HP_MODIFIER * 3), `dmg_multiplier` = 39 WHERE `entry` = @SOUL_WEAVER_25_ENTRY;

SET @UNSTOPPABLE_ABOM_25_BASE_HP_MODIFIER:= 16.5;
SET @ABOM_25_ENTRY:= 30048;

UPDATE `creature_template` SET `Health_mod` = (@UNSTOPPABLE_ABOM_25_BASE_HP_MODIFIER * 3), `dmg_multiplier` = 69 WHERE `entry` = @ABOM_25_ENTRY;

SET @SOLDIER_FROZEN_WASTE_BASE_HP_MODIFIER:= 0.349206;
SET @SOLDIER_FROZEN_25_ENTRY:= 30015;

UPDATE `creature_template` SET `Health_mod` = (@SOLDIER_FROZEN_WASTE_BASE_HP_MODIFIER * 3), `dmg_multiplier` = 39 WHERE `entry` = @SOLDIER_FROZEN_25_ENTRY;

UPDATE `smart_scripts` SET `event_param3` = '5000', `event_param4` = '5000' WHERE `smart_scripts`.`entryorguid` = 16505 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =0 AND `smart_scripts`.`link` =0;
UPDATE `smart_scripts` SET `event_phase_mask` = '0', `action_param2` = '4' WHERE `smart_scripts`.`entryorguid` =16573 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =3 AND `smart_scripts`.`link` =0;

UPDATE `creature_template` SET `dmg_multiplier` = '110', `Health_mod` = '2374' WHERE `creature_template`.`entry` =29991;
UPDATE `creature_template` SET `Health_mod` = '2818' WHERE `creature_template`.`entry` =30061;

UPDATE `creature_template` SET `dmg_multiplier` = '23' WHERE `creature_template`.`entry` =30048;
UPDATE `creature_template` SET `dmg_multiplier` = '1', `mindmg` = 145000, `maxdmg` = 150000, `speed_walk` = 0.65, `speed_run` = 0.65  WHERE `creature_template`.`entry` =30057;


/* NAXXRAMAS ORB */
DELETE FROM `areatrigger_teleport` WHERE `areatrigger_teleport`.`id` = 4156;

UPDATE `gameobject` SET  `phaseMask` = '1', `position_x` = '3005.51', `position_y` = '-3434.63', `position_z` = '304.195', `orientation` = '5.810410' WHERE `gameobject`.`guid` = 5216;

UPDATE `gameobject_template` SET `data3` = '0', `data10` = '72617' WHERE `gameobject_template`.`entry` = 202277;
UPDATE `gameobject_template` SET `data3` = '0', `data10` = '72613' WHERE `gameobject_template`.`entry` = 202278;

DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 65853; /* Delete portal from 3.3.0 */

/* MALYGOS */
SET @MALYGOS_BASE_HP_MODIFIER:= 1400;
SET @MALYGOS_25_ENTRY:= 31734;
SET @MALYGOS_BASE_HP_MODIFIER_10:= 500;
SET @MALYGOS_10_ENTRY:= 28859;

UPDATE `creature_template` SET `Health_mod` = 2387 WHERE `entry` = @MALYGOS_25_ENTRY;
UPDATE `creature_template` SET `Health_mod` = @MALYGOS_BASE_HP_MODIFIER_10 + (@MALYGOS_BASE_HP_MODIFIER_10 * 0.45) WHERE `entry` = @MALYGOS_10_ENTRY;

SET @NEXUS_LORD_HP_BASE_MODIFIER:= 45;
SET @NEXUS_LORD_25_ENTRY:= 31750;
SET @NEXUS_LORD_10_ENTRY:= 30245;

SET @NEXUS_LORD_BASE_DMG_10:= 17;
SET @NEXUS_LORD_BASE_DMG_25:= 35;

UPDATE `creature_template` SET `Health_mod` = @NEXUS_LORD_HP_BASE_MODIFIER + (@NEXUS_LORD_HP_BASE_MODIFIER * 0.5), `dmg_multiplier` = @NEXUS_LORD_BASE_DMG_25 * 2.5 WHERE `entry` = @NEXUS_LORD_25_ENTRY;
UPDATE `creature_template` SET `dmg_multiplier` = @NEXUS_LORD_BASE_DMG_10 * 2 WHERE `entry` = @NEXUS_LORD_10_ENTRY;

SET @SCION_OF_ETERNITY_HP_BASE_MODIFIER:= 30;
SET @SCION_OF_ETERNITY_25_ENTRY:= 31751;

UPDATE `creature_template` SET `Health_mod` = @SCION_OF_ETERNITY_HP_BASE_MODIFIER + (@SCION_OF_ETERNITY_HP_BASE_MODIFIER * 0.6) WHERE `entry` = @SCION_OF_ETERNITY_25_ENTRY;

SET @POWER_SPARK_25_BASE_HP:= 3;
SET @POWER_SPARK_10_BASE_HP:= 1;

SET @POWER_SPARK_25:= 32187;
SET @POWER_SPARK_10:= 30084;

UPDATE `creature_template` SET `health_mod` = @POWER_SPARK_10_BASE_HP * 2 WHERE `entry` = @POWER_SPARK_10;
UPDATE `creature_template` SET `health_mod` = @POWER_SPARK_25_BASE_HP * 4 WHERE `entry` = @POWER_SPARK_25;

SET @MALYGOS_10_BASE_DMG_MULTIPLIER:= 25;
SET @MALYGOS_25_BASE_DMG_MULTIPLIER:= 50;

UPDATE `creature_template` SET `dmg_multiplier` = @MALYGOS_10_BASE_DMG_MULTIPLIER + 35 WHERE `entry` = @MALYGOS_10_ENTRY;
UPDATE `creature_template` SET `dmg_multiplier` = @MALYGOS_25_BASE_DMG_MULTIPLIER + 20 WHERE `entry` = @MALYGOS_25_ENTRY;

DELETE FROM `conditions` WHERE `sourceEntry` = 64381;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 64381, 0, 0, 31, 0, 3, 34014, 0, 0, 0, 0, '', ''),
(13, 1, 64381, 0, 1, 31, 0, 3, 30245, 0, 0, 0, 0, '', '');

