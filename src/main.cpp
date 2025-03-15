#include <Geode/Geode.hpp>

using namespace geode::prelude;


#include <Geode/modify/CustomSongWidget.hpp>
class $modify(MyCustomSongWidget, CustomSongWidget) {

    struct Fields {
        bool m_hasInitialized;
        CCMenu* m_copySongIDMenu;
        CCMenuItemSpriteExtra* m_copySongIDButton;
    };
    
    bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
        if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

        m_fields->m_copySongIDMenu = CCMenu::create();
        auto copySongIDButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");

        if (isMusicLibrary) {
            copySongIDButtonSprite->setScale(0.375f);
        } else {
            copySongIDButtonSprite->setScale(0.5f);
        }

        positionIDLabel();

        m_fields->m_copySongIDButton = CCMenuItemSpriteExtra::create(copySongIDButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
        m_fields->m_copySongIDMenu->addChildAtPosition(m_fields->m_copySongIDButton, Anchor::Center);

        m_fields->m_copySongIDButton->setID("copy-song-id-button");
        m_fields->m_copySongIDMenu->setID("copy-song-id-menu");

        m_fields->m_hasInitialized = true;

        return true;
    }

    void positionInfoObjects() {
        CustomSongWidget::positionInfoObjects();
        positionIDLabel();
    }

    void loadSongInfoFinished(SongInfoObject* p0) {
        CustomSongWidget::loadSongInfoFinished(p0);
        positionIDLabel();
    }

    void loadSongInfoFailed(int p0, GJSongError p1) {
        CustomSongWidget::loadSongInfoFailed(p0, p1);
        positionIDLabel();
    }

    void downloadSongFinished(int p0) {
        CustomSongWidget::downloadSongFinished(p0);
        positionIDLabel();
    }

    void downloadSongFailed(int p0, GJSongError p1) {
        CustomSongWidget::downloadSongFailed(p0, p1);
        positionIDLabel();
    }

    void downloadSFXFinished(int p0) {
        CustomSongWidget::downloadSFXFinished(p0);
        positionIDLabel();
    }

    void downloadSFXFailed(int p0, GJSongError p1) {
        CustomSongWidget::downloadSFXFailed(p0, p1);
        positionIDLabel();
    }

    void musicActionFinished(GJMusicAction p0) {
        CustomSongWidget::musicActionFinished(p0);
        positionIDLabel();
    }

    void musicActionFailed(GJMusicAction p0) {
        CustomSongWidget::musicActionFailed(p0);
        positionIDLabel();
    }

    void FLAlert_Clicked(FLAlertLayer* p0, bool p1) {
        CustomSongWidget::FLAlert_Clicked(p0, p1);
        positionIDLabel();
    }

    void songStateChanged() {
        CustomSongWidget::songStateChanged();
        positionIDLabel();
    }

    void positionIDLabel() {
        if (!m_fields->m_hasInitialized) return;

        if (m_isMusicLibrary) {
            m_fields->m_copySongIDMenu->setPosition(ccp(-142.f, -10.f));
            m_songIDLabel->setPosition(ccp(-131.f, -10.f));
        } else {
            m_fields->m_copySongIDMenu->setPosition(ccp(-131.f, -27.f));
            m_songIDLabel->setPosition(ccp(-115.f, -27.f));
        }
    }

    void onCopySongID(CCObject* sender) {
        bool hasSucceeded = clipboard::write(fmt::format("{}", m_customSongID));
        if (hasSucceeded) {
            Notification::create("Successfully copied song ID!", NotificationIcon::Success, 1.f)->show();
        } else {
            Notification::create("Failed to copy song ID.", NotificationIcon::Error, 1.f)->show();
        }
    }
};
