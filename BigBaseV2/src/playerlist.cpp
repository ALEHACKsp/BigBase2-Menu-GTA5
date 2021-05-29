#include "common.hpp"
#include "playerlist.hpp"
#include "pointers.hpp"
#include "features.hpp"
#include "gta/natives.hpp"
#include "natives.hpp"

namespace big
{
    void UpdatePlayer()
    {
        for (int32_t i = 0; i < gta::num_players; i++)
        {
            if (auto net_player = g_pointers->m_GetNetPlayer(i))
            {
                g_player[i].m_net_player = net_player;
                g_player[i].m_name = PLAYER::GET_PLAYER_NAME(i);
            }
        }
    }
}