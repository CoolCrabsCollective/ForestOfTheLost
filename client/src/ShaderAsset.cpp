//
// Created by cedric on 2022-10-01.
//

#include "ShaderAsset.h"

#include <utility>

ShaderAsset::ShaderAsset(std::string vertexShader, std::string fragmentShader) : vsPath(std::move(vertexShader)), fsPath(std::move(fragmentShader)), name(vsPath + "_" + fsPath) {

}

const std::string &ShaderAsset::getName() const {
    return name;
}

void *ShaderAsset::load() const {
    auto* shader = new sf::Shader();
#ifdef OS_SWITCH
    if(!shader->loadFromFile("romfs/" + vsPath, "romfs/" + fsPath))
#else
    if(!shader->loadFromFile("res/" + vsPath, "res/" + fsPath))
#endif
        throw std::runtime_error("Shader is BAD");
    return shader;
}