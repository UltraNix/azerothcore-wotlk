ALTER TABLE `pet_aura`
DROP PRIMARY KEY,
ADD PRIMARY KEY (`guid`,`caster_guid`,`spell`,`effect_mask`);