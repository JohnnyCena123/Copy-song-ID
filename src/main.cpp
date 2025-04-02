#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn || m_customSongID < 1 || isRobtopSong) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

		CCMenuItemSpriteExtra* copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
		copySongIDButton->setPositionX(m_downloadBtn->getPositionX() + (isMusicLibrary ? 20.f : 25.f));
		copySongIDButton->setPositionY(m_downloadBtn->getPositionY() + (isMusicLibrary ? 20.f : 60.f));
		copySongIDButton->setID("copy-song-id-button"_spr);

		m_buttonMenu->addChild(copySongIDButton);

		return true;
	}

	void onCopySongID(CCObject* sender) {
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Song ID {} was copied.", m_customSongID))->show();
	}
};