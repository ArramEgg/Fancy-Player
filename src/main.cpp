#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/binding/PlayerObject.hpp>

using namespace geode::prelude;

namespace fancy
{
	struct Settings
	{
		bool changeParticles = false;
		bool rainbowFade = false;
		float sCR = 0.f;
		float sCG = 0.f;
		float sCB = 0.f;
		float sCA = 0.f;
		float fCR = 0.f;
		float fCG = 0.f;
		float fCB = 0.f;
		float fCA = 0.f;
		bool changeDashFire = false;
		bool rainbowDash = false;
		int dCR = 0.f;
		int dCG = 0.f;
		int dCB = 0.f;
		float rgbSpeed = 0.1f;
		bool changeRadius = false;
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

// obligatory comment
class $modify(PlayerObject) {
	// fight other mods to the death
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
	};

	// player init
	bool init(int player, int ship, GJBaseGameLayer * gameLayer, cocos2d::CCLayer * layer, bool playLayer) {
		if (!PlayerObject::init(player, ship, gameLayer, layer, playLayer)) return false;

		// wall of settings
		typedef geode::prelude::Mod mod;
		fancy::settings.changeParticles = mod::get()->getSettingValue<bool>("change-particles");
		fancy::settings.rainbowFade = mod::get()->getSettingValue<bool>("rainbow-fade");
		fancy::settings.sCR = mod::get()->getSettingValue<int>("sCR") / 255.0f;
		fancy::settings.sCG = mod::get()->getSettingValue<int>("sCG") / 255.0f;
		fancy::settings.sCB = mod::get()->getSettingValue<int>("sCB") / 255.0f;
		fancy::settings.sCA = mod::get()->getSettingValue<int>("sCA") / 255.0f;
		fancy::settings.fCR = mod::get()->getSettingValue<int>("fCR") / 255.0f;
		fancy::settings.fCG = mod::get()->getSettingValue<int>("fCG") / 255.0f;
		fancy::settings.fCB = mod::get()->getSettingValue<int>("fCB") / 255.0f;
		fancy::settings.fCA = mod::get()->getSettingValue<int>("fCA") / 255.0f;
		fancy::settings.changeDashFire = mod::get()->getSettingValue<bool>("change-dash-fire");
		fancy::settings.rainbowDash = mod::get()->getSettingValue<bool>("rainbow-dash");
		fancy::settings.dCR = mod::get()->getSettingValue<int>("dCR");
		fancy::settings.dCG = mod::get()->getSettingValue<int>("dCG");
		fancy::settings.dCB = mod::get()->getSettingValue<int>("dCB");
		fancy::settings.rgbSpeed = mod::get()->getSettingValue<float>("rgb-speed") * 0.1f;
		fancy::settings.changeRadius = mod::get()->getSettingValue<bool>("change-radius");
		if (!fancy::settings.changeParticles) return true;

		// get fields ready for comparison
		m_fields->lastUpsideDown = m_isUpsideDown;
		m_fields->lastMode = getCurrentMode();
		m_fields->lastVehicleSize = m_vehicleSize;
		m_fields->lastOnGround = m_isOnGround2;
		return true;
	}

	// call on player reset
	void resetObject() {
		PlayerObject::resetObject();
		if (!fancy::settings.changeParticles) return;
		// epic hack doubles as a mega hack reset fix + UFO reset bug fix
		m_fields->lastMode = static_cast<PlayerMode>((getCurrentMode() + 1) % 7);
		modifyPlayerParticles();
	}

	// call when loading from checkpoint
	void loadFromCheckpoint(PlayerCheckpoint* object) {
		PlayerObject::loadFromCheckpoint(object);
		if (!fancy::settings.changeParticles) return;
		modifyPlayerParticles();
	}

	// color dash fire
	void updateDashAnimation() {
		PlayerObject::updateDashAnimation();
		if (!fancy::settings.changeDashFire) return;
		updateDashColor();
	}

	// put stuff here to update/check per tick
    void update(float dt) {
        PlayerObject::update(dt);

		// update hue for rainbow effects
		if (fancy::settings.rainbowFade || fancy::settings.rainbowDash) {
			m_fields->hue += dt * fancy::settings.rgbSpeed;
			if (m_fields->hue > 1.f) m_fields->hue -= 1.f;
		}

		// change particles
		if (fancy::settings.changeParticles) {
			// color particles per frame if rainbow fade is on
			if (fancy::settings.rainbowFade) {
				modifyPlayerParticles();
			}
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

		// rainbow dash (ha) fire
		if (fancy::settings.rainbowDash) {
			if (m_fields->lastHue != m_fields->hue) {
				updateDashColor();
			}
		}
    }

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
		modifyParticles(m_ufoClickParticles);
		modifyParticles(m_robotBurstParticles);
		modifyParticles(m_dashParticles);
		modifyParticles(m_swingBurstParticles1);
		modifyParticles(m_swingBurstParticles2);
	}

	// function to set particle colors
    void modifyParticles(CCParticleSystemQuad* p) {
        if (!p || m_isDart) return;
		// normal color
		if (!fancy::settings.rainbowFade) {
        	p->setStartColor({fancy::settings.sCR, fancy::settings.sCG, fancy::settings.sCB, fancy::settings.sCA});
        	p->setEndColor({fancy::settings.fCR, fancy::settings.fCG, fancy::settings.fCB, fancy::settings.fCA});
		}
		// rainbow color
		else if (fancy::settings.rainbowFade) {
			cocos2d::ccColor4F startColor = HSVtoRGB(m_fields->hue, 1.f, 1.f, fancy::settings.sCA);
			cocos2d::ccColor4F endColor = HSVtoRGB(m_fields->hue, 1.f, 1.f, fancy::settings.fCA);
			p->setStartColor(startColor);
			p->setEndColor(endColor);
		}
		// radius scale
		if (!fancy::settings.changeRadius) return;
		if (!m_fields->baseRadius.contains(p)) {
			m_fields->baseRadius[p] = p->getStartRadius();
		}
		float base = m_fields->baseRadius[p];
		p->setStartRadius(base * m_vehicleSize);
    }

	// function for coloring sprites
	void colorSprite(CCSprite* d) {
		if (!d || !m_isDashing) return;
		if (fancy::settings.rainbowDash) {
			cocos2d::ccColor4F color = HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			d->setColor(color4Fto3B(color));
			return;
		}
		d->setColor(ccColor3B{
			static_cast<GLubyte>(fancy::settings.dCR),
			static_cast<GLubyte>(fancy::settings.dCG),
			static_cast<GLubyte>(fancy::settings.dCB)
		});
	}

	// color dash fire sprite
	void updateDashColor() {
		if (!m_dashFireSprite) return;
		colorSprite(m_dashFireSprite);
		m_fields->lastHue = m_fields->hue;
	}

	// HSV mogs
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

	// get 3 byte color from 4 float color for sprites
	ccColor3B color4Fto3B(cocos2d::ccColor4F c) {
		return {
			static_cast<GLubyte>(c.r * 255),
			static_cast<GLubyte>(c.g * 255),
			static_cast<GLubyte>(c.b * 255)
		};
	}
};