DROP TABLE IF EXISTS `log_trade`;
CREATE TABLE `log_trade` (
    `time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `realm_id` INT(10) NOT NULL,
    `sender_acc` INT(11) UNSIGNED NOT NULL,
    `sender_guid` INT(11) UNSIGNED NOT NULL,
    `sender_name` CHAR(32) CHARACTER SET utf8 NOT NULL,
    `sender_ip` CHAR(32) CHARACTER SET utf8 NOT NULL,
    `receiver_acc` INT(11) UNSIGNED NOT NULL,
    `receiver_guid` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    `receiver_name` CHAR(32) CHARACTER SET utf8 NOT NULL,
    `receiver_ip` CHAR(32) CHARACTER SET utf8 NOT NULL DEFAULT '',
    `item_guid` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    `item_entry` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    `item_count` INT(11) UNSIGNED NOT NULL DEFAULT 0,
    `topic` CHAR(255) CHARACTER SET utf8 NOT NULL
) ENGINE=INNODB COMMENT='Log trade';