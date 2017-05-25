DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 785;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 786;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 787;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 788;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 789;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 790;
DELETE FROM `warden_checks` WHERE `warden_checks`.`id` = 791;

INSERT INTO `warden_checks` (`id`, `type`, `data`, `str`, `address`, `length`, `result`, `comment`) VALUES
(785, 243, '', '', 9995315, 5, '75440FB75E', 'Multi-Jump Patch'),
(786, 217, '', 'WPESPY.DLL', 0, 0, '', 'WPE PRO - injected dll'),
(787, 217, '', 'ICANHAZSPEED.DLL', 0, 0, '', 'ICanHazSpeed - Injected DLL'),
(788, 217, '', 'MAELSTROM_KEYS_HOOK.', 0, 0, '', 'Maelstrom - Injected DLL'),
(789, 217, '', 'MAELSTROM_MESS_HOOK.', 0, 0, '', 'Maelstrom - Injected DLL'),
(790, 217, NULL, 'SETPRIV.DLL', 0, 0, NULL, 'HideToolz - Injected DLL'),
(791, 217, NULL, 'SPEEDHACK.DLL', 0, 0, NULL, 'Cheat Engine - Injected DLL');