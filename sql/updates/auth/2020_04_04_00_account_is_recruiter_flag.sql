UPDATE `account` SET `account_flags` = `account_flags` | 0x02 WHERE `id` IN (SELECT DISTINCT `recruiter` FROM `account`);
