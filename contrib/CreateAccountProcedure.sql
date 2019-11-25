DELIMITER //
DROP PROCEDURE IF EXISTS CreateAccount;
CREATE PROCEDURE CreateAccount( IN usrName varchar(75), IN pssWd varchar(75), IN rbacGMLevel int(10) )
BEGIN
    SET @shaPass := SHA1(CONCAT(UPPER(usrName),':',UPPER(pssWd)));
    INSERT INTO account(`username`, `sha_pass_hash`, `expansion`) VALUES(usrName, @shaPass, 2);
    SELECT @accID := `id` FROM account WHERE username = `usrName`;
    INSERT INTO account_access(`id`, `gmlevel`, `RealmID`) VALUES(@accId, rbacGMLevel, -1);
END //

DELIMITER ;
