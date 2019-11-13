DROP TABLE IF EXISTS `world_relay_addresses`;
CREATE TABLE `world_relay_addresses`
(
	`RelayType` INT(10) UNSIGNED NOT NULL DEFAULT 0,
	`RelayAddress` VARCHAR(60) NOT NULL DEFAULT ""
);

INSERT INTO `world_relay_addresses` VALUES
(1, "https://priv.wherego.pl/hooks/qtbrw6tcm38mbd5xih4uce5ruc"),
(2, "https://priv.wherego.pl/hooks/qtbrw6tcm38mbd5xih4uce5ruc"),
(3, "https://priv.wherego.pl/hooks/bae1b89ki3fgiqt7rqpmcmuxac"),
(4, "https://priv.wherego.pl/hooks/bae1b89ki3fgiqt7rqpmcmuxac"),
(5, "https://priv.wherego.pl/hooks/t5wmb19khp8z7bp5xhtmhm5h8h"),
(6, "https://priv.wherego.pl/hooks/ozzaptko97b8bg9hwz9e3egnih");