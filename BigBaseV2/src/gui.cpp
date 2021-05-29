#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"

#include <imgui.h>

#include "gui/base_tab.h"

namespace big
{
	void gui::dx_init()
	{
		auto &style = ImGui::GetStyle();
		style.WindowRounding = 5.3f;
		style.FrameRounding = 4.3f;
		style.ScrollbarRounding = 4.5f;

		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 8.f, 4.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 1.f;
		style.ChildBorderSize = 0.f;
		style.PopupBorderSize = 1.f;
		style.FrameBorderSize = 0.f;
		style.TabBorderSize = 0.f;
		style.WindowRounding = 0.f;
		style.ChildRounding = 5.3f;
		style.FrameRounding = 5.3f;
		style.ScrollbarRounding = 0.f;
		style.GrabRounding = 5.3f;
		style.ChildRounding = 5.3f;
		style.TabRounding = 5.3f;
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };

		auto &colors = style.Colors;
		colors[ImGuiCol_Text] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.00, 0.40, 0.41, 1.00);
		colors[ImGuiCol_WindowBg] = ImVec4(0.00, 0.00, 0.00, 1.00);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00, 0.00, 0.00, 0.00);
		colors[ImGuiCol_Border] = ImVec4(0.00, 1.00, 1.00, 0.65);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00, 0.00, 0.00, 0.00);
		colors[ImGuiCol_FrameBg] = ImVec4(0.44, 0.80, 0.80, 0.18);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44, 0.80, 0.80, 0.27);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.44, 0.81, 0.86, 0.66);
		colors[ImGuiCol_TitleBg] = ImVec4(0.14, 0.18, 0.21, 0.73);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00, 0.00, 0.00, 0.54);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.00, 1.00, 1.00, 0.27);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.00, 0.00, 0.00, 0.20);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22, 0.29, 0.30, 0.71);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00, 1.00, 1.00, 0.44);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00, 1.00, 1.00, 0.74);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_CheckMark] = ImVec4(0.00, 1.00, 1.00, 0.68);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.00, 1.00, 1.00, 0.36);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00, 1.00, 1.00, 0.76);
		colors[ImGuiCol_Button] = ImVec4(0.00, 0.65, 0.65, 0.46);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.01, 1.00, 1.00, 0.43);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.00, 1.00, 1.00, 0.62);
		colors[ImGuiCol_Header] = ImVec4(0.00, 1.00, 1.00, 0.33);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00, 1.00, 1.00, 0.42);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.00, 1.00, 1.00, 0.54);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00, 1.00, 1.00, 0.54);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00, 1.00, 1.00, 0.74);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_PlotLines] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00, 1.00, 1.00, 1.00);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00, 1.00, 1.00, 0.22);
	}

	void gui::dx_on_tick()
	{
		TRY_CLAUSE
		{
			if (ImGui::Begin("BigBaseV2"))
			{
				ImGui::BeginTabBar("tabbar");
				render_player_tab();
				render_online_tab();
				render_recovery_tab();
				render_players_tab();
				render_weapon_tab();
				render_vehicles_tab();
				render_misc_tab();
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
		EXCEPT_CLAUSE
	}

	void gui::script_init()
	{
	}

	void gui::script_on_tick()
	{
		TRY_CLAUSE
		{
			if (g_gui.m_opened)
			{
				CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
			}
		}
		EXCEPT_CLAUSE
	}

	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}
}
