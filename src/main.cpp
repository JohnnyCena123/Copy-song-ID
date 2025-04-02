#include <Geode/modify/CustomSongWidget.hpp>
#include <Geode/modify/CustomSFXWidget.hpp>

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
		if (m_customSongID < 1 || m_isRobtopSong) return Notification::create(fmt::format("Song ID {} is not a valid ID.", m_customSongID), NotificationIcon::Error, 2.0f)->show();
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Song ID {} was copied.", m_customSongID))->show();
	}
};

#ifndef GEODE_IS_IOS
class $modify(MyCustomSFXWidget, CustomSFXWidget) {
	bool init(SFXInfoObject* sfxInfo, CustomSFXDelegate* sfxDelegate, bool p2, bool p3, bool p4, bool p5, bool p6) {
		if (!CustomSFXWidget::init(sfxInfo, sfxDelegate, p2, p3, p4, p5, p6)) return false;

		if (!sfxInfo || sfxInfo->m_folder || !m_downloadButton || m_sfxID < 1 || m_compactMode) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(0.375f);

		CCMenuItemSpriteExtra* copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSFXWidget::onCopySongID));
		copySongIDButton->setPosition(m_downloadButton->getPosition() + ccp(20.f, 20.f));
		copySongIDButton->setID("copy-sfx-id-button"_spr);

		m_buttonMenu->addChild(copySongIDButton);

		return true;
	}

	void onCopySongID(CCObject* sender) {
		if (m_sfxID < 1) return Notification::create(fmt::format("SFX ID {} is not a valid ID.", m_sfxID), NotificationIcon::Error, 2.0f)->show();
		(void) clipboard::write(fmt::format("{} [SFX]", m_sfxID));
		Notification::create(fmt::format("SFX ID {} was copied.", m_sfxID))->show();
	}
};
#endif