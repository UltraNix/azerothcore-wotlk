-- Meathook
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (52696,52666);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES
(52696,52696,58823),
(52666,52666,58824);
-- Salramm the Fleshcrafter
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_salramm_steal_flesh';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(52708,'spell_salramm_steal_flesh');
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (52480,57725);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES
(52480,52480,58825),
(57725,57725,58827);
-- Chrono-Lord Epoch
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (52737,52771);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES
(52737,52737,58829),
(52771,52771,58830);
-- Mal'ganis
DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (52720,52722,52721);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES
(52720,52720,58852),
(52722,52722,58850),
(52721,52721,58849);