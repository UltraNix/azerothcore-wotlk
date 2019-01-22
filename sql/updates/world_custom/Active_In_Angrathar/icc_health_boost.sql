/* ICC HEALTH BOOST */

SET @AXETHROWER:= 38676;
SET @AXETHROWER_BASE:= 22.4;

UPDATE `creature_template` SET `health_mod` = @AXETHROWER_BASE + (@AXETHROWER_BASE * 0.5) WHERE `entry` = @AXETHROWER;

SET @RIFLEMAN:= 38690;
SET @RIFLEMAN_BASE:= 22.4;

UPDATE `creature_template` SET `health_mod` = @RIFLEMAN_BASE + (@RIFLEMAN_BASE * 0.5) WHERE `entry` = @RIFLEMAN;

SET @SORCERER:= 37116;
SET @SORCERER_BASE:= 15;

SET @BATTLEMAGE:= 37117;
SET @BATTLEMAGE_BASE:= 15;

UPDATE `creature_template` SET `health_mod` = @SORCERER_BASE + (@SORCERER_BASE * 0.8) WHERE `entry` = @SORCERER;
UPDATE `creature_template` SET `health_mod` = @BATTLEMAGE_BASE + (@BATTLEMAGE_BASE * 0.8) WHERE `entry` = @BATTLEMAGE;

SET @REAVER:= 38680;
SET @REAVER_BASE:= 22.4;

SET @MARINE:= 38686;
SET @MARINE_BASE:= 22.4;

UPDATE `creature_template` SET `health_mod` = @REAVER_BASE + (@REAVER_BASE * 0.5) WHERE `entry` = @REAVER;
UPDATE `creature_template` SET `health_mod` = @MARINE_BASE + (@MARINE_BASE * 0.5) WHERE `entry` = @MARINE;


SET @MARROWGAR:= 37959;
SET @MARROWGAR_BASE:= 2250;

UPDATE `creature_template` SET `health_mod` = @MARROWGAR_BASE + (@MARROWGAR_BASE * 0.246) WHERE `entry` = @MARROWGAR;

SET @DEATHWHISPER:= 38297;
SET @DEATHWHISPER_BASE:= 2400;

UPDATE `creature_template` SET `health_mod` = @DEATHWHISPER_BASE + (@DEATHWHISPER_BASE * 0.237) WHERE `entry` = @DEATHWHISPER;

SET @DEATHBRINGER:= 38583;
SET @DEATHBRINGER_BASE:= 3150;

UPDATE `creature_template` SET `health_mod` = @DEATHBRINGER_BASE + (@DEATHBRINGER_BASE * 0.203) WHERE `entry` = @DEATHBRINGER;

SET @FESTERGUT:= 37506;
SET @FESTERGUT_BASE:= 3750;

UPDATE `creature_template` SET `health_mod` = @FESTERGUT_BASE + (@FESTERGUT_BASE * 0.2) WHERE `entry` = @FESTERGUT;

SET @ROTFACE:= 38550;
SET @ROTFACE_BASE:= 3400;

UPDATE `creature_template` SET `health_mod` = @ROTFACE_BASE + (@ROTFACE_BASE * 0.221) WHERE `entry` = @ROTFACE;

SET @PROF:= 38586;
SET @PROF_BASE:= 3600;

UPDATE `creature_template` SET `health_mod` = @PROF_BASE + (@PROF_BASE * 0.19) WHERE `entry` = @PROF;

SET @VOLATILE_OOZE:= 38759;
SET @VOLATILE_OOZE_BASE:= 350;

UPDATE `creature_template` SET `health_mod` = @VOLATILE_OOZE_BASE + (@VOLATILE_OOZE_BASE * 0.15) WHERE `entry` = @VOLATILE_OOZE;

SET @GAS:= 38761;
SET @GAS_BASE:= 350;

UPDATE `creature_template` SET `health_mod` = @GAS_BASE + (@GAS_BASE * 0.15) WHERE `entry` = @GAS;

SET @KELE:= 38770;
SET @TALDRAM:= 38772;
SET @VALANAR:= 38785;
SET @PRINCE_BASE:= 2187;

UPDATE `creature_template` SET `health_mod` = @PRINCE_BASE + (@PRINCE_BASE * 0.283) WHERE `entry` IN (@KELE, @TALDRAM, @VALANAR);

SET @BQL:= 38436;
SET @BQL_BASE:= 5113;

UPDATE `creature_template` SET `health_mod` = @BQL_BASE + (@BQL_BASE * 0.15) WHERE `entry` = @BQL;

SET @BLAZING_SKELETON:= 38722;
SET @BLAZING_SKELETON_BASE:= 25;

UPDATE `creature_template` SET `health_mod` = @BLAZING_SKELETON_BASE + (@BLAZING_SKELETON_BASE * 0.25) WHERE `entry` = @BLAZING_SKELETON;

SET @GLUT:= 38734;
SET @GLUT_BASE:= 94;

UPDATE `creature_template` SET `health_mod` = @GLUT_BASE + (@GLUT_BASE * 0.15) WHERE `entry` = @GLUT;

SET @BLISTERING:= 38733;
SET @BLISTERING_BASE:= 24;

UPDATE `creature_template` SET `health_mod` = @BLISTERING_BASE + (@BLISTERING_BASE * 0.25) WHERE `entry` = @BLISTERING;

SET @RISEN_ARCH:= 38735;
SET @RISEN_ARCH_BASE:= 30;

UPDATE `creature_template` SET `health_mod` = @RISEN_ARCH_BASE + (@RISEN_ARCH_BASE * 0.2) WHERE `entry` = @RISEN_ARCH;

SET @SIDNRA:= 38267;
SET @SINDRA_BASE:= 3300;

UPDATE `creature_template` SET `health_mod` = @SINDRA_BASE + (@SINDRA_BASE * 0.287) WHERE `entry` = @SINDRA;

SET @LK:= 39168;
SET @LK_BASE:= 7397;

UPDATE `creature_template` SET `health_mod` = @LK_BASE + (@LK_BASE * 0.15) WHERE `entry` = @LK;

SET @GHOUL:= 39311;
SET @GHOUL_BASE:= 60;

UPDATE `creature_template` SET `health_mod` = @GHOUL_BASE + (@GHOUL_BASE * 0.2) WHERE `entry` = @GHOUL;

SET @VILE:= 39286;
SET @VILE_BASE:= 21.4286;

UPDATE `creature_template` SET `health_mod` = @VILE_BASE + (@VILE_BASE * 0.15) WHERE `entry` = @VILE;

SET @WICKED:= 39289;
SET @WICKED_BASE:= 0.634921;

UPDATE `creature_template` SET `health_mod` = @WICKED_BASE + (@WICKED_BASE * 0.75) WHERE `entry` = @WICKED;






















