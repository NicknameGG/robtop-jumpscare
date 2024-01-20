#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

CCSprite *RobertTopala = nullptr;

class $modify( PlayerObject ) {

  TodoReturn pushButton(PlayerButton p0) {
    PlayerObject::pushButton(p0);

    // Do nothing if PlayLayer doesnt exist
    if (!GameManager::sharedState()->getPlayLayer())
      return;

    const auto runningScene = CCDirector::get()->getRunningScene();

    // Create robert if it doesn't exist in scene
    if (!runningScene->getChildByID("robert-topala")) {
      RobertTopala = CCSprite::create("RobertTopala.png"_spr);
	    RobertTopala->setID("robert-topala");
      CCSize winSize = CCDirector::get()->getWinSize();

      RobertTopala->setPosition({winSize.width / 2, winSize.height / 2});
      runningScene->addChild(RobertTopala, 100);
    }

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
};
