#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

CCSprite *RobertTopala = nullptr;

class $modify(PlayerObject) {

  void incrementJumps() {
    PlayerObject::incrementJumps();

    // Do nothing if PlayLayer doesnt exist
    if (!GameManager::sharedState()->getPlayLayer())
      return;

    // Create robert if it doesn't exist in scene
    if (!this->getChildByID("robert-topala")) {
      RobertTopala = CCSprite::create("RobertTopala.png"_spr);
	    RobertTopala->setID("robert-topala");
      CCSize winSize = CCDirector::get()->getWinSize();

      RobertTopala->setPosition({winSize.width / 2, winSize.height / 2});
      RobertTopala->setScale(3);
      CCDirector::get()->getRunningScene()->addChild(RobertTopala, 100);
    }

    GameSoundManager::get()->playEffect("vine-boom.mp3"_spr, 1, 0, 1);

    // If action is running stop it
    if (RobertTopala->getActionByTag(1)) {
      RobertTopala->stopActionByTag(1);
    }

	  // Ensure opacity is 255
    RobertTopala->setOpacity(255);
    // Fade out robert
    RobertTopala->runAction(CCFadeOut::create(1.0))->setTag(1);
  }
};
