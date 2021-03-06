#include "MapGenerator.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map*       MapGenerator::s_Map      = NULL;
MapConfig* MapGenerator::s_Config   = NULL;
Coord      MapGenerator::s_ULCorner;
Coord      MapGenerator::s_LRCorner;

Map& MapGenerator::generate()
{
    return generate(DEFAULT_MAP_CONFIG);
}

Map& MapGenerator::generate(const char* i_MapConfigFile)
{
    // Read config file
    s_Config = new MapConfig(i_MapConfigFile);

    // Initialized map with dimensions specified by the config file
    s_Map = new Map(s_Config->m_Dim);

    // Build map constraints from the config file
    s_Config->buildConstraints(*s_Map);

    // Initialize environments
    placeBorders();

    // Fill with initial environment
    fillWithInitEnv();

    // Execute map generation phases
    for (const Phase& phase : s_Config->m_Phases) {
        executeMapGenPhase(phase);
    }

    // Delete map config
    delete s_Config;

    return *s_Map;
}

void MapGenerator::placeBorders()
{
    // Zone that will be filled by the initial env 
    // (borders may reduce this space)
    s_ULCorner = Coord(0, 0);
    s_LRCorner = Coord(s_Map->m_Dim);

    // Borders overlap each other (the last one has the priority)
    for (Border border : s_Config->m_Borders) {
        // Adjust generation zone
        switch (border.m_Side) {
        case UP:    s_ULCorner.y = border.m_Width; break;
        case DOWN:  s_LRCorner.y = s_Map->m_Dim.y - border.m_Width; break;
        case LEFT:  s_ULCorner.x = border.m_Width; break;
        case RIGHT: s_LRCorner.x = s_Map->m_Dim.x - border.m_Width; break;
        }

        // Skip ocean borders because tiles are ocean at initialization
        if (border.m_Env == OCEAN) {
            // Tiles are already ocean
            continue;
        }

        // Generate borders
        Coord coord;
        switch (border.m_Side) {
        case UP:
            if (border.m_Width > s_Map->m_Dim.y * 0.5) {
                FatalErrorDialog("North border cannot be \
                                  larger than half of the map");
            }
            for (UINT i = 0; i < border.m_Width * s_Map->m_Dim.x; ++i) {
                s_Map->m_Tiles[i].setEnvironment(border.m_Env);
            }
            break;
        case DOWN:
            if (border.m_Width > s_Map->m_Dim.y * 0.5) {
                FatalErrorDialog("South border cannot be \
                                  larger than half of the map");
            }
            for (UINT i(s_Map->m_Dim.x * s_Map->m_Dim.y - 
                border.m_Width * s_Map->m_Dim.x); 
                i < s_Map->m_Dim.x * s_Map->m_Dim.y; ++i) {
                s_Map->m_Tiles[i].setEnvironment(border.m_Env);
            }
            break;
        case LEFT:
            if (border.m_Width > s_Map->m_Dim.x * 0.5) {
                FatalErrorDialog("West border cannot be \
                                  larger than half of the map");
            }
            for (coord.y = 0; coord.y < s_Map->m_Dim.y; ++coord.y) {
                for (coord.x = 0; coord.x < border.m_Width; ++coord.x) {
                    s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                        setEnvironment(border.m_Env);
                }
            }
            break;
        case RIGHT:
            if (border.m_Width > s_Map->m_Dim.x * 0.5) {
                FatalErrorDialog("East border cannot be \
                                  larger than half of the map");
            }
            UINT dimX(s_Map->m_Dim.x);
            for (coord.y = 0; coord.y < s_Map->m_Dim.y; ++coord.y) {
                for (coord.x = dimX - border.m_Width; coord.x<dimX; ++coord.x) {
                    s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                        setEnvironment(border.m_Env);
                }
            }
            break;
        }
    }
}

void MapGenerator::fillWithInitEnv()
{
    if (s_Config->m_InitEnvType == OCEAN) {
        // Tiles are already ocean
        return;
    }

    Coord coord;
    for (coord.y = s_ULCorner.y; coord.y < s_LRCorner.y; ++coord.y) {
        for (coord.x = s_ULCorner.x; coord.x < s_LRCorner.x; ++coord.x) {
            s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                setEnvironment(s_Config->m_InitEnvType);
        }
    }
}

void MapGenerator::executeMapGenPhase(const Phase& i_Phase)
{
    for (const auto& envCnstrnts : i_Phase.m_Cnstrts) {
        UINT qty(envCnstrnts.second.first);
        UINT placed(0);
        UINT tries(0);

        // Progress logging
        std::stringstream ss;
        ss << "World generation - " << i_Phase.m_Name << " - " 
            << ENV_NAMES[envCnstrnts.first] << " [" << qty << " tiles]";
        std::string msg = ss.str();
        ProgressLogger progressLogger(qty, msg);

        // Loop until all needed tiles are placed
        while (placed < qty) {
            // Generate a random coord
            const Coord coord(randCoord());

            // At first, the probability of placing the env. is 100 %
            double totalProb(1.0);

            // Each constraint will reduce this probability 
            // (product of all constraint weights)
            for (const auto& constraint : envCnstrnts.second.second) {
                totalProb *= constraint->getWeightFor(coord);
            }

            // Generate a probability
            if (randProb() < totalProb) {
                // Set the env.
                s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x]
                    .setEnvironment(envCnstrnts.first);
                ++placed;
                progressLogger.next();
            }
            else if (++tries > i_Phase.m_MaxTries) {
                LOG(ERROR) << "Maximum number of tries reached."
                           << " Skipping phase for this environent.";
                break;
            }
        }
    }
}

const Coord MapGenerator::randCoord()
{
    UINT x(randUINT(s_ULCorner.x, s_LRCorner.x - 1));
    UINT y(randUINT(s_ULCorner.y, s_LRCorner.y - 1));
    return Coord(x, y);
}