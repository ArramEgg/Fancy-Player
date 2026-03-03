#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

namespace fancy
{
	struct Settings
	{
		bool p1ChangeParticles = false;
		bool p1RainbowParticles = false;
		ccColor4B p1StartColor = {255, 255, 255, 255};
		ccColor4F p1StartColorF = {1.f, 1.f, 1.f, 1.f};
		ccColor4B p1FinishColor = {255, 255, 255, 255};
		ccColor4F p1FinishColorF = {1.f, 1.f, 1.f, 1.f};
		bool p1ChangeDashFire = false;
		bool p1RainbowDashFire = false;
		ccColor3B p1DashFireColor = {255, 255, 255};
		bool p1ChangeSpiderDash = false;
		bool p1RainbowSpiderDash = false;
		ccColor3B p1SpiderDashColor = {255, 255, 255};
		bool p2Enable = false;
		bool p2ChangeParticles = false;
		bool p2RainbowParticles = false;
		ccColor4B p2StartColor = {255, 255, 255, 255};
		ccColor4F p2StartColorF = {1.f, 1.f, 1.f, 1.f};
		ccColor4B p2FinishColor = {255, 255, 255, 255};
		ccColor4F p2FinishColorF = {1.f, 1.f, 1.f, 1.f};
		bool p2ChangeDashFire = false;
		bool p2RainbowDashFire = false;
		ccColor3B p2DashFireColor = {255, 255, 255};
		bool p2ChangeSpiderDash = false;
		bool p2RainbowSpiderDash = false;
		ccColor3B p2SpiderDashColor = {255, 255, 255};
		float rgbSpeed = 0.1f;
		bool changeRadius = false;
		bool addButton = false;
	} settings;
}

// enums for getCurrentMode
enum PlayerMode {
    Cube,
    Ship,
    Bird,
    Dart,
    Robot,
    Spider,
    Swing
};


// obligatory comment #1
class $modify(FPGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;

		// make button or nah?
		fancy::settings.addButton = Mod::get()->getSettingValue<bool>("add-button");
		if (!fancy::settings.addButton) return true;

		// add settings button
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto menu = CCMenu::create();
		menu->setPosition({winSize.width * 0.95f, winSize.height * 0.44f});
		auto spr = CCSprite::create("FP_logoBtn_001.png"_spr);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(FPGarageLayer::onLogoBtn));
		btn->setAnchorPoint({0.5f, 0.5f});
		btn->setScale(0.8f);
		menu->addChild(btn);
		menu->updateLayout();
		menu->setID("fancy-menu");
		btn->setID("fancy-button");
		this->addChild(menu);
		return true;
	}

	// i really don't need to add all these comments but i'm still going to... you're welcome
	void onLogoBtn(CCObject *) {
		openSettingsPopup(Mod::get());
	}
};


// obligatory comment #2
/*
class $modify(FPPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
		auto spr = CCSprite::create("FP_logoBtn_001.png"_spr);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(FPPauseLayer::onLogoBtn));
		btn->setAnchorPoint({0.5f, 0.5f});
		btn->setID("fancy-button");
		if (auto menu = this->getChildByID("right-button-menu")) {
			menu->addChild(btn);
			menu->updateLayout();
		}
	}
	void onLogoBtn(CCObject *) {
		openSettingsPopup(Mod::get());
	}
};
*/

// obligatory comment #3
class $modify(PlayerObject) {
	// set priority to last so mega hack doesn't override change
	static void onModify(auto& self) {
		(void)self.setHookPriorityPost("PlayerObject::updateDashAnimation", Priority::Last);
	}

	// fields for comparing against changes
	struct Fields {
		bool lastUpsideDown = false;
		PlayerMode lastMode = Cube;
		float lastVehicleSize = 1.f;
		std::unordered_map<CCParticleSystemQuad*, float> baseRadius;
		float hue = 0.f;
		float lastHue = 0.f;
		bool lastOnGround = false;
		bool runHue = false;
	};

