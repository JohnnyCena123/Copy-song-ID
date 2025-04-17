#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CustomSongWidget.hpp>
class $modify(MyCustomSongWidget, CustomSongWidget) {
	static void onModify(auto& self) {
		if (!self.setHookPriorityAfterPost("CustomSongWidget::updateWithMultiAssets", "spaghettdev.songpreview"))
			log::warn("failed to set hook priority for CustomSongWidget::updateWithMultiAssets!");
	}

	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn || m_customSongID < 1) return true;

		auto copySongIDSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
        copySongIDSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);
		auto copySongIDButton = CCMenuItemSpriteExtra::create(
			copySongIDSprite, this, menu_selector(MyCustomSongWidget::onCopySongID)
		);
		copySongIDButton->setPosition({
			m_downloadBtn->getPositionX() + (isMusicLibrary ? 20.f : 21.5f),
			m_downloadBtn->getPositionY() + (isMusicLibrary ? 20.f : 61.5f)
		});

		copySongIDButton->setID("copy-song-id-button"_spr);

		return true;
	}

	void updateWithMultiAssets(gd::string p0, gd::string p1, int p2) {
		CustomSongWidget::updateWithMultiAssets(p0, p1, p2);
		if (!m_infoBtn || m_songs.empty() && m_sfx.empty() || m_playbackBtn->isVisible() || m_isMusicLibrary) return;
		m_infoBtn->setPositionX(m_infoBtn->getPositionX() - 10.f);
	}

	void onCopySongID(CCObject* sender) {
		if (m_customSongID < 1) return Notification::create(fmt::format("Song ID {} is not a valid ID.", m_customSongID), NotificationIcon::Error, 1.f)->show();
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Successfully copied song ID {}!", m_customSongID), NotificationIcon::Success, 1.f)->show();
	}
};

#include <Geode/modify/CustomSFXWidget.hpp>
class $modify(MyCustomSFXWidget, CustomSFXWidget) {
	bool init(SFXInfoObject* sfxInfo, CustomSFXDelegate* sfxDelegate, bool p2, bool p3, bool p4, bool p5, bool p6) {
		if (!CustomSFXWidget::init(sfxInfo, sfxDelegate, p2, p3, p4, p5, p6)) return false;

		if (!sfxInfo || sfxInfo->m_folder || !m_downloadButton || m_sfxID < 1 || m_compactMode) return true;

		auto copySFXIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySFXIDButtonSprite->setScale(0.375f);

		auto copySFXIDButton = CCMenuItemSpriteExtra::create(copySFXIDButtonSprite, this, menu_selector(MyCustomSFXWidget::onCopySFXID));
		copySFXIDButton->setPosition(m_downloadButton->getPosition() + CCPoint(20.f, 20.f));
		copySFXIDButton->setID("copy-sfx-id-button"_spr);

		m_buttonMenu->addChild(copySFXIDButton);

		return true;
	}

	void onCopySFXID(CCObject* sender) {
		if (m_sfxID < 1) return Notification::create(fmt::format("SFX ID {} is not a valid ID.", m_sfxID), NotificationIcon::Error, 2.0f)->show();
		(void) clipboard::write(fmt::format("{}", m_sfxID));
		Notification::create(fmt::format("Successfully copied SFX ID {}!", m_sfxID), NotificationIcon::Success, 1.f)->show();
	}
};