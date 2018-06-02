#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    // 添加资源搜索路径
    FileUtils::getInstance()->addSearchPath("Resources");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("IORI", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add sprite
    auto sc = SpriteFrameCache::getInstance();
	
	sc->addSpriteFramesWithFile("iori/stand.plist");
	sc->addSpriteFramesWithFile("iori/run.plist");
	auto sprite1 = Sprite::createWithSpriteFrameName("stand_1.png");
	auto sprite2 = Sprite::createWithSpriteFrameName("run_1.png");

	sprite1->setPosition(Vec2(visibleSize.width * 0.25f + origin.x, visibleSize.height / 4 + origin.y));
	this->addChild(sprite1, 0);
	sprite2->setPosition(Vec2(visibleSize.width * 0.75f + origin.x, visibleSize.height / 4 + origin.y));
	this->addChild(sprite2, 0);

	cocos2d::Vector<cocos2d::SpriteFrame *> allFrames1(10);
	for (int i = 1; i < 9; ++i) {
		char name[32] = { 0 };
		snprintf(name, 32, "stand_%d.png", i + 1);
		auto frameName = sc->getSpriteFrameByName(name);
		allFrames1.pushBack(frameName);
	}

	log("add keyboard event listener");
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode kc, Event *ev) {
		log("keypress:%d", kc);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto animation1 = Animation::createWithSpriteFrames(allFrames1);
	animation1->setDelayPerUnit(0.10f);
	animation1->setLoops(-1);
	animation1->setRestoreOriginalFrame(true);
	auto animate1 = Animate::create(animation1);
	//sprite1->setScale(1.8f);
	sprite1->setScale(0.5f);
	sprite1->runAction(animate1);
	
	cocos2d::Vector<cocos2d::SpriteFrame *> allFrames2(10);
	for (int i = 1; i < 8; ++i) {
		char name[32] = { 0 };
		snprintf(name, 32, "run_%d.png", i + 1);
		auto frameName = sc->getSpriteFrameByName(name);
		allFrames2.pushBack(frameName);
	}

	auto animation2 = Animation::createWithSpriteFrames(allFrames2);
	animation2->setDelayPerUnit(0.10f);
	animation2->setLoops(-1);
	animation2->setRestoreOriginalFrame(true);
	auto animate2 = Animate::create(animation2);
	//sprite2->setScale(1.8f);
	sprite2->setScale(0.5f);
	sprite2->runAction(animate2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
