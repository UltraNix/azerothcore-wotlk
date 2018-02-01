-- Remove unique items from reference table 24078
DELETE FROM `reference_loot_template` WHERE `Entry`=24078 AND `Item` IN (899,1391,1440,1446,1469,1473,1929,1930,1936,1943,1944,1945,1951,2020,4290,10400,10401,10402);

-- Add former items from reference table 24078 to their proper NPCs
DELETE FROM `creature_loot_template` WHERE `Item` IN (899,1391,1440,1446,1469,1473,1929,1930,1936,1943,1944,1945,1951,2020,4290,10400,10401,10402);
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`GroupId`) VALUES
(217,899,0.1,0), -- Venom Web Spider - Venom Web Fang
(446,1440,0.1,0),  -- Redridge Basher - Gnoll Skull Basher
(440,1446,0.1,0),  -- Blackrock Grunt - Blackrock Boots
(578,1469,0.1,0),  -- Murloc Scout - Scimitar of Atun"
(14270,1469,1,0),  -- Squiddic - Scimitar of Atun
(545,1473,0.1,0),  -- Murloc Tidecaller - Riverside Staff
(1729,1929,0.1,0),  -- Defias Evoker - Silk-threaded Trousers
(4418,1929,0.1,0),  -- Defias Wizard - Silk-threaded Trousers
(598,1930,0.1,0),  -- Defias Miner - Stonemason Cloak
(622,1936,0.1,0),  -- Goblin Engineer - Goblin Screwdriver
(3947,1943,0.1,0),  -- Goblin Shipbuilder - Goblin Mail Leggings
(1731,1944,0.1,0),  -- Goblin Craftsman - Metalworking Gloves
(641,1945,0.1,0),  -- Goblin Woodcarver - Woodworking Gloves
(657,1951,0.1,0),  -- Defias Pirate - Blackwater Cutlass
(1732,1951,0.1,0),  -- Defias Squallshaper - Blackwater Cutlass
(539,2020,0.1,0),  -- Pygmy Venom Web Spider - Hollowfang Blade
(832,4290,0.5,0),  -- Dust Devil - Dust Bowl
(634,10400,0.5,2),  -- Defias Overseer - Blackened Defias Leggings
(4417,10400,0.5,2),  -- Defias Taskmaster - Blackened Defias Leggings
(634,10401,0.5,2),  -- Defias Overseer - Blackened Defias Gloves
(4417,10401,0.5,2),  -- Defias Taskmaster - Blackened Defias Gloves
(4416,10402,0.5,0); -- Defias Strip Miner - Blackened Defias Boots


-- Mindless Zombie
DELETE FROM `creature_loot_template` WHERE `Entry`=1501;
INSERT INTO `creature_loot_template` VALUES
(1501,159,10,1,0,1,1),  -- Refreshing Spring Water
(1501,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1501,24073,5,1,0,1,1),  -- Junk
(1501,11111,0.5,1,0,1,1); -- Bags

-- Wretched Ghoul
DELETE FROM `creature_loot_template` WHERE `Entry`=1502;
INSERT INTO `creature_loot_template` VALUES
(1502,159,10,1,0,1,1),  -- Refreshing Spring Water
(1502,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1502,24073,5,1,0,1,1),  -- Junk
(1502,11111,0.5,1,0,1,1); -- Bags

-- Rattlecage Skeleton
DELETE FROM `creature_loot_template` WHERE `Entry`=1890;
INSERT INTO `creature_loot_template` VALUES
(1890,159,10,1,0,1,1),  -- Refreshing Spring Water
(1890,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1890,3262,1,1,0,1,1),  -- Putrid Wooden Hammer (unique)
(1890,6281,100,1,0,1,1),  -- Rattlecage Skull (quest)
(1890,24073,5,1,0,1,1),  -- Junk
(1890,11111,0.1,1,0,1,1); -- Bags

-- Young Nightweb Spider
DELETE FROM `creature_loot_template` WHERE `Entry`=1504;
INSERT INTO `creature_loot_template` VALUES
(1504,1476,25,1,1,1,2),  -- Snapped Spider Limb
(1504,7100,25,1,1,1,2),  -- Sticky Ichor
(1504,7101,25,1,1,1,2),  -- Bug Eye
(1504,24073,2,1,0,1,1),  -- Junk
(1504,11111,0.1,1,0,1,1); -- Bags