	// player init (my beloved)
	bool init(int player, int ship, GJBaseGameLayer * gameLayer, cocos2d::CCLayer * layer, bool playLayer) {
		if (!PlayerObject::init(player, ship, gameLayer, layer, playLayer)) return false;

		// THE GREAT, UGLY WALL OF SETTINGS
		// player 1 settings
		fancy::settings.p1ChangeParticles = Mod::get()->getSettingValue<bool>("p1-change-particles");
		fancy::settings.p1RainbowParticles = Mod::get()->getSettingValue<bool>("p1-rainbow-particles");
		fancy::settings.p1StartColor = Mod::get()->getSettingValue<ccColor4B>("p1-start-color");
		fancy::settings.p1StartColorF = {
				fancy::settings.p1StartColor.r / 255.f,
				fancy::settings.p1StartColor.g / 255.f,
				fancy::settings.p1StartColor.b / 255.f,
				fancy::settings.p1StartColor.a / 255.f
			}; // not too sure about this one chief
		fancy::settings.p1FinishColor = Mod::get()->getSettingValue<ccColor4B>("p1-finish-color");
		fancy::settings.p1FinishColorF = {
				fancy::settings.p1FinishColor.r / 255.f,
				fancy::settings.p1FinishColor.g / 255.f,
				fancy::settings.p1FinishColor.b / 255.f,
				fancy::settings.p1FinishColor.a / 255.f
			}; // like i'm making two fields to do one thing
		fancy::settings.p1ChangeDashFire = Mod::get()->getSettingValue<bool>("p1-change-dash-fire");
		fancy::settings.p1RainbowDashFire = Mod::get()->getSettingValue<bool>("p1-rainbow-dash-fire");
		fancy::settings.p1DashFireColor = Mod::get()->getSettingValue<ccColor3B>("p1-dash-fire-color");
		fancy::settings.p1ChangeSpiderDash = Mod::get()->getSettingValue<bool>("p1-change-spider-dash");
		fancy::settings.p1RainbowSpiderDash = Mod::get()->getSettingValue<bool>("p1-rainbow-spider-dash");
		fancy::settings.p1SpiderDashColor = Mod::get()->getSettingValue<ccColor3B>("p1-spider-dash-color");
		// player 2 settings
		fancy::settings.p2Enable = Mod::get()->getSettingValue<bool>("p2-enable");
		fancy::settings.p2ChangeParticles = Mod::get()->getSettingValue<bool>("p2-change-particles");
		fancy::settings.p2RainbowParticles = Mod::get()->getSettingValue<bool>("p2-rainbow-particles");
		fancy::settings.p2StartColor = Mod::get()->getSettingValue<ccColor4B>("p2-start-color");
		fancy::settings.p2StartColorF = {
				fancy::settings.p2StartColor.r / 255.f,
				fancy::settings.p2StartColor.g / 255.f,
				fancy::settings.p2StartColor.b / 255.f,
				fancy::settings.p2StartColor.a / 255.f
			}; // it's some stupid way of converting 4B to 4F (and it works)
		fancy::settings.p2FinishColor = Mod::get()->getSettingValue<ccColor4B>("p2-finish-color");
		fancy::settings.p2FinishColorF = {
				fancy::settings.p2FinishColor.r / 255.f,
				fancy::settings.p2FinishColor.g / 255.f,
				fancy::settings.p2FinishColor.b / 255.f,
				fancy::settings.p2FinishColor.a / 255.f
			}; // but still i can't help but question myself... thank you for reading
		fancy::settings.p2ChangeDashFire = Mod::get()->getSettingValue<bool>("p2-change-dash-fire");
		fancy::settings.p2RainbowDashFire = Mod::get()->getSettingValue<bool>("p2-rainbow-dash-fire");
		fancy::settings.p2DashFireColor = Mod::get()->getSettingValue<ccColor3B>("p2-dash-fire-color");
		fancy::settings.p2ChangeSpiderDash = Mod::get()->getSettingValue<bool>("p2-change-spider-dash");
		fancy::settings.p2RainbowSpiderDash = Mod::get()->getSettingValue<bool>("p2-rainbow-spider-dash");
		fancy::settings.p2SpiderDashColor = Mod::get()->getSettingValue<ccColor3B>("p2-spider-dash-color");
		// global settings
		fancy::settings.rgbSpeed = Mod::get()->getSettingValue<float>("rgb-speed") * 0.1f;
		fancy::settings.changeRadius = Mod::get()->getSettingValue<bool>("change-radius");

		// no need to update fields without particles
		if (!fancy::settings.p1ChangeParticles && !fancy::settings.p2ChangeParticles) return true;

		// get fields ready for comparison
		m_fields->lastUpsideDown = m_isUpsideDown;
		m_fields->lastMode = getCurrentMode();
		m_fields->lastVehicleSize = m_vehicleSize;
		m_fields->lastOnGround = m_isOnGround2;
		m_fields->runHue = fancy::settings.p1RainbowParticles || fancy::settings.p1RainbowDashFire || fancy::settings.p1RainbowSpiderDash || (fancy::settings.p2Enable && (fancy::settings.p2RainbowParticles || fancy::settings.p2RainbowDashFire || fancy::settings.p2RainbowSpiderDash));
		return true;
	}

