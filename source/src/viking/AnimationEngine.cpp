#include "viking/AnimationEngine.hpp"
#include "viking/GameApp.hpp"
#include <irrxml/irrXML.h>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <iostream>

namespace vik
{

void AnimationEngine::update(GameTime& time)
{
	for (auto it = spriteList.begin(); it != spriteList.end(); ++it)
	{
		(*it)->update(time);
	}
}

void AnimationEngine::addSprite(std::shared_ptr<AnimatedSprite> sprite)
{
	spriteList.push_back(sprite);
}

void AnimationEngine::removeSprite(const std::shared_ptr<AnimatedSprite>& sprite)
{
	auto it = std::find(spriteList.begin(), spriteList.end(), sprite);
	assert(it != spriteList.end());
	spriteList.erase(it);
}

std::shared_ptr<AnimatedSpriteData> AnimationEngine::load(const std::string& filename, bool cacheIt)
{
	std::vector<std::shared_ptr<AnimatedSpriteData>>::iterator cacheLookup;
	for (cacheLookup = spriteDataCache.begin(); cacheLookup != spriteDataCache.end(); ++cacheLookup)
	{
		irr::core::stringc n = (*cacheLookup)->getTexture()->getName().getInternalName();
		if (n == filename.c_str()) break;
	}

	if (cacheLookup != spriteDataCache.end())
	{
		return *cacheLookup;
	}

	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(filename.c_str());

	if (!xml)
	{
		std::cout << "Failed to open XML file: " << filename << std::endl;
		return nullptr;
	}

	std::string textureFileName;
	int tileSetWidth;
	int tileSetHeight;
	std::vector<AnimatedSpriteSequence> sequences;
	
	while (xml->read())
	{
		irr::io::EXML_NODE node = xml->getNodeType();
		if (node == irr::io::EXN_ELEMENT)
		{
			const char* elm = xml->getNodeName();
			if (!strcmp(elm, "animSequence"))
			{
				std::string seqName = xml->getAttributeValue("name");
				std::istringstream sseqStart(xml->getAttributeValue("start"));
				std::istringstream sseqLength(xml->getAttributeValue("length"));
				std::istringstream sseqFPS(xml->getAttributeValue("fps"));
				int seqStart, seqLength, seqFPS;
				sseqStart >> seqStart;
				sseqLength >> seqLength;
				sseqFPS >> seqFPS;

				std::cout << "Read animSequence: " << seqName << " start: " << seqStart << " length: " << seqLength << " fps: " << seqFPS << std::endl;
				sequences.push_back(AnimatedSpriteSequence(seqName,seqStart,seqLength,seqFPS));
			}
			else if (!strcmp(elm, "tileSet"))
			{
				textureFileName = xml->getAttributeValue("texture");
				std::istringstream swidth(xml->getAttributeValue("width"));
				std::istringstream sheight(xml->getAttributeValue("height"));
				swidth >> tileSetWidth;
				sheight >> tileSetHeight;

				std::cout << "Read tileSet: " << textureFileName << " width: " << tileSetWidth << " height: " << tileSetHeight << std::endl;
			}
		}
	}

	irr::video::ITexture* tex = GameApp::getSingleton().getVideoDriver()->getTexture(textureFileName.c_str());
	auto spr = std::make_shared<AnimatedSpriteData>(tex);
	spr->setWidth(tileSetWidth);
	spr->setHeight(tileSetHeight);
	for (size_t i = 0; i < sequences.size(); i++)
	{
		spr->addSequence(sequences[i]);
	}

	if (cacheIt)
	{
		spriteDataCache.push_back(spr);
	}

	delete xml;

	return spr;
}

void AnimationEngine::clearSpriteDataCache()
{
	spriteDataCache.clear();
}

} // end namespace vik
