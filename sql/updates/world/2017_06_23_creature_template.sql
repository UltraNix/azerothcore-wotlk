-- Quest 10425 - Escape from the Staging Grounds
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=20854;
-- Janalai visual
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|0x00000080 WHERE `entry`=23920;
