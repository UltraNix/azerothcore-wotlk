DELETE FROM `world_relay_json_strings` WHERE `RelayType` = 7;
INSERT INTO `world_relay_json_strings` (`RelayType`, `JsonString`) VALUES
(7, '{{\r\n  "text": "{}",\r\n  "username": "{}"\r\n}}');

DELETE FROM `world_relay_addresses` WHERE `RelayType` = 7;
INSERT INTO `world_relay_addresses` (`RelayType`, `RelayAddress`) VALUES
(7, 'https://priv.wherego.pl/hooks/477tx5uez7bqubyy8j7fo7iuth');
