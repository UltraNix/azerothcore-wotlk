-- Lower ICD a little bit due to how auras are refresh on sc
UPDATE `spell_proc_event` SET `Cooldown` = 5500 WHERE `entry` = -56636;