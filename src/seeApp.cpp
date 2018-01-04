#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class seeApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void seeApp::setup()
{
}

void seeApp::mouseDown( MouseEvent event )
{
}

void seeApp::update()
{
}

void seeApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( seeApp, RendererGl )
