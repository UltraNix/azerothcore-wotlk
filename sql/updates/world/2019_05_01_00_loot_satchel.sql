DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 10 AND `SourceGroup` IN (10058, 10059, 10060, 10061);
INSERT INTO `conditions` VALUES 
(10, 10058, 51991, 0, 0, 15, 0, 400, 0, 0, 0, 0, 0, '', 'SOHG: Turbulent Signet only for clothusers'),
(10, 10058, 51969, 0, 0, 15, 0, 400, 0, 0, 0, 0, 0, '', 'SOHG: Enumerated Shoulders only for clothusers'),
(10, 10059, 51961, 0, 0, 15, 0, 1032, 0, 0, 0, 0, 0, '', 'SOHG: Vigorous Shoulderguards only for leatherusers'),
(10, 10059, 51991, 0, 0, 15, 0, 1032, 0, 0, 0, 0, 0, '', 'SOHG: Turbulent Signet only for leatherusers'),
(10, 10060, 51975, 0, 0, 15, 0, 68, 0, 0, 0, 0, 0, '', 'SOHG: Earthbound Shoulders only for mail users'),
(10, 10060, 51991, 0, 0, 15, 0, 68, 0, 0, 0, 0, 0, '', 'SOHG: Turbulent Signet only for Mail users'),
(10, 10061, 51983, 0, 0, 15, 0, 35, 0, 0, 0, 0, 0, '', 'SOHG: Stalwart Shoulderguards only for plate users'),
(10, 10061, 51991, 0, 0, 15, 0, 35, 0, 0, 0, 0, 0, '', 'SOHG: Turbulent Signet only for plate users');

DELETE FROM `reference_loot_template` WHERE `entry` IN (10058, 10059, 10060, 10061);
INSERT INTO `reference_loot_template` VALUES
(10058, 51969, 0, 1, 1, 1, 1),
(10058, 51991, 0, 1, 1, 1, 1),
(10059, 51961, 0, 1, 2, 1, 1),
(10059, 51991, 0, 1, 2, 1, 1),
(10060, 51975, 0, 1, 3, 1, 1),
(10060, 51991, 0, 1, 3, 1, 1),
(10061, 51983, 0, 1, 4, 1, 1),
(10061, 51991, 0, 1, 4, 1, 1);
