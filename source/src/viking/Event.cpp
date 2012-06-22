#include "viking/Event.hpp"
#include "viking/GameApp.hpp"

namespace vik
{

Event::Event():
timeStamp(GameApp::getSingleton().getTimer()->getRealTime())
{
}

} // end namespace vik