	// MORE HOOKS

	// call when hitting the ground
	void hitGround(GameObject* object, bool notFlipped) {
		PlayerObject::hitGround(object, notFlipped);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		modifyPlayerParticles();
	}

	// call when loading from checkpoint
	void loadFromCheckpoint(PlayerCheckpoint* object) {
		PlayerObject::loadFromCheckpoint(object);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		modifyPlayerParticles();
	}

	// call when doing the cool spider thing
	void playSpiderDashEffect(CCPoint from, CCPoint to) {
		auto parent = this->getParent();
		int before = parent->getChildrenCount();
		PlayerObject::playSpiderDashEffect(from, to);
		int after = parent->getChildrenCount();
		
		for (int i = before; i < after; ++i) {
			auto child = parent->getChildByIndex(i);
			if (auto sprite = typeinfo_cast<CCSprite*>(child)) {
				colorSpiderDashSprite(sprite);
			}
			if (auto circle = typeinfo_cast<CCCircleWave*>(child)) {
				colorSpiderDashCircle(circle);
			}
		}
	}

	// call on player reset
	void resetObject() {
		PlayerObject::resetObject();
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		// epic hack doubles as a mega hack reset fix + UFO reset bug fix
		m_fields->lastMode = static_cast<PlayerMode>((getCurrentMode() + 1) % 7);
		modifyPlayerParticles();
	}

	// color dash fire
	void updateDashAnimation() {
		PlayerObject::updateDashAnimation();
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeDashFire = p2 ? fancy::settings.p2ChangeDashFire : fancy::settings.p1ChangeDashFire;
		if (!changeDashFire) return;
		updateDashColor();
	}

	// put stuff here to update/check per tick
    void update(float dt) {
        PlayerObject::update(dt);

		// update hue for rainbow effects
		if (m_fields->runHue) {
				m_fields->hue += dt * fancy::settings.rgbSpeed;
			if (m_fields->hue > 1.f) m_fields->hue -= 1.f;
		}
		// player 2 check
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		bool rainbowDashFire = p2 ? fancy::settings.p2RainbowDashFire : fancy::settings.p1RainbowDashFire;
		// change particles
		if (changeParticles) {
			// color particles per frame if rainbow fade is on
			if (rainbowParticles) {
				modifyPlayerParticles();
			}
			// otherwise only color on changes
			else {
				// check for player changes
				PlayerMode mode = getCurrentMode();
				if (m_isUpsideDown != m_fields->lastUpsideDown || mode != m_fields->lastMode || m_vehicleSize != m_fields->lastVehicleSize || m_isOnGround2 != m_fields->lastOnGround) {
					// update fields when changes occur
					m_fields->lastUpsideDown = m_isUpsideDown;
					m_fields->lastMode = mode;
					m_fields->lastVehicleSize = m_vehicleSize;
					m_fields->lastOnGround = m_isOnGround2;
					// color particles after changes
					modifyPlayerParticles();
				}
			}
		}

		// rainbow dash fire
		if (rainbowDashFire) {
			// avoid double update just in case
			if (m_fields->lastHue != m_fields->hue) {
				updateDashColor();
			}
		}
    }

	// CUSTOM FUNCTIONS
	// yo mama
	PlayerMode getCurrentMode() {
		if (m_isShip) return Ship;
		if (m_isBird) return Bird;
		if (m_isDart) return Dart;
		if (m_isRobot) return Robot;
		if (m_isSpider) return Spider;
		if (m_isSwing) return Swing;
		return Cube;
	}

	// select which particle systems to modify
	void modifyPlayerParticles() {
		modifyParticles(m_playerGroundParticles);
		modifyParticles(m_trailingParticles);
		modifyParticles(m_shipClickParticles);
		modifyParticles(m_vehicleGroundParticles);
		modifyParticles(m_ufoClickParticles);
		modifyParticles(m_robotBurstParticles);
		modifyParticles(m_dashParticles);
		modifyParticles(m_swingBurstParticles1);
		modifyParticles(m_swingBurstParticles2);
		modifyParticles(m_landParticles0);
		modifyParticles(m_landParticles1);
	}

