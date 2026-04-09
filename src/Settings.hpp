#pragma once

namespace fancy
{
	struct Settings
	{
		// p1 settings
		bool p1ChangeParticles = Mod::get()->getSavedValue<bool>("p1-change-particles", true);
		bool p1RainbowParticles = Mod::get()->getSavedValue<bool>("p1-rainbow-particles", false);;
		ccColor4B p1StartColor = Mod::get()->getSavedValue<ccColor4B>("p1-start-color", {61, 69, 255, 255});
		ccColor4F p1StartColorF = {
				p1StartColor.r / 255.f,
				p1StartColor.g / 255.f,
				p1StartColor.b / 255.f,
				p1StartColor.a / 255.f
			};
		ccColor4B p1FinishColor = Mod::get()->getSavedValue<ccColor4B>("p1-finish-color", {115, 122, 255, 255});
		ccColor4F p1FinishColorF = {
				p1FinishColor.r / 255.f,
				p1FinishColor.g / 255.f,
				p1FinishColor.b / 255.f,
				p1FinishColor.a / 255.f
			};
		bool p1ChangeDashFire = Mod::get()->getSavedValue<bool>("p1-change-dash-fire", true);
		bool p1RainbowDashFire = Mod::get()->getSavedValue<bool>("p1-rainbow-dash-fire", false);
		ccColor3B p1DashFireColor = Mod::get()->getSavedValue<ccColor3B>("p1-dash-fire-color", {0, 0, 255});
		bool p1ChangeSpiderDash = Mod::get()->getSavedValue<bool>("p1-change-spider-dash", true);
		bool p1RainbowSpiderDash = Mod::get()->getSavedValue<bool>("p1-rainbow-spider-dash", false);
		ccColor3B p1SpiderDashColor = Mod::get()->getSavedValue<ccColor3B>("p1-spider-dash-color", {0, 0, 255});
		bool p1ChangeStreak = Mod::get()->getSavedValue<bool>("p1-change-streak", false);
		bool p1RainbowStreak = Mod::get()->getSavedValue<bool>("p1-rainbow-streak", false);
		ccColor3B p1StreakColor = Mod::get()->getSavedValue<ccColor3B>("p1-streak-color", {0, 0, 255});
		// p2 settings
		bool p2Enable = Mod::get()->getSavedValue<bool>("p2-enable", false);
		bool p2ChangeParticles = Mod::get()->getSavedValue<bool>("p2-change-particles", true);
		bool p2RainbowParticles = Mod::get()->getSavedValue<bool>("p2-rainbow-particles", false);
		ccColor4B p2StartColor = Mod::get()->getSavedValue<ccColor4B>("p2-start-color", {255, 255, 0, 255});
		ccColor4F p2StartColorF = {
				p2StartColor.r / 255.f,
				p2StartColor.g / 255.f,
				p2StartColor.b / 255.f,
				p2StartColor.a / 255.f
			};
		ccColor4B p2FinishColor = Mod::get()->getSavedValue<ccColor4B>("p2-finish-color", {255, 255, 40, 255});
		ccColor4F p2FinishColorF = {
				p2FinishColor.r / 255.f,
				p2FinishColor.g / 255.f,
				p2FinishColor.b / 255.f,
				p2FinishColor.a / 255.f
			};
		bool p2ChangeDashFire = Mod::get()->getSavedValue<bool>("p2-change-dash-fire", true);
		bool p2RainbowDashFire = Mod::get()->getSavedValue<bool>("p2-rainbow-dash-fire", false);
		ccColor3B p2DashFireColor = Mod::get()->getSavedValue<ccColor3B>("p2-dash-fire-color", {255, 255, 0});
		bool p2ChangeSpiderDash = Mod::get()->getSavedValue<bool>("p2-change-spider-dash", true);
		bool p2RainbowSpiderDash = Mod::get()->getSavedValue<bool>("p2-rainbow-spider-dash", false);
		ccColor3B p2SpiderDashColor = Mod::get()->getSavedValue<ccColor3B>("p2-spider-dash-color", {255, 255, 0});
		bool p2ChangeStreak = Mod::get()->getSavedValue<bool>("p2-change-streak", false);
		bool p2RainbowStreak = Mod::get()->getSavedValue<bool>("p2-rainbow-streak", false);
		ccColor3B p2StreakColor = Mod::get()->getSavedValue<ccColor3B>("p2-streak-color", {255, 255, 0});
		// global settings
		float rgbSpeed = Mod::get()->getSavedValue<float>("rgb-speed", 0.4f);
		bool changeRadius = Mod::get()->getSavedValue<bool>("change-radius", false);
		bool alignParticles = Mod::get()->getSavedValue<bool>("align-particles", false);
		bool customStreak = Mod::get()->getSavedValue<bool>("custom-streak", false);
		bool streakAlignWave = Mod::get()->getSavedValue<bool>("streak-align-wave", false);
		// streak settings
		bool streakConfigure = Mod::get()->getSavedValue<bool>("streak-configure", false);
		bool streakFadeEnable = Mod::get()->getSavedValue<bool>("streak-fade-enable", false);
		float streakFade = Mod::get()->getSavedValue<float>("streak-fade", 0.5f);
		bool streakStrokeEnable = Mod::get()->getSavedValue<bool>("streak-stroke-enable", false);
		float streakStroke = Mod::get()->getSavedValue<float>("streak-stroke", 10.f);
		bool streakRepeatEnable = Mod::get()->getSavedValue<bool>("streak-repeat-enable", false);
		float streakRepeat = Mod::get()->getSavedValue<float>("streak-repeat", 0.f);
		bool streakAlign = Mod::get()->getSavedValue<bool>("streak-align", false);
		bool streakBlend = Mod::get()->getSavedValue<bool>("streak-blend", false);
		bool streakAlwaysShow = Mod::get()->getSavedValue<bool>("streak-always-show", false);
	};
	extern Settings settings;
} // mod settings
