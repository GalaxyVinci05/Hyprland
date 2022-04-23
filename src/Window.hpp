#pragma once

#include "defines.hpp"
#include "events/Events.hpp"
#include "helpers/SubsurfaceTree.hpp"
#include "helpers/AnimatedVariable.hpp"

struct SWindowSpecialRenderData {
    float alpha = 1.f;
};  

class CWindow {
public:
    CWindow();
    ~CWindow();

    DYNLISTENER(commitWindow);
    DYNLISTENER(mapWindow);
    DYNLISTENER(unmapWindow);
    DYNLISTENER(destroyWindow);
    DYNLISTENER(setTitleWindow);
    DYNLISTENER(fullscreenWindow);
    DYNLISTENER(newPopupXDG);
   // DYNLISTENER(newSubsurfaceWindow);

    union {
        wlr_xdg_surface* xdg;
        wlr_xwayland_surface* xwayland;
    } m_uSurface;

    // this is the position and size of the "bounding box"
    Vector2D            m_vPosition = Vector2D(0,0);
    Vector2D            m_vSize = Vector2D(0,0);

    // this is the real position and size used to draw the thing
    CAnimatedVariable m_vRealPosition;
    CAnimatedVariable m_vRealSize;

    // this is used for pseudotiling
    bool                m_bIsPseudotiled = false;
    Vector2D            m_vPseudoSize = Vector2D(0,0);

    uint64_t        m_iTags = 0;
    bool            m_bIsFloating = false;
    bool            m_bDraggingTiled = false; // for dragging around tiled windows
    bool            m_bIsFullscreen = false;
    uint64_t        m_iMonitorID = -1;
    std::string     m_szTitle = "";
    int             m_iWorkspaceID = -1;

    bool            m_bIsMapped = false;

    // This is for fullscreen apps
    bool            m_bCreatedOverFullscreen = false;

    // XWayland stuff
    bool            m_bIsX11 = false;
    bool            m_bMappedX11 = false;
    uint64_t        m_iX11Type = 0;
    bool            m_bIsModal = false;
    bool            m_bX11DoesntWantBorders = false;
    DYNLISTENER(activateX11);
    DYNLISTENER(configureX11);
    //

    SSurfaceTreeNode* m_pSurfaceTree = nullptr;

    // Animated border
    CAnimatedVariable m_cRealBorderColor;

    // Fade in-out
    CAnimatedVariable m_fAlpha;
    bool            m_bFadingOut = false;
    bool            m_bReadyToDelete = false;

    // For hidden windows and stuff
    bool            m_bHidden = false;

    // Special render data, rules, etc
    SWindowSpecialRenderData m_sSpecialRenderData;

    // For the list lookup
    bool operator==(const CWindow& rhs) {
        return m_uSurface.xdg == rhs.m_uSurface.xdg && m_uSurface.xwayland == rhs.m_uSurface.xwayland && m_vPosition == rhs.m_vPosition && m_vSize == rhs.m_vSize && m_bFadingOut == rhs.m_bFadingOut;
    }

};