	// function to set particle colors
    void modifyParticles(CCParticleSystemQuad* p) {
        if (!p) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		// rainbow color
		if (rainbowParticles) {
			float startAlpha = p2 ? fancy::settings.p2StartColorF.a : fancy::settings.p1StartColorF.a;
			float finishAlpha = p2 ? fancy::settings.p2FinishColorF.a : fancy::settings.p1FinishColorF.a;
			cocos2d::ccColor4F startColor = HSVtoRGB(m_fields->hue, 1.f, 1.f, startAlpha);
			cocos2d::ccColor4F endColor = HSVtoRGB(m_fields->hue, 1.f, 1.f, finishAlpha);
			p->setStartColor(startColor);
			p->setEndColor(endColor);
		}
		// normal colors
		else if (p2) {
			p->setStartColor(fancy::settings.p2StartColorF);
			p->setEndColor(fancy::settings.p2FinishColorF);
		}
		else {
			p->setStartColor(fancy::settings.p1StartColorF);
			p->setEndColor(fancy::settings.p1FinishColorF);
		}
		// radius scale
		if (!fancy::settings.changeRadius) return;
		if (!m_fields->baseRadius.contains(p)) {
			m_fields->baseRadius[p] = p->getStartRadius();
		}
		float base = m_fields->baseRadius[p];
		p->setStartRadius(base * m_vehicleSize);
    }

	// function for coloring spider dash circles
	void colorSpiderDashCircle(CCCircleWave* c) {
		if (!c) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;

		ccColor3B col;
		bool rainbowSpiderDash = p2 ? fancy::settings.p2RainbowSpiderDash : fancy::settings.p1RainbowSpiderDash;
		if (rainbowSpiderDash) {
			cocos2d::ccColor4F color = HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			col = color4Fto3B(color);
			c->m_color = col;
			return;
		}
		if (p2 && fancy::settings.p2ChangeSpiderDash) {
			c->m_color = fancy::settings.p2SpiderDashColor;
			return;
		}
		c->m_color = fancy::settings.p1SpiderDashColor;
	}

	// function for coloring spider dash sprite
	void colorSpiderDashSprite(CCSprite* s) {
		if (!s) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowSpiderDash = p2 ? fancy::settings.p2RainbowSpiderDash : fancy::settings.p1RainbowSpiderDash;
		if (rainbowSpiderDash) {
			cocos2d::ccColor4F color = HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			s->setColor(color4Fto3B(color));
			return;
		}
		if (p2 && fancy::settings.p2ChangeSpiderDash) {
			s->setColor(fancy::settings.p2SpiderDashColor);
			return;
		}
		s->setColor(fancy::settings.p1SpiderDashColor);
	}

	// function for coloring dash fire sprite
	void colorDashSprite(CCSprite* d) {
		if (!d) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowDashFire = p2 ? fancy::settings.p2RainbowDashFire : fancy::settings.p1RainbowDashFire;
		if (rainbowDashFire) {
			cocos2d::ccColor4F color = HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			d->setColor(color4Fto3B(color));
			return;
		}
		if (p2 && fancy::settings.p2ChangeDashFire) {
			d->setColor(fancy::settings.p2DashFireColor);
			return;
		}
		d->setColor(fancy::settings.p1DashFireColor);
	}

	// color dash fire sprite
	void updateDashColor() {
		if (!m_dashFireSprite) return;
		colorDashSprite(m_dashFireSprite);
		m_fields->lastHue = m_fields->hue;
	}

	// hue shifter
	cocos2d::ccColor4F HSVtoRGB(float h, float s, float v, float a) {
		float r, g, b;
		int i = static_cast<int>(h * 6);
		float f = h * 6 - i;
		float p = v * (1 - s);
		float q = v * (1 - f * s);
		float t = v * (1 - (1 - f) * s);
		switch (i % 6) {
			case 0: r = v; g = t; b = p; break;
			case 1: r = q; g = v; b = p; break;
			case 2: r = p; g = v; b = t; break;
			case 3: r = p; g = q; b = v; break;
			case 4: r = t; g = p; b = v; break;
			case 5: r = v; g = p; b = q; break;
		}
		return {r, g, b, a};
	}

	// get 3 byte color from 4 float color (output from hue shifter) for sprites
	ccColor3B color4Fto3B(cocos2d::ccColor4F c) {
		return {
			static_cast<GLubyte>(c.r * 255),
			static_cast<GLubyte>(c.g * 255),
			static_cast<GLubyte>(c.b * 255)
		};
	}
};