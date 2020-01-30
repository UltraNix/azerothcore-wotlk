-- DB/NPC: Hide some Demolisionists on Ulduar 25
UPDATE `creature` SET `spawnMask` = 1 WHERE `guid` IN (136361,136369,136362);