#ifndef _GAME_RENDER_MWSCENE_H
#define _GAME_RENDER_MWSCENE_H

#include <utility>
#include <openengine/ogre/renderer.hpp>
#include <openengine/bullet/physic.hpp>

#include <vector>
#include <string>

namespace Ogre
{
    class Camera;
    class Viewport;
    class SceneManager;
    class SceneNode;
    class RaySceneQuery;
    class Quaternion;
    class Vector3;
}

namespace MWWorld
{
    class World;
}

namespace MWRender
{
    class Player;

    /// \brief 3D-scene (rendering and physics)

    class MWScene
    {
        OEngine::Render::OgreRenderer &rend;

        /// Root node for all objects added to the scene. This is rotated so
        /// that the OGRE coordinate system matches that used internally in
        /// Morrowind.
        Ogre::SceneNode *mwRoot;
        Ogre::RaySceneQuery *mRaySceneQuery;

		OEngine::Physic::PhysicEngine* eng;

        MWRender::Player *mPlayer;

        bool mFreeFly;

    public:

        MWScene (OEngine::Render::OgreRenderer &_rend , OEngine::Physic::PhysicEngine* physEng);

        ~MWScene();

        Ogre::Camera *getCamera() { return rend.getCamera(); }
        Ogre::SceneNode *getRoot() { return mwRoot; }
        Ogre::SceneManager *getMgr() { return rend.getScene(); }
        Ogre::Viewport *getViewport() { return rend.getViewport(); }
        Ogre::RaySceneQuery *getRaySceneQuery() { return mRaySceneQuery; }
        MWRender::Player *getPlayer() { return mPlayer; }

        /// Gets the handle of the object the player is looking at
        /// pair<name, distance>
        /// name is empty and distance = -1 if there is no object which
        /// can be faced
        std::pair<std::string, float> getFacedHandle (MWWorld::World& world);

        /// Run physics simulation and modify \a world accordingly.
        void doPhysics (float duration, MWWorld::World& world,
            const std::vector<std::pair<std::string, Ogre::Vector3> >& actors);

        /// Add object to physics system.
        void addObject (const std::string& handle, const std::string& mesh,
            const Ogre::Quaternion& rotation, float scale, const Ogre::Vector3& position);

        /// Add actor to physics system.
        void addActor (const std::string& handle, const std::string& mesh,
            const Ogre::Vector3& position);

        /// Remove object from physic systems.
        void removeObject (const std::string& handle);

        /// Move object.
        void moveObject (const std::string& handle, const Ogre::Vector3& position, bool updatePhysics);

        /// Change object's orientation.
        void rotateObject (const std::string& handle, const Ogre::Quaternion& rotation);

        /// Change object's scale.
        void scaleObject (const std::string& handle, float scale);

        /// Toggle collision mode for player. If disabled player object should ignore
        /// collisions and gravity.
        void toggleCollisionMode();

        /// Toggle render mode
        /// \todo Using an int instead of a enum here to avoid cyclic includes. Will be fixed
        /// when the mw*-refactoring is done.
        void toggleRenderMode (int mode);
    };
}

#endif
