//
// Created by cedric on 2022-10-01.
//

#ifndef LD51_CLIENT_SHADERASSET_H
#define LD51_CLIENT_SHADERASSET_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <WIZ/asset/Asset.h>

namespace wiz {
    class ShaderAsset;
}


class ShaderAsset : public wiz::Asset<sf::Shader> {
protected:
    const std::string vsPath;
    const std::string fsPath;
    const std::string name;
public:
    explicit ShaderAsset(std::string  vertexShader, std::string  fragmentShader);
    void* load() const override;
    const std::string& getName() const override;

};


#endif //LD51_CLIENT_SHADERASSET_H
//
// Created by Alexander Winter on 2022-02-11.
//

#ifndef GAMETEMPLATE_SINGLEPATHASSET_H
#define GAMETEMPLATE_SINGLEPATHASSET_H




template <typename T>
class wiz::SinglePathAsset

template<typename T>
wiz::SinglePathAsset<T>::SinglePathAsset(std::string path)
        : path(std::move(path)) {}

template<typename T>
const std::string& wiz::SinglePathAsset<T>::getName() const {
    return path;
}


#endif //GAMETEMPLATE_SINGLEPATHASSET_H