-- Savage Gladiator's Longbow & Heavy Crossbow, Hateful Gladiator's Longbow & Heavy Crossbow:
UPDATE `item_template` SET `ammo_type`= 2, `RangedModRange` = 100 WHERE `entry` IN (42445,42446,42489,42494);
-- Hateful Gladiator's War Edge (42449):
UPDATE `item_template` SET `RangedModRange` = 100, `spelltrigger_1` = 1 WHERE `entry` IN (42449);
-- Savage Gladiator's Rifle (42447) & Hateful Gladiator's Rifle (42484) :
UPDATE `item_template` SET `ammo_type`= 3, `RangedModRange` = 100 WHERE `entry` IN (42447,42484);
-- Hateful Gladiator's Baton of Light, Hateful Gladiator's Piercing Touch, Hateful Gladiator's Touch of Defeat:
UPDATE `item_template` SET `RangedModRange` = 100 WHERE `entry` IN (42512,42518,42501);

-- Hateful Gladiator's Baton of Light damage restore
UPDATE `item_template` SET 
`dmg_min1` = '437',
`dmg_max1` = '812',
`dmg_type1` = '2' WHERE `item_template`.`entry` = 42512;

-- Hateful Gladiator's Piercing Touch damage restore
UPDATE `item_template` SET 
`dmg_min1` = '437',
`dmg_max1` = '812',
`dmg_type1` = '2' WHERE `item_template`.`entry` = 42518;

-- Hateful Gladiator's Touch of Defeat damage restore
UPDATE `item_template` SET 
`dmg_min1` = '437',
`dmg_max1` = '812',
`dmg_type1` = '2' WHERE `item_template`.`entry` = 42501;