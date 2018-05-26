-- Ring of Blood
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x01000000  WHERE `entry` IN (18398,18399, 18400, 18401, 18402, 18069);
-- Amphitheatre
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x01000000  WHERE `entry` IN (30014, 30017, 30026, 30020, 30023, 30022);
