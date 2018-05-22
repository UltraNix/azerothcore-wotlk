/* XT-002 */
UPDATE `creature` SET `position_x` = 880.838135, `position_y` = -11.261101, `position_z` = 409.799011, `orientation` = 3.095640 WHERE `guid` = 136054;

DELETE FROM `waypoint_data` WHERE `id` = 1360540;
INSERT INTO `waypoint_data` VALUES 
(1360540, 0, 884.598694, -12.463288, 409.700714, 3.169458, 0, 0, 0, 100, 0), -- start
(1360540, 1, 890.488098, -73.048302, 409.802460, 4.929536, 7000, 0, 0, 100, 0), -- tantrum lewo
(1360540, 2, 884.186707, -12.205178, 409.702026, 3.108984, 17000, 0, 0, 100, 0), -- srodek dance
(1360540, 3, 887.900513, 55.831417, 409.802551, 1.188685, 7000, 0, 0, 100, 0), -- prawo tantrum
(1360540, 4, 884.598694, -12.463288, 409.700714, 3.169458, 17000, 0, 0, 100, 0); -- koniec

DELETE FROM `waypoint_scripts` WHERE `id` = 1360540;
