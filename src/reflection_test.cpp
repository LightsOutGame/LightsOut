#include "reflector.h"
#include "macros.h"

class testClass {

	#define FIELDS \
    REFLECT((int) x) \
    REFLECT((char) y)

	#include "reflection_body.h"
};

class testSubclass {

	#define FIELDS \
    REFLECT((bool) a) \
    REFLECT((float) b)

	#include "reflection_body.h"
};


int main(int argc, char** argv)
{

	reflector::getAllFields<testClass>();
	reflector::getAllFields<testSubclass>();


	int a;
	cin >> a;

	return 0;
}