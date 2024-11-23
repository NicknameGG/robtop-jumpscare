#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

CCSprite* RobertTopala = nullptr;
bool isHolding = false;

class $modify(PlayerObject) {
  void jumpscare() {
    // Check if randomizing is enabled
    bool randomizeOption = Mod::get()->getSettingValue<bool>("randomize-jumpscare");
    double randomizeOptionChance = Mod::get()->getSettingValue<double>("randomize-jumpscare-chance");

    // if randomize is turned on then there is certain percent chance of the jumpscare
    float randPercent = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100;

    if (randomizeOption && (randPercent > randomizeOptionChance))
      return;

    FMODAudioEngine::sharedEngine()->playEffect("vine-boom.mp3"_spr);

    // If action is running stop it
    if (RobertTopala->getActionByTag(1)) {
      RobertTopala->stopActionByTag(1);
    }

    // Ensure opacity is 255
    RobertTopala->setOpacity(255);
    // Fade out robert
    RobertTopala->runAction(CCFadeOut::create(1.0))->setTag(1);
  }

  /*void playerDestroyed(bool p0) {
    PlayerObject::playerDestroyed(p0);
    isHolding = false;
  }*/

  void playerDestroyed(bool p0) {
    PlayerObject::playerDestroyed(p0);
    isHolding = false;
  }

  bool releaseButton(PlayerButton p0) {
    bool ret = PlayerObject::releaseButton(p0);

    if (p0 != PlayerButton::Jump)
      return ret;

    isHolding = false;
    return false;
  }

  void incrementJumps() {
    // Check if randomizing is enabled
    auto randomizeOption = Mod::get()->getSettingValue<bool>("randomize-jumpscare");

    // increment jump jumpscares only happen if randomization is disabled.
    if (randomizeOption == false) {
      // Check if robert exists and if the user is holding jump (Works only for the cube)
      const auto runningScene = CCDirector::get()->getRunningScene();
      if (runningScene->getChildByID("robert-topala") && isHolding) {
        this->jumpscare();
      }
    }

    PlayerObject::incrementJumps();
  }

  bool pushButton(PlayerButton p0) {
    bool ret = PlayerObject::pushButton(p0);

    if (p0 != PlayerButton::Jump)
      return ret;

    isHolding = true;

    // Do nothing if PlayLayer doesnt exist
    if (!GameManager::sharedState()->getPlayLayer())
      return ret;

    const auto runningScene = CCDirector::get()->getRunningScene();

    // Create robert if it doesn't exist in scene
    if (!runningScene->getChildByID("robert-topala")) {
      RobertTopala = CCSprite::create("RobertTopala.png"_spr);
      RobertTopala->setID("robert-topala");
      CCSize winSize = CCDirector::get()->getWinSize();

      float scaleRatio = (winSize.height / RobertTopala->getContentSize().height);

      // Scale robert to fit screen
      RobertTopala->setScaleX(scaleRatio);
      RobertTopala->setScaleY(scaleRatio);

      // Center the robert
      RobertTopala->setPosition({ winSize.width / 2, winSize.height / 2 });
      runningScene->addChild(RobertTopala, 100);

      // Set robert opacity to 0
      RobertTopala->setOpacity(0);
    }

    this->jumpscare();
    return false;
  }
};
