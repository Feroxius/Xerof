#pragma once
#include "rapidjson\document.h"
#include "rapidjson\error\en.h"
#include "..\utils\Elem2D.h"
#include "Environment.h"
#include "..\utils\JSONUtils.h"
#include "LandTypePropotions.h"

// File paths
static const char* DEFAULT_MAP_CONFIG        = "map/DefaultConfig.json";
static const char* MAP_LIMITS                = "map/Limits.json";

// JSON configuration file elements
static const char* CONFIG_ROOT_ELEM          = "XerofMapConfig";
static const char* DIM_ELEM                  = "MapDimensions";
static const char* DIM_WIDTH_SUB_ELEM        = "width";
static const char* DIM_HEIGHT_SUB_ELEM       = "height";
static const char* LAND_PROPOR_ELEM          = "LandProportion";
static const char* INIT_LAND_PROP_ELEM       = "InitLandProportion";
static const char* LAND_DISPERS_ELEM         = "LandDispertion";
static const char* LAND_COMPACT_ELEM         = "LandCompactness";
static const char* TUNDRA_TRANS_W_ELEM       = "TundraTransitionWidth";
static const char* OCEAN_BORDERS_W_ELEM      = "OceanBordersWidth";
static const char* ROCKY_BORDERS_W_ELE       = "RockyZonesThickness";
static const char* TOTAL_LAND_TYPE_PROP_ELEM = "TotalLandTypeProportions";
static const char* INIT_LAND_TYPE_PROP_ELEM  = "InitialSeedLandTypeProportions";

// JSON configurations limits file elements
static const char* LIMITS_ROOT_ELEM          = "XerofMapConfigLimits";
static const char* MIN_MAP_SIZE_ELEM         = "MinimumMapSize";
static const char* MAX_MAP_SIZE_ELEM         = "MaximumMapSize";


class MapConfig
{
public:
    Dimensions      m_Dim;
    double          m_LandProp;
    double          m_InitLandProp;
    double          m_LandDispertion;
    double          m_LandCompactness;
    UINT            m_RandTundraWidth;
    UINT            m_OceanBorderWidth;
    UINT            m_RockyZoneThickn;
    LandProportions m_TotalProp;
    LandProportions m_InitProp;

    // CONSTRUCTOR/DESTRUCTOR
    MapConfig();
    MapConfig(const char* i_ParamFile);

private:
    // CONSTRUCTOR/DESTRUCTOR
    UINT readMapSizeElem(const Value& i_Root, const char* i_Elem);

    // LOAD CONFIGURATION LIMITS
    struct Limits
    {
        UINT m_MinMapSize;
        UINT m_MaxMapSize;
    };
    static const Limits s_ConfigLimits;

    static Limits loadConfigLimits();
};