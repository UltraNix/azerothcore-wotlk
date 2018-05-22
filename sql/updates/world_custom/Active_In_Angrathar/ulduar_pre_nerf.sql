-- Ignis
SET @IGNIS_10:= 33118;
SET @IGNIS_25:= 33190;
SET @IGNIS_10_BASE_HEALTH:= 400;
SET @IGNIS_25_BASE_HEALTH:= 1400;

-- 10 man
UPDATE `creature_template` SET `health_mod` = @IGNIS_10_BASE_HEALTH + (@IGNIS_10_BASE_HEALTH * 0.25) WHERE `entry` = @IGNIS_10;

-- 25 man
UPDATE `creature_template` SET `health_mod` = @IGNIS_25_BASE_HEALTH + (@IGNIS_25_BASE_HEALTH * 0.25) WHERE `entry` = @IGNIS_25;

-- XT-002
SET @XT_10:= 33293;
SET @XT_25:= 33885;
SET @XT_BASE_HEALTH_10:= 358.552;
SET @XT_BASE_HEALTH_25:= 1613.48;

-- 10m
UPDATE `creature_template` SET `health_mod` = @XT_BASE_HEALTH_10 + (@XT_BASE_HEALTH_10 * 0.20) WHERE `entry` = @XT_10;
-- 25m
UPDATE `creature_template` SET `health_mod` = @XT_BASE_HEALTH_25 + (@XT_BASE_HEALTH_25 * 0.11) WHERE `entry` = @XT_25;

SET @PUMMELER_10:= 33344;
SET @PUMMELER_25:= 33888;
SET @PUMMELER_BASE_10:= 15;
SET @PUMMELER_BASE_25:= 40;
SET @LIFE_SPARK_25:= 34005;
SET @LIFE_SPARK_10:= 34004;
SET @LIFE_SPARK_BASE_10:= 4;
SET @LIFE_SPARK_BASE_25:= 14;

-- 10m
UPDATE `creature_template` SET `health_mod` = @PUMMELER_BASE_10 + (@PUMMELER_BASE_10 * 0.15) WHERE `entry` = @PUMMELER_10;
-- 25m
UPDATE `creature_template` SET `health_mod` = @PUMMELER_BASE_25 + (@PUMMELER_BASE_25 * 0.15) WHERE `entry` = @PUMMELER_25;

-- life spark 10m
UPDATE `creature_template` SET `health_mod` = @LIFE_SPARK_BASE_10 + (@LIFE_SPARK_BASE_10) WHERE `entry` = @LIFE_SPARK_10;

-- life spark 25m
UPDATE `creature_template` SET `health_mod` = @LIFE_SPARK_BASE_25 + (@LIFE_SPARK_BASE_25) WHERE `entry` = @LIFE_SPARK_25;

-- life spark
UPDATE `creature_template` SET `mindmg` = 14000, `maxdmg` = 15000, `dmg_multiplier` = 1 WHERE `entry` = @LIFE_SPARK_25;

-- XT adds
UPDATE `creature_template` SET `mechanic_immune_mask` =
 1              -- MECHANIC_CHARM  
 | 2            -- MECHANIC_DISORIENTED    
 | 4            -- MECHANIC_DISARM         
 | 8            -- MECHANIC_DISTRACT       
 | 16           -- MECHANIC_FEAR  
 | 32           -- MECHANIC_GRIP
 | 64           -- MECHANIC_ROOT  
 -- | 128          -- MECHANIC_PACIFY
 | 256          -- MECHANIC_SILENCE      
 | 512          -- MECHANIC_SLEEP        
 | 1024         -- MECHANIC_SNARE       
 | 2048         -- MECHANIC_STUN        
 | 4096         -- MECHANIC_FREEZE      
 | 8192         -- MECHANIC_KNOCKOUT
 -- | 16384        -- MECHANIC_BLEED    
 | 32768        -- MECHANIC_BANDAGE
 | 65536        -- MECHANIC_POLYMORPH  
 | 131072       -- MECHANIC_BANISH    
 -- | 262144       -- MECHANIC_SHIELD  
 | 524288       -- MECHANIC_SHACKLE
 | 1048576      -- MECHANIC_MOUNT
 -- | 2097152      -- MECHANIC_INFECTED
 | 4194304      -- MECHANIC_TURN
 | 8388608      -- MECHANIC_HORROR
 -- | 16777216     -- MECHANIC_INVULNERABILITY
 | 33554432     -- MECHANIC_INTERRUPT       
 | 67108864     -- MECHANIC_DAZE    
 -- | 134217728    -- MECHANIC_DISCOVERY
 -- | 268435456    -- MECHANIC_IMMUNE_SHIELD
 | 536870912    -- MECHANIC_SAPPED         
 -- | 1073741824   -- MECHANIC_ENRAGED 
