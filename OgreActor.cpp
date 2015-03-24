#include "OgreActor.h"

OgreActor::OgreActor(SceneManager * sceneMgr) : m_sceneMgr(sceneMgr) {

}

OgreActor::~OgreActor(){
	delete m_node;
	delete m_sceneMgr;
}

void OgreActor::trackPhysObj(Vector3 position, Quaternion newOgRot){
	//set the nodes position
	m_node->setPosition(position);
	//set its current rotation
	m_node->setOrientation(newOgRot);
}

void OgreActor::createOSphere(Vector3 position, Real size) {
	Ogre::Entity* ogreSphere = m_sceneMgr->createEntity("Sphere" + StringConverter::toString(ID), "sphere.mesh");
	ogreSphere->setMaterialName("Examples/Checker");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode" + StringConverter::toString(ID));//add a ID generator to this later to add more
	m_node->attachObject(ogreSphere);
	AxisAlignedBox abb = ogreSphere->getBoundingBox();
	Vector3 sz = abb.getSize();
	float scalesizex = size/sz.x;
	float scalesizey = size/sz.y;
	float scalesizez = size/sz.z;
	//get down to 1 unit size first, then multiply by size
	m_node->scale( scalesizex, scalesizey, scalesizez );
	m_node->setPosition(position);
	ID++;
}

void OgreActor::createOCuboid(Vector3 position, Vector3 widths) {
	Ogre::Entity* ogreCuboid = m_sceneMgr->createEntity("Cube" + StringConverter::toString(ID), "cube.mesh");
	ogreCuboid->setMaterialName("Examples/BumpyMetal");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode" + StringConverter::toString(ID));//add a ID generator to this later to add more
	m_node->attachObject(ogreCuboid);
	AxisAlignedBox abb = ogreCuboid->getBoundingBox();
	Vector3 sz = abb.getSize();
	float scalesizex = widths.x/sz.x;
	float scalesizey = widths.y/sz.y;
	float scalesizez = widths.z/sz.z;
	//get down to 1 unit size first, then multiply by size
	m_node->scale( (scalesizex), (scalesizey), (scalesizez) );
	m_node->setPosition(position);
	ID++;
}