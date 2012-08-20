#include "viking/AnimatedSpriteData.cpp"
#include "viking/AnimatedSpriteSequence.cpp"
#include "unittest/UnitTest.hpp"

int main()
{
	irr::video::ITexture* fakeTexture = reinterpret_cast<irr::video::ITexture*>(5);

	// test AnimatedSpriteSequence properties
	vik::AnimatedSpriteSequence idleSeq("idle", 0, 1, 12);
	vik::AnimatedSpriteSequence walkSeq("walk", 1, 1, 12);

	test_assert(walkSeq.getName() == "walk");
	test_assert(walkSeq.getHashedName() == vik::hashString("walk"));
	test_assert(walkSeq.getStartIndex() == 1);
	test_assert(idleSeq.getStartIndex() == 0);
	test_assert(walkSeq.getLength() == 1);
	test_assert(walkSeq.getFPS() == 12);

	// test AnimatedSpriteData properties
	vik::AnimatedSpriteData data(fakeTexture);
	const vik::AnimatedSpriteData cdata(fakeTexture);

	test_assert(data.getTexture() == fakeTexture);
	test_assert(cdata.getTexture() == fakeTexture);

	data.setWidth(3);
	data.setHeight(2);

	test_assert(data.getWidth() == 3);
	test_assert(data.getHeight() == 2);

	data.addSequence(idleSeq);

	const vik::AnimatedSpriteSequence* s0 = data.getSequence(vik::hashString("idle")), *s1 =0;
	test_assert(s0);
	test_assert(s0->getName() == idleSeq.getName());

	data.addSequence(walkSeq);
	s0 = data.getSequence(vik::hashString("idle"));
	s1 = data.getSequence(vik::hashString("walk"));
	test_assert(s0 && s1);
	test_assert(s0->getName()== idleSeq.getName());
	test_assert(s1->getName()== walkSeq.getName());

	generateReport();
}
