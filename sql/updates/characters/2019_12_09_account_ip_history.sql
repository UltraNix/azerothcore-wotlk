DROP TABLE IF EXISTS `account_history`;
CREATE TABLE IF NOT EXISTS `account_history`
(
    `AccountId` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    `IpAddress` VARCHAR(35) NOT NULL DEFAULT "127.0.0.1",
    `LoginDate` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (AccountId, IpAddress)
);