WHERE `entry` IN (33343, 33887, 33346, 33886);

-- Razorscale
SET @RAZORSCALE_10:= 33186;
SET @RAZORSCALE_BASE_HEALTH_10:= 255;
SET @RAZORSCALE_25:= 33724;
SET @RAZORSCALE_BASE_HEALTH_25:= 900;

-- 10 man
UPDATE `creature_template` SET `health_mod` = @RAZORSCALE_BASE_HEALTH_10 + (@RAZORSCALE_BASE_HEALTH_10 * 0.37) WHERE `entry` = @RAZORSCALE_10;

-- 25 man
UPDATE `creature_template` SET `health_mod` = @RAZORSCALE_BASE_HEALTH_25 + (@RAZORSCALE_BASE_HEALTH_25 * 0.25) WHERE `entry` = @RAZORSCALE_25;

SET @DARK_SENTINEL_10:= 33846;
SET @DARK_SENTINEL_10_BASE_HP:= 13;

-- 10 man
UPDATE `creature_template` SET `health_mod` = @DARK_SENTINEL_10_BASE_HP + (@DARK_SENTINEL_10_BASE_HP * 0.4) WHERE `entry` = @DARK_SENTINEL_10;

-- Flame Leviathan
SET @WARD_OF_LIFE_10:= 34275;
SET @WARD_OF_LIFE_25:= 34276;
SET @WARD_BASE_HEALTH_10:= 24;
SET @WARD_BASE_HEALTH_25:= 40;

SET @WRITHING_LASHER10:= 33387;
SET @WRITHING_LASHER25:= 34277;
SET @WRITHING_LASHER10_BASE_HP:= 5.1;
SET @WRITHING_LASHER25_BASE_HP:= 15.1;


-- 10 man
UPDATE `creature_template` SET `health_mod` = @WRITHING_LASHER10_BASE_HP + (@WRITHING_LASHER10_BASE_HP * 0.15) WHERE `entry` = @WRITHING_LASHER10;
UPDATE `creature_template` SET `health_mod` = @WARD_BASE_HEALTH_10 + (@WARD_BASE_HEALTH_10 * 0.15) WHERE `entry` = @WARD_OF_LIFE_10;

-- 25 man
UPDATE `creature_template` SET `health_mod` = @WRITHING_LASHER25_BASE_HP + (@WRITHING_LASHER25_BASE_HP * 0.15) WHERE `entry` = @WRITHING_LASHER25;
UPDATE `creature_template` SET `health_mod` = @WARD_BASE_HEALTH_25 + (@WARD_BASE_HEALTH_25 * 0.15) WHERE `entry` = @WARD_OF_LIFE_25;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 65045;

DELETE FROM `spell_script_names` WHERE `spell_id` = 65045;
INSERT INTO `spell_script_names` VALUES
(65045, "spell_flames_flame_leviathan_fury_remover");

UPDATE `creature_template` SET `ScriptName` = "npc_flame_leviathan_vehicles" WHERE `entry` IN (33060, 33062, 33109);

-- kologarn
SET @LEFT_ARM_10:= 32933;
SET @LEFT_ARM_25:= 33910;
SET @RIGHT_ARM_10:= 32934;
SET @RIGHT_ARM_25:= 33911;
SET @KOLOGARN_10:= 32930;
SET @KOLOGARN_25:= 33909;

