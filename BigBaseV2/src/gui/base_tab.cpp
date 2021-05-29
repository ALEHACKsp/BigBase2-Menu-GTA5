#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include <gta/array.hpp>
#include <imgui.h>
#include "features.hpp"

namespace big
{

	void render_player_tab()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			ImGui::Text("Bools");

			if (ImGui::Checkbox("God Mode", &features::self::god_mode_bool))
			{
				features::self::god_mode(PLAYER::PLAYER_ID());
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Noclip", &features::self::no_clip_bool))
			{
				features::self::no_clip();
			}

			if (ImGui::Checkbox("Super Jump", &features::self::super_jump_bool))
			{
				features::self::super_jump();
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Never Wanted", &features::self::never_wanted_bool))
			{
				features::self::never_wanted(PLAYER::PLAYER_ID());
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Buff Health Regen", &features::self::buff_hp_regen_bool))
			{
				features::self::buff_hp_regen(PLAYER::PLAYER_ID());
			}

			ImGui::NewLine();

			ImGui::Text("Floats");

			static int alpha;
			if (ImGui::SliderInt("Player alpha", &alpha, 0, 255))
			{
				g_fiber_pool->queue_job([]
					{
						features::self::player_alpha(alpha);
					});
			}

			ImGui::NewLine();

			ImGui::Text("Useful stuff");

			if (ImGui::Button("Teleport to waypoint [F12]"))
			{
				features::self::tp_to_waypoint();
			}

			ImGui::SameLine();

			if (ImGui::Button("Teleport to objective"))
			{
				features::self::tp_to_objective();
			}

			ImGui::Separator();

			if (ImGui::Button("Needs"))
			{
				features::self::give_needs(PLAYER::PLAYER_PED_ID());
			}

			ImGui::SameLine();

			if (ImGui::Button("Suicide"))
			{
				features::self::suicide(PLAYER::PLAYER_PED_ID());
			}

			if (ImGui::Button("Skip Cutscene"))
			{
				features::self::skip_cutscene();
			}
			ImGui::EndTabItem();
		}
	}

	void render_recovery_tab()
	{
		if (ImGui::BeginTabItem("Recovery"))
		{
			if (*g_pointers->m_is_session_started)
			{
				ImGui::Text("Packed Bools");

				static char* boolslist[]
				{
					"_NGPSTAT_BOOL",
					"_NGTATPSTAT_BOOL",
					"_NGDLCPSTAT_BOOL",
					"_DLCBIKEPSTAT_BOOL",
					"_DLCGUNPSTAT_BOOL",
					"_GUNTATPSTAT_BOOL",
					"_DLCSMUGCHARPSTAT_BOOL",
					"_GANGOPSPSTAT_BOOL",
					"_BUSINESSBATPSTAT_BOOL",
					"_ARENAWARSPSTAT_BOOL",
					"_CASINOPSTAT_BOOL",
					"_CASINOHSTPSTAT_BOOL",
					"_HEIST3TATTOOSTAT_BOOL",
					"_SU20PSTAT_BOOL",
					"_SU20TATTOOSTAT_BOOL",
					"_HISLANDPSTAT_BOOL",
				};
				static int combo_pos = 0;

				ImGui::Combo("Packed Bools", &combo_pos, boolslist, sizeof(boolslist) / sizeof(*boolslist));

				ImGui::SameLine();

				if (ImGui::Button("Unlock"))
				{
					g_fiber_pool->queue_job([] {
						switch (combo_pos) {
						case 0:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(4207, 4335, boolslist[combo_pos]);
							});
							
							break;
						case 1:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(4335, 4399, boolslist[combo_pos]);
							});
							
							break;
						case 2:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(7385, 7641, boolslist[combo_pos]);
								features::recovery::packed_bool(7321, 7385, boolslist[combo_pos]);
							});
							break;
						case 3:
							features::recovery::packed_bool(9361, 9553, boolslist[combo_pos]);
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(9361, 9553, boolslist[combo_pos]);
							});
							break;
						case 4:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(15369, 15561, boolslist[combo_pos]);
								features::recovery::packed_bool(15381, 15499, boolslist[combo_pos]);
							});
							break;
						case 5:
							
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(15562, 15946, boolslist[combo_pos]);
							});
							break;
						case 6:		
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(15946, 16010, boolslist[combo_pos]);
							});
							break;
						case 7:							
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(18098, 18162, boolslist[combo_pos]);
							});
							break;
						case 8:					
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(22066, 22194, boolslist[combo_pos]);
							});
							break;
						case 9:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(24962, 25538, boolslist[combo_pos]);
							});
							break;
						case 10:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(26810, 27258, boolslist[combo_pos]);
							});
							break;
						case 11:			
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(28098, 28354, boolslist[combo_pos]);
							});
							break;
						case 12:						
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(28355, 28483, boolslist[combo_pos]);
							});
							break;
						case 13:					
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(30260, 30295, boolslist[combo_pos]);
							});
							break;
						case 14:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(30355, 30483, boolslist[combo_pos]);
							});
							break;
						case 15:
							g_fiber_pool->queue_job([]
							{
								features::recovery::packed_bool(30515, 30707, boolslist[combo_pos]);
							});
							break;
						default:
							break;
						}
						});
				}

				if (ImGui::Button("Max Character Stats"))
				{
					g_fiber_pool->queue_job([]
					{
						features::recovery::unlock_character_stats();
					});
				}

				ImGui::SameLine();

				if (ImGui::Button("Unlock Fast Run"))
				{
					g_fiber_pool->queue_job([]
					{
						features::recovery::unlock_fast_run();
					});
				}

				ImGui::NewLine();

				if (ImGui::Button("Unlock Wireframe Suits"))
				{
					g_fiber_pool->queue_job([]
					{
						features::recovery::unlock_wireframe_suits();
					});
				}

				ImGui::SameLine();

				if (ImGui::Button("Unlock Atomizer Paint Job"))
				{				
					g_fiber_pool->queue_job([]
					{
						features::recovery::unlock_raygun_paint();
					});
				}
				
				ImGui::SameLine();

				if (ImGui::Button("Unlock Weapon Tints"))
				{
					g_fiber_pool->queue_job([]
					{
						features::recovery::unlock_weapon_colors();
					});
				}

				ImGui::Separator();

				if (ImGui::TreeNodeEx("Cayo Perico", ImGuiWindowFlags_NoCollapse))
				{
					ImGui::Text("Setup Cayo Perico For");

					ImGui::SameLine();

					if (ImGui::Button("Solo"))
					{
						g_fiber_pool->queue_job([]
							{
								features::recovery::setup_cayo(1);
							});
					}

					ImGui::SameLine();

					if (ImGui::Button("Duo And More"))
					{
						g_fiber_pool->queue_job([]
							{
								features::recovery::setup_cayo(2);
							});
					}
				}
		
				static char kills[10];
				ImGui::InputText("Kills", kills, 10);

				static char deaths[8];
				ImGui::InputText("Deaths", deaths, 10);


				int k = (int)kills;
				int d = (int)deaths;

				if (ImGui::Button("Change KD"))
				{
					g_fiber_pool->queue_job([&]
					{
						features::recovery::change_kd(1, k, d);
						features::recovery::change_kd(2, k, d);
					});
				}

				ImGui::Separator();

				ImGui::Checkbox("AFK Casino", &features::recovery::start_casino_bool);
			}
			else
			{
				ImGui::Text("You're not online");
			}

			ImGui::EndTabItem();
		}
	}

	void render_online_tab()
	{
		if (ImGui::BeginTabItem("Online"))
		{
			if (ImGui::Button("Reset reports"))
			{
				features::recovery::reset_reports();
			}

			ImGui::SameLine();

			if (ImGui::Button("Remove bad sport"))
			{
				features::recovery::remove_bad_sport();
			}

			static bool phone_disabled;
			if (ImGui::Checkbox("Mute phonecalls", &phone_disabled))
			{
				features::online::disable_phone(phone_disabled);
			}

			static bool blocked_afk;
			if (ImGui::Checkbox("Anti-AFK", &blocked_afk))
			{
				features::online::block_afk();
			}

			ImGui::NewLine();

			ImGui::Text("Freemode stuff [Online]");

			if (ImGui::Button("BST"))
			{
				features::online::bst();
			}

			ImGui::SameLine();

			if (ImGui::Button("Enable grinding"))
			{
				features::online::grinding_mode();
			}

			ImGui::SameLine();

			if (ImGui::Button("Bribe authorities"))
			{
				features::online::bribe();
			}

			if (ImGui::Button("Remove orbital cooldown"))
			{
				features::online::no_orb_cooldown();
			}

			ImGui::SameLine();

			if (ImGui::Button("Remove EWO cooldown"))
			{
				features::online::ewo_cooldown_remove();
			}

			ImGui::EndTabItem();
		}
	}

	void render_players_tab()
	{

		if (ImGui::BeginTabItem("Players"))
		{
			if (*g_pointers->m_is_session_started)
			{
				features::online::show_players();

				features::online::draw_extra_info();

				ImGui::NewLine();
			}
			else
			{
				ImGui::Text("You're not online");
			}

			ImGui::EndTabItem();
		}
	}

	void render_weapon_tab()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			ImGui::Text("Ammo");

			if (ImGui::Checkbox("Unlimited ammo", &features::weapons::unlimited_ammo_bool))
			{
				features::weapons::unlimited_ammo(PLAYER::PLAYER_PED_ID());
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Unlimited clip", &features::weapons::unlimited_clip_bool))
			{
				features::weapons::unlimited_clip(PLAYER::PLAYER_PED_ID());
			}

			ImGui::SameLine();

			if (ImGui::Button("Refill current weapon ammo"))
			{
				features::weapons::refill_ammo(PLAYER::PLAYER_PED_ID());
			}

			ImGui::NewLine();

			ImGui::Text("Weapons");

			if (ImGui::Button("Give all weapons"))
			{
				g_fiber_pool->queue_job([]
					{
						features::weapons::give_all_weps(PLAYER::PLAYER_PED_ID());
					});
			}

			ImGui::SameLine();

			if (ImGui::Button("Give all mk2 weapons"))
			{
				g_fiber_pool->queue_job([]
					{
						features::weapons::give_all_mk2(PLAYER::PLAYER_PED_ID());
					});
			}

			ImGui::SameLine();

			if (ImGui::Button("Give stungun"))
			{
				g_fiber_pool->queue_job([]
					{
						features::weapons::give_stun_gun(PLAYER::PLAYER_PED_ID());
					});

			}

			ImGui::SameLine();

			if (ImGui::Button("Give scanner"))
			{
				g_fiber_pool->queue_job([]
					{
						features::weapons::give_scanner(PLAYER::PLAYER_PED_ID());
					});
			}
			ImGui::EndTabItem();
		}
	}

	void render_vehicles_tab()
	{
		if (ImGui::BeginTabItem("Vehicles"))
		{
			ImGui::Text("Vehicle Spawner");

			static char* vehicleslist[]
			{
				"OPPRESSOR2",
				"NIGHTSHARK",
				"OPPRESSOR",
				"LAZER",
				"HYDRA",
				"MOLOTOK",
				"HAKUCHOU2",
				"KHANJALI",
				"CARGOBOB",
				"KURUMA2"
			};
			static int combo_pos = 0;

			ImGui::Combo("Choice", &combo_pos, vehicleslist, sizeof(vehicleslist) / sizeof(*vehicleslist));
			if (ImGui::Button("Spawn"))
			{
				g_fiber_pool->queue_job([]
					{
						features::vehicles::spawn_vehicle(PLAYER::PLAYER_PED_ID(), vehicleslist[combo_pos]);
					});
			}

			static char platename[8];
			ImGui::InputText("2FAST", platename, 8);

			ImGui::SameLine();

			if (ImGui::Button("Set License Plate"))
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				features::vehicles::set_plate(vehicle, platename);
			}

			if (ImGui::Button("Max Vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
						features::vehicles::max_vehicle();
					});
			}

			ImGui::EndTabItem();
		}

	}
	void render_misc_tab()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			ImGui::Text("Features");

			if (ImGui::Button("Unload"))
			{
				g_running = false;
			}

			ImGui::EndTabItem();
		}

	}
}