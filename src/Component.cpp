#include "Component.h"
#include "GameObject.h"
using namespace std;

Component::Component(GameObject& associated) : associated(associated){}

Component::~Component(){}