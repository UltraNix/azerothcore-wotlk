-- DB/Loot: Fix Mighty Protection Potion recipe drops 
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=20, `GroupId`=2 WHERE `Item` IN (44564, 44565, 44566, 44567, 44568);
-- DB/Loot: remove deprecated item Tome of Tranquilizing Shot 
DELETE FROM `creature_loot_template` WHERE `Item`=16665;
--  Core/Spell: allow Northrend Inscription Research to unlock three recipes the first time it is cast.