SET @LEFT_ARM_10_BASE:= 39;
SET @LEFT_ARM_25_BASE:= 165;

SET @RIGHT_ARM_10_BASE:= 39;
SET @RIGHT_ARM_25_BASE:= 165;

SET @KOLOGARN_10_BASE:= 260;
SET @KOLOGARN_25_BASE:= 1100;

-- left arm
UPDATE `creature_template` SET `health_mod` = @LEFT_ARM_10_BASE + (@LEFT_ARM_10_BASE * 1.2) WHERE `entry` = @LEFT_ARM_10;
UPDATE `creature_template` SET `health_mod` = @LEFT_ARM_25_BASE + (@LEFT_ARM_25_BASE * 1.2) WHERE `entry` = @LEFT_ARM_25;
-- right arm
UPDATE `creature_template` SET `health_mod` = @RIGHT_ARM_10_BASE + (@RIGHT_ARM_10_BASE * 1.2) WHERE `entry` = @RIGHT_ARM_10;
UPDATE `creature_template` SET `health_mod` = @RIGHT_ARM_25_BASE + (@RIGHT_ARM_25_BASE * 1.2) WHERE `entry` = @RIGHT_ARM_25;
-- Kologarn
UPDATE `creature_template` SET `health_mod` = @KOLOGARN_10_BASE + (@KOLOGARN_10_BASE * 0.37) WHERE `entry` = @KOLOGARN_10;
UPDATE `creature_template` SET `health_mod` = @KOLOGARN_25_BASE + (@KOLOGARN_25_BASE * 0.37) WHERE `entry` = @KOLOGARN_25;

-- Dark rune champion disarm immunity
UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` | 4 WHERE `entry` IN (32876, 33158);

-- Assault bot
SET @ASSAULT_BOT_25:= 34115;
SET @ASSAULT_BOT_25_BASE:= 50;

UPDATE `creature_template` SET `health_mod` = @ASSAULT_BOT_25_BASE + (@ASSAULT_BOT_25_BASE * 0.3), `dmg_multiplier` = 16 WHERE `entry` = @ASSAULT_BOT_25;

-- General Vezax
SET @GENERAL_VEZAX_10:= 33271;
SET @GENERAL_VEZAX_25:= 33449;

SET @SARONITE_ANIMUS_10:= 33524;
SET @SARONITE_ANIMUS_25:= 34152;

SET @GENERAL_VEZAX_BASE_10:= 450;
SET @GENERAL_VEZAX_BASE_25:= 1648.09;

SET @SARONITE_ANIMUS_10_BASE:= 113;
SET @SARONITE_ANIMUS_25_BASE:= 1012;

-- 10 man
UPDATE `creature_template` SET `health_mod` = @GENERAL_VEZAX_BASE_10 + (@GENERAL_VEZAX_BASE_10 * 0.33), `dmg_multiplier` = 7.7 WHERE `entry` = @GENERAL_VEZAX_10;
-- 25 man
UPDATE `creature_template` SET `health_mod` = @GENERAL_VEZAX_BASE_25 + (@GENERAL_VEZAX_BASE_25 * 0.33) WHERE `entry` = @GENERAL_VEZAX_25;
-- 10 man
UPDATE `creature_template` SET `health_mod` = @SARONITE_ANIMUS_10_BASE + (@SARONITE_ANIMUS_10_BASE * 0.6) WHERE `entry` = @SARONITE_ANIMUS_10;
-- 25 man
UPDATE `creature_template` SET `health_mod` = @SARONITE_ANIMUS_25_BASE - (@SARONITE_ANIMUS_25_BASE * 0.015) WHERE `entry` = @SARONITE_ANIMUS_25;

-- yogg saron
SET @YOGG_SARON_25:= 33955;

SET @YOGG_SARON_25_BASE:= 3155.2;

UPDATE `creature_template` SET `health_mod` = @YOGG_SARON_25_BASE + (@YOGG_SARON_25_BASE * 0.25) WHERE `entry` = @YOGG_SARON_25;
