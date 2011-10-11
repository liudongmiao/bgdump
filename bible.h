#ifndef __BIBLE_H__
#define __BIBLE_H__

#define OLD 0x1
#define NEW 0x2
#define ALL 0x3

struct book {
	char *osis;
	char *human;
	int chapter;
	int testament;
};

struct audio {
	char *audio;
	char *human;
	char *language;
	int testament;
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static const struct book books[] = {
	{"Gen", "Genesis", 50, OLD},
	{"Exod", "Exodus", 40, OLD},
	{"Lev", "Leviticus", 27, OLD},
	{"Num", "Numbers", 36, OLD},
	{"Deut", "Deuteronomy", 34, OLD},
	{"Josh", "Joshua", 24, OLD},
	{"Judg", "Judges", 21, OLD},
	{"Ruth", "Ruth", 4, OLD},
	{"1Sam", "1 Samuel", 31, OLD},
	{"2Sam", "2 Samuel", 24, OLD},
	{"1Kgs", "1 Kings", 22, OLD},
	{"2Kgs", "2 Kings", 25, OLD},
	{"1Chr", "1 Chronicles", 29, OLD},
	{"2Chr", "2 Chronicles", 36, OLD},
	{"Ezra", "Ezra", 10, OLD},
	{"Neh", "Nehemiah", 13, OLD},
	{"Esth", "Esther", 10, OLD},
	{"Job", "Job", 42, OLD},
	{"Ps", "Psalm", 150, OLD},
	{"Prov", "Proverbs", 31, OLD},
	{"Eccl", "Ecclesiastes", 12, OLD},
	{"Song", "Song of Solomon", 8, OLD},
	{"Isa", "Isaiah", 66, OLD},
	{"Jer", "Jeremiah", 52, OLD},
	{"Lam", "Lamentations", 5, OLD},
	{"Ezek", "Ezekiel", 48, OLD},
	{"Dan", "Daniel", 12, OLD},
	{"Hos", "Hosea", 14, OLD},
	{"Joel", "Joel", 3, OLD},
	{"Amos", "Amos", 9, OLD},
	{"Obad", "Obadiah", 1, OLD},
	{"Jonah", "Jonah", 4, OLD},
	{"Mic", "Micah", 7, OLD},
	{"Nah", "Nahum", 3, OLD},
	{"Hab", "Habakkuk", 3, OLD},
	{"Zeph", "Zephaniah", 3, OLD},
	{"Hag", "Haggai", 2, OLD},
	{"Zech", "Zechariah", 14, OLD},
	{"Mal", "Malachi", 4, OLD},
	{"Matt", "Matthew", 28, NEW},
	{"Mark", "Mark", 16, NEW},
	{"Luke", "Luke", 24, NEW},
	{"John", "John", 21, NEW},
	{"Acts", "Acts", 28, NEW},
	{"Rom", "Romans", 16, NEW},
	{"1Cor", "1 Corinthians", 16, NEW},
	{"2Cor", "2 Corinthians", 13, NEW},
	{"Gal", "Galatians", 6, NEW},
	{"Eph", "Ephesians", 6, NEW},
	{"Phil", "Philippians", 4, NEW},
	{"Col", "Colossians", 4, NEW},
	{"1Thess", "1 Thessalonians", 5, NEW},
	{"2Thess", "2 Thessalonians", 3, NEW},
	{"1Tim", "1 Timothy", 6, NEW},
	{"2Tim", "2 Timothy", 4, NEW},
	{"Titus", "Titus", 3, NEW},
	{"Phlm", "Philemon", 1, NEW},
	{"Heb", "Hebrews", 13, NEW},
	{"Jas", "James", 5, NEW},
	{"1Pet", "1 Peter", 5, NEW},
	{"2Pet", "2 Peter", 3, NEW},
	{"1John", "1 John", 5, NEW},
	{"2John", "2 John", 1, NEW},
	{"3John", "3 John", 1, NEW},
	{"Jude", "Jude", 1, NEW},
	{"Rev", "Revelation", 22, NEW},
};

static const struct audio audios[] = {
	{"cev-hosanna", "CEV (New Testament) by Hosanna", "English", NEW},
	{"esv-mclean", "ESV by Max McLean", "English", ALL},
	{"esv-laughlin", "ESV (New Testament) by Marquis Laughlin", "English", NEW},
	{"kjv-mclean", "KJV by Max McLean", "English", ALL},
	{"kjv-mims", "KJV (Old Testament) by Paul Mims", "English", OLD},
	{"kjv-dramatized", "KJV by Dramatized", "English", ALL},
	{"nasb-mcconachie", "NASB by Dale McConachie", "English", ALL},
	{"niv-mclean", "NIV by Max McLean", "English", ALL},
	{"niv-dramatized", "NIV by Dramatized", "English", ALL},
	{"niv-voice", "NIV by Charles Taylor", "English", ALL},
	{"tniv-multi", "TNIV by Multiple Readers (Zondervan Multi-Voice Edition)", "English", ALL},
	{"lbla-montoya", "LBLA (New Testament) by Samuel Montoya H", "Español", NEW},
	{"nvi-single", "NVI by Rafael Cruz", "Español", ALL},
	{"reimer-reimer", "REIMER (New Testament) by Elmer Reimer", "Plautdietsch", NEW},
	{"tlm-hodul", "SLO1979 (New Testament) by Joseph Hodul", "Slovenčina", NEW},
	{"tpv-as", "Farsi (New Testament) by Audio Scriptures", "ﻑﺍﺮﺳی", NEW},
};
#endif
