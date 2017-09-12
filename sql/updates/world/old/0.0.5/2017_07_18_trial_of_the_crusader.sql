-- Mistress of Pain & Felflame Infernal 10 man
UPDATE `creature_template` SET `mindmg`=2000, `maxdmg`=2400, `dmg_multiplier`=10 WHERE `entry` IN (34826, 34815, 35271, 35263);
-- Nether Portal 10hc
UPDATE `creature_template` SET `Health_mod`=2175/189 WHERE `entry`=35279;
-- Mistress of Pain & Felflame Infernal 25 man
UPDATE `creature_template` SET `mindmg`=2300, `maxdmg`=3000, `dmg_multiplier`=10 WHERE `entry` IN (35262, 35264, 35270, 35272);
-- Felflame Infernal 10 hc 
UPDATE `creature_template` SET `Health_mod`=980/94 WHERE `entry`=35263;
-- Felflame Infernal 25 hc
UPDATE `creature_template` SET `Health_mod`=9545/310 WHERE `entry`=35264;
-- Eydis Darkbane 10 norm
UPDATE `creature_template` SET `mindmg`=2200, `maxdmg`=2500, `dmg_multiplier`=10 WHERE `entry`=34496;
-- Fjola Darkbane 10 norm
UPDATE `creature_template` SET `mindmg`=2200, `maxdmg`=2500, `dmg_multiplier`=10 WHERE `entry`=34497;
-- Eydis Darkbane 10 hc
UPDATE `creature_template` SET `mindmg`=3000, `maxdmg`=3500, `dmg_multiplier`=10 WHERE `entry`=35348;
-- Fjola Darkbane 10 hc
UPDATE `creature_template` SET `mindmg`=3000, `maxdmg`=3500, `dmg_multiplier`=10 WHERE `entry`=35351;
-- Eydis Darkbane 25 norm
UPDATE `creature_template` SET `mindmg`=3000, `maxdmg`=3500, `dmg_multiplier`=10 WHERE `entry`=35347;
-- Fjola Darkbane 25 norm
UPDATE `creature_template` SET `mindmg`=3000, `maxdmg`=3500, `dmg_multiplier`=10 WHERE `entry`=35350;
-- Eydis Darkbane 25 hc
UPDATE `creature_template` SET `mindmg`=3300, `maxdmg`=3900, `dmg_multiplier`=10 WHERE `entry`=35349;
-- Fjola Darkbane 25 hc
UPDATE `creature_template` SET `mindmg`=3300, `maxdmg`=3900, `dmg_multiplier`=10 WHERE `entry`=35352;
-- Nerubian Burrower
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82 WHERE `entry` IN (34607, 34648, 35655, 35656); 