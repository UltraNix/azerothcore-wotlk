ALTER TABLE `petition`
    CHANGE `petitionguid` `petitionItemGuid` INT(10) UNSIGNED DEFAULT '1',
    ADD `petitionGUID` INT(10) UNSIGNED NOT NULL DEFAULT '1';
