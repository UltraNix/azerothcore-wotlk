ALTER TABLE `character_stats` 
ADD `spellHit` INT(10)  UNSIGNED NOT NULL DEFAULT '0' AFTER `regMana`, 
ADD `meleeHit` INT(10)  UNSIGNED NOT NULL DEFAULT '0' AFTER `spellHit`, 
ADD `rangeHit` INT(10)  UNSIGNED NOT NULL DEFAULT '0' AFTER `meleeHit`, 