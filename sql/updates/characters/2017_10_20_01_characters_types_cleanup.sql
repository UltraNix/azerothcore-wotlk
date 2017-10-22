ALTER TABLE `character_queststatus_seasonal` CHANGE `event` `event` SMALLINT( 5 ) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Event Identifier';
ALTER TABLE `game_event_condition_save` CHANGE `eventEntry` `eventEntry` SMALLINT( 5 ) UNSIGNED NOT NULL ;
ALTER TABLE `game_event_save` CHANGE `eventEntry` `eventEntry` SMALLINT( 5 ) UNSIGNED NOT NULL ;
ALTER TABLE `character_brew_of_the_month` CHANGE `lastEventId` `lastEventId` SMALLINT( 5 ) UNSIGNED NOT NULL DEFAULT '0';