-- Nightweb Spider
DELETE FROM `creature_loot_template` WHERE `Entry`=1505;
INSERT INTO `creature_loot_template` VALUES
(1505,1476,25,1,1,1,2),  -- Snapped Spider Limb
(1505,7100,25,1,1,1,2),  -- Sticky Ichor
(1505,7101,25,1,1,1,2),  -- Bug Eye
(1505,3263,1,1,0,1,1),  -- Webbed Pants (unique)
(1505,24073,2,1,0,1,1); -- Junk

-- Nightweb Matriach
DELETE FROM `creature_loot_template` WHERE `Entry`=1688;
INSERT INTO `creature_loot_template` VALUES
(1688,1476,25,1,1,1,1),  -- Snapped Spider Limb
(1688,7100,25,1,1,1,1),  -- Sticky Ichor
(1688,7101,25,1,1,1,1),  -- Bug Eye
(1688,3261,100,1,0,1,1); -- Webbed Cloak (unique)

-- Scarlet Convert
DELETE FROM `creature_loot_template` WHERE `Entry`=1506;
INSERT INTO `creature_loot_template` VALUES
(1506,159,10,1,0,1,1),  -- Refreshing Spring Water
(1506,2070,15,1,0,1,1),  -- Darnassian Bleu
(1506,2754,1,1,0,1,1),  -- Tarnished Bastard Sword (unique)
(1506,3266,100,1,0,1,1),  -- Scarlet Armband (quest)
(1506,24073,20,1,0,1,1),  -- Junk
(1506,11111,0.5,1,0,1,1); -- Bags

-- Scarlet Initiate
-- Adds missing robe
DELETE FROM `creature_loot_template` WHERE `Entry`=1507;
INSERT INTO `creature_loot_template` VALUES
(1507,159,10,1,0,1,1),  -- Refreshing Spring Water
(1507,2070,15,1,0,1,1),  -- Darnassian Bleu
(1507,3260,1,1,0,1,1),  -- Scarlet Initiate Robes (unique)
(1507,3266,100,1,0,1,1),  -- Scarlet Armband (quest)
(1507,24073,20,1,0,1,1),  -- Junk
(1507,11111,0.5,1,0,1,1); -- Bags

-- Young Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry`=1508;
INSERT INTO `creature_loot_template` VALUES
(1508,3300,25,1,1,1,1),  -- Rabbit's Foot
(1508,7074,25,1,1,1,2),  -- Chipped Claw
(1508,4865,25,1,1,1,2),  -- Ruined Pelt
(1508,7073,25,1,1,1,2),  -- Broken Fang
(1508,3265,100,1,0,1,1),  -- Scavenger Paw (quest)
(1508,24073,2,1,0,1,1),  -- Junk
(1508,11111,0.1,1,0,1,1); -- Bags

-- Ragged Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry`=1509;
INSERT INTO `creature_loot_template` VALUES
(1509,3300,25,1,1,1,1),  -- Rabbit's Foot
(1509,7074,25,1,1,1,2),  -- Chipped Claw
(1509,4865,25,1,1,1,2),  -- Ruined Pelt
(1509,7073,25,1,1,1,2),  -- Broken Fang
(1509,3265,100,1,0,1,1),  -- Scavenger Paw (quest)
(1509,24073,2,1,0,1,1),  -- Junk
(1509,11111,0.1,1,0,1,1); -- Bags

-- Duskbat
DELETE FROM `creature_loot_template` WHERE `Entry`=1512;
INSERT INTO `creature_loot_template` VALUES
(1512,6296,25,1,1,1,1),  -- Patch of Bat Hair
(1512,7074,15,1,1,1,2),  -- Chipped Claw
(1512,4865,15,1,1,1,2),  -- Ruined Pelt
(1512,7073,15,1,1,1,2),  -- Broken Fang
(1512,3264,100,1,0,1,1),  -- Duskbat Wing (quest)
(1512,24073,2,1,0,1,1),  -- Junk
(1512,11111,0.1,1,0,1,1); -- Bags

