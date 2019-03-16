ALTER TABLE log_money
    ADD COLUMN sender_account_name CHAR(32) NOT NULL,
    ADD COLUMN receiver_account_name CHAR(32) NOT NULL
AFTER date;