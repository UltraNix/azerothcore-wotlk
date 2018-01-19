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

UPDATE `creature_template` SET `Health_mod` = '340' WHERE `creature_template`.`entry` =30601;
UPDATE `creature_template` SET `Health_mod` = '340' WHERE `creature_template`.`entry` =30602;
UPDATE `creature_template` SET `Health_mod` = '340' WHERE `creature_template`.`entry` =30603;
UPDATE `creature_template` SET `Health_mod` = '340' WHERE `creature_template`.`entry` =30600;

UPDATE `smart_scripts` SET `event_param3` = '5000', `event_param4` = '5000' WHERE `smart_scripts`.`entryorguid` = 16505 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =0 AND `smart_scripts`.`link` =0;
UPDATE `smart_scripts` SET `event_phase_mask` = '0', `action_param2` = '4' WHERE `smart_scripts`.`entryorguid` =16573 AND `smart_scripts`.`source_type` =0 AND `smart_scripts`.`id` =3 AND `smart_scripts`.`link` =0;

UPDATE `creature_template` SET `dmg_multiplier` = '110', `Health_mod` = '1800' WHERE `creature_template`.`entry` =29991;
UPDATE `creature_template` SET `Health_mod` = '2100' WHERE `creature_template`.`entry` =30061;

UPDATE `creature_template` SET `dmg_multiplier` = '23' WHERE `creature_template`.`entry` =30048;
UPDATE `creature_template` SET `dmg_multiplier` = '26' WHERE `creature_template`.`entry` =30057;

/* NAXXRAMAS ORB */
DELETE FROM `areatrigger_teleport` WHERE `areatrigger_teleport`.`id` = 4156;

UPDATE `gameobject` SET  `phaseMask` = '2', `position_x` = '3005.51', `position_y` = '-3434.63', `position_z` = '304.195', `orientation` = '5.810410' WHERE `gameobject`.`guid` = 5216;

UPDATE `gameobject_template` SET `data3` = '0', `data10` = '72617' WHERE `gameobject_template`.`entry` = 202277;
UPDATE `gameobject_template` SET `data3` = '0', `data10` = '72613' WHERE `gameobject_template`.`entry` = 202278;

DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 65853; /* Delete portal from 3.3.0 */