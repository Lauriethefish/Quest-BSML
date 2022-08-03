#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include <string>
#include <vector>
#include <map>

#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLNodeParser.hpp"

namespace BSML {
    class ComponentTypeWithData;
    class BSMLParserParams;
    class BSMLDocParser;
    class BSMLParser;
    class BSMLNode {
        public:
            BSMLNode();
            ~BSMLNode();

            virtual void Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const;
            virtual void HandleChildren(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const;
            bool valid() const;
            void AddChild(BSMLNode* child);
            
            friend class ::BSML::BSMLDocParser;
            friend class ::BSML::BSMLNodeParserBase;
            friend class ::BSML::BSMLParser;
        protected:
            bool is_valid = false;
            BSMLNode* root;
            BSMLNode* parent;
            std::vector<BSMLNode*> children;
            std::map<std::string, std::string> attributes = {};

            virtual void parse(const tinyxml2::XMLElement& elem);
    };
}