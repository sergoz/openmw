#ifndef _ESM_LTEX_H
#define _ESM_LTEX_H

#include "esm_reader.hpp"

namespace ESM {

/*
 * Texture used for texturing landscape.
 *
 * They are probably indexed by 'num', not 'id', but I don't know for
 * sure. And num is not unique between files, so one option is to keep
 * a separate list for each input file (that has LTEX records, of
 * course.) We also need to resolve references to already existing
 * land textures to save space.

 * I'm not sure if it is even possible to override existing land
 * textures, probably not. I'll have to try it, and have to mimic the
 * behaviour of morrowind. First, check what you are allowed to do in
 * the editor. Then make an esp which changes a commonly used land
 * texture, and see if it affects the game.
 */

struct LandTexture
{
  std::string id, texture;
  int index;

  void load(ESMReader &esm)
  {
    esm.getHNT(index, "INTV");
    texture = esm.getHNString("DATA");
  }
};
}
#endif
