#include <Geode/Geode.hpp>

using namespace geode::prelude;


#include <Geode/modify/CustomSongWidget.hpp>
class $modify(MyCustomSongWidget, CustomSongWidget) {
    
    bool init(SongInfoObject* songInfo, CustomSongDelegate* songDelegate, bool showSongSelect, bool showPlayMusic, bool showDownload, bool isRobtopSong, bool unkBool, bool isMusicLibrary, int unk) {
        if (!CustomSongWidget::init(songInfo, songDelegate, showSongSelect, showPlayMusic, showDownload, isRobtopSong, unkBool, isMusicLibrary, unk)) return false;

        m_songIDLabel->setPosition(ccp(-115.f, -27.f));

        auto CopySongIDMenu = CCMenu::create()
        this->addChildAtPosition(CopySongIDMenu, Anchor::BottomLeft, ccp(-131.f, -27.f));
        auto copyButtonSprite = CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png");
        copyButtonSprite->setScale(0.5f);
        auto copyButton = CCMenuItemSpriteExtra::create(copyButtonSprite, this, menu_selector(MyCustomSongWidget::onCopySongID));
        CopySongIDMenu->addChildAtPosition(copyButton, Anchor::Center);


        return true;
    }

    void onCopySongID(CCObject* sender) {
        bool hasSucceeded = clipboard::write(fmt::format("{}", m_customSongID));
        if (hasSucceeded) {
            Notification::create("Successfully copied song ID!", NotificationIcon::Success, 1.f);
        } else {
            Notification::create("Failed to copy song ID.", NotificationIcon::Error, 1.f);
        }
    }
};