#include "BSML/Parsing/BSMLParserParams.hpp"
#include "BSML/Parsing/BSMLNode.hpp"

namespace BSML {
    BSMLParserParams::~BSMLParserParams() {
        for (auto& pair : values) {
            delete pair.second;
        }
    }

    // idk if returning a vector like this is valid
    const std::vector<UnityEngine::GameObject*>& BSMLParserParams::GetObjectsWithTag(const std::string& tag) const {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            static std::vector<UnityEngine::GameObject*> _;
            return _;
        } else {
            // especially this
            return itr->second;
        }
    }

    void BSMLParserParams::AddObjectWithTag(UnityEngine::GameObject* object, const std::string& tag) {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            objectsWithIds.insert({tag, {object}});
        } else {
            itr->second.emplace_back(object);
        }
    }

    void BSMLParserParams::AddObjectsWithTag(const std::vector<UnityEngine::GameObject*>& objects, const std::string& tag) {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            objectsWithIds.emplace(tag, std::vector<UnityEngine::GameObject*>(objects.begin(), objects.end()));
        } else {
            itr->second.insert(itr->second.begin(), objects.begin(), objects.end());
        }
    }

    void BSMLParserParams::AddObjectWithTags(UnityEngine::GameObject* object, const std::vector<std::string>& tags) {
        for (auto tag : tags) {
            AddObjectWithTag(object, tag);
        }
    }

    void BSMLParserParams::PassTaggedObjects(BSMLParserParams& other) const {
        for (const auto& [tag, value] : objectsWithIds) {
            other.AddObjectsWithTag(value, tag);
        }
    }

    BSMLValue* BSMLParserParams::TryGetValue(const std::string& key) const {
        auto itr = values.find(key);
        if (itr != values.end()) return itr->second;
        return nullptr;
    }

    void BSMLParserParams::AddValue(const std::string& key, BSMLValue* value) {
        auto itr = values.find(key);
        if (itr == values.end()) {
            values.insert({key, value});
        } else {
            delete itr->second;
            itr->second = value;
        }
    }

    BSMLAction* BSMLParserParams::TryGetAction(const std::string& key) const {
        auto itr = actions.find(key);
        if (itr != actions.end()) return itr->second;
        return nullptr;
    }
    
    void BSMLParserParams::AddAction(const std::string& key, BSMLAction* action) {
        auto itr = actions.find(key);
        if (itr == actions.end()) {
            actions.insert({key, action});
        } else {
            delete itr->second;
            itr->second = action;
        }
    }

    Il2CppObject* BSMLParserParams::get_host() { return host; }
}