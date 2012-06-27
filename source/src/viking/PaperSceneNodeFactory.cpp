#include "viking/PaperSceneNodeFactory.hpp"
#include <irrlicht/CMeshBuffer.h>
#include <irrlicht/SMesh.h>
#include <irrlicht/IMeshSceneNode.h>
#include "viking/IrrlichtStream.hpp"

using namespace irr;

namespace vik
{

PaperSceneNodeFactory::PaperSceneNodeFactory(scene::ISceneManager* smgr):
smgr(smgr)
{
}

scene::ISceneNode* PaperSceneNodeFactory::create(video::ITexture* tex)
{
	using video::S3DVertex;

	const video::SColor white(255, 255, 255, 255);
	const f32 width = tex->getSize().Width;
	const f32 height = tex->getSize().Height;
	const S3DVertex verts[] = {
		S3DVertex(0.0f,0.0f,0.0f, -1.0f,-1.0f,0.0f, white, 0.0f, 0.0f),
		S3DVertex(0.0f,height,0.0f, -1.0f,1.0f,0.0f, white, 0.0f, 1.0f),
		S3DVertex(width,height,0.0f, -1.0f,-1.0f,0.0f, white, 1.0f, 1.0f),
		S3DVertex(width,0.0f,0.0f, -1.0f,-1.0f,0.0f, white, 1.0f, 0.0f)
	};
	const u16 indices[] = {
		0, 1, 2, 0, 2, 3
	};

	scene::IMeshBuffer* paperBuffer = new scene::SMeshBuffer();
	paperBuffer->append(verts, sizeof(verts)/sizeof(*verts), indices, sizeof(indices)/sizeof(*indices));

	scene::SMesh* paperMesh = new scene::SMesh();
	paperMesh->addMeshBuffer(paperBuffer);
	paperMesh->setBoundingBox(paperBuffer->getBoundingBox());

	scene::IMeshSceneNode* createdNode = smgr->addMeshSceneNode(paperMesh);
	createdNode->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);
	createdNode->setMaterialFlag(video::EMF_FRONT_FACE_CULLING, false);
	createdNode->setMaterialFlag(video::EMF_LIGHTING, false);
	createdNode->setMaterialTexture(0, tex);

	paperMesh->drop();
	paperBuffer->drop();

	return createdNode;
}

} // end namespace vik
