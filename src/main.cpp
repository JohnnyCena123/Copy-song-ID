#include <Geode/Geode.hpp>

using namespace geode::prelude;

bool alreadyCalled = false;
bool isSongPreviews = false;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

    }
};

class $modify(DoesSongPreviewsExist, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		if (alreadyCalled) return true;
		isSongPreviews = Loader::get()->isModLoaded("spaghettdev.songpreview");
		alreadyCalled = true;
		return true;
	}
};