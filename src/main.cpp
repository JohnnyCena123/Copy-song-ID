#include <Geode/modify/CustomSongWidget.hpp>
#include <Geode/modify/CustomSFXWidget.hpp>

using namespace geode::prelude;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	static void onModify(auto& self) {
		(void) self.setHookPriorityAfterPost("CustomSongWidget::updateWithMultiAssets", "spaghettdev.songpreview");
	}

	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn || m_customSongID < 1 || isRobtopSong) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

		CCMenuItemSpriteExtra* copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
		copySongIDButton->setPositionX(m_downloadBtn->getPositionX() + (isMusicLibrary ? 20.f : 21.5f));
		copySongIDButton->setPositionY(m_downloadBtn->getPositionY() + (isMusicLibrary ? 20.f : 61.5f));
		copySongIDButton->setID("copy-song"_spr);

		m_buttonMenu->addChild(copySongIDButton);

		return true;
	}

	void updateWithMultiAssets(gd::string p0, gd::string p1, int p2) {
		CustomSongWidget::updateWithMultiAssets(p0, p1, p2);
		if (!m_infoBtn || m_songs.empty() && m_sfx.empty() || m_playbackBtn->isVisible() || m_isMusicLibrary) return;
		m_infoBtn->setPositionX(m_infoBtn->getPositionX() - 5.f);
	}

	void onCopySongID(CCObject* sender) {
		if (m_customSongID < 1 || m_isRobtopSong) return Notification::create(fmt::format("Song ID {} is not a valid ID.", m_customSongID), NotificationIcon::Error, 2.0f)->show();
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Song ID {} was copied.", m_customSongID))->show();
	}
};

class $modify(MyCustomSFXWidget, CustomSFXWidget) {
	bool init(SFXInfoObject* sfxInfo, CustomSFXDelegate* sfxDelegate, bool p2, bool p3, bool p4, bool p5, bool p6) {
		if (!CustomSFXWidget::init(sfxInfo, sfxDelegate, p2, p3, p4, p5, p6)) return false;

		if (!sfxInfo || sfxInfo->m_folder || !m_downloadButton || m_sfxID < 1 || m_compactMode) return true;

		CCSprite* copySFXIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySFXIDButtonSprite->setScale(0.375f);

		CCMenuItemSpriteExtra* copySFXIDButton = CCMenuItemSpriteExtra::create(copySFXIDButtonSprite, this, menu_selector(MyCustomSFXWidget::onCopySFXID));
		copySFXIDButton->setPosition(m_downloadButton->getPosition() + ccp(20.f, 20.f));
		copySFXIDButton->setID("copy-sfx"_spr);

		m_buttonMenu->addChild(copySFXIDButton);

		return true;
	}

	void onCopySFXID(CCObject* sender) {
		if (m_sfxID < 1) return Notification::create(fmt::format("SFX ID {} is not a valid ID.", m_sfxID), NotificationIcon::Error, 2.0f)->show();
		(void) clipboard::write(fmt::format("{} [SFX]", m_sfxID));
		Notification::create(fmt::format("SFX ID {} was copied.", m_sfxID))->show();
	}
};