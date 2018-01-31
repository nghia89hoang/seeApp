#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "ViewController.hpp"
#include "poScene/Scene.h"
#if defined(CINDER_COCOA_TOUCH)
    #include "MainViewController.h"
#endif

#define SCREEN_W (800)
#define SCREEN_H (600)

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;
#if defined(CINDER_COCOA_TOUCH)
MainViewController *sMainViewController = [[MainViewController alloc] init];
#endif
class seeApp : public App {
  public:
	void setup() override;
    void mouseDown( ci::app::MouseEvent event ) override;
    void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
    
    static void prepareSettings(Settings *setting);
private:
    void onNextView();
    void onPrevView();
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
#if defined(CINDER_COCOA_TOUCH)
    #if 1
        [sMainViewController addCinderViewToFront];
    #else
        [sMainViewController addCinderViewAsBarButton];
    #endif
#endif
    mVc = see::ViewController::create();
    mScene = Scene::create(mVc);
#if defined(CINDER_COCOA_TOUCH)
    [sMainViewController setPrevButtonCallback: bind(&seeApp::onPrevView, this)];
    [sMainViewController setNextButtonCallback: bind(&seeApp::onNextView, this)];
#endif
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
    switch(event.getCode()) {
        case KeyEvent::KEY_LEFT:
            onPrevView();
            break;
        case KeyEvent::KEY_RIGHT:
            onNextView();
            break;
        case KeyEvent::KEY_1:
        case KeyEvent::KEY_2:
            mVc->keyDown(event);
            break;
    }
}
#if defined(CINDER_COCOA_TOUCH)
void seeApp::prepareSettings(cinder::app::AppCocoaTouch::Settings *settings) {
    settings->prepareWindow(Window::Format().rootViewController(sMainViewController));
    settings->setFrameRate(30.0f);    
}
#else
void seeApp::prepareSettings(cinder::app::AppBase::Settings *setting) {
    setting->setFrameRate(30.0f);
    setting->setWindowSize(SCREEN_W, SCREEN_H);
}
#endif
void seeApp::onNextView() {
    mVc->changeView(true);
}
void seeApp::onPrevView() {
    mVc->changeView(false);
}

CINDER_APP( seeApp, RendererGl, seeApp::prepareSettings )
