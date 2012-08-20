#include <vector>
#include <iostream>
#include <map>
#include <cstring>
#include "viking/HashedString.hpp"
#include "unittest/UnitTest.hpp"

// future ideas: 
// constructing classes from Class objects
// also reflecting available member functions in one way or other
// hooking up to scripting engine

namespace vik
{

// interface to the RTTI (RunTime Type Information) of a class
// Not to be created directly, use the macro below.
class Class
{
public:
	Class(const char* className, const std::vector<const Class*>& parents):
	className(className),
  	parents(parents)
	{
	}

	const char* getName() const
	{
		return className;
	}

	// returns true if the Class is a parent/derivation/subclass of the other
	bool derivesFrom(const Class& other) const
	{
		if (this == &other)
		{
			return true;
		}

		for (unsigned i = 0; i < parents.size(); ++i)
		{
			if (parents[i]->derivesFrom(other))
			{
				return true;
			}
		}

		return false;
	}

	// returns ancestor/base/super Class by name. Returns 0 if the parent is not found.
	// will return "this" also if you ask for the same class as what it is.
	const Class* getBase(const char* baseName) const
	{
		if (strcmp(className, baseName) == 0)
		{
			return this;
		}

		for (unsigned i = 0; i < parents.size(); ++i)
		{
			if (const Class* myParent = parents[i]->getBase(baseName))
			{
				return myParent;
			}
		}

		return 0;
	}
private:
	const char* className;
	const std::vector<const Class*> parents;
};

// global static table for the RTTI system
class Reflection
{
public:
	~Reflection()
	{
		const std::map<HashedString, Class*>::const_iterator end = classTable.end();
		for (std::map<HashedString, Class*>::iterator it = classTable.begin(); it != end; ++it)
		{
			delete (*it).second;
		}
	}

	// add new class definition and return it
	// if class already exists, will return the already existing instance of it.
	template<class Derived, class... Parents>
	const Class* addClass(const char* className)
	{
		if (const Class* found = findClass(className))
		{
			return found;
		}

		Class* newClass = new Class(className, { &Parents::getClass()... });
		classTable[HashedString(className)] = newClass;

		return newClass;
	}

	// lookup class definition from hashed name
	const Class* findClass(const HashedString& hash) const
	{
		std::map<HashedString, Class*>::const_iterator it = classTable.find(hash);

		if (it == classTable.end())
		{
			return 0;
		}

		return (*it).second;
	}

	// lookup class definition from name
	const Class* findClass(const char* className)
	{
		return findClass(HashedString(className));
	}

	// for debugging the RTTI system
	// todo: show hierarchy as well
	void debugPrint() const
	{
		std::cout << "<hashed name key,address> : class name : hashed name" << std::endl;

		const std::map<HashedString, Class*>::const_iterator end = classTable.end();
		for (std::map<HashedString, Class*>::const_iterator it = classTable.begin(); it != end; ++it)
		{
			std::cout << "<" << (*it).first << ", " << (*it).second << "> : "
			<< (*it).second->getName() << " : "
			<< HashedString((*it).second->getName()) << std::endl;
		}
	}

	static Reflection& getSingleton()
	{
		static Reflection refl;
		return refl;
	}
private:

	Reflection() = default;

	// mapping of hashed strings of class names to their RTTI objects
	std::map<HashedString, Class*> classTable;
};

// Declares necessary members for RTTI. To be used within the class declaration.
// the _classInfo variable is an implementation detail. Use ::getClass() to access it instead.
#define ClassDeclare() \
	static const Class* _classInfoDetail; \
	virtual const Class& getInstanceClass() const \
	{ \
		return *_classInfoDetail; \
	} \
	static const Class& getClass() \
	{ \
		return *_classInfoDetail; \
	} 

// Defines a new Class object with the given parents and adds it to the Reflection singleton at static initialization time.
// Watch out: ClassDefine(SomeClass::NestedClass) creates a different definition than ClassInfo(NestedClass) but both are accepted.
#define ClassDefine(ThisClass, Parents...) \
const Class* ThisClass::_classInfoDetail = Reflection::getSingleton().addClass<ThisClass,##Parents>(#ThisClass);

} // end namespace vik

using namespace vik;

// Unit tests

class StaffMember
{
public:
	virtual ~StaffMember(){}
	ClassDeclare();
};

class Librarian : virtual public StaffMember
{
public:
	ClassDeclare();
};

class Teacher : virtual public StaffMember
{
public:
	ClassDeclare();
};

class TeachingLibrarian : public Teacher, public Librarian
{
public:
	ClassDeclare();
};

class Sailboat
{
public:
	virtual ~Sailboat(){}
	ClassDeclare();
};

class Dog
{
public:
	ClassDeclare();
};

