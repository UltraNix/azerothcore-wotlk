-- Workshops on WG - bump phaseMask to handle dynamicTree model intersections properly
UPDATE `gameobject` SET `phaseMask`=1|16|32|64|128 WHERE `id` BETWEEN 192028 AND 192033;