-- Mangy Duskbat
DELETE FROM `creature_loot_template` WHERE `Entry`=1513;
INSERT INTO `creature_loot_template` VALUES
(1513,6296,25,1,1,1,1),  -- Patch of Bat Hair
(1513,7074,15,1,1,1,2),  -- Chipped Claw
(1513,4865,15,1,1,1,2),  -- Ruined Pelt
(1513,7073,15,1,1,1,2),  -- Broken Fang
(1513,3264,100,1,0,1,1),  -- Duskbat Wing (quest)
(1513,24073,2,1,0,1,1),  -- Junk
(1513,11111,0.1,1,0,1,1); -- Bags

-- Meven Korgal
DELETE FROM `creature_loot_template` WHERE `Entry`=1667;
INSERT INTO `creature_loot_template` VALUES
(1667,159,10,1,0,1,1),  -- Refreshing Spring Water
(1667,2070,15,1,0,1,1),  -- Darnassian Bleu
(1667,2885,100,1,0,1,1),  -- Scarlet Crusade Documents (quest)
(1667,3266,100,1,0,1,1),  -- Scarlet Armband (quest)
(1667,24073,35,1,0,1,1),  -- Junk
(1667,11111,1,1,0,1,1); -- Bags


-- Stephen Bhartec
DELETE FROM `creature_loot_template` WHERE `Entry`=1916;
INSERT INTO `creature_loot_template` VALUES
(1916,159,10,1,0,1,1),  -- Refreshing Spring Water
(1916,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1916,3296,1,1,0,1,1),  -- Deadman Dagger (unique)
(1916,24073,20,1,0,1,1),  -- Junk
(1916,11111,1,1,0,1,1); -- Bags

-- Daniel Ulfman
DELETE FROM `creature_loot_template` WHERE `Entry`=1917;
INSERT INTO `creature_loot_template` VALUES
(1917,159,10,1,0,1,1),  -- Refreshing Spring Water
(1917,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1917,3293,1,1,0,1,1),  -- Deadman Cleaver (unique)
(1917,24073,20,1,0,1,1),  -- Junk
(1917,11111,1,1,0,1,1); -- Bags

-- Karrel Grayves
DELETE FROM `creature_loot_template` WHERE `Entry`=1918;
INSERT INTO `creature_loot_template` VALUES
(1918,159,10,1,0,1,1),  -- Refreshing Spring Water
(1918,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1918,3294,1,1,0,1,1),  -- Deadman Club (unique)
(1918,24073,20,1,0,1,1),  -- Junk
(1918,11111,1,1,0,1,1); -- Bags

-- Samuel Fipps
DELETE FROM `creature_loot_template` WHERE `Entry`=1919;
INSERT INTO `creature_loot_template` VALUES
(1919,159,10,1,0,1,1),  -- Refreshing Spring Water
(1919,4604,15,1,0,1,1),  -- Forest Mushroom Cap
(1919,3295,1,1,0,1,1),  -- Deadman Blade (unique)
(1919,16333,100,1,0,1,1),  -- Samuel's Remains (quest)
(1919,24073,20,1,0,1,1),  -- Junk
(1919,11111,1,1,0,1,1); -- Bags

-- Remove unique items from reference table 24077
DELETE FROM `reference_loot_template` WHERE `Entry`=24077 AND `Item` IN (827, 1214, 1219, 1405, 1925, 1928, 1958, 1959, 4676);

-- Add former items from reference table 24077 to their proper NPCs
DELETE FROM `creature_loot_template` WHERE `Item` IN (827, 1214, 1219, 1405, 1925, 1928, 1958, 1959, 4676);
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`GroupId`) VALUES
(122, 827, 0.1, 0),  -- Defias Highwayman - Wicked Blackjack
(449, 827, 0.1, 0),  -- Defias Knuckleduster - Wicked Blackjack
(426, 1214, 0.1, 0),  -- Redridge Brute - Gnoll Punisher
(424, 1219, 0.1, 0),  -- Redridge Poacher - Redridge Machete
(517, 1405, 0.1, 0),  -- Murloc Oracle - Foamspittle Staff
(1725, 1925, 0.1, 0),  -- Defias Watchman - Defias Rapier
(1726, 1928, 0.1, 0),  -- Defias Magician - Defias Mage Staff
(623, 1958, 0.1, 2),  -- Skeletal Miner - Petrified Shinbone
(623, 1959, 0.1, 2),  -- Skeletal Miner - Cold Iron Pick
(624, 1958, 0.1, 2),  -- Undead Excavator - Petrified Shinbone
(624, 4676, 0.1, 2),  -- Undead Excavator - Skeletal Gauntlets
(625, 1958, 0.1, 0);  -- Undead Dynamiter - Petrified Shinbone

