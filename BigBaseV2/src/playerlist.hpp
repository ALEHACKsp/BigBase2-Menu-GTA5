#pragma once
#include "gta/player.hpp"

namespace big
{
    void UpdatePlayer();

    class playerclass
    {
    public:
        rage::netPlayer* m_net_player;
        std::string m_name;
        uint64_t m_rockstar_id;
        std::string m_str_rockstar_id;
    };

    inline playerclass g_player[gta::num_players]{};
}