#include "ExampleEntries.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "EmptyExample.h"


#include "../SoftDemo/SoftDemo.h"


#include "../Constraints/TestHingeTorque.h"




//Extended Tutorial Includes Added by Mobeen and Benelot

struct ExampleEntry
{
	int									m_menuLevel;
	const char*							m_name;
	const char*							m_description;
	CommonExampleInterface::CreateFunc*		m_createFunc;
	int									m_option;

	ExampleEntry(int menuLevel, const char* name)
		:m_menuLevel(menuLevel), m_name(name), m_description(0), m_createFunc(0), m_option(0)
	{
	}

	ExampleEntry(int menuLevel, const char* name,const char* description, CommonExampleInterface::CreateFunc* createFunc, int option=0)
		:m_menuLevel(menuLevel), m_name(name), m_description(description), m_createFunc(createFunc), m_option(option)
	{
	}
};



static ExampleEntry gDefaultExamples[]=
{

	ExampleEntry(0,"API"),
	
    ExampleEntry(1,"TestHingeTorque", "Apply a torque in the hinge axis. This example uses a btHingeConstraint and btRigidBody. The setup is similar to the multi body example TestJointTorque.",
                 TestHingeTorqueCreateFunc),


};


static btAlignedObjectArray<ExampleEntry> gAdditionalRegisteredExamples;


struct ExampleEntriesInternalData
{
	btAlignedObjectArray<ExampleEntry> m_allExamples;
};

ExampleEntriesAll::ExampleEntriesAll()
{
	m_data = new ExampleEntriesInternalData;
}

ExampleEntriesAll::~ExampleEntriesAll()
{
	delete m_data;
}

void ExampleEntriesAll::initOpenCLExampleEntries()
{
#ifdef B3_USE_CLEW
#ifndef NO_OPENGL3
	int numDefaultEntries = sizeof(gOpenCLExamples)/sizeof(ExampleEntry);
	for (int i=0;i<numDefaultEntries;i++)
	{
		m_data->m_allExamples.push_back(gOpenCLExamples[i]);
	}
#endif
#endif //B3_USE_CLEW
}

void ExampleEntriesAll::initExampleEntries()
{
	m_data->m_allExamples.clear();

	for (int i=0;i<gAdditionalRegisteredExamples.size();i++)
	{
		m_data->m_allExamples.push_back(gAdditionalRegisteredExamples[i]);
	}



	int numDefaultEntries = sizeof(gDefaultExamples)/sizeof(ExampleEntry);
	for (int i=0;i<numDefaultEntries;i++)
	{
		m_data->m_allExamples.push_back(gDefaultExamples[i]);
	}

	if (m_data->m_allExamples.size()==0)
	{

		{
			ExampleEntry e(0,"Empty");
			m_data->m_allExamples.push_back(e);
		}

		{
			ExampleEntry e(1,"Empty","Empty Description", EmptyExample::CreateFunc);
			m_data->m_allExamples.push_back(e);
		}
	}

}

void ExampleEntriesAll::registerExampleEntry(int menuLevel, const char* name,const char* description, CommonExampleInterface::CreateFunc* createFunc, int option)
{
	ExampleEntry e( menuLevel,name,description, createFunc, option);
	gAdditionalRegisteredExamples.push_back(e);
}

int ExampleEntriesAll::getNumRegisteredExamples()
{
	return m_data->m_allExamples.size();
}

CommonExampleInterface::CreateFunc* ExampleEntriesAll::getExampleCreateFunc(int index)
{
	return m_data->m_allExamples[index].m_createFunc;
}

int ExampleEntriesAll::getExampleOption(int index)
{
	return m_data->m_allExamples[index].m_option;
}

const char* ExampleEntriesAll::getExampleName(int index)
{
	return m_data->m_allExamples[index].m_name;
}

const char* ExampleEntriesAll::getExampleDescription(int index)
{
	return m_data->m_allExamples[index].m_description;
}
