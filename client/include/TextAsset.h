//
// Created by cedric on 2022-10-01.
//

#ifndef LD51_CLIENT_TEXTASSET_H
#define LD51_CLIENT_TEXTASSET_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <WIZ/asset/Asset.h>



class TextAsset : public wiz::Asset<std::string> {
protected:
    const std::string path;
public:
    explicit TextAsset(std::string path);
    void* load() const override;
    const std::string& getName() const override;

};


#endif //LD51_CLIENT_TEXTASSET_H