#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Button.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/SliderNode.hpp>
#include <Geode/ui/ColorPickPopup.hpp>
#include "Utilities.hpp"
#include "Settings.hpp"

using namespace geode::prelude;

// To whoever may be reading this, I apologize in advance. The UI was quite complex, so I built it all manually.
// FancyPopup::init() ends at line 1,189.
// Callback functions end at line 1,961.

class FancyPopup : public Popup {
protected:
	int CurrentPage = 1;
	bool runHue = false;
	float hue = 0.f;
	CCLabelBMFont* m_rgbfslbl;
	// page 1
	CCMenu* m_togglesP1Page1;
	CCMenu* m_group1P1Page1;
	CCMenu* m_group2P1Page1;
	CCMenu* m_group3P1Page1;
	CCMenu* m_togglesP2Page1;
	CCMenu* m_group1P2Page1;
	CCMenu* m_group2P2Page1;
	CCMenu* m_group3P2Page1;
	// page 2
	CCMenu* m_togglesP1Page2;
	CCMenu* m_group1P1Page2;
	CCMenu* m_togglesP2Page2;
	CCMenu* m_group1P2Page2;
	CCMenu* m_toggleSlidersMenu;
	CCMenu* m_streakMiscToggles;
	SliderNode* m_streakFadeSlider;
	SliderNode* m_streakStrokeSlider;
	SliderNode* m_streakRepeatSlider;
	CCLabelBMFont* m_streakFadeNumberLabel;
	CCLabelBMFont* m_streakStrokeNumberLabel;
	CCLabelBMFont* m_streakRepeatNumberLabel;


	/*--------------------------------
	Section 1: Big-Ahh init() Function
	--------------------------------*/


