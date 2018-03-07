UPDATE `creature_template` SET `AIName` = "SmartAI", `spell1` = 0, `spell2` = 0  WHERE `entry` = 30108;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 9891;
INSERT INTO `conditions` VALUES
(15, 9891, 1, 0, 0, 9, 0, 12869, 0, 0, 0, 0, 0, '', 'Show gossip option 1 if player has quest 12869'),
(15, 9891, 0, 0, 0, 9, 0, 12874, 0, 0, 0, 0, 0, '', 'show gossip on quest 12874 taken');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 9891;
INSERT INTO `gossip_menu_option` VALUES
(9891, 0, 0, 'King Stormheart sent me to be tested as a frostborn would. I am ready for my test, Fjorlin', 1, 1, 0, 0, 0, 0, ''),
(9891, 1, 0, 'I am ready to join the battle against the wyrms. Do you have an eagle ready for me, Fjorlin?', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29732, 30108);
INSERT INTO `smart_scripts` VALUES
(29732, 0, 0, 1, 62, 0, 100, 1, 9891, 1, 0, 0, 11, 56411, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Fjorlin Frostbrow - On Gossip Option 1 Selected - Cast \'Forcecast Summon Scripted Eagle\''),
(29732, 0, 1, 0, 61, 0, 100, 1, 9891, 1, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Fjorlin Frostbrow - On Gossip Option 1 Selected - Close Gossip'),
(29732, 0, 2, 3, 62, 0, 100, 1, 9891, 0, 0, 0, 85, 55942, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Fjorlin Frostbrow - On Gossip Option 0 Selected - Invoker Cast \'Summon Battle Eagle\''),
(29732, 0, 3, 0, 61, 0, 100, 1, 9891, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Fjorlin Frostbrow - On Gossip Option 0 Selected - Close Gossip'),
(30108, 0, 0, 0, 27, 0, 100, 1, 0, 0, 0, 0, 53, 1, 30108, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Passenger Boarded - Start Waypoint'),
(30108, 0, 1, 0, 40, 0, 100, 1, 1, 30108, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 1 Reached - Say Line 0'),
(30108, 0, 2, 0, 40, 0, 100, 1, 2, 30108, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 2 Reached - Say Line 1'),
(30108, 0, 3, 0, 40, 0, 100, 1, 4, 30108, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 4 Reached - Say Line 2'),
(30108, 0, 4, 0, 40, 0, 100, 1, 6, 30108, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 6 Reached - Say Line 3'),
(30108, 0, 5, 0, 40, 0, 100, 1, 8, 30108, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 8 Reached - Say Line 4'),
(30108, 0, 6, 0, 40, 0, 100, 1, 10, 30108, 0, 0, 1, 5, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 10 Reached - Say Line 5'),
(30108, 0, 7, 0, 40, 0, 100, 1, 12, 30108, 0, 0, 1, 6, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 12 Reached - Say Line 6'),
(30108, 0, 8, 0, 40, 0, 100, 1, 14, 30108, 0, 0, 1, 7, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 14 Reached - Say Line 7'),
(30108, 0, 9, 0, 40, 0, 100, 1, 16, 30108, 0, 0, 1, 8, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 16 Reached - Say Line 8'),
(30108, 0, 10, 0, 40, 0, 100, 1, 18, 30108, 0, 0, 1, 9, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 18 Reached - Say Line 9'),
(30108, 0, 12, 0, 40, 0, 100, 1, 22, 30108, 0, 0, 1, 10, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 22 Reached - Say Line 10'),
(30108, 0, 13, 0, 40, 0, 100, 1, 24, 30108, 0, 0, 1, 11, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 24 Reached - Say Line 11'),
(30108, 0, 14, 0, 40, 0, 100, 1, 25, 30108, 0, 0, 1, 12, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 25 Reached - Say Line 12'),
(30108, 0, 15, 0, 40, 0, 100, 1, 26, 30108, 0, 0, 1, 13, 0, 0, 0, 0, 0, 19, 30401, 10, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 26 Reached - Say Line 13'),
(30108, 0, 16, 0, 40, 0, 100, 1, 28, 30108, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stormcrest Eagle - On Waypoint 28 Reached - Despawn Instant');

DELETE FROM `waypoints` WHERE `entry` = 30108;
INSERT INTO `waypoints` VALUES
(30108, 1, 6586.2, -294.997, 989.82, 'Eagle'),
(30108, 2, 6519.83, -384.722, 994.117, 'Eagle'),
(30108, 3, 6519.97, -524.613, 986.315, 'Eagle'),
(30108, 4, 6582.99, -676.868, 973.055, 'Eagle'),
(30108, 5, 6687.48, -733.39, 964.698, 'Eagle'),
(30108, 6, 6855.16, -744.853, 961.192, 'Eagle'),
(30108, 7, 6994.31, -760.115, 959.543, 'Eagle'),
(30108, 8, 7119.54, -785.058, 970.552, 'Eagle'),
(30108, 9, 7245.46, -832.456, 982.112, 'Eagle'),
(30108, 10, 7372.43, -884.75, 992.92, 'Eagle'),
(30108, 11, 7451.38, -912.608, 999.791, 'Eagle'),
(30108, 12, 7550.54, -946.482, 1008.39, 'Eagle'),
(30108, 13, 7627.06, -969.296, 1025.31, 'Eagle'),
(30108, 14, 7701.49, -991.429, 1041.78, 'Eagle'),
(30108, 15, 7767.2, -1011.33, 1056.82, 'Eagle'),
(30108, 16, 7837.09, -1032.49, 1072.82, 'Eagle'),
(30108, 17, 7898.99, -1053.29, 1090.37, 'Eagle'),
(30108, 18, 7944.64, -1070.18, 1112.88, 'Eagle'),
(30108, 19, 7995.38, -1111.07, 1138.38, 'Eagle'),
(30108, 20, 8075.38, -1184.51, 1180.87, 'Eagle'),
(30108, 21, 8133, -1259.6, 1214.29, 'Eagle'),
(30108, 22, 8221.79, -1381.51, 1271, 'Eagle'),
(30108, 23, 8300.22, -1485.87, 1321.57, 'Eagle'),
(30108, 24, 8367.07, -1592.58, 1382.36, 'Eagle'),
(30108, 25, 8414.48, -1701.68, 1449.03, 'Eagle'),
(30108, 26, 8456.78, -1783.6, 1462.78, 'Eagle'),
(30108, 27, 8482.2, -1838.47, 1470, 'Eagle'),
(30108, 28, 8526.7, -1956.21, 1473.59, 'Eagle');

DELETE FROM `vehicle_template_accessory` WHERE `entry` = 30108;
INSERT INTO `vehicle_template_accessory` VALUES
(30108, 30401, 1, 1, 'Stormcrest Eagle', 8, 0);
