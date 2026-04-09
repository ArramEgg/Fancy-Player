#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "SettingsMenu.hpp"
#include "Utilities.hpp"
#include "Settings.hpp"

using namespace geode::prelude;

namespace fancy
{
	Settings settings;
} // mod settings

enum PlayerMode {
    Cube,
    Ship,
    Bird,
    Dart,
    Robot,
    Spider,
    Swing
}; // enums for custom utility function getCurrentMode() in $modify(PlayerObject)


class $modify(FPGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;

		// create the things
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto menu = CCMenu::create();
		menu->setContentSize({50.f, 50.f});
		menu->setPosition({winSize.width * 0.9f, winSize.height * 0.4f});
		auto spr = CCSprite::create("FP_logoBtn_001.png"_spr);
		spr->setScale(0.8f);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(FPGarageLayer::onLogoBtn));
		btn->setAnchorPoint({0.5f, 0.5f});
		btn->setPosition({25.f, 25.f});
		menu->setID("fancy-menu");
		btn->setID("fancy-button");

		// add the things
		menu->addChild(btn);
		menu->updateLayout();
		this->addChild(menu);
		return true;
	}
	void onLogoBtn(CCObject *) {
		FancyPopup::create()->show();
	}
}; // add button to garage


class $modify(FPPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
		
		// create button
		auto spr = CCSprite::create("FP_logoBtn_001.png"_spr);
		spr->setScale(0.65f);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(FPPauseLayer::onLogoBtn));
		btn->setAnchorPoint({0.5f, 0.5f});
		btn->setID("fancy-button");
		
		// add button
		if (auto menu = this->getChildByID("right-button-menu")) {
			menu->addChild(btn);
			menu->updateLayout();
		}
	}
	void onLogoBtn(CCObject *) {
		FancyPopup::create()->show();
	}
}; // add button to pause menu


class $modify(FPPlayerObject, PlayerObject) {
	static void onModify(auto& self) {
		// set updateDashAnimation to last so Mega Hack doesn't mysteriously override it
		(void)self.setHookPriorityPost("PlayerObject::updateDashAnimation", Priority::Last);
	} // hook priorities (with explanations)

	
	struct Fields {
		bool lastUpsideDown = false;
		PlayerMode lastMode = Cube;
		std::unordered_map<CCParticleSystemQuad*, float> baseRadius;
		float hue = 0.f;
		float lastHue = 0.f;
		bool lastOnGround = false;
		bool runHue = false;
		int playerStreak = GameManager::sharedState()->getPlayerStreak();
	}; // fields for comparing changes


	/* -------------
	Section 1: Hooks
	--------------*/


	void activateStreak() {
		PlayerObject::activateStreak();
		if (fancy::settings.streakConfigure && fancy::settings.streakStrokeEnable && !fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize);
			}
		}
		if (fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize);
			}
		}
	} // call when streak is activated


	void hitGround(GameObject* object, bool notFlipped) {
		PlayerObject::hitGround(object, notFlipped);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		modifyPlayerParticles();
	} // call when hitting the ground


	bool init(int player, int ship, GJBaseGameLayer * gameLayer, cocos2d::CCLayer * layer, bool playLayer) {
		if (!PlayerObject::init(player, ship, gameLayer, layer, playLayer)) return false;

		// no need to update fields without particles
		if (!fancy::settings.p1ChangeParticles && !fancy::settings.p2ChangeParticles) return true;

		// get fields ready for comparison
		m_fields->lastUpsideDown = m_isUpsideDown;
		m_fields->lastMode = getCurrentMode();
		m_fields->lastOnGround = m_isOnGround2;
		return true;
	} // end of PlayerObject:init()


	void loadFromCheckpoint(PlayerCheckpoint* object) {
		PlayerObject::loadFromCheckpoint(object);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		modifyPlayerParticles();
	} // call when loading from checkpoint


	void playSpiderDashEffect(CCPoint from, CCPoint to) {
		int before = GJBaseGameLayer::get()->m_objectLayer->getChildrenCount();
		PlayerObject::playSpiderDashEffect(from, to);
		int after = GJBaseGameLayer::get()->m_objectLayer->getChildrenCount();
		
		for (int i = before; i < after; ++i) {
			auto child = GJBaseGameLayer::get()->m_objectLayer->getChildByIndex(i);
			if (auto sprite = typeinfo_cast<CCSprite*>(child)) {
				colorSpiderDashSprite(sprite);
			}
			if (auto circle = typeinfo_cast<CCCircleWave*>(child)) {
				colorSpiderDashCircle(circle);
			}
		}
	} // call when doing the cool spider thing


	void resetObject() {
		PlayerObject::resetObject();

		// player 2 check
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		
		// epic hack doubles as a mega hack reset fix + UFO reset bug fix (forces update next tick)
		m_fields->lastMode = static_cast<PlayerMode>((getCurrentMode() + 1) % 7);
		modifyPlayerParticles();
	} // call on player reset


	void resetStreak() {
		PlayerObject::resetStreak();
		if (fancy::settings.customStreak) {
			CCPoint pos = this->getPosition();
			this->m_regularTrail->setPosition(pos + ccp(5.f, 0.f));
		}
	} // dumb hack to reduce custom streak flipping, mainly on level start


	void setupStreak() {
		PlayerObject::setupStreak();
		if (fancy::settings.streakConfigure && !fancy::settings.customStreak) {
			if (fancy::settings.streakFadeEnable) {
				this->m_regularTrail->updateFade(fancy::settings.streakFade);
			}
			if (fancy::settings.streakRepeatEnable) {
				if (fancy::settings.streakRepeat > 0.f) {
					this->m_regularTrail->enableRepeatMode(fancy::settings.streakRepeat);
				}
				else {
					this->m_regularTrail->m_bRepeatMode = false;
				}
			}
			if (fancy::settings.streakBlend) {
				this->m_regularTrail->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
			}
			if (fancy::settings.streakAlwaysShow) {
				this->m_alwaysShowStreak = true;
			}
		} // streak slop
		if (fancy::settings.customStreak) {
			this->m_regularTrail->updateFade(1.f);
			this->m_regularTrail->setStroke(26.f);
			this->m_regularTrail->m_bRepeatMode = false;
			this->m_regularTrail->setTexture(CCTextureCache::sharedTextureCache()->addImage("customStreak_001.png"_spr, 0));
			this->m_regularTrail->setOpacity(255);
			this->m_regularTrail->setDontOpacityFade(true);
			this->m_regularTrail->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
			this->m_alwaysShowStreak = true;
		} // absolute cinema
	} // call on streak setup 


	void toggleDartMode(bool enable, bool noEffects) {
		PlayerObject::toggleDartMode(enable, noEffects);
		if (fancy::settings.streakConfigure && fancy::settings.streakStrokeEnable && !fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize);
			}
		}
		if (fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize);
			}
		}
	} // evil


	void togglePlayerScale(bool enable, bool noEffects) {
		PlayerObject::togglePlayerScale(enable, noEffects);
		modifyParticleRadius();
		if (fancy::settings.streakConfigure && fancy::settings.streakStrokeEnable && !fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(fancy::settings.streakStroke * m_vehicleSize);
			}
		}
		if (fancy::settings.customStreak) {
			if (m_isDart) {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize * 0.5f);
			}
			else {
				this->m_regularTrail->setStroke(26.f * m_vehicleSize);
			}
		}
	} // call on size changes


    void update(float dt) {
        PlayerObject::update(dt);

		// update hue or nah?
		m_fields->runHue = fancy::settings.p1RainbowParticles || fancy::settings.p1RainbowDashFire || fancy::settings.p1RainbowSpiderDash || fancy::settings.p1RainbowStreak || (fancy::settings.p2Enable && (fancy::settings.p2RainbowParticles || fancy::settings.p2RainbowDashFire || fancy::settings.p2RainbowSpiderDash || fancy::settings.p2RainbowStreak));

		if (m_fields->runHue) {
			m_fields->hue += dt * (fancy::settings.rgbSpeed * 0.05f);
			if (m_fields->hue > 1.f) m_fields->hue -= 1.f;
		} // update hue for rainbow effects

		// player 2 check
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		// update effects if player 1 or 2 is enabled (player 2 check is done in each effect's respective function)
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		bool rainbowDashFire = p2 ? fancy::settings.p2RainbowDashFire : fancy::settings.p1RainbowDashFire;
		bool changeStreak = fancy::settings.p1ChangeStreak || (fancy::settings.p2Enable && fancy::settings.p2ChangeStreak);

		if (changeParticles) {
			if (rainbowParticles) {
				modifyPlayerParticles();
			} // color particles per frame if rainbow fade is on
			else {
				PlayerMode mode = getCurrentMode();
				if (m_isUpsideDown != m_fields->lastUpsideDown || mode != m_fields->lastMode || m_isOnGround2 != m_fields->lastOnGround) {
					// update fields when changes occur
					m_fields->lastUpsideDown = m_isUpsideDown;
					m_fields->lastMode = mode;
					m_fields->lastOnGround = m_isOnGround2;
					// color particles after changes
					if (changeParticles) {
						modifyPlayerParticles();
					}
				} // check for player changes
			} // otherwise only color on changes
		} // change particles if enabled

		if (fancy::settings.customStreak) {
			this->m_regularTrail->tintWithColor({255, 255, 255});
		} // bruh
		
		if (rainbowDashFire) {
			if (m_fields->lastHue != m_fields->hue) {
				updateDashColor();
			} // avoid double update just in case
		} // rainbow dash fire

		if (changeStreak) {
			modifyPlayerStreak();
		} // ROW, ROW, FIGHT THE POWAH

		if (m_isDart && (fancy::settings.streakAlignWave || fancy::settings.customStreak)) {
			this->m_regularTrail->setPosition(this->getPosition());
		} // align streak to wave
    } // put stuff here to update/check per tick


	void updateDashAnimation() {
		PlayerObject::updateDashAnimation();
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeDashFire = p2 ? fancy::settings.p2ChangeDashFire : fancy::settings.p1ChangeDashFire;
		if (!changeDashFire) return;
		updateDashColor();
	} // color dash fire


	void updateShipRotation(float dt) {
		PlayerObject::updateShipRotation(dt);
		alignParticlesToPlayer();
		alignStreakToPlayer();
	} // ROW, ROW, FIGHT THE POWAH


	void updateStreakBlend(bool blend) {	
		PlayerObject::updateStreakBlend(blend);
		if ((fancy::settings.streakBlend && fancy::settings.streakConfigure) || fancy::settings.customStreak) {
			this->m_regularTrail->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
		}
	} // disable additive blending if enabled


	/*-------------------------
	Section 2: Custom functions
	-------------------------*/


	void alignParticlesToPlayer() {
		if (!fancy::settings.alignParticles) return;
		if (!(m_isShip || m_isBird)) return;
		bool reverse = m_isGoingLeft;
		float plusMinus = reverse ? 10.f : -10.f;
		CCPoint offset = ccpRotateByAngle({plusMinus * m_vehicleSize, 0.f}, {0.f, 0.f}, -CC_DEGREES_TO_RADIANS(this->getRotation()));
		CCPoint alignPoint = ccpAdd(this->getPosition(), offset);

		auto alignParticle = [alignPoint](CCParticleSystemQuad* p) {
			if (!p) return;
			p->setPosition(alignPoint);
		}; // c++ is cool, yo

		alignParticle(m_shipClickParticles);
		alignParticle(m_ufoClickParticles);
		alignParticle(m_trailingParticles);
	} // align ship/ufo particles if enabled


	void alignStreakToPlayer() {
		if (!(m_isShip || m_isBird)) return;
		if (!this->m_regularTrail) return;
		if ((fancy::settings.customStreak) || (fancy::settings.streakConfigure && fancy::settings.streakAlign)) {
			this->m_regularTrail->setPosition(this->getPosition());
		}
	} // align custom streak if enabled

	
	void colorDashSprite(CCSprite* d) {
		if (!d) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowDashFire = p2 ? fancy::settings.p2RainbowDashFire : fancy::settings.p1RainbowDashFire;
		if (rainbowDashFire) {
			cocos2d::ccColor4F color = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			d->setColor(FancyPlayer::color4Fto3B(color));
			return;
		}
		if (p2 && fancy::settings.p2ChangeDashFire) {
			d->setColor(fancy::settings.p2DashFireColor);
			return;
		}
		d->setColor(fancy::settings.p1DashFireColor);
	} // function for coloring dash fire sprite


	void colorSpiderDashCircle(CCCircleWave* c) {
		if (!c) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;

		ccColor3B col;
		bool rainbowSpiderDash = p2 ? fancy::settings.p2RainbowSpiderDash : fancy::settings.p1RainbowSpiderDash;
		if (rainbowSpiderDash) {
			cocos2d::ccColor4F color = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			col = FancyPlayer::color4Fto3B(color);
			c->m_color = col;
			return;
		}
		if (p2 && fancy::settings.p2ChangeSpiderDash) {
			c->m_color = fancy::settings.p2SpiderDashColor;
			return;
		}
		c->m_color = fancy::settings.p1SpiderDashColor;
	} // function for coloring spider dash circles


	void colorSpiderDashSprite(CCSprite* s) {
		if (!s) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowSpiderDash = p2 ? fancy::settings.p2RainbowSpiderDash : fancy::settings.p1RainbowSpiderDash;
		if (rainbowSpiderDash) {
			cocos2d::ccColor4F color = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			s->setColor(FancyPlayer::color4Fto3B(color));
			return;
		}
		if (p2 && fancy::settings.p2ChangeSpiderDash) {
			s->setColor(fancy::settings.p2SpiderDashColor);
			return;
		}
		s->setColor(fancy::settings.p1SpiderDashColor);
	} // function for coloring spider dash sprite


    void modifyParticles(CCParticleSystemQuad* p) {
        if (!p) return;
		// player 2 check
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		if (rainbowParticles) {
			float startAlpha = p2 ? fancy::settings.p2StartColorF.a : fancy::settings.p1StartColorF.a;
			float finishAlpha = p2 ? fancy::settings.p2FinishColorF.a : fancy::settings.p1FinishColorF.a;
			cocos2d::ccColor4F startColor = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, startAlpha);
			cocos2d::ccColor4F endColor = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, finishAlpha);
			p->setStartColor(startColor);
			p->setEndColor(endColor);
		} // rainbow color
		else if (p2) {
			p->setStartColor(fancy::settings.p2StartColorF);
			p->setEndColor(fancy::settings.p2FinishColorF);
		} // normal color p2
		else {
			p->setStartColor(fancy::settings.p1StartColorF);
			p->setEndColor(fancy::settings.p1FinishColorF);
		} // normal color p1
    } // function to modify particles

	void modifyPlayerStreak() {
		if (!this->m_regularTrail) return;
		if (fancy::settings.customStreak) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		ccColor3B streakColor = p2 ? fancy::settings.p2StreakColor : fancy::settings.p1StreakColor;
		bool rainbowStreak = p2 ? fancy::settings.p2RainbowStreak : fancy::settings.p1RainbowStreak;
		if (rainbowStreak) {
			cocos2d::ccColor4F color = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			this->m_regularTrail->tintWithColor(FancyPlayer::color4Fto3B(color));
			return;
		}
		if (m_regularTrail->getColor() == streakColor) return;
		if (p2 && fancy::settings.p2ChangeStreak) {
			this->m_regularTrail->tintWithColor(fancy::settings.p2StreakColor);
			return;
		}
		this->m_regularTrail->tintWithColor(fancy::settings.p1StreakColor);
	} // function to modify streak

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
	} // select which particle systems to modify


	void modifyParticleRadius() {
		modifyRadius(m_playerGroundParticles);
		modifyRadius(m_trailingParticles);
		modifyRadius(m_shipClickParticles);
		modifyRadius(m_vehicleGroundParticles);
		modifyRadius(m_ufoClickParticles);
		modifyRadius(m_robotBurstParticles);
		modifyRadius(m_dashParticles);
		modifyRadius(m_swingBurstParticles1);
		modifyRadius(m_swingBurstParticles2);
		modifyRadius(m_landParticles0);
		modifyRadius(m_landParticles1);
	} // select which particle systems to modify radius of


	void modifyRadius(CCParticleSystemQuad* p) { // probably a good idea to make this check if the emitter type is radius
		if (!fancy::settings.changeRadius) return;
		if (!p) return;
		if (!m_fields->baseRadius.contains(p)) {
			m_fields->baseRadius[p] = p->getStartRadius();
		} // radius scale
		float base = m_fields->baseRadius[p];
		p->setStartRadius(base * m_vehicleSize);
	} // function to modify emiiter type 1 radius


	void updateDashColor() {
		if (!m_dashFireSprite) return;
		colorDashSprite(m_dashFireSprite);
		m_fields->lastHue = m_fields->hue;
	} // color dash fire sprite

	
	/*---------------------------------
	Section 3: Custom Utility Functions
	---------------------------------*/
	
	PlayerMode getCurrentMode() {
		if (m_isShip) return Ship;
		if (m_isBird) return Bird;
		if (m_isDart) return Dart;
		if (m_isRobot) return Robot;
		if (m_isSpider) return Spider;
		if (m_isSwing) return Swing;
		return Cube;
	} // used for optimized particle color changing
}; // modify PlayerObject