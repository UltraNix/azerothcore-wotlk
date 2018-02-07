SET @SMALL_FIRE_ENTRY = 187676;
SET @BIG_FIRE_ENTRY = 187675;
SET @FIRE_DESPAWN_TIME = 10;

SET @NORTH_PLATFORM_ENTRY = 25441;
SET @WEST_PLATFORM_ENTRY = 25443;
SET @EAST_PLATFORM_ENTRY = 25442;

DELETE FROM `gameobject` WHERE `id` IN (@SMALL_FIRE_ENTRY, @BIG_FIRE_ENTRY); 

UPDATE `smart_scripts` SET `link` = 1 WHERE `entryorguid` IN (@NORTH_PLATFORM_ENTRY, @WEST_PLATFORM_ENTRY, @EAST_PLATFORM_ENTRY) AND `id` = 0;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@NORTH_PLATFORM_ENTRY, @WEST_PLATFORM_ENTRY, @EAST_PLATFORM_ENTRY) AND `id` IN (1,2,3,4,5,6,7);
INSERT INTO `smart_scripts` VALUES
(@NORTH_PLATFORM_ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 50, @BIG_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3670.08, 5556.74, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3664.58, 5543.46, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3672.65, 5537.60, 67.51, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3680.28, 5551.31, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3685.06, 5559.32, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3674.30, 5571.54, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@NORTH_PLATFORM_ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3660.24, 5562.54, 66.08, 0, "North Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),

(@WEST_PLATFORM_ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 50, @BIG_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3591.26, 5632.42, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3581.33, 5620.27, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3595.00, 5617.88, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3602.83, 5626.51, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3603.17, 5638.20, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3590.51, 5645.46, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@WEST_PLATFORM_ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3578.21, 5635.98, 75.99, 0, "West Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),

(@EAST_PLATFORM_ENTRY, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 50, @BIG_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3564.72, 5532.70, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3570.11, 5519.84, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3577.34, 5528.13, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3576.73, 5539.17, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3570.16, 5546.62, 86.00, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3555.03, 5541.35, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire"),
(@EAST_PLATFORM_ENTRY, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 50, @SMALL_FIRE_ENTRY, @FIRE_DESPAWN_TIME, 0, 0, 0, 0, 8, 0, 0, 0, 3552.60, 5527.65, 86.10, 0, "East Platform - On Spellhit 'Throw Gnomish Grenade' - Temp Summon Fire");