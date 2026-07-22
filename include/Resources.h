#pragma once

#include <algorithm>
#include <filesystem>
#include <functional>
#include <ios>
#include <ranges>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

using std::function;
using std::string;
using std::unordered_map;
using std::vector;
using std::filesystem::path;

using io_exception = std::ios_base::failure;

struct Resource
{
public:
	string type;
	Texture texture = { };
	Image image     = { };
	Sound sound     = { };
	Music music     = { };
	Model model     = { };
	Font font       = { };

public:
	operator Texture() const
	{
		return texture;
	}

	operator Image() const
	{
		return image;
	}

	operator Sound() const
	{
		return sound;
	}

	operator Music() const
	{
		return music;
	}

	operator Model() const
	{
		return model;
	}

	operator Font() const
	{
		return font;
	}
};

class Resources
{
public:
	static Resources& GetInstance();

public:
	template<typename T>
	Resource* Get(const string& key);

	void Clear();

private:
	unordered_map<string, Resource> m_resources;

	unordered_map<string, function<Resource(const char*)>> m_resourceCreators =
	{
		std::make_pair(typeid(Texture).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Texture).name(), .texture = LoadTexture(path) };
		}),
		std::make_pair(typeid(Image).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Image).name(), .image = LoadImage(path) };
		}),
		std::make_pair(typeid(Sound).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Sound).name(), .sound = LoadSound(path) };
		}),
		std::make_pair(typeid(Music).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Music).name(), .music = LoadMusicStream(path) };
		}),
		std::make_pair(typeid(Model).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Model).name(), .model = LoadModel(path) };
		}),
		std::make_pair(typeid(Font).name(), [](const char* path) -> Resource
		{
			return { .type = typeid(Font).name(), .font = LoadFont(path) };
		}),
	};

	unordered_map<string, function<void(Resource)>> m_resourceDestroyers =
	{
		std::make_pair(typeid(Texture).name(), [](const Resource& resource)
		{
			UnloadTexture(resource.texture);
		}),
		std::make_pair(typeid(Image).name(), [](const Resource& resource)
		{
			UnloadImage(resource.image);
		}),
		std::make_pair(typeid(Sound).name(), [](const Resource& resource)
		{
			UnloadSound(resource.sound);
		}),
		std::make_pair(typeid(Music).name(), [](const Resource& resource)
		{
			UnloadMusicStream(resource.music);
		}),
		std::make_pair(typeid(Model).name(), [](const Resource& resource)
		{
			UnloadModel(resource.model);
		}),
		std::make_pair(typeid(Font).name(), [](const Resource& resource)
		{
			UnloadFont(resource.font);
		}),
	};

	unordered_map<string, vector<const char*>> m_resourceExtensions =
	{
		std::make_pair(typeid(Texture).name(), vector{ "jpg", "tga", "png" }),
		std::make_pair(typeid(Image).name(), vector{ "jpg", "tga", "png" }),
		std::make_pair(typeid(Sound).name(), vector{ "wav", "ogg", "mp3" }),
		std::make_pair(typeid(Music).name(), vector{ "wav", "ogg", "mp3" }),
		std::make_pair(typeid(Model).name(), vector{ "gltf", "glb", "obj" }),
		std::make_pair(typeid(Font).name(), vector{ "ttf", "otf" }),
	};

private:
	Resources() = default;

	~Resources() = default;

private:
	bool TryLoadResource(const string& key, const char* id);
};

#ifndef DEFINED_RESOURCES
#define DEFINED_RESOURCES

inline Resources& Resources::GetInstance()
{
	static Resources resources;
	return resources;
}

template<typename T>
Resource* Resources::Get(const string& key)
{
	static_assert(
	              std::is_same_v<T, Texture> || std::is_same_v<T, Image> || std::is_same_v<T, Sound> ||
	              std::is_same_v<T, Music> || std::is_same_v<T, Model> || std::is_same_v<T, Font>,
	              "T is not a Texture, Image, Sound, Music, Model or Font"
	             );

	// If the resource has already been loaded, we can just ignore it
	if (m_resources.contains(key))
	{
		return &m_resources[key];
	}

	// No file was found, so throw an error
	if (!TryLoadResource(key, typeid(T).name()))
	{
		throw io_exception("Failed to load or find resource for key: " + key);
	}

	return &m_resources[key];
}

inline void Resources::Clear()
{
	for (const Resource& res : m_resources | std::views::values)
	{
		m_resourceDestroyers[res.type](res);
	}
}

inline bool Resources::TryLoadResource(const string& key, const char* id)
{
	return std::ranges::any_of(m_resourceExtensions[id], [this, key, id](const string& ext)
	{
		if (const path resPath = path("resources").append(key + "." + ext); std::filesystem::exists(resPath))
		{
			m_resources[key] = m_resourceCreators[id](resPath.string().c_str());
			return true;
		}

		return false;
	});
}
#endif
