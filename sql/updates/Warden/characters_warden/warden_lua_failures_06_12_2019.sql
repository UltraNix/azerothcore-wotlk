ALTER TABLE `warden_lua_failures`
ADD COLUMN `CallStack` VARCHAR(255) NOT NULL DEFAULT "" AFTER FailureDate;
