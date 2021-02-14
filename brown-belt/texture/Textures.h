//
// Created by smarty on 25.10.2020.
//

#ifndef TEXTURE_TEXTURES_H
#define TEXTURE_TEXTURES_H

#include "Common.h"

#include <memory>

std::unique_ptr<ITexture> MakeTextureSolid(Size size, char pixel);

std::unique_ptr<ITexture> MakeTextureCheckers(Size size, char pixel1,
                                              char pixel2);

std::unique_ptr<ITexture> MakeTextureCow();
#endif //TEXTURE_TEXTURES_H
