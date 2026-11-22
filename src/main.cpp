#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
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

class $modify(FPGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;

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

		menu->addChild(btn);
		menu->updateLayout();
		this->addChild(menu);
		return true;
	}
	void onLogoBtn(CCObject *) {
		FancyPopup::create()->show();
	}
};


class $modify(FPPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
		
		auto spr = CCSprite::create("FP_logoBtn_001.png"_spr);
		spr->setScale(0.575f);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(FPPauseLayer::onLogoBtn));
		btn->setAnchorPoint({0.5f, 0.5f});
		btn->setID("fancy-button");
		
		if (auto menu = this->getChildByIDRecursive("right-button-menu")) {
			menu->addChild(btn);
			menu->updateLayout();
		}
	}
	void onLogoBtn(CCObject *) {
		FancyPopup::create()->show();
	}
};


class $modify(FPGJBaseGameLayer, GJBaseGameLayer) {
	static void onModify(auto& self) {
		// set update to last so Frame Extrapolation doesn't break particle alignment
		(void)self.setHookPriorityPost("GJBaseGameLayer::update", Priority::Last);
	} // hook priorities (with explanations)


	void update(float dt) {	
		GJBaseGameLayer::update(dt);
		alignParticlesToPlayer(m_player1);
		alignStreakToPlayer(m_player1);
		if (m_gameState.m_isDualMode) {
			alignParticlesToPlayer(m_player2);
			alignStreakToPlayer(m_player2);
		}
	} // a man walked into a bar


	void alignParticlesToPlayer(PlayerObject* player) {
		if (!fancy::settings.alignParticles) return;
		if (!(player->m_isShip || player->m_isBird)) return;
		bool reverse = player->m_isGoingLeft;
		float plusMinus = reverse ? 10.f : -10.f;
		CCPoint offset = ccpRotateByAngle({plusMinus * player->m_vehicleSize, 0.f}, {0.f, 0.f}, -CC_DEGREES_TO_RADIANS(player->getRotation()));
		CCPoint alignPoint = ccpAdd(player->m_position, offset);

		auto alignParticle = [alignPoint](CCParticleSystemQuad* p) {
			if (!p) return;
			p->setPosition(alignPoint);
		};

		alignParticle(player->m_shipClickParticles);
		alignParticle(player->m_ufoClickParticles);
		alignParticle(player->m_trailingParticles);
	}


	void alignStreakToPlayer(PlayerObject* player) {
		if (!player->m_regularTrail) return;

		if ((player->m_isDart && (fancy::settings.streakAlignWave || fancy::settings.customStreak)) || ((player->m_isShip || player->m_isBird) && ((fancy::settings.customStreak) || (fancy::settings.streakConfigure && fancy::settings.streakAlign)))) {
			player->m_regularTrail->setPosition(player->m_position);
		} // W logic
	}
};


