#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "ViewController.hpp"
#include "poScene/Scene.h"
#include "MainViewController.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

MainViewController *sMainViewController = [[MainViewController alloc] init];

class seeApp : public App {
  public:
	void setup() override;
    void mouseDown( ci::app::MouseEvent event ) override;
    void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
    
    static void prepareSettings(Settings *setting);
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
#if 1
    [sMainViewController addCinderViewToFront];
#else
    [sMainViewController addCinderViewAsBarButton];
#endif
    mVc = see::ViewController::create();
    mScene = Scene::create(mVc);
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

void seeApp::prepareSettings(cinder::app::AppCocoaTouch::Settings *settings) {
    settings->prepareWindow(Window::Format().rootViewController(sMainViewController));
    settings->setFrameRate(30.0f);
}


CINDER_APP( seeApp, RendererGl, seeApp::prepareSettings )
