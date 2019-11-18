-- https://github.com/SunwellTracker/issues/issues/2474 Ruby Keepers get attacked by Mobb
UPDATE `creature` SET `unit_flags` = 537133056, `dynamicflags` = 32 WHERE `guid` = 108330;
UPDATE `creature_template` SET `faction` = 35 WHERE `entry` = 27530;
