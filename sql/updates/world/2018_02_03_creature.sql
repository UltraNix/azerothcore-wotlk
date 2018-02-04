-- Roanauk Icemist, Under-King Anub'et'kan - reduce respawnTime
UPDATE `creature` SET `spawntimesecs` = 30 WHERE `guid` IN (75022, 85321); -- 120