-- Mottled Boar
DELETE FROM `creature_loot_template` WHERE `Entry`=3098;
INSERT INTO `creature_loot_template` VALUES
(3098,771, 5, 1, 0, 1, 1), -- Chipped Boar Tusk
(3098,4865, 2, 1, 0, 1, 2), -- Ruined Pelt
(3098,7098, 2, 1, 0, 1, 2), -- Splintered Tusk
(3098,117, 90, 1, 0, 1, 3), -- Tough Jerky
(3098,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Vile Familiar
-- Also removes obsolete Vile Familiar Head quest item
DELETE FROM `creature_loot_template` WHERE `Entry`=3101;
INSERT INTO `creature_loot_template` VALUES
(3101,117, 2, 1, 0, 1, 1), -- Tough Jerky
(3101,159, 1, 1, 0, 1, 1), -- Refreshing Spring Water
(3101,24073, 1, 1, 0, 1, 1), -- Junk
(3101,11111, 0.5, 1, 0, 1, 1); -- Bags

-- Felstalker
DELETE FROM `creature_loot_template` WHERE `Entry`=3102;
INSERT INTO `creature_loot_template` VALUES
(3102,6640, 100, 1, 0, 1, 1), -- Felstalker Hoof (quest)
(3102,3300, 5, 1, 0, 1, 1), -- Rabbit's Foot
(3102,7073, 0.5, 1, 0, 1, 2), -- Broken Fang
(3102,7074, 0.5, 1, 0, 1, 2), -- Chipped Claw
(3102,4865, 0.5, 1, 0, 1, 2), -- Ruined Pelt
(3102,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Scorpid Worker
DELETE FROM `creature_loot_template` WHERE `Entry`=3124;
INSERT INTO `creature_loot_template` VALUES
(3124,4862, 100, 1, 0, 1, 1), -- Scorpid Tail (quest)
(3124,4867, 1, 1, 0, 1, 2), -- Broken Scorpid Leg
(3124,7099, 40, 1, 0, 1, 2), -- Severed Pincer
(3124,7101, 1, 1, 0, 1, 2), -- Sticky Ichor
(3124,7100, 1, 1, 0, 1, 2), -- Bug Eye
(3124,24073, 1, 1, 0, 1, 1), -- Junk
(3124,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Sarkoth
DELETE FROM `creature_loot_template` WHERE `Entry`=3281;
INSERT INTO `creature_loot_template` VALUES
(3281,4905, 100, 1, 0, 1, 1), -- Sarkoth's Mangled Claw (quest)
(3281,4867, 1, 1, 0, 1, 1), -- Broken Scorpid Leg
(3281,7099, 40, 1, 0, 1, 1), -- Severed Pincer
(3281,7101, 1, 1, 0, 1, 1), -- Sticky Ichor
(3281,7100, 1, 1, 0, 1, 1), -- Bug Eye
(3281,24073, 1, 1, 0, 1, 1), -- Junk
(3281,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Yarrog Baneshadow
DELETE FROM `creature_loot_template` WHERE `Entry`=3183;
INSERT INTO `creature_loot_template` VALUES
(3183,4859, 100, 1, 0, 1, 1), -- Burning Blade Medallion (quest)
(3183,117, 1, 1, 0, 1, 1), -- Tough Jerky
(3183,159, 1, 1, 0, 1, 1), -- Refreshing Spring Water
(3183,24073, 1, 1, 0, 1, 1), -- Junk
(3183,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Remove unique items from reference table 24076
DELETE FROM `reference_loot_template` WHERE `Item` IN
(826, 1211, 1287, 1394, 1926, 1927, 1933, 2088, 4767, 4768, 4771);

-- Add former items from reference table 24076 to their proper NPCs
DELETE FROM `creature_loot_template` WHERE `Item` IN
(826, 1211, 1287, 1394, 1926, 1927, 1933, 2088, 4767, 4768, 4771);

INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`GroupId`) VALUES
(124, 826, 0.1, 0),
(423, 1211, 0.1, 0),
(442, 1287, 0.1, 0),
(171, 1394, 0.1, 0),
(824, 1926, 0.1, 0),
(594, 1927, 0.1, 0),
(619, 1933, 0.1, 0),
(831, 2088, 0.1, 0),
(3578, 4767, 3, 0),
(3270, 4768, 3, 2),
(3270, 4771, 3, 2);

-- Item should only drop from Riverpaw Mongrel (123)
DELETE FROM `reference_loot_template` WHERE `Item`=821;
-- Item should only drop from Sandcrawler  (830)
DELETE FROM `reference_loot_template` WHERE `Item`=2087;
-- Item is from crafting and should never drop
DELETE FROM `reference_loot_template` WHERE `Item`=2300;

-- Add unique drops to appropriate NPCs
DELETE FROM `creature_loot_template` WHERE `Item` IN (821, 2087);
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `ChanceOrQuestChance`) VALUES
('123', '821', '2.5'),
('830', '2087', '2');

-- Kobold Vermin
DELETE FROM `creature_loot_template` WHERE `Entry`=6;
INSERT INTO `creature_loot_template` VALUES
(6,755, 50, 1, 0, 1, 1), -- Melted Candle
(6,4536, 20, 1, 0, 1, 1), -- Shiny Red Apple
(6,159, 10, 1, 0, 1, 1), -- Refreshing Spring Water
(6,24073, 10, 1, 0, 1, 1), -- Junk
(6,11111, 0.5, 1, 0, 1, 1); -- Bags

-- Kobold Worker
DELETE FROM `creature_loot_template` WHERE `Entry`=257;
INSERT INTO `creature_loot_template` VALUES
(257,755, 50, 1, 0, 1, 1), -- Melted Candle
(257,4536, 20, 1, 0, 1, 1), -- Shiny Red Apple
(257,159, 10, 1, 0, 1, 1), -- Refreshing Spring Water
(257,24073, 10, 1, 0, 1, 1), -- Junk
(257,11111, 0.5, 1, 0, 1, 1); -- Bags

-- Kobold Laborer (Also adds unique item missing from game)
DELETE FROM `creature_loot_template` WHERE `Entry`=80;
INSERT INTO `creature_loot_template` VALUES
(80,755, 50, 1, 0, 1, 1), -- Melted Candle
(80,4536, 20, 1, 0, 1, 1), -- Shiny Red Apple
(80,159, 10, 1, 0, 1, 1), -- Refreshing Spring Water
(80,24073, 5, 1, 0, 1, 1), -- Junk
(80,11111, 0.5, 1, 0, 1, 1), -- Bags
(80,2055, 2.5, 1, 0, 1, 1); -- Small Wooden Hammer (Unique)

-- Diseased Young Wolf (Removed drop of level 12-13 green items)
DELETE FROM `creature_loot_template` WHERE `Entry`=299;
INSERT INTO `creature_loot_template` VALUES
(299,4865, 5, 1, 0, 1, 2), -- Ruined Pelt
(299,7073, 5, 1, 0, 1, 2), -- Broken Fang
(299,7074, 5, 1, 0, 1, 2), -- Chipped Claw
(299,50432, 100, 1, 0, 1, 1), -- Diseased Wolf Pelt (Quest)
(299,24073, 1, 1, 0, 1, 1), -- Junk
(299,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Diseased Timber Wolf
DELETE FROM `creature_loot_template` WHERE `Entry`=69;
INSERT INTO `creature_loot_template` VALUES
(69,4865, 5, 1, 0, 1, 2), -- Ruined Pelt
(69,7073, 5, 1, 0, 1, 2), -- Broken Fang
(69,7074, 5, 1, 0, 1, 2), -- Chipped Claw
(69,50432, 100, 1, 0, 1, 1), -- Diseased Wolf Pelt (Quest)
(69,24073, 1, 1, 0, 1, 1), -- Junk
(69,11111, 0.1, 1, 0, 1, 1); -- Bags

-- Defias Thug
DELETE FROM `creature_loot_template` WHERE `Entry`=38;
INSERT INTO `creature_loot_template` VALUES
(38,752, 100, 1, 0, 1, 1), -- Red Burlap Bandana (Quest)
(38,2070, 15, 1, 0, 1, 1), -- Darnassian Bleu
(38,159, 5, 1, 0, 1, 1), -- Refreshing Spring Water
(38,2057, 1.5, 1, 0, 1, 1), -- Pitted Defias Shorsword (Unique)
(38,24073, 10, 1, 0, 1, 1), -- Junk
(38,11111, 0.5, 1, 0, 1, 1); -- Bags




