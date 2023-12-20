DROP TABLE IF EXISTS `custom_solocraft_character_stats`;
CREATE TABLE IF NOT EXISTS `custom_solocraft_character_stats` (
  `GUID` tinyint(3) unsigned NOT NULL,
  `Difficulty` float NOT NULL,
  `GroupSize` int(11) NOT NULL,
  `SpellPower` int(10) unsigned NOT NULL DEFAULT "0",
  `Stats` float NOT NULL DEFAULT "100",
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
