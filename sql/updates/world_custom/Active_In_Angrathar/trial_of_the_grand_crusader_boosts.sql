UPDATE `creature_template` SET `health_mod` = 12.05 WHERE `entry` = 34800;
UPDATE `creature_template` SET `health_mod` = 40 WHERE `entry` = 35441;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (65950, 67296, 67297, 67298, 66001, 67281, 67282, 67283);
INSERT INTO `spell_script_names` VALUES
(65950, "spell_valkyr_touch"),
(67296, "spell_valkyr_touch"),
(67297, "spell_valkyr_touch"),
(67298, "spell_valkyr_touch"),
(66001, "spell_valkyr_touch"),
(67281, "spell_valkyr_touch"),
(67282, "spell_valkyr_touch"),
(67283, "spell_valkyr_touch");

SET @GORMOK_BASE_HEALTH:= 850;
UPDATE `creature_template` SET `health_mod` = @GORMOK_BASE_HEALTH + (@GORMOK_BASE_HEALTH * 0.25) WHERE `entry` = 35440;

SET @VASSAL_BASE_HEALTH:= 60;
UPDATE `creature_template` SET `health_mod` = @VASSAL_BASE_HEALTH + (@VASSAL_BASE_HEALTH * 0.25) WHERE `entry` = 35443;

SET @ACIDMAW_BASE_HEALTH:= 480;
UPDATE `creature_template` SET `health_mod` = @ACIDMAW_BASE_HEALTH + (@ACIDMAW_BASE_HEALTH * 0.25) WHERE `entry` = 35513;

SET @DREADSCALE_BASE_HEALTH:= 480;
UPDATE `creature_template` SET `health_mod` = @DREADSCALE_BASE_HEALTH + (@DREADSCALE_BASE_HEALTH * 0.25) WHERE `entry` = 35516;

SET @ICEHOWL_BASE_HEALTH:= 1300;
UPDATE `creature_template` SET `health_mod` = @ICEHOWL_BASE_HEALTH + (@ICEHOWL_BASE_HEALTH * 0.25) WHERE `entry` = 35449;

SET @JARAXXUS_BASE_HEALTH:= 1900;
UPDATE `creature_template` SET `health_mod` = @JARAXXUS_BASE_HEALTH + (@JARAXXUS_BASE_HEALTH * 0.25) WHERE `entry` = 35269;

SET @MISTRESS_BASE_HEALTH:= 70;
UPDATE `creature_template` SET `health_mod` = @MISTRESS_BASE_HEALTH + (@MISTRESS_BASE_HEALTH * 0.25) WHERE `entry` = 35272;

SET @INFERNAL_BASE_HEALTH:= 23;
UPDATE `creature_template` SET `health_mod` = @INFERNAL_BASE_HEALTH + (@INFERNAL_BASE_HEALTH * 0.20) WHERE `entry` = 35264;

SET @NETHER_PORTAL_BASE_HEALTH:= 64;
UPDATE `creature_template` SET `health_mod` = @NETHER_PORTAL_BASE_HEALTH + (@NETHER_PORTAL_BASE_HEALTH * 0.25) WHERE `entry` = 35280;

SET @INFERNAL_VOLCANO_BASE_HEALTH:= 64;
UPDATE `creature_template` SET `health_mod` = @INFERNAL_VOLCANO_BASE_HEALTH + (@INFERNAL_VOLCANO_BASE_HEALTH * 0.25) WHERE `entry` = 35267;

SET @FJOLA_BASE_HEALTH:= 2800;
UPDATE `creature_template` SET `health_mod` = @FJOLA_BASE_HEALTH + (@FJOLA_BASE_HEALTH * 0.35) WHERE `entry` = 35352;

SET @DARK_BASE_HEALTH:= 2800;
UPDATE `creature_template` SET `health_mod` = @DARK_BASE_HEALTH + (@DARK_BASE_HEALTH * 0.35) WHERE `entry` = 35349;

SET @SCARAB_BASE_HEALTH:= 11.7;
UPDATE `creature_template` SET `health_mod` = @SCARAB_BASE_HEALTH + (@SCARAB_BASE_HEALTH * 0.35) WHERE `entry` = 35659;

SET @NERRUBIAN_BASE_HEALTH:= 54;
UPDATE `creature_template` SET `health_mod` = @NERRUBIAN_BASE_HEALTH + (@NERRUBIAN_BASE_HEALTH * 0.35) WHERE `entry` = 35656;

SET @ANUB_BASE_HEALTH:= 1950;
UPDATE `creature_template` SET `health_mod` = @ANUB_BASE_HEALTH + (@ANUB_BASE_HEALTH * 0.35) WHERE `entry` = 35616;

-- faction champs
SET @ALLIANCE_CHAMPIONS_BASE_HEALTH:= 256;
UPDATE `creature_template` SET `health_mod` = @ALLIANCE_CHAMPIONS_BASE_HEALTH + (@ALLIANCE_CHAMPIONS_BASE_HEALTH * 0.15) WHERE `entry` IN
(35704,
35745,
35736,
35748,
35667,
35664,
35723,
35716,
35730,
35670,
35701,
35676,
35733,
35739);

SET @HORDE_CHAMPIONS_BASE_HEALTH:= 256;
UPDATE `creature_template` SET `health_mod` = @HORDE_CHAMPIONS_BASE_HEALTH + (@HORDE_CHAMPIONS_BASE_HEALTH * 0.15) WHERE `entry` IN
(35749,
35742,
35707,
35685,
35726,
35691,
35697,
35673,
35720,
35713,
35682,
35710,
35694,
35688);


SET @PET_BASE_HEALTH:= 55;
UPDATE `creature_template` SET `health_mod` = @PET_BASE_HEALTH + (@PET_BASE_HEALTH * 0.15) WHERE `entry` IN (36303, 35776);
