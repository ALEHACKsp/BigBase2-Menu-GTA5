#pragma once
#include "common.hpp"

namespace big::features
{
	// Players list
	namespace online {
		extern bool block_afk_bool;

		void show_players();
		void draw_extra_info();
		extern int selectedPlayer;

		void teleport_to_player(Player player);
        void cage(Player player);

		void block_afk();
		void disable_phone(bool b);
		void bst();
		void bribe();
		void no_orb_cooldown();
		void ewo_cooldown_remove();
		void grinding_mode();
		void block_vote();
	}

	namespace basic {
		float deg_to_rad(float deg);
		Hash load(char* str);
		Hash $(std::string str);
	}

	// Recovery 
	namespace recovery {
		extern bool start_casino_bool;

		void start_casino();
		void packed_bool(int loop, int looptwo, char* boolname);
		void remove_bad_sport();
		void reset_reports();
		void unlock_fast_run();
		void unlock_wireframe_suits();
		void unlock_raygun_paint();
		void unlock_character_stats();
		void unlock_weapon_colors();
		void setup_cayo(const int choice);
		void change_kd(const int choice, const int kills = 100, const int deaths = 0);
	}

	namespace weapons {
		extern bool unlimited_ammo_bool;
		extern bool unlimited_clip_bool;

		void unlimited_ammo(Ped ped);
		void unlimited_clip(Ped ped);
		void give_all_weps(Ped ped);
		void give_all_mk2(Ped ped);
		void give_stun_gun(Ped ped);
		void give_scanner(Ped ped);
		void refill_ammo(Ped ped);
	}

	namespace vehicles {
		void max_vehicle();
		void spawn_vehicle(Ped ped, char* c);
		void set_plate(Vehicle veh, char* c);
	}

	namespace objects {
		void request_control_id(int network_id);
		void request_control_ent(Entity entity);
		void attach_obj_to_player(char* object, Player player);
		void detach_all(Player player);
	}

	// Self
	namespace self {
		extern bool god_mode_bool;
		extern bool never_wanted_bool;
		extern bool buff_hp_regen_bool;
		extern bool super_jump_bool;
		extern bool no_clip_bool;

		Vector3 get_blip_marker();
		Vector3 get_mission_objective();

		void tp_to_destination(Entity e, Vector3 coords);
		void tp_to_waypoint();
		void tp_to_objective();

		void god_mode(Player player);
		void never_wanted(Player player);
		void buff_hp_regen(Player player);
		void super_jump();
		void no_clip();
		void give_needs(Ped ped);
		void player_alpha(int alpha);
		void suicide(Ped ped);
		void skip_cutscene();
	}

	void run_tick();
	void script_func();
}
