UPDATE `creature_template` SET `modelid1` = '1166' WHERE `creature_template`.`entry` = 359;

REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(90029, 0, 0, 0, 0, 0, 29673, 0, 0, 0, 'Winter Wolf', NULL, NULL, 0, 10, 10, 0, 35, 0, 0.91, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2200, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 100, 1, 0, 359, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 140, 1, 0, 2, '', 12340);

UPDATE `item_template` SET `Quality` = '4',
`AllowableClass` = '262143', 
`AllowableRace` = '2147483647',
`RequiredSkill` = '762',
`RequiredSkillRank` = '150',
`description` = 'Three Sunwell developers died while they were trying to tame him.'  WHERE `item_template`.`entry` = 1133;