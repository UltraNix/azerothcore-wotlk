UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_hourglass_of_eternity" WHERE `entry`=27840;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=27899;

DELETE FROM `creature_text` WHERE `entry`=27899;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(27899,1,0,'Hey there, $N, don''t be alarmed. It''s me... you... from the future. I''m here to help.',15,0,100,396,0,0,'Future You'),
(27899,2,0,'Head''s up... here they come. I''ll help as much as I can. Let''s just keep them off the hourglass!',15,0,100,396,0,0,'Future You'),
(27899,3,0,'No matter what, you can''t die, because that would mean that I would cease to exist, right? I was here before when i was you. I''m so confused!',15,0,100,0,0,0,'Future You'),
(27899,4,0,'I can''t believe that I used to wear that.',15,0,100,0,0,0,'Future You'),
(27899,5,0,'Sorry, but Chromie said that I couldn''t reveal anything about your future to you. She said that if I did, I would cease to exist.',15,0,100,0,0,0,'Future You'),
(27899,6,0,'Wow, I''d forgotten how inexperienced I used to be.',15,0,100,0,0,0,'Future You'),
(27899,7,0,'Look at you fight; no wonder I turned to drinking.',15,0,100,0,0,0,'Future You'),
(27899,8,0,'What? Am I here alone. We both have a stake at this, you know!',15,0,100,0,0,0,'Future You'),
(27899,9,0,'Listen. I''m not supposed to tell you this, but there''s going to be this party that you''re invited to. Whatever you do, DO NOT DRINK THE PUNCH!',15,0,100,0,0,0,'Future You'),
(27899,10,0,'Wish I could remember how many of the Infinite Dragonflight were going to try to stop you. This fight was so long ago.',15,0,100,0,0,0,'Future You'),
(27899,11,0,'Look, $N, the hourglass has revealed Nozdormu!',15,0,100,25,0,0,'Future You'),
(27899,12,0,'Farewell, $N, Keep us alive and get some better equipment!',15,0,100,0,0,0,'Future You');

DELETE FROM `creature_text` WHERE `entry`=32331;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(32331,1,0,'Whoa! You''re me, but from the future! Hey, my equipment got an upgrade! Cool!',15,0,100,396,0,0,'Past You'),
(32331,2,0,'Here come the Infinites! I''ve got to keep the hourglass safe. Can you help?',15,0,100,396,0,0,'Past You'),
(32331,3,0,'Chromie said that if I don''t do this just right, I might wink out of existence. If I go, then you go!',15,0,100,0,0,0,'Past You'),
(32331,4,0,'I think I''m going to turn to drinking after this.',15,0,100,0,0,0,'Past You'),
(32331,5,0,'I just want you to know that if we get through this alive, I''m making sure that we turn out better than you. No offense.',15,0,100,0,0,0,'Past You'),
(32331,6,0,'Wait a minute! If you''re here, then that means that in the not-so-distant future I''m going to be you helping me? Are we stuck in a time loop?!',15,0,100,0,0,0,'Past You'),
(32331,7,0,'Looks like I''m an underachiever.',15,0,100,0,0,0,'Past You'),
(32331,8,0,'This equipment looks cool and all, but couldn''t we have done a little better? Are you even raiding?',15,0,100,0,0,0,'Past You'),
(32331,9,0,'Listen. I''m not supposed to tell you this, but there''s going to be this party that you''re invited to. Whatever you do, DO NOT DRINK THE PUNCH!',15,0,100,0,0,0,'Past You'),
(32331,10,0,'Wish I could remember how many of the Infinite Dragonflight were going to try to stop you. This fight was so long ago.',15,0,100,0,0,0,'Past You'),
(32331,11,0,'What the heck? Nozdormu is up there!',15,0,100,25,0,0,'Past You'),
(32331,12,0,'I feel like I''m being pulled away through time. Thanks for the help....',15,0,100,0,0,0,'Past You');