	bool init() {
		if (!Popup::init(360.f, 280.f, getThemeSpriteName())) return false;
		this->setTitle("Fancy Player Configuration");
		this->setID("fancy-popup");


		/*----
		Layers
		----*/


		auto page1Layer = CCLayer::create();
		page1Layer->setID("page-1-layer");
		page1Layer->setContentSize({360.f, 280.f});
		m_mainLayer->addChild(page1Layer, 1);

		auto page2Layer = CCLayer::create();
		page2Layer->setID("page-2-layer");
		page2Layer->setContentSize({360.f, 280.f});
		m_mainLayer->addChild(page2Layer, 1);

		auto page3Layer = CCLayer::create();
		page3Layer->setID("page-3-layer");
		page3Layer->setContentSize({360.f, 280.f});
		m_mainLayer->addChild(page3Layer, 1);


		/*------
		9 Slices
		------*/


		// main
		auto bgGlobal = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgGlobal->setPosition({180.f, 146.f});
		bgGlobal->setColor(getThemePrimaryColor());
		bgGlobal->setContentSize({280.f, 157.f});
		m_mainLayer->addChild(bgGlobal);

		// page 1
		auto bgP1RGB1 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP1RGB1->setPosition({90.f, 184.f});
		bgP1RGB1->setColor(getThemeSecondaryColor());
		bgP1RGB1->setContentSize({90.f, 60.f});
		bgP1RGB1->setID("rgb-bg1-p1");
		page1Layer->addChild(bgP1RGB1);

		auto bgP1RGB2 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP1RGB2->setPosition({90.f, 129.f});
		bgP1RGB2->setColor(getThemeSecondaryColor());
		bgP1RGB2->setContentSize({90.f, 30.f});
		bgP1RGB2->setID("rgb-bg2-p1");
		page1Layer->addChild(bgP1RGB2);

		auto bgP1RGB3 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP1RGB3->setPosition({90.f, 89.f});
		bgP1RGB3->setColor(getThemeSecondaryColor());
		bgP1RGB3->setContentSize({90.f, 30.f});
		bgP1RGB3->setID("rgb-bg3-p1");
		page1Layer->addChild(bgP1RGB3);

		auto bgP2RGB1 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP2RGB1->setPosition({270.f, 184.f});
		bgP2RGB1->setColor(getThemeSecondaryColor());
		bgP2RGB1->setContentSize({90.f, 60.f});
		bgP2RGB1->setID("rgb-bg1-p2");
		page1Layer->addChild(bgP2RGB1);

		auto bgP2RGB2 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP2RGB2->setPosition({270.f, 129.f});
		bgP2RGB2->setColor(getThemeSecondaryColor());
		bgP2RGB2->setContentSize({90.f, 30.f});
		bgP2RGB2->setID("rgb-bg2-p2");
		page1Layer->addChild(bgP2RGB2);

		auto bgP2RGB3 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP2RGB3->setPosition({270.f, 89.f});
		bgP2RGB3->setColor(getThemeSecondaryColor());
		bgP2RGB3->setContentSize({90.f, 30.f});
		bgP2RGB3->setID("rgb-bg3-p2");
		page1Layer->addChild(bgP2RGB3);

		// page 2 
		auto bgP1RGB4 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP1RGB4->setPosition({90.f, 199.f});
		bgP1RGB4->setColor(getThemeSecondaryColor());
		bgP1RGB4->setContentSize({90.f, 30.f});
		bgP1RGB4->setID("rgb-bg4-p1");
		page2Layer->addChild(bgP1RGB4);

		auto bgP2RGB4 = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgP2RGB4->setPosition({270.f, 199.f});
		bgP2RGB4->setColor(getThemeSecondaryColor());
		bgP2RGB4->setContentSize({90.f, 30.f});
		bgP2RGB4->setID("rgb-bg4-p2");
		page2Layer->addChild(bgP2RGB4);

		auto bgStreak = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		bgStreak->setPosition({180.f, 123.f});
		bgStreak->setColor(getThemeSecondaryColor());
		bgStreak->setContentSize({270.f, 100.f});
		bgStreak->setID("streak-config-bg");
		page2Layer->addChild(bgStreak);

		// page 3
		auto page3Bg = CCScale9Sprite::create("square02b_001.png", {1, 1, 78, 78});
		page3Bg->setPosition({180.f, 143.f});
		page3Bg->setColor(getThemeSecondaryColor());
		page3Bg->setContentSize({270.f, 140.f});
		page3Bg->setID("page-3-bg");
		page3Layer->addChild(page3Bg);


		/*---
		Menus
		---*/


		// main
		auto toggleLinkMenu = CCMenu::create();
		toggleLinkMenu->setPosition({155.f, 213.f});
		toggleLinkMenu->setContentSize({50.f, 50.f});
		toggleLinkMenu->setID("toggle-link-menu");
		m_mainLayer->addChild(toggleLinkMenu);

		auto fancyPlayerInfoMenu = CCMenu::create();
		fancyPlayerInfoMenu->setPosition({330.f, 250.f});
		fancyPlayerInfoMenu->setContentSize({30.f, 30.f});
		fancyPlayerInfoMenu->setID("fancy-player-info-menu");
		m_mainLayer->addChild(fancyPlayerInfoMenu);

		auto arrowMenu = CCMenu::create();
		arrowMenu->setPosition({0.f, 120.f});
		arrowMenu->setContentSize({360.f, 50.f});
		arrowMenu->setID("arrow-menu");
		m_mainLayer->addChild(arrowMenu);

		auto page3Menu = CCMenu::create();
		page3Menu->setPosition({45.f, 73.f});
		page3Menu->setContentSize({270.f, 140.f});
		page3Menu->setID("page-3-menu");
		page3Layer->addChild(page3Menu, 1);


		// page 1
		// player 1
		m_togglesP1Page1 = CCMenu::create();
		m_togglesP1Page1->setPosition({90.f, 60.f});
		m_togglesP1Page1->setContentSize({60.f, 170.f});
		m_togglesP1Page1->setID("toggles-p1-page-1");
		page1Layer->addChild(m_togglesP1Page1);

		m_group1P1Page1 = CCMenu::create();
		m_group1P1Page1->setPosition({45.f, 154.f});
		m_group1P1Page1->setContentSize({60.f, 60.f});
		m_group1P1Page1->setID("group-1-p1-page-1");
		page1Layer->addChild(m_group1P1Page1);

		m_group2P1Page1 = CCMenu::create();
		m_group2P1Page1->setPosition({45.f, 114.f});
		m_group2P1Page1->setContentSize({60.f, 30.f});
		m_group2P1Page1->setID("group-2-p1-page-1");
		page1Layer->addChild(m_group2P1Page1);

		m_group3P1Page1 = CCMenu::create();
		m_group3P1Page1->setPosition({45.f, 74.f});
		m_group3P1Page1->setContentSize({60.f, 30.f});
		m_group3P1Page1->setID("group-3-p1-page-1");
		page1Layer->addChild(m_group3P1Page1);

		// player 2
		m_togglesP2Page1 = CCMenu::create();
		m_togglesP2Page1->setPosition({210.f, 60.f});
		m_togglesP2Page1->setContentSize({60.f, 170.f});
		m_togglesP2Page1->setID("toggles-p2-page-1");
		page1Layer->addChild(m_togglesP2Page1);

		m_group1P2Page1 = CCMenu::create();
		m_group1P2Page1->setPosition({255.f, 154.f});
		m_group1P2Page1->setContentSize({60.f, 60.f});
		m_group1P2Page1->setID("group-1-p2-page-1");
		page1Layer->addChild(m_group1P2Page1);

		m_group2P2Page1 = CCMenu::create();
		m_group2P2Page1->setPosition({255.f, 114.f});
		m_group2P2Page1->setContentSize({60.f, 30.f});
		m_group2P2Page1->setID("group-2-p2-page-1");
		page1Layer->addChild(m_group2P2Page1);

		m_group3P2Page1 = CCMenu::create();
		m_group3P2Page1->setPosition({255.f, 74.f});
		m_group3P2Page1->setContentSize({60.f, 30.f});
		m_group3P2Page1->setID("group-3-p2-page-1");
		page1Layer->addChild(m_group3P2Page1);

		// page 2
		// player 1
		m_togglesP1Page2 = CCMenu::create();
		m_togglesP1Page2->setPosition({90.f, 169.f});
		m_togglesP1Page2->setContentSize({60.f, 60.f});
		m_togglesP1Page2->setID("toggles-p1-page-2");
		page2Layer->addChild(m_togglesP1Page2);

		m_group1P1Page2 = CCMenu::create();
		m_group1P1Page2->setPosition({45.f, 184.f});
		m_group1P1Page2->setContentSize({60.f, 30.f});
		m_group1P1Page2->setID("group-1-p1-page-2");
		page2Layer->addChild(m_group1P1Page2);

		// player 2
		m_togglesP2Page2 = CCMenu::create();
		m_togglesP2Page2->setPosition({210.f, 169.f});
		m_togglesP2Page2->setContentSize({60.f, 60.f});
		m_togglesP2Page2->setID("toggles-p2-page-2");
		page2Layer->addChild(m_togglesP2Page2);

		m_group1P2Page2 = CCMenu::create();
		m_group1P2Page2->setPosition({255.f, 184.f});
		m_group1P2Page2->setContentSize({60.f, 30.f});
		m_group1P2Page2->setID("group-1-p2-page-2");
		page2Layer->addChild(m_group1P2Page2);

		// streak config
		auto toggleStreakConfigMenu = CCMenu::create();
		toggleStreakConfigMenu->setPosition({45.f, 143.f});
		toggleStreakConfigMenu->setContentSize({60.f, 30.f});
		toggleStreakConfigMenu->setID("toggle-streak-config-menu");
		page2Layer->addChild(toggleStreakConfigMenu);

		auto streakInfoMenu = CCMenu::create();
		streakInfoMenu->setPosition({115.f, 73.f});
		streakInfoMenu->setContentSize({30.f, 80.f});
		streakInfoMenu->setID("streak-info-menu");
		page2Layer->addChild(streakInfoMenu);

		m_toggleSlidersMenu = CCMenu::create();
		m_toggleSlidersMenu->setPosition({285.f, 73.f});
		m_toggleSlidersMenu->setContentSize({30.f, 100.f});
		m_toggleSlidersMenu->setID("toggle-sliders-menu");
		page2Layer->addChild(m_toggleSlidersMenu);

		m_streakMiscToggles = CCMenu::create();
		m_streakMiscToggles->setPosition({45.f, 73.f});
		m_streakMiscToggles->setContentSize({100.f, 75.f});
		m_streakMiscToggles->setID("streak-misc-toggles");
		page2Layer->addChild(m_streakMiscToggles);


		/*-----
		Buttons
		-----*/


		auto backArrow = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
		backArrow->setScale(0.7f);
		auto forwardArrow = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
		forwardArrow->setFlipX(true);
		forwardArrow->setScale(0.7f);
		auto infoButton = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
		infoButton->setScale(0.6f);

		auto backButton = CCMenuItemSpriteExtra::create(backArrow, this, menu_selector(FancyPopup::backArrowCallback));
		backButton->setAnchorPoint({0.5f, 0.5f});
		backButton->setPosition({25.f, 25.f});
		backButton->setID("back-button");
		arrowMenu->addChild(backButton);

		auto forwardButton = CCMenuItemSpriteExtra::create(forwardArrow, this, menu_selector(FancyPopup::forwardArrowCallback));
		forwardButton->setAnchorPoint({0.5f, 0.5f});
		forwardButton->setPosition({335.f, 25.f});
		forwardButton->setID("forward-button");
		arrowMenu->addChild(forwardButton);

		auto fancyPlayerInfoButton = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::fancyPlayerInfoCallback));
		fancyPlayerInfoButton->setAnchorPoint({0.5f, 0.5f});
		fancyPlayerInfoButton->setPosition({15.f, 15.f});
		fancyPlayerInfoButton->setID("fancy-player-info-button");
		fancyPlayerInfoMenu->addChild(fancyPlayerInfoButton);

		auto enableStreakConfigInfo = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::enableStreakConfigInfoCallback));
		enableStreakConfigInfo->setAnchorPoint({0.5f, 0.5f});
		enableStreakConfigInfo->setPosition({40.f, 15.f});
		enableStreakConfigInfo->setID("enable-streak-config-info-button");
		toggleStreakConfigMenu->addChild(enableStreakConfigInfo);

		auto streakAlignInfo = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::streakAlignInfoCallback));
		streakAlignInfo->setAnchorPoint({0.5f, 0.5f});
		streakAlignInfo->setPosition({16.f, 38.f});
		streakAlignInfo->setID("align-streak-info-button");
		streakInfoMenu->addChild(streakAlignInfo);

		auto streakBlendInfo = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::streakBlendInfoCallback));
		streakBlendInfo->setAnchorPoint({0.5f, 0.5f});
		streakBlendInfo->setPosition({15.f, 15.f});
		streakBlendInfo->setID("disable-blending-info-button");
		streakInfoMenu->addChild(streakBlendInfo);

		auto alignInfoMenuItem = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::alignInfoCallback));
		alignInfoMenuItem->setAnchorPoint({0.5f, 0.5f});
		alignInfoMenuItem->setPosition({127.f, 125.f});
		alignInfoMenuItem->setID("align-particles-info-button");
		page3Menu->addChild(alignInfoMenuItem);

		auto streakAlignWaveInfo = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::streakAlignWaveInfoCallback));
		streakAlignWaveInfo->setAnchorPoint({0.5f, 0.5f});
		streakAlignWaveInfo->setPosition({113.f, 93.f});
		streakAlignWaveInfo->setID("align-streak-wave-info-button");
		page3Menu->addChild(streakAlignWaveInfo);

		auto scaleRadiusInfo = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::scaleRadiusInfoCallback));
		scaleRadiusInfo->setAnchorPoint({0.5f, 0.5f});
		scaleRadiusInfo->setPosition({113.f, 65.f});
		scaleRadiusInfo->setID("scale-radius-info-button");
		page3Menu->addChild(scaleRadiusInfo);

		auto customInfoMenuItem = CCMenuItemSpriteExtra::create(infoButton, this, menu_selector(FancyPopup::customInfoCallback));
		customInfoMenuItem->setAnchorPoint({0.5f, 0.5f});
		customInfoMenuItem->setPosition({107.f, 35.f});
		customInfoMenuItem->setID("custom-trail-info-button");
		page3Menu->addChild(customInfoMenuItem);


		/*----
		Labels
		----*/


		// main
		auto p1lbl = CCLabelBMFont::create("Player 1", "bigFont.fnt");
		p1lbl->setScale(0.4f);
		p1lbl->setPosition({120.f, 240.f});
		p1lbl->setID("p1-label");
		m_mainLayer->addChild(p1lbl);

		auto p2lbl = CCLabelBMFont::create("Player 2", "bigFont.fnt");
		p2lbl->setScale(0.4f);
		p2lbl->setPosition({240.f, 240.f});
		p2lbl->setID("p2-label");
		m_mainLayer->addChild(p2lbl);

		auto rgbfs = CCLabelBMFont::create("RGB Fade Speed", "goldFont.fnt");
		rgbfs->setScale(0.5f);
		rgbfs->setPosition({160.f, 45.f});
		rgbfs->setID("rgb-fade-speed-label");
		m_mainLayer->addChild(rgbfs);

		m_rgbfslbl = CCLabelBMFont::create(numToString(fancy::settings.rgbSpeed, 1).c_str(), "bigFont.fnt");
		m_rgbfslbl->setScale(0.45f);
		m_rgbfslbl->setPosition({230.f, 45.f});
		m_rgbfslbl->setID("rgb-fade-speed-number-label");
		m_mainLayer->addChild(m_rgbfslbl);

		auto pageNumber = CCLabelBMFont::create("1/3", "goldFont.fnt");
		pageNumber->setScale(0.6f);
		pageNumber->setPosition({180.f, 60.f});
		pageNumber->setID("page-number-label");
		m_mainLayer->addChild(pageNumber);

		// page 1
		auto p1rgblbl1 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p1rgblbl1->setScale(0.35f);
		p1rgblbl1->setPosition({60.f, 220.f});
		p1rgblbl1->setOpacity(100);
		p1rgblbl1->setID("p1-rgb-label-1");
		page1Layer->addChild(p1rgblbl1);

		auto p1rgblbl2 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p1rgblbl2->setScale(0.35f);
		p1rgblbl2->setPosition({60.f, 150.f});
		p1rgblbl2->setOpacity(100);
		p1rgblbl2->setID("p1-rgb-label-2");
		page1Layer->addChild(p1rgblbl2);

		auto p1rgblbl3 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p1rgblbl3->setScale(0.35f);
		p1rgblbl3->setPosition({60.f, 110.f});
		p1rgblbl3->setOpacity(100);
		p1rgblbl3->setID("p1-rgb-label-3");
		page1Layer->addChild(p1rgblbl3);

		auto p2rgblbl1 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p2rgblbl1->setScale(0.35f);
		p2rgblbl1->setPosition({300.f, 220.f});
		p2rgblbl1->setOpacity(100);
		p2rgblbl1->setID("p2-rgb-label-1");
		page1Layer->addChild(p2rgblbl1);

		auto p2rgblbl2 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p2rgblbl2->setScale(0.35f);
		p2rgblbl2->setPosition({300.f, 150.f});
		p2rgblbl2->setOpacity(100);
		p2rgblbl2->setID("p2-rgb-label-2");
		page1Layer->addChild(p2rgblbl2);

		auto p2rgblbl3 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p2rgblbl3->setScale(0.35f);
		p2rgblbl3->setPosition({300.f, 110.f});
		p2rgblbl3->setOpacity(100);
		p2rgblbl3->setID("p2-rgb-label-3");
		page1Layer->addChild(p2rgblbl3);

		auto ccopp = CCLabelBMFont::create("Configure Color of Player Particles", "goldFont.fnt");
		ccopp->setScale(0.4f);
		ccopp->setPosition({180.f, 220.f});
		ccopp->setID("configure-particles-label");
		page1Layer->addChild(ccopp);

		auto psc = CCLabelBMFont::create("startColor", "bigFont.fnt");
		psc->setScale(0.35f);
		psc->setPosition({180.f, 200.f});
		psc->setID("start-color-label");
		page1Layer->addChild(psc);

		auto pfc = CCLabelBMFont::create("finishColor", "bigFont.fnt");
		pfc->setScale(0.35f);
		pfc->setPosition({180.f, 170.f});
		pfc->setID("finish-color-label");
		page1Layer->addChild(pfc);

		auto ccodf = CCLabelBMFont::create("Configure Color of Dash Fire", "goldFont.fnt");
		ccodf->setScale(0.4f);
		ccodf->setPosition({180.f, 150.f});
		ccodf->setID("configure-dash-fire-label");
		page1Layer->addChild(ccodf);

		auto ccosd = CCLabelBMFont::create("Configure Color of Spider Dash", "goldFont.fnt");
		ccosd->setScale(0.4f);
		ccosd->setPosition({180.f, 110.f});
		ccosd->setID("configure-spider-dash-label");
		page1Layer->addChild(ccosd);

		auto enableText1 = CCLabelBMFont::create("<- Enable ->", "goldFont.fnt");
		enableText1->setScale(0.4f);
		enableText1->setPosition({180.f, 185.f});
		enableText1->setOpacity(100);
		enableText1->setID("enable-text-1");
		page1Layer->addChild(enableText1);

		auto enableText2 = CCLabelBMFont::create("<- Enable ->", "goldFont.fnt");
		enableText2->setScale(0.4f);
		enableText2->setPosition({180.f, 130.f});
		enableText2->setOpacity(100);
		enableText2->setID("enable-text-2");
		page1Layer->addChild(enableText2);

		auto enableText3 = CCLabelBMFont::create("<- Enable ->", "goldFont.fnt");
		enableText3->setScale(0.4f);
		enableText3->setPosition({180.f, 90.f});
		enableText3->setOpacity(100);
		enableText3->setID("enable-text-3");
		page1Layer->addChild(enableText3);

		// page 2
		auto p1rgblbl4 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p1rgblbl4->setScale(0.35f);
		p1rgblbl4->setPosition({60.f, 220.f});
		p1rgblbl4->setOpacity(100);
		p1rgblbl4->setID("p1-rgb-label-4");
		page2Layer->addChild(p1rgblbl4);

		auto p2rgblbl4 = CCLabelBMFont::create("RGB", "bigFont.fnt");
		p2rgblbl4->setScale(0.35f);
		p2rgblbl4->setPosition({300.f, 220.f});
		p2rgblbl4->setOpacity(100);
		p2rgblbl4->setID("p2-rgb-label-4");
		page2Layer->addChild(p2rgblbl4);

		auto enableText4 = CCLabelBMFont::create("<- Enable ->", "goldFont.fnt");
		enableText4->setScale(0.4f);
		enableText4->setPosition({180.f, 200.f});
		enableText4->setOpacity(100);
		enableText4->setID("enable-text-4");
		page2Layer->addChild(enableText4);

		auto ccops = CCLabelBMFont::create("Configure Color of Player Streak", "goldFont.fnt");
		ccops->setScale(0.4f);
		ccops->setPosition({180.f, 220.f});
		ccops->setID("configure-streak-color-label");
		page2Layer->addChild(ccops);

		auto epsc = CCLabelBMFont::create("Global Player Streak Configuration", "goldFont.fnt");
		epsc->setScale(0.4f);
		epsc->setPosition({180.f, 180.f});
		epsc->setID("configure-streak-label");
		page2Layer->addChild(epsc);

		auto eepsc1 = CCLabelBMFont::create("Enable", "bigFont.fnt");
		eepsc1->setScale(0.3f);
		eepsc1->setPosition({60.f, 180.f});
		eepsc1->setID("enable-streak-config-label");
		eepsc1->setOpacity(100);
		page2Layer->addChild(eepsc1);

		auto eepsc2 = CCLabelBMFont::create("Enable", "bigFont.fnt");
		eepsc2->setScale(0.3f);
		eepsc2->setPosition({300.f, 180.f});
		eepsc2->setID("enable-streak-config-label");
		eepsc2->setOpacity(100);
		page2Layer->addChild(eepsc2);

		auto streakFadeLabel = CCLabelBMFont::create("Length", "goldFont.fnt");
		streakFadeLabel->setScale(0.4f);
		streakFadeLabel->setPosition({220.f, 163.f});
		streakFadeLabel->setID("streak-fade-label");
		page2Layer->addChild(streakFadeLabel);

		m_streakFadeNumberLabel = CCLabelBMFont::create(numToString(fancy::settings.streakFade, 1).c_str(), "bigFont.fnt");
		m_streakFadeNumberLabel->setScale(0.3f);
		m_streakFadeNumberLabel->setPosition({255.f, 163.f});
		m_streakFadeNumberLabel->setID("streak-fade-number-label");
		page2Layer->addChild(m_streakFadeNumberLabel);

		auto streakStrokeLabel = CCLabelBMFont::create("Width", "goldFont.fnt");
		streakStrokeLabel->setScale(0.4f);
		streakStrokeLabel->setPosition({220.f, 133.f});
		streakStrokeLabel->setID("streak-stroke-label");
		page2Layer->addChild(streakStrokeLabel);

		m_streakStrokeNumberLabel = CCLabelBMFont::create(numToString(fancy::settings.streakStroke, 1).c_str(), "bigFont.fnt");
		m_streakStrokeNumberLabel->setScale(0.3f);
		m_streakStrokeNumberLabel->setPosition({255.f, 133.f});
		m_streakStrokeNumberLabel->setID("streak-stroke-number-label");
		page2Layer->addChild(m_streakStrokeNumberLabel);

		auto streakRepeatLabel = CCLabelBMFont::create("Repeat", "goldFont.fnt");
		streakRepeatLabel->setScale(0.4f);
		streakRepeatLabel->setPosition({220.f, 103.f});
		streakRepeatLabel->setID("streak-repeat-label");
		page2Layer->addChild(streakRepeatLabel);

		m_streakRepeatNumberLabel = CCLabelBMFont::create(numToString(fancy::settings.streakRepeat, 2).c_str(), "bigFont.fnt");
		m_streakRepeatNumberLabel->setScale(0.3f);
		m_streakRepeatNumberLabel->setPosition({255.f, 103.f});
		m_streakRepeatNumberLabel->setID("streak-repeat-number-label");
		page2Layer->addChild(m_streakRepeatNumberLabel);

		auto streakAlwaysShowLabel = CCLabelBMFont::create("Always Show\nStreak", "bigFont.fnt");
		streakAlwaysShowLabel->setScale(0.3f);
		streakAlwaysShowLabel->setPosition({106.f, 135.f});
		streakAlwaysShowLabel->setID("streak-always-show-label");
		page2Layer->addChild(streakAlwaysShowLabel);

		auto streakAlignLabel = CCLabelBMFont::create("Align If\nAirborne", "bigFont.fnt");
		streakAlignLabel->setScale(0.3f);
		streakAlignLabel->setPosition({97.f, 112.f});
		streakAlignLabel->setID("streak-align-label");
		page2Layer->addChild(streakAlignLabel);

		auto streakBlendLabel = CCLabelBMFont::create("Disable\nBlending", "bigFont.fnt");
		streakBlendLabel->setScale(0.3f);
		streakBlendLabel->setPosition({97.f, 89.f});
		streakBlendLabel->setID("streak-blend-label");
		page2Layer->addChild(streakBlendLabel);

		// page 3
		auto emsp3 = CCLabelBMFont::create("Enable", "bigFont.fnt");
		emsp3->setScale(0.3f);
		emsp3->setPosition({60.f, 220.f});
		emsp3->setID("enable-streak-config-label");
		emsp3->setOpacity(100);
		page3Layer->addChild(emsp3);

		auto misclbl = CCLabelBMFont::create("Miscellaneous Settings", "goldFont.fnt");
		misclbl->setScale(0.4f);
		misclbl->setPosition({180.f, 220.f});
		misclbl->setID("misc-settings-label");
		page3Layer->addChild(misclbl);

		auto aplbl = CCLabelBMFont::create("Align Particles\nWhen Airborne", "bigFont.fnt");
		aplbl->setScale(0.325f);
		aplbl->setPosition({118.f, 199.f});
		aplbl->setID("align-particles-label");
		page3Layer->addChild(aplbl);

		auto streakAlignWaveLabel = CCLabelBMFont::create("Align Streak\nWhen Wave", "bigFont.fnt");
		streakAlignWaveLabel->setScale(0.325f);
		streakAlignWaveLabel->setPosition({111.f, 169.f});
		streakAlignWaveLabel->setID("streak-align-wave-label");
		page3Layer->addChild(streakAlignWaveLabel);

		auto changeRadiusLabel = CCLabelBMFont::create("Scale Radius\nEmitters", "bigFont.fnt");
		changeRadiusLabel->setScale(0.325f);
		changeRadiusLabel->setPosition({111.f, 139.f});
		changeRadiusLabel->setID("change-radius-label");
		page3Layer->addChild(changeRadiusLabel);

		auto tctlbl = CCLabelBMFont::create("Enable Nyan\nCat Trail", "bigFont.fnt");
		tctlbl->setScale(0.325f);
		tctlbl->setPosition({108.f, 109.f});
		tctlbl->setID("custom-trail-label");
		page3Layer->addChild(tctlbl);

		auto name = CCSprite::create("FP_shamelessPlug_001.png"_spr);
		name->setPosition({255.f, 145.f});
		name->setColor(getThemePrimaryColor());
		name->setID("shameless-plug");
		page3Layer->addChild(name, 1);


		/*------------------
		Color Picker Buttons
		------------------*/


		// page 1
		// player 1
		auto colorBtnPSP1 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnPSP1->setScale(0.7f);
		auto colorPickerParticleStartP1 = CCMenuItemSpriteExtra::create(colorBtnPSP1, this, menu_selector(FancyPopup::colorPickerParticleStartP1Callback));
		colorPickerParticleStartP1->setAnchorPoint({0.5f, 0.5f});
		colorPickerParticleStartP1->setPosition({45.f, 45.f});
		colorPickerParticleStartP1->setColor(color4BTo3B(fancy::settings.p1StartColor));
		colorPickerParticleStartP1->setID("color-picker-particle-start-p1");
		m_group1P1Page1->addChild(colorPickerParticleStartP1);

		auto colorBtnPFP1 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnPFP1->setScale(0.7f);
		auto colorPickerParticleFinishP1 = CCMenuItemSpriteExtra::create(colorBtnPFP1, this, menu_selector(FancyPopup::colorPickerParticleFinishP1Callback));
		colorPickerParticleFinishP1->setAnchorPoint({0.5f, 0.5f});
		colorPickerParticleFinishP1->setPosition({45.f, 15.f});
		colorPickerParticleFinishP1->setColor(color4BTo3B(fancy::settings.p1FinishColor));
		colorPickerParticleFinishP1->setID("color-picker-particle-finish-p1");
		m_group1P1Page1->addChild(colorPickerParticleFinishP1);

		auto colorBtnDFP1 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnDFP1->setScale(0.7f);
		auto colorPickerDashFireP1 = CCMenuItemSpriteExtra::create(colorBtnDFP1, this, menu_selector(FancyPopup::colorPickerDashFireP1Callback));
		colorPickerDashFireP1->setAnchorPoint({0.5f, 0.5f});
		colorPickerDashFireP1->setPosition({45.f, 15.f});
		colorPickerDashFireP1->setColor(fancy::settings.p1DashFireColor);
		colorPickerDashFireP1->setID("color-picker-dash-fire-p1");
		m_group2P1Page1->addChild(colorPickerDashFireP1);

		auto colorBtnSDP1 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnSDP1->setScale(0.7f);
		auto colorPickerSpiderDashP1 = CCMenuItemSpriteExtra::create(colorBtnSDP1, this, menu_selector(FancyPopup::colorPickerSpiderDashP1Callback));
		colorPickerSpiderDashP1->setAnchorPoint({0.5f, 0.5f});
		colorPickerSpiderDashP1->setPosition({45.f, 15.f});
		colorPickerSpiderDashP1->setColor(fancy::settings.p1SpiderDashColor);
		colorPickerSpiderDashP1->setID("color-picker-spider-dash-p1");
		m_group3P1Page1->addChild(colorPickerSpiderDashP1);

		// player 2
		auto colorBtnPSP2 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnPSP2->setScale(0.7f);
		auto colorPickerParticleStartP2 = CCMenuItemSpriteExtra::create(colorBtnPSP2, this, menu_selector(FancyPopup::colorPickerParticleStartP2Callback));
		colorPickerParticleStartP2->setAnchorPoint({0.5f, 0.5f});
		colorPickerParticleStartP2->setPosition({15.f, 45.f});
		colorPickerParticleStartP2->setColor(color4BTo3B(fancy::settings.p2StartColor));
		colorPickerParticleStartP2->setID("color-picker-particle-start-p2");
		m_group1P2Page1->addChild(colorPickerParticleStartP2);

		auto colorBtnPFP2 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnPFP2->setScale(0.7f);
		auto colorPickerParticleFinishP2 = CCMenuItemSpriteExtra::create(colorBtnPFP2, this, menu_selector(FancyPopup::colorPickerParticleFinishP2Callback));
		colorPickerParticleFinishP2->setAnchorPoint({0.5f, 0.5f});
		colorPickerParticleFinishP2->setPosition({15.f, 15.f});
		colorPickerParticleFinishP2->setColor(color4BTo3B(fancy::settings.p2FinishColor));
		colorPickerParticleFinishP2->setID("color-picker-particle-finish-p2");
		m_group1P2Page1->addChild(colorPickerParticleFinishP2);

		auto colorBtnDFP2 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnDFP2->setScale(0.7f);
		auto colorPickerDashFireP2 = CCMenuItemSpriteExtra::create(colorBtnDFP2, this, menu_selector(FancyPopup::colorPickerDashFireP2Callback));
		colorPickerDashFireP2->setAnchorPoint({0.5f, 0.5f});
		colorPickerDashFireP2->setPosition({15.f, 15.f});
		colorPickerDashFireP2->setColor(fancy::settings.p2DashFireColor);
		colorPickerDashFireP2->setID("color-picker-dash-fire-p2");
		m_group2P2Page1->addChild(colorPickerDashFireP2);

		auto colorBtnSDP2 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnSDP2->setScale(0.7f);
		auto colorPickerSpiderDashP2 = CCMenuItemSpriteExtra::create(colorBtnSDP2, this, menu_selector(FancyPopup::colorPickerSpiderDashP2Callback));
		colorPickerSpiderDashP2->setAnchorPoint({0.5f, 0.5f});
		colorPickerSpiderDashP2->setPosition({15.f, 15.f});
		colorPickerSpiderDashP2->setColor(fancy::settings.p2SpiderDashColor);
		colorPickerSpiderDashP2->setID("color-picker-spider-dash-p2");
		m_group3P2Page1->addChild(colorPickerSpiderDashP2);

		// page 2
		// player 1
		auto colorBtnSP1 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnSP1->setScale(0.7f);
		auto colorPickerStreakP1 = CCMenuItemSpriteExtra::create(colorBtnSP1, this, menu_selector(FancyPopup::colorPickerStreakP1Callback));
		colorPickerStreakP1->setAnchorPoint({0.5f, 0.5f});
		colorPickerStreakP1->setPosition({45.f, 15.f});
		colorPickerStreakP1->setColor(fancy::settings.p1StreakColor);
		colorPickerStreakP1->setID("color-picker-streak-p1");
		m_group1P1Page2->addChild(colorPickerStreakP1);

		// player 2
		auto colorBtnSP2 = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		colorBtnSP2->setScale(0.7f);
		auto colorPickerStreakP2 = CCMenuItemSpriteExtra::create(colorBtnSP2, this, menu_selector(FancyPopup::colorPickerStreakP2Callback));
		colorPickerStreakP2->setAnchorPoint({0.5f, 0.5f});
		colorPickerStreakP2->setPosition({15.f, 15.f});
		colorPickerStreakP2->setColor(fancy::settings.p2StreakColor);
		colorPickerStreakP2->setID("color-picker-streak-p2");
		m_group1P2Page2->addChild(colorPickerStreakP2);


		/*----------
		Toggle Boxes
		----------*/


		// reused sprites
		auto toggleOffSpr = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSpr = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleOffSprP2Enable = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprP2Enable = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleOffSprStreak = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprStreak = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

		// main
		auto linkBtnOff = CCSprite::createWithSpriteFrameName("gj_linkBtnOff_001.png");
		auto linkBtnOn = CCSprite::createWithSpriteFrameName("gj_linkBtn_001.png");
		auto toggleLinkButton = CCMenuItemToggler::create(linkBtnOn, linkBtnOff, this, menu_selector(FancyPopup::toggleLinkCallback));
		toggleLinkButton->setAnchorPoint({0.5f, 0.5f});
		toggleLinkButton->setPosition({25.f, 25.f});
		toggleLinkButton->setScale(0.8f);
		toggleLinkButton->setID("toggle-link-button");
		toggleLinkMenu->addChild(toggleLinkButton);
		bool toggleLinkButtonState = fancy::settings.p2Enable;
		toggleLinkButton->toggle(toggleLinkButtonState ? 1 : 0);

		// page 1
		// player 1
		auto toggleOffSprRPP1 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRPP1 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowParticlesP1 = CCMenuItemToggler::create(toggleOffSprRPP1, toggleOnSprRPP1, this, menu_selector(FancyPopup::toggleRainbowParticlesP1Callback));
		toggleRainbowParticlesP1->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowParticlesP1->setPosition({15.f, 30.f});
		toggleRainbowParticlesP1->setScale(0.7f);
		toggleRainbowParticlesP1->setID("toggle-rainbow-particles-p1");
		m_group1P1Page1->addChild(toggleRainbowParticlesP1);
		bool toggleRainbowParticlesP1State = fancy::settings.p1RainbowParticles;
		toggleRainbowParticlesP1->toggle(toggleRainbowParticlesP1State ? 1 : 0);

		auto toggleOffSprRDFP1 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRDFP1 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowDashFireP1 = CCMenuItemToggler::create(toggleOffSprRDFP1, toggleOnSprRDFP1, this, menu_selector(FancyPopup::toggleRainbowDashFireP1Callback));
		toggleRainbowDashFireP1->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowDashFireP1->setPosition({15.f, 15.f});
		toggleRainbowDashFireP1->setScale(0.7f);
		toggleRainbowDashFireP1->setID("toggle-rainbow-dash-fire-p1");
		m_group2P1Page1->addChild(toggleRainbowDashFireP1);
		bool toggleRainbowDashFireP1State = fancy::settings.p1RainbowDashFire;
		toggleRainbowDashFireP1->toggle(toggleRainbowDashFireP1State ? 1 : 0);

		auto toggleOffSprRSDP1 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRSDP1 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowSpiderDashP1 = CCMenuItemToggler::create(toggleOffSprRSDP1, toggleOnSprRSDP1, this, menu_selector(FancyPopup::toggleRainbowSpiderDashP1Callback));
		toggleRainbowSpiderDashP1->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowSpiderDashP1->setPosition({15.f, 15.f});
		toggleRainbowSpiderDashP1->setScale(0.7f);
		toggleRainbowSpiderDashP1->setID("toggle-rainbow-spider-dash-p1");
		m_group3P1Page1->addChild(toggleRainbowSpiderDashP1);
		bool toggleRainbowSpiderDashP1State = fancy::settings.p1RainbowSpiderDash;
		toggleRainbowSpiderDashP1->toggle(toggleRainbowSpiderDashP1State ? 1 : 0);

		// player 1 enable toggles
		auto toggleEnableParticlesP1 = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleEnableParticlesP1Callback));
		toggleEnableParticlesP1->setAnchorPoint({0.5f, 0.5f});
		toggleEnableParticlesP1->setPosition({30.f, 124.f});
		toggleEnableParticlesP1->setScale(0.7f);
		toggleEnableParticlesP1->setID("toggle-enable-particles-p1");
		m_togglesP1Page1->addChild(toggleEnableParticlesP1);
		bool toggleEnableParticlesP1State = fancy::settings.p1ChangeParticles;
		toggleEnableParticlesP1->toggle(toggleEnableParticlesP1State ? 1 : 0);

		auto toggleEnableDashFireP1 = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleEnableDashFireP1Callback));
		toggleEnableDashFireP1->setAnchorPoint({0.5f, 0.5f});
		toggleEnableDashFireP1->setPosition({30.f, 69.f});
		toggleEnableDashFireP1->setScale(0.7f);
		toggleEnableDashFireP1->setID("toggle-enable-dash-fire-p1");
		m_togglesP1Page1->addChild(toggleEnableDashFireP1);
		bool toggleEnableDashFireP1State = fancy::settings.p1ChangeDashFire;
		toggleEnableDashFireP1->toggle(toggleEnableDashFireP1State ? 1 : 0);

		auto toggleEnableSpiderDashP1 = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleEnableSpiderDashP1Callback));
		toggleEnableSpiderDashP1->setAnchorPoint({0.5f, 0.5f});
		toggleEnableSpiderDashP1->setPosition({30.f, 29.f});
		toggleEnableSpiderDashP1->setScale(0.7f);
		toggleEnableSpiderDashP1->setID("toggle-enable-spider-dash-p1");
		m_togglesP1Page1->addChild(toggleEnableSpiderDashP1);
		bool toggleEnableSpiderDashP1State = fancy::settings.p1ChangeSpiderDash;
		toggleEnableSpiderDashP1->toggle(toggleEnableSpiderDashP1State ? 1 : 0);

		// player 2
		auto toggleOffSprRPP2 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRPP2 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowParticlesP2 = CCMenuItemToggler::create(toggleOffSprRPP2, toggleOnSprRPP2, this, menu_selector(FancyPopup::toggleRainbowParticlesP2Callback));
		toggleRainbowParticlesP2->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowParticlesP2->setPosition({45.f, 30.f});
		toggleRainbowParticlesP2->setScale(0.7f);
		toggleRainbowParticlesP2->setID("toggle-rainbow-particles-p2");
		m_group1P2Page1->addChild(toggleRainbowParticlesP2);
		bool toggleRainbowParticlesP2State = fancy::settings.p2RainbowParticles;
		toggleRainbowParticlesP2->toggle(toggleRainbowParticlesP2State ? 1 : 0);

		auto toggleOffSprRDFP2 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRDFP2 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowDashFireP2 = CCMenuItemToggler::create(toggleOffSprRDFP2, toggleOnSprRDFP2, this, menu_selector(FancyPopup::toggleRainbowDashFireP2Callback));
		toggleRainbowDashFireP2->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowDashFireP2->setPosition({45.f, 15.f});
		toggleRainbowDashFireP2->setScale(0.7f);
		toggleRainbowDashFireP2->setID("toggle-rainbow-dash-fire-p2");
		m_group2P2Page1->addChild(toggleRainbowDashFireP2);
		bool toggleRainbowDashFireP2State = fancy::settings.p2RainbowDashFire;
		toggleRainbowDashFireP2->toggle(toggleRainbowDashFireP2State ? 1 : 0);

		auto toggleOffSprRSDP2 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRSDP2 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowSpiderDashP2 = CCMenuItemToggler::create(toggleOffSprRSDP2, toggleOnSprRSDP2, this, menu_selector(FancyPopup::toggleRainbowSpiderDashP2Callback));
		toggleRainbowSpiderDashP2->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowSpiderDashP2->setPosition({45.f, 15.f});
		toggleRainbowSpiderDashP2->setScale(0.7f);
		toggleRainbowSpiderDashP2->setID("toggle-rainbow-spider-dash-p2");
		m_group3P2Page1->addChild(toggleRainbowSpiderDashP2);
		bool toggleRainbowSpiderDashP2State = fancy::settings.p2RainbowSpiderDash;
		toggleRainbowSpiderDashP2->toggle(toggleRainbowSpiderDashP2State ? 1 : 0);

		// player 2 enable toggles
		auto toggleEnableParticlesP2 = CCMenuItemToggler::create(toggleOffSprP2Enable, toggleOnSprP2Enable, this, menu_selector(FancyPopup::toggleEnableParticlesP2Callback));
		toggleEnableParticlesP2->setAnchorPoint({0.5f, 0.5f});
		toggleEnableParticlesP2->setPosition({30.f, 124.f});
		toggleEnableParticlesP2->setScale(0.7f);
		toggleEnableParticlesP2->setID("toggle-enable-particles-p2");
		m_togglesP2Page1->addChild(toggleEnableParticlesP2);
		bool toggleEnableParticlesP2State = fancy::settings.p2ChangeParticles;
		toggleEnableParticlesP2->toggle(toggleEnableParticlesP2State ? 1 : 0);

		auto toggleEnableDashFireP2 = CCMenuItemToggler::create(toggleOffSprP2Enable, toggleOnSprP2Enable, this, menu_selector(FancyPopup::toggleEnableDashFireP2Callback));
		toggleEnableDashFireP2->setAnchorPoint({0.5f, 0.5f});
		toggleEnableDashFireP2->setPosition({30.f, 69.f});
		toggleEnableDashFireP2->setScale(0.7f);
		toggleEnableDashFireP2->setID("toggle-enable-dash-fire-p2");
		m_togglesP2Page1->addChild(toggleEnableDashFireP2);
		bool toggleEnableDashFireP2State = fancy::settings.p2ChangeDashFire;
		toggleEnableDashFireP2->toggle(toggleEnableDashFireP2State ? 1 : 0);

		auto toggleEnableSpiderDashP2 = CCMenuItemToggler::create(toggleOffSprP2Enable, toggleOnSprP2Enable, this, menu_selector(FancyPopup::toggleEnableSpiderDashP2Callback));
		toggleEnableSpiderDashP2->setAnchorPoint({0.5f, 0.5f});
		toggleEnableSpiderDashP2->setPosition({30.f, 29.f});
		toggleEnableSpiderDashP2->setScale(0.7f);
		toggleEnableSpiderDashP2->setID("toggle-enable-spider-dash-p2");
		m_togglesP2Page1->addChild(toggleEnableSpiderDashP2);
		bool toggleEnableSpiderDashP2State = fancy::settings.p2ChangeSpiderDash;
		toggleEnableSpiderDashP2->toggle(toggleEnableSpiderDashP2State ? 1 : 0);

		// page 2
		// player 1
		auto toggleOffSprRSP1 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRSP1 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowStreakP1 = CCMenuItemToggler::create(toggleOffSprRSP1, toggleOnSprRSP1, this, menu_selector(FancyPopup::toggleRainbowStreakP1Callback));
		toggleRainbowStreakP1->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowStreakP1->setPosition({15.f, 15.f});
		toggleRainbowStreakP1->setScale(0.7f);
		toggleRainbowStreakP1->setID("toggle-rainbow-streak-p1");
		m_group1P1Page2->addChild(toggleRainbowStreakP1);
		bool toggleRainbowStreakP1State = fancy::settings.p1RainbowStreak;
		toggleRainbowStreakP1->toggle(toggleRainbowStreakP1State ? 1 : 0);

		// player 1 enable toggles
		auto toggleEnableStreakP1 = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleEnableStreakP1Callback));
		toggleEnableStreakP1->setAnchorPoint({0.5f, 0.5f});
		toggleEnableStreakP1->setPosition({30.f, 30.f});
		toggleEnableStreakP1->setScale(0.7f);
		toggleEnableStreakP1->setID("toggle-enable-streak-p1");
		m_togglesP1Page2->addChild(toggleEnableStreakP1);
		bool toggleEnableStreakP1State = fancy::settings.p1ChangeStreak;
		toggleEnableStreakP1->toggle(toggleEnableStreakP1State ? 1 : 0);

		// player 2
		auto toggleOffSprRSP2 = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOnSprRSP2 = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		auto toggleRainbowStreakP2 = CCMenuItemToggler::create(toggleOffSprRSP2, toggleOnSprRSP2, this, menu_selector(FancyPopup::toggleRainbowStreakP2Callback));
		toggleRainbowStreakP2->setAnchorPoint({0.5f, 0.5f});
		toggleRainbowStreakP2->setPosition({45.f, 15.f});
		toggleRainbowStreakP2->setScale(0.7f);
		toggleRainbowStreakP2->setID("toggle-rainbow-streak-p2");
		m_group1P2Page2->addChild(toggleRainbowStreakP2);
		bool toggleRainbowStreakP2State = fancy::settings.p2RainbowStreak;
		toggleRainbowStreakP2->toggle(toggleRainbowStreakP2State ? 1 : 0);

		// player 2 enable toggles
		auto toggleEnableStreakP2 = CCMenuItemToggler::create(toggleOffSprP2Enable, toggleOnSprP2Enable, this, menu_selector(FancyPopup::toggleEnableStreakP2Callback));
		toggleEnableStreakP2->setAnchorPoint({0.5f, 0.5f});
		toggleEnableStreakP2->setPosition({30.f, 30.f});
		toggleEnableStreakP2->setScale(0.7f);
		toggleEnableStreakP2->setID("toggle-enable-streak-p2");
		m_togglesP2Page2->addChild(toggleEnableStreakP2);
		bool toggleEnableStreakP2State = fancy::settings.p2ChangeStreak;
		toggleEnableStreakP2->toggle(toggleEnableStreakP2State ? 1 : 0);

		// streak config
		auto toggleStreakConfig = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleStreakConfigCallback));
		toggleStreakConfig->setAnchorPoint({0.5f, 0.5f});
		toggleStreakConfig->setPosition({15.f, 15.f});
		toggleStreakConfig->setScale(0.7f);
		toggleStreakConfig->setID("toggle-streak-config");
		toggleStreakConfigMenu->addChild(toggleStreakConfig);
		bool toggleStreakConfigState = fancy::settings.streakConfigure;
		toggleStreakConfig->toggle(toggleStreakConfigState ? 1 : 0);

		auto toggleStreakFadeSlider = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakFadeSliderCallback));
		toggleStreakFadeSlider->setAnchorPoint({0.5f, 0.5f});
		toggleStreakFadeSlider->setPosition({15.f, 80.f});
		toggleStreakFadeSlider->setScale(0.6f);
		toggleStreakFadeSlider->setID("toggle-streak-fade-slider");
		m_toggleSlidersMenu->addChild(toggleStreakFadeSlider);
		bool toggleStreakFadeSliderState = fancy::settings.streakFadeEnable;
		toggleStreakFadeSlider->toggle(toggleStreakFadeSliderState ? 1 : 0);

		auto toggleStreakStrokeSlider = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakStrokeSliderCallback));
		toggleStreakStrokeSlider->setAnchorPoint({0.5f, 0.5f});
		toggleStreakStrokeSlider->setPosition({15.f, 50.f});
		toggleStreakStrokeSlider->setScale(0.6f);
		toggleStreakStrokeSlider->setID("toggle-streak-stroke-slider");
		m_toggleSlidersMenu->addChild(toggleStreakStrokeSlider);
		bool toggleStreakStrokeSliderState = fancy::settings.streakStrokeEnable;
		toggleStreakStrokeSlider->toggle(toggleStreakStrokeSliderState ? 1 : 0);

		auto toggleStreakRepeatSlider = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakRepeatSliderCallback));
		toggleStreakRepeatSlider->setAnchorPoint({0.5f, 0.5f});
		toggleStreakRepeatSlider->setPosition({15.f, 20.f});
		toggleStreakRepeatSlider->setScale(0.6f);
		toggleStreakRepeatSlider->setID("toggle-streak-repeat-slider");
		m_toggleSlidersMenu->addChild(toggleStreakRepeatSlider);
		bool toggleStreakRepeatSliderState = fancy::settings.streakRepeatEnable;
		toggleStreakRepeatSlider->toggle(toggleStreakRepeatSliderState ? 1 : 0);

		auto toggleStreakAlwaysShow = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakAlwaysShowCallback));
		toggleStreakAlwaysShow->setAnchorPoint({0.5f, 0.5f});
		toggleStreakAlwaysShow->setPosition({15.f, 61.f});
		toggleStreakAlwaysShow->setScale(0.6f);
		toggleStreakAlwaysShow->setID("toggle-streak-always-show");
		m_streakMiscToggles->addChild(toggleStreakAlwaysShow);
		bool toggleStreakAlwaysShowState = fancy::settings.streakAlwaysShow;
		toggleStreakAlwaysShow->toggle(toggleStreakAlwaysShowState ? 1 : 0);
		
		auto toggleStreakAlign = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakAlignCallback));
		toggleStreakAlign->setAnchorPoint({0.5f, 0.5f});
		toggleStreakAlign->setPosition({15.f, 38.f});
		toggleStreakAlign->setScale(0.6f);
		toggleStreakAlign->setID("toggle-streak-align");
		m_streakMiscToggles->addChild(toggleStreakAlign);
		bool toggleStreakAlignState = fancy::settings.streakAlign;
		toggleStreakAlign->toggle(toggleStreakAlignState ? 1 : 0);

		auto toggleStreakBlend = CCMenuItemToggler::create(toggleOffSprStreak, toggleOnSprStreak, this, menu_selector(FancyPopup::toggleStreakBlendCallback));
		toggleStreakBlend->setAnchorPoint({0.5f, 0.5f});
		toggleStreakBlend->setPosition({15.f, 15.f});
		toggleStreakBlend->setScale(0.6f);
		toggleStreakBlend->setID("toggle-streak-blend");
		m_streakMiscToggles->addChild(toggleStreakBlend);
		bool toggleStreakBlendState = fancy::settings.streakBlend;
		toggleStreakBlend->toggle(toggleStreakBlendState ? 1 : 0);

		// page 3
		auto toggleAlignParticles = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleAlignParticlesCallback));
		toggleAlignParticles->setAnchorPoint({0.5f, 0.5f});
		toggleAlignParticles->setPosition({15.f, 125.f});
		toggleAlignParticles->setScale(0.6f);
		toggleAlignParticles->setID("toggle-align-particles");
		page3Menu->addChild(toggleAlignParticles);
		bool toggleAlignParticlesState = fancy::settings.alignParticles;
		toggleAlignParticles->toggle(toggleAlignParticlesState ? 1 : 0);

		auto toggleCustomTrail = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleCustomTrailCallback));
		toggleCustomTrail->setAnchorPoint({0.5f, 0.5f});
		toggleCustomTrail->setPosition({15.f, 35.f});
		toggleCustomTrail->setScale(0.6f);
		toggleCustomTrail->setID("toggle-custom-trail");
		page3Menu->addChild(toggleCustomTrail);
		bool toggleCustomTrailState = fancy::settings.customStreak;
		toggleCustomTrail->toggle(toggleCustomTrailState ? 1 : 0);

		auto toggleStreakAlignWave = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleStreakAlignWaveCallback));
		toggleStreakAlignWave->setAnchorPoint({0.5f, 0.5f});
		toggleStreakAlignWave->setPosition({15.f, 95.f});
		toggleStreakAlignWave->setScale(0.6f);
		toggleStreakAlignWave->setID("toggle-streak-align-wave");
		page3Menu->addChild(toggleStreakAlignWave);
		bool toggleStreakAlignWaveState = fancy::settings.streakAlignWave;
		toggleStreakAlignWave->toggle(toggleStreakAlignWaveState ? 1 : 0);

		auto toggleScaleRadius = CCMenuItemToggler::create(toggleOffSpr, toggleOnSpr, this, menu_selector(FancyPopup::toggleScaleRadiusCallback));
		toggleScaleRadius->setAnchorPoint({0.5f, 0.5f});
		toggleScaleRadius->setPosition({15.f, 65.f});
		toggleScaleRadius->setScale(0.6f);
		toggleScaleRadius->setID("toggle-scale-radius");
		page3Menu->addChild(toggleScaleRadius);
		bool toggleScaleRadiusState = fancy::settings.changeRadius;
		toggleScaleRadius->toggle(toggleScaleRadiusState ? 1 : 0);


		/*-----
		Sliders
		-----*/


		// main
		auto rgbspeed = SliderNode::create([this](SliderNode* slider, float value) {
			this->rgbSpeedSliderCallback(value);
		}, 0);
		rgbspeed->setMin(0.1f);
		rgbspeed->setMax(1.f);
		rgbspeed->setValue(fancy::settings.rgbSpeed);
		rgbspeed->setPosition({180.f, 25.f});
		rgbspeed->setID("rgb-speed-slider");
		rgbspeed->setScale(0.9f);
		rgbspeed->setSnapStep(0.1f);
		m_mainLayer->addChild(rgbspeed);

		// page 2
		m_streakFadeSlider = SliderNode::create([this](SliderNode* slider, float value) {
			this->streakFadeSliderCallback(value);
		}, 0);
		m_streakFadeSlider->setMin(0.1f);
		m_streakFadeSlider->setMax(2.f);
		m_streakFadeSlider->setValue(fancy::settings.streakFade);
		m_streakFadeSlider->setPosition({220.f, 148.f});
		m_streakFadeSlider->setID("streak-fade-slider");
		m_streakFadeSlider->setScale(0.6f);
		m_streakFadeSlider->setSnapStep(0.1f);
		page2Layer->addChild(m_streakFadeSlider);

		m_streakStrokeSlider = SliderNode::create([this](SliderNode* slider, float value) {
			this->streakStrokeSliderCallback(value);
		}, 0);
		m_streakStrokeSlider->setMin(1.f);
		m_streakStrokeSlider->setMax(30.f);
		m_streakStrokeSlider->setValue(fancy::settings.streakStroke);
		m_streakStrokeSlider->setPosition({220.f, 118.f});
		m_streakStrokeSlider->setID("streak-stroke-slider");
		m_streakStrokeSlider->setScale(0.6f);
		m_streakStrokeSlider->setSnapStep(1.f);
		page2Layer->addChild(m_streakStrokeSlider);

		m_streakRepeatSlider = SliderNode::create([this](SliderNode* slider, float value) {
			this->streakRepeatSliderCallback(value);
		}, 0);
		m_streakRepeatSlider->setMin(0.f);
		m_streakRepeatSlider->setMax(1.f);
		m_streakRepeatSlider->setValue(fancy::settings.streakRepeat);
		m_streakRepeatSlider->setPosition({220.f, 88.f});
		m_streakRepeatSlider->setID("streak-repeat-slider");
		m_streakRepeatSlider->setScale(0.6f);
		m_streakRepeatSlider->setSnapStep(0.05f);
		page2Layer->addChild(m_streakRepeatSlider);


		/*----------------------------
		Purely Logic Passed This Point
		----------------------------*/


		m_mainLayer->getChildByID("page-2-layer")->setVisible(false);
		m_mainLayer->getChildByID("page-3-layer")->setVisible(false);

		if (!fancy::settings.p2Enable) {
			m_togglesP2Page1->setEnabled(false);
			setOpacityOfItems(m_togglesP2Page1, 100);
			m_group1P2Page1->setEnabled(false);
			setOpacityOfItems(m_group1P2Page1, 100);
			m_group2P2Page1->setEnabled(false);
			setOpacityOfItems(m_group2P2Page1, 100);
			m_group3P2Page1->setEnabled(false);
			setOpacityOfItems(m_group3P2Page1, 100);
			m_togglesP2Page2->setEnabled(false);
			setOpacityOfItems(m_togglesP2Page2, 100);
			m_group1P2Page2->setEnabled(false);
			setOpacityOfItems(m_group1P2Page2, 100);

			colorPickerParticleStartP2->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-start-color")));
			colorPickerParticleFinishP2->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-finish-color")));
			colorPickerDashFireP2->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color"));
			colorPickerSpiderDashP2->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color"));
			colorPickerStreakP2->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-streak-color"));
		}

		if (!fancy::settings.p1ChangeParticles) {
			m_group1P1Page1->setEnabled(false);
			setOpacityOfItems(m_group1P1Page1, 100);
		}

		if (!fancy::settings.p1ChangeDashFire) {
			m_group2P1Page1->setEnabled(false);
			setOpacityOfItems(m_group2P1Page1, 100);
		}

		if (!fancy::settings.p1ChangeSpiderDash) {
			m_group3P1Page1->setEnabled(false);
			setOpacityOfItems(m_group3P1Page1, 100);
		}

		if (!fancy::settings.p1ChangeStreak) {
			m_group1P1Page2->setEnabled(false);
			setOpacityOfItems(m_group1P1Page2, 100);
		}

		if (!fancy::settings.p2ChangeParticles && fancy::settings.p2Enable) {
			m_group1P2Page1->setEnabled(false);
			setOpacityOfItems(m_group1P2Page1, 100);
		}

		if (!fancy::settings.p2ChangeDashFire && fancy::settings.p2Enable) {
			m_group2P2Page1->setEnabled(false);
			setOpacityOfItems(m_group2P2Page1, 100);
		}

		if (!fancy::settings.p2ChangeSpiderDash && fancy::settings.p2Enable) {
			m_group3P2Page1->setEnabled(false);
			setOpacityOfItems(m_group3P2Page1, 100);
		}

		if (!fancy::settings.p2ChangeStreak && fancy::settings.p2Enable) {
			m_group1P2Page2->setEnabled(false);
			setOpacityOfItems(m_group1P2Page2, 100);
		}

		if (!fancy::settings.streakConfigure) {
			m_toggleSlidersMenu->setEnabled(false);
			setOpacityOfItems(m_toggleSlidersMenu, 100);
			m_streakMiscToggles->setEnabled(false);
			setOpacityOfItems(m_streakMiscToggles, 100);
			m_streakFadeSlider->setEnabled(false);
			m_streakFadeSlider->setOpacity(100);
			m_streakStrokeSlider->setEnabled(false);
			m_streakStrokeSlider->setOpacity(100);
			m_streakRepeatSlider->setEnabled(false);
			m_streakRepeatSlider->setOpacity(100);
		}

		this->scheduleUpdate();
		return true;
	}


	/*---------------------------
	Section 2: Callback Functions
	---------------------------*/


	// buttons
	void backArrowCallback(CCObject* sender) {
		if (CurrentPage == 1) {
			CurrentPage = 3;
			m_mainLayer->getChildByID("page-1-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-3-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("3/3");
		}
		else if (CurrentPage == 2) {
			CurrentPage = 1;
			m_mainLayer->getChildByID("page-2-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-1-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("1/3");
		}
		else if (CurrentPage == 3) {
			CurrentPage = 2;
			m_mainLayer->getChildByID("page-3-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-2-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("2/3");
		}
	}

	void forwardArrowCallback(CCObject* sender) {
		if (CurrentPage == 1) {
			CurrentPage = 2;
			m_mainLayer->getChildByID("page-1-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-2-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("2/3");
		}
		else if (CurrentPage == 2) {
			CurrentPage = 3;
			m_mainLayer->getChildByID("page-2-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-3-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("3/3");
		}
		else if (CurrentPage == 3) {
			CurrentPage = 1;
			m_mainLayer->getChildByID("page-3-layer")->setVisible(false);
			m_mainLayer->getChildByID("page-1-layer")->setVisible(true);
			auto pageNumberLabel = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("page-number-label"));
			pageNumberLabel->setString("1/3");
		}
	}

	// info buttons
	void fancyPlayerInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Configuration Info",
			"<cg>Player 1/2 Link</c>\nWhen linked, player 2 will copy player 1's color settings. Unlink to configure player 2's colors separately.",
			"OK",
			nullptr,
			300.f,
			nullptr,
			true,
			true
		);
	}

	void enableStreakConfigInfoCallback(CCObject* sender) {
		FLAlertLayer::create(
			nullptr,
			"Streak Configuration Info",
			"Streak configuration settings will be applied to both player 1 and player 2.\n<cr>These settings will be disabled when the Nyan Cat preset is enabled and, if playing, require reentering the level to take effect.</c>\n\n<cy>Width</c>\nSets the width of the streak, with 30 being the width of one block.\n\n<cg>Repeat</c>\nSets the number of times the image is repeated. No repeat means the image will be stretched. (e.g. Fire Streak)",
			"OK",
			nullptr,
			350.f,
			false,
			315.f,
			0.75f
		)->show();
	}

	void streakBlendInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"This option will disable the additive blending normally present on streaks.",
			"OK",
			nullptr,
			220.f,
			nullptr,
			true,
			true
		);
	}

	void streakAlignInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"When enabled, the player streak will be aligned vertically to the Ship/UFO. Useful for high-width streaks.",
			"OK",
			nullptr,
			280.f,
			nullptr,
			true,
			true
		);
	}

	void alignInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"When enabled, Ship/UFO particles will be aligned vertically to the player.\n<cy>This will only be useful to some people with custom particles.</c>",
			"OK",
			nullptr,
			300.f,
			nullptr,
			true,
			true
		);
	}

	void streakAlignWaveInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"When enabled, the player streak will be more accurately aligned to the wave.\n<cr>This does NOT affect the wave trail.</c>",
			"OK",
			nullptr,
			270.f,
			nullptr,
			true,
			true
		);
	}

	void scaleRadiusInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"When enabled, the radius setting of emitter-type player particles will be scaled based on the player's size.\n<cy>The default particles are of the gravity-type, so unless you have custom particles, you'll never use this.</c>\nDon't use if you have 'Classic Particles' enabled.",
			"OK",
			nullptr,
			330.f,
			nullptr,
			true,
			true
		);
	}

	void customInfoCallback(CCObject* sender) {
		createQuickPopup(
			"Info",
			"This will configure the streak effect to poorly mimic the Nyan Cat rainbow.\n<cr>If playing, this requires reentering the level to take effect.</c>",
			"OK",
			nullptr,
			320.f,
			nullptr,
			true,
			true
		);
	}


	// toggle boxes
	// link
	void toggleLinkCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-enable", state);
		if (state) {
			m_togglesP2Page1->setEnabled(true);
			setOpacityOfItems(m_togglesP2Page1, 255);
			m_togglesP2Page2->setEnabled(true);
			setOpacityOfItems(m_togglesP2Page2, 255);

			if (Mod::get()->getSavedValue<bool>("p2-change-particles")) {
				m_group1P2Page1->setEnabled(true);
				setOpacityOfItems(m_group1P2Page1, 255);
			}
			else {
				m_group1P2Page1->setEnabled(false);
				setOpacityOfItems(m_group1P2Page1, 100);
			}

			if (Mod::get()->getSavedValue<bool>("p2-change-dash-fire")) {
				m_group2P2Page1->setEnabled(true);
				setOpacityOfItems(m_group2P2Page1, 255);
			}
			else {
				m_group2P2Page1->setEnabled(false);
				setOpacityOfItems(m_group2P2Page1, 100);
			}

			if (Mod::get()->getSavedValue<bool>("p2-change-spider-dash")) {
				m_group3P2Page1->setEnabled(true);
				setOpacityOfItems(m_group3P2Page1, 255);
			}
			else {
				m_group3P2Page1->setEnabled(false);
				setOpacityOfItems(m_group3P2Page1, 100);
			}

			if (Mod::get()->getSavedValue<bool>("p2-change-streak")) {
				m_group1P2Page2->setEnabled(true);
				setOpacityOfItems(m_group1P2Page2, 255);
			}
			else {
				m_group1P2Page2->setEnabled(false);
				setOpacityOfItems(m_group1P2Page2, 100);
			}

			auto pscp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
			auto pfcp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
			pscp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-start-color")));
			pfcp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-finish-color")));

			auto rdfp2c = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
			rdfp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color"));

			auto rsdp2c = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
			rsdp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color"));

			auto rsp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
			rsp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-streak-color"));
		}
		else {
			m_togglesP2Page1->setEnabled(false);
			setOpacityOfItems(m_togglesP2Page1, 100);
			m_group1P2Page1->setEnabled(false);
			setOpacityOfItems(m_group1P2Page1, 100);
			m_group2P2Page1->setEnabled(false);
			setOpacityOfItems(m_group2P2Page1, 100);
			m_group3P2Page1->setEnabled(false);
			setOpacityOfItems(m_group3P2Page1, 100);
			m_togglesP2Page2->setEnabled(false);
			setOpacityOfItems(m_togglesP2Page2, 100);
			m_group1P2Page2->setEnabled(false);
			setOpacityOfItems(m_group1P2Page2, 100);

			auto pscp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
			auto pfcp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
			pscp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-start-color")));
			pfcp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-finish-color")));

			auto rdfp2c = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
			rdfp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color"));

			auto rsdp2c = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
			rsdp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color"));

			auto rsp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
			rsp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-streak-color"));
		}
	}

	// player 1
	void toggleRainbowParticlesP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-rainbow-particles", state);
		if (!state) {
			auto btn1 = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-start-p1"));
			auto btn2 = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-finish-p1"));
			btn1->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-start-color")));
			btn2->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-finish-color")));
			if (!Mod::get()->getSavedValue<bool>("p2-enable")) {
				auto pscp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
				auto pfcp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
				pscp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-start-color")));
				pfcp2c->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p1-finish-color")));
			}
		}
	}

	void toggleRainbowDashFireP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-rainbow-dash-fire", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P1Page1->getChildByID("color-picker-dash-fire-p1"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color"));
			if (!Mod::get()->getSavedValue<bool>("p2-enable")) {
				auto rdfp2c = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
				rdfp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color"));
			}
		}
	}

	void toggleRainbowSpiderDashP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-rainbow-spider-dash", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P1Page1->getChildByID("color-picker-spider-dash-p1"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color"));
			if (!Mod::get()->getSavedValue<bool>("p2-enable")) {
				auto rsdp2c = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
				rsdp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color"));
			}
		}
	}

	void toggleRainbowStreakP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-rainbow-streak", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page2->getChildByID("color-picker-streak-p1"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-streak-color"));
			if (!Mod::get()->getSavedValue<bool>("p2-enable")) {
				auto rsp2c = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
				rsp2c->setColor(Mod::get()->getSavedValue<ccColor3B>("p1-streak-color"));
			}
		}
	}

	void toggleEnableParticlesP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-change-particles", state);
		if (state) {
			m_group1P1Page1->setEnabled(true);
			setOpacityOfItems(m_group1P1Page1, 255);
		}
		else {
			m_group1P1Page1->setEnabled(false);
			setOpacityOfItems(m_group1P1Page1, 100);
		}
	}

	void toggleEnableDashFireP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-change-dash-fire", state);
		if (state) {
			m_group2P1Page1->setEnabled(true);
			setOpacityOfItems(m_group2P1Page1, 255);
		}
		else {
			m_group2P1Page1->setEnabled(false);
			setOpacityOfItems(m_group2P1Page1, 100);
		}
	}

	void toggleEnableSpiderDashP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-change-spider-dash", state);
		if (state) {
			m_group3P1Page1->setEnabled(true);
			setOpacityOfItems(m_group3P1Page1, 255);
		}
		else {
			m_group3P1Page1->setEnabled(false);
			setOpacityOfItems(m_group3P1Page1, 100);
		}
	}

	void toggleEnableStreakP1Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p1-change-streak", state);
		if (state) {
			m_group1P1Page2->setEnabled(true);
			setOpacityOfItems(m_group1P1Page2, 255);
		}
		else {
			m_group1P1Page2->setEnabled(false);
			setOpacityOfItems(m_group1P1Page2, 100);
		}
	}

	// player 2
	void toggleRainbowParticlesP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-rainbow-particles", state);
		if (!state) {
			auto btn1 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
			auto btn2 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
			btn1->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-start-color")));
			btn2->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-finish-color")));
		}
	}

	void toggleRainbowDashFireP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-rainbow-dash-fire", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color"));
		}
	}

	void toggleRainbowSpiderDashP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-rainbow-spider-dash", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color"));
		}
	}

	void toggleRainbowStreakP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-rainbow-streak", state);
		if (!state) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-streak-color"));
		}
	}

	void toggleEnableParticlesP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-change-particles", state);
		if (state) {
			m_group1P2Page1->setEnabled(true);
			setOpacityOfItems(m_group1P2Page1, 255);
		}
		else {
			m_group1P2Page1->setEnabled(false);
			setOpacityOfItems(m_group1P2Page1, 100);
			auto btn1 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
			auto btn2 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
			btn1->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-start-color")));
			btn2->setColor(color4BTo3B(Mod::get()->getSavedValue<ccColor4B>("p2-finish-color")));
		}
	}

	void toggleEnableDashFireP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-change-dash-fire", state);
		if (state) {
			m_group2P2Page1->setEnabled(true);
			setOpacityOfItems(m_group2P2Page1, 255);
		}
		else {
			m_group2P2Page1->setEnabled(false);
			setOpacityOfItems(m_group2P2Page1, 100);
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color"));
		}
	}

	void toggleEnableSpiderDashP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-change-spider-dash", state);
		if (state) {
			m_group3P2Page1->setEnabled(true);
			setOpacityOfItems(m_group3P2Page1, 255);
		}
		else {
			m_group3P2Page1->setEnabled(false);
			setOpacityOfItems(m_group3P2Page1, 100);
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color"));
		}
	}

	void toggleEnableStreakP2Callback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("p2-change-streak", state);
		if (state) {
			m_group1P2Page2->setEnabled(true);
			setOpacityOfItems(m_group1P2Page2, 255);
		}
		else {
			m_group1P2Page2->setEnabled(false);
			setOpacityOfItems(m_group1P2Page2, 100);
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
			btn->setColor(Mod::get()->getSavedValue<ccColor3B>("p2-streak-color"));
		}
	}

	// global
	void toggleAlignParticlesCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("align-particles", state);
	}

	void toggleCustomTrailCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("custom-streak", state);
	}

	// streak config
	void toggleStreakConfigCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-configure", state);
		if (state) {
			m_toggleSlidersMenu->setEnabled(true);
			setOpacityOfItems(m_toggleSlidersMenu, 255);
			m_streakMiscToggles->setEnabled(true);
			setOpacityOfItems(m_streakMiscToggles, 255);

			if (Mod::get()->getSavedValue<bool>("streak-fade-enable")) {
				m_streakFadeSlider->setEnabled(true);
				m_streakFadeSlider->setOpacity(255);
			}
			else {
				m_streakFadeSlider->setEnabled(false);
				m_streakFadeSlider->setOpacity(100);
			}

			if (Mod::get()->getSavedValue<bool>("streak-stroke-enable")) {
				m_streakStrokeSlider->setEnabled(true);
				m_streakStrokeSlider->setOpacity(255);
			}
			else {
				m_streakStrokeSlider->setEnabled(false);
				m_streakStrokeSlider->setOpacity(100);
			}

			if (Mod::get()->getSavedValue<bool>("streak-repeat-enable")) {
				m_streakRepeatSlider->setEnabled(true);
				m_streakRepeatSlider->setOpacity(255);
			}
			else {
				m_streakRepeatSlider->setEnabled(false);
				m_streakRepeatSlider->setOpacity(100);
			}
		}
		else {
			m_toggleSlidersMenu->setEnabled(false);
			setOpacityOfItems(m_toggleSlidersMenu, 100);
			m_streakMiscToggles->setEnabled(false);
			setOpacityOfItems(m_streakMiscToggles, 100);

			m_streakFadeSlider->setEnabled(false);
			m_streakFadeSlider->setOpacity(100);
			m_streakStrokeSlider->setEnabled(false);
			m_streakStrokeSlider->setOpacity(100);
			m_streakRepeatSlider->setEnabled(false);
			m_streakRepeatSlider->setOpacity(100);
		}
	}

	void toggleStreakFadeSliderCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-fade-enable", state);
		if (state) {
			m_streakFadeSlider->setEnabled(true);
			m_streakFadeSlider->setOpacity(255);
		}
		else {
			m_streakFadeSlider->setEnabled(false);
			m_streakFadeSlider->setOpacity(100);
		}
	}

	void toggleStreakStrokeSliderCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-stroke-enable", state);
		if (state) {
			m_streakStrokeSlider->setEnabled(true);
			m_streakStrokeSlider->setOpacity(255);
		}
		else {
			m_streakStrokeSlider->setEnabled(false);
			m_streakStrokeSlider->setOpacity(100);
		}
	}

	void toggleStreakRepeatSliderCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-repeat-enable", state);
		if (state) {
			m_streakRepeatSlider->setEnabled(true);
			m_streakRepeatSlider->setOpacity(255);
		}
		else {
			m_streakRepeatSlider->setEnabled(false);
			m_streakRepeatSlider->setOpacity(100);
		}
	}

	void toggleStreakAlwaysShowCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-always-show", state);
	}

	void toggleStreakAlignWaveCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-align-wave", state);
	}

	void toggleScaleRadiusCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("change-radius", state);
	}

	void toggleStreakAlignCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-align", state);
	}

	void toggleStreakBlendCallback(CCObject* sender) {
		auto toggle = static_cast<CCMenuItemToggler*>(sender);
		bool state = !toggle->isToggled();
		Mod::get()->setSavedValue("streak-blend", state);
	}

	// sliders
	void rgbSpeedSliderCallback(float value) {
		Mod::get()->setSavedValue("rgb-speed", value);
		m_rgbfslbl->setString(numToString(value, 1).c_str());
	}

	void streakFadeSliderCallback(float value) {
		Mod::get()->setSavedValue("streak-fade", value);
		m_streakFadeNumberLabel->setString(numToString(value, 1).c_str());
	}

	void streakStrokeSliderCallback(float value) {
		Mod::get()->setSavedValue("streak-stroke", value);
		m_streakStrokeNumberLabel->setString(numToString(value, 1).c_str());
	}

	void streakRepeatSliderCallback(float value) {
		Mod::get()->setSavedValue("streak-repeat", value);
		m_streakRepeatNumberLabel->setString(numToString(value, 2).c_str());
	}

	// color pickers
	// player 1
	void colorPickerParticleStartP1Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor4B>("p1-start-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerParticleStartP1CallbackCallback(color);
		});
		popup->show();
	}
	void colorPickerParticleStartP1CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p1-start-color", color);
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-start-p1"));
		btn->setColor(color4BTo3B(color));
	} // callback-ception

	void colorPickerParticleFinishP1Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor4B>("p1-finish-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerParticleFinishP1CallbackCallback(color);
		});
		popup->show();
	}
	void colorPickerParticleFinishP1CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p1-finish-color", color);
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-finish-p1"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerDashFireP1Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerDashFireP1CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerDashFireP1CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p1-dash-fire-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P1Page1->getChildByID("color-picker-dash-fire-p1"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerSpiderDashP1Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerSpiderDashP1CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerSpiderDashP1CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p1-spider-dash-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P1Page1->getChildByID("color-picker-spider-dash-p1"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerStreakP1Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p1-streak-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerStreakP1CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerStreakP1CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p1-streak-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page2->getChildByID("color-picker-streak-p1"));
		btn->setColor(color4BTo3B(color));
	}

	// player 2
	void colorPickerParticleStartP2Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor4B>("p2-start-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerParticleStartP2CallbackCallback(color);
		});
		popup->show();
	}
	void colorPickerParticleStartP2CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p2-start-color", color);
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerParticleFinishP2Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor4B>("p2-finish-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerParticleFinishP2CallbackCallback(color);
		});
		popup->show();
	}
	void colorPickerParticleFinishP2CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p2-finish-color", color);
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerDashFireP2Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerDashFireP2CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerDashFireP2CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p2-dash-fire-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
		btn->setColor(color4BTo3B(color));
	}
	
	void colorPickerSpiderDashP2Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerSpiderDashP2CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerSpiderDashP2CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p2-spider-dash-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
		btn->setColor(color4BTo3B(color));
	}

	void colorPickerStreakP2Callback(CCObject* sender) {
		auto popup = ColorPickPopup::create(Mod::get()->getSavedValue<ccColor3B>("p2-streak-color"));
		popup->setCallback([this](const ccColor4B& color) {
			this->colorPickerStreakP2CallbackCallback({color.r, color.g, color.b, 255});
		});
		popup->show();
	}
	void colorPickerStreakP2CallbackCallback(const ccColor4B& color) {
		Mod::get()->setSavedValue("p2-streak-color", ccc3(color.r, color.g, color.b));
		auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
		btn->setColor(color4BTo3B(color));
	}


	/*---------------
	Utility Functions
	---------------*/

	
	char const* getThemeSpriteName() {
		auto theme = Mod::get()->getSettingValue<std::string>("mod-theme");
		if (theme == "Brown") return "GJ_square01.png";
		else if (theme == "Blue") return "GJ_square02.png";
		else if (theme == "Green") return "GJ_square03.png";
		else if (theme == "Purple") return "GJ_square04.png";
		else if (theme == "Gray") return "GJ_square05.png";
		else if (theme == "White") return "GJ_square06.png";
		else return "GJ_square01.png";
	}

	ccColor3B getThemePrimaryColor() {
		auto theme = Mod::get()->getSettingValue<std::string>("mod-theme");
		if (theme == "Brown") return {111, 60, 24};
		else if (theme == "Blue") return {42, 52, 108};
		else if (theme == "Green") return {56, 115, 47};
		else if (theme == "Purple") return {58, 25, 96};
		else if (theme == "Gray") return {56, 56, 56};
		else if (theme == "White") return {152, 152, 152};
		else return {111, 60, 24};
	}

	ccColor3B getThemeSecondaryColor() {
		auto theme = Mod::get()->getSettingValue<std::string>("mod-theme");
		if (theme == "Brown") return {133, 68, 41};
		else if (theme == "Blue") return {51, 67, 125};
		else if (theme == "Green") return {66, 144, 66};
		else if (theme == "Purple") return {72, 42, 108};
		else if (theme == "Gray") return {70, 70, 70};
		else if (theme == "White") return {176, 176, 176};
		else return {133, 68, 41};
	}

	ccColor3B color4BTo3B(const ccColor4B& color) {
		return {color.r, color.g, color.b};
	} // convert ccColor4B to ccColor3B

	void setOpacityOfItems(CCMenu* menu, GLubyte opacity) {
		for (auto item : menu->getChildrenExt<CCMenuItemSpriteExtra*>()) {
			if (item->getOpacity() == opacity) continue;
			item->setOpacity(opacity);
		}
		for (auto toggler : menu->getChildrenExt<CCMenuItemToggler*>()) {
			for (auto item : toggler->getChildrenExt<CCMenuItemSpriteExtra*>()) {
				if (item->getOpacity() == opacity) continue;
				item->setOpacity(opacity);
			}
		}
	} // set opacity of MenuItemSpriteExtra instances

	void update(float dt) {
		runHue = Mod::get()->getSavedValue<bool>("p1-rainbow-particles") || Mod::get()->getSavedValue<bool>("p1-rainbow-dash-fire") || Mod::get()->getSavedValue<bool>("p1-rainbow-spider-dash") || Mod::get()->getSavedValue<bool>("p1-rainbow-streak") || Mod::get()->getSavedValue<bool>("p2-rainbow-particles") || Mod::get()->getSavedValue<bool>("p2-rainbow-dash-fire") || Mod::get()->getSavedValue<bool>("p2-rainbow-spider-dash") || Mod::get()->getSavedValue<bool>("p2-rainbow-streak");
		if (runHue) {
			hue += dt * Mod::get()->getSavedValue<float>("rgb-speed") * 2.f;
			if (hue > 1.f) hue -= 1.f;
			cocos2d::ccColor4F colorf = FancyPlayer::HSVtoRGB(hue, 1.f, 1.f, 1.f);
			cocos2d::ccColor3B colorb = FancyPlayer::color4Fto3B(colorf);
			updateRainbowParticlesP1Button(colorb);
			updateRainbowDashFireP1Button(colorb);
			updateRainbowSpiderDashP1Button(colorb);
			updateRainbowStreakP1Button(colorb);
			updateRainbowParticlesP2Button(colorb);
			updateRainbowDashFireP2Button(colorb);
			updateRainbowSpiderDashP2Button(colorb);
			updateRainbowStreakP2Button(colorb);
		}
	}

	void updateRainbowParticlesP1Button(ccColor3B color) {
		if (Mod::get()->getSavedValue<bool>("p1-rainbow-particles")) {
			auto btn1 = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-start-p1"));
			auto btn2 = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page1->getChildByID("color-picker-particle-finish-p1"));
			btn1->setColor(color);
			btn2->setColor(color);
		}
	}

	void updateRainbowDashFireP1Button(ccColor3B color) {
		if (Mod::get()->getSavedValue<bool>("p1-rainbow-dash-fire")) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P1Page1->getChildByID("color-picker-dash-fire-p1"));
			btn->setColor(color);
		}
	}

	void updateRainbowSpiderDashP1Button(ccColor3B color) {
		if (Mod::get()->getSavedValue<bool>("p1-rainbow-spider-dash")) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P1Page1->getChildByID("color-picker-spider-dash-p1"));
			btn->setColor(color);
		}
	}

	void updateRainbowStreakP1Button(ccColor3B color) {
		if (Mod::get()->getSavedValue<bool>("p1-rainbow-streak")) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P1Page2->getChildByID("color-picker-streak-p1"));
			btn->setColor(color);
		}
	}

	void updateRainbowParticlesP2Button(ccColor3B color) {
		if ((Mod::get()->getSavedValue<bool>("p2-enable") && Mod::get()->getSavedValue<bool>("p2-change-particles") && Mod::get()->getSavedValue<bool>("p2-rainbow-particles")) || (Mod::get()->getSavedValue<bool>("p1-rainbow-particles") && !Mod::get()->getSavedValue<bool>("p2-enable"))) {
			auto btn1 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-start-p2"));
			auto btn2 = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page1->getChildByID("color-picker-particle-finish-p2"));
			btn1->setColor(color);
			btn2->setColor(color);
		}
	}

	void updateRainbowDashFireP2Button(ccColor3B color) {
		if ((Mod::get()->getSavedValue<bool>("p2-enable") && Mod::get()->getSavedValue<bool>("p2-change-dash-fire") && Mod::get()->getSavedValue<bool>("p2-rainbow-dash-fire")) || (Mod::get()->getSavedValue<bool>("p1-rainbow-dash-fire") && !Mod::get()->getSavedValue<bool>("p2-enable"))) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group2P2Page1->getChildByID("color-picker-dash-fire-p2"));
			btn->setColor(color);
		}
	}

	void updateRainbowSpiderDashP2Button(ccColor3B color) {
		if ((Mod::get()->getSavedValue<bool>("p2-enable") && Mod::get()->getSavedValue<bool>("p2-change-spider-dash") && Mod::get()->getSavedValue<bool>("p2-rainbow-spider-dash")) || (Mod::get()->getSavedValue<bool>("p1-rainbow-spider-dash") && !Mod::get()->getSavedValue<bool>("p2-enable"))) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group3P2Page1->getChildByID("color-picker-spider-dash-p2"));
			btn->setColor(color);
		}
	}

	void updateRainbowStreakP2Button(ccColor3B color) {
		if ((Mod::get()->getSavedValue<bool>("p2-enable") && Mod::get()->getSavedValue<bool>("p2-change-streak") && Mod::get()->getSavedValue<bool>("p2-rainbow-streak")) || (Mod::get()->getSavedValue<bool>("p1-rainbow-streak") && !Mod::get()->getSavedValue<bool>("p2-enable"))) {
			auto btn = static_cast<CCMenuItemSpriteExtra*>(m_group1P2Page2->getChildByID("color-picker-streak-p2"));
			btn->setColor(color);
		}
	}

	void updateSettings() {
		/*---------------
		player 1 settings
		---------------*/
		fancy::settings.p1ChangeParticles = Mod::get()->getSavedValue<bool>("p1-change-particles");
		fancy::settings.p1RainbowParticles = Mod::get()->getSavedValue<bool>("p1-rainbow-particles");
		fancy::settings.p1StartColor = Mod::get()->getSavedValue<ccColor4B>("p1-start-color");
		fancy::settings.p1StartColorF = { // p1 startColor float
				fancy::settings.p1StartColor.r / 255.f,
				fancy::settings.p1StartColor.g / 255.f,
				fancy::settings.p1StartColor.b / 255.f,
				fancy::settings.p1StartColor.a / 255.f
			};
		fancy::settings.p1FinishColor = Mod::get()->getSavedValue<ccColor4B>("p1-finish-color");
		fancy::settings.p1FinishColorF = { // p1 finishColor float
				fancy::settings.p1FinishColor.r / 255.f,
				fancy::settings.p1FinishColor.g / 255.f,
				fancy::settings.p1FinishColor.b / 255.f,
				fancy::settings.p1FinishColor.a / 255.f
			};
		fancy::settings.p1ChangeDashFire = Mod::get()->getSavedValue<bool>("p1-change-dash-fire");
		fancy::settings.p1RainbowDashFire = Mod::get()->getSavedValue<bool>("p1-rainbow-dash-fire");
		fancy::settings.p1DashFireColor = Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color");
		fancy::settings.p1ChangeSpiderDash = Mod::get()->getSavedValue<bool>("p1-change-spider-dash");
		fancy::settings.p1RainbowSpiderDash = Mod::get()->getSavedValue<bool>("p1-rainbow-spider-dash");
		fancy::settings.p1SpiderDashColor = Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color");
		fancy::settings.p1ChangeStreak = Mod::get()->getSavedValue<bool>("p1-change-streak");
		fancy::settings.p1RainbowStreak = Mod::get()->getSavedValue<bool>("p1-rainbow-streak");
		fancy::settings.p1StreakColor = Mod::get()->getSavedValue<ccColor3B>("p1-streak-color");
		/*---------------
		player 2 settings
		---------------*/
		fancy::settings.p2Enable = Mod::get()->getSavedValue<bool>("p2-enable");
		fancy::settings.p2ChangeParticles = Mod::get()->getSavedValue<bool>("p2-change-particles");
		fancy::settings.p2RainbowParticles = Mod::get()->getSavedValue<bool>("p2-rainbow-particles");
		fancy::settings.p2StartColor = Mod::get()->getSavedValue<ccColor4B>("p2-start-color");
		fancy::settings.p2StartColorF = { // p2 startColor float
				fancy::settings.p2StartColor.r / 255.f,
				fancy::settings.p2StartColor.g / 255.f,
				fancy::settings.p2StartColor.b / 255.f,
				fancy::settings.p2StartColor.a / 255.f
			};
		fancy::settings.p2FinishColor = Mod::get()->getSavedValue<ccColor4B>("p2-finish-color");
		fancy::settings.p2FinishColorF = { // p2 finishColor float
				fancy::settings.p2FinishColor.r / 255.f,
				fancy::settings.p2FinishColor.g / 255.f,
				fancy::settings.p2FinishColor.b / 255.f,
				fancy::settings.p2FinishColor.a / 255.f
			};
		fancy::settings.p2ChangeDashFire = Mod::get()->getSavedValue<bool>("p2-change-dash-fire");
		fancy::settings.p2RainbowDashFire = Mod::get()->getSavedValue<bool>("p2-rainbow-dash-fire");
		fancy::settings.p2DashFireColor = Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color");
		fancy::settings.p2ChangeSpiderDash = Mod::get()->getSavedValue<bool>("p2-change-spider-dash");
		fancy::settings.p2RainbowSpiderDash = Mod::get()->getSavedValue<bool>("p2-rainbow-spider-dash");
		fancy::settings.p2SpiderDashColor = Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color");
		fancy::settings.p2ChangeStreak = Mod::get()->getSavedValue<bool>("p2-change-streak");
		fancy::settings.p2RainbowStreak = Mod::get()->getSavedValue<bool>("p2-rainbow-streak");
		fancy::settings.p2StreakColor = Mod::get()->getSavedValue<ccColor3B>("p2-streak-color");
		/*-------------
		global settings
		-------------*/
		fancy::settings.rgbSpeed = Mod::get()->getSavedValue<float>("rgb-speed");
		fancy::settings.changeRadius = Mod::get()->getSavedValue<bool>("change-radius");
		fancy::settings.alignParticles = Mod::get()->getSavedValue<bool>("align-particles");
		fancy::settings.customStreak = Mod::get()->getSavedValue<bool>("custom-streak");
		/*-------------
		streak settings
		-------------*/
		fancy::settings.streakConfigure = Mod::get()->getSavedValue<bool>("streak-configure");
		fancy::settings.streakFadeEnable = Mod::get()->getSavedValue<bool>("streak-fade-enable");
		fancy::settings.streakFade = Mod::get()->getSavedValue<float>("streak-fade");
		fancy::settings.streakStrokeEnable = Mod::get()->getSavedValue<bool>("streak-stroke-enable");
		fancy::settings.streakStroke = Mod::get()->getSavedValue<float>("streak-stroke");
		fancy::settings.streakRepeatEnable = Mod::get()->getSavedValue<bool>("streak-repeat-enable");
		fancy::settings.streakRepeat = Mod::get()->getSavedValue<float>("streak-repeat");
		fancy::settings.streakAlign = Mod::get()->getSavedValue<bool>("streak-align");
		fancy::settings.streakAlignWave = Mod::get()->getSavedValue<bool>("streak-align-wave");
		fancy::settings.streakBlend = Mod::get()->getSavedValue<bool>("streak-blend");
		fancy::settings.streakAlwaysShow = Mod::get()->getSavedValue<bool>("streak-always-show");
	}

	void onClose(CCObject* sender) {
		Popup::onClose(sender);
		updateSettings();
	}
public:
	static FancyPopup* create() {
		auto ret = new FancyPopup();
		if (ret && ret->init()) {
			ret->autorelease();
			return ret;
		}
		delete ret;
		return nullptr;
	} // popup create function
};
