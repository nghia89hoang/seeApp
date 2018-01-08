#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "ViewController.hpp"
#include "poScene/Scene.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class seeApp : public App {
  public:
	void setup() override;
    void mouseDown( ci::app::MouseEvent event ) override;
    void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
private:
#pragma mark FUNC
    void printDevice();
    void setupCamera();
    void updateCapture();
    void drawMainTex();
#pragma -
    see::ViewControllerRef mVc;
    SceneRef mScene;
    gl::TextureRef mMaintex;
};

void seeApp::setup()
{
    mVc = see::ViewController::create();
    mScene = Scene::create(mVc);
    setFrameRate(30.0f);
}

void seeApp::update()
{
    mScene->update();
}

void seeApp::draw()
{
    mScene->draw();
}

void seeApp::mouseDown( ci::app::MouseEvent event)
{
}

void seeApp::keyDown(cinder::app::KeyEvent event) {
    
}
CINDER_APP( seeApp, RendererGl )
