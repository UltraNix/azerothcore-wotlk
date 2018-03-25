/*
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _PATH_GENERATOR_H
#define _PATH_GENERATOR_H

#include "SharedDefines.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "MoveSplineInitArgs.h"
#include "MMapFactory.h"
#include "MMapManager.h"

class Unit;

// 74*4.0f=296y  number_of_points*interval = max_path_len
// this is way more than actual evade range
// I think we can safely cut those down even more
#define MAX_PATH_LENGTH             74
#define MAX_POINT_PATH_LENGTH       74

#define SMOOTH_PATH_STEP_SIZE       4.0f
#define SMOOTH_PATH_SLOP            0.3f
#define ALLOWED_DIST_FROM_POLY      2.5f
#define ADDED_Z_FOR_POLY_LOOKUP     0.3f
#define DISALLOW_TIME_AFTER_FAIL    3 // secs
#define MAX_FIXABLE_Z_ERROR         12.0f

#define VERTEX_SIZE       3
#define INVALID_POLYREF   0

enum PathType
{
    PATHFIND_BLANK          = 0x00,   // path not built yet
    PATHFIND_NORMAL         = 0x01,   // normal path
    PATHFIND_SHORTCUT       = 0x02,   // travel through obstacles, terrain, air, etc (old behavior)
    PATHFIND_INCOMPLETE     = 0x04,   // we have partial path to follow - getting closer to target
    PATHFIND_NOPATH         = 0x08,   // no valid path at all or error in generating one
    PATHFIND_NOT_USING_PATH = 0x10,   // used when we are either flying/swiming or on map w/o mmaps
    PATHFIND_SHORT          = 0x20,   // path is longer or equal to its limited path length
};

class PathGeneratorContext
{
public:
    explicit PathGeneratorContext( Unit const* owner );

    void                 SetPathLengthLimit( float limit );
    float                GetPathLengthLimit() const;

    virtual G3D::Vector3 GetStartPosition() const;

    virtual bool         CanSourceSwim() const;
    virtual bool         CanSourceFly() const;
    virtual bool         CanSourceWalk() const;
    virtual bool         CanSourceWaterWalk() const;

    virtual bool         IsIgnoringPathFinding() const;
    virtual bool         IsSourceInWater() const;

    virtual float        GetSourceSize() const;
    virtual uint32_t     GetPhaseMask() const;
    virtual Map const*   GetBaseMap() const;
    virtual Map const*   GetMap() const;

protected:
    Unit const*          m_source;
    float                m_pathLengthLimit;
};

class AsyncPathGeneratorContext final : public PathGeneratorContext
{
public:
    AsyncPathGeneratorContext( Unit const* owner, G3D::Vector3 const& destPos, bool forceShortcut = false );

    virtual G3D::Vector3    GetStartPosition() const override;
    G3D::Vector3 const&     GetEndPosition() const;

    virtual bool            CanSourceSwim() const override;
    virtual bool            CanSourceFly() const override;
    virtual bool            CanSourceWalk() const override;
    virtual bool            CanSourceWaterWalk() const override;

    virtual bool            IsIgnoringPathFinding() const override;
    virtual bool            IsSourceInWater() const override;
    bool                    IsForcingShortcut() const;

    virtual float           GetSourceSize() const override;
    virtual uint32_t        GetPhaseMask() const override;
    virtual Map const*      GetBaseMap() const override;
    virtual Map const*      GetMap() const override;

protected:
    G3D::Vector3            m_startPosition;
    G3D::Vector3            m_endPosition;
    float                   m_sourceSize;
    uint32_t                m_phaseMask;
    Map const*              m_sourceMap;

    bool                    m_isForcingShortcut     : 1;
    bool                    m_canSourceSwim         : 1;
    bool                    m_canSourceFly          : 1;
    bool                    m_canSourceWalk         : 1;
    bool                    m_canSourceWaterWalk    : 1;
    bool                    m_isSourceInWater       : 1;
    bool                    m_isIgnoringPathFinding : 1;
};

class PathGenerator
{
    public:
        explicit PathGenerator( PathGeneratorContext const* ctx, bool destroyContext = false );
        ~PathGenerator();

        // Calculate the path from owner to given destination
        // return: true if new path was calculated, false otherwise (no change needed)
        bool                            CalculatePath(float destX, float destY, float destZ, bool forceDest = false);

        // result getters
        G3D::Vector3 const&             GetStartPosition() const;
        G3D::Vector3 const&             GetEndPosition() const;
        G3D::Vector3 const&             GetActualEndPosition() const { return _actualEndPosition; }
        Movement::PointsArray const&    GetPath() const { return _pathPoints; }
        Movement::PointsArray &&        StealPath() { return std::move(_pathPoints ); }

        PathType                        GetPathType() const;
        float                           GetPathLength() const;

    private:
        PathGeneratorContext const*  m_context;
        bool                         m_destroyContext;

        dtPolyRef               _pathPolyRefs[MAX_PATH_LENGTH];   // array of detour polygon references
        uint32                  _polyLength;                         // number of polygons in the path

        Movement::PointsArray   _pathPoints;  // our actual (x,y,z) path to the target
        PathType                _type;                     // tells what kind of path this is

        bool                    _forceDestination; // when set, we will always arrive at given point

        G3D::Vector3            _startPosition;        // {x, y, z} of current location
        G3D::Vector3            _endPosition;          // {x, y, z} of the destination
        G3D::Vector3            _actualEndPosition;    // {x, y, z} of the closest possible point to given destination

        dtNavMesh const*        _navMesh;              // the nav mesh
        dtNavMeshQuery*         _navMeshQuery;    // the nav mesh query used to find the path

        dtQueryFilter _filter;  // use single filter for all movements, update it when needed

        void        SetStartPosition(G3D::Vector3 const& point) { _startPosition = point; }
        void        SetEndPosition(G3D::Vector3 const& point) { _actualEndPosition = point; _endPosition = point; }
        void        SetActualEndPosition(G3D::Vector3 const& point) { _actualEndPosition = point; }
        void        UpdateAllowedPositionZ( G3D::Vector3 & pos );

        void        Clear();

        float       Dist3DSqr(G3D::Vector3 const& p1, G3D::Vector3 const& p2) const;
        bool        HaveTile( G3D::Vector3 const& p ) const;
        bool        InRange(G3D::Vector3 const& p1, G3D::Vector3 const& p2, float r, float h) const;
        bool        InRangeYZX(float const* v1, float const* v2, float r, float h) const;

        dtPolyRef   GetPathPolyByPosition(dtPolyRef const* polyPath, uint32 polyPathSize, float const* Point, float* Distance = NULL) const;
        dtPolyRef   GetPolyByLocation(float* Point, float* Distance) const;
        NavTerrain  GetNavTerrain( float x, float y, float z );


        void        BuildPolyPath( G3D::Vector3 const& startPos, G3D::Vector3 const& endPos, ACE_RW_Thread_Mutex& lock );
        void        BuildPointPath( float const* startPoint, float const* endPoint );
        void        BuildShortcut();

        void        CreateFilter();
        void        UpdateFilter();

        // smooth path aux functions
        uint32      FixupCorridor(dtPolyRef* path, uint32 npath, uint32 maxPath, dtPolyRef const* visited, uint32 nvisited);
        bool        GetSteerTarget(float const* startPos, float const* endPos, float minTargetDist, dtPolyRef const* path, uint32 pathSize, float* steerPos,
                            unsigned char& steerPosFlag, dtPolyRef& steerPosRef);
        dtStatus    FindSmoothPath(float const* startPos, float const* endPos,
                              dtPolyRef const* polyPath, uint32 polyPathSize,
                              float* smoothPath, int* smoothPathSize, uint32 smoothPathMaxSize);
};

#endif
