#ifndef DECKMANAGER_H
#define DECKMANAGER_H

#include "config.h"
#include "client_card.h"
#include <unordered_map>
#include <vector>
#include <sstream>

namespace ygo {

struct LFList {
	unsigned int hash;
	std::wstring listName;
	std::unordered_map<int, int> content;
};
struct Deck {
	std::vector<code_pointer> main;
	std::vector<code_pointer> extra;
	std::vector<code_pointer> side;
	std::vector<code_pointer> Gcheck;
	uint16 deckcountry = 0;
	int trigger_card = 0;
	int trigger_heal =0;
	int trigger_crit =0;
	int trigger_draw =0;
	int trigger_front = 0;
	bool monster_marble = false;
	bool monster_marble_dragon = false;
	bool disaster = false;
	bool trigger_over = false;
	bool regalis_piece = false;
	Deck() {}
	Deck(const Deck& ndeck) {
		main = ndeck.main;
		extra = ndeck.extra;
		side = ndeck.side;
	}
	void clear() {
		main.clear();
		extra.clear();
		side.clear();
		trigger_card = 0;
		trigger_heal = 0;
		trigger_crit = 0;
		trigger_draw = 0;
		trigger_front = 0;
		monster_marble = false;
		monster_marble_dragon = false;
		disaster = false;
		trigger_over = false;
		regalis_piece = false;
		deckcountry = 0;
	}
};

class DeckManager {
public:
	Deck current_deck;
	std::vector<LFList> _lfList;

	static char deckBuffer[0x10000];

	void LoadLFListSingle(const char* path);
	void LoadLFList();
	const wchar_t* GetLFListName(int lfhash);
	const std::unordered_map<int, int>* GetLFListContent(int lfhash);
	int CheckDeck(Deck& deck, int lfhash, int rule);
	int LoadDeck(Deck& deck, int* dbuf, int mainc,int extrac, int sidec, bool is_packlist = false);
	bool LoadSide(Deck& deck, int* dbuf, int mainc, int sidec);
	void GetCategoryPath(wchar_t* ret, int index, const wchar_t* text);
	void GetDeckFile(wchar_t* ret, irr::gui::IGUIComboBox* cbCategory, irr::gui::IGUIComboBox* cbDeck);
	bool LoadDeck(irr::gui::IGUIComboBox* cbCategory, irr::gui::IGUIComboBox* cbDeck);
	FILE* OpenDeckFile(const wchar_t* file, const char* mode);
	IReadFile* OpenDeckReader(const wchar_t* file);
	bool CheckCard(Deck& deck, CardDataC cd);
	bool CheckCardEx(Deck& deck, CardDataC cd);
	bool LoadDeck(const wchar_t* file, bool is_packlist = false);
	bool LoadDeck(std::istringstream* deckStream, bool is_packlist = false);
	bool SaveDeck(Deck& deck, const wchar_t* file);
	bool DeleteDeck(const wchar_t* file);
	bool CreateCategory(const wchar_t* name);
	bool RenameCategory(const wchar_t* oldname, const wchar_t* newname);
	bool DeleteCategory(const wchar_t* name);
};

extern DeckManager deckManager;

}

#endif //DECKMANAGER_H
