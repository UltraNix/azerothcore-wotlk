DELETE FROM `pool_template` WHERE `entry` = 369;
INSERT INTO `pool_template` (`entry`, `max_limit`, `description`) VALUES 
(369, 5, 'Ethereum Jailor');
DELETE FROM `pool_creature` WHERE `pool_entry` = 369;
INSERT INTO `pool_creature` VALUES
(152635, 369, 0, 'Ethereum Jailor'),
(152634, 369, 0, 'Ethereum Jailor'),
(152619, 369, 0, 'Ethereum Jailor'),
(152620, 369, 0, 'Ethereum Jailor'),
(152621, 369, 0, 'Ethereum Jailor'),
(152622, 369, 0, 'Ethereum Jailor'),
(152623, 369, 0, 'Ethereum Jailor'),
(152624, 369, 0, 'Ethereum Jailor'),
(152625, 369, 0, 'Ethereum Jailor'),
(152626, 369, 0, 'Ethereum Jailor'),
(152627, 369, 0, 'Ethereum Jailor'),
(152628, 369, 0, 'Ethereum Jailor'),
(152629, 369, 0, 'Ethereum Jailor'),
(152630, 369, 0, 'Ethereum Jailor'),
(152631, 369, 0, 'Ethereum Jailor'),
(152632, 369, 0, 'Ethereum Jailor'),
(152633, 369, 0, 'Ethereum Jailor'),
(152636, 369, 0, 'Ethereum Jailor'),
(152637, 369, 0, 'Ethereum Jailor'),
(152638, 369, 0, 'Ethereum Jailor'),
(152639, 369, 0, 'Ethereum Jailor');
