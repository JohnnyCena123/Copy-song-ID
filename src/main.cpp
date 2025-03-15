#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude;

bool alreadyCalled = false;
bool isSongPreviews = false;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_downloadBtn) return true;

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

		copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
		copySongIDButton->setPosition({m_downloadBtn->getPositionX() - 31.f, m_downloadBtn->getPositionY() - 5.f});
		if (isMusicLibrary) {
			copySongIDButton->setPositionY(copySongIDButton->getPositionY() - 2.5f);
			const bool songIsDownloaded = std::filesystem::exists(static_cast<std::string>(MusicDownloadManager::sharedState()->pathForSong(m_customSongID)));
			if ((!songIsDownloaded || LevelEditorLayer::get()) && isSongPreviews) copySongIDButton->setPositionX(copySongIDButton->getPositionX() - 37.5f);
		}
		copySongIDButton->setID("copy-song-id-button"_spr);

		m_buttonMenu->addChild(copySongIDButton);

		return true;
	}

	void onCopySongID(CCObject* sender) {
		(void) clipboard::write(fmt::format("{}", m_customSongID));
		Notification::create(fmt::format("Song ID {} was copied.", m_customSongID))->show();
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