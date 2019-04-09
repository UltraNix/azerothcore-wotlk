SET @FOUNTAIN:= 151164;

UPDATE `gameobject` SET `state` = 0 WHERE `guid` = @FOUNTAIN;

SET @TEXT:= "Dedicated to those that fell to the Scourge during the war in the frozen wastes.                     
$b                Guild <Synthesis> 21.03.2019$B                        
$B                        Amaroczek    
$B                        Chriz    
$B                        Daney    
$B                        Demola    
$B                        Durotos    
$B                        Ernine    
$B                        Gurcina    
$B                        Htb    
$B                        Keloif    
$B                        Kluseq    
$B                        Lamaxgodx    
$B                        Leinard    
$B                        Nestoo    
$B                        Ojczysty    
$B                        Oriihara    
$B                        Pozdrawiam    
$B                        Randomdog    
$B                        Rourek    
$B                        Senatorix    
$B                        Skay    
$B                        Stgxgodx    
$B                        Takpanie    
$B                        Vanquis    
$B                        Vraelxgodx    
$B                        Zlyy";

UPDATE `page_text` SET `text` = @TEXT WHERE `entry` = 3605;