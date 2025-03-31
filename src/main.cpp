#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn || m_customSongID < 1 || m_isRobtopSong) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

		CCMenuItemSpriteExtra* copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
		if (!isMusicLibrary) copySongIDButton->setPosition({m_downloadBtn->getPositionX() + 19.f, m_downloadBtn->getPositionY() + 60.f});
		else copySongIDButton->setPosition({m_downloadBtn->getPositionX() - 20.f, m_downloadBtn->getPositionY() - 20.f});
		copySongIDButton->setID("copy-song-id-button"_spr);

		m_buttonMenu->addChild(copySongIDButton);

		return true;
	}

	void onCopySongID(CCObject* sender) {
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Song ID {} was copied.", m_customSongID))->show();
	}
};