class $modify(FPPlayerObject, PlayerObject) {
	static void onModify(auto& self) {
		// set updateDashAnimation to last so Mega Hack doesn't mysteriously override it
		(void)self.setHookPriorityPost("PlayerObject::updateDashAnimation", Priority::Last);
	} // hook priorities (with explanations)

	
	struct Fields {
		std::unordered_map<CCParticleSystemQuad*, float> baseRadius;
		float hue = 0.f;
		bool runHue = false;
	};


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
	}


	void playSpiderDashEffect(CCPoint from, CCPoint to) {
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeSpiderDash = p2 ? fancy::settings.p2ChangeSpiderDash : fancy::settings.p1ChangeSpiderDash;
		
		if (!changeSpiderDash) {
			PlayerObject::playSpiderDashEffect(from, to);
			return;
		}
		
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
	}


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
		} // nyan nyan nyan nynan aaaaaaaaaaa AAAAAAAAAAAAAAA
	}
	
	
	void toggleBirdMode(bool enable, bool noEffects) {
		PlayerObject::toggleBirdMode(enable, noEffects);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles) return;
		modifyPlayerParticles();
	}


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
	}


	void toggleFlyMode(bool enable, bool noEffects) {
		PlayerObject::toggleFlyMode(enable, noEffects);
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		if (!changeParticles || !fancy::settings.bigShipFire) return;
		if (fancy::settings.bigShipFire) {
			if (this->m_shipStreak) {
				this->m_shipStreak->setM_fMaxSeg(40.f);
				this->m_shipStreak->updateFade(.2f * this->m_vehicleSize);
				this->m_shipStreak->setStroke(25.f * this->m_vehicleSize);
				this->m_shipStreak->m_fMinSeg = 20.f;
			}
		}
		if (!changeParticles) return;
		modifyPlayerParticles();
	}


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
		if (fancy::settings.bigShipFire) {
			if (this->m_shipStreak) {
				this->m_shipStreak->setM_fMaxSeg(30.f);
				this->m_shipStreak->updateFade(.2f * this->m_vehicleSize);
				this->m_shipStreak->setStroke(25.f * this->m_vehicleSize);
				this->m_shipStreak->m_fMinSeg = 20.f;
			}
		}
	}


    void update(float dt) {
        PlayerObject::update(dt);

		// update hue or nah?
		m_fields->runHue = 
			fancy::settings.p1RainbowParticles ||
			fancy::settings.p1RainbowDashFire ||
			fancy::settings.p1RainbowSpiderDash ||
			fancy::settings.p1RainbowStreak ||
			(fancy::settings.p2Enable && (
				fancy::settings.p2RainbowParticles ||
				fancy::settings.p2RainbowDashFire ||
				fancy::settings.p2RainbowSpiderDash ||
				fancy::settings.p2RainbowStreak
				)
			);

		if (m_fields->runHue) {
			m_fields->hue += dt * (fancy::settings.rgbSpeed * 0.05f);
			if (m_fields->hue > 1.f) m_fields->hue -= 1.f;
		} // update hue for rainbow effects

		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		// update effects if player 1 or 2 is enabled (player 2 check is done in each effect's respective function)
		bool changeParticles = p2 ? fancy::settings.p2ChangeParticles : fancy::settings.p1ChangeParticles;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		bool rainbowDashFire = p2 ? fancy::settings.p2RainbowDashFire : fancy::settings.p1RainbowDashFire;
		bool changeStreak = fancy::settings.p1ChangeStreak || (fancy::settings.p2Enable && fancy::settings.p2ChangeStreak);

		if (changeParticles && rainbowParticles) {
			modifyPlayerParticles();
		}

		if (changeStreak || fancy::settings.customStreak) {
			modifyPlayerStreak();
		} // bruh
    }


	void updateDashAnimation() {
		PlayerObject::updateDashAnimation();
		bool p2 = m_isSecondPlayer;
		bool changeDashFire = p2 ? fancy::settings.p2ChangeDashFire : fancy::settings.p1ChangeDashFire;
		if (!changeDashFire) return;
		if (!m_dashFireSprite) return;
		colorDashSprite(m_dashFireSprite);
	} // color dash fire


	void updateStreakBlend(bool blend) {	
		PlayerObject::updateStreakBlend(blend);
		if ((fancy::settings.streakBlend && fancy::settings.streakConfigure) || fancy::settings.customStreak) {
			this->m_regularTrail->setBlendFunc({GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
		}
	}


	void updateTimeMod(float speed, bool noEffects) {
		PlayerObject::updateTimeMod(speed, noEffects);
		if (fancy::settings.bigShipFire) {
			if (this->m_shipStreak) {
				this->m_shipStreak->setM_fMaxSeg(30.f);
				this->m_shipStreak->updateFade(.2f * this->m_vehicleSize);
				this->m_shipStreak->setStroke(25.f * this->m_vehicleSize);
				this->m_shipStreak->m_fMinSeg = 20.f;
			}
		}
	} // go listen to my music


	/*-------------------------
	Section 2: Custom functions
	-------------------------*/

	
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
	}


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
	}


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
	}

    void modifyParticles(CCParticleSystemQuad* p) {
        if (!p) return;
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		bool rainbowParticles = p2 ? fancy::settings.p2RainbowParticles : fancy::settings.p1RainbowParticles;
		if (rainbowParticles) {
			float startAlpha = p2 ? fancy::settings.p2StartColorF.a : fancy::settings.p1StartColorF.a;
			float finishAlpha = p2 ? fancy::settings.p2FinishColorF.a : fancy::settings.p1FinishColorF.a;
			cocos2d::ccColor4F startColor = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, startAlpha);
			cocos2d::ccColor4F endColor = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, finishAlpha);
			p->setStartColor(startColor);
			p->setEndColor(endColor);
		}
		else if (p2) {
			p->setStartColor(fancy::settings.p2StartColorF);
			p->setEndColor(fancy::settings.p2FinishColorF);
		}
		else {
			p->setStartColor(fancy::settings.p1StartColorF);
			p->setEndColor(fancy::settings.p1FinishColorF);
		}
    }


	void modifyPlayerStreak() {
		if (!this->m_regularTrail) return;
		if (fancy::settings.customStreak) {
			this->m_regularTrail->tintWithColor({255, 255, 255});
			return;
		}
		bool p2 = m_isSecondPlayer && fancy::settings.p2Enable;
		ccColor3B streakColor = p2 ? fancy::settings.p2StreakColor : fancy::settings.p1StreakColor;
		bool rainbowStreak = p2 ? fancy::settings.p2RainbowStreak : fancy::settings.p1RainbowStreak;
		if (rainbowStreak) {
			cocos2d::ccColor4F color = FancyPlayer::HSVtoRGB(m_fields->hue, 1.f, 1.f, 1.f);
			this->m_regularTrail->tintWithColor(FancyPlayer::color4Fto3B(color));
			return;
		}
		if (p2 && fancy::settings.p2ChangeStreak) {
			if (m_regularTrail->getColor() == streakColor) return;
			this->m_regularTrail->tintWithColor(fancy::settings.p2StreakColor);
			return;
		}
		if (m_regularTrail->getColor() == streakColor) return;
		this->m_regularTrail->tintWithColor(fancy::settings.p1StreakColor);
	}


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
	}


	void modifyRadius(CCParticleSystemQuad* p) {
		if (!fancy::settings.changeRadius) return;
		if (!p) return;
		if (!m_fields->baseRadius.contains(p)) {
			m_fields->baseRadius[p] = p->getStartRadius();
		} // radius scale
		float base = m_fields->baseRadius[p];
		p->setStartRadius(base * m_vehicleSize);
	}
}; // modify PlayerObject


$on_game(Loaded) {
	Mod::get()->setSavedValue<int>("menu-page", 1);
}