ClassDefine(StaffMember);
ClassDefine(Librarian,StaffMember);
ClassDefine(Teacher,StaffMember);
ClassDefine(TeachingLibrarian,Teacher,Librarian);
ClassDefine(Sailboat);
ClassDefine(Dog);

class UnitTest
{

	void classlessRTTITest()
	{
		const Class vehicleType("Vehicle", {});
		const Class landVehicleType("LandVehicle", { &vehicleType });
		const Class waterVehicleType("WaterVehicle", { &vehicleType });
		const Class amphibiousVehicleType("AmphibiousVehicle", { &landVehicleType, &waterVehicleType });
		const Class fruitType("Fruit", {});

		// class name
		test_assert(std::string(vehicleType.getName()) == "Vehicle");

		// single inheritance valid upcast
		test_assert(landVehicleType.derivesFrom(vehicleType));

		// single inheritance invalid upcast
		test_assert(landVehicleType.derivesFrom(fruitType) == false);

		// single inheritance invalid cross-cast
		test_assert(landVehicleType.derivesFrom(waterVehicleType) == false);

		// multiple inheritance 1 level valid upcast
		test_assert(amphibiousVehicleType.derivesFrom(landVehicleType));

		// multiple inheritance 2 level valid upcast
		test_assert(amphibiousVehicleType.derivesFrom(vehicleType));

		// multiple inheritance 1 level invalid upcast
		test_assert(amphibiousVehicleType.derivesFrom(fruitType) == false);

		// getting valid grandparent class by name
		test_assert(amphibiousVehicleType.getBase("Vehicle") == &vehicleType);

		// getting valid parent class by name
		test_assert(amphibiousVehicleType.getBase("WaterVehicle") == &waterVehicleType);

		// getting valid self class by name
		test_assert(waterVehicleType.getBase("WaterVehicle") == &waterVehicleType);

		std::cout << "Classless tests successful" << std::endl;
	}

	void classfulRTTITest()
	{
		StaffMember* staff = new StaffMember();
		StaffMember* librarian = new Librarian();
		StaffMember* teacher = new Teacher();
		StaffMember* teachingLibrarian = new TeachingLibrarian();
		Sailboat* sailboat = new Sailboat();

		// class name
		test_assert(std::string(staff->getInstanceClass().getName()) == "StaffMember");

		// single inheritance valid upcast
		test_assert(librarian->getInstanceClass().derivesFrom(staff->getInstanceClass()));

		// single inheritance valid upcast through static member
		test_assert(librarian->getInstanceClass().derivesFrom(StaffMember::getClass()));

		// single inheritance invalid upcast
		test_assert(librarian->getInstanceClass().derivesFrom(sailboat->getInstanceClass()) == false);

		// single inheritance invalid cross-cast
		test_assert(librarian->getInstanceClass().derivesFrom(teacher->getInstanceClass()) == false);

		// multiple inheritance 1 level valid upcast
		test_assert(teachingLibrarian->getInstanceClass().derivesFrom(librarian->getInstanceClass()));

		// multiple inheritance 2 level valid upcast
		test_assert(teachingLibrarian->getInstanceClass().derivesFrom(staff->getInstanceClass()));

		// multiple inheritance 1 level invalid upcast
		test_assert(teachingLibrarian->getInstanceClass().derivesFrom(sailboat->getInstanceClass()) == false);

		delete staff;
		delete librarian;
		delete teacher;
		delete teachingLibrarian;
		delete sailboat;

		std::cout << "Classful tests successful" << std::endl;
	}

	// must be called AFTER the classful test to be valid
	void reflectionTest()
	{
		// getting existing class by name
		test_assert(Reflection::getSingleton().findClass("Sailboat") != 0);
		test_assert(&Sailboat::getClass() != 0);
		test_assert(Reflection::getSingleton().findClass("Sailboat") == &Sailboat::getClass());

		// getting nonexistant class by name
		test_assert(Reflection::getSingleton().findClass("ASFJasdf") == 0);

		// getting existing class by hashed name
		test_assert(Reflection::getSingleton().findClass(HashedString("Sailboat")) == &Sailboat::getClass());

		// getting nonexistant class by hashed name
		test_assert(Reflection::getSingleton().findClass(HashedString("ASFJasdf")) == 0);

		// getting class that exists but was not used previously
		test_assert(Reflection::getSingleton().findClass("Dog") != 0);

		// print all classes for sanity check
		std::cout << "reflection debug information:" << std::endl;
		Reflection::getSingleton().debugPrint();

		std::cout << "Reflection tests successful" << std::endl;
	}

public:
	void testAll()
	{
		classlessRTTITest();
		classfulRTTITest();
		reflectionTest();
	}
};

int main()
{
	UnitTest test;
	test.testAll();
	generateReport();
}

