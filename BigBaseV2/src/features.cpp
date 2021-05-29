#include "common.hpp"
#include "features.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "gui/base_tab.h"
#include "playerlist.hpp"
#include "pointers.hpp"
#include "gta/player.hpp"
#include "fiber_pool.hpp"
#include "imgui.h"
#include "misc.h"
#include "gta/Weapons.h"
#include "script_local.hpp"
#include "hooking.hpp"

namespace big::features
{

	namespace online {
		void features::online::draw_extra_info()
		{
			if (CNetGamePlayer* net_player = g_pointers->m_GetNetPlayer(online::selectedPlayer))
			{
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize;

				if (ImGui::BeginChild("Player Menu", ImVec2(700, 500), true, window_flags))
				{
					if (ImGui::TreeNodeEx("Player Info", ImGuiWindowFlags_NoCollapse))
					{
						const char* name = g_player[features::online::selectedPlayer].m_name.c_str();
						const char* rid = g_player[features::online::selectedPlayer].m_str_rockstar_id.c_str();

						ImGui::Text("Username: %s | RID: %s", name, rid);
					}

					ImGui::Separator();

					if (ImGui::Button("Give all weapons"))
					{
						g_fiber_pool->queue_job([]
							{
								features::weapons::give_all_weps(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online::selectedPlayer));
							});
					}

					ImGui::SameLine();

					if (ImGui::Button("Give all MK2 weapons"))
					{
						g_fiber_pool->queue_job([]
							{
								features::weapons::give_all_mk2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online::selectedPlayer));
							});
					}

					if (ImGui::Button("Give Stun Gun"))
					{
						g_fiber_pool->queue_job([]
							{
								features::weapons::give_stun_gun(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online::selectedPlayer));
							});
					}

					ImGui::SameLine();

