ALTER TABLE account_premium DROP PRIMARY KEY;
ALTER TABLE `account_premium`
  CHANGE RealmID RealmID INT NOT NULL DEFAULT '1',
  CHANGE premium_type premium_type tinyint unsigned NOT NULL DEFAULT '1',
  CHANGE set_date set_date int NOT NULL DEFAULT '0',
  CHANGE unset_date unset_date int NOT NULL DEFAULT '0',
  ADD PRIMARY KEY (id, RealmID, premium_type);
