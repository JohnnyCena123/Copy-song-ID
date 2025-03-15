#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude

bool alreadyCalled = false;
bool isSongPreviews = false;

class $modify(MyCustomSongWidget, CustomSongWidget) {
	struct Fields {
		CCMenuItemSpriteExtra* m_copySongIDButton;
	};
	bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
		if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

		if (!m_infoBtn || !m_downloadBtn) return true;

		const auto fields = m_fields.self();

		CCSprite* copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
		copySongIDButtonSprite->setScale(isMusicLibrary ? 0.375f : 0.5f);

		fields->m_copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
		fields->m_copySongIDButton->setPosition({m_downloadBtn->getPositionX() - 31.f, m_downloadBtn->getPositionY() - 5.f});
		if (isMusicLibrary) {
			fields->m_copySongIDButton->setPositionY(fields->m_copySongIDButton->getPositionY() - 2.5f);
			const bool songIsDownloaded = std::filesystem::exists(MusicDownloadManager::sharedState()->pathForSong(m_customSongID));
			if ((!songIsDownloaded || LevelEditorLayer::get()) && isSongPreviews) fields->m_copySongIDButton->setPositionX(fields->m_copySongIDButton->getPositionX() - 37.5f);
		}
		fields->m_copySongIDButton->setID("copy-song-id-button"_spr);

		m_buttonMenu->addChild(fields->m_copySongIDButton);

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