					if (ImGui::Button("Give Scanner"))
					{
						g_fiber_pool->queue_job([]
							{
								features::weapons::give_scanner(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online::selectedPlayer));
							});
					}

					ImGui::Separator();

					if (ImGui::Button("Teleport"))
					{
						features::online::teleport_to_player(online::selectedPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("Cage"))
					{
						features::online::cage(online::selectedPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("Crash"))
					{
						//features::crashplayer(online::selectedPlayer);
					}

					if (ImGui::Button("Give needs"))
					{
						features::self::give_needs(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online::selectedPlayer));
					}

					static char* objects[] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };

					static int combo_pos = 0;

					ImGui::Separator();

					ImGui::Combo("Combo", &combo_pos, objects, sizeof(objects) / sizeof(*objects));

					ImGui::SameLine();

					if (ImGui::Button("Attach"))
					{
						g_fiber_pool->queue_job([]
							{
								features::objects::attach_obj_to_player(objects[combo_pos], online::selectedPlayer);
							});
					}

					if (ImGui::Button("Attach All"))
					{
						g_fiber_pool->queue_job([]
							{
								features::objects::attach_obj_to_player(objects[combo_pos], online::selectedPlayer);
							});
					}

					ImGui::SameLine();

					if (ImGui::Button("Detach all objects"))
					{
						g_fiber_pool->queue_job([]
							{
								features::objects::detach_all(online::selectedPlayer);
							});
					}
				}
				ImGui::EndChild();
			}
		}

		void features::online::show_players()
		{

			auto wSize = ImGui::GetWindowSize();

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;
			float x = (wSize.x / 2) - 300;
			float y = wSize.y - 100;
			if (ImGui::BeginChild("Player List", ImVec2(x, y), true, window_flags))
			{
				for (Player i = 0; i < gta::num_players; i++)
				{
					if (CNetGamePlayer* net_player = g_pointers->m_GetNetPlayer(i))
					{
						if (ImGui::Selectable(g_player[i].m_name.c_str(), false))
						{
							online::selectedPlayer = i;
						}
					}
				}
			}
			ImGui::EndChild();

			ImGui::SameLine();
		}

		int features::online::selectedPlayer = 0;

		void features::online::teleport_to_player(Player player) {
			Entity handle;
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
			PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
			ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
		}
		void features::online::cage(Player player)
		{
			Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0);
			Object obj = OBJECT::CREATE_OBJECT(features::basic::$("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
		}
		bool features::online::block_afk_bool = false;
		void features::online::block_afk()
		{
			if (block_afk_bool)
			{
				misc::set_global(2550148 + 296, -1000000);
				misc::set_global(1377236 + 1149, -1000000);
			}
			else
			{
				misc::set_global(2550148 + 296, 0);
				misc::set_global(1377236 + 1149, 0);
			}
		}
		void features::online::disable_phone(bool phone_disabled)
		{
			if (phone_disabled)
			{
				misc::set_global(19664 + 1, 1);
			}
			else
			{
				misc::set_global(19664 + 1, 0);
			}
		}
		void features::online::bst()
		{
			misc::set_global(2440049 + 4006, 3);
		}
		void features::online::bribe()
		{
			misc::set_global(2540384 + 4024, 5);
			misc::set_global(2540384 + 4620, 1);
			misc::set_global(2537071 + 4622, static_cast<int64_t>(NETWORK::GET_NETWORK_TIME()) + 720000);
		}
		void features::online::no_orb_cooldown()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ORBITAL_CANNON_COOLDOWN"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ORBITAL_CANNON_COOLDOWN"), 0, 0);
		}
		void features::online::ewo_cooldown_remove()
		{
			misc::set_global(2540384 + 6672, 0);
		}

		void features::online::grinding_mode()
		{
			misc::set_global(2451787 + 742, 1);
		}

		void features::online::block_vote()
		{
			//Global_1388057 = func_16450(joaat("MPPLY_BECAME_CHEATER_NUM"));
			//Global_1388059 = func_16450(joaat("MPPLY_OFFENSIVE_LANGUAGE"));
			//Global_1388060 = func_16450(joaat("MPPLY_GRIEFING"));
			//Global_1388062 = func_16450(joaat("MPPLY_OFFENSIVE_TAGPLATE"));
			//Global_1388063 = func_16450(joaat("MPPLY_OFFENSIVE_UGC"));

			misc::set_global(1388057, 0);
			misc::set_global(1388059, 0);
			misc::set_global(1388060, 0);
			misc::set_global(1388062, 0);
			misc::set_global(1388063, 0);
		}
	}

	namespace basic {
		float features::basic::deg_to_rad(float degs)
		{
			return degs * 3.141592653589793f / 180.f;
		}
		Hash features::basic::load(char* name)
		{
			Hash hash = GAMEPLAY::GET_HASH_KEY(name);

			STREAMING::REQUEST_MODEL(hash);
			while (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				script::get_current()->yield();
			}
			return hash;
		}
		Hash features::basic::$(std::string str) {
			return GAMEPLAY::GET_HASH_KEY(&str[0u]);
		}
	}

	namespace recovery {

		//AFK Slots        
		bool features::recovery::start_casino_bool = false;
		void features::recovery::start_casino() // only loop it
		{
			if (start_casino_bool)
			{
				auto CASINO_SLOTS = find_script_thread(RAGE_JOAAT("casino_slots"));
				auto transaction = script_local::script_local(CASINO_SLOTS, 1644).as<int*>();
				auto checker = *script_local::script_local(CASINO_SLOTS, 3407).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
				if (checker == 0)
				{
					GAMEPLAY::SET_BIT(transaction, 3);
				}
			}		
		}

		//Fast Spinning
		//void features::recovery::sameValue() // only loop it
		//{
		//	auto CASINO_SLOTS = find_script_thread(RAGE_JOAAT("casino_slots"));
		//	auto checker = *script_local::script_local(CASINO_SLOTS, 3401).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
		//	if (checker == 3)
		//	{
		//		GAMEPLAY::SET_BIT(checker, 2);
		//	}
		//}
		
		void features::recovery::packed_bool(int loop, int looptwo, char* boolname)
		{
			if ((boolname != NULL) && (boolname[0] == '\0')) {
				for (int i = loop; i <= looptwo; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - loop), 0, 1, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), boolname), TRUE, ((i - loop) - STATS::_0xF4D8E7AC2A27758C((i - loop)) * 64), 1);
				}
			}
		}

		void features::recovery::reset_reports()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, 1);
		}

		void features::recovery::remove_bad_sport()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 0, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, 1);
		}

		void features::recovery::unlock_fast_run()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ABILITY_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ABILITY_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_ABILITY_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1, 1);
		}

		void features::recovery::unlock_wireframe_suits()
		{
			misc::set_global(262145 + 22912, 1);
			misc::set_global(262145 + 22913, 1);
			misc::set_global(262145 + 22914, 1);
			misc::set_global(262145 + 22915, 1);
			misc::set_global(262145 + 22916, 1);
		}

		void features::recovery::unlock_raygun_paint()
		{
			misc::set_global(101851, 90);
		}

		void features::recovery::unlock_character_stats()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);

			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
		}

		void features::recovery::unlock_weapon_colors()
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);

			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PISTOL50_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTMG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BULLPUP_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_STKYBMB_ENEMY_KILLS"), 600, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
		}

		void features::recovery::change_kd(const int choice, const int kills, const int deaths)
		{
			switch (choice) {
			    case 1:
				    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), kills, 1);
				    break;
			    case 2:
				    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), deaths, 1);
				    break;
			    default:
				    break;
			}
		}

		void cayo_stat(char* stat, const int id, const int save)
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(stat), id, save);
		}

		void features::recovery::setup_cayo(const int choice)
		{
			static int characterid = 0;

			switch (choice) {
			case 1: { // Solo
				static int solo_cayo_array_ids[31] = { 131071, 63, 63, 5, 3, 3, 3, 5, 2, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 126823, 0, 0, 0, 0, 0, 0, -1, -1, -1, 65535, 10 };
				static char* solo_cayo_array_stats[31] = { "MPx_H4CNF_BS_GEN", "MPx_H4CNF_BS_ENTR", "MPx_H4CNF_BS_ABIL", "MPx_H4CNF_WEAPONS", "MPx_H4CNF_WEP_DISRP", "MPx_H4CNF_ARM_DISRP", "MPx_H4CNF_HEL_DISRP",
					"MPx_H4CNF_TARGET", "MPx_H4CNF_TROJAN", "MPx_H4CNF_APPROACH", "MPx_H4LOOT_CASH_I", "MPx_H4LOOT_CASH_C", "MPx_H4LOOT_WEED_I", "MPx_H4LOOT_WEED_C", "MPx_H4LOOT_COKE_I", "MPx_H4LOOT_COKE_C", "MPx_H4LOOT_GOLD_I",
					"MPx_H4LOOT_GOLD_C", "MPx_H4LOOT_PAINT", "MPx_H4_PROGRESS", "MPx_H4LOOT_CASH_I_SCOPED", "MPx_H4LOOT_CASH_C_SCOPED", "MPx_H4LOOT_WEED_I_SCOPED", "MPx_H4LOOT_WEED_C_SCOPED", "MPx_H4LOOT_COKE_I_SCOPED", "MPx_H4LOOT_COKE_C_SCOPED",
					"MPx_H4LOOT_GOLD_I_SCOPED" , "MPx_H4LOOT_GOLD_C_SCOPED" , "MPx_H4LOOT_PAINT_SCOPED" , "MPx_H4_MISSIONS" , "MPx_H4_PLAYTHROUGH_STATUS" };

				for (int i = 0; i <= 31; i++)
				{
					std::string currentstr = solo_cayo_array_stats[i];
					currentstr.erase(0, 3);

					currentstr = "MP" + characterid + currentstr;

					cayo_stat((char*)currentstr.c_str(), solo_cayo_array_ids[i], 1);
				}

				characterid = 1;

				for (int i = 0; i <= 31; i++)
				{
					std::string currentstr = solo_cayo_array_stats[i];
					currentstr.erase(0, 3);

					currentstr = "MP" + characterid + currentstr;

					cayo_stat((char*)currentstr.c_str(), solo_cayo_array_ids[i], 1);
				}
			}
			case 2: { // Duo+
				static int duoplus_cayo_array_ids[36] = { 131071, 63, 63, 2, 3, 3, 3, 5, 4424, 5256, 5156, 1, -1, 1185000, 1185000, 0, 0, 0, 0, -1, -1, 0, 0, -1, 126823, 0, 0, 0, 0, -1, -1, 0, 0, -1, 65535, 40000 };
				static char* duoplus_cayo_array_stats[36] = { "MPx_H4CNF_BS_GEN", "MPx_H4CNF_BS_ENTR", "MPx_H4CNF_BS_ABIL", "MPx_H4CNF_WEAPONS", "MPx_H4CNF_WEP_DISRP", "MPx_H4CNF_ARM_DISRP", "MPx_H4CNF_HEL_DISRP",
					"MPx_H4CNF_TARGET", "MP0_H4CNF_BOLTCUT", "MP0_H4CNF_UNIFORM", "MP0_H4CNF_GRAPPEL", "MP0_H4CNF_TROJAN", "MP0_H4CNF_APPROACH", "MP0_H4LOOT_COKE_V", "MP0_H4LOOT_PAINT_V", "MP0_H4LOOT_CASH_I", "MP0_H4LOOT_CASH_C",
					"MP0_H4LOOT_WEED_I", "MP0_H4LOOT_WEED_C", "MP0_H4LOOT_COKE_I", "MP0_H4LOOT_COKE_C", "MP0_H4LOOT_GOLD_I", "MP0_H4LOOT_GOLD_C", "MP0_H4LOOT_PAINT", "MP0_H4_PROGRESS", "MP0_H4LOOT_CASH_I_SCOPED",
					"MP0_H4LOOT_CASH_C_SCOPED" , "MP0_H4LOOT_WEED_I_SCOPED" , "MP0_H4LOOT_WEED_C_SCOPED" , "MP0_H4LOOT_COKE_I_SCOPED" , "MP0_H4LOOT_COKE_C_SCOPED", "MP0_H4LOOT_GOLD_I_SCOPED", "MP0_H4LOOT_GOLD_C_SCOPED",
					"MP0_H4LOOT_PAINT_SCOPED", "MP1_H4_MISSIONS", "MP1_H4_PLAYTHROUGH_STATUS" };

				for (int i = 0; i <= 36; i++)
				{
					std::string currentstr = duoplus_cayo_array_stats[i];
					currentstr.erase(0, 3);

					currentstr = "MP" + characterid + currentstr;

					cayo_stat((char*)currentstr.c_str(), duoplus_cayo_array_ids[i], 1);
				}

				characterid = 1;

				for (int i = 0; i <= 36; i++)
				{
					std::string currentstr = duoplus_cayo_array_stats[i];
					currentstr.erase(0, 3);

					currentstr = "MP" + characterid + currentstr;

					cayo_stat((char*)currentstr.c_str(), duoplus_cayo_array_ids[i], 1);
				}
			}
			}
			    
		}
	}

	namespace weapons {
		bool features::weapons::unlimited_ammo_bool = false;
		bool features::weapons::unlimited_clip_bool = false;

		void features::weapons::unlimited_ammo(Ped ped)
		{

			if (features::weapons::unlimited_ammo_bool)
			{
				WEAPON::SET_PED_INFINITE_AMMO(ped, true, 0);
			}
			else
			{
				WEAPON::SET_PED_INFINITE_AMMO(ped, false, 0);
			}

		}

		void features::weapons::unlimited_clip(Ped ped)
		{

			if (features::weapons::unlimited_clip_bool)
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, true);
			}
			else
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, false);
			}

		}

		void features::weapons::give_all_weps(Ped ped)
		{
			int Weapons[] = { WEAPON_ADVANCEDRIFLE, WEAPON_APPISTOL, WEAPON_ASSAULTRIFLE, WEAPON_ASSAULTRIFLE_MK2, WEAPON_ASSAULTSHOTGUN, WEAPON_ASSAULTSMG, WEAPON_BALL, WEAPON_BAT, WEAPON_BATTLEAXE, WEAPON_BOTTLE, WEAPON_BULLPUPRIFLE, WEAPON_BULLPUPRIFLE_MK2, WEAPON_BULLPUPSHOTGUN, WEAPON_BZGAS, WEAPON_CARBINERIFLE, WEAPON_CARBINERIFLE_MK2, WEAPON_COMBATMG, WEAPON_COMBATMG_MK2, WEAPON_COMBATPDW, WEAPON_COMBATPISTOL, WEAPON_COMPACTLAUNCHER, WEAPON_COMPACTRIFLE, WEAPON_CROWBAR, WEAPON_DAGGER, WEAPON_DOUBLEACTION, WEAPON_FIREEXTINGUISHER, WEAPON_FIREWORK, WEAPON_FLARE, WEAPON_FLAREGUN, WEAPON_FLASHLIGHT, WEAPON_GOLFCLUB, WEAPON_GRENADE, WEAPON_GRENADELAUNCHER, WEAPON_GRENADELAUNCHER_SMOKE, WEAPON_GUSENBERG, WEAPON_HAMMER, WEAPON_HATCHET, WEAPON_HEAVYPISTOL, WEAPON_HEAVYSHOTGUN, WEAPON_HEAVYSNIPER, WEAPON_HEAVYSNIPER_MK2, WEAPON_HOMINGLAUNCHER, WEAPON_KNIFE, WEAPON_KNUCKLE, WEAPON_MACHETE, WEAPON_MACHINEPISTOL, WEAPON_MARKSMANPISTOL, WEAPON_MARKSMANRIFLE, WEAPON_MARKSMANRIFLE_MK2, WEAPON_MG, WEAPON_MICROSMG, WEAPON_MINIGUN, WEAPON_MINISMG, WEAPON_MOLOTOV, WEAPON_MUSKET, WEAPON_NIGHTSTICK, WEAPON_PETROLCAN, WEAPON_PIPEBOMB, WEAPON_PISTOL50, WEAPON_PISTOL, WEAPON_PISTOL_MK2, WEAPON_POOLCUE, WEAPON_PROXMINE, WEAPON_PUMPSHOTGUN, WEAPON_PUMPSHOTGUN_MK2, WEAPON_RAILGUN, WEAPON_RAYCARBINE, WEAPON_RAYPISTOL, WEAPON_RAYMINIGUN, WEAPON_REVOLVER, WEAPON_REVOLVER_MK2, WEAPON_RPG, WEAPON_SAWNOFFSHOTGUN, WEAPON_SMG, WEAPON_SMG_MK2, WEAPON_SMOKEGRENADE, WEAPON_SNIPERRIFLE, WEAPON_SNOWBALL, WEAPON_SNSPISTOL, WEAPON_SNSPISTOL_MK2, WEAPON_SPECIALCARBINE, WEAPON_SPECIALCARBINE_MK2, WEAPON_STICKYBOMB, WEAPON_STINGER, WEAPON_STONE_HATCHET, WEAPON_STUNGUN, WEAPON_SWITCHBLADE, WEAPON_UNARMED, WEAPON_VINTAGEPISTOL, WEAPON_WRENCH };
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				if (!WEAPON::HAS_PED_GOT_WEAPON(ped, Weapons[i], false))
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, Weapons[i], 9999, 1);
			}
		}

		void features::weapons::give_all_mk2(Ped ped) {
			int Weapons[] = { WEAPON_ASSAULTRIFLE_MK2, WEAPON_BULLPUPRIFLE_MK2, WEAPON_CARBINERIFLE_MK2, WEAPON_COMBATMG_MK2, WEAPON_HEAVYSNIPER_MK2, WEAPON_MARKSMANRIFLE_MK2, WEAPON_PISTOL_MK2, WEAPON_PUMPSHOTGUN_MK2, WEAPON_REVOLVER_MK2, WEAPON_SMG_MK2, WEAPON_SNSPISTOL_MK2, WEAPON_SPECIALCARBINE_MK2 };
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, Weapons[i], 9999, 1);
			}
		}

		void features::weapons::give_stun_gun(Ped ped) {
			int Weapons[] = { 0x3656C8C1, 911657153 };
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, Weapons[i], 9999, 1);
			}
		}

		void features::weapons::give_scanner(Ped ped) {
			int Weapons[] = { 0xFDBADCED, 4256881901 };
			for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, Weapons[i], 9999, 1);
			}
		}

		void features::weapons::refill_ammo(Ped ped)
		{
			Hash weaponhash;
			WEAPON::GET_CURRENT_PED_WEAPON(ped, &weaponhash, 1);
			WEAPON::SET_PED_AMMO(ped, weaponhash, 9999);
		}
	}

	namespace vehicles {
		void features::vehicles::max_vehicle()
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			for (int i = 0; i < 50; i++)
			{
				VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
			}
			features::vehicles::set_plate(vehicle, "BBV2");
		}

		void features::vehicles::spawn_vehicle(Ped ped, char* name)
		{
			static const int DISTANCE_SPAWN = 3;

			auto pos = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
			auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(ped);
			auto heading = ENTITY::GET_ENTITY_HEADING(ped);

			pos.x += DISTANCE_SPAWN * forward.x;
			pos.y += DISTANCE_SPAWN * forward.y;

			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, FALSE);

			Hash hash_vehicle = features::basic::load(name);

			auto vehicle = VEHICLE::CREATE_VEHICLE(hash_vehicle, pos.x, pos.y, pos.z, heading + 90.0f, TRUE, TRUE);

			char __b[256]; sprintf(__b, ",LOG,CREATE_VEHICLE");

			ENTITY::SET_ENTITY_INVINCIBLE(vehicle, TRUE);
			//ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicle, FALSE);
			//ENTITY::SET_ENTITY_PROOFS(vehicle, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
			//VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, FALSE);
			//VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, FALSE);
			//VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, FALSE);

			VEHICLE::SET_VEHICLE_CAN_BE_TARGETTED(vehicle, FALSE);
			//OBJECT::SET_OBJECT_TARGETTABLE(vehicle, FALSE);
			//VEHICLE::_SET_VEHICLE_CAN_BE_LOCKED_ON(vehicle, FALSE, FALSE);

			//VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, 1.39f * VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle));
			//VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, 1.39f);
			//VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle, 1.39f);

			if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle))
			{
				VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, 0.0f);
			}
			//VEHICLE::SET_VEHICLE_LOD_MULTIPLIER(vehicle, 1.39f);

		}

		void features::vehicles::set_plate(Vehicle veh, char* platename)
		{
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, platename);
		}
	}

	namespace objects {
		void features::objects::request_control_id(int network_id)
		{
			int tick = 0;

			while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(network_id) && tick <= 25)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(network_id);
				tick++;
			}
		}

		void features::objects::request_control_ent(Entity entity)
		{
			int tick = 0;
			while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);

				tick++;
			}
			if (g_pointers->m_is_session_started)
			{
				int network_id = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
				features::objects::request_control_id(network_id);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(network_id, 1);
			}
		}

		void features::objects::attach_obj_to_player(char* object, Player player)
		{
			Entity t = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vector3 pos = { 0.f, -.26f, .1f };
			Vector3 rot = { 0.f, 0.f, 0.f };
			Hash hash = GAMEPLAY::GET_HASH_KEY(object);
			const auto ped_position = ENTITY::GET_ENTITY_COORDS(t, true);
			Vector3 empty;
			auto objectToAttach = OBJECT::CREATE_OBJECT(hash, ped_position.x, ped_position.y, ped_position.z, true, false, false);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(objectToAttach, t, SKEL_Spine0, 0, 0, 0, 0, 0, 0, 1, 1, false, true, 2, 1);
			return;
		}

		void features::objects::detach_all(Player player)
		{
			static char* objects[] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };

			for (int i = 0; i < 5; i++) {
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1);
				GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
				GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
				GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
				for (int i = 0; i < 136; i++) {
					Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

					if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player))) {
						features::objects::request_control_ent(obj);
						int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
						NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
						features::objects::request_control_id(netID);
						ENTITY::DETACH_ENTITY(obj, 1, 1);
					}
				}
			}
		}
	}

	namespace self {
		bool features::self::super_jump_bool = false;
		bool features::self::no_clip_bool = false;
		bool features::self::god_mode_bool = false;
		bool features::self::never_wanted_bool = false;
		bool features::self::buff_hp_regen_bool = false;

		Vector3 features::self::get_blip_marker()
		{
			static Vector3 zero;
			Vector3 coords;

			bool blipFound = false;
			// search for marker blip
			int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
			{
				if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
				{
					coords = UI::GET_BLIP_INFO_ID_COORD(i);
					blipFound = true;
					break;
				}
			}
			if (blipFound)
			{
				return coords;
			}

			return zero;
		}

		Vector3 features::self::get_mission_objective()
		{
			Vector3 blipCoords;

			for (Blip x = UI::GET_FIRST_BLIP_INFO_ID(1); UI::DOES_BLIP_EXIST(x) != 0; x = UI::GET_NEXT_BLIP_INFO_ID(1))
			{
				if (UI::GET_BLIP_COLOUR(x) == 0x42 || UI::GET_BLIP_COLOUR(x) == 0x5 || UI::GET_BLIP_COLOUR(x) == 0x3C || UI::GET_BLIP_COLOUR(x) == 0x2)
				{
					blipCoords = UI::GET_BLIP_COORDS(x);
					break;
				}
			}
			for (Blip y = UI::GET_FIRST_BLIP_INFO_ID(38); UI::DOES_BLIP_EXIST(y) != 0; y = UI::GET_NEXT_BLIP_INFO_ID(38))
			{
				if (UI::GET_BLIP_COLOUR(y) == 0x0)
				{
					blipCoords = UI::GET_BLIP_COORDS(y);
					break;
				}
			}
			for (Blip z = UI::GET_FIRST_BLIP_INFO_ID(431); UI::DOES_BLIP_EXIST(z) != 0; z = UI::GET_NEXT_BLIP_INFO_ID(431))
			{
				if (UI::GET_BLIP_COLOUR(z) == 0x3C)
				{
					blipCoords = UI::GET_BLIP_COORDS(z);
					break;
				}
			}

			return blipCoords;
		}

		void features::self::tp_to_destination(Entity e, Vector3 coords)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
		}

		void features::self::tp_to_waypoint()
		{
			Vector3 coords = get_blip_marker();

			if (coords.x == 0 && coords.y == 0)
			{
				return;
			}

			// get entity to teleport
			Entity entity = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
			{
				entity = PED::GET_VEHICLE_PED_IS_USING(entity);
			}
			bool worldLevel = false;
			static float groundCheckHeight[] =
			{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
			for (int i = 0; i < 800 / sizeof(float); i++)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);

				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
				{
					worldLevel = true;
					coords.z += 3.0;
					break;
				}
			}
			if (!worldLevel)
			{
				coords.z = 1000.0;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			}
			features::self::tp_to_destination(entity, coords);

		}

		void features::self::tp_to_objective()
		{
			Vector3 coords = features::self::get_mission_objective();

			if (coords.x == 0 && coords.y == 0)
			{
				return;
			}

			// get entity to teleport
			Entity entity = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
			{
				entity = PED::GET_VEHICLE_PED_IS_USING(entity);
			}
			bool worldLevel = false;
			static float groundCheckHeight[] =
			{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
			for (int i = 0; i < 800 / sizeof(float); i++)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);

				if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
				{
					worldLevel = true;
					coords.z += 3.0;
					break;
				}
			}
			if (!worldLevel)
			{
				coords.z = 1000.0;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			}

			features::self::tp_to_destination(PLAYER::PLAYER_PED_ID(), coords);
		}
	}

	void features::self::god_mode(Player player)
	{
		if (features::self::god_mode_bool)
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), features::self::god_mode_bool);
	}

	void features::self::never_wanted(Player player)
	{

		if (features::self::never_wanted_bool)
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
		}
		else
		{
			PLAYER::SET_MAX_WANTED_LEVEL(5);
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
		}

	}

	void features::self::buff_hp_regen(Player player)
	{
		if (features::self::buff_hp_regen_bool)
		{
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(player, 1.5);
		}
		else
		{
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(player, 1.0);
		}
	}

	void features::self::super_jump()
	{
		if (features::self::super_jump_bool)
		{
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_PED_ID());
		}
	}

	void features::self::no_clip()
	{

		if (features::self::no_clip_bool) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
			if (GetAsyncKeyState(0x57) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
				float fivef = 2.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				float xVec = fivef * sin(features::basic::deg_to_rad(heading)) * -1.0f;
				float yVec = fivef * cos(features::basic::deg_to_rad(heading));
				ENTITY::SET_ENTITY_HEADING(playerPed, heading);

				pos.x -= xVec, pos.y -= yVec;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(0x53) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
				float fivef = 2.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				float xVec = fivef * sin(features::basic::deg_to_rad(heading)) * -1.0f;
				float yVec = fivef * cos(features::basic::deg_to_rad(heading));
				ENTITY::SET_ENTITY_HEADING(playerPed, heading);

				pos.x += xVec, pos.y += yVec;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(0x41) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
				float fivef = .5f;
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				ENTITY::SET_ENTITY_HEADING(playerPed, heading + 3.5f);
			}
			if (GetAsyncKeyState(0x44) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
				float fivef = .5f;
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				ENTITY::SET_ENTITY_HEADING(playerPed, heading - 3.5f);
			}
			if (GetAsyncKeyState(VK_LBUTTON)) {
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				ENTITY::SET_ENTITY_HEADING(playerPed, heading);

				pos.z += 2.5;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(VK_RBUTTON)) {
				float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
				ENTITY::SET_ENTITY_HEADING(playerPed, heading);

				pos.z -= 2.5;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
			}
		}
	}

	void features::self::give_needs(Ped ped)
	{
		ENTITY::SET_ENTITY_HEALTH(ped, 328);
		PED::ADD_ARMOUR_TO_PED(ped, 50);
		PED::CLEAR_PED_BLOOD_DAMAGE(ped);
	}

	void features::self::player_alpha(int alpha)
	{
		ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), alpha, 0);
	}

	void features::self::suicide(Ped ped)
	{
		ENTITY::SET_ENTITY_HEALTH(ped, 0);
	}

	void features::self::skip_cutscene()
	{
		if (CUTSCENE::HAS_CUTSCENE_LOADED()) {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
		else
		{
			return;
		}
	}

	void features::run_tick()
	{
		if (GetAsyncKeyState(VK_F12)) {
			features::self::tp_to_waypoint();
		}

		features::self::god_mode(PLAYER::PLAYER_ID());
		features::self::super_jump();
		features::self::no_clip();
		features::online::block_afk();
		features::recovery::start_casino();

		UpdatePlayer(); // Player List
	}

	

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
				EXCEPT_CLAUSE
				script::get_current()->yield();
		